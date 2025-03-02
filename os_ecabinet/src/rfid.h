#ifndef RFID_H
#define RFID_H
#include "closet.h"
#include <MFRC522v2.h>
#include <MFRC522DriverI2C.h>
#include <MFRC522Debug.h>
#include "mqtt.h"
#include "led_matrix.h"
#include "i2c.h"
#include "closet.h"
#include <sstream>
#include <iomanip>
#include <vector>
#endif
extern uint8_t init_status;

bool rfid_setup(void);
void rfid_debugprint_details(byte *uid, byte *length);
bool is_UID_preseent(const std::vector<byte> &uid, const std::vector<std::vector<byte>> &uid_list);
void loop_UIDs(byte *uid, byte *length);
