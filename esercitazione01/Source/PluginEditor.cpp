/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Math.h"

//==============================================================================
Esercitazione01AudioProcessorEditor::Esercitazione01AudioProcessorEditor (Esercitazione01AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    //setSize (400, 500);
    
    lfoValue = audioProcessor.lfoFreq;
    
    guadagno = new class myKnob();
    addAndMakeVisible(guadagno);
    guadagno->setTextValueSuffix (" Cazzo");
    
    cutoff = new class myKnob();
    addAndMakeVisible(cutoff);
    cutoff->setTextValueSuffix ("  Hz");
    cutoff->setRange(30.0, 22050.0, 0.01);
    
    freqLFO = new class myKnob();
    addAndMakeVisible(freqLFO);
    freqLFO->setTextValueSuffix (" Hz");
    freqLFO->setRange(0.5, 22050.0, 0.01);
    
    cutOffFilter = new class myKnob();
    addAndMakeVisible(cutOffFilter);
    cutOffFilter->setTextValueSuffix (" HZ");
    
    resonance = new class myKnob();
    addAndMakeVisible(resonance);
    resonance->setTextValueSuffix (" HZ");
    
    setSize (600, 400);

    gainLabel.setText ("Gain", juce::dontSendNotification);
    gainLabel.attachToComponent (guadagno, false); // [4]
    gainLabel.setFont (juce::Font (16.0f, juce::Font::bold));
    gainLabel.setJustificationType (juce::Justification::centred);
    
    cutoffLabel.setText ("Freq", juce::dontSendNotification);
    cutoffLabel.attachToComponent (cutoff, false); // [4]
    cutoffLabel.setFont (juce::Font (16.0f, juce::Font::bold));
    cutoffLabel.setJustificationType (juce::Justification::centred);
    
    freqLfo.setText ("LFOFreq", juce::dontSendNotification);
    freqLfo.attachToComponent (freqLFO, false); // [4]
    freqLfo.setFont (juce::Font (16.0f, juce::Font::bold));
    freqLfo.setJustificationType (juce::Justification::centred);
    
    cutOffFilterLabel.setText ("CutOff", juce::dontSendNotification);
    cutOffFilterLabel.attachToComponent (cutOffFilter, false); // [4]
    cutOffFilterLabel.setFont (juce::Font (16.0f, juce::Font::bold));
    cutOffFilterLabel.setJustificationType (juce::Justification::centred);
    
    resonanceLabel.setText ("Resonance", juce::dontSendNotification);
    resonanceLabel.attachToComponent (resonance, false); // [4]
    resonanceLabel.setFont (juce::Font (16.0f, juce::Font::bold));
    resonanceLabel.setJustificationType (juce::Justification::centred);

    freqLFO->addListener (this);
    guadagno->addListener (this);
    cutoff->addListener (this);
    cutOffFilter->addListener (this);
    resonance->addListener (this);
    
    //Button
    
      addAndMakeVisible (arm1);
      addAndMakeVisible (arm2);
      addAndMakeVisible (arm3);
      addAndMakeVisible (mute);
      addAndMakeVisible (muteLfo);
    
      arm1.setRadioGroupId (1001);
      arm2.setRadioGroupId (1001);
      arm3.setRadioGroupId (1001);

      arm1.setToggleState(true, "arm1");

      arm1.onClick = [&] { updateToggleState (&arm1); };
      arm2.onClick = [&] { updateToggleState (&arm2); };
      arm3.onClick = [&] { updateToggleState (&arm3); };
      mute.onClick = [&] { updateToggleState (&mute); };
      muteLfo.onClick = [&] { updateToggleState (&muteLfo); };
        
}

Esercitazione01AudioProcessorEditor::~Esercitazione01AudioProcessorEditor()
{
    delete guadagno;
    delete cutoff;
    delete freqLFO;
    delete resonance;
    delete cutOffFilter;
}

//==============================================================================
void Esercitazione01AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("", getLocalBounds(), juce::Justification::centred, 1);
}

void Esercitazione01AudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    if(slider == guadagno) {
        audioProcessor.gain = linToLog((slider->getValue()/127.0), 0.0001 , 1.0);
        printf("gain\n");
    } else if (slider == cutoff){
        printf("cutoff\n");
        audioProcessor.freq = linToLog((slider->getValue()), 30.0 , 22050.0);
    } else if (slider == freqLFO){
        lfoValue = slider->getValue();
        audioProcessor.lfoFreq = slider->getValue();
        printf("freqLFO\n");
    } else if (slider == cutOffFilter){
        audioProcessor.setValueFilterCutOff(slider->getValue()/127.0);
        printf("cut");
    } else if (slider == resonance){
        audioProcessor.setValueFilterQ(slider->getValue()/127.0);
        printf("q");
    }

}

void Esercitazione01AudioProcessorEditor::updateToggleState (juce::Button* button)
{
    auto state = button->getToggleState();
    juce::String stateString = state ? "ON" : "OFF";
    
    if(button == &arm1){
        audioProcessor.index = 0;
    } else if (button == &arm2){
        audioProcessor.index = 1;
    } else if (button == &arm3){
        audioProcessor.gain = 0.5;
    } else if (button == &mute){
        if(stateString == "OFF"){
            audioProcessor.gain = 0;
        } else {
            audioProcessor.gain = 1;
        }
        
    } else if (button == &muteLfo){
        if(stateString == "OFF"){
            audioProcessor.lfoFreq = 0.0;
        } else {
            audioProcessor.lfoFreq = lfoValue;
        }
    }
}

void Esercitazione01AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
   //gain.setBounds (getWidth()/2 - 100, getHeight()/2 - 100, 200, 200);
    guadagno->setBounds (100, 20, 150, 150);
    cutoff->setBounds (100, 200, 150, 150);
    freqLFO->setBounds (300, 20, 150, 150);
    cutOffFilter->setBounds (300, 200, 150, 150);
    resonance->setBounds (500, 20, 150, 150);
    
    arm1.setBounds (20, 40, getWidth() - 30, 20);
    arm2.setBounds (20, 70, getWidth() - 30, 20);
    arm3.setBounds (20, 100, getWidth() - 30, 20);
    mute.setBounds (20, 130, getWidth() - 30, 20);
    muteLfo.setBounds (20, 160, getWidth() - 30, 20);
}



float Esercitazione01AudioProcessorEditor::linToLog (float value, float min, float max){
    
    float logValue;
    float esponente;
    
    esponente = (((value - min)/(max-min))*(log10(max) - log10(min)) + log10(min));
    
    logValue = pow(10,esponente);
    
    return logValue;
}
