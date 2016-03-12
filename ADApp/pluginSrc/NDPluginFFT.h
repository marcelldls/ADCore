/**
 * NDPluginFFT.h
 *
 * Computes the FFT of 1-D or 2-D data. 
 * 
 * @author Mark Rivers 
 * @date February 2016
 */

#ifndef NDPluginFFT_H
#define NDPluginFFT_H

#include <epicsTypes.h>
#include <epicsTime.h>

#include "NDPluginDriver.h"

/* Per-plugin parameters */
#define FFTReadString            "FFT_READ"             /* (asynInt32,        r/w) Read data */
#define FFTFreqAxisString        "FFT_FREQ_AXIS"        /* (asynFloat64Array, r/o) Frequency axis array */
#define FFTTimePerPointString    "FFT_TIME_PER_POINT"   /* (asynFloat64,      r/o) Time per time point from driver */

/* Per-signal parameters */
#define FFTRealString            "FFT_REAL"             /* (asynFloat64Array, r/o) Real part of FFT */
#define FFTImaginaryString       "FFT_IMAGINARY"        /* (asynFloat64Array, r/o) Imaginary part of FFT */
#define FFTAbsValueString        "FFT_ABS_VALUE"        /* (asynFloat64Array, r/o) Absolute value of FFT */

/** Compute FFTs on signals */
class epicsShareClass NDPluginFFT : public NDPluginDriver {
public:
  NDPluginFFT(const char *portName, int queueSize, int blockingCallbacks, 
              const char *NDArrayPort, int NDArrayAddr, 
              int maxSignals, int maxBuffers, size_t maxMemory,
              int priority, int stackSize);

  //These methods override the virtual methods in the base class
  void processCallbacks(NDArray *pArray);

protected:

  // Per-plugin parameters
  int P_FFTRead;
  #define FIRST_NDPLUGIN_FFT_PARAM P_FFTRead
  int P_FFTTimePerPoint;
  int P_FFTFreqAxis;

  // Per-signal parameters
  int P_FFTReal;
  int P_FFTImaginary;
  int P_FFTAbsValue;
  #define LAST_NDPLUGIN_FFT_PARAM P_FFTAbsValue
                                
private:
  template <typename epicsType> asynStatus convertToDoubleT(NDArray *pArray);
  void allocateArrays();
  void zeroArrays();
  void createAxisArrays();
  asynStatus computeFFTs(NDArray *pArray);
  void computeFFT_1D();

  int maxSignals_;
  int numTimePoints_;
  int numFreqPoints_;
  double timePerPoint_; /* Actual time between points in input arrays */
  double *freqAxis_;
  double *timeSeries_;
  double *FFTComplex_;
  double *FFTReal_;
  double *FFTImaginary_;
  double *FFTAbsValue_;
};

#define NUM_NDPLUGIN_FFT_PARAMS (int)(&LAST_NDPLUGIN_FFT_PARAM - &FIRST_NDPLUGIN_FFT_PARAM + 1)
    
#endif //NDPluginFFT_H
