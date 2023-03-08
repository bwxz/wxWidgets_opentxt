#ifndef INTEGER_TIME_HPP
#define INTEGER_TIME_HPP

#include "General.h"

class IntgerTime;

class IntegerTime
{
protected:
	static const uint32 nanosecondsPerSecond;
	static const uint logNanosecondsPerSecond;
	uint32 seconds;
	uint32 nanoseconds;
	bool negative;

public:
	IntegerTime(uint32 mySecs = 0, uint32 myNanoseconds = 0, bool myNegative = false)
		:seconds(mySecs), nanoseconds(myNanoseconds),negative(myNegative)
	{}

	IntegerTime(double a);

	void Set(uint32 mySecs, uint32 myNanoseconds = 0, bool myNegative = false)
	{seconds = mySecs, nanoseconds = myNanoseconds, negative = myNegative;}

	bool Zero() const {return (seconds == 0 && nanoseconds == 0);}  //returns true if zero
	bool Negative() const {return negative;}
	uint32 Nanoseconds() const {return nanoseconds;}

	operator double() const;
	IntegerTime operator-() const;

	friend IntegerTime operator+(IntegerTime const& a, IntegerTime const& b);
	friend IntegerTime operator-(IntegerTime const& a, IntegerTime const& b);
	friend int operator==(IntegerTime const& a, IntegerTime const& b);
	friend int operator<(IntegerTime const& a, IntegerTime const& b);
	friend IntegerTime operator/(IntegerTime const& a, uint b);
};

IntegerTime operator-(IntegerTime const& a, IntegerTime const& b);
IntegerTime operator+(IntegerTime const& a, IntegerTime const& b);
int operator==(IntegerTime const& a, IntegerTime const& b);
int operator<(IntegerTime const& a, IntegerTime const& b);
inline int operator!=(IntegerTime const& a, IntegerTime const& b) {return !(a == b);}
inline int operator>=(IntegerTime const& a, IntegerTime const& b) {return !(a < b);}
inline int operator>(IntegerTime const& a, IntegerTime const& b) {return (a != b) && !(a<b);}


IntegerTime operator/(IntegerTime const& a, uint b);

#endif