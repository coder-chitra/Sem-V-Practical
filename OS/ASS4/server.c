#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main()
{
char *ip ="127.0.0.0";
int port = 56007;
int c, read_size;
int server_sock,client_sock;
struct sockaddr_in server_addr,client_addr;
socklen_t addr_size;
char buffer[1024];
char client_message[2000];
int n;
server_sock=socket(AF_INET,SOCK_STREAM,0);

if(server_sock<0)
{
perror("[-] socket not created");
exit(1);
}
printf("[+] TCP server socket created\n");
memset(&server_addr,'0',sizeof(server_addr));
server_addr.sin_addr.s_addr = inet_addr(ip);
server_addr.sin_family=AF_INET;
server_addr.sin_port= port;
printf("\n %l",  server_addr.sin_addr.s_addr );
n=bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
printf("\n after bind : %d", server_sock);
printf("[+] Bind to the port number:%d\n",port);
listen(server_sock,5);
printf("Listening...\n");
puts("Waiting for incoming connections...");
//printf("\nServer sock : %d",server_sock);
c = sizeof(struct sockaddr_in);
//accept connection from an incoming client
client_sock = accept(server_sock, (struct sockaddr *)&client_addr,(socklen_t*)&c);
//printf("hello");
if (client_sock < 0)
{
perror("accept failed");
return 1;
}
puts("Connection accepted");
//Receive a message from client
while( (read_size = recv(client_sock , client_message , 2000 , 0))> 0 )
{
printf("\n Cliet messaged %s", client_message);
//Send the message back to client
write(client_sock , client_message , strlen(client_message));
}if(read_size == 0)
{
puts("Client disconnected");
fflush(stdout);
}
else if(read_size == -1)
{
perror("recv failed");
}
if(n<0)
{
perror("[-]Bind error");
exit(1);
}
/*while(1)
{
addr_size=sizeof(client_addr);
client_sock =accept(server_sock,(struct
sockaddr*)&client_addr,&addr_size);
printf("[+] Client connected\n");
}*/
/*if(connect(server_sock,(struct sockaddr
*)&server,sizeof(server))<0)
{
puts("connect error");
return 1;
}
puts("connected");*/
return 0;
}
