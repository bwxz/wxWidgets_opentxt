#include "IntegerTime.hpp"

const uint32 IntegerTime::nanosecondsPerSecond = 1000000000UL;
const uint IntegerTime::logNanosecondsPerSecond = 9U;


IntegerTime::IntegerTime(double a)
{
	negative = a < 0;

	if (negative)
		a = -a;

	seconds = uint32(a);
	a -= seconds;
	a *= nanosecondsPerSecond;
	nanoseconds = uint32(a);
}

IntegerTime::operator double() const
{
	double result;
	result = seconds + double(nanoseconds) / nanosecondsPerSecond;

	if (Negative())
		result = -result;

	return result;
}


IntegerTime IntegerTime::operator-() const
{
	IntegerTime result = *this;

	if (Zero())
		result.negative = false;
	else
		result.negative = !result.negative;

	return result;
}


IntegerTime operator+(IntegerTime const& a, IntegerTime const& b)
{
	bool sameSign = b.Negative() == a.Negative();
	bool changeSign = false;
	IntegerTime result;

	if (sameSign)
	{
		int carry = 0;
		result.nanoseconds = a.nanoseconds + b.nanoseconds;
		
		if (result.nanoseconds >= IntegerTime::nanosecondsPerSecond)
		{
			carry = 1;
			result.nanoseconds -= IntegerTime::nanosecondsPerSecond; 
		}

		result.seconds = a.seconds + b.seconds + carry;
	}
	else
	{
		int borrow = 0;

		result.nanoseconds = a.nanoseconds - b.nanoseconds;
		
		if (result.nanoseconds >= IntegerTime::nanosecondsPerSecond)
		{
			borrow = 1;
			result.nanoseconds += IntegerTime::nanosecondsPerSecond;
		}

		if (a.seconds >= (b.seconds + borrow))
		{
			result.seconds = a.seconds - (b.seconds + borrow); // no sign change
		}
		else
		{
			result.seconds = (b.seconds + borrow) - a.seconds -1; // sign change
			result.nanoseconds = IntegerTime::nanosecondsPerSecond - result.nanoseconds;
			changeSign = true;
		}
	}

	if (!changeSign)
		result.negative = a.negative;
	else
		result.negative = !a.negative;

	return result;
}

IntegerTime operator-(IntegerTime const& a, IntegerTime const& b)
{
	IntegerTime negativeB = -b;
	IntegerTime result = a + negativeB;
	return result;
}

int operator==(IntegerTime const& a, IntegerTime const& b)
{
	int result;

	if (a.Zero() && b.Zero())
		result = int(true);

	else if (a.seconds == b.seconds && 
		a.nanoseconds == b.nanoseconds &&
		a.Negative() == b.Negative())
		result = int(true);

	else
		result = int(false);

	return result;
}

int operator<(IntegerTime const& a, IntegerTime const& b)
{
	int result;

	if (a == b)
		return int(false);


	if (a.Zero() || b.Zero())
	{
		if (b.Zero())
			result = a.Negative() ? int(true) : int(false);
		else  // b is zero
			result = a.Negative() ? int(false) : int(true);
	}

	else if (a.Negative() != b.Negative())
	{
		result = a.Negative();
	}
	else 
	{
		if (a.seconds > b.seconds)
			result = int(false);
		else if (a.seconds < b.seconds)
			result = int(true);
		else if (a.nanoseconds < b.nanoseconds)
			result = int (true);
		else
			result = false;

		if (a.Negative())
			result = result ? int(false) : int(true);
	}
	return result;
}


IntegerTime operator/(IntegerTime const& a, uint b)
{
	const int countEnd = 9; // log10 of 
	IntegerTime result;

	if (b == 0)
		return a;

	result.seconds = a.seconds / b;

	uint32 quotient = 0;
	uint32 dividend = a.seconds % b;
	for( uint32 i = 0; i < IntegerTime::logNanosecondsPerSecond; 
		i++, dividend *= 10, quotient *= 10)
	{

		quotient += dividend / b;
		dividend %= b;		
	}

	result.nanoseconds = a.nanoseconds/ b + quotient;

	return result;
}
