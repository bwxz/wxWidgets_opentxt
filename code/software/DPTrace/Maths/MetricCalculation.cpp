/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Maths/MetricCalculation.cpp $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#include "MetricCalculation.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>

#include <vector>
#include <math.h>
#include <limits>

#include <windows.h>

const size_t startOfData = 0x0;

class Point
{
	public:
		unsigned X;	//timestamps
		double Y;
};

class PointsStore
{
	public:
		unsigned maxNumberOfPointsToHold;
		std::list<Point> pointList; //list of points
		void addPoint(Point point);
		std::list<Point>::iterator GetIterator() {std::list<Point>::iterator it; return it;};


		Point *pointArray;
		unsigned pointArrayLength;

		// the follow array is an extension of pointArray. The X is normalized so that there is one point every second.
		// Is a point is missing then a new point is created and it is a linear interpolation between the closest existing points
		double *normalizedArray; //an Array of Y
		unsigned normalizedArrayLength;
		unsigned normalizedArrayFirstXValue;

		PointsStore();
		~PointsStore();

		void ConvertToArray();
		void ConvertToNormalizedArray();
};

PointsStore::PointsStore()
{
	pointArray = NULL;
	pointArrayLength = 0;

	normalizedArray = NULL; //an Array of Y
	normalizedArrayLength = 0;
	normalizedArrayFirstXValue = 0;
}

PointsStore::~PointsStore()
{
	if (pointArray != NULL)
	{
		delete[] pointArray;
	}
	if (normalizedArray != NULL)
	{
		delete[] normalizedArray;
	}
}

void PointsStore::ConvertToNormalizedArray()
{
	if (normalizedArray != NULL)
	{
		delete[] normalizedArray;
	}
	unsigned initialX = pointList.front().X;
	unsigned finalX = pointList.back().X;
	unsigned totalPoints = finalX - initialX + 1;

	normalizedArrayLength = 0;
	normalizedArrayFirstXValue = initialX;


	normalizedArray = new (double[totalPoints]);

	std::list<Point>::iterator it;
	std::list<Point>::iterator itNext;

	for (it = pointList.begin(); it != pointList.end() ; it++)
	{
		if (normalizedArrayLength >= totalPoints)
		{
			//std::cout << "Warning, too many points while normalizing the input file!" << std::endl;
			return;
		}
		normalizedArray[normalizedArrayLength] = it->Y;
		normalizedArrayLength++;	
		
		itNext = it;
		itNext++;

		//if the next element is not one point ahead, then create the missing point(s)	
		// how many missing points?
		if (itNext != pointList.end())
		{
			Point currentPoint = *it;
			Point nextPoint = *(itNext);
			unsigned distance = (nextPoint.X - currentPoint.X);
			if (distance > 1)
			{
				// y = mx + q
				double m = ((nextPoint.Y - currentPoint.Y ) / distance);
				unsigned pointsCreated = 0;
				for (pointsCreated=0; pointsCreated < (distance - 1); pointsCreated++)
				{
					if (normalizedArrayLength >= totalPoints)
					{
						//std::cout << "Warning, too many points while normalizing the input file!" << std::endl;
						return;
					}
					// there is always a previous point
					normalizedArray[normalizedArrayLength] = currentPoint.Y + (pointsCreated + 1) * m;
					normalizedArrayLength++;
				}
			}
		}
	}
}

void PointsStore::ConvertToArray()
{
	
	if (pointArray != NULL)
	{
		delete[] pointArray;

	}
	pointArray = new(Point[pointList.size()]);

	pointArrayLength = 0;

	std::list<Point>::iterator it;
	for (it = pointList.begin(); it != pointList.end() ; it++)
	{
		pointArray[pointArrayLength] = *it;
		pointArrayLength++;
	}
}

void PointsStore::addPoint(Point point)
{
	pointList.push_back(point);
}

class TDEV
{
	public:
		PointsStore* pointStore;
		unsigned windowSize; //this is to avoid computational errors

		double tdevValue;
		bool tdevValueValid;

