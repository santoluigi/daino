/*
  ==============================================================================

    OtherLookAndFeel.h
    Created: 9 Jun 2022 4:44:34pm
    Author:  gabrielepetrillo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OtherLookAndFeel : public juce::LookAndFeel_V4
{
public:
    
    
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;
};
