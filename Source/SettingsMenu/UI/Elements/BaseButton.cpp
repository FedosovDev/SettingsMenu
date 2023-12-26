// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/Elements/BaseButton.h"
#include "Components/Overlay.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

UBaseButton::UBaseButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    ButtonTextToDisplay = FText::FromString(TEXT("Text"));
    InnerBorderTopPadding = 16.f;
    InnerBorderBottomPadding = -16.f;
}

void UBaseButton::NativePreConstruct()
{
    Super::NativePreConstruct();
    if (ButtonTextBlock)
    {
        ButtonTextBlock->SetText(ButtonTextToDisplay);
    }
}

void UBaseButton::NativeConstruct()
{
    Super::NativeConstruct();
    SetupUIHierarchy();
    BindEvents();
    if (InnerBorder)
    {
        InnerBorder->SetPadding(FMargin(0.f, InnerBorderTopPadding, 0.f, InnerBorderBottomPadding));
    }
}

void UBaseButton::SetupUIHierarchy()
{
    if (GeneralOverlay)
    {
        GeneralOverlay->AddChild(InnerBorder);
        GeneralOverlay->AddChild(OuterBorder);
        GeneralOverlay->AddChild(VolumeButton);
    }
    if (OuterBorder)
    {
        OuterBorder->AddChild(ButtonTextBlock);
    }
}

void UBaseButton::BindEvents()
{
    if (VolumeButton)
    {
        VolumeButton->OnClicked.AddDynamic(this, &UBaseButton::OnButtonClicked);
        VolumeButton->OnHovered.AddDynamic(this, &UBaseButton::OnButtonHovered);
        VolumeButton->OnUnhovered.AddDynamic(this, &UBaseButton::OnButtonHovered);
        VolumeButton->OnPressed.AddDynamic(this, &UBaseButton::OnButtonPressed);
        VolumeButton->OnReleased.AddDynamic(this, &UBaseButton::OnButtonReleased);
    }
}

void UBaseButton::OnButtonClicked()
{
    OnButtonClickedDelegate.Broadcast();
}

void UBaseButton::OnButtonHovered()
{
    OnButtonHoveredDelegate.Broadcast();
}

void UBaseButton::OnButtonUnhovered()
{
    OnButtonUnhoveredDelegate.Broadcast();
}

void UBaseButton::OnButtonPressed()
{
    OnButtonPressedDelegate.Broadcast();
}

void UBaseButton::OnButtonReleased()
{
    OnButtonReleasedDelegate.Broadcast();
}