		TDEV(unsigned windowSize, PointsStore* pointStore);
		void ComputeTDEV();
		void ComputeOldTDEV();
};


void TDEV::ComputeOldTDEV()
{
	if (3 * windowSize < pointStore->normalizedArrayLength)
	{
		double internalSquareSum = 0;
		double fractionalValue = (6.0 * pow(windowSize, 2.0) * (pointStore->normalizedArrayLength  - 3.0 * windowSize + 1));
		
		for (int j = 0; j <= pointStore->normalizedArrayLength - 3 * windowSize; j++)
		{
			double internalSum = 0;
			for (int i = j;	i < j + windowSize; i++)
			{
				internalSum = internalSum 
					+ pointStore->normalizedArray[i] 
					- 2.0 * pointStore->normalizedArray[i + windowSize] 
					+ pointStore->normalizedArray[i + 2 * windowSize];
			}
			internalSquareSum += pow(internalSum, 2.0);
		}
		tdevValue = pow(internalSquareSum / fractionalValue, 0.5);
		tdevValueValid = TRUE;		
	}
	return;
}


void TDEV::ComputeTDEV()
{
	if (3 * windowSize > pointStore->normalizedArrayLength)
	{
		std::cout << "Error calculating TDEV, window too big";
		return;
	}
	double internalSquareSum = 0.0;
	double fractionalValue = (6.0 * pow(windowSize, 2.0) * (pointStore->normalizedArrayLength  - 3.0 * windowSize + 1));

	double internalSum = 0;

	for (int j = 0; j <= pointStore->normalizedArrayLength - 3.0 * windowSize; j++)
	{
		
		if (j==0) // calculate the first sum
		{
			for (int i = j;	i < j + windowSize; i++)
			{
				internalSum = internalSum 
					+ pointStore->normalizedArray[i] 
					- 2 * pointStore->normalizedArray[i + windowSize] 
					+ pointStore->normalizedArray[i + 2 * windowSize];
			}
		}
		else 
		{
			internalSum = internalSum
				- pointStore->normalizedArray[(j - 1)] 
				+ 3 * pointStore->normalizedArray[(j - 1) + windowSize]
				- 3 * pointStore->normalizedArray[(j -1) + 2 * windowSize]
				+ pointStore->normalizedArray[j + 3 * windowSize - 1];
		}
		internalSquareSum += pow(internalSum, 2.0);
	}
	tdevValue = pow(internalSquareSum / fractionalValue, 0.5);
	tdevValueValid = TRUE;
	return;
}

double TdevMadness(const unsigned long &n, const unsigned long &N, double x[]);

double TdevMadness(const unsigned long &n, const unsigned long &N, double x[])
{
	const unsigned long outerMin = 0;
	const unsigned long outerMax = N - (3*n) + 1;
	
	double outerSum = 0.0;
	
	for (unsigned long j=outerMin; j<outerMax; ++j)
	{
		
		const unsigned long innerMin = j;
		const unsigned long innerMax = n + j;
		
		double innerSum = 0.0;
		
		for (unsigned long i=innerMin; i<innerMax; ++i)
		{
			innerSum += x[i+(2*n)] - (2 * x[i+n]) + x[i];
		}
		outerSum += pow(innerSum, 2.0);
	}
	
	double underSquare = outerSum / (6 * pow(n, 2.0) * (N-(3*n)+1));
	double result = pow(underSquare, 0.5);
	return result;
}

TDEV::TDEV(unsigned windowSize, PointsStore* pointStore)
{
	this->pointStore = pointStore;
	this->windowSize = windowSize;
	
	tdevValue = 0;
	tdevValueValid = false;
}

class MTIEWindow
{
	public:

		Point firstPointInTheWindow;

		unsigned size;	//the size of the window, in seconds

		PointsStore* pointStore;

		Point MaxValue;	//max value within the window
		Point MinValue;	//min value within the window
		bool MaxMinValueValid;

		double yDifference;
		double absoluteMaxYDifference;

	
		MTIEWindow(unsigned size, PointsStore* pointStore); // constructor
		
