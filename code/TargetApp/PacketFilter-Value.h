#ifndef PACKET_FILTER_VALID_BY_VALUE_H
#define PACKET_FILTER_VALID_BY_VALUE_H

#include "General.h"
#include "PacketFilter-FastRise.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
	FastRiseFilter filter;

	struct
	{
		uint16 		above;
		uint16		below;
		Bool		valid;
	} monitor;

} PacketFilterValidByValue;


void InitialisePacketFilterValidByValue(PacketFilterValidByValue* fvbv,
					Frequency openBandwidth, Frequency closedBandwidth,
					uint8 numberOfFilters, float filterRiseTimesBeforeValid,
					ElapsedTime samplePeriod);

/*Filter will be valid after filterRiseTimeBeforeValid rises times have passed (moderated by the weight of the inputs.
If allowSampleDistributionToSetFilterValid is TRUE then filter will go valid when or when at least proportionBelowFilterValue samples out of minSamplesBeforeFilterValid have been received below the
*/
void ResetPacketFilterValidByValue(PacketFilterValidByValue* fvbv);
void PacketFilterValidByValueInput(PacketFilterValidByValue* fvbv, Signal input);
#define SetSamplePeriodPacketFilterValidByValue(fvbv, period) SetSamplePeriodFastRiseFilter(&(fvbv)->filter, period)


#define SetBandwidthPacketFilterValidByValue(fvbv, narrow, bandwidth) SetBandwidthFastRiseFilter(&(fvbv)->filter, narrow, bandwidth)
#define SetChainLengthPacketFilterValidByValue(fvbv, numberOfFilters) SetChainLengthFastRiseFilter(&(fvbv)->filter, numberOfFilters)
#define PacketFilterValidByValueSetValue(fvbv,value) FastRiseFilterSetValue(&(fvbv)->filter,value)
#define PacketFilterValidByValueSetValid(fvbv, v)       ((fvbv)->monitor.valid = (v))

#define PacketFilterValidByValueValue(fvbv) FastRiseFilterValue(&(fvbv)->filter)

#define DataValidPacketFilterValidByValue(fvbv) ((fvbv)->monitor.valid)
#define SetPacketFilterValidByValueSamplePeriod(fvbv, samplePeriod) SetSamplePeriodFastRiseFilter(&(fvbv)->filter, samplePeriod)

#ifdef __cplusplus
}
#endif

#endif
