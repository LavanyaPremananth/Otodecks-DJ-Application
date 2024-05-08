/*
  ==============================================================================

    DeckGUI.cpp
    Created: 22 Feb 2023 8:18:42pm
    Author:  lavan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
    /*AudioFormatManager & 	formatManagerToUse,
    AudioThumbnailCache & 	cacheToUse*/
    waveFormDisplay* _waveformDisplay) : player(_player), waveformDisplay(_waveformDisplay) {

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(resumeButton);

    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    volSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    speedSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    volSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 25);
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 25);
    speedSlider.setValue(1.0);
    volSlider.setValue(1.0);

    addAndMakeVisible(volume);
    addAndMakeVisible(position);
    addAndMakeVisible(speed);

    getLookAndFeel().setColour(Slider::thumbColourId, Colour::fromRGB(38, 246, 198));
    getLookAndFeel().setColour(Slider::rotarySliderFillColourId, Colour::fromRGB(178, 102, 255));
    getLookAndFeel().setColour(TextButton::buttonColourId, Colour::fromRGB(38, 246, 198));
    getLookAndFeel().setColour(TextButton::textColourOffId, Colour::fromRGB(0,0,0));
    getLookAndFeel().setColour(Slider::trackColourId, Colour::fromRGB(178, 102, 255));

    volume.setText("volume", juce::dontSendNotification);
    position.setText("Position", juce::dontSendNotification);
    speed.setText("Speed", juce::dontSendNotification);

    volume.setJustificationType(Justification::centredBottom);
    speed.setJustificationType(Justification::centredBottom);

    volume.attachToComponent(&volSlider, false);
    position.attachToComponent(&posSlider, true);
    speed.attachToComponent(&speedSlider, false);


    //addAndMakeVisible(waveFormDisplay);


    playButton.addListener(this);
    stopButton.addListener(this);
    resumeButton.addListener(this);
    //loadButton.addListener(this);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);


    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 10.0);
    posSlider.setRange(0.0, 1.0);

    startTimer(500);


}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint(Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.
       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
    g.fillAll(Colour::fromRGB(0, 0, 0));   // clear the background

    g.setColour(Colour::fromRGB(178, 102, 255));
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(Colours::greenyellow);
    g.setFont(14.0f);
    g.drawText("DECK GUI", getLocalBounds(),
        Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    auto labelposition = 55;//the sapce for the label
    double rowH = getHeight() / 8.0;
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    resumeButton.setBounds(0, rowH * 2, getWidth(), rowH - 10);
    volSlider.setBounds(0, rowH * 2 + 40, getWidth() / 2, rowH * 4);
    speedSlider.setBounds(getWidth() / 2, rowH * 2 + 40, getWidth() / 2, rowH * 4);
    posSlider.setBounds(labelposition, rowH * 7, getWidth() - 10 - labelposition, rowH);

    //waveFormDisplay->setBounds(0, rowH * 5, getWidth(), rowH * 2);
}

void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        playButton.setEnabled(false);
        stopButton.setEnabled(true);
        player->start();
    }
    if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        stopButton.setEnabled(false);
        playButton.setEnabled(true);
        player->stop();

    }
    if (button == &resumeButton) {
        stopButton.setEnabled(true);
        playButton.setEnabled(true);
        player->stop();
        posSlider.setValue(0.0);
        player->resume();
    }

    //if (button == &loadButton)
    //{
    //    FileChooser chooser{"Select a file..."};
    //    if (chooser.browseForFileToOpen())
    //    {
    //        player->loadURL(URL{chooser.getResult()});
    //        waveFormDisplay->loadURL(URL{chooser.getResult()});
    //        
    //    }
    //}
}

void DeckGUI::sliderValueChanged(Slider* slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }

    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }

}

bool DeckGUI::isInterestedInFileDrag(const StringArray& files)
{
    std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
    return true;
}

void DeckGUI::filesDropped(const StringArray& files, int x, int y)
{
    std::cout << "DeckGUI::filesDropped" << std::endl;
    if (files.size() == 1)
    {
        player->loadURL(URL{ File{files[0]} });
        waveformDisplay->loadURL(URL{ File{files[0]} });
    }
}

void DeckGUI::timerCallback()
{
    //std::cout << "DeckGUI::timerCallback" << std::endl;
    waveformDisplay->setPositionRelative(
        player->getPositionRelative());
    if (player->getPositionRelative() >= 0.0 && player->getPositionRelative() <= 1.0) {
        posSlider.setValue(player->getPositionRelative());
    }

}