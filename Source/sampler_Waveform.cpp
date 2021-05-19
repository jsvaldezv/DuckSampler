#include <JuceHeader.h>
#include "sampler_Waveform.h"

sampler_Waveform::sampler_Waveform(Sampler_Curso_FinalAudioProcessor& p) : audioProcessorMine (p)
{

}

sampler_Waveform::~sampler_Waveform(){}

void sampler_Waveform::paint (juce::Graphics& g)
{
    //g.fillAll(juce::Colours::cadetblue.darker());
    auto waveform = audioProcessorMine.getWaveform();
    
    if(waveform.getNumSamples() > 0)
    {
        juce::Path p;
        audioPoints.clear();
        
        auto ratio = waveform.getNumSamples() / 700;
        auto buffer = waveform.getReadPointer(0);
        
        for(int sample = 0; sample < waveform.getNumSamples(); sample+=ratio)
        {
            audioPoints.push_back(buffer[sample]);
        }
        
        g.setColour(juce::Colours::yellow);
        p.startNewSubPath(0, 200/2);
        
        for(int sample = 0; sample < audioPoints.size(); ++sample)
        {
            auto point = juce::jmap(audioPoints[sample], -1.0f, 1.0f, 0.0f, 200.0f);
            p.lineTo(sample, point);
        }
        
        g.strokePath(p, juce::PathStrokeType(1));
        g.setColour(juce::Colours::white);
        g.setFont(15.0f);
        auto textBounds = getLocalBounds().reduced(10, 10);
        g.drawFittedText(fileName, textBounds, juce::Justification::topRight, 1);
        
        auto playHeadPositon = juce::jmap<int>(audioProcessorMine.getSampleCount(),
                                               0,audioProcessorMine.getWaveform().getNumSamples(),
                                               0,getWidth());
        g.setColour(juce::Colours::white);
        g.drawLine(playHeadPositon, 0, playHeadPositon, getHeight(), 0.5f);
        g.setColour(juce::Colours::black.withAlpha(0.2f));
        g.fillRect(0,0,playHeadPositon,getHeight());
    }
    else
    {
        g.setColour(juce::Colours::white);
        g.setFont(40.0f);
        g.drawFittedText("Jala un audio", 250, 50, 200, 40, juce::Justification::centred, 1);
    }
}

void sampler_Waveform::resized()
{

}
