/*
 * Copyright (c) 2016 Duane Wessels and The Measurement Factory, Inc.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip6.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <sys/socket.h>
#include <net/if_arp.h>
#include <net/if.h>
#include <netinet/if_ether.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>

typedef int l7_callback(const u_char *, int , void *);

extern int (*callback_ether) (const u_char * pkt, int len, void *userdata);
extern int (*callback_vlan) (unsigned short vlan, void *userdata);
extern int (*callback_ipv4) (const struct ip *ipv4, int len, void *userdata);
extern int (*callback_ipv6) (const struct ip6_hdr *ipv6, int len, void *userdata);
extern int (*callback_gre) (const u_char *pkt, int len, void *userdata);
extern int (*callback_tcp) (const struct tcphdr *tcp, int len, void *userdata);
extern int (*callback_udp) (const struct udphdr *udp, int len, void *userdata);
extern int (*callback_tcp_sess) (const struct tcphdr *tcp, int len, void *userdata, l7_callback *);
extern int (*callback_l7) (const u_char * l7, int len, void *userdata);

extern void handle_pcap(u_char * userdata, const struct pcap_pkthdr *hdr, const u_char * pkt);
extern int pcap_layers_init(int dlt, int reassemble);
