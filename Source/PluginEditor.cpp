#include "PluginProcessor.h"
#include "PluginEditor.h"

MyPluginEditor::MyPluginEditor(MyPluginProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(400, 300);
}

MyPluginEditor::~MyPluginEditor() {}

void MyPluginEditor::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Hello JUCE + CMake!", getLocalBounds(), juce::Justification::centred, 1);
}

void MyPluginEditor::resized() {}
