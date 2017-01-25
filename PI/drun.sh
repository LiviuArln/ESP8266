#!/bin/sh
docker run \
	--name acompiler \
	-h acompiler \
	-it \
	-v /home/pi/rpd:/home/pi/rpd \
	--group-add dialout \
	--device=/dev/ttyUSB0:/dev/ttyUSB0:rw \
	arduino-compiler
