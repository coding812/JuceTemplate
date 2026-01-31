#include "PluginProcessor.h"
#include "PluginEditor.h"

MyPluginProcessor::MyPluginProcessor()
    : AudioProcessor (BusesProperties().withInput ("Input", juce::AudioChannelSet::stereo(), true)
                                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{}

MyPluginProcessor::~MyPluginProcessor() {}

void MyPluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {}

void MyPluginProcessor::releaseResources() {}

void MyPluginProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Clear buffer to avoid noise
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Simple Volume Bypass (Audio passes through unchanged)
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        // Do audio processing here!
    }
}

juce::AudioProcessorEditor* MyPluginProcessor::createEditor()
{
    return new MyPluginEditor (*this);
}

// This creates the processor instance
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MyPluginProcessor();
}