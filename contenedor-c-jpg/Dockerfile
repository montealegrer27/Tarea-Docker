FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    libjpeg-dev \
    make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

CMD ["make", "run"]