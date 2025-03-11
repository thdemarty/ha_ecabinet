FROM python:3.11.1-slim

WORKDIR /app

COPY requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt
RUN apt-get update && apt-get install -y git
RUN git clone https://github.com/hassio-addons/bashio.git /bashio

COPY main.py main.py
COPY automations.py automations.py
COPY start.sh start.sh

EXPOSE 8001

CMD ["/bin/bash", "start.sh"]