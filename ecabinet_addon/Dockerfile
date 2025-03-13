ARG BUILD_FROM
FROM $BUILD_FROM


RUN \
  apk add --no-cache \
    python3

RUN apt-get install --no-install-recommends -y gnupg gpg-agent \
      && apt-get --no-install-recommends install -y \
      build-essential \
      python3-dev \
      python3 \
      python3-setuptools \
      python3-pip
      
WORKDIR /app

COPY requirements.txt ./
RUN pip3 install --no-cache-dir -r requirements.txt
COPY main.py main.py
COPY automations.py automations.py

EXPOSE 8001

COPY run.sh /
RUN chmod a+x /run.sh
CMD [ "/run.sh" ]

