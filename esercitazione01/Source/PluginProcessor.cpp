/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Esercitazione01AudioProcessor::Esercitazione01AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    gain = 1.0;
    preGain = gain;
    
    osc = new COSC();
    lfo = new COSC();
    saw = new CSAW();
    tri = new CTRI();
    rect = new CRECT();
    white = new WHITE();
    
    filter1 = new Filter();
    filter2 = new Filter();
    
    lfoFreq = 3;
    freq = 440;
    
    index = 0;
}

Esercitazione01AudioProcessor::~Esercitazione01AudioProcessor()
{
    delete osc;
    delete lfo;
    delete saw;
    delete tri;
    delete rect;
    delete white;
    delete filter1;
    delete filter2;
}

//==============================================================================
const juce::String Esercitazione01AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Esercitazione01AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Esercitazione01AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Esercitazione01AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Esercitazione01AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Esercitazione01AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Esercitazione01AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Esercitazione01AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Esercitazione01AudioProcessor::getProgramName (int index)
{
    return {};
}

void Esercitazione01AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Esercitazione01AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    if(sampleRate > 0 && osc != 0){
        osc->setNormalizedFreq(freq / sampleRate);
        lfo->setNormalizedFreq(lfoFreq / sampleRate);
        saw->setNormalizedFreq(freq / sampleRate);
        tri->setNormalizedFreq(freq / sampleRate);
        rect->setNormalizedFreq(freq / sampleRate);
    }
}

void Esercitazione01AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Esercitazione01AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Esercitazione01AudioProcessor::setValueFilterCutOff(float cutOff){
    
    filter1->SetFilterCutOffFreq(cutOff);
    filter2->SetFilterCutOffFreq(cutOff);
    
};

void Esercitazione01AudioProcessor::setValueFilterQ(float q){
    
    filter1->SetFilterQFactor(q);
    filter2->SetFilterQFactor(q);
    
};

void Esercitazione01AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    float tempGain;
    float incremento = (gain - preGain) /buffer.getNumSamples();
    
    long cycleLength = buffer.getNumSamples();
    
     // ==============================================================================
     // Parametri per Oscillatore
     // ==============================================================================
    
    
    float *samplesFromOSC = new float[buffer.getNumSamples()];
    float *samplesFromLFO = new float[buffer.getNumSamples()];
    float *samplesFromSAW = new float[buffer.getNumSamples()];
    float *samplesFromTRI = new float[buffer.getNumSamples()];
    float *samplesFromRECT = new float[buffer.getNumSamples()];

    float sampleRate = getSampleRate();
    if(sampleRate > 0){
        osc->setNormalizedFreq(freq/sampleRate);
        osc->process(samplesFromOSC, buffer.getNumSamples(),index,freq);
        lfo->setNormalizedFreq(lfoFreq/sampleRate);
        lfo->process(samplesFromLFO, buffer.getNumSamples(),0,lfoFreq);
        saw->setNormalizedFreq(freq/sampleRate);
        saw->process(samplesFromSAW, buffer.getNumSamples(),0,freq);
        tri->setNormalizedFreq(freq/sampleRate);
        tri->process(samplesFromTRI, buffer.getNumSamples(),0,freq);
        rect->setNormalizedFreq(freq/sampleRate);
        rect->process(samplesFromRECT, buffer.getNumSamples(),0,freq);

    }
    
    for(int ct1 = 0; ct1 < buffer.getNumSamples(); ct1++ )    {
        samplesFromLFO[ct1] = 0.5 * samplesFromLFO[ct1] + 0.5;
    }
    
    //  ==============================================================================

    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        tempGain = preGain;
        
        for(int ct1 = 0; ct1<buffer.getNumSamples(); ct1++){
            //channelData[ct1] = samplesFromLFO[ct1] * samplesFromOSC[ct1] * tempGain;
            //channelData[ct1] = samplesFromLFO[ct1] * samplesFromSAW[ct1] * tempGain;
            //channelData[ct1] = samplesFromLFO[ct1] * samplesFromTRI[ct1] * tempGain;
            //channelData[ct1] = samplesFromLFO[ct1] * samplesFromRECT[ct1] * tempGain;
            channelData[ct1] = samplesFromLFO[ct1] * white->init() * tempGain;
       
           
            tempGain += incremento;
        }

        // ..do something to the data...
    }
    preGain = gain;
    delete [] samplesFromOSC;
    delete [] samplesFromLFO;
    delete [] samplesFromSAW;
    delete [] samplesFromTRI;
    delete [] samplesFromRECT;
    
    //=====================================================
    //FILTRO
    //=====================================================
    
    if(totalNumInputChannels > 0){
        
        auto* channelData = buffer.getWritePointer (0);
        filter1->Process(channelData, channelData, cycleLength);

        if (totalNumInputChannels > 1) {
            channelData = buffer.getWritePointer (1);
            filter2->Process(channelData, channelData, cycleLength);
        }
    }
    //======================================================

}

//==============================================================================
bool Esercitazione01AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Esercitazione01AudioProcessor::createEditor()
{
    return new Esercitazione01AudioProcessorEditor (*this);
}

//==============================================================================
void Esercitazione01AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Esercitazione01AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Esercitazione01AudioProcessor();
}
