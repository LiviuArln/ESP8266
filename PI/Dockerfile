FROM pablogn/rospiduino
ADD heart.ino .
ADD Makefile .
ADD makeEspArduino.mk .
RUN sudo mkdir -p /usr/share/arduino/hardware/esp8266com/esp8266
RUN cd /usr/share/arduino/hardware/esp8266com && sudo git clone https://github.com/esp8266/Arduino.git esp8266
RUN cd /usr/share/arduino/hardware/esp8266com/esp8266/tools && sudo python get.py


