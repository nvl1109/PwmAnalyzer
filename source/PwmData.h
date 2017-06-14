#ifndef PWM_DATA_H
#define PWM_DATA_H
#pragma once
#include "AnalyzerTypes.h"

#define PWM_FLAG_ABNORMAL  0x00000001
#define PWM_FLAG_MAX       0x00000002
#define PWM_FLAG_MIN       0x00000004
#define PWM_FLAG_PERIOD    0x10000000
#define PWM_FLAG_POS_PULSE 0x20000000
#define PWM_FLAG_NEG_PULSE 0x40000000

class PwmData
{
public:
	PwmData();
	PwmData(double start_time, float period, float pos_pulse, float neg_pulse, U32 flags);
	~PwmData();

	double mTimeStart;
	float mPeriod;
	float mPosPulse;
	float mNegPulse;
	U32 mFlags;
};

#endif
