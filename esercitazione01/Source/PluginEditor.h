/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "myknob.h"
#include "OtherLookAndFeel.h"

//==============================================================================
/**
*/
class Esercitazione01AudioProcessorEditor  : public juce::AudioProcessorEditor,
                                             private juce::Slider::Listener
{
public:
    Esercitazione01AudioProcessorEditor (Esercitazione01AudioProcessor&);
    ~Esercitazione01AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Esercitazione01AudioProcessor& audioProcessor;

    
    //juce::Slider gain;
    juce::Label gainLabel;
    juce::Label cutoffLabel;
    juce::Label freqLfo;
    juce::Label cutOffFilterLabel;
    juce::Label resonanceLabel;
    
    float lfoValue;
    
    //radioBUTTON
    
    juce::ToggleButton arm1 {"arm1"},
                       arm2 {"arm2"},
                       arm3 {"arm3"},
                       mute {"mute"},
                       muteLfo{"muteLfo"};
    
    void updateToggleState (juce::Button* button);

    
    void sliderValueChanged (juce::Slider* slider) override;
    OtherLookAndFeel otherLookAndFeel;
    
    float linToLog(float value, float min, float max);
  
protected:
    myKnob *guadagno;
    myKnob *cutoff;
    myKnob *freqLFO;
    myKnob *cutOffFilter;
    myKnob *resonance;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Esercitazione01AudioProcessorEditor)
};
