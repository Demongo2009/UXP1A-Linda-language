//
// Created by bartlomiej on 24.05.2021.
//

#include "../../include/tuple/Tuple.h"
#include "../../include/server/MasterProcess.h"


void MasterProcess::receive() {

    memset(buffer, 0, sizeof(buffer));
    printf("waiting to read...\n");
    long bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived == -1){
        printf("RECV ERROR: %s\n", strerror(errno));
        close(socketFileDescriptor);
        close(clientSocket);
        exit(1);
    }
    else {
        printf("DATA RECEIVED = %s\n", buffer);
    }
    memset(buffer, 0, sizeof(buffer));

}



void MasterProcess::init() {
    if ((socketFileDescriptor = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
    }

    unlink(serverFilename.c_str());
    currentReturnCode = bind(socketFileDescriptor, (struct sockaddr *) &serverAddr, serverAddressLength);
    if (currentReturnCode == -1) {
        printf("BIND ERROR: %s\n", strerror(errno));
        close(socketFileDescriptor);
        exit(1);
    }

    currentReturnCode = listen(socketFileDescriptor, QUEUE_LENGTH);
    if (currentReturnCode == -1) {
        printf("LISTEN ERROR: %s\n", strerror(errno));
        close(socketFileDescriptor);
        exit(1);
    }

    printf("socket listening...\n");
}

void MasterProcess::acceptClient() {

    clientSocket = accept(socketFileDescriptor, (struct sockaddr *) &clientAddr, &serverAddressLength);
    if (clientSocket == -1){
        printf("ACCEPT ERROR: %s\n", strerror(errno));
        close(socketFileDescriptor);
        close(clientSocket);
        exit(1);
    }

    clientAddressLength = sizeof(clientAddr);
    currentReturnCode = getpeername(clientSocket, (struct sockaddr *) &clientAddr, &clientAddressLength);
    if (currentReturnCode == -1){
        printf("GETPEERNAME ERROR: %s\n", strerror(errno));
        close(socketFileDescriptor);
        close(clientSocket);
        exit(1);
    }
    else {
        printf("Client socket filepath: %s\n", clientAddr.sun_path);
    }

}

void MasterProcess::run() {
    init();
    while (1) {
        acceptClient();
        receive();
        processMessage();
        counter++;
        std::cout<<"counter: "<<counter<<std::endl;
//
    }
    close(socketFileDescriptor);
    close(clientSocket);
}
void MasterProcess::respond() {
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, RESPONSE);
    currentReturnCode = send(clientSocket, buffer, strlen(buffer), 0);
    if (currentReturnCode == -1) {
        printf("SEND ERROR: %s", strerror(errno));
        close(socketFileDescriptor);
        close(clientSocket);
        exit(1);
    }
    else {
        printf("Data sent!\n");
    }

}
void MasterProcess::processMessage() {
    if( strstr(clientAddr.sun_path, "linda_output") != nullptr){
        processOutput();
    }else if( strstr(clientAddr.sun_path, "linda_read") != nullptr){
        processRead();
    }else if( strstr(clientAddr.sun_path, "linda_input") != nullptr){
        processInput();
    }
}

void MasterProcess::processOutput() {
    Tuple tuple = Tuple::deserialize(buffer);
    tuple.print();
    tuples.emplace_back(tuple); //if no one waits
    respond();
}
void MasterProcess::processRead() {

}
void MasterProcess::processInput() {

}
