ARG BUILD_FROM
FROM $BUILD_FROM

RUN apk update && apk add --no-cache \
    python3 \
    build-base \
    python3-dev \
    gnupg \
    gpg-agent

WORKDIR /app

# Créer un environnement virtuel
RUN python3 -m venv /app/venv

COPY requirements.txt ./

# Activer l'environnement virtuel et installer les dépendances
RUN /app/venv/bin/pip install --break-system-packages -r requirements.txt

COPY main.py main.py
COPY automations.py automations.py

EXPOSE 8001

COPY run.sh /
RUN chmod a+x /run.sh
CMD [ "/run.sh" ]