/*
  ==============================================================================

    CTRI.h
    Created: 14 Jun 2022 11:31:54am
    Author:  gabrielepetrillo

  ==============================================================================
*/

#pragma once
#include "CDSP.h"
#define KCOSCMaxSampleNumber 4096

class CTRI : public CDSP
{
    
public:
    
    CTRI();
    virtual ~CTRI();
    
    virtual void init();
    
    void setNormalizedFreq(double freq);
    
    void process(float *buffer, long bufferLenght, int currentTableIndex, float freq);
    
    int currentTableIndex;
    
protected:
    
    double table1[KCOSCMaxSampleNumber];
    
    double inc;
    double readPos;
    
};
