/*
  ==============================================================================

    CSAW.h
    Created: 14 Jun 2022 10:40:56am
    Author:  gabrielepetrillo

  ==============================================================================
*/

#pragma once
#include "CDSP.h"
#define KCOSCMaxSampleNumber 4096

class CSAW : public CDSP
{
    
public:
    
    CSAW();
    virtual ~CSAW();
    
    virtual void init();
    
    void setNormalizedFreq(double freq);
    
    void process(float *buffer, long bufferLenght, int currentTableIndex, float freq);
    
    int currentTableIndex;
    
protected:
    
    double table1[KCOSCMaxSampleNumber];
    
    double inc;
    double readPos;
    
};
