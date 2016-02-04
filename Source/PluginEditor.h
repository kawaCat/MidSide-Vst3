
//=============================================================================
#ifndef INCLUDE_PLUGINEDITOR_MjAxNjAy54Gr5puc5pelMDcxNTUz
#define INCLUDE_PLUGINEDITOR_MjAxNjAy54Gr5puc5pelMDcxNTUz
//=============================================================================
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//=============================================================================

//window define
//=============================================================================
#define WINDOW_HEGIHT 300
#define WINDOW_WIDTH 600


// button Text 
//=============================================================================
#define UPDATE_TIMER_TIME_MS (1000/10) // 10 fps  
//=============================================================================
#define BUTTON_TEXT_MID_MODE    " MID "
#define BUTTON_TEXT_SIDE_MODE   " SIDE "
#define BUTTON_TEXT_DOUBLE_MODE "DOUBLE" 
#define BUTTON_TEXT_NORMAL_MODE "NORMAL"
//=============================================================================
#define COLOR_MIDE_MODE_Back  Colours::green
#define COLOR_SIDE_MODE_Back  Colours::orange
#define COLOR_MIDE_MODE_TEXT  Colours::white
#define COLOR_SIDE_MODE_TEXT  Colours::white
//=============================================================================
#define COLOR_NORMAL_LEVEL_MODE_Back  Colours::white
#define COLOR_DOUBLE_LEVEL_MODE_Back  Colours::brown
#define COLOR_NORMAL_LEVEL_MODE_TEXT  Colours::black
#define COLOR_DOUBLE_LEVEL_MODE__TEXT Colours::white
//=============================================================================

//=============================================================================
class KawaMidSideAudioProcessorEditor  : public AudioProcessorEditor
                                       , public ButtonListener
                                       , public Timer
{
public:
    //=========================================================================
    KawaMidSideAudioProcessorEditor (KawaMidSideAudioProcessor&);
    ~KawaMidSideAudioProcessorEditor();

    //=========================================================================
    void paint (Graphics&) override;
    void resized() override;
    //=========================================================================
    virtual void buttonClicked( Button* ) override;
    void syncTextButton() { _syncTextButtonName(); };
    virtual void timerCallback() override;

private:

    void _syncTextButtonName();
    void _changeColor( TextButton* bt, Colour newColor, Colour newTextColor );

    //=========================================================================
    class LNF_TextButton :public LookAndFeel_V3
    {
    private:
        Font m_textButtonFont;
    public :
        LNF_TextButton();
        virtual Font getTextButtonFont( TextButton&, int buttonHeight ) override;
        //=====================================================================
    };

    //=========================================================================
    LNF_TextButton lnf;
    ScopedPointer<TextButton> m_MidSideSwitch;
    ScopedPointer<TextButton> m_DoubleLevelSwitch;
    KawaMidSideAudioProcessor& processor;
    //=========================================================================

    //=========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KawaMidSideAudioProcessorEditor)
};
//=============================================================================
#endif // INCLUDE_PLUGINEDITOR_MjAxNjAy54Gr5puc5pelMDcxNTUz 
//=============================================================================