		void update(); //use only with list
		void CalculateFullMTIEfromArray(); // to use when the array is specified
		void CalculateFullMTIEFromNormalizedArray();
		// pointer to the point buffer

	private:
		unsigned currentLeftIndex, currentRightIndex;
		void UpdateMTIECalculationBetweenVectorIndexes(unsigned left, unsigned right);
		bool ShiftWindowsVectorPoints(); // shift the window, doesn't calculate anything
		void InitialiseCurrentLeftRightVectorIndexes();
};

MTIEWindow::MTIEWindow(unsigned size, PointsStore* pointStore)
{
	this->size = size;
	this->pointStore = pointStore;

	MaxValue.X = 0;
	MaxValue.Y = 0;
	
	MinValue.X = 0;
	MinValue.Y = 0;
	MaxMinValueValid = false;
	absoluteMaxYDifference = 0;
	currentLeftIndex = currentRightIndex = 0;

}

bool MTIEWindow::ShiftWindowsVectorPoints() // shift the window, doesn't calculate anything
{
	// check if can be done
	if ((currentRightIndex+1) >= (pointStore->pointArrayLength))
	{
		return false;
	}
	
	//increase the right index, retrieve the best left index associated
	currentRightIndex++;
	Point newRightPoint = pointStore->pointArray[currentRightIndex];
	Point *parser = &pointStore->pointArray[currentLeftIndex];
	
	for (currentLeftIndex; ((currentLeftIndex < currentRightIndex) && (newRightPoint.X - parser->X > size)); currentLeftIndex++, parser++)
	{
		int a = newRightPoint.X - parser->X;
		int b = currentLeftIndex;

	}
	// note in the worst case leftIndex = rightIndex. This can happen if there are gaps in the array X values.
	return true;
}


void MTIEWindow::InitialiseCurrentLeftRightVectorIndexes()
{
	unsigned left = 0;
	unsigned right = 0;
	pointStore->pointArray;
	pointStore->pointArrayLength;

	unsigned initialXValue = pointStore->pointArray[0].X;

	Point *parser = pointStore->pointArray;

	//very simple search
	for (right = 0; (right < pointStore->pointArrayLength) && ((parser->X - initialXValue) <= size); right ++, parser++)
	{
		int a = ((parser->X - initialXValue));
		int b = 2;
	};
	currentLeftIndex = left;
	currentRightIndex = right;

}

//the following expect a window of normalized values: i.e. one point per second
void MTIEWindow::CalculateFullMTIEFromNormalizedArray()
{
	if (pointStore->normalizedArrayLength == 0)
	{
		std::cerr << "MTIE Error: no normalized array" << std::endl;

		return;
	}
	if (pointStore->normalizedArrayLength < size)
	{
		std::cerr << "MTIE Error: Window size too big" << std::endl;
		return;
	}
	if (size < 2)
	{
		std::cerr << "MTIE Error: Window size too small. Minimum window size: 2 seconds" << std::endl;
		return;
	}

	std::cout << "Calculating MTIE: size " << size << ". Optimization enabled " << std::endl;

	double currentMaxValue = pointStore->normalizedArray[0];
	double currentMinValue = pointStore->normalizedArray[0];
	MaxMinValueValid = false;
	absoluteMaxYDifference = 0;

	unsigned leftIndex=0, rightIndex;
	unsigned currentMaxYIndex = leftIndex;
	unsigned currentMinYIndex = leftIndex;

	currentMaxValue = pointStore->normalizedArray[leftIndex];
	currentMinValue = pointStore->normalizedArray[leftIndex];

	bool firstPass = false;

	for (leftIndex = 0; leftIndex < pointStore->normalizedArrayLength - size; leftIndex++)
	{
		rightIndex = leftIndex + size - 1; // rightIndex is included in the MTIE window
		double NewPoint = pointStore->normalizedArray[rightIndex];
		
		if ((firstPass == false) || (NewPoint > currentMaxValue) || (NewPoint < currentMinValue))
		{
			currentMaxValue = pointStore->normalizedArray[leftIndex];
			currentMinValue = pointStore->normalizedArray[leftIndex];

			for (unsigned i = leftIndex; i <= rightIndex; i++)
			{
				double currentPoint = pointStore->normalizedArray[i];
				if (currentPoint > currentMaxValue)
				{
					currentMaxValue = currentPoint;
				} 
				else if (currentPoint < currentMinValue)
				{
					currentMinValue = currentPoint;
				}
			}

			firstPass = true;
		}
		if (currentMaxValue - currentMinValue > absoluteMaxYDifference)
		{
			absoluteMaxYDifference = currentMaxValue - currentMinValue;
		}
	}
}


