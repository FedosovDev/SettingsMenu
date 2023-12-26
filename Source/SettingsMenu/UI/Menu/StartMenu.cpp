// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/Menu/StartMenu.h"
#include "Components/HorizontalBox.h"
#include "Components/Overlay.h"
#include "Components/BackgroundBlur.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "SettingsMenu/UI/Elements/BaseButton.h"

UStartMenu::UStartMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UStartMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UStartMenu::NativeConstruct()
{
	Super::NativeConstruct();
	BindEvents();
}

void UStartMenu::BindEvents()
{
	if (PlayButton)
	{
		PlayButton->OnButtonClickedDelegate.AddDynamic(this, &UStartMenu::OnPlayButtonClicked);
	}
	if (SettingsButton)
	{
		SettingsButton->OnButtonClickedDelegate.AddDynamic(this, &UStartMenu::OnSettingsButtonClicked);
	}
	if (ExitButton)
	{
		ExitButton->OnButtonClickedDelegate.AddDynamic(this, &UStartMenu::OnExitButtonClicked);
	}
}

void UStartMenu::OnPlayButtonClicked()
{
}

void UStartMenu::OnSettingsButtonClicked()
{
}

void UStartMenu::OnExitButtonClicked()
{
}
