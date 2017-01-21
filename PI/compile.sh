#!/bin/sh
docker run --name rospiduino -h rospiduino -it -v /home/pi/rpd:/home/pi/rpd --group-add dialout --device=/dev/ttyACM0:/dev/ttyACM0:rw pablogn/rospiduino