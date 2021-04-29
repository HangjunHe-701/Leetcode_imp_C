
#if 0
sockaddr/sockaddr_in/in_addr (IPv4)、sockaddr6_in/in6_addr/addrinfo (IPv6)

struct sockaddr {  
      unsigned short sa_family;     　　　　/* address family, AF_xxx */ 
      char sa_data[14];                  　/* 14 bytes of protocol address */ 
};  


#if ULONG_MAX > 0xffffffff
#define __ss_aligntype __uint64_t
#else
#define __ss_aligntype __uint32_t
#endif
#define _SS_SIZE		128
#define _SS_PADSIZE 	(_SS_SIZE - (2 * sizeof (__ss_aligntype)))
struct sockaddr_storage
{
 	sa_family_t ss_family;		/* Address family */
 	__ss_aligntype __ss_align;	/* Force desired alignment.  */
 	char __ss_padding[_SS_PADSIZE];
};

struct sockaddr_in {  
      short int sin_family;                /* Address family AF_INET */ 
      unsigned short int sin_port;    　　　/* Port number */ 
      struct in_addr sin_addr;         　　/* Internet address */ 
      unsigned char sin_zero[8];     　　　/* Same size as struct sockaddr */ 
};  <br>
struct in_addr {  
      unsigned long s_addr;           　　/* Internet address */ 
};  
   
struct sockaddr_in6 {  
      sa_family_t sin6_family;         　　/* AF_INET6 */ 
      in_port_t sin6_port;                /* transport layer port # */ 
      uint32_t sin6_flowinfo;           　 /* IPv6 traffic class & flow info */ 
      struct in6_addr sin6_addr;    　　　 /* IPv6 address */ 
      uint32_t sin6_scope_id;        　　　/* set of interfaces for a scope */ 
};  
struct in6_addr {  
      uint8_t s6_addr[16];            　　/* IPv6 address */ 
};  
   
struct addrinfo{  
      int ai_flags;                         /* AI_PASSIVE,AI_CANONNAME,AI_NUMERICHOST */ 
      int ai_family;                        /* AF_INET,AF_INET6 */ 
      int ai_socktype;                   　　/* SOCK_STREAM,SOCK_DGRAM */ 
      int ai_protocol;                   　　/* IPPROTO_IP, IPPROTO_IPV4, IPPROTO_IPV6 */ 
      size_t ai_addrlen;               　　　/* Length */ 
      char *ai_cannoname;         　　　　　　/* */ 
      struct sockaddr *ai_addr;  　　　　　　 /* struct sockaddr */ 
      struct addrinfo *ai_next;     　　　　 /* pNext */ 
}  
#endif

/*
1. inet_ntoa/inet_aton来转化字符串形式表示的IPv4地址和数字形式表示的IPv4地址。此两函数不适用于IPv6地址转换。在Linux环境下使用inet_ntoa/inet_atoa时，需加头文件：

int inet_aton(const char * cp,struct in_addr *inp);
char * inet_ntoa(struct in_addr in);

2. IPv6中，使用inet_ntop/inet_pton来转化字符串形式表示的IPv6地址和数字形式表示的IPv6地址。IPv4中也可使用这两个函数。

函数原型：
//这个函数转换字符串到网络地址，第一个参数af是地址族，转换后存在dst中 af的值可为AF_INET (代表使用IPv4协议）或AF_INET6（代表作用IPv6协议）
int inet_pton(int af, const char *src, void *dst);
const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt);
//这个函数转换网络二进制结构到ASCII类型的地址，参数的作用和上面相同，只是多了一个参数socklen_t cnt,
//他是所指向缓存区dst的大小，避免溢出，如果缓存区太小无法存储地址的值，则返回一个空指针，并将errno置为ENOSPC
*/

#include <stdlib.h> 
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include "misc.h" 

/* ip is in network order */
#define AH_IN_MULTICAST(ip) (((ip) & htonl(0xf0000000)) == htonl(0xe0000000))  

#define AH_IPV4_LINK_LOCAL_SUBNET 0xA9FE0000 // 169.254.0.0
#define AH_IPV4_LINK_LOCAL_MASK   0xFFFF0000 // slash 16
/* ip is big endian format */
#define AH_IS_LINK_LOCAL_ADDR(ip)               \
        (((ip) & AH_IPV4_LINK_LOCAL_MASK) == AH_IPV4_LINK_LOCAL_SUBNET)


