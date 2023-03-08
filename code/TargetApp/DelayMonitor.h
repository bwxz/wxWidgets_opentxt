#ifndef DELAY_MONITOR_H
#define DELAY_MONITOR_H

#include "IEEE1588Time.h"
#include "General.h"

typedef enum
{
	referenceFromClockTSA	= 0,
	referenceFromClockTSB,
	noReferenceClockSpecified
} DelayMonitorReferenceClock;

typedef enum
{
	noSelectedSourceDM,
	no1HzInputDetectedDM,
	calibratingTo1HzInputDM,
	sourceDataNotValidDM,
	masterInvisibleDM,
	masterInvalidDM,
	masterValidatingDM,
	masterTooFewTimingMessagesDM,
	masterNotOfInterestDM,
	masterRequestingContractDM,
	aligningTo1HzDM,
	notPrintingDM,
	printingDelaysDM,
	numberOfDelayMeasurementStates
		
} DelayMonitorState;

typedef struct
{
	DelayMonitorState		state;
	Bool					enabled;
	Bool					enablePtpErrorMonitor;		//when this is enabled, the clock is used as reference to calculate Ptp error.
	
	IEEE1588Time			ptpVsClockTimeDiff;
	ElapsedTime				ptpVsClockTimeDiffFloat;	//= (ClockTime - PtpTime)
	ElapsedTime				ptpVsOtherPtpTimeDiff;		//= (OtherPtpTime - ThisPtpTime)
	ElapsedTime				nodeTimeVsClockTimeDiff;		//= (ClockTime - NodeTime), depending on the clockPath, it will be nodeTime 1 or 2
	ElapsedTime				clockPll2VsClockPll1TimeDiff;		//= (Clock PLL1 Time - Clock PLL2 Time), 
	
	DelayMonitorReferenceClock	referenceClockId;

} DelayMonitor;

void InitialiseDelayMonitor(DelayMonitor *delayMonitor);
void SlowTickDelayMonitor(void);

void EnableDelayMonitor(DelayMonitor *delayMonitor, Bool enable);
#define DelayMonitorEnabled(delayMonitor)  ((delayMonitor).enabled)

#define GetDelayMonitorState(delayMonitor) (delayMonitor.state)
#define DelayMonitorPrintingDelays(delayMonitor) (delayMonitor.state == printingDelaysDM ? TRUE : FALSE)
char const* DelayMonitorStateText(DelayMonitor *delayMonitor);

void EnablePtpErrorMonitor(DelayMonitor *delayMonitor, Bool enable);
#define PtpErrorMonitorEnabled(delayMonitor)  (delayMonitor.enablePtpErrorMonitor)

void SendDelayReport(DelayMonitor *delayMonitor,
	IEEE1588Time const* masterSendTime, IEEE1588Time const* slaveReceiveTime, sint32 timeCorrectionNsMS,
	IEEE1588Time const* slaveSendTime,  IEEE1588Time const* masterReceiveTime, sint32 timeCorrectionNsSM);

void PrintDelayMonitor(DelayMonitor const* dm, char** ptrptr, long *bufferSize, Bool printTitle);


#endif

