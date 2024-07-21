#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include "udp_sock.h"

#define MAXBUF 1024

int main()
{
 int sockfd, len, i;
  unsigned char buf[MAXBUF];
  struct sockaddr_in udp_server_addr;
  struct sockaddr_in udp_client_addr;
  struct sockaddr_storage server_storage;
  socklen_t addr_size, client_addr_size;

  sockfd = socket(PF_INET, SOCK_DGRAM, 0); // create a UDP socket
  if(sockfd<=0) { printf("socket error !\n"); return 0; }

  /* configure settings to register UDP server */
  udp_server_addr.sin_family = AF_INET;
  udp_server_addr.sin_port = htons(6810); // server port
  udp_server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // local-host
  memset(udp_server_addr.sin_zero, '\0', sizeof udp_server_addr.sin_zero);  
  bind(sockfd, (struct sockaddr *) &udp_server_addr, sizeof(udp_server_addr)); // bind the socket
  addr_size = sizeof server_storage;
  
  len = recvfrom(sockfd, buf, MAXBUF, 0, (struct sockaddr *)&server_storage, &addr_size); //receive data from client 
  printf("Received from client: %d bytes\n", len);
  for(i=0;i<len;i++) { printf("%02x ", buf[i]); } printf("\n"); //print received data dump
  
  if(len==3) //check valid ??
  {	struct math_proto mp; struct math_proto mp_result;
  		math_proto_parse_pkt(&mp, buf); math_proto_print_debug(&mp);

   	math_proto_calculate(&mp, &mp_result); math_proto_print_debug(&mp_result);
   	
   	math_proto_create_pkt(&mp_result, buf);
   	
		sendto(sockfd, buf, 3, 0, (struct sockaddr *)&server_storage, addr_size); //send the data to client
		
  }

  return 0;
}
