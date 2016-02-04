
//=============================================================================
#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================
KawaMidSideAudioProcessorEditor::KawaMidSideAudioProcessorEditor (KawaMidSideAudioProcessor& p)
: AudioProcessorEditor (&p)
, processor (p)
{
    m_DoubleLevelSwitch = new TextButton( BUTTON_TEXT_NORMAL_MODE );
    m_MidSideSwitch = new TextButton( BUTTON_TEXT_MID_MODE );
    //=========================================================================
    m_MidSideSwitch->setLookAndFeel( &lnf );
    m_DoubleLevelSwitch->setLookAndFeel( &lnf );
    //=========================================================================
    m_MidSideSwitch->setConnectedEdges( TextButton::ConnectedOnLeft 
                                      | TextButton::ConnectedOnRight );
    m_DoubleLevelSwitch->setConnectedEdges( TextButton::ConnectedOnLeft 
                                          | TextButton::ConnectedOnRight );
    //=========================================================================
    addAndMakeVisible( m_MidSideSwitch );
    addAndMakeVisible( m_DoubleLevelSwitch );
    //=========================================================================
    m_DoubleLevelSwitch->addListener( this );
    m_MidSideSwitch->addListener( this );
    //=========================================================================
    setSize (WINDOW_WIDTH, WINDOW_HEGIHT);
    //=========================================================================
    _syncTextButtonName();
    //=========================================================================
    startTimer( UPDATE_TIMER_TIME_MS );
}
//=============================================================================
KawaMidSideAudioProcessorEditor::~KawaMidSideAudioProcessorEditor()
{
    if ( isTimerRunning() )
        stopTimer();
    //=========================================================================
}
//=============================================================================
void KawaMidSideAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}
//=============================================================================
void KawaMidSideAudioProcessorEditor::resized()
{
    auto rect = getLocalBounds();
    int reduce = 0;
    //=========================================================================
    auto oneButtonRect = rect.removeFromTop( rect.getHeight() / 2 );
    m_MidSideSwitch->setBounds( oneButtonRect.reduced( reduce ) );
    //=========================================================================
    oneButtonRect.translate( 0, oneButtonRect.getHeight()-reduce /2 );
    m_DoubleLevelSwitch->setBounds( oneButtonRect.reduced( reduce ) );
    //=========================================================================
}
//=============================================================================
void KawaMidSideAudioProcessorEditor::buttonClicked( Button* bt )
{
    if ( bt == m_MidSideSwitch )
    {
        processor.toggleMidMode();
        //=====================================================================
        m_MidSideSwitch->setToggleState( processor.isMidMode()
                                       , NotificationType::dontSendNotification );
    }
    else if ( bt == m_DoubleLevelSwitch )
    {
        processor.toggleDoubleLevelMode();
        //=====================================================================
        m_DoubleLevelSwitch->setToggleState( processor.isDoubleLevelMode()
                                           , NotificationType::dontSendNotification);
    }
    //=========================================================================
    _syncTextButtonName();
}
//=============================================================================
void KawaMidSideAudioProcessorEditor::_syncTextButtonName()
{
    if ( processor.isMidMode() )
    {
        m_MidSideSwitch->setButtonText( BUTTON_TEXT_MID_MODE );
        _changeColor( m_MidSideSwitch, COLOR_MIDE_MODE_Back, COLOR_MIDE_MODE_TEXT );
    }
    else
    {
        m_MidSideSwitch->setButtonText( BUTTON_TEXT_SIDE_MODE );
        _changeColor( m_MidSideSwitch, COLOR_SIDE_MODE_Back, COLOR_SIDE_MODE_TEXT );
    }
    //=========================================================================
    if ( processor.isDoubleLevelMode() )
    {
        m_DoubleLevelSwitch->setButtonText( BUTTON_TEXT_DOUBLE_MODE);
        _changeColor( m_DoubleLevelSwitch, COLOR_DOUBLE_LEVEL_MODE_Back, COLOR_DOUBLE_LEVEL_MODE__TEXT );
    }
    else
    {
        m_DoubleLevelSwitch->setButtonText( BUTTON_TEXT_NORMAL_MODE );
        _changeColor( m_DoubleLevelSwitch, COLOR_NORMAL_LEVEL_MODE_Back, COLOR_NORMAL_LEVEL_MODE_TEXT );
    };
    //=========================================================================
}
//=============================================================================
void KawaMidSideAudioProcessorEditor::_changeColor( TextButton* bt, Colour newColor, Colour newTextColor )
{
    bt->setColour( TextButton::ColourIds::buttonColourId, newColor );
    bt->setColour( TextButton::ColourIds::buttonOnColourId, newColor );
    //=========================================================================
    bt->setColour( TextButton::ColourIds::textColourOffId , newTextColor );
    bt->setColour( TextButton::ColourIds::textColourOnId , newTextColor );
}
//=============================================================================
void KawaMidSideAudioProcessorEditor::timerCallback()
{
    syncTextButton();
}
//=============================================================================

//=============================================================================
KawaMidSideAudioProcessorEditor::LNF_TextButton::LNF_TextButton()
{
    m_textButtonFont.setTypefaceName("arial");
}
//=============================================================================
Font KawaMidSideAudioProcessorEditor::LNF_TextButton::getTextButtonFont( TextButton&, int buttonHeight )
{
    m_textButtonFont.setHeight(buttonHeight);
    m_textButtonFont.setBold(true);
    return m_textButtonFont;
}
//=============================================================================
