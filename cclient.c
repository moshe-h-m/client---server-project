#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define N 256

void gerror(char* msg){
        perror(msg);
        exit(0);
}

int main(int argc,char* argv[]){

        int sockfd,portno,n;
        struct sockaddr_in serv_addr;
        struct hostent *server;
        char buffer[N];

        if(argc<3){
                fprintf(stderr,"usage %s hostname port\n",argv[0]);
                exit(0);
        }
	printf("we going connectig to server\n");
        portno=atoi(argv[2]);
	printf("___1___\n");
        if((sockfd=socket(PF_INET,SOCK_STREAM,0))<0)
                gerror("ERROR: no socket is opening");
	printf("___2___\n");
        if((server=gethostbyname(argv[1]))==NULL){
                fprintf(stderr,"ERROR: nosuch host\n");
                exit(0);
	}
	printf("%s\n",server->h_name);
        bzero((char*)&serv_addr,sizeof(serv_addr));
        serv_addr.sin_family=AF_INET;
        bcopy((char*)server->h_addr,(char*)&serv_addr.sin_addr.s_addr,server->h_length);
        serv_addr.sin_port=htons(portno);
	printf("___ ___\n");
        if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
                gerror("ERROR: invalid connecting (connect)");
	printf("___3___\n");
        if(n=write(sockfd,"HELLO THERE",sizeof("HELLO THERE"))<=0)
                gerror("ERROR: inaccessible to writing to sogket");
	printf("___4___\n");
        bzero(buffer,N);
        if((n=read(sockfd,buffer,N-1))<0)
                gerror("ERROR: in reading from socket");
        printf("message: %s\n",buffer);
	close(sockfd);
	printf("by by \n");



        return 0;
}
