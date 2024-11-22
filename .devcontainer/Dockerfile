FROM gcc:bookworm
RUN echo 'deb http://deb.debian.org/debian bookworm-backports main' > /etc/apt/sources.list.d/backports.list
RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y cmake 
RUN apt-get install -y gcc-arm-none-eabi
RUN apt-get install -y build-essential
RUN apt-get install -y git
RUN apt-get install -y g++