#!/bin/sh
apt-get update
apt-get install -Y git
git clone https://github.com/LiviuArln/ESP8266.git
curl -sSL https://get.docker.com | sh
sudo usermod -aG docker pi