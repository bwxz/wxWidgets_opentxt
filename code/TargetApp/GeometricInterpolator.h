#ifndef GEOMETRIC_INTERPOLATOR_H
#define GEOMETRIC_INTERPOLATOR_H


#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
    double logValueWhen0;  // log of output when value of input is 0
//    double logValueWhen1;  // log of output when value of input is 1 - not used
	double logDifference;  // logValueWhen1 - logValueWhen0
} GeometricInterpolator;

void ConfigureGeometricInterpolator(
      GeometricInterpolator* gi,double valueWhen0, double valueWhen1);

double GetInterpolatedValue(GeometricInterpolator const* gi,double input); // input is between 0 and 1
#ifdef __cplusplus
}
#endif

#endif

