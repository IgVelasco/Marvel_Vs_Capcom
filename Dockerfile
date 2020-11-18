FROM ubuntu:latest

WORKDIR /app

ENV TZ=Europe/Kiev
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt update && apt-get install -y
RUN apt install make cmake g++ libsdl2-dev libsdl2-mixer-dev libsdl2-image-dev -y

COPY . ./app


EXPOSE 6996

CMD ["cmake"]

