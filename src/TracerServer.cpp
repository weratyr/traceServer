//============================================================================
// Name        : TracerServer.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "TracerServer.h"
using namespace std;

vector<CMessage> send_queue, recv_queue, temp_queue;

pthread_mutex_t globalMutex = PTHREAD_MUTEX_INITIALIZER;

int main() {

	printf("Start Tracer-Server\n");

	CInetAddr recv_Addr;
	CSockAcceptor recv_Acc;
	UInt16 port2 = 1111;
	recv_Addr.set(port2, "192.168.56.1");


	printf("Init Server...\n");

	recv_Acc.open(recv_Addr);

	CSockStream recv_cStream;


	int newsockfd;
	CMessage tempMsg;
	int pid;

	pthread_t sending;

	int test;

	test = pthread_create(&sending, NULL, foo, NULL);

	printf("Threadcode: %d \n", test);

	while(1) {
		printf("Server: waiting for client...\n");
		newsockfd = recv_Acc.accept(recv_cStream);

		pthread_mutex_lock(&globalMutex);
		printf("Server: new client: %d\n", newsockfd);
		recv_cStream.read(&tempMsg, sizeof(CMessage));
		printf("Server: Message Send ID: %d \n", tempMsg.getSenderID());
		printf("Server: Message Recv ID: %d \n", tempMsg.getReceiverID());

		recv_queue.push_back(tempMsg);
		pthread_mutex_unlock(&globalMutex);

	}


}

void *foo(void *arg) {

	printf("Starting Send Server\n");
	UInt16 port1 = 1234;
	CInetAddr send_Addr;
	send_Addr.set(port1, "192.168.56.1");
	CSockStream send_cStream;
	CSockAcceptor send_Acc;
	send_Acc.open(send_Addr);
	printf("afteropen\n");
	int newsockfd;
	CMessage tempMsg;
	CMessage * tempMsgPtr = &tempMsg;

	while(1) {
		printf("inwhile\n");
		newsockfd = send_Acc.accept(send_cStream);


		pthread_mutex_lock(&globalMutex);
		temp_queue = recv_queue;
		recv_queue = send_queue;
		send_queue = temp_queue;
		pthread_mutex_unlock(&globalMutex);

		while(!send_queue.empty()) {
			tempMsgPtr = &send_queue.front();
			send_cStream.write(const_cast<CMessage *>(tempMsgPtr), sizeof(CMessage));
			send_cStream.flush();
			//send_cStream.close();
			send_queue.pop_back();
		}
	}
}