/* RFC 1918 "Address Allocation for Private Internets" defines the IPv4
 * private address space as the following:
 *
 * 10.0.0.0 - 10.255.255.255 (10/8 prefix)
 * 172.16.0.0.0 - 172.31.255.255 (172.16/12 prefix)
 * 192.168.0.0 - 192.168.255.255 (192.168/16 prefix)
 */
#define AH_IS_IPV4_PRIVATE_ADDRESS(a) \
	((((unsigned char *)(a))[0] == 10) || \
	((((unsigned char *)(a))[0] == 172) && \
	(((unsigned char *)(a))[1] >= 16) && \
	(((unsigned char *)(a))[1] < 32)) || \
	((((unsigned char *)(a))[0] == 192) && \
	(((unsigned char *)(a))[1] == 168)))



bool NetworkGetAddressForHost(char *host, struct sockaddr_storage *addrPtr) {

	struct addrinfo hints, *res, *ressave;
	char serviceName[5];
	int sock;
	char str[INET6_ADDRSTRLEN];
	
	if(host == NULL || addrPtr == NULL)
		return false;
	
	memset(&hints, 0, sizeof(struct addrinfo));


	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	
	/* endianness will be handled by getaddrinfo */
	//snprintf(serviceName, 5, "%d", CW_CONTROL_PORT);
	
	if (getaddrinfo(host, NULL, &hints, &res) !=0 ) {

		return false;
	}
	
	ressave = res;
	
	do {
		if((sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0) {
			/* try next address */
			continue;
		}
		/* success */
		break;
	} while ( (res = res->ai_next) != NULL);
	
	close(sock);
	
	if(res == NULL) { 
		/* error on last iteration */
		//CWNetworkRaiseSystemError(CW_ERROR_CREATING);
	}

	if(inet_ntop(res->ai_family, &res->ai_addr, str, INET6_ADDRSTRLEN) == NULL){       
        printf("inet ntop failed\n");     
        return false;     
    }     
           
    printf("%s\n", str);  
	
	memcpy(addrPtr, (res->ai_addr), sizeof(*addrPtr));
	freeaddrinfo(ressave);
	
	return true;
}



int main(int argc, char **argv)     
{     
	struct in6_addr addr6;
    int domain, s;     
    char str[INET6_ADDRSTRLEN];  

	struct in_addr addr1;
    ulong l1;
	struct sockaddr_storage ss;

	
    l1 = inet_addr("192.168.0.74");
    memcpy(&addr1, &l1, sizeof(l1));
	// IP addr string
    printf("%s\n", inet_ntoa(addr1));
	if(inet_aton("127.0.0.1", &addr1)){
		printf("inet_aton:ip=%lu\n", ntohl(addr1.s_addr));
	}
	else{
		printf("inet_aton return -1 when 255.255.255.255\n");
	}
           
    if(argc != 3){     
        fprintf(stderr, "usage: %s {i4|i6|<num>} string/n", argv[0]);     
        exit(EXIT_FAILURE);     
    }     

	//IPv6 start
    domain = (strcmp(argv[1], "i4") == 0) ? AF_INET:(strcmp(argv[1], "i6") == 0) ? AF_INET6 : atoi(argv[1]);     
               
    //IP字符串 ——》网络字节流  
    printf("IP string %s domain %d AF_INET = %d AF_INET6 = %d\n", argv[2], domain, AF_INET, AF_INET6);
    s = inet_pton(domain, argv[2], &addr6);     
    if(s<=0){     
        if(0 == s)     
            fprintf(stderr, "Not in presentation format/n");     
        else
            perror("inet_pton");     
        exit(EXIT_FAILURE);     
    } 
           
    //网络字节流 ——》IP字符串     
    if(inet_ntop(domain, &addr6, str, INET6_ADDRSTRLEN) == NULL){       
        perror("inet ntop");     
        exit(EXIT_FAILURE);     
    }     
           
    printf("%s\n", str);  

	printf("NetworkGetAddressForHost %s\n", NetworkGetAddressForHost ("baidu.com", &ss)? "true" : "false");  
	
    exit(EXIT_SUCCESS);     
}

