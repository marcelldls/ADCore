#ifndef NDPluginROI_H
#define NDPluginROI_H

#include <epicsTypes.h>
#include <asynStandardInterfaces.h>

#include "NDPluginDriver.h"

#define MAX_CENTROID_FRAMES 100

/** Structure defining a Region-Of-Interest (ROI) */
struct NDROI {
    NDDimension_t dims[ND_ARRAY_MAX_DIMS];
    double *profiles[ND_ARRAY_MAX_DIMS];
    int profileSize[ND_ARRAY_MAX_DIMS];
    int nElements;
    int bgdWidth;
    double total;
    double net;
    double mean;
    double min;
    double max;
    double lowClip;
    int doLowClip;
    double highClip;
    int doHighClip;
    double centroidX;
    double centroidY;
    int nCentroidFrames;
    int centroidFrameNo;
    double arrCentroidX[MAX_CENTROID_FRAMES];
    double arrCentroidY[MAX_CENTROID_FRAMES];
    NDArray *pBackground;
    int nBackgroundElements;
    int validBackground;
    int doBackground;
    double histMin;
    double histMax;
    int histSize;
    double *histogram;
    
    NDROI();
    ~NDROI();
};

NDROI::NDROI() {
    this->nCentroidFrames  = 1;
    this->centroidFrameNo  = 0;
    this->pBackground      = NULL;
}

NDROI::~NDROI() {
    if (pBackground) pBackground->release();
}    

/* ROI general parameters */
#define NDPluginROINameString               "NAME"                /* (asynOctet,   r/w) Name of this ROI */
#define NDPluginROIUseString                "USE"                 /* (asynInt32,   r/w) Use this ROI? */
#define NDPluginROIHighlightString          "HIGHLIGHT"           /* (asynInt32,   r/w) Highlight ROIs? */

/* ROI definition */
#define NDPluginROIDim0MinString            "DIM0_MIN"          /* (asynInt32,   r/w) Starting element of ROI in each dimension */
#define NDPluginROIDim0SizeString           "DIM0_SIZE"         /* (asynInt32,   r/w) Size of ROI in each dimension */
#define NDPluginROIDim0MaxSizeString        "DIM0_MAX_SIZE"     /* (asynInt32,   r/o) Maximum size of ROI in each dimension */
#define NDPluginROIDim0BinString            "DIM0_BIN"          /* (asynInt32,   r/w) Binning of ROI in each dimension */
#define NDPluginROIDim0ReverseString        "DIM0_REVERSE"      /* (asynInt32,   r/w) Reversal of ROI in each dimension */
#define NDPluginROIDim1MinString            "DIM1_MIN"          /* (asynInt32,   r/w) Starting element of ROI in each dimension */
#define NDPluginROIDim1SizeString           "DIM1_SIZE"         /* (asynInt32,   r/w) Size of ROI in each dimension */
#define NDPluginROIDim1MaxSizeString        "DIM1_MAX_SIZE"     /* (asynInt32,   r/o) Maximum size of ROI in each dimension */
#define NDPluginROIDim1BinString            "DIM1_BIN"          /* (asynInt32,   r/w) Binning of ROI in each dimension */
#define NDPluginROIDim1ReverseString        "DIM1_REVERSE"      /* (asynInt32,   r/w) Reversal of ROI in each dimension */
#define NDPluginROIDim2MinString            "DIM2_MIN"          /* (asynInt32,   r/w) Starting element of ROI in each dimension */
#define NDPluginROIDim2SizeString           "DIM2_SIZE"         /* (asynInt32,   r/w) Size of ROI in each dimension */
#define NDPluginROIDim2MaxSizeString        "DIM2_MAX_SIZE"     /* (asynInt32,   r/o) Maximum size of ROI in each dimension */
#define NDPluginROIDim2BinString            "DIM2_BIN"          /* (asynInt32,   r/w) Binning of ROI in each dimension */
#define NDPluginROIDim2ReverseString        "DIM2_REVERSE"      /* (asynInt32,   r/w) Reversal of ROI in each dimension */
#define NDPluginROIDataTypeString           "ROI_DATA_TYPE"     /* (asynInt32,   r/w) Data type for ROI.  -1 means automatic. */

/* ROI high and low clipping */
#define NDPluginROILowClipString            "LOW_CLIP"          /* (asynFloat64, r/w) Low clip value */
#define NDPluginROIDoLowClipString          "DO_LOW_CLIP"       /* (asynInt32,   r/w) Do low clipping? */
#define NDPluginROIHighClipString           "HIGH_CLIP"         /* (asynFloat64, r/w) High clip value */
#define NDPluginROIDoHighClipString         "DO_HIGH_CLIP"      /* (asynInt32,   r/w) Do high clipping? */
    
/* ROI background array subtraction */
#define NDPluginROIGrabBackgroundString     "GRAB_BACKGROUND"     /* (asynInt32,   r/w) Use current frame as background */
#define NDPluginROIDoBackgroundString       "DO_BACKGROUND"       /* (asynInt32,   r/w) Do background subtraction? */
#define NDPluginROIValidBackgroundString    "VALID_BACKGROUND"    /* (asynInt32,   r/o) Is there a valid background */
    
