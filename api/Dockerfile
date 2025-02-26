FROM python:3.11.1-slim

WORKDIR /app

RUN pip install "fastapi[standard]"

COPY db.sqlite db.sqlite
COPY main.py main.py

EXPOSE 8000

CMD ["fastapi", "dev", "main.py", "--host", "0.0.0.0"]


