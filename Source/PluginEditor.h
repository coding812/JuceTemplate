#pragma once
#include "PluginProcessor.h"

class MyPluginEditor : public juce::AudioProcessorEditor
{
public:
    MyPluginEditor (MyPluginProcessor&);
    ~MyPluginEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    MyPluginProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyPluginEditor)
};