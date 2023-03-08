/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/Validation.h $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#ifndef TT_VALIDATOR_NUMERIC_H
#define TT_VALIDATOR_NUMERIC_H

#include <wx/validate.h>

#include <wx/regex.h>

extern wxString localeJunkNumberChars;
extern wxChar localeDecimalPoint;

/************
  Functions
************/

int GetMagnitudeOfPrefix(const wxString &prefix);
wxString GetPrefixOfMagnitude(const int &magnitude);
void TrimZeroes(wxString &output);

/********
  Event
********/

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE(wxEVT_VALIDATOR_CHANGE, -1)
END_DECLARE_EVENT_TYPES()

class ValidatorChangeEvent : public wxEvent
{
	public:
		ValidatorChangeEvent();
		wxEvent* Clone() const;
};

typedef void (wxEvtHandler::*ValidatorChangeEventFunction)(ValidatorChangeEvent&);

#define EVT_VALIDATOR_CHANGE(fn) \
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_VALIDATOR_CHANGE, wxID_ANY, wxID_ANY, \
	(wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(ValidatorChangeEventFunction, &fn), \
	(wxObject*)NULL),

/****************
  ValidatorHost
****************/

class ValidatorHost
{
	public:
		ValidatorHost() {};
		~ValidatorHost() {};
		virtual bool Validate(wxWindow* control, const unsigned long &value) { return true; };
		virtual bool Validate(wxWindow* control, const signed long &value) { return true; };
		virtual bool Validate(wxWindow* control, const double &value) { return true; };
};

/****************************
  ValidatorNumeric<generic>
****************************/

template<class T>
class ValidatorNumeric : public wxValidator
{
	public:
		ValidatorNumeric(T* source=NULL, ValidatorHost* host=NULL, const wxString &unit=wxEmptyString);
		~ValidatorNumeric();
		virtual wxObject* Clone() const;
		bool Validate(wxWindow* WXUNUSED(parent));
		bool TransferToWindow();
		bool TransferFromWindow();
		bool IsInternallyValid() const;
		void SetExternalValidity(const bool &valid);
		void SetValue(const T &value);
		void SetSource(T* source);
		T GetValue() const;

	protected:
		static bool SaveToType(T &destination, const double &value);
		static bool SaveToType(T &destination, const unsigned long &value);
		ValidatorHost* m_host;
		wxString m_unit;
		T*   m_valueSource;
		bool m_valueValid;
		T    m_value;
		static const unsigned short m_significantFigures;

	private:
		void OnType(wxKeyEvent &event);
		void OnLeave(wxFocusEvent &event);
		void OnChange(ValidatorChangeEvent &event);
		virtual void InterpretContents();
		virtual void FormatValue() const;
		bool ValidateExternally() const;
		static wxString FormatBasic(const T &value);
		//static double GetMagnitude(const T &value);
		bool m_previousValidity;
		bool m_currentlyValidating;
		DECLARE_CLASS(ValidatorNumeric)
		DECLARE_EVENT_TABLE()
};

template<class T>
const unsigned short ValidatorNumeric<T>::m_significantFigures = 9;

template<class T>
wxClassInfo ValidatorNumeric<T>::ms_classInfo(
	wxT("ValidatorNumeric"),
	&wxValidator::ms_classInfo,
	NULL,
	(int)sizeof(ValidatorNumeric<T>),
	NULL
);

BEGIN_EVENT_TABLE_TEMPLATE1(ValidatorNumeric, wxValidator, T)
	EVT_CHAR             ( ValidatorNumeric::OnType   )
	EVT_KILL_FOCUS       ( ValidatorNumeric::OnLeave  )
	EVT_VALIDATOR_CHANGE ( ValidatorNumeric::OnChange )
END_EVENT_TABLE()

template<class T>
ValidatorNumeric<T>::ValidatorNumeric(
	T* source,
	ValidatorHost* host,
	const wxString &unit
) :
	m_host(host),
	m_unit(unit),
	m_valueSource(source),
	m_valueValid(false),
	m_previousValidity(true),
	m_currentlyValidating(false)
{
}

template<class T>
ValidatorNumeric<T>::~ValidatorNumeric()
{
}

template<class T>
wxClassInfo *ValidatorNumeric<T>::GetClassInfo() const
{
	return &ValidatorNumeric<T>::ms_classInfo;
}

