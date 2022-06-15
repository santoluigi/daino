/*
  ==============================================================================

    CWHITE.h
    Created: 14 Jun 2022 4:45:07pm
    Author:  gabrielepetrillo

  ==============================================================================
*/

#pragma once
#include "CDSP.h"
#define KCOSCMaxSampleNumber 4096

class WHITE : public CDSP
{
    
public:
    
    WHITE();
    virtual ~WHITE();
    
    float init();
    
};
