/*
  ==============================================================================

    myknob.cpp
    Created: 2 Jun 2022 2:44:08pm
    Author:  gabrielepetrillo

  ==============================================================================
*/

#include "myknob.h"
//#include "/Users/gabrielepetrillo/Desktop/esercitazioneJuce/esercitazione01/Source/PluginProcessor.h"
//#include "/Users/gabrielepetrillo/Desktop/esercitazioneJuce/esercitazione01/Source/PluginEditor.h"



myKnob::myKnob()
{
    init();
}

myKnob::~myKnob()
{
    
}

void myKnob::init(){
    
    setSliderStyle (juce::Slider::RotaryVerticalDrag);
    setRange (0.0001, 127.0, 0.01);
    setTextBoxStyle (juce::Slider::TextBoxBelow, false, 90, 20);
    setPopupDisplayEnabled (true, false, this);
    //setTextValueSuffix ("Cazzo");
    //setTextValueSuffix (suffisso);
    setValue(0.0);
    
    
    setLookAndFeel(&otherLookAndFeel);
    
//    setText ("Gain", juce::dontSendNotification);
//    attachToComponent (&gain, false); // [4]
//    setFont (juce::Font (16.0f, juce::Font::bold));
//    setJustificationType (juce::Justification::centred);
    
    
}
