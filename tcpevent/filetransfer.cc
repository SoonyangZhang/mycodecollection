#define PORT 1234
#define LENGTH 1024 

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>
using namespace std;

int main(int argc, char *argv[]){

	uint16_t port=1234;
	char servAddr[32]="127.0.0.1";
	int total_size=200*1024;//200MB;
int sockfd; 
int nsockfd;
char revbuf[LENGTH]; 
struct sockaddr_in remote_addr;
/* Get the Socket file descriptor */
if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
{
    fprintf(stderr, "ERROR: Failed to obtain Socket Descriptor! (errno = %d)\n",1);
    exit(1);
}

/* Fill the socket address struct */
remote_addr.sin_family = AF_INET; 
remote_addr.sin_port = htons(port); 
inet_pton(AF_INET, "127.0.0.1", &remote_addr.sin_addr); 
bzero(&(remote_addr.sin_zero), 8);

/* Try to connect the remote */
if (connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1)
{
    fprintf(stderr, "ERROR: Failed to connect to the host! (errno = %d)\n",2);
    exit(1);
}
else 
    printf("[Client] Connected to server at port %d...ok!\n", PORT);
    const char* fs_name = "house.jpg";
   char sdbuf[LENGTH];

	int sendsize=0;
	
    //while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, fs)) > 0)
    while(sendsize<total_size)
	{
		//usleep(100*1000);
		int n=send(sockfd, sdbuf, LENGTH, 0);
        if( n< 0)
        {
            fprintf(stderr, "ERROR: Failed to send file %s. (errno = %d)\n", fs_name, errno);
            break;
        }
        bzero(sdbuf, LENGTH);
		sendsize+=n;
    }
    printf("Ok File from Client was Sent!\n");


close (sockfd);
printf("[Client] Connection lost.\n");
return (0);
}
