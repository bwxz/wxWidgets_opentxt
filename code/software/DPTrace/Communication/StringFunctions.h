/*
Copyright © 2004 Semtech Corporation, P.O. Box 6097, Camarillo, 
CA 93011-6097 U.S.A.  

All rights reserved. The copyright of the content of this file is owned 
by Semtech Corporation (Semtech).  

This is an unpublished work.  The content of this file must be used only 
for the purpose for which it was supplied by Semtech or its distributors.   
The content of this file must not be copied or disclosed unless authorised in 
writing by Semtech.  

Name		$Workfile: StringFunctions.h $
Version     $Revision: 1 $
Date		$Date: 18/06/09 14:28 $

*/

#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#ifdef __cplusplus
	extern "C"
{
#endif

char const* FindWhiteSpace(char const string[]);
char const* FindAlphaNumeric(char const string[]);
char const* FindNonWhiteSpace(char const string[]); /* finds number, letter or - */
char const* FindWord(char const string[], unsigned int number);
char*		FindCharacter(char const string[], char quarry);	/* returns ptr to first occurrance of quarry */
char*		FindNthCharacter(char const string[], char quarry, unsigned int number); /* 1 is first character */
char*		FindCharacterReverse(char const string[], char quarry);	/* returns ptr to first occurrance of quarry */
char*		FindSubString(char const string[], char const quarry[]);	/* returns ptr to first occurrance of quarry */
int CopyWord(char output[], char const input[], unsigned int number);  /* returns non zero on success */
void SetToLower(char text[]);
void SetToUpper(char text[]);
int CaseInsensitiveStrcmp(char const left[], char const right[]);
unsigned int Words(char const string[]);  /* returns the number of "words" in a string.  A word is 1 or more non white characters */
int CompareStringFragment(char const test[], char const reference[]);  
	/* returns 0 if the first characters of the test string match all of the reference string*/

/* Replaces the characters after and including the last . with extension */
void ReplaceFileNameExtension(char filename[], char const newExtension[]);

/* Adds newText to file name before extension
e.g. AppendTextToFileName(out, "test.txt", "ADD") sets out to "testADD.txt"
*/
void AppendTextToFileName(char outputFilename[], char const inputFilename[], char const newText[]);

void RemoveTrailingNewLine(char text[]);

#ifdef __cplusplus
}
#endif

#endif
