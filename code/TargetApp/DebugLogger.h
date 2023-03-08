#ifndef __DEBUG_LOGGER_H__
#define __DEBUG_LOGGER_H__

#ifdef TS_DO_CUSTOM_LOGGING
  #include "mqx.h"
  #include "lwlog.h"
  #include "lwlogprv.h"
  #include "IEEE1588Time.h"

  #define DEBUG_LOG_NUM 1

  typedef enum
  {
 	  DebugLoggerEventReadTimeStamp,
 	  DebugLoggerDebouncerToggle,
 	  DebugLoggerAlignClockTsToNodeTime,
 	  DebugLoggerGetTwoHardwareTimes,
 	  DebugLoggerSetClockSrc,
 	  DebugLoggerApplyTimeOffset,
 	  DebugLoggerClockEdgeDetected,
 	  DebugLoggerEpochRollover,
 	  DebugLoggerSetTimeCorrectionLag,
 	  DebugLoggerTimeSmootherLag1588,
 	  DebugLoggerTRSelectorSlowTickSelected,
 	  DebugLoggerSelectorSourceActionCompleteTRSelector,
 	  DebugLoggerApplyTimeOffsetBEFORE,
 	  DebugLoggerApplyTimeOffsetAFTER,
 	  DebugLoggerAFTERAlignClockTsToNodeTime,
	  DebugLoggerEventUserDefined
  } DebugLoggerEvent;

  typedef enum
  {
	  DbgLogClockEdgeDetected_Rxd,
	  DbgLogClockEdgeDetected_RawPhaseLag,
	  DbgLogClockEdgeDetected_NextIdeal,
	  DbgLogClockEdgeDetected_NextExpected,
	  DbgLogClockEdgeDetected_PhaseDiscontinuity,
	  DbgLogClockEdgeDetected_TimeErrTooGreat
  } DbgLogClockEdgeDetected;

  typedef enum
  {
	  DbgLogGetTwoHardwareTimes_Which,
	  DbgLogGetTwoHardwareTimes_Reference,
	  DbgLogGetTwoHardwareTimes_Selected,
  } DbgLog2Times;

  typedef struct
  {
	  DebugLoggerEvent eventType;
	  _mqx_max_type    eventData[5];
  } DebugLoggerData;

  #define LogToDebuggerStartCR() _task_stop_preemption()
  #define LogToDebuggerEndCR()   _task_start_preemption()

  void CreateDebugLogger(void);
  void LogToDebugLogger(DebugLoggerData const *data);
  void LogToDebugLoggerSimple(DebugLoggerEvent ev);
  void LogToDebugLoggerTimeStampEvent(DebugLoggerEvent eventType, IEEE1588Timestamp const *tstamp);
  void LogToDebugLoggerDebouncerStatus(Bool on);
  void LogToDebugLoggerClockTimeAlignmentToNodeTime(IEEE1588Time const *offset);
  void LogToDebugLoggerGetTwoHardwareTimes(
  		uint8 tested,
  		Bool testedIsClockTimestamper,
  		uint8 reference,
  		IEEE1588Time const *reference,
  		IEEE1588Time const *tested);
  void LogToDebugLoggerSetClockSrc(_mqx_max_type ts, _mqx_max_type src);
  void LogToDebugLoggerApplyTimeOffset( IEEE1588Time const *offset );
  void LogToDebugLoggerEpochRollover(void);
  void LogToDebugLoggerClockEdgeDetected(DbgLogClockEdgeDetected event, IEEE1588Time const *edgeTime);
  void LogToDebugLoggerApplyTimeOffsetAFTER( IEEE1588Timestamp const *after, uint8 tsnum );
  void LogToDebugLoggerApplyTimeOffsetBEFORE( IEEE1588Timestamp const *after, uint8 tsnum );
  void LogToDebugLoggeAFTERrClockTimeAlignmentToNodeTime(IEEE1588Time const *offset);
#else
  #define LogToDebuggerStartCR()
  #define LogToDebuggerEndCR()
  #define CreateDebugLogger()
  #define LogToDebugLogger(a)
  #define LogToDebugLoggerSimple(a)
  #define LogToDebugLoggerTimeStampEvent(a, b)
  #define LogToDebugLoggerDebouncerStatus(a)
  #define LogToDebugLoggerClockTimeAlignmentToNodeTime(a)
  #define LogToDebugLoggerGetTwoHardwareTimes(a, b, c, d, e)
  #define LogToDebugLoggerSetClockSrc(a, b)
  #define LogToDebugLoggerApplyTimeOffset( a )
  #define LogToDebugLoggerEpochRollover()
  #define LogToDebugLoggerClockEdgeDetected(a, b)
  #define LogToDebugLoggerApplyTimeOffsetAFTER(a, b)
  #define  LogToDebugLoggerApplyTimeOffsetBEFORE(a, b)
  #define LogToDebugLoggeAFTERrClockTimeAlignmentToNodeTime(a)
#endif

#endif
