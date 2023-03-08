/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/Validation.cpp $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#include "Validation.h"

#include "Floats.h"
#include "Macros.h"

#include <wx/string.h>
#include <wx/textctrl.h>

#include <iomanip>
#include <sstream>

/************
  Functions
************/

int GetMagnitudeOfPrefix(const wxString &prefix)
{
	if (!prefix.IsEmpty())
	{
		switch ((char)(wchar_t)prefix[0])	// ◊◊÷ƒ∏
		{
			case 'Y':
				return 24;
			case 'Z':
				return 21;
			case 'E':
			case 'e':
				return 18;
			case 'P':
				return 15;
			case 'T':
			case 't':
				return 12;
			case 'G':
			case 'g':
				return 9;
			case 'M':
				return 6;
			case 'k':
			case 'K':
				return 3;
			case 'h':
			case 'H':
				return 2;
			case 'D':
				return 1; // Unofficial capitalisation-based variant of da (deca)
			case 'd':
				if (prefix.Len()>1 && prefix[1]=='a') return 1; // deca (da)
				return -1; // deci (d)
			case 'c':
			case 'C':
				return -2;
			case 'm':
				return -3;
			case '¶Ã':							//-------- ≤√¥£ª£ªŒ¢√Î
			case 'u':
			case 'U':
				return -6;
			case 'n':
			case 'N':
				return -9;
			case 'p':
				return -12;
			case 'f':
			case 'F':
				return -15;
			case 'a':
			case 'A':
				return -18;
			case 'z':
				return -21;
			case 'y':
				return -24;
		}
	}
	return 0;
}

wxString GetPrefixOfMagnitude(const int &magnitude)
{
	switch (magnitude)
	{
		case 24:
			return "Y";
		case 21:
			return "Z";
		case 18:
			return "E";
		case 15:
			return "P";
		case 12:
			return "T";
		case 9:
			return "G";
		case 6:
			return "M";
		case 3:
			return "k";
		case 2:
			return "h";
		case -1:
			return "da"; // deci (d)
		case -2:
			return "c";
		case -3:
			return "m";
		case -6:
			return wxString::FromUTF8("\xC2\xB5");
		case -9:
			return "n";
		case -12:
			return "p";
		case -15:
			return "f";
		case -18:
			return "a";
		case -21:
			return "z";
		case -24:
			return "y";
	}
	return wxEmptyString;
}

void TrimZeroes(wxString &output)
{
	if (output.Contains(localeDecimalPoint))
	{
		wxString regexScratch;
		regexScratch << "\\" << localeDecimalPoint << "?0+(?=[^" << localeDecimalPoint << "0-9]|$)";
		wxRegEx decimals(regexScratch,wxRE_ADVANCED);
		decimals.ReplaceFirst(&output,"");
	}
	wxRegEx zeroes("[Ee]([-+])0+",wxRE_ADVANCED);
	zeroes.ReplaceAll(&output,"e\\1");
	if (output.Last()=='+' || output.Last()=='-') output.Append("0");
}

/********
  Event
********/

DEFINE_EVENT_TYPE(wxEVT_VALIDATOR_CHANGE)

ValidatorChangeEvent::ValidatorChangeEvent()
	: wxEvent(0,wxEVT_VALIDATOR_CHANGE)
{
}

wxEvent* ValidatorChangeEvent::Clone() const
{
	return new ValidatorChangeEvent();
}

/************************
  Class Specialisations
************************/

// unsigned short

template<>
bool ValidatorNumeric<unsigned short>::ValidateExternally() const
{
	return (m_host==NULL || m_host->Validate(GetWindow(),unsigned long(m_value)));
}

template<>
wxString ValidatorNumeric<unsigned short>::FormatBasic(const unsigned short &value)
{
	return wxString::Format("%u",value);
}

template<>
bool ValidatorNumeric<unsigned short>::SaveToType(unsigned short &destination, const double &value)
{
	if (value<0.0 || value>double(unsigned short(-1)))
	{ // Out of type bounds
		return false;
	}
	else
	{
		destination = unsigned short(value);
		return true;
	}
}

template<>
bool ValidatorNumeric<unsigned short>::SaveToType(unsigned short &destination, const unsigned long &value)
{
	if (value>(unsigned long)(unsigned short(-1)))
	{ // Out of type bounds
		return false;
	}
	else
	{
		destination = unsigned short(value);
		return true;
	}
}

/*template<>
unsigned short ValidatorNumeric<unsigned short>::GetMagnitude(const unsigned short &value)
{
	abs
}*/

/*********************************
  Helper Functions (specialised)
*********************************/

template <>
bool ReadValueFromString<unsigned long>(const wxString &theString, unsigned long* value)
{
	return theString.ToULong(value);
}

template <>
bool ReadValueFromString<signed long>(const wxString &theString, signed long* value)
{
	return theString.ToLong(value);
}