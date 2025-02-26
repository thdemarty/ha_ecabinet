ARG BUILD_FROM
FROM $BUILD_FROM

# Install requirements for add-on
RUN apk add --no-cache python3 py3-pip

# Install via pip
RUN pip3 install "fastapi[standard]"

WORKDIR /app

COPY run.sh /
RUN chmod +x /run.sh

COPY ./api/main.py /main.py
COPY ./api/db.sqlite /db.sqlite

CMD ["/run.sh"]