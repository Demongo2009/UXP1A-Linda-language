//
// Created by bartlomiej on 24.05.2021.
//

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
//        close(socketFileDescriptor);
        close(clientSocket);
//        exit(1);
    }

    clientAddressLength = sizeof(clientAddr);
    currentReturnCode = getpeername(clientSocket, (struct sockaddr *) &clientAddr, &clientAddressLength);
    if (currentReturnCode == -1){
        printf("GETPEERNAME ERROR: %s\n", strerror(errno));
//        close(socketFileDescriptor);
        close(clientSocket);
//        exit(1);
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
}
void MasterProcess::respond() {
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, RESPONSE);
    currentReturnCode = send(clientSocket, buffer, strlen(buffer), 0);
    if (currentReturnCode == -1) {
        printf("SEND ERROR: %s", strerror(errno));
//        close(socketFileDescriptor);
//        close(clientSocket);
//        exit(1);
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
    if(waitingProcesses.empty()) {
        tuples.emplace_back(tuple);
    } else{
        checkWaitingProcesses(tuple);
    }
    respond(); //TODO:może od razu odpowiedzieć?
    close(clientSocket);
}

void MasterProcess::processRead() {
    TuplePattern pattern = TuplePattern::deserialize(buffer);
    pattern.print();
    std::optional<Tuple> tuple;
    if((tuple = pattern.findMatching(tuples))){
        sendTuple(tuple.value());
    }else{
        createAwaitingProcess(pattern, false);
    }
}

void MasterProcess::processInput() {
    TuplePattern pattern = TuplePattern::deserialize(buffer);
    pattern.print();
    std::optional<Tuple> tuple;
    if((tuple = pattern.deleteMatching(tuples))){
        if(!sendTuple(tuple.value()))
            tuples.emplace_back(tuple.value());
    }else{
        createAwaitingProcess(pattern, true);
    }
}

bool MasterProcess::sendTuple(const Tuple& tuple) {
    char *msg = tuple.serialize();
    currentReturnCode = send(clientSocket, msg, strlen(msg), 0);
    delete[] msg;
    if (currentReturnCode == -1) {
        printf("SEND ERROR: %s", strerror(errno));
         // TODO: chyba się właśnie dowiedzieliśmy że klient sobie poszedł
        return false;
    }
    else {
        printf("Data sent!\n");
        return true;
    }
}

void MasterProcess::createAwaitingProcess(const TuplePattern& pattern, bool isInput) {
    int fd1[2];
    int fd2[2];
    if (pipe(fd1)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
    }
    if (pipe(fd2)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
    }
    pid_t pid = fork();
    if(pid < 0) {
        fprintf(stderr, "fork Failed");
    }else if( pid > 0){
        close(fd1[0]);
        close(fd2[1]);
        WaitingProcessInfo waitingProcess = WaitingProcessInfo(pid, fd2[0], fd1[1], pattern, isInput );
        waitingProcesses.emplace_back(waitingProcess);
        close(clientSocket);
    }else{
        WaitingProcess waitingProcess = WaitingProcess(fd1[0], fd2[1], clientSocket);
        waitingProcess.run();
    }
}

void MasterProcess::checkWaitingProcesses(const Tuple& tuple) {
    auto it = waitingProcesses.begin();

    while(it != waitingProcesses.end()) {
        if(it->getPattern().checkIfMatch(tuple)){
            memset(buffer, 0, sizeof(buffer));
            char* serialized = tuple.serialize();
            write(it->getWritePipeDescriptor(), serialized, strlen(serialized));
            read(it->getReadPipeDescriptor(), buffer, sizeof(buffer));
            if(it->isInput()) {
                if (strcmp(RESPONSE, buffer) == 0) {
                    waitingProcesses.erase(it);
                    return;
                }
            }
            it = waitingProcesses.erase(it);
        } else
            ++it;
    }
    tuples.emplace_back(tuple);
}
