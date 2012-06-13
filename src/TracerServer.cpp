//============================================================================
// Name        : TracerServer.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "TracerServer.h"
using namespace std;

int main() {

	printf("Start Tracer-Server\n");

	CInetAddr send_Addr;
	CInetAddr recv_Addr;
	send_Addr.set(1234, "localhost");
	recv_Addr.set(1111, "localhost");

	CSockAcceptor send_Acc;
	CSockAcceptor recv_Acc;
	//Int8 *memPtr;
	send_Acc.open(send_Addr);
	recv_Acc.open(recv_Addr);

	CBinarySemaphore *sem = new CBinarySemaphore(false, true);

	CCommQueue *recv_Queue = new CCommQueue(100, *sem); //Immer die selben Semaphore?
	CCommQueue *send_Queue = new CCommQueue(100, *sem);
	CCommQueue *temp_Queue;

	CSockStream recv_cStream;
	CSockStream send_cStream;
	int newsockfd;
	CMessage tempMsg;
	int pid;


	while(true) {
		newsockfd = recv_Acc.accept(recv_cStream);
		recv_cStream.read(&tempMsg, sizeof(CMessage));
		recv_Queue->add(const_cast<CMessage &>(tempMsg), false);

		printf("ID: %d \n", tempMsg.getReceiverID());

//		if((pid = fork()) == 0) {
//
//			temp_Queue = send_Queue;
//			send_Queue = recv_Queue;
//			recv_Queue = temp_Queue;
//
//			while(0 != send_Queue->getNumOfMessages()) {
//				send_Queue->getMessage(const_cast<CMessage &>(tempMsg));
//				send_cStream.write(&tempMsg, sizeof(CMessage));
//			}
//		}
	}


}