template<class T>
wxObject* ValidatorNumeric<T>::Clone() const
{
	ValidatorNumeric<T>* newOne = new ValidatorNumeric<T>(m_valueSource,m_host,m_unit);
	return newOne;
}

template<class T>
bool ValidatorNumeric<T>::Validate(wxWindow* WXUNUSED(parent))
{
	if (!m_currentlyValidating)
	{
		m_currentlyValidating = true;
		bool result = m_valueValid;

		if (m_valueValid)
		{ // Perform additional validation
			result = ValidateExternally();
		}

		SetExternalValidity(result);

		m_currentlyValidating = false;

		return (result || !GetWindow()->IsEnabled());
	}

	else
	{
		return true;
	}
}

template<class T>
bool ValidatorNumeric<T>::TransferFromWindow()
{
	return true;
}

template<class T>
bool ValidatorNumeric<T>::TransferToWindow()
{
	if (m_valueSource!=NULL) SetValue(*m_valueSource);
	return true;
}

template<class T>
void ValidatorNumeric<T>::InterpretContents()		//解释内容？
{
	wxString contents = dynamic_cast<wxTextCtrl*>(GetWindow())->GetValue();

	{
		wxRegEx junk("["+localeJunkNumberChars+"]");
		junk.ReplaceAll(&contents,"");
	}
	if (!contents.IsEmpty())
	{
		wxRegEx hex("^0[xX]([0-9a-fA-F]+)$");
		if (hex.Matches(contents))
		{ // Hexadecimal entry
			unsigned long hexValue;
			if (sscanf(hex.GetMatch(contents,1).char_str(),"%lx",&hexValue)==1)
			{
				if (SaveToType(m_value,hexValue))
				{
					m_valueValid = true;
					return;
				}
			}
		}
		else
		{ // Ordinary entry, possibly including units
			wxString regexString;
			regexString << "^([-+eE0-9" << localeDecimalPoint << "]+)([" << wxString::FromUTF8("YZEePTtGgMkKhHdDcCm\xC2\xB5uUnNpfFaAzy") << "]?)";
			if (!m_unit.IsEmpty()) regexString << "(?:" << m_unit << "|" << m_unit.Lower() << "|" << m_unit.Upper() << "|)";
			regexString << "$";
			wxRegEx full(regexString,wxRE_ADVANCED);
			if (full.Matches(contents))
			{
				double typedValue;
				if (full.GetMatch(contents,1).ToDouble(&typedValue))
				{
					wxString prefix = full.GetMatch(contents,2);
					double realValue = typedValue * pow(10.0, GetMagnitudeOfPrefix(prefix));
					if (SaveToType(m_value,realValue))
					{
						m_valueValid = true;
						return;
					}
				}
			}
		}
	}

	m_valueValid = false;
}

template<class T>
void ValidatorNumeric<T>::FormatValue() const
{
	wxString result = wxEmptyString;
	if (!m_unit.IsEmpty())
	{
		double shownValue = double(m_value);
		int newMagnitude = 0;
		if (shownValue!=0.0)
		{
			newMagnitude = 3 * (int)floor( log10(abs( shownValue )) / 3.0 );
			if (floor(shownValue / pow(10.0, newMagnitude)) > 999) {
			// Actually falls into next magnitude group - miscalculation due to float inaccuracy
				newMagnitude += 3;
			}
			shownValue /= pow(10.0, newMagnitude);
		}

		result << wxString::Format("%.*f",m_significantFigures-int(abs(log10(shownValue))),shownValue);
		TrimZeroes(result);
		result << " " << GetPrefixOfMagnitude(newMagnitude) << m_unit;
	}
	else
	{
		/*if (hexademical)
		{


		}
		else*/
		{
			result << FormatBasic(m_value);
		}
	}

	wxTextCtrl* field = dynamic_cast<wxTextCtrl*>(GetWindow());
	long location = field->GetInsertionPoint();
	long endLocation = field->GetLastPosition();
	// Apply output
	field->ChangeValue(result);
	// Return it either to where it was, or the end if it was at the end before (as the length of the field may have changed
	if (location==endLocation)
	{ // Return to end point, in case the string length was changed
		field->SetInsertionPoint(field->GetLastPosition());
	}
	else
	{
		field->SetInsertionPoint(location);
	}
}

