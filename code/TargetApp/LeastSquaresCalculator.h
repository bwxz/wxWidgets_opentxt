#ifndef LEAST_SQUARES_CALCULATOR_H
#define LEAST_SQUARES_CALCULATOR_H

#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
	double sumX;
	double sumY;
	double sumXY;
	double sumXSquared;
	uint32 n;

} LeastSquaresCalculator;

#define InitialiseLeastSquaresCalculator(lsc) ResetLeastSquaresCalculator(lsc)
void ResetLeastSquaresCalculator(LeastSquaresCalculator* lsc);
void InputLSC(LeastSquaresCalculator* lsc,double x, double y);
double GradientLSC(LeastSquaresCalculator const* lsc);
double InterceptLSC(LeastSquaresCalculator const* lsc);
#define SamplesLSC(lsc) ((lsc)->n)

#ifdef __cplusplus
}
#endif

#endif


