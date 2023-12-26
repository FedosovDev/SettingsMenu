// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/Elements/SettingsKeySetter.h"
#include "Components/Overlay.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/InputKeySelector.h"

USettingsKeySetter::USettingsKeySetter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    OptionTextToDisplay = FText::FromString(TEXT("Text"));
}

void USettingsKeySetter::NativePreConstruct()
{
    Super::NativePreConstruct();
    if (OptionTextBlock)
    {
        OptionTextBlock->SetText(OptionTextToDisplay);
    }
}

void USettingsKeySetter::NativeConstruct()
{
    Super::NativeConstruct();
    SetupUIHierarchy();
}

void USettingsKeySetter::SetupUIHierarchy()
{
    if (GeneralOverlay)
    {
        GeneralOverlay->AddChild(InnerBorder);
        GeneralOverlay->AddChild(OuterBorder);
        GeneralOverlay->AddChild(OptionHorizontalBox);
    }
    if (OptionHorizontalBox)
    {
        OptionHorizontalBox->AddChild(OptionTextBlock);
        OptionHorizontalBox->AddChild(OptionBorder);
        OptionHorizontalBox->AddChild(KeySelectorOverlay);
    }
    if (KeySelectorOverlay)
    {
        KeySelectorOverlay->AddChild(KeySelectorBorder);
        KeySelectorOverlay->AddChild(KeySelector);
    }
}

void USettingsKeySetter::BindEvents()
{
    if (KeySelector)
    {
        KeySelector->OnKeySelected.AddDynamic(this, &USettingsKeySetter::OnKeySelectedHandler);
        KeySelector->OnIsSelectingKeyChanged.AddDynamic(this, &USettingsKeySetter::OnIsSelectedKeyChangedHandler);
    }
}

void USettingsKeySetter::OnKeySelectedHandler(FInputChord InSelectedKey)
{
    OnKeySelectedDelegate.Broadcast(InSelectedKey);
}

void USettingsKeySetter::OnIsSelectedKeyChangedHandler()
{
    OnIsSelectedKeyChangedDelegate.Broadcast();
}