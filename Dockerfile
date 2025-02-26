ARG BUILD_FROM
FROM $BUILD_FROM

# Install requirements for add-on
CMD ["/bin/bash", "-o", "pipefail", "-c"]
RUN \
    apk add --no-cache \
         python3 \
             py3-pip \
     \
     && pip3 install fastapi[standard]

WORKDIR /app

COPY run.sh /
RUN chmod +x /run.sh

COPY ./api/main.py /main.py
COPY ./api/db.sqlite /db.sqlite

CMD ["/run.sh"]