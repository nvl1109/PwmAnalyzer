#ifndef PWM_ANALYZER_SETTINGS
#define PWM_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

#define PWM_POR_HIGH 0
#define PWM_POR_LOW  1

class PWMAnalyzerSettings : public AnalyzerSettings
{
public:
	PWMAnalyzerSettings();
	virtual ~PWMAnalyzerSettings();

	virtual bool SetSettingsFromInterfaces();
	void UpdateInterfacesFromSettings();
	virtual void LoadSettings( const char* settings );
	virtual const char* SaveSettings();

	
	Channel mInputChannel;
	double mPolarity;

protected:
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mInputChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceNumberList >	mPolarityInterface;
};

#endif //PWM_ANALYZER_SETTINGS