void MTIEWindow::CalculateFullMTIEfromArray()
{
	MaxValue = pointStore->pointArray[0];
	MinValue = pointStore->pointArray[0];
	MaxMinValueValid = false;
	absoluteMaxYDifference = 0;

	std::cout << "New MTIE: size " << size << " ";
	InitialiseCurrentLeftRightVectorIndexes();
	std::cout << "Init: " << currentLeftIndex << " " << currentRightIndex;
	UpdateMTIECalculationBetweenVectorIndexes(currentLeftIndex, currentRightIndex);

	while (ShiftWindowsVectorPoints() == true)
	{
		Point newPoint = pointStore->pointArray[currentRightIndex];

		// should the old Max/Min point go out of the window -> force recalculation
		if (MaxValue.X < pointStore->pointArray[currentLeftIndex].X || 
			MinValue.X < pointStore->pointArray[currentLeftIndex].X )
		{
			UpdateMTIECalculationBetweenVectorIndexes(currentLeftIndex, currentRightIndex);
		}
		else
		{
			if (newPoint.Y > MaxValue.Y)
			{
				MaxValue = newPoint;
			}
			if (newPoint.Y < MinValue.Y)
			{
				MinValue = newPoint;
			}

			double maxYDifference = MaxValue.Y - MinValue.Y;
			yDifference = maxYDifference;
			if (yDifference > absoluteMaxYDifference)
			{
				absoluteMaxYDifference = yDifference;
			}

		}
	}
	std::cout << std::endl;
	return;
}

void MTIEWindow::UpdateMTIECalculationBetweenVectorIndexes(unsigned left, unsigned right)
{
	if ((left > right) || (right > pointStore->pointArrayLength))
	{
		//std::cout << "Error in MTIEWindow::UpdateMTIECalculationBetweenVectorIndexes" << std::endl;
		return;
	}

	unsigned index;
	Point max;
	Point min;
	Point* pointArray = pointStore->pointArray;
	Point currentPoint;

	for (index = left; index <= right; index ++)
	{		
		currentPoint = pointArray[index]; 
		if (index == left)
		{
			max = pointArray[index];
			min = pointArray[index];		
		}
		else
		{
			if (currentPoint.Y > max.Y)
			{
					//new maximum found
				max = currentPoint;
			}
			if (currentPoint.Y < min.Y)
			{
				min = currentPoint;
			}
		}
	}

	double maxYDifference = max.Y - min.Y;
	yDifference = maxYDifference;
	if (yDifference > absoluteMaxYDifference)
	{
		absoluteMaxYDifference = yDifference;
	}

	// update the object MaxValue
	MaxValue = max;
	MinValue = min;
	MaxMinValueValid = true;
}


