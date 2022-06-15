/*
  ==============================================================================

    myknob.h
    Created: 2 Jun 2022 2:44:08pm
    Author:  gabrielepetrillo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "OtherLookAndFeel.h"


class myKnob : public juce::Slider, OtherLookAndFeel
               
{
    
public:
    
    myKnob();
    virtual ~myKnob();
    
    virtual void init();
    
    OtherLookAndFeel otherLookAndFeel;
    
   // juce::Slider knob;
    
    //void setBounds (int x, int y, int width, int height) override;
    
    
};
