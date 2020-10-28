FROM ubuntu:latest

ENV DEBIAN_FRONTEND="noninteractive" TZ="Europe/London"

RUN apt update && apt install cmake make gcc g++ clang libsdl2-2.0-0 libsdl2-dev -y

CMD [ "mkdir", "workspace"  ]
