#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pcap.h>
#include <err.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "pcap_layers.h"

struct _foo {
	struct in_addr src;
	struct in_addr dst;
	unsigned short qtype;
	/* etc... */
};

/*
 * this will only be called if 'ip' is a complete IPv header
 */
int
my_ip4_handler(const struct ip *ip4, int len, void *userdata)
{
    fprintf(stderr, "got IPv4 layer, src=%s\n", inet_ntoa(ip4->ip_src));
    return 0;
}

int
my_dns_handler(const u_char *buf, int len, void *userdata)
{
    fprintf(stderr, "got DNS layer, %d bytes\n", len);
    return 0;
}

int
main(int argc, char *argv[])
{
    pcap_t *in = NULL;
    char errbuf[PCAP_ERRBUF_SIZE + 1];
    struct pcap_pkthdr hdr;
    const u_char *data;

    in = pcap_open_offline("-", errbuf);
    if (NULL == in) {
	fprintf(stderr, "stdin: %s", errbuf);
	exit(1);
    }

    pcap_layers_init(pcap_datalink(in), 1);
    callback_ipv4 = my_ip4_handler;
    callback_l7 = my_dns_handler;

    while ((data = pcap_next(in, &hdr))) {
	    struct _foo f;
	    memset(&f, 0, sizeof(f));
	    handle_pcap((u_char *) &f, &hdr, data);
    }

    pcap_close(in);
    exit(0);
}

