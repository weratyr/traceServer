/*
 * TracerServer.h
 *
 *  Created on: 08.06.2012
 *      Author: istchhapp
 */

#ifndef TRACERSERVER_H_
#define TRACERSERVER_H_

#include "socket/CInetAddr.h"
#include "socket/CSockAcceptor.h"
#include "socket/CSockConnector.h"
#include "socket/CSockStream.h"
#include "socket/IIOStream.h"
#include "CBinarySemaphore.h"
#include "CCommQueue.h"
#include "Global.h"
#include "CMessage.h"



enum Component_Index
{
	ADMIN_INDEX, /* Admin bekommt eigene Komponente zum Prio setzen */
	MDISP_INDEX,
	HMI_INDEX,
	OpenGL_INDEX,
	TUNER_INDEX,
	NAVI_INDEX,
	GPS_INDEX,
	CD_INDEX,
	INPUT_INDEX,
	TRACER_INDEX
};

void swapQueue(CCommQueue &send_Queue, CCommQueue &recv_Queue);

#endif /* TRACERSERVER_H_ */
