NAME=pcap_layers
LIB=lib${NAME}.a
CFLAGS=-Wall -O2


all: ${LIB}

${LIB}: ${NAME}.o
	ar r $@ ${NAME}.o

${NAME}.o: ${NAME}.c ${NAME}.h

demo: demo.c ${NAME}.o ${NAME}.h
	${CC} ${CFLAGS} -o $@ -I. demo.c ${NAME}.o -lpcap

install: ${LIB}
	install -C -m 644 ${LIB} /usr/local/lib
	install -C -m 644 ${NAME}.h /usr/local/include
	install -C -m 644 byteorder.h /usr/local/include/pcap_layers_byteorder.h

clean:
	rm -f ${NAME}.o
	rm -f ${LIB}
	rm -f demo
