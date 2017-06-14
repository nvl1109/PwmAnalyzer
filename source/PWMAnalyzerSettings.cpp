#include "PWMAnalyzerSettings.h"
#include <AnalyzerHelpers.h>


PWMAnalyzerSettings::PWMAnalyzerSettings()
:	mInputChannel( UNDEFINED_CHANNEL ),
	mPolarity( 0 )
{
	mInputChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
	mInputChannelInterface->SetTitleAndTooltip( "Serial", "Standard PWM Analyzer" );
	mInputChannelInterface->SetChannel( mInputChannel );

	mPolarityInterface.reset( new AnalyzerSettingInterfaceNumberList() );
	mPolarityInterface->SetTitleAndTooltip( "Polarity",  "Specify the PWM polarity." );
	mPolarityInterface->AddNumber(0, "High", "PWM high porality");
	mPolarityInterface->AddNumber(1, "Low", "PWM low porality");

	AddInterface( mInputChannelInterface.get() );
	AddInterface( mPolarityInterface.get() );

	AddExportOption( 0, "Export as text/csv file" );
	AddExportExtension( 0, "text", "txt" );
	AddExportExtension( 0, "csv", "csv" );

	ClearChannels();
	AddChannel( mInputChannel, "PWM", false );
}

PWMAnalyzerSettings::~PWMAnalyzerSettings()
{
}

bool PWMAnalyzerSettings::SetSettingsFromInterfaces()
{
	mInputChannel = mInputChannelInterface->GetChannel();
	mPolarity = mPolarityInterface->GetNumber();

	ClearChannels();
	AddChannel( mInputChannel, "PWM Analyzer", true );

	return true;
}

void PWMAnalyzerSettings::UpdateInterfacesFromSettings()
{
	mInputChannelInterface->SetChannel( mInputChannel );
	mPolarityInterface->SetNumber( mPolarity );
}

void PWMAnalyzerSettings::LoadSettings( const char* settings )
{
	SimpleArchive text_archive;
	text_archive.SetString( settings );

	text_archive >> mInputChannel;
	text_archive >> mPolarity;

	ClearChannels();
	AddChannel( mInputChannel, "PWM Analyzer", true );

	UpdateInterfacesFromSettings();
}

const char* PWMAnalyzerSettings::SaveSettings()
{
	SimpleArchive text_archive;

	text_archive << mInputChannel;
	text_archive << mPolarity;

	return SetReturnString( text_archive.GetString() );
}
