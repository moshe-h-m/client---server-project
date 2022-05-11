#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<errno.h>
#include<time.h>

#define N 256

void gerror(char* msg){
        perror(msg);
        exit(1);
}

int main(int argc,char* argv[]){
        int sockfd,newsockfd,portno,clilengh;
        struct sockaddr_in serv_addr, cli_addr;
        char buffer[N+1];
        int n;
	char name[N];
	char writ[N];

        if(argc<2){
                fprintf(stderr,"ERROR: no port provided\n");
                exit(1);
        }
	printf("\t ~~~walcome to moshe haim chat room~~~\n");
        if((sockfd=socket(PF_INET,SOCK_STREAM,0))<0)
                gerror("ERROR: no socket is opening");

        bzero((char*)&serv_addr,sizeof(serv_addr));
        portno=atoi(argv[1]);
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_addr.s_addr=INADDR_ANY;
        serv_addr.sin_port=htons(portno);
        if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
                gerror("ERROR: on bind fonction");
	printf("%d\n",INADDR_ANY);

        if(listen(sockfd,100)<0)
                gerror("ERROR: can't listening");
	printf("whaiting to conecter.....\n");
        clilengh=sizeof(cli_addr);
        if((newsockfd=accept(sockfd,(struct sockaddr*) &cli_addr,&clilengh))<0)
                gerror("ERROR: no returned new socket descriptor");
	printf("%d is conecting (:\n",newsockfd);
	write(newsockfd,"\t walcome !!  \n plase enter your name:\n",40); 
        bzero(buffer,N);
        read(newsockfd,buffer,N-1);
	*name=*buffer;
	while(*buffer!='q'){
	//n=read(newsockfd,*buffer,N-1);
	
        if((n=read(newsockfd,buffer,N-1))<0)
                gerror("ERROR: no accesible to reading to socket");
	printf("_\n");
        printf("%s: %s\n",name,buffer);
        scanf("you : %s\n",writ);
        if((n=write(newsockfd,writ,N-1))<0)
                gerror("ERROR: no accesible to writing to socket");
	bzero(buffer,N);
	bzero(writ,N);
	}
	close(sockfd);
	printf("service stoped\n");
	return 0;
}
