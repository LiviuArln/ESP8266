FROM resin/rpi-raspbian:jessie

RUN apt-get update && apt-get install -y wget 
RUN wget -q -O - https://repo.mosquitto.org/debian/mosquitto-repo.gpg.key | apt-key add - && \
    wget -q -O /etc/apt/sources.list.d/mosquitto-jessie.list https://repo.mosquitto.org/debian/mosquitto-jessie.list && \
    apt-get update 
RUN apt-get install -y mosquitto && \
    adduser --system --disabled-password --disabled-login mosquitto

RUN mkdir -p /mqtt/config /mqtt/data /mqtt/log
COPY config /mqtt/config
RUN chown -R mosquitto:mosquitto /mqtt
VOLUME ["/mqtt/config", "/mqtt/data", "/mqtt/log"]


EXPOSE 1883 9001
CMD /usr/sbin/mosquitto -v -c /mqtt/config/mosquitto.conf

