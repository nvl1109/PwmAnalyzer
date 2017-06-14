#include "PwmData.h"



PwmData::PwmData()
:	mTimeStart(0),
	mFlags(0),
	mPeriod(0),
	mPosPulse(0),
	mNegPulse(0)
{
}


PwmData::PwmData(double start_time, float period, float pos_pulse, float neg_pulse, U32 flags)
	: mTimeStart(start_time),
	mFlags(flags),
	mPeriod(period),
	mPosPulse(pos_pulse),
	mNegPulse(neg_pulse)
{
}


PwmData::~PwmData()
{
}
