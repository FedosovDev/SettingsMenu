// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/SettingsWidgets/SettingsInGame.h"
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


USettingsInGame::USettingsInGame(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void USettingsInGame::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void USettingsInGame::NativeConstruct()
{
	Super::NativeConstruct();
	SetupUIHierarchy();
	BindEvents();
}

void USettingsInGame::SetupUIHierarchy()
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

void USettingsInGame::BindEvents()
{
	if (DisplayButton)
	{
		DisplayButton->OnButtonClickedDelegate.AddDynamic(this, &USettingsInGame::OnDisplayButtonClicked);
	}
	if (GraphicsButton)
	{
		GraphicsButton->OnButtonClickedDelegate.AddDynamic(this, &USettingsInGame::OnGraphicsButtonClicked);
	}
	if (ControlsButton)
	{
		ControlsButton->OnButtonClickedDelegate.AddDynamic(this, &USettingsInGame::OnControlsButtonClicked);
	}
	if (AudioButton)
	{
		AudioButton->OnButtonClickedDelegate.AddDynamic(this, &USettingsInGame::OnAudioButtonClicked);
	}
}

void USettingsInGame::OnDisplayButtonClicked()
{
	if (SettingsSwitcher)
	{
		SettingsSwitcher->SetActiveWidgetIndex(0);
	}
}

void USettingsInGame::OnGraphicsButtonClicked()
{
	if (SettingsSwitcher)
	{
		SettingsSwitcher->SetActiveWidgetIndex(1);
	}
}

void USettingsInGame::OnControlsButtonClicked()
{
	if (SettingsSwitcher)
	{
		SettingsSwitcher->SetActiveWidgetIndex(2);
	}
}

void USettingsInGame::OnAudioButtonClicked()
{
	if (SettingsSwitcher)
	{
		SettingsSwitcher->SetActiveWidgetIndex(3);
	}
}
