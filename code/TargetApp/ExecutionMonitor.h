#ifndef EXECUTION_MONITOR_H
#define EXECUTION_MONITOR_H

#include "General.h"
#include "HysteresisController.h"
#include "AlarmClient.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	timed,  // a set number of events per sec  SuccessEM()
	tryAndSucceed,  // events are tried and may succeed - TryEM() and SuccessEM()
	successAndFail, // events may succeed or fail = SuccessEM() and FailEM()
} ExecutionMonitorMode; 

// Grant fulfilment monitoring - are we actually getting the messages?
typedef struct
{		//configuration
		uint16					monitoringPeriodTicks;
		uint16					ticksPerSecond;
		float					eventsPerSecond;	//only used in timedMode
		ExecutionMonitorMode	mode;
		uint16					expectedEvents;  //only used in timedMode
		Bool					active;

		//monitoring
		struct
		{
			uint16				successes;
			union
			{
				struct
				{
					uint16		failures;
				} successAndFailS;

				struct
				{
					uint16		tries;
				} tryAndSucceedS;
			} specific;

			uint16					tickCount;  // in current period
		} condition;

		HysteresisController	executionGood;
		AlarmClient				alarmClient;

		struct
		{
			Bool valid;
			float successRate;
		} result;
		Bool pathDelayValid;
} ExecutionMonitor;

/* Fulfilment monitor functions */
void InitialiseEM(ExecutionMonitor* monitor, AlarmSource alarmSource, AlarmSourceIdentity identity,
						 struct AlarmMonitorStruct* alarmMonitor, ExecutionMonitorMode mode,
						 uint16 ticksPerSecond);

void ResetEM(ExecutionMonitor* monitor);
void SetLogEventPeriodEM(ExecutionMonitor* monitor, LogMessagePeriod logPeriod);
void SlowTickEM(ExecutionMonitor* monitor);
void SetActiveEM(ExecutionMonitor* monitor, Bool set);
void PathDelayValidEM(ExecutionMonitor* monitor, Bool set);

#define ActiveEM(mon) ((mon)->active)
#define ModeEM(mom) ((mom)->mode)


//Updating
#define SuccessEM(em) ((em)->condition.successes++)										// use with all
#define FailureEM(em) ((em)->condition.specific.successAndFailS.failures++)				// use with successAndFail
#define TryEM(em) ((em)->condition.specific.tryAndSucceedS.tries++)						// use with tryAndSucceed


//Fulfilment monitoring
#define FailuresEM(em, f) ((em)->condition.specific.successAndFailS.failures += (f))
#define GoodEM(em) IsSetHyC(&(em)->executionGood)

#define EventsPerSecondEM(em) ((em)->eventsPerSecond)

//Results
#define ResultIsValid(em) ((em)->result.valid)
#define SuccessRateEM(em) ((em)->result.successRate)

#ifdef __cplusplus
}
#endif

#endif
