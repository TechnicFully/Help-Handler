# syntax=docker/dockerfile:1
FROM ubuntu:22.04


### Dependencies
RUN ln -snf /usr/share/zoneinfo/$CONTAINER_TIMEZONE /etc/localtime && echo $CONTAINER_TIMEZONE > /etc/timezone #Needed to prevent query when adding PPAs
RUN apt-get update
RUN apt-get install -y software-properties-common tox
RUN add-apt-repository ppa:deadsnakes/ppa
RUN apt-get update
RUN apt install -y python2
RUN apt install -y python3.7
RUN apt install -y python3.8
RUN apt install -y python3.9
RUN apt install -y python3.10
RUN apt install -y python3.11
RUN apt install -y python3.12
RUN apt install -y python3.13

### Compile
WORKDIR /app/test/
COPY ./help_handler.py /app
COPY test/ /app/test/

### Run
CMD [ "tox" ]
