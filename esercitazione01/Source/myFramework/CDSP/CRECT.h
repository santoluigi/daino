/*
  ==============================================================================

    CRECT.h
    Created: 14 Jun 2022 12:21:35pm
    Author:  gabrielepetrillo

  ==============================================================================
*/

#pragma once
#include "CDSP.h"
#define KCOSCMaxSampleNumber 4096

class CRECT : public CDSP
{
    
public:
    
    CRECT();
    virtual ~CRECT();
    
    virtual void init();
    
    void setNormalizedFreq(double freq);
    
    void process(float *buffer, long bufferLenght, int currentTableIndex, float freq);
    
    int currentTableIndex;
    
protected:
    
    double table1[KCOSCMaxSampleNumber];
    
    double inc;
    double readPos;
    
};
