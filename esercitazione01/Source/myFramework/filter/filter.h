#pragma once

class Filter
{
public:

Filter();
virtual ~Filter();

virtual void SetFilterCutOffFreq(double inFilterFc);
virtual void SetFilterQFactor(double inFilterQ);

virtual void Process(float *inBuffer,
                    float *outBuffer,
                     long inNumOfFrames);


protected:

   float mNormFilterFc; //cutOff
   float mFilterFc;
   
   float mNormFilterQ; //QFactor
    float mFilterQ;
    
    float mAmpFactor;
    
    float mIIRFilterHist1;
    float mIIRFilterHist0;
};

