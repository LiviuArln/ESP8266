#!/bin/sh
docker rm acompiler
docker rmi arduino-compiler
docker build -t arduino-compiler .