//=============================================================================
#ifndef INCLUDE_PLUGINPROCESSOR_MjAxNjAy54Gr5puc5pelMDY0NTQw
#define INCLUDE_PLUGINPROCESSOR_MjAxNjAy54Gr5puc5pelMDY0NTQw
//=============================================================================
#include "../JuceLibraryCode/JuceHeader.h"
//=============================================================================

//=============================================================================
class KawaMidSideAudioProcessor  : public AudioProcessor
{
public:
    //=========================================================================
    KawaMidSideAudioProcessor();
    ~KawaMidSideAudioProcessor();

    //=========================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //=========================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //=========================================================================
    const String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //=========================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //=========================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //=========================================================================
    bool isMidMode() const { return _m_isMidMode; }
    void setMidMode( bool val ) { _m_isMidMode = val; }
    void toggleMidMode() { _m_isMidMode = (isMidMode() == false); }
    //=========================================================================
    bool isDoubleLevelMode() const { return _m_isDoubleLevel; }
    void setDoubleLevelMode( bool val ) { _m_isDoubleLevel = val; }
    void toggleDoubleLevelMode() { _m_isDoubleLevel = (isDoubleLevelMode() == false); }

private:
    //=========================================================================
    void _processMid ( AudioSampleBuffer& buffer );
    void _processSide( AudioSampleBuffer& buffer );
    //=========================================================================
    bool _m_isMidMode;
    bool _m_isDoubleLevel;
    //=========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KawaMidSideAudioProcessor)
    //=========================================================================
};
//=============================================================================
#endif // INCLUDE_PLUGINPROCESSOR_MjAxNjAy54Gr5puc5pelMDY0NTQw 
//=============================================================================
