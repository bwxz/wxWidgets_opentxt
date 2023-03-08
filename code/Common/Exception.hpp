/**
  * \file Exception.hpp Declaration of Exception class.
  */
#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include "General.h"
#include <string>
#include <stdexcept>
using namespace std;

namespace Semtech
{
	/**
	  * Class representing an exception. The first constructor takes the reason for the exception, and the line/file 
	  * from which the exception was thrown, as arguments. The second constructor takes as an additional argument, 
	  * the lower level exception which caused the exception to be thrown. A copy constructor and assignment operator are also provided.
	  * This exception class permits chaining of exceptions, so that the the chain of exceptions can be propagated up through the layers 
	  * of the application.  The class provides several methods to access the actual exception data. It inherits from the standard library exception class,
	  * and can be used either as is, or
	  * specialised into more specific exception types.
	  */
	class Exception : public exception
	{	
	public :
		/**
		 * Class constructor.
		 * \param reason The reason the exception was thrown.
		 * \param line The line the exception was thrown from.
		 * \param fileName The file the exception was thrown from.
		 */
		Exception(const string& reason, uint16 line, const string& fileName);

		/**
		 * Class constructor.
		 * \param reason The reason the exception was thrown.
		 * \param line The line the exception was thrown from.
		 * \param fileName The file the exception was thrown from.
		 * \param cause The lower level exception which resulted in this exception.
		 */
		Exception(const string& reason, uint16 line, const string& fileName, const Semtech::Exception& cause);

		/**
		 * Copy constructor. Performs deep copy.
		 * \param rhs The exception to be copied.
		 */
		Exception(const Semtech::Exception& rhs);

		/**
		 * Get the cause of the exception.
		 * \return The causing exception if one exists, null otherwise.
		 */
		const Semtech::Exception* getCause() const;

		/**
		 * Get the line the exception was thrown from.
		 * \return The line the exception was thrown from.
		 */
		uint16 getLine() const;

		/**
		 * Get the file the exception was thrown from.
		 * \return The file the exception was thrown from.
		 */
		const string& getFile() const;

		/**
		 * Get the reason for the exception as a string. Implements the %what() method of the standard library exception class.
		 * \return The reason the exception was thrown.
		 */
		virtual const char* what() const;

		/**
		  * Assignment operator.  Performs deep copy.
		  * \param rhs The exception to be assigned.
		  */
		Semtech::Exception& operator=(const Semtech::Exception& rhs);

		/**
		  * Class destructor.
		  */
		~Exception();


	private :
		/**
		 * The reason the exception was thrown.
		 */
		string mReason;

		/**
		 * The cause of the exception.
		 */
		const Semtech::Exception* mCause;

		/**
		  * The name of the file from which the exception was thrown.
		  */
		string mFileName;

		/**
		 * The line in the file from which the exception was thrown.
		 */
		uint16 mLine;
	};
};


#endif