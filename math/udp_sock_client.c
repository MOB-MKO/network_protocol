#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include "udp_sock.h"

#define MAXBUF 3

int main()
{ int sockfd, len,i;
  unsigned char buf[MAXBUF];
  struct sockaddr_in udp_server_addr;
  socklen_t addr_size;

  sockfd = socket(PF_INET, SOCK_DGRAM, 0); // create a UDP socket
  if(sockfd<=0) { printf("socket error !\n"); return 0; }

  /* configure settings to communicate with remote UDP server */
  udp_server_addr.sin_family = AF_INET;
  udp_server_addr.sin_port = htons(6810); // server port
  udp_server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // local-host
  memset(udp_server_addr.sin_zero, '\0', sizeof udp_server_addr.sin_zero);  
  addr_size = sizeof udp_server_addr;

	{	struct math_proto mp;	
		mp.opr='+'; mp.val1=0x0a; mp.val2=0x01; math_proto_print_debug(&mp);
		
		math_proto_create_pkt(&mp, buf);
		
  		sendto(sockfd, buf, MAXBUF, 0, (struct sockaddr *)&udp_server_addr, addr_size); //send the data to server
  
    	len = recvfrom(sockfd, buf, MAXBUF, 0, NULL, NULL); // receive data from server
    	printf("Received from server: %d bytes\n", len);
  		for(i=0;i<len;i++) { printf("%02x", buf[i]); } printf("\n"); //print received data dump
    	
    	//parsing back to the data-structure
    	if(len==3) //check valid ??
    	{ math_proto_parse_pkt(&mp, buf); math_proto_print_debug(&mp); }	
  
	}  	
  	
  close(sockfd); //close socket file-descriptor
  
  return 0;
}
