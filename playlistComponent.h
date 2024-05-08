/*
  ==============================================================================

    playlistComponent.h
    Created: 13 Mar 2023 9:52:21am
    Author:  lavan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
//#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "waveFormDisplay.h"
#include <fstream>
//==============================================================================
/*
*/
class playlistComponent  : public juce::Component,
    public TableListBoxModel,
    public Button::Listener,
    public FileDragAndDropTarget
{
public:
    playlistComponent(DJAudioPlayer* _player1, DJAudioPlayer* _player2,
        AudioFormatManager& formatManagerToUse,
        waveFormDisplay* _waveFormDisplay1, waveFormDisplay* _waveFormDisplay2);
    ~playlistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    int getNumRows() override;
    void paintRowBackground(Graphics&, int rowNumber,
        int width, int height, bool rowIsSelected) override;

    void paintCell(Graphics&, int rowNumber,
        int columnId, int width, int height,
        bool rowIsSelected) override;

    Component* refreshComponentForCell(int rowNumber,
        int columnId, bool isRowSelected,
        Component* existingComponentToUpdate) override;

    void buttonClicked(Button* button) override;

    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;
    void loadURL(URL audioURL);
    std::vector<std::string> tokenise(std::string Line, char separator);
    void loading();
private:
    juce::TableListBox tableComponent;
    juce::TextEditor searchingTextBox;

    std::vector<juce::String> trackTitlesNames;//file's name
    std::vector<URL> trackTitles;//the files' URL
    std::vector<int> trackLengths;

    TextButton saveButton{ "Save List" };
    TextButton loadButton{ "Read List" };

    juce::String urljuce;
    std::string urlstd;
    std::string filenamestd;
    std::ofstream playlistSave;

    DJAudioPlayer* player1;
    DJAudioPlayer* player2;
    waveFormDisplay* waveFormDisplay1;
    waveFormDisplay* waveFormDisplay2;
    //AudioTransportSource transportSource;
    //AudioFormatManager formatManagerToUse;
    //std::unique_ptr<juce::AudioFormatReaderSource> readerSource;

    SafePointer<DialogWindow> dialogWindow;

    void searching(String inputtext);
    void illustration();


private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (playlistComponent)
};
