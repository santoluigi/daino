/*
  ==============================================================================

    OtherLookAndFeel.cpp
    Created: 10 Jun 2022 5:48:05pm
    Author:  gabrielepetrillo

  ==============================================================================
*/

#include "OtherLookAndFeel.h"

void OtherLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&)
{
    
    auto radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
    auto centreX = (float) x + (float) width  * 0.5f;
    auto centreY = (float) y + (float) height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    
    juce::Path p;
    auto pointerLength = radius * 0.33f;
    auto pointerThickness = 2.0f;
    p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));
    

    
    // fill
    g.setColour (juce::Colours::black);
    g.fillEllipse (rx, ry, rw, rw);

    // outline
    g.setColour (juce::Colours::grey);
    g.drawEllipse (rx, ry, rw, rw, 1.0f);
    
    // pointer
    g.setColour (juce::Colours::white);
    g.fillPath (p);
}
