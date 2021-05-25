//
// Created by bartlomiej on 24.05.2021.
//

#include "../../include/client/linda.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

unsigned char PATH_LENGTH_LIMIT = 100;

void linda_output(const Tuple& tuple){
    std::string server_filename = "/tmp/linda_server";
    std::string client_filename = "/tmp/linda_output_" + std::to_string(getpid());

    struct sockaddr_un server_addr;
    struct sockaddr_un client_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, server_filename.c_str(), PATH_LENGTH_LIMIT);

    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    strncpy(client_addr.sun_path, client_filename.c_str(), PATH_LENGTH_LIMIT);

    int sockfd;
    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
    }

    if(bind(sockfd, (struct sockaddr *) &client_addr, sizeof(client_addr))){
//        perror("bind failed");
    }

    if(connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr))){
        perror("connect failed");
    }

    char *msg = tuple.serialize();
    int len = offsetof(struct sockaddr_un, sun_path) + server_filename.size();
    int n = send(sockfd, msg, strlen(msg), 0);
    if (n < 0)
        perror("send failed");
//    else
//        printf("sent %d bytes\n", n);
    delete[] msg;
    char buf[256];
    memset(buf, 0, sizeof(buf));
    int rc = recv(sockfd, buf, sizeof(buf), 0);
    if (rc == -1) {
        printf("RECV ERROR = %s\n", strerror(errno));
        close(sockfd);
        exit(1);
    }
//    else {
//        printf("DATA RECEIVED = %s\n", buf);
//    }


    close(sockfd);

}

Tuple linda_read(const TuplePattern& pattern, unsigned int timeout){
    std::string server_filename = "/tmp/linda_server";
    std::string client_filename = "/tmp/linda_read_" + std::to_string(getpid());

    struct sockaddr_un server_addr;
    struct sockaddr_un client_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, server_filename.c_str(), PATH_LENGTH_LIMIT);

    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    strncpy(client_addr.sun_path, client_filename.c_str(), PATH_LENGTH_LIMIT);

    int sockfd;
    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
    }

    if(bind(sockfd, (struct sockaddr *) &client_addr, sizeof(client_addr))){
//        perror("bind failed");
    }

    if(connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr))){
        perror("connect failed");
    }

    char *msg = pattern.serialize();
    int len = offsetof(struct sockaddr_un, sun_path) + server_filename.size();
    int n = send(sockfd, msg, strlen(msg), 0);
    if (n < 0)
        perror("send failed");

    delete[] msg;
    char buf[256];
    memset(buf, 0, sizeof(buf));
    int rc = recv(sockfd, buf, sizeof(buf), 0);
    if (rc == -1) {
        printf("RECV ERROR = %s\n", strerror(errno));
        close(sockfd);
        exit(1);
    }
    else {
        Tuple tuple = Tuple::deserialize(buf);
        printf("DATA RECEIVED = %s\n", buf);
        tuple.print();
        close(sockfd);
        return tuple;
    }


}

Tuple linda_input(const TuplePattern& pattern, unsigned int timeout){
    std::string server_filename = "/tmp/linda_server";
    std::string client_filename = "/tmp/linda_input_" + std::to_string(getpid());

    struct sockaddr_un server_addr;
    struct sockaddr_un client_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, server_filename.c_str(), PATH_LENGTH_LIMIT);

    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    strncpy(client_addr.sun_path, client_filename.c_str(), PATH_LENGTH_LIMIT);

    int sockfd;
    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
    }

    if(bind(sockfd, (struct sockaddr *) &client_addr, sizeof(client_addr))){
//        perror("bind failed");
    }

    if(connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr))){
        perror("connect failed");
    }

    char *msg = pattern.serialize();
    int len = offsetof(struct sockaddr_un, sun_path) + server_filename.size();
    int n = send(sockfd, msg, strlen(msg), 0);
    if (n < 0)
        perror("send failed");

    delete[] msg;
    char buf[256];
    memset(buf, 0, sizeof(buf));
    int rc = recv(sockfd, buf, sizeof(buf), 0);
    if (rc == -1) {
        printf("RECV ERROR = %s\n", strerror(errno));
        close(sockfd);
        exit(1);
    }
    else {
        Tuple tuple = Tuple::deserialize(buf);
        printf("DATA RECEIVED = %s\n", buf);
        tuple.print();
        close(sockfd);
        return tuple;
    }

}