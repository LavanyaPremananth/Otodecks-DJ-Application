/*
  ==============================================================================

    waveFormDisplay.h
    Created: 22 Feb 2023 8:18:42pm
    Author:  lavan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class waveFormDisplay  : public Component,
                         public ChangeListener
{
public:
    waveFormDisplay( AudioFormatManager& formatManagerToUse,
                     AudioThumbnailCache& cacheToUse);
    ~waveFormDisplay();

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void changeListenerCallback (ChangeBroadcaster* source) override;

    void loadURL(URL audioURL);
    
    // set the relative position of the playhead
    void setPositionRelative(double pos);

private:
    AudioThumbnail audioThumb; 
    bool fileLoaded;
    double position;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (waveFormDisplay)
};