void MTIEWindow::update()
{
	//retrieve the value from pointStore;

	Point newPoint = pointStore->pointList.front();
	if (MaxMinValueValid == false)
	{
		MaxValue = newPoint;
		MinValue = newPoint;

		MaxMinValueValid = true;
	}

	
	// check if the timestamp requires a shift in the window
	unsigned newFirstPointInTheWindow; // the left point of the window
	newFirstPointInTheWindow = newPoint.X - size;
	if (newFirstPointInTheWindow > firstPointInTheWindow.X)
	{
		// if the max value or the min value shifted out of the window, they need to be recalculated
		if ((MaxValue.X < newFirstPointInTheWindow) || (MinValue.X < newFirstPointInTheWindow))
		{		
		 	// recalculate max and minimum for the window
			std::list<Point>::iterator it;
			it = pointStore->pointList.end();
			
			Point max;
			Point min;
			
			for (it; ((it != pointStore->pointList.begin()) || ((newPoint.X - size) > (*it).X )) ; it--)
			{
				// check for the biggest X and smallest Y
				if (it == pointStore->pointList.end())
				{
					max = *it;
					min = *it;		
				}
				else
				{
					if (it->Y > max.Y)
					{
						//new maximum found
						max = *it;
					}
					if (it->Y < min.Y)
					{
						min = *it;
					}
				}
			}
			double maxYDifference = max.X - min.X;
			yDifference = maxYDifference;
			if (yDifference > absoluteMaxYDifference)
			{
				absoluteMaxYDifference = yDifference;
			}
		}
		else // otherwise check if the new point is a new max or min point
		{
			if (newPoint.Y > MaxValue.Y)
			{
				MaxValue = newPoint;
			}
			if (newPoint.Y < MinValue.Y)
			{
				MinValue = newPoint;
			}
		}
	}

}

void CalculateMetrics(const std::vector<double> &x, const std::vector<double> &y, std::vector<double> &xMtie, std::vector<double> &yMtie, std::vector<double> &xTdev, std::vector<double> &yTdev)
{
	if (!x.empty())
	{
		unsigned count = 0;

		PointsStore pointStore;

		for (size_t i=0; i<x.size(); ++i)
		{
			Point newPoint;
			newPoint.X = x[i];
			newPoint.Y = y[i];
			pointStore.addPoint(newPoint);
		}

		pointStore.ConvertToArray(); // used by MTIE;
		unsigned intervalSize = pointStore.pointList.back().X - pointStore.pointList.front().X;

		std::vector<MTIEWindow> windows;
		unsigned step = 1;
	
		//populate the windows vector
		for (unsigned i = 0; i < intervalSize; i += step)
		{
			windows.push_back(MTIEWindow(i, &pointStore));
		
			for (int temp = 0; temp < 10; temp++)
			{
				if (i == pow(10.0, temp))
				{
					step = pow (10.0, temp);
					break;
				}
			}
		}
		windows.push_back(MTIEWindow(intervalSize, &pointStore));
		std::cout << windows.size() << std::endl;

		// MTIE calculation
		pointStore.ConvertToNormalizedArray(); // used by TDEV;

		std::vector<MTIEWindow>::iterator vectorIterator;
		for (vectorIterator = windows.begin(); vectorIterator < windows.end(); vectorIterator++)
		{
			vectorIterator->CalculateFullMTIEFromNormalizedArray();
		}		

		// TDEV calculation
		std::vector<TDEV> tdevVector;
		for (unsigned i = 2; i < (pointStore.normalizedArrayLength / 3) ; i = i * 2)
		{
			tdevVector.push_back(TDEV(i, &pointStore));
		}
		tdevVector.push_back(TDEV(pointStore.normalizedArrayLength / 3, &pointStore));

		std::vector<TDEV>::iterator tdevIterator;
		for (tdevIterator = tdevVector.begin(); tdevIterator < tdevVector.end(); tdevIterator ++)
		{
			tdevIterator->ComputeTDEV();
		}		

		// print out MTIE results
		for (vectorIterator = windows.begin(); vectorIterator < windows.end(); vectorIterator++)
		{
			xMtie.push_back(vectorIterator->size);
			yMtie.push_back(vectorIterator->absoluteMaxYDifference);
		}

		// print out TDEV results
		for (tdevIterator = tdevVector.begin(); tdevIterator < tdevVector.end(); tdevIterator ++)
		{
			if (tdevIterator->tdevValueValid)
			{
				xTdev.push_back(tdevIterator->windowSize);
				yTdev.push_back(tdevIterator->tdevValue);
			}
		}
	}
}