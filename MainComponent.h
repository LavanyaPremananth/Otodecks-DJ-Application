#pragma once

#include <JuceHeader.h>
#include "DJAudioPLayer.h"
#include "DeckGUI.h"
#include "playlistComponent.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public AudioAppComponent
    /*public Button::Listener,
    public Slider::Listener*/
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

    //// implement Button::Listener
    //void buttonClicked(Button*) override;

    ////Implement Slider::Listener
    //void sliderValueChanged(Slider* slider) override;

private:
    //==============================================================================
    // Your private member variables go here...

    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{100};

    DJAudioPlayer player1{formatManager};
    DeckGUI deckGUI1{ &player1, &waveFormDisplay1};

    DJAudioPlayer player2{ formatManager };
    DeckGUI deckGUI2{ &player2, &waveFormDisplay2 };

    MixerAudioSource mixerSource; 

    waveFormDisplay waveFormDisplay1{ formatManager, thumbCache };
    waveFormDisplay waveFormDisplay2{ formatManager, thumbCache };

    playlistComponent playlistComponent{ &player1, &player2, formatManager, &waveFormDisplay1, &waveFormDisplay2 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
