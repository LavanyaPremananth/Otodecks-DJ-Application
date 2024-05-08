/*
  ==============================================================================

    waveFormDisplay.cpp
    Created: 22 Feb 2023 8:18:42pm
    Author:  lavan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "waveFormDisplay.h"

//==============================================================================
waveFormDisplay::waveFormDisplay(AudioFormatManager& formatManagerToUse,
                                 AudioThumbnailCache& cacheToUse) :
                                 audioThumb(1000, formatManagerToUse, cacheToUse),
                                 fileLoaded(false),
                                 position(0)

{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    audioThumb.addChangeListener(this);

}

waveFormDisplay::~waveFormDisplay()
{

}

void waveFormDisplay::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    g.fillAll(Colour::fromRGB(0,0,0));

    g.setColour(Colour::fromRGB(178, 102, 255));
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::greenyellow);
    if (fileLoaded)
    {
        audioThumb.drawChannel(g, 
            getLocalBounds(),
            0, 
            audioThumb.getTotalLength(),
            0,
            1.0f
        );
        g.setColour(Colour::fromRGB(178, 102, 255));
        g.drawRect(position * getWidth(), 0, getWidth() / 20, getHeight());
    }
    else
    {
        g.setFont(14.0f);
        g.drawText("File not loaded...", getLocalBounds(),
            juce::Justification::centred, true);   // draw some placeholder text
    }
    
}

void waveFormDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void waveFormDisplay::loadURL(URL audioURL)
{
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new URLInputSource(audioURL));
    if (fileLoaded)
    {
        std::cout << "wfd: loaded!" << std::endl;
        repaint();
    }
    else {
        std::cout << "wfd: not loaded!" << std::endl;
    }
}

void waveFormDisplay::changeListenerCallback(ChangeBroadcaster* source)
{
    std::cout << "wfd: change received!" << std::endl;
    repaint();
}

void waveFormDisplay::setPositionRelative(double pos)
{
    if (pos != position)
    {
        position = pos;
        repaint();
    }
}