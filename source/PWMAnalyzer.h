#ifndef PWM_ANALYZER_H
#define PWM_ANALYZER_H

#include <Analyzer.h>
#include "PWMAnalyzerResults.h"
#include "PWMSimulationDataGenerator.h"
#include "PwmData.h"

class PWMAnalyzerSettings;
class ANALYZER_EXPORT PWMAnalyzer : public Analyzer2
{
public:
	PWMAnalyzer();
	virtual ~PWMAnalyzer();

	virtual void SetupResults();
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	virtual U32 GetMinimumSampleRateHz();

	virtual const char* GetAnalyzerName() const;
	virtual bool NeedsRerun();

protected: //vars
	std::auto_ptr< PWMAnalyzerSettings > mSettings;
	std::auto_ptr< PWMAnalyzerResults > mResults;
	AnalyzerChannelData* mPwm;

	PWMSimulationDataGenerator mSimulationDataGenerator;
	bool mSimulationInitilized;

	//Serial analysis vars:
	float mMinPositivePulse;
	float mMaxPositivePulse;
	float mMinNegativePulse;
	float mMaxNegativePulse;
	float mMinPeriod;
	float mMaxPeriod;
	float mAvgPeriod;
	float mMinFreq;
	float mMaxFreq;
	float mAvgFreq;

	std::vector<PwmData> mPwmData;

	void processData();
	void calculateResult();

private:
	bool mIsEdgeFound;
	bool mIsCalculationDone;
	U64 mPrevSampleNumber;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //PWM_ANALYZER_H
