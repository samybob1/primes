FROM ubuntu as builder
LABEL maintainer "Wassim DHIF <wassimdhif@gmail.com>"

WORKDIR /primes

COPY . .
RUN apt-get update && apt-get install build-essential cmake -y && cmake . && make

FROM ubuntu
LABEL maintainer "Wassim DHIF <wassimdhif@gmail.com>"

COPY --from=builder /primes/primes .

ENTRYPOINT ["./primes"]

