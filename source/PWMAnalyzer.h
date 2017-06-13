#ifndef PWM_ANALYZER_H
#define PWM_ANALYZER_H

#include <Analyzer.h>
#include "PWMAnalyzerResults.h"
#include "PWMSimulationDataGenerator.h"

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
	AnalyzerChannelData* mSerial;

	PWMSimulationDataGenerator mSimulationDataGenerator;
	bool mSimulationInitilized;

	//Serial analysis vars:
	U32 mSampleRateHz;
	U32 mStartOfStopBitOffset;
	U32 mEndOfStopBitOffset;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //PWM_ANALYZER_H
