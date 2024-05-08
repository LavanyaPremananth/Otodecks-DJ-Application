/*
  ==============================================================================

    DeckGUI.h
    Created: 22 Feb 2023 8:18:42pm
    Author:  lavan

  ==============================================================================
*/
#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "waveFormDisplay.h"

//==============================================================================
/*
*/
class DeckGUI : public Component,
    public Button::Listener,
    public Slider::Listener,
    public FileDragAndDropTarget,
    public Timer
{
public:
    DeckGUI(DJAudioPlayer* player,
        /*AudioFormatManager &formatManagerToUse,
        AudioThumbnailCache &cacheToUse*/
        waveFormDisplay* waveformDisplay);
    ~DeckGUI();

    void paint(Graphics&) override;
    void resized() override;

    /** implement Button::Listener */
    void buttonClicked(Button*) override;

    /** implement Slider::Listener */
    void sliderValueChanged(Slider* slider) override;

    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;

    void timerCallback() override;

private:

    TextButton playButton{ "PLAY" };
    TextButton stopButton{ "STOP" };
    TextButton resumeButton{ "RESUME" };

    Slider volSlider;
    juce::Label volume;
    Slider speedSlider;
    juce::Label speed;
    Slider posSlider;
    juce::Label position;


    waveFormDisplay* waveformDisplay;
    DJAudioPlayer* player;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};