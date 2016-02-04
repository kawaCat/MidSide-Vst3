
//=============================================================================
#include "PluginProcessor.h"
#include "PluginEditor.h"
//=============================================================================

//=============================================================================
KawaMidSideAudioProcessor::KawaMidSideAudioProcessor()
    :_m_isMidMode(true)
    ,_m_isDoubleLevel(false)
{
}
//=============================================================================
KawaMidSideAudioProcessor::~KawaMidSideAudioProcessor()
{
}
//=============================================================================
const String KawaMidSideAudioProcessor::getName() const
{
    return JucePlugin_Name;
}
//=============================================================================
bool KawaMidSideAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}
//=============================================================================
bool KawaMidSideAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}
//=============================================================================
bool KawaMidSideAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}
//=============================================================================
double KawaMidSideAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}
//=============================================================================
int KawaMidSideAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}
//=============================================================================
int KawaMidSideAudioProcessor::getCurrentProgram()
{
    return 0;
}
//=============================================================================
void KawaMidSideAudioProcessor::setCurrentProgram (int index)
{
}
//=============================================================================
const String KawaMidSideAudioProcessor::getProgramName (int index)
{
    return String();
}
//=============================================================================
void KawaMidSideAudioProcessor::changeProgramName (int index, const String& newName)
{
}
//=============================================================================
void KawaMidSideAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}
//=============================================================================
void KawaMidSideAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}
//=============================================================================
void KawaMidSideAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    //=========================================================================
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    //=========================================================================
    if ( getNumInputChannels() == 2 )
    {
        if ( isMidMode() )
            _processMid ( buffer );
        else
            _processSide( buffer );
    }
    //=========================================================================
}
//=============================================================================
bool KawaMidSideAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}
//=============================================================================
AudioProcessorEditor* KawaMidSideAudioProcessor::createEditor()
{
    return new KawaMidSideAudioProcessorEditor (*this);
}
//=============================================================================
void KawaMidSideAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    //=========================================================================
    XmlElement xml( "kawaMidSide_Parameter" );
    //=========================================================================
    xml.setAttribute( "isMidMode", isMidMode() );
    xml.setAttribute( "isDoubleLevelMode", isDoubleLevelMode() );
    //=========================================================================
    copyXmlToBinary (xml, destData);
    //=========================================================================
}
//=============================================================================
void KawaMidSideAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState( getXmlFromBinary (data, sizeInBytes) );
    //=========================================================================
    if ( xmlState != nullptr )
    {
        if ( xmlState->hasTagName( "kawaMidSide_Parameter" ) )
        {
            bool isMideMode_ = xmlState->getBoolAttribute( "isMidMode", false );
            bool isDoubleMode_ = xmlState->getBoolAttribute( "isDoubleLevelMode", false );
            //=================================================================
            setDoubleLevelMode( isDoubleMode_ );
            setMidMode( isMideMode_ );
            //=================================================================
        }
    }
    //=========================================================================
}
//=============================================================================
void KawaMidSideAudioProcessor::_processMid( AudioSampleBuffer& buffer )
{
    const float* inL = buffer.getReadPointer( 0 );//L 
    const float* inR = buffer.getReadPointer( 1 );//R
    float* outL = buffer.getWritePointer( 0 );
    float* outR = buffer.getWritePointer( 1 );
    int blockSize = buffer.getNumSamples();
    //=========================================================================
    float offsetLevel = 1.0f;
    //=========================================================================
    if ( isDoubleLevelMode() )
        offsetLevel = 2.0f;
    //=========================================================================
    for ( int i = 0; i < blockSize; i++ )
    {
        float mid = (inL[i] +inR[i] )/2;
        outL[i] = mid*offsetLevel;
        outR[i] = mid*offsetLevel;
    }
    //=========================================================================
}
//=============================================================================
void KawaMidSideAudioProcessor::_processSide( AudioSampleBuffer& buffer )
{
    const float* inL = buffer.getReadPointer( 0 );//L 
    const float* inR = buffer.getReadPointer( 1 );//R
    float* outL = buffer.getWritePointer( 0 );
    float* outR = buffer.getWritePointer( 1 );
    int blockSize = buffer.getNumSamples();
    //=========================================================================
    float offsetLevel = 1.0f;
    //=========================================================================
    if ( isDoubleLevelMode() )
        offsetLevel = 2.0f;
    //=========================================================================
    for ( int i = 0; i < blockSize; i++ )
    {
        float mid = (inL[i] + inR[i]) / 2.0f;
        float sideL = inL[i] - mid;
        float sideR = inR[i] - mid;
        outL[i] = sideL*offsetLevel;
        outR[i] = sideR*offsetLevel;
    }
    //=========================================================================
}
//=============================================================================
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KawaMidSideAudioProcessor();
}
//=============================================================================