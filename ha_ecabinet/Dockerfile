FROM python:3.11.1-slim

WORKDIR /app

RUN apt-get update && apt-get install -y git

COPY requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt
RUN git clone https://github.com/hassio-addons/bashio.git /bashio
RUN ls -l /bashio/lib/
RUN chmod +x /bashio/lib/bashio

COPY main.py main.py
COPY automations.py automations.py
COPY start.sh start.sh

EXPOSE 8001

CMD ["/bin/bash", "start.sh"]