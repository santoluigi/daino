/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "COSC.h"
#include "CSAW.h"
#include "CTRI.h"
#include "CRECT.h"
#include "CWHITE.h"
#include "filter.h"

//==============================================================================
/**
*/
class Esercitazione01AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Esercitazione01AudioProcessor();
    ~Esercitazione01AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float gain;

    
    double freq; //in hz
    double lfoFreq; //in Hz
    
    void setValueFilterCutOff(float cutOff);
    void setValueFilterQ(float q);
    
    int index;
    
protected:
    
    float preGain;
    
    COSC *osc;
    COSC *lfo;
    CSAW *saw;
    CTRI *tri;
    CRECT *rect;
    WHITE *white;
    
    Filter *filter1;
    Filter *filter2;


private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Esercitazione01AudioProcessor)
};
