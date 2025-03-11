ARG BUILD_FROM
FROM $BUILD_FROM

WORKDIR /app

COPY requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt
COPY main.py main.py
COPY automations.py automations.py

EXPOSE 8001

COPY run.sh /
RUN chmod a+x /run.sh
CMD [ "/run.sh" ]

