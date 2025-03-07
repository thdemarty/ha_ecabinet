import os
import paho.mqtt.client as mqtt
import re
import requests


#MQTT_HOST = os.environ.get("MQTT_HOST")
#MQTT_USER = os.environ.get("MQTT_USER")
#MQTT_PASSWORD = os.environ.get("MQTT_PASSWORD")

MQTT_HOST = "192.168.0.69"
MQTT_USER = "arnaud"
MQTT_PASSWORD = "arnaud"


def callback(client, userdata, msg):
    # Regex pour extraire l'ID et l'action
    match = re.match(r"cabinet/(\d+)/(add|return)", msg.topic)
    if match:
        item_id = match.group(1)
        action = match.group(2)
        item_content = msg.payload.decode()  # Décoder le payload en string

        # Construire l'URL de la requête backend
        backend_url = f"http://{MQTT_HOST}:8001/items/salt/{action}"

        # Envoyer la requête au backend (à adapter selon votre backend)
        try:
            response = requests.post(backend_url, data={})  # Remplacer data={} par les données nécessaires
            response.raise_for_status()  # Lever une exception en cas d'erreur HTTP
            data = response.json()
            if (data.absent == 0):
                client.publish('cabinet/1/status','OK')
            print(f"Requête envoyée avec succès à {backend_url}")
        except requests.exceptions.RequestException as e:
            print(f"Erreur lors de l'envoi de la requête : {e}")
    else:
        print("Topic MQTT non reconnu")


client = mqtt.Client()
client.username_pw_set(MQTT_USER, MQTT_PASSWORD)
#client.connect(MQTT_HOST)
client.on_message = callback


def mqttloop():
    if (client.is_connected() != True):
        reconnect()
    client.loop()
        
def reconnect():
    if (client.connect(MQTT_HOST) == 0):
        print('connected')
        client.subscribe('cabinet/#') #listen all cabinet
    else:
        print('Error connecting mqtt broker')
# Exemple de publication
run = True
while run:
    mqttloop()

client.disconnect()