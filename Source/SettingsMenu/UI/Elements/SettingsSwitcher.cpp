// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/Elements/SettingsSwitcher.h"
#include "SettingsMenu/UI/Elements/BaseButton.h"
#include "Components/Overlay.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"

USettingsSwitcher::USettingsSwitcher(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    OptionTextToDisplay = FText::FromString(TEXT("Text"));
    OptionsTextToDisplay = FText::FromString(TEXT("Text"));
}

void USettingsSwitcher::NativePreConstruct()
{
    Super::NativePreConstruct();
    if (OptionTextBlock && OptionsTextBlock)
    {
        OptionTextBlock->SetText(OptionTextToDisplay);
        OptionsTextBlock->SetText(OptionsTextToDisplay);
    }
}

void USettingsSwitcher::NativeConstruct()
{
    Super::NativeConstruct();
    SetupUIHierarchy();
    BindEvents();
}

void USettingsSwitcher::SetupUIHierarchy()
{
    if (GeneralOverlay)
    {
        GeneralOverlay->AddChild(InnerBorder);
        GeneralOverlay->AddChild(OuterBorder);
        GeneralOverlay->AddChild(OuterHorizontalBox);
    }
    if (OuterHorizontalBox)
    {
        OuterHorizontalBox->AddChild(OptionTextBlock);
        OuterHorizontalBox->AddChild(OptionBorder);
        OuterHorizontalBox->AddChild(InnerHorizontalBox);
    }
    if (InnerHorizontalBox)
    {
        InnerHorizontalBox->AddChild(LeftButton);
        InnerHorizontalBox->AddChild(OptionsTextBlock);
        InnerHorizontalBox->AddChild(RightButton);
    }
}

void USettingsSwitcher::BindEvents()
{
    if (LeftButton)
    {
        LeftButton->OnButtonClickedDelegate.AddDynamic(this, &USettingsSwitcher::OnLeftButtonClicked);
    }
    if (RightButton)
    {
        RightButton->OnButtonClickedDelegate.AddDynamic(this, &USettingsSwitcher::OnRightButtonClicked);
    }
}

void USettingsSwitcher::OnRightButtonClicked()
{
    OnRightButtonClickedDelegate.Broadcast();
}

void USettingsSwitcher::OnLeftButtonClicked()
{
    OnLeftButtonClickedDelegate.Broadcast();
}

void USettingsSwitcher::SetOptionsTextBlock(FText TextToDisplay)
{
    OptionsTextBlock->SetText(OptionsTextToDisplay);
}
