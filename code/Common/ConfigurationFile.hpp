/**
  * \file ConfigurationFile.hpp Declaration of the ConfigurationFile class and the ConfigurationFileException class.
  *
  *
  */
#ifndef CONFIGURATION_FILE_HPP
#define CONFIGURATION_FILE_HPP 

#ifdef _MSC_VER
#pragma warning (disable : 4786)
#endif

#include "ConfigurationValue.hpp"
#include <string>
#include <map>

#define DEFAULT_DELIMITORS_LIST " \t\r\n"

using namespace std;

/**
  * A class providing a simple interface to a file of plain text configuration values.  
  * A configuration file is assumed to be comprised of one or more named sections.  The section name has the syntax:
  *
  * [Section Name] 
  * 
  * where Name is the name of the section.  Within each named section, zero or more configuration values may be defined, using 
  * the syntax: 
  *
  * Key = Value
  * 
  * where Key is the unique name (key) of the configuration value, and value is its value expressed as plain text. 
  * The types of value supported are string and numeric values.  Hexadecimal numeric values must be preceded by a 
  * 0x or 0X. Only positive hexadecimal values are supported.
  * For example, the contents of the configuration file could be as follows
  * 
  * [Section Foo]
  * 
  * FooVar1 = Dog
  * 
  * FooVar2 = 0.5
  *
  * [Section Bar]
  *
  * BarVar1 = Cat
  * 
  * BarVar2 = 0.9
  *
  * BarVarHex = 0x0FFD
  * 
  * Names and values of configuration variables must not contain whitespace.  Section names may contain 
  * whitespace. Lines beginning with an '#' are treated as comments.
  * 
  * The value returned by the getValue() function is a %ConfigurationValue. The %ConfigurationValue class permits the returned value to be converted 
  * automatically to the type of the lvalue.  It is up to the user to ensure that the lvalue is of a type appropriate to 
  * the configuration value requested.
  *
  * The contents of the configuration file are cached when the instance is constructed, making subsequent access quite efficient.
  */
class ConfigurationFile
{
public:

	/**
	  * Default constructor.
	  *
	  */
	ConfigurationFile();

	/**
	  * Class constructor. Constructs an instance of ConfigFile from a filename.
	  * \param configFile The name of the config file.
	  *
	  */
	ConfigurationFile(string const& configFile);

	/**
	  * Opens and reads the supplied configuration file.
	  * \param configFile The name of the config file.
	  *
	  */
	void Open(string const& configFile);
	
	/**
	  * Saves the configuration stored in mContents to the supplied file name.
	  * \param fileName The name of the config file.
	  * \param align	If true it aligns the key-values into two columns.
	  *
	  */
	void ConfigurationFile::SaveToFile(string const& fileName, bool align = true);	

	/**
	  * Get a value from the configuration file. The value is keyed by its name and its section within the file. 
	  * If the value does not exist, an exception is thrown.  Otherwise, the value is returned as a StringValueConversion 
	  * object, which will be automatically converted to the type of the lvalue.
	  * \param section The section of the config file in which the value is contained.
	  * \param key	The name of the value within the section.
	  * \return The value of the entry.
	  *
	  */
	const ConfigurationValue& getValue(string const& section, string const& key) const;

	/**
	  * Set a value to the configuration file. The value is keyed by its name and its section.
	  * \param section The section of the config file in which the value is contained.
	  * \param key	The name of the value within the section.
	  * \param The value of the entry.
	  *
	  */	
	void setValue(const string& section, const string& key, const ConfigurationValue& value);
  
private:
	/**
	  * Removes leading and trailing delimitors from a string. The recognised delimitors may be supplied as an argument. 
	  * The defaults delimitors which are recognised are " ", "\t", "\r" and "\n".
	  * \param source The source string.
	  * \param delimitors The recognised delimitors.
	  * \return The substring.
	  *
	  */
	string removeDelimitors(const string& source,  const char* delimitors = DEFAULT_DELIMITORS_LIST); 

	/**
	  * Retrieves the section and key from the 'section/key' format.
	  * \param sectionAndKey Section and key in 'section/key' format.
	  * \param section The retrieved section.
	  * \param key The retrieved key.
	  *
	  */
	void getSectionAndKey(const string& sectionAndKey, string& section, string& key);

	/**
	  * Extracted keys and values. 
	  * This maps the name of the configuration variable to the value of the configuration variable.
	  *
	  */
	map<string, ConfigurationValue> mContents;

};

#endif