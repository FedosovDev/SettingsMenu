// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/SettingsWidgets/SettingsAudio.h"
#include "Components/VerticalBox.h"
#include "Components/ScrollBox.h"
#include "SettingsMenu/UI/Elements/SettingsSlider.h"
#include "Components/Spacer.h"
#include "SettingsMenu/UI/Elements/BaseButton.h"

void USettingsAudio::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void USettingsAudio::NativeConstruct()
{
	Super::NativeConstruct();
	SetupUIHierarchy();
	BindEvents();
	UCustomGameUserSettings* CustomSettings = UCustomGameUserSettings::GetCustomGameUserSettings();
	SetMasterVolumeDefaultValue(CustomSettings);
	SetMusicVolumeDefaultValue(CustomSettings);
	SetSFXVolumeDefaultValue(CustomSettings);
	SetUIVolumeDefaultValue(CustomSettings);
}

void USettingsAudio::SetupUIHierarchy()
{
	if (GeneralVerticalBox)
	{
		GeneralVerticalBox->AddChild(GeneralScrollBox);
		GeneralVerticalBox->AddChild(ApplySettingsButton);
	}
	if (GeneralScrollBox)
	{
		GeneralScrollBox->AddChild(OptionsVerticalBox);
	}
	if (OptionsVerticalBox)
	{
		OptionsVerticalBox->AddChild(MasterVolumeSlider);
		OptionsVerticalBox->AddChild(MasterVolumeSpacer);
		OptionsVerticalBox->AddChild(MusicVolumeSlider);
		OptionsVerticalBox->AddChild(MusicVolumeSpacer);
		OptionsVerticalBox->AddChild(SFXVolumeSlider);
		OptionsVerticalBox->AddChild(SFXVolumeSpacer);
		OptionsVerticalBox->AddChild(UIVolumeSlider);
		OptionsVerticalBox->AddChild(UIVolumeSpacer);
	}
}

void USettingsAudio::BindEvents()
{
	if (MasterVolumeSlider)
	{
		MasterVolumeSlider->OnSliderValueChangedDelegate.AddDynamic(this, &USettingsAudio::OnMasterVolumeValueChanged);
	}
	if (MusicVolumeSlider)
	{
		MusicVolumeSlider->OnSliderValueChangedDelegate.AddDynamic(this, &USettingsAudio::OnMusicVolumeValueChanged);
	}
	if (SFXVolumeSlider)
	{
		SFXVolumeSlider->OnSliderValueChangedDelegate.AddDynamic(this, &USettingsAudio::OnSFXVolumeValueChanged);
	}
	if (UIVolumeSlider)
	{
		UIVolumeSlider->OnSliderValueChangedDelegate.AddDynamic(this, &USettingsAudio::OnUIVolumeValueChanged);
	}
}

void USettingsAudio::SetMasterVolumeDefaultValue(UCustomGameUserSettings* Settings)
{
	if (Settings)
	{
		float SettingsMasterVolume = Settings->GetMasterVolume();
		MasterVolumeValue = SettingsMasterVolume;
		MasterVolumeSlider->SetSliderValue(SettingsMasterVolume);
	}
}

void USettingsAudio::SetMusicVolumeDefaultValue(UCustomGameUserSettings* Settings)
{
	if (Settings)
	{
		float SettingsMusicVolume = Settings->GetMusicVolume();
		MusicVolumeValue = SettingsMusicVolume;
		MusicVolumeSlider->SetSliderValue(SettingsMusicVolume);
	}
}

void USettingsAudio::SetSFXVolumeDefaultValue(UCustomGameUserSettings* Settings)
{
	if (Settings)
	{
		float SettingsSFXVolume = Settings->GetSFXVolume();
		SFXVolumeValue = SettingsSFXVolume;
		SFXVolumeSlider->SetSliderValue(SettingsSFXVolume);
	}
}

void USettingsAudio::SetUIVolumeDefaultValue(UCustomGameUserSettings* Settings)
{
	if (Settings)
	{
		float SettingsUIVolume = Settings->GetUIVolume();
		UIVolumeValue = SettingsUIVolume;
		UIVolumeSlider->SetSliderValue(SettingsUIVolume);
	}
}

void USettingsAudio::OnMasterVolumeValueChanged(float NewValue)
{
	MasterVolumeValue = NewValue;
}

void USettingsAudio::OnMusicVolumeValueChanged(float NewValue)
{
	MusicVolumeValue = NewValue;
}

void USettingsAudio::OnSFXVolumeValueChanged(float NewValue)
{
	SFXVolumeValue = NewValue;
}

void USettingsAudio::OnUIVolumeValueChanged(float NewValue)
{
	UIVolumeValue = NewValue;
}


