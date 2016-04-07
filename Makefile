NAME=pcap_layers
LIB=lib${NAME}.a
CFLAGS=-Wall -O2
PREFIX=/usr/local


all: ${LIB}

${LIB}: ${NAME}.o
	ar r $@ ${NAME}.o

${NAME}.o: ${NAME}.c ${NAME}.h

demo: demo.c ${NAME}.o ${NAME}.h
	${CC} ${CFLAGS} -o $@ -I. demo.c ${NAME}.o -lpcap

install: ${LIB}
	install -d -m 755 ${PREFIX}/lib
	install -d -m 755 ${PREFIX}/include
	install -C -m 644 ${LIB} ${PREFIX}/lib
	install -C -m 644 ${NAME}.h ${PREFIX}/include
	install -C -m 644 byteorder.h ${PREFIX}/include/pcap_layers_byteorder.h

clean:
	rm -f ${NAME}.o
	rm -f ${LIB}
	rm -f demo
