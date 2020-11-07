FROM ubuntu:latest

ENV DEBIAN_FRONTEND="noninteractive" TZ="Europe/London"

RUN apt update && apt install cmake make gcc g++ clang libsdl2-2.0-0 libsdl2-dev -y

RUN apt install libgl1-mesa-dev libglew-dev libsdl2-image-dev libglm-dev libfreetype6-dev -y

RUN apt install freeglut3 freeglut3-dev -y

CMD [ "mkdir", "workspace"  ]

WORKDIR /workspace
