#include "client.h"

/*void set_connection () {
    struct sockaddr_in client_addr;
    int socket_desc;
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    client_addr.sin_port = htons(1111);

    if (connect(socket_desc, (struct sockaddr *)&client_addr, sizeof(client_addr)) == 0)
    {
        char *answer;
        write (1, "Connected to server, port is \n", mx_strlen("Connected to server, port is \n"));
        mx_printint(port);
        //send - recv dalee
        send(socket_desc,"{\"function_number\":\"1\",\"data\":[\"bebra\", \"agag\"]}",49,0);
        recv(socket_desc,answer,100,0);
        write(1, answer, mx_strlen(answer));
        send(socket_desc,"{\"function_number\":\"1\",\"data\":[\"bebra\", \"agag\"]}",49,0);
        // send(socket_desc,"sending some shit",18,0);
    }
    else
    {
        // vizov okna s reconnectom v recursii or cikle
        // server_set_connection();
        //printf("Something wrong!\n");
        exit(1);
    }
}*/

void func(int sockfd) {
    char buff[80];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        write (1, "Enter the string : ", mx_strlen("Enter the string : "));
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        write (1, "From Server : ", mx_strlen("From Server : "));
        write (1, buff, mx_strlen(buff));
        if ((strncmp(buff, "exit", 4)) == 0) {
            write (1, "Client Exit...\n", mx_strlen("Client Exit...\n"));
            break;
        }
    }
}

void set_connection () {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
   
    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        write(1, "socket creation failed...\n", mx_strlen("socket creation failed...\n"));
        exit(0);
    }
    else
        write(1, "Socket successfully created..\n", mx_strlen("Socket successfully created..\n"));
    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    servaddr.sin_port = htons(1111);
   
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        write (1, "connection with the server failed...\n", mx_strlen("connection with the server failed...\n"));
        exit(0);
    }
    else
        write (1, "connected to the server..\n", mx_strlen("connected to the server..\n"));
   
    // function for chat
    for (;;)
        func(sockfd);
   
    // close the socket
    close(sockfd);
}
