/**
  * \file ConfigurationValue.hpp Declaration of the ConfigurationValue class.
  */
#ifndef CONFIGURATION_VALUE_HPP
#define CONFIGURATION_VALUE_HPP


#include "General.h"
#include <string>
using namespace std;

/**
  * Class representing a value in a configuration file.  This class is used to convert plain text values, read from a 
  * configuration file, into the type required by the application, via the defined conversion operators. Currently the types  
  * double and string are supported. This class can easily be extended to handle other 'simple' types.  
  */
class ConfigurationValue
{
public:
	/**
	  * Default constructor.
	  */
	ConfigurationValue(void);

	/**
	  * Constructs a value from a string. Declared explicit (non-converting constructor).
	  * \param value The string value.
	  */
	explicit ConfigurationValue(const string& value);

	/**
	  * Constructs a value from a double value. Declared explicit (non-converting constructor).
	  * \param value The double value.
	  */
	explicit ConfigurationValue(double value);

	/**
	  * Constructs a value from a C-string (null-terminated) value. Declared explicit (non-converting constructor).
	  * \param value The C-string value.
	  */
	explicit ConfigurationValue(const uint8* value);

	/**
	  * Copy constructor. 
	  * \param value The value.
	  */
	ConfigurationValue(const ConfigurationValue& value);

	/**
	  *	Assignment operator.
	  * \param value The value to be assigned, expressed as a %ConfigurationValue.
	  * \return The newly assigned value.
	  */
	ConfigurationValue& operator=(ConfigurationValue const& value);

	/**
	  *	Assignment operator.
	  * \param value The value to be assigned, expressed as a double.
	  * \return The newly assigned value.
	  */
	ConfigurationValue& operator=(double value);

	/**
	  *	Assignment operator.
	  * \param value The value to be assigned, expressed as a string.
	  * \return The newly assigned value.
	  */
	ConfigurationValue& operator=(string const& value);

	/**
	  * Conversion operator. Converts the value to a string.
	  * \return The value as a string.
	  */
	operator string() const;

	/**
	  * Conversion operator. Converts the value to a double.
	  * \return The value as a double.
	  */
	operator double() const;

	operator uint32() const;

private:
	/**
	  * The value.
	  */
	string mValue;
};



#endif