/* ROI statistics */
#define NDPluginROIComputeStatisticsString  "COMPUTE_STATISTICS"  /* (asynInt32,   r/w) Compute statistics for this ROI? */
#define NDPluginROIBgdWidthString           "BGD_WIDTH"         /* (asynInt32,   r/w) Width of background region when computing net */
#define NDPluginROIMinValueString           "MIN_VALUE"         /* (asynFloat64, r/o) Minimum counts in any element */
#define NDPluginROIMaxValueString           "MAX_VALUE"         /* (asynFloat64, r/o) Maximum counts in any element */
#define NDPluginROIMeanValueString          "MEAN_VALUE"        /* (asynFloat64, r/o) Mean counts of all elements */
#define NDPluginROITotalString              "TOTAL"             /* (asynFloat64, r/o) Sum of all elements */
#define NDPluginROINetString                "NET"               /* (asynFloat64, r/o) Sum of all elements minus background */
#define NDPluginROICentroidFramesString     "CENTROID_FRAMES"   /* (asynInt32,   r/w) Number of frames to average centroids */
#define NDPluginROICentroidXString          "CENTROIDX_VALUE"   /* (asynFloat64, r/o) X centroid */
#define NDPluginROICentroidYString          "CENTROIDY_VALUE"   /* (asynFloat64, r/o) Y centroid */
    
/* ROI histogram */
#define NDPluginROIComputeHistogramString   "COMPUTE_HISTOGRAM"   /* (asynInt32,   r/w) Compute histogram for this ROI? */
#define NDPluginROIHistSizeString           "HIST_SIZE"         /* (asynInt32,   r/w) Number of elements in histogram */
#define NDPluginROIHistMinString            "HIST_MIN"          /* (asynFloat64, r/w) Minimum value for histogram */
#define NDPluginROIHistMaxString            "HIST_MAX"          /* (asynFloat64, r/w) Maximum value for histogram */
#define NDPluginROIHistEntropyString        "HIST_ENTROPY"      /* (asynFloat64, r/o) Image entropy calculcated from histogram */
#define NDPluginROIHistArrayString          "HIST_ARRAY"        /* (asynFloat64Array, r/o) Histogram array */

/* ROI profiles - not yet implemented */
#define NDPluginROIComputeProfilesString    "COMPUTE_PROFILES"    /* (asynInt32,   r/w) Compute profiles for this ROI? */

/* Arrays of total and net counts for MCA or waveform record */   
#define NDPluginROITotalArrayString         "TOTAL_ARRAY"       /* (asynInt32Array, r/o) Total counts array */
#define NDPluginROINetArrayString           "NET_ARRAY"         /* (asynInt32Array, r/o) Net counts array */


/** Extract Regions-Of-Interest (ROI) from NDArray data; the plugin can be a source of NDArray callbacks for
  * other plugins, passing these sub-arrays. 
  * The plugin also optionally computes a statistics on the ROI. */
class NDPluginROI : public NDPluginDriver {
public:
    NDPluginROI(const char *portName, int queueSize, int blockingCallbacks, 
                 const char *NDArrayPort, int NDArrayAddr, int maxROIs, 
                 int maxBuffers, size_t maxMemory,
                 int priority, int stackSize);
    /* These methods override the virtual methods in the base class */
    void processCallbacks(NDArray *pArray);
    asynStatus writeInt32(asynUser *pasynUser, epicsInt32 value);

    /* These methods are unique to this class */
    asynStatus readFloat64Array(asynUser *pasynUser, epicsFloat64 *value, 
                                size_t nelements, size_t *nIn);
protected:
    /* ROI general parameters */
    int NDPluginROIName;
    #define FIRST_NDPLUGIN_ROI_PARAM NDPluginROIName
    int NDPluginROIUse;
    int NDPluginROIHighlight;

    /* ROI definition */
    int NDPluginROIDim0Min;
    int NDPluginROIDim0Size;
    int NDPluginROIDim0MaxSize;
    int NDPluginROIDim0Bin;
    int NDPluginROIDim0Reverse;
    int NDPluginROIDim1Min;
    int NDPluginROIDim1Size;
    int NDPluginROIDim1MaxSize;
    int NDPluginROIDim1Bin;
    int NDPluginROIDim1Reverse;
    int NDPluginROIDim2Min;
    int NDPluginROIDim2Size;
    int NDPluginROIDim2MaxSize;
    int NDPluginROIDim2Bin;
    int NDPluginROIDim2Reverse;
    int NDPluginROIDataType;

    /* ROI high and low clipping */
    int NDPluginROILowClip;
    int NDPluginROIDoLowClip;
    int NDPluginROIHighClip;
    int NDPluginROIDoHighClip;

    /* ROI background array subtraction */
    int NDPluginROIGrabBackground;
    int NDPluginROIDoBackground;
    int NDPluginROIValidBackground;

    /* ROI statistics */
    int NDPluginROIComputeStatistics;
    int NDPluginROIBgdWidth;
    int NDPluginROIMinValue;
    int NDPluginROIMaxValue;
    int NDPluginROIMeanValue;
    int NDPluginROITotal;
    int NDPluginROINet;
    int NDPluginROICentroidFrames;
    int NDPluginROICentroidX;
    int NDPluginROICentroidY;

    /* ROI histogram */
    int NDPluginROIComputeHistogram;
    int NDPluginROIHistSize;
    int NDPluginROIHistMin;
    int NDPluginROIHistMax;
    int NDPluginROIHistEntropy;
    int NDPluginROIHistArray;
    int NDPluginROIThreshold;

    /* ROI profiles - not yet implemented */
    int NDPluginROIComputeProfiles;

    /* Arrays of total and net counts for MCA or waveform record */   
    int NDPluginROITotalArray;
    int NDPluginROINetArray;
    #define LAST_NDPLUGIN_ROI_PARAM NDPluginROINetArray
                                
private:
    int maxROIs;
    NDROI *pROIs;    /* Array of NDROI structures */
    epicsInt32 *totalArray;
    epicsInt32 *netArray;
};
#define NUM_NDPLUGIN_ROI_PARAMS (&LAST_NDPLUGIN_ROI_PARAM - &FIRST_NDPLUGIN_ROI_PARAM + 1)
    
#endif
