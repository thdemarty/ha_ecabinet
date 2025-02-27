ARG BUILD_FROM
FROM $BUILD_FROM

# Install requirements for add-on
COPY addon_deps.sh /
RUN a+x addon_deps.sh
RUN ./addon_deps.sh

RUN chmod +x addon_deps.sh
RUN \
    apk add --no-cache \
        python3 \
        py3-pip \
     && pip3 install fastapi[standard]

WORKDIR /app

COPY run.sh /
RUN chmod +x /run.sh

COPY ./ha_ecabinet/main.py /main.py
COPY ./ha_ecabinet/db.sqlite /db.sqlite

CMD ["/run.sh"]