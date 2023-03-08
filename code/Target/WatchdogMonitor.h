#ifndef WATCHDOG_MONITOR_H
#define WATCHDOG_MONITOR_H

#include "General.h"
#include "ApplicationInfrastructureInterface.h"
#include "GlobalData.h"


#ifdef __cplusplus
extern "C" {
#endif

#define TIME_TASK_WD		 				0x001
#define EVENT_TASK_WD						0x002
#define REACT_TO_UDP_MESSAGE_TASK_WD		0x004
#define REACT_TO_STACK_BYPASS_TASK_WD		0x008
#define CONTROL_MESSAGE_TASK_WD				0x010
#define DELAY_RESP_SEND_TASK_WD				0x020
#define EVENT_PACKET_SEND_TASK_WD			0x040
#define IDLE_TASK_WD						0x080

#define ALL_TASKS_OK_MASK   \
	(TIME_TASK_WD | \
	EVENT_TASK_WD | \
	REACT_TO_UDP_MESSAGE_TASK_WD | \
	REACT_TO_STACK_BYPASS_TASK_WD | \
	CONTROL_MESSAGE_TASK_WD | \
	DELAY_RESP_SEND_TASK_WD | \
	EVENT_PACKET_SEND_TASK_WD | \
	IDLE_TASK_WD  \
	)

void StartWatchdog(void);
void TaskRunning(uint32 id);
#define TaskRunningLightWeight(id) (DisableInterrupts(), currentResetData.taskHasRunMask |= (id), EnableInterrupts())	//use in time critical tasks

#ifdef __cplusplus
}
#endif

#endif
