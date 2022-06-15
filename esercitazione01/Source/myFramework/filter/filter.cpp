#include "filter.h"
#include "Math.h"

Filter::Filter()
{
   SetFilterCutOffFreq(1.0);
   SetFilterQFactor(0.0);
   
    mAmpFactor = 1.0;
}

Filter::~Filter()
{
}

#pragma mark -

void Filter::SetFilterCutOffFreq(double inFilterFc)
{
    if(inFilterFc < 0)
        inFilterFc = 0;
    if(inFilterFc > 1)
        inFilterFc = 1.0;
    
    mNormFilterFc = inFilterFc;
    
    // limit the max value
    inFilterFc = 0.65 * inFilterFc;
    
    mFilterFc = 2.0 * sin(3.14 * 0.4 * pow(inFilterFc, 3));
    
}

void Filter::SetFilterQFactor(double inFilterQ)
{
    mNormFilterQ = inFilterQ;
    
    mFilterQ = 2.0 - 1.8 * inFilterQ;
    mAmpFactor = 1.0 - 0.6 * inFilterQ;
}

void Filter::Process(float *inBuffer,
                     float *outBuffer,
                     long inNumOfFrames)
{
    if(inNumOfFrames == 0)
        return;
    
    double L, H, B;
    long counter;
    long length = inNumOfFrames;
    
    //get the value in only one step
    double fc = mFilterFc;
    double q = mFilterQ;
    
    
    for(counter = 0; counter<length; counter++){
        L = mIIRFilterHist1 + fc * mIIRFilterHist0;
        mIIRFilterHist0 += fc * (inBuffer[counter] - L - q * mIIRFilterHist0);
        mIIRFilterHist1 = L;
        outBuffer[counter] = mAmpFactor * L;
        

    }

}

