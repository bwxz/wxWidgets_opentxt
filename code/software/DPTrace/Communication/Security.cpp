/**
 * \file Security.cpp
 * Implements a function to check for a security key in a particular
 * location in the hard drive. This is used to enable certain features
 * in an application when the key is present.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TEAFunctions.h"

#define VALIDATION_FILE_NAME "DebugKey.dat"
#define VALIDATION_FILE_TEXT "lihwedasdduio1wens2htsd3shntfm0toxhelrr23onlwesdakl;wfdrdwresasfdwsdsfdr"
#define VALIDATION_LINE_LENGTH 300


bool IsSemtech(void)
{
	char fileName[FILENAME_MAX+1];
													//获取ProgramFiles环境变量值
	sprintf(fileName,"%s\\Semtech\\UdpPrintf\\%s",getenv("ProgramFiles"),VALIDATION_FILE_NAME);

	FILE* file = fopen(fileName,"r");
	bool result;

	if (!file)
		return false;

	char text[VALIDATION_LINE_LENGTH+1];

	if (!fgets(text, VALIDATION_LINE_LENGTH, file))
		return false;
    
    //remove CR and LF.
    char* ptr = strchr(text, '\n');//查找出text首次出现‘\n’的位置
    if(ptr)
        *ptr = '\0';

    result = strcmp(text,VALIDATION_FILE_TEXT) == 0 ? true : false;

	fclose(file);
    
	return result;
}

bool GetEncryptionKey(uint32 encyptionKey[ENCRYPTION_KEY_LENGTH_WORDS])
{
	char fileName[FILENAME_MAX+1];

	sprintf(fileName,"%s\\Semtech\\UdpPrintf\\%s",getenv("ProgramFiles"),VALIDATION_FILE_NAME);

	FILE* file = fopen(fileName,"r");
	bool result = false;

	if (!file)
		return false;

    char line[VALIDATION_LINE_LENGTH];
	
    // first line is validation text.
    if (!fgets(line, VALIDATION_LINE_LENGTH, file))
		return false;

	// second line is encryption key.
    if (!fgets(line, VALIDATION_LINE_LENGTH, file))
		return false;

    int words = sscanf(line, "%X-%X-%X-%X", &encyptionKey[0], &encyptionKey[1], &encyptionKey[2], &encyptionKey[3]);
    if(words == ENCRYPTION_KEY_LENGTH_WORDS)
        result = true;

    fclose(file);

	return result;
}