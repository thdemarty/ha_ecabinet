#!/bin/bash
MQTT_HOST=$(bashio::services mqtt "host")
MQTT_USER=$(bashio::services mqtt "username")
MQTT_PASSWORD=$(bashio::services mqtt "password")

uvicorn main:app --host 0.0.0.0 --port 8080 &
python automations.py