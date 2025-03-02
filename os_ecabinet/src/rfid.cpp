#include "rfid.h"

const uint8_t customAddress = 0x28;

TwoWire &customI2C = Wire;

MFRC522DriverI2C driver{customAddress, customI2C}; // Create I2C driver.

MFRC522 mfrc522{driver}; // Create MFRC522 instance.

uint8_t init_status = 0;
uint8_t flag_i2c_test_failed = 0;

std::vector<std::vector<byte>> previous_UIDs;

//  M5.Display.printf("SCL -> 22   SDA -> 21");
bool rfid_setup(void)
{
    bool res = 0;

    if (i2c_check(0x28)) {
        res = mfrc522.PCD_Init();
        delay(5);
        MFRC522Debug::PCD_DumpVersionToSerial(mfrc522, Serial);    
    } else {
        flag_i2c_test_failed = 1;
    }

    if (res) init_status = 1;
    else init_status = 0;

    return res;
}

void rfid_debugprint_details(byte *uid, byte *length) 
{
    if ( !mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
        return;
    }
    Serial.print(F("Card UID:"));
    *length = mfrc522.uid.size;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        uid[i] = mfrc522.uid.uidByte[i];
    }
    Serial.println();  
    // Pour encore PLUS de données décommenter ça : 
    //MFRC522Debug::PICC_DumpToSerial(mfrc522, Serial, &(mfrc522.uid));
}

std::string uid_to_hex_string(const std::vector<byte>& uid) {
    std::ostringstream oss;
    for (byte b : uid) {
        oss << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << (int)b;
    }
    return oss.str();
}

bool is_UID_preseent(const std::vector<byte>& uid, const std::vector<std::vector<byte>>& uid_list) {
    for (const auto& u : uid_list) {
        if (u == uid) {
            return true;
        }
    }
    return false;
}

void loop_UIDs(byte *uid_b, byte *length) {
    std::vector<std::vector<byte>> current_UIDs;

    while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
            *length = mfrc522.uid.size;

            std::vector<byte> uid_v(*length);
            for (byte i = 0; i < mfrc522.uid.size; i++) {
                uid_b[i] = mfrc522.uid.uidByte[i];
                uid_v[i] = mfrc522.uid.uidByte[i];
            }

            if (!is_UID_preseent(uid_v, previous_UIDs)) {
                Serial.print(F("Nouveau UID ajouté:"));
                std::string uid_str = uid_to_hex_string(uid_v);
                Serial.println(uid_str.c_str());
                
                char topic[30];
                sprintf(topic, "cabinet/%d/add", get_cabinet_id());
                mqtt_publish(topic, const_cast<char*>(uid_str.c_str()));
            }

            current_UIDs.push_back(uid_v);
            // mfrc522.PICC_HaltA(); // pour stopper la lecture
    }
    for (const auto &uid_p : previous_UIDs) {
        if (!is_UID_preseent(uid_p, current_UIDs)) {
            Serial.print(F("UID retiré:"));
            std::string uid_str = uid_to_hex_string(uid_p);
            Serial.println(uid_str.c_str());

            char topic[30];
            sprintf(topic, "cabinet/%d/remove", get_cabinet_id());
            mqtt_publish(topic, const_cast<char*>(uid_str.c_str()));
            show_removal(get_cabinet_id());
        }
    }
    previous_UIDs = current_UIDs;
}
