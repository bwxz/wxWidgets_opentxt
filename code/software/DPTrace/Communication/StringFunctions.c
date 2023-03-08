/*
Copyright © 2004 Semtech Corporation, P.O. Box 6097, Camarillo, 
CA 93011-6097 U.S.A.  

All rights reserved. The copyright of the content of this file is owned 
by Semtech Corporation (Semtech).  

This is an unpublished work.  The content of this file must be used only 
for the purpose for which it was supplied by Semtech or its distributors.   
The content of this file must not be copied or disclosed unless authorised in 
writing by Semtech.  

Name		$Workfile: StringFunctions.c $
Version     $Revision: 1 $
Date		$Date: 18/06/09 14:28 $

*/

#include "StringFunctions.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


char const* FindWhiteSpace(char const string[])
{
	char const* cptr = string;

	/*lint -e{722} Suspicious use of ; */
	for(;cptr && *cptr != '\0' && !isspace(*cptr);cptr++);

	if (cptr && *cptr == '\0')
	{
		cptr = 0;
	}
	return cptr;
}

char const* FindNonWhiteSpace(char const string[])
{
	char const* cptr = string;

	/*lint -e{722} Suspicious use of ; */
	for(;cptr && *cptr != '\0' && isspace(*cptr);cptr++);

	if (cptr && *cptr == '\0')
	{
		cptr = 0;
	}
	return cptr;
}


char const* FindAlphaNumeric(char const string[])
{
	char const* cptr = string;

	/*lint -e{722} Suspicious use of ; */
	for(;cptr && *cptr != '\0' && !isalnum(*cptr);cptr++);

	if (cptr && *cptr == '\0')
	{
		cptr = 0;
	}
	return cptr;
}

char const* FindWord(char const string[], unsigned int number)
{
	unsigned int word = 1;

	char const* cptr = FindNonWhiteSpace(string);

	while (cptr && word < number)
	{
		cptr = FindWhiteSpace(cptr);
		cptr = FindNonWhiteSpace(cptr);
		word++;
	}

	return cptr;
}

unsigned int Words(char const string[])
{
	unsigned int words = 0;

	char const* cptr = FindNonWhiteSpace(string);
	while (cptr)
	{
		cptr = FindWhiteSpace(cptr);
		cptr = FindNonWhiteSpace(cptr);
		words++;
	}

	return words;
}

char*	FindCharacter(char const string[], char quarry)	/* returns ptr to first occurrance of quarry */
{
	char const* cptr = string;
	while (*cptr != quarry && *cptr != '\0') 
		cptr++;

	if (*cptr == '\0')
		cptr = NULL;

	return (char *) cptr;
}

char* FindNthCharacter(char const string[], char quarry, unsigned int number) /* 1 is first character */
{
	char const* cptr = string;
	unsigned int count = 0;

	if (number < 1) number = 1;  // avoid not searching at all
	for (count = 0; cptr != NULL && count < number; count++)
	{
		cptr = FindCharacter(cptr,quarry);

		if (!cptr) break;
		cptr++;
	}
	return (char *) cptr;
}

char* FindCharacterReverse(char const string[], char quarry)	/* returns ptr to last occurrance of quarry */
{
	char* cptr = (char *) string + strlen(string) -1;

	while (*cptr != quarry && cptr != string) 
		cptr--;

	if (cptr == string)
		cptr = NULL;

	return cptr;
}


char* FindSubString(char const string[], char const quarry[])	/* returns ptr to first occurrance of quarry */
{
	char const* stringPtr = string;
	char const* quarryPtr = quarry;

	for (; *stringPtr != '0';stringPtr++)
	{
		if (*quarryPtr == *stringPtr)
		{
			quarryPtr++;

			if (*quarryPtr == '\0')
				return (char*) (stringPtr + 1 - strlen(quarry));
		}
		else
			quarryPtr = quarry;
	}
	return NULL;
}


int CopyWord(char output[], char const input[], unsigned int number)
{
	char const* start = FindWord(input,number);
	char const* end;
	int result = 1;
	
	if (start)
	{
		end = FindWhiteSpace(start);

		if (!end)
		{
			end = start + strlen(start);
		}

		memcpy(output,start,(unsigned int)(end - start));
		output[end-start] = '\0';
	}
	else
	{
		result = 0;
	}
	return result;
}

void ReplaceFileNameExtension(char filename[], char const newExtension[])
{
	char *cptr;

	/*lint -e{722} Suspicious use of ; */
	for(
		cptr = filename + strlen(filename);
		cptr >= filename &&
		*cptr != '.' &&
		*cptr != '\\' &&
		*cptr != '/'
		;
		cptr--);

	if (*cptr == '.')
	{
		//lint -e{669} possible data overrun
		strcpy(cptr,newExtension);
	}
	else
	{
		strcat(filename,newExtension);
	}
}

void AppendTextToFileName(char outputFilename[], char const inputFilename[], char const newText[])
{
	char* dot;

	strcpy(outputFilename,inputFilename);
	dot = FindCharacterReverse(outputFilename,'.');

	if (!dot)
		strcat(outputFilename,newText);
	else
	{
		char extension[_MAX_EXT]; // including '.'
	
		strcpy(extension,dot);
		*dot = '\0';  // remove dot and extension
		dot = NULL;

		strcat(outputFilename,newText);
		strcat(outputFilename,extension);
	}
}

void RemoveTrailingNewLine(char text[])
{
	char *cptr = text + strlen(text) -1;	/* last character */

	if (cptr > text && *cptr == '\n')
	{
		*cptr = '\0';
	}
}

void SetToLower(char text[])
{
	char *cptr = text;

	if (!text)
		return;

	for(;*cptr != '\0';cptr++)
		*cptr = (char) tolower(*cptr);
}

void SetToUpper(char text[])
{
	char *cptr = text;

	if (!text)
		return;

	for(;*cptr != '\0';cptr++)
		*cptr = (char) toupper(*cptr);
}
int CaseInsensitiveStrcmp(char const left[], char const right[])
{
	char const *lptr = left;
	char const *rptr = right;
	int result = 0;

	for (; (*lptr != '\0' || *rptr != '\0'); lptr++, rptr++)
	{
		if (tolower(*lptr) != tolower(*rptr))
		{
			if (tolower(*lptr) > tolower(*rptr))
				result = 1;
			else
				result = -1;
			break;
		}
	}
	return result;
}

int CompareStringFragment(char const test[], char const reference[])
{
	char const *tptr = test;
	char const *rptr = reference;
	int result = 0;

	for (; *rptr != '\0'; tptr++, rptr++)
	{
		if (*tptr != *rptr)
		{
			if (*tptr > *rptr)
				result = 1;
			else
				result = -1;
			break;
		}
	}
	return result;
}
