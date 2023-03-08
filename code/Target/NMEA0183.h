#ifndef NMEA0183_H
#define NMEA0183_H

#include "General.h"
#include "TimeOfDayInterface.h"
#include "ToPSyncInterfaceTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	activeSentence = 0,
	smtcProprietaryMessageTimeFormat,
	smtcProprietaryMessageTimeAlignment,
	smtcSmtsMessageData=10,
	numberOfNMEA0183Parameters
} NMEA0183Parameter;
void InitNMEA0183(uint8 uart);
void SendNMEA0183Time(ClockPath const* clockPath, uint8 uart, ToPSyncTimeOfDay const* utcTimeOfDay,
		IEEE1588Time const* taiTime, const tGPSstatus* gpsStatus);
void ParseNMEA0183(uint8 uart, uint8 rxCh);
void GetNMEATODInputStatus(uint8 uart, TODInputStatus* status);
ToPSyncConfigResult SetNMEA0183Parameter(uint8 uart, NMEA0183Parameter parameter, uint8 id1, uint32 value);
Bool GetNMEA0183Parameter(uint8 uart, NMEA0183Parameter parameter, uint8 id1, uint32* value);
Bool SetNMEA0183ParameterDeprecated(NMEA0183Parameter parameter, uint8 id1, float value);
Bool GetNMEA0183ParameterDeprecated(NMEA0183Parameter parameter, uint8 id1, float* value);

#ifdef __cplusplus
}
#endif


#endif
