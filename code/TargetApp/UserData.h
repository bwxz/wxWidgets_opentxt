#ifndef USER_DATA_H
#define USER_DATA_H

#include "SystemManagementMessageHandler.h"
#include "SampleDivider.h"
#include "TwoLevelAddress.h"
#include "TLVIdentities.h"

#ifdef __cplusplus
extern "C" {
#endif

#define WORD_SIZE 4
#define USER_DATA_MAX_LENGTH_WORDS SEMTECH_ORGANIZATION_SUB_TYPE_USER_DATA_WORDS_LENGTH  //64
#define USER_DATA_MAX_LENGTH_BYTES SEMTECH_ORGANIZATION_SUB_TYPE_USER_DATA_LENGTH  //256

typedef struct SendUserDataStruct
{
	//firstly the send data
	Bool			enable;
	sint8			sendPeriod; //of data
	uint8			maxRepeats; //amount of times to repeat the send
	uint8			repeats;
	Bool			unicast;
	TransmissionProtocolAddress receiverTpa;
	Bool			sendTheData;
	uint8			sendControlRegister;
	ElapsedTime		tickPeriod;
	SampleDivider	sampleDivider;
	uint16			sendDataWordsLength;
	uint32			sendData[USER_DATA_MAX_LENGTH_WORDS];
}SendUserData;

typedef struct ReceiveUserDataStruct
{
	TwoLevelAddress sourceAddress;
	PortId			sourceId;
	Bool			enable;
	sint8			sendPeriod; //acks
	uint8			maxRepeats;//amount of times to repeat the send of ack
	uint8			repeats;
	Bool			dataReady; //data is ready to read
	Bool			sendAck;
	Bool			receiveFailed;
	ElapsedTime		tickPeriod;
	SampleDivider	sampleDivider;
	uint16			receivedDataWordsLength;
	uint32			receivedData[USER_DATA_MAX_LENGTH_WORDS];
}ReceiveUserData;



typedef struct UserDataStruct
{
	SendUserData sendUserData;
	ReceiveUserData receiveUserData;
} UserData;


typedef enum
{
	SEND_USER_DATA_TIMEOUT= 0,
	SEND_USER_DATA_RECEIVER_TPA_ADDRESS_LENGTH = 1,
	SEND_USER_DATA_RECEIVER_TPA_ADDRESS1= 2,
	SEND_USER_DATA_RECEIVER_TPA_ADDRESS2= 3,
	SEND_USER_DATA_RECEIVER_TPA_ADDRESS3= 4,
	SEND_USER_DATA_RECEIVER_TPA_ADDRESS4= 5,
	SEND_USER_DATA_ENABLE= 8,
	SEND_USER_DATA_SEND = 9,
	SEND_USER_DATA_SEND_CONTROL_REGISTER = 10,
	SEND_USER_DATA_SEND_DATA_LENGTH= 16,
	SEND_USER_DATA_SEND_DATA1= 17,
	SEND_USER_DATA_SEND_DATA64= 80,
	SEND_USER_DATA_END
}mmApiUserDataSubBlockSendUserData;


typedef enum
{
	RECEIVE_USER_DATA_TIMEOUT= 0,
	RECEIVE_USER_DATA_ENABLE= 1,
	RECEIVE_USER_DATA_SENDER_TPA_ADDRESS_LENGTH = 2,
	RECEIVE_USER_DATA_SENDER_TPA_ADDRESS1= 3,
	RECEIVE_USER_DATA_SENDER_TPA_ADDRESS2= 4,
	RECEIVE_USER_DATA_SENDER_TPA_ADDRESS3= 5,
	RECEIVE_USER_DATA_SENDER_TPA_ADDRESS4= 6,
	RECEIVE_USER_DATA_READY= 8,
	RECEIVE_USER_DATA_FAIL= 9,
	RECEIVE_USER_DATA_LENGTH= 16,
	RECEIVE_USER_DATA_DATA1= 17,
	RECEIVE_USER_DATA_DATA64= 80,
	RECEIVE_USER_DATA_END
}mmApiUserDataSubBlockReceiveUserData;



void InitialiseUserData(UserData* userData, ElapsedTime tickPeriod);
void ResetUserData(UserData* userData);
ToPSyncConfigResult UserDataSetSendTheData(UserData* userData, Bool send);
void UserDataReceived(UserData* userData, TwoLevelAddress const* sourceAddress, PortId const* sourceId, uint16 lengthInBytes, uint8 const **data);
void UserDataAckReceived(UserData* userData);


Bool TickUserDataSend(UserData* userData);
Bool TickUserDataReceive(UserData* userData);
void SetTransmissionProtocol(UserData* userData, TransmissionProtocol protocol);
ToPSyncConfigResult mmApiSetSendUserData(UserData* userData, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiGetSendUserData(UserData* userData, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiSetReceiveUserData(UserData* userData, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiGetReceiveUserData(UserData* userData, uint8 ptpNum, uint16 offset, uint32 length, uint32 *data);

ToPSyncConfigResult UserDataSetSendTimeout(UserData* userData, uint32 timeoutInSecs);
uint32 UserDataGetReceiverTimeout(UserData* userData);
ToPSyncConfigResult UserDataSetSendEnable(UserData* userData, Bool enable);
ToPSyncConfigResult UserDataSetSendRepeats(UserData* userData, uint8 repeats);
ToPSyncConfigResult UserDataSendSetTPA(UserData* userData, TransmissionProtocolAddress *address);

ToPSyncConfigResult UserDataSetReceiverTimeout(UserData* userData, uint32 timeoutInSecs);
uint32 UserDataGetSendTimeout(UserData* userData);
ToPSyncConfigResult UserDataSetReceiverRepeats(UserData* userData, uint8 repeats);
ToPSyncConfigResult UserDataSetReceiveEnable(UserData* userData, Bool enable);

#ifdef __cplusplus
}
#endif

#endif
