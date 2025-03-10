FROM python:3.11.1-slim

WORKDIR /app

COPY requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt

COPY main.py main.py
COPY automations.py automations.py
COPY start.sh start.sh

EXPOSE 8001

CMD ["/bin/bash", "start.sh"]