template<class T>
wxString ValidatorNumeric<T>::FormatBasic(const T &value)
{
	wxString result;
	int currentMagnitude = 3 * (int)floor( log10(abs( value )) / 3.0 );
	int scalingMagnitude = 0;
	if (currentMagnitude==-3)
	{ // Format as simple floating point, but ensure it doesn't result in too long a number
		result = wxString::Format("%.*f",m_significantFigures-int(abs(log10(value))),value);
		TrimZeroes(result);
		if (int(result.Length()) > (value<0.0 ? 6 : 5))
		{ // Longer than x.xxx or -x.xxx, so print in engineering notation
			scalingMagnitude = 3;
		}
		else
		{ // Otherwise we've already got a valid representation
			return result;
		}
	}
	else if (currentMagnitude!=3 && currentMagnitude!=0)
	{ // Format in engineering notation, so scale the value for printing
		scalingMagnitude -= currentMagnitude;
	}

	if (scalingMagnitude!=0)
	{
		double shownValue = value * pow(10.0, scalingMagnitude);
		result = wxString::Format("%.*f",m_significantFigures-int(abs(log10(shownValue))),shownValue);
		result << "e";
		if (currentMagnitude>0) result << "+";
		result << currentMagnitude;
	}
	else
	{
		result = wxString::Format("%.*f",m_significantFigures-int(abs(log10(value))),value);
	}
	TrimZeroes(result);
	return result;
}

template<class T>
bool ValidatorNumeric<T>::ValidateExternally() const
{
	return (m_host==NULL || m_host->Validate(GetWindow(),m_value));
}

template<class T>
bool ValidatorNumeric<T>::IsInternallyValid() const
{
	return m_valueValid;
}

template<class T>
void ValidatorNumeric<T>::SetExternalValidity(const bool &valid)
{
	if (valid!=m_previousValidity)
	{
		dynamic_cast<wxTextCtrl*>(GetWindow())->SetOwnBackgroundColour(valid ? wxNullColour: wxColour(255,191,191));
		GetWindow()->Refresh();
		m_previousValidity = valid;
	}
}

template<class T>
void ValidatorNumeric<T>::SetValue(const T &value)
{
	m_value = value;
	m_valueValid = true;
	Validate(NULL);
	FormatValue();
}

template<class T>
void ValidatorNumeric<T>::SetSource(T* source)
{
	m_valueSource = source;
}

template<class T>
T ValidatorNumeric<T>::GetValue() const
{
	return m_value;
}

template<class T>
bool ValidatorNumeric<T>::SaveToType(T &destination, const double &value)
{
	destination = T(value);
	return true;
}

template<class T>
bool ValidatorNumeric<T>::SaveToType(T &destination, const unsigned long &value)
{
	destination = T(value);
	return true;
}

/*template<class T>
double ValidatorNumeric<T>::GetMagnitude(const T &value)
{
	return log10(abs( value ));
}*/

template<class T>
void ValidatorNumeric<T>::OnType(wxKeyEvent &event)
{
	ValidatorChangeEvent newEvent;
	AddPendingEvent(newEvent);
	event.Skip();
}

template<class T>
void ValidatorNumeric<T>::OnLeave(wxFocusEvent &event)
{
	if (m_valueValid) FormatValue();
	event.Skip();
}

template<class T>
void ValidatorNumeric<T>::OnChange(ValidatorChangeEvent &event)
{
	InterpretContents();
	Validate(NULL);
}

/********************************
  ValidatorNumeric<specialised>
********************************/

// double

template<>
wxClassInfo ValidatorNumeric<double>::ms_classInfo(
	wxT("ValidatorNumeric<double>"),
	&wxValidator::ms_classInfo,
	NULL,
	(int)sizeof(ValidatorNumeric<double>),
	NULL
);

// unsigned short

template<>
bool ValidatorNumeric<unsigned short>::ValidateExternally() const;
template<>
wxString ValidatorNumeric<unsigned short>::FormatBasic(const unsigned short &value);
template<>
bool ValidatorNumeric<unsigned short>::SaveToType(unsigned short &destination, const double &value);
template<>
bool ValidatorNumeric<unsigned short>::SaveToType(unsigned short &destination, const unsigned long &value);
template<>
const unsigned short ValidatorNumeric<unsigned short>::m_significantFigures = 5;
template<>
wxClassInfo ValidatorNumeric<unsigned short>::ms_classInfo(
	wxT("ValidatorNumeric<unsigned short>"),
	&wxValidator::ms_classInfo,
	NULL,
	(int)sizeof(ValidatorNumeric<unsigned short>),
	NULL
);

/****************************
  ValidatorTime<generic>
****************************/

template<class T>
class ValidatorTime : public ValidatorNumeric<T>
{
	public:
		ValidatorTime(T* source=NULL, ValidatorHost* host=NULL);
		~ValidatorTime();
		virtual wxObject* Clone() const;

	private:
		void InterpretContents();
		void FormatValue() const;
		DECLARE_CLASS(ValidatorTime)
};

template<class T>
wxClassInfo ValidatorTime<T>::ms_classInfo(
	wxT("ValidatorTime"),
	&ValidatorNumeric<T>::ms_classInfo,
	NULL,
	(int)sizeof(ValidatorTime<T>),
	NULL
);

template<class T>
ValidatorTime<T>::ValidatorTime(
	T* source,
	ValidatorHost* host
) :
	ValidatorNumeric<T>(source,host,wxEmptyString)
{
}

template<class T>
ValidatorTime<T>::~ValidatorTime()
{
}

template<class T>
wxClassInfo *ValidatorTime<T>::GetClassInfo() const
{
	return &ValidatorTime<T>::ms_classInfo;
}

template<class T>
wxObject* ValidatorTime<T>::Clone() const
{
	ValidatorTime<T>* newOne = new ValidatorTime<T>(m_valueSource,m_host);
	return newOne;
}

template<class T>
void ValidatorTime<T>::InterpretContents()
{
	// Catch HH:MM:SS and any trailing units
	static wxRegEx combo("([.0-9]+):([.0-9]+):([.0-9]+)[:space:]*[^.0-9]*[^.[:space:]0-9]*");
	// Catch individual units and whatever surrounds them (right neighbour may have a space)
	static wxRegEx single("([^.0-9[:space:]]*)([.0-9]+)([:space:]*[^.0-9]*[^.[:space:]0-9]*)");
	double days    = 0.0;
	double hours   = 0.0;
	double minutes = 0.0;
	double seconds = 0.0;
	double dummy;
	double* destination;
	wxString leftUnit;
	wxString rightUnit;
	wxString value;
	bool gotOne = false;

	wxString contents = dynamic_cast<wxTextCtrl*>(GetWindow())->GetValue();

	while (combo.Matches(contents))
	{
		gotOne = true;
		combo.GetMatch(contents,1).ToDouble(&dummy);
		hours += dummy;
		combo.GetMatch(contents,2).ToDouble(&dummy);
		minutes += dummy;
		combo.GetMatch(contents,3).ToDouble(&dummy);
		seconds += dummy;
		contents.Replace(combo.GetMatch(contents,0),wxEmptyString,false);
	}

	while (single.Matches(contents))
	{
		gotOne = true;
		destination = NULL;
		value = single.GetMatch(contents,2);
		value.ToDouble(&dummy);
		leftUnit = single.GetMatch(contents,1);
		rightUnit = single.GetMatch(contents,3).Trim(false);

//		dummy *= pow(10.0, GetMagnitudeOfPrefix(rightUnit.Mid(0,1)));

		if (!rightUnit.IsEmpty())
		{
			if (rightUnit.EndsWith("s") && rightUnit.Length()<=2)
			{ // Seconds, maybe with an SI prefix - XX xs
				destination = &seconds;
				if (rightUnit.Length()==2)
				{ // Includes a prefix, and therefore needs to scale the unit；prefix：前缀，根据前缀来改变单位
					dummy *= pow(10.0, GetMagnitudeOfPrefix(rightUnit.Mid(0,1)));
				}
			}
			else if (rightUnit.StartsWith("d"))
			{ // Days - XX d
				destination = &days;
			}
			else if (rightUnit.StartsWith("h"))
			{ // Hours - XX h
				destination = &hours;
			}
			else if (rightUnit.StartsWith("m") || rightUnit.StartsWith(":"))
			{ // Minutes - XX m or XX:--
				destination = &minutes;
			}
		}
		if (destination==NULL)
		{ // Still haven't matched it
			if (!leftUnit.IsEmpty())
			{
				if (leftUnit.EndsWith("h"))
				{ // Minutes - --hXX
					destination = &minutes;
				}
				else if (leftUnit.EndsWith(":"))
				{ // Seconds - --:XX
					destination = &seconds;
				}
			}
		}
		if (destination==NULL) destination = &seconds;
		*destination += dummy;
		contents.Replace(leftUnit+value,wxEmptyString,false);
	}

	if (gotOne)
	{
		seconds += minutes * 60.0;
		seconds += hours * 3600.0;
		seconds += days * 86400.0;
		if (SaveToType(m_value,seconds))
		{
			m_valueValid = true;
			return;
		}
	}
	else
	{
		m_valueValid = false;
	}
}

template<class T>
void ValidatorTime<T>::FormatValue() const
{
	wxString result = wxEmptyString;

	double seconds = abs(double(m_value));
	unsigned long days = floor(seconds / 86400.0);
	seconds -= double(days) * 86400.0;
	unsigned long hours = floor(seconds / 3600.0);
	seconds -= double(hours) * 3600.0;
	unsigned long minutes = floor(seconds / 60.0);
	seconds -= double(minutes) * 60.0;
	unsigned long wholeSeconds = floor(seconds);
	double subSeconds = seconds - double(wholeSeconds);
	double* subSecondsToPrint = &subSeconds;
	bool printedSubSeconds = false;

	if (days>0) result << days << " d "; // Xd
	if (hours>0)
	{
		result << hours;
		if (wholeSeconds>0/* || (days>0 && minutes>0)*/)
		{
			result << wxString::Format(":%02lu:%02lu ",minutes,wholeSeconds); // XX:XX:XX
		}
		else
		{
			if (minutes>0)
			{
				result << wxString::Format("h%02lu ",minutes); // XhXX
			}
			else
			{
				result << " h"; // X h
			}
		}
	}
	else
	{
		if (minutes>0)
		{
			result << minutes;
			if (wholeSeconds>0)
			{
				result << wxString::Format(":%02lu ",wholeSeconds); // X:XX
			}
			else
			{
				result << " m "; // X m
			}
		}
		else
		{ // Just print subseconds, but include the whole seconds in that value
			subSecondsToPrint = &seconds;
		}
	}
	if (*subSecondsToPrint>0.0 || result.IsEmpty())
	{
		if (!result.IsEmpty())
		{
			result.Trim();
			result << ", ";
		}
		double shownValue = *subSecondsToPrint;
		int newMagnitude = 0;
		if (shownValue!=0.0)
		{
			newMagnitude = 3 * (int)floor( log10(abs( shownValue )) / 3.0 );
			if (floor(shownValue / pow(10.0, newMagnitude)) > 999)
			{ // Actually falls into next magnitude group - miscalculation due to float inaccuracy
				newMagnitude += 3;
			}
			shownValue /= pow(10.0, newMagnitude);
		}

		wxString secondResult = wxString::Format("%.*f",m_significantFigures-int(abs(log10(shownValue))),shownValue);
		TrimZeroes(secondResult);
		result << secondResult << " " << GetPrefixOfMagnitude(newMagnitude) << "s";
	}
	result.Trim();

	wxTextCtrl* field = dynamic_cast<wxTextCtrl*>(GetWindow());
	long location = field->GetInsertionPoint();
	long endLocation = field->GetLastPosition();
	// Apply output
	field->ChangeValue(result);
	// Return it either to where it was, or the end if it was at the end before (as the length of the field may have changed
	if (location==endLocation)
	{ // Return to end point, in case the string length was changed
		field->SetInsertionPoint(field->GetLastPosition());
	}
	else
	{
		field->SetInsertionPoint(location);
	}
}

/*****************************
  ValidatorTime<specialised>
*****************************/

// double

template<>
wxClassInfo ValidatorTime<double>::ms_classInfo(
	wxT("ValidatorTime<double>"),
	&ValidatorNumeric<double>::ms_classInfo,
	NULL,
	(int)sizeof(ValidatorTime<double>),
	NULL
);

/*****************************
  Helper Functions (generic)
*****************************/

template<class T>
bool ReadValueFromString(const wxString &theString, T* value)
{
	double tempValue;
	if (theString.ToDouble(&tempValue))
	{
		*value = T(tempValue);
		return true;
	}
	else
	{
		return false;
	}
}

/*********************************
  Helper Functions (specialised)
*********************************/

template<>
bool ReadValueFromString<unsigned long>(const wxString &theString, unsigned long* value);

template<>
bool ReadValueFromString(const wxString &theString, signed long* value);

#endif // TT_VALIDATOR_NUMERIC_H