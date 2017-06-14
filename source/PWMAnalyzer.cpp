#include "PWMAnalyzer.h"
#include "PWMAnalyzerSettings.h"
#include <AnalyzerChannelData.h>

PWMAnalyzer::PWMAnalyzer()
:	Analyzer2(),  
	mSettings( new PWMAnalyzerSettings() ),
	mSimulationInitilized( false ),
	mMinPositivePulse(0),
	mMaxPositivePulse(0),
	mMinNegativePulse(0),
	mMaxNegativePulse(0),
	mMinPeriod(0),
	mMaxPeriod(0),
	mAvgPeriod(0),
	mMinFreq(0),
	mMaxFreq(0),
	mAvgFreq(0),
	mIsCalculationDone(false),
	mIsEdgeFound(false)
{
	SetAnalyzerSettings( mSettings.get() );
}

PWMAnalyzer::~PWMAnalyzer()
{
	KillThread();
}

void PWMAnalyzer::SetupResults()
{
	mResults.reset( new PWMAnalyzerResults( this, mSettings.get() ) );
	SetAnalyzerResults( mResults.get() );
	mResults->AddChannelBubblesWillAppearOn( mSettings->mInputChannel );
}

void PWMAnalyzer::WorkerThread()
{
	U64 tmp;

	mPwm = GetAnalyzerChannelData( mSettings->mInputChannel );

	for (;;) {
		mPwm->AdvanceToNextEdge();

		// rising edge
		if (mPwm->GetBitState() == BIT_HIGH) {
			if (!mIsEdgeFound) {
				mIsEdgeFound = true;
				mPrevSampleNumber = mPwm->GetSampleNumber();
				continue;
			}

			tmp = mPwm->GetSampleNumber();
			Frame frame;
			frame.mStartingSampleInclusive = mPrevSampleNumber;
			frame.mEndingSampleInclusive = tmp;
			frame.mData1 = 'L';
			frame.mFlags = DISPLAY_AS_WARNING_FLAG;
			mResults->AddFrame(frame);


			mPrevSampleNumber = tmp;
			mResults->CommitResults();
		}

		ReportProgress(mPwm->GetSampleNumber());
		CheckIfThreadShouldExit();
	}

}

void PWMAnalyzer::processData() {
	int polarity = mSettings->mPolarity;
	U32 tmp;

	if (!mIsEdgeFound) {
		// Find the first edge
		do {
			CheckIfThreadShouldExit();
			mPwm->AdvanceToNextEdge();
			if (mPwm->GetBitState() == BIT_HIGH) {
				// edge found
				mIsEdgeFound = true;
				mPrevSampleNumber = mPwm->GetSampleNumber();
				//mResults->AddMarker(mPrevSampleNumber, AnalyzerResults::Square, mSettings->mInputChannel);
			}
			ReportProgress(mPwm->GetSampleNumber());
		} while (!mIsEdgeFound); 
	} else {
		bool isNext = false;
		// find next period
		mPwm->AdvanceToNextEdge();
		tmp = mPwm->GetSampleNumber();

		if (mPwm->GetBitState() == BIT_HIGH) {
			mResults->AddMarker(tmp, AnalyzerResults::ErrorSquare, mSettings->mInputChannel);
			Frame frame;
			frame.mStartingSampleInclusive = mPrevSampleNumber;
			frame.mEndingSampleInclusive = tmp;
			frame.mData1 = 'L';
			frame.mFlags = DISPLAY_AS_WARNING_FLAG;
			mResults->AddFrame(frame);
			mResults->AddResultString("T");
			mPrevSampleNumber = tmp;
		}
		
		mResults->CommitResults();
	}
	ReportProgress(mPwm->GetSampleNumber());
}

void PWMAnalyzer::calculateResult() {

}

bool PWMAnalyzer::NeedsRerun()
{
	return false;
}

U32 PWMAnalyzer::GenerateSimulationData( U64 minimum_sample_index, U32 device_sample_rate, SimulationChannelDescriptor** simulation_channels )
{
	if( mSimulationInitilized == false )
	{
		mSimulationDataGenerator.Initialize( GetSimulationSampleRate(), mSettings.get() );
		mSimulationInitilized = true;
	}

	return mSimulationDataGenerator.GenerateSimulationData( minimum_sample_index, device_sample_rate, simulation_channels );
}

U32 PWMAnalyzer::GetMinimumSampleRateHz()
{
	return 0;
}

const char* PWMAnalyzer::GetAnalyzerName() const
{
	return "PWM Analyzer";
}

const char* GetAnalyzerName()
{
	return "PWM Analyzer";
}

Analyzer* CreateAnalyzer()
{
	return new PWMAnalyzer();
}

void DestroyAnalyzer( Analyzer* analyzer )
{
	delete analyzer;
}