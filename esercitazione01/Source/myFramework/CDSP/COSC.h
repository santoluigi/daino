/*
  ==============================================================================

    COSC.h
    Created: 12 Apr 2022 12:08:51pm
    Author:  gabrielepetrillo

  ==============================================================================
*/

#pragma once
#include "CDSP.h"
#define KCOSCMaxSampleNumber 4096

class COSC : public CDSP
{
    
public:
    
    COSC();
    virtual ~COSC();
    
    virtual void init();
    
    void setNormalizedFreq(double freq);
    
    void process(float *buffer, long bufferLenght, int currentTableIndex, float freq);
    
    int currentTableIndex;
    
protected:
    
    double table[KCOSCMaxSampleNumber];
    double table2[KCOSCMaxSampleNumber];
    
    double inc;
    double readPos;
    
};
