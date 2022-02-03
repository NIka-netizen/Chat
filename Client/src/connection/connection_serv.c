#include "client.h"

void func(int sockfd, char *buff) {
    int n;
    for (;;) {
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(sockfd, buff, sizeof(buff));
        mx_memset(buff, 0, mx_strlen(buff));
        //bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        write (1, "From Server : ", mx_strlen("From Server : "));
        write (1, buff, mx_strlen(buff));
        // if ((strncmp(buff, "exit", 4)) == 0) {
        //     write (1, "Client Exit...\n", mx_strlen("Client Exit...\n"));
        //     break;
        // }
    }
}

void set_connection (char *answer) {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket creation failed...\n");
        exit(EXIT_FAILURE);
    }
    else
        write(1, "Socket successfully created..\n", mx_strlen("Socket successfully created..\n"));

    //bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    servaddr.sin_port = htons(1111);
   
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        perror("connection with the server failed...\n");
        exit(0);
    }
    else
        write (1, "connected to the server..\n", mx_strlen("connected to the server..\n"));
   
    // function for chat
    func(sockfd, answer);
    // close the socket
    close(sockfd);
}
