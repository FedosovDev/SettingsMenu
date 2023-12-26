// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/SettingsWidgets/Settings.h"
#include "Components/Overlay.h"
#include "Components/Border.h"
#include "Components/BackgroundBlur.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "SettingsMenu/UI/Elements/BaseButton.h"
#include "Components/WidgetSwitcher.h"
#include "SettingsMenu/UI/SettingsWidgets/SettingsDisplay.h"
#include "SettingsMenu/UI/SettingsWidgets/SettingsGraphics.h"
#include "SettingsMenu/UI/SettingsWidgets/SettingsControls.h"
#include "SettingsMenu/UI/SettingsWidgets/SettingsAudio.h"

USettings::USettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void USettings::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void USettings::NativeConstruct()
{
	Super::NativeConstruct();
	SetupUIHierarchy();
	BindEvents();
}

void USettings::SetupUIHierarchy()
{
	if (GeneralOverlay)
	{
		GeneralOverlay->AddChild(BackgroundBackgroundBlur);
		GeneralOverlay->AddChild(BackgroundBorder);
	}
	if (OptionsVerticalBox)
	{
		OptionsVerticalBox->AddChild(SettingsButtonsBox);
		OptionsVerticalBox->AddChild(SettingsSwitcher);
		OptionsVerticalBox->AddChild(BackButton);
	}
	if (SettingsButtonsBox)
	{
		SettingsButtonsBox->AddChild(DisplayButton);
		SettingsButtonsBox->AddChild(GraphicsButton);
		SettingsButtonsBox->AddChild(ControlsButton);
		SettingsButtonsBox->AddChild(AudioButton);
	}
	if (SettingsSwitcher)
	{
		SettingsSwitcher->AddChild(DisplaySettings);
		SettingsSwitcher->AddChild(GraphicsSettings);
		SettingsSwitcher->AddChild(ControlsSettings);
		SettingsSwitcher->AddChild(AudioSettings);
	}
}

void USettings::BindEvents()
{
	if (DisplayButton)
	{
		DisplayButton->OnButtonClickedDelegate.AddDynamic(this, &USettings::OnDisplayButtonClicked);
	}
	if (GraphicsButton)
	{
		GraphicsButton->OnButtonClickedDelegate.AddDynamic(this, &USettings::OnGraphicsButtonClicked);
	}
	if (ControlsButton)
	{
		ControlsButton->OnButtonClickedDelegate.AddDynamic(this, &USettings::OnControlsButtonClicked);
	}
	if (AudioButton)
	{
		AudioButton->OnButtonClickedDelegate.AddDynamic(this, &USettings::OnAudioButtonClicked);
	}
}

void USettings::OnDisplayButtonClicked()
{
	if (SettingsSwitcher)
	{
		SettingsSwitcher->SetActiveWidgetIndex(0);
	}
}

void USettings::OnGraphicsButtonClicked()
{
	if (SettingsSwitcher)
	{
		SettingsSwitcher->SetActiveWidgetIndex(1);
	}
}

void USettings::OnControlsButtonClicked()
{
	if (SettingsSwitcher)
	{
		SettingsSwitcher->SetActiveWidgetIndex(2);
	}
}

void USettings::OnAudioButtonClicked()
{
	if (SettingsSwitcher)
	{
		SettingsSwitcher->SetActiveWidgetIndex(3);
	}
}