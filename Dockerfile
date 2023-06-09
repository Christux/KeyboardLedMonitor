FROM alpine AS builder

LABEL autodelete="true"

RUN set -ex && apk add gcc make musl-dev linux-headers

WORKDIR /usr/src/app

COPY *.h .
COPY *.c .
COPY Makefile .

RUN make klm

FROM alpine

WORKDIR /usr/sbin

COPY --from=builder /usr/src/app/klm ./klm

CMD ["./klm", "-k", "/dev/tty1"]
