// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/SettingsWidgets/SettingsGraphics.h"
#include "SettingsMenu/UI/Elements/SettingsSwitcher.h"
#include "SettingsMenu/UI/Elements/BaseButton.h"
#include "Components/VerticalBox.h"
#include "Components/ScrollBox.h"
#include "Components/Spacer.h"

USettingsGraphics::USettingsGraphics(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	QualityIndexToTextMap = 
	{
	{0, FText::FromString(TEXT("Low"))},
	{ 1, FText::FromString(TEXT("Medium")) },
	{ 2, FText::FromString(TEXT("High")) },
	{ 3, FText::FromString(TEXT("Ultra")) },
	{ 4, FText::FromString(TEXT("Epic"))} 
	};
}

void USettingsGraphics::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void USettingsGraphics::NativeConstruct()
{
	Super::NativeConstruct();
	SetupUIHierarchy();
	BindEvents();
	UCustomGameUserSettings* CustomSettings = UCustomGameUserSettings::GetCustomGameUserSettings();
	if (CustomSettings)
	{
		if (TextureQualitySwitcher)
		{
			TextureQualityIndex = CustomSettings->GetTextureQuality();
			SetQualitySwitcherWidget(TextureQualityIndex, TextureQualitySwitcher);
		}
		if (ShadowQualitySwitcher)
		{
			ShadowQualityIndex = CustomSettings->GetShadowQuality();
			SetQualitySwitcherWidget(ShadowQualityIndex, ShadowQualitySwitcher);
		}
		if (ShadingQualitySwitcher)
		{
			ShadingQualityIndex = CustomSettings->GetShadingQuality();
			SetQualitySwitcherWidget(ShadingQualityIndex, ShadingQualitySwitcher);
		}
		if (AntiAliasingQualitySwitcher)
		{
			AntiAliasingQualityIndex = CustomSettings->GetAntiAliasingQuality();
			SetQualitySwitcherWidget(AntiAliasingQualityIndex, AntiAliasingQualitySwitcher);
		}
		if (PostProcessQualitySwitcher)
		{
			PostProcessQualityIndex = CustomSettings->GetAntiAliasingQuality();
			SetQualitySwitcherWidget(PostProcessQualityIndex, PostProcessQualitySwitcher);
		}
		if (ViewDistanceQualitySwitcher)
		{
			ViewDistanceQualityIndex = CustomSettings->GetViewDistanceQuality();
			SetQualitySwitcherWidget(ViewDistanceQualityIndex, ViewDistanceQualitySwitcher);
		}
		if (VisualEffectsQualitySwitcher)
		{
			VisualEffectsQualityIndex = CustomSettings->GetVisualEffectQuality();
			SetQualitySwitcherWidget(VisualEffectsQualityIndex, VisualEffectsQualitySwitcher);
		}
		if (FoliageQualitySwitcher)
		{
			FoliageQualityIndex = CustomSettings->GetFoliageQuality();
			SetQualitySwitcherWidget(FoliageQualityIndex, FoliageQualitySwitcher);
		}
		if (FocalDistanceSwitcher)
		{
			bUseFocalDistance = CustomSettings->GetUseFocalDistanse();
			SetSwitcherBoolText(bUseFocalDistance, FocalDistanceSwitcher);
		}
	}
}

void USettingsGraphics::SetupUIHierarchy()
{
	if (GeneralVerticalBox)
	{
		GeneralVerticalBox->AddChild(GeneralScrollBox);
		GeneralVerticalBox->AddChild(ApplySettingsButton);
	}
	if (GeneralScrollBox) GeneralScrollBox->AddChild(OptionsVerticalBox);
	if (OptionsVerticalBox)
	{
		OptionsVerticalBox->AddChild(TextureQualitySwitcher);
		OptionsVerticalBox->AddChild(TextureQualitySpacer);
		OptionsVerticalBox->AddChild(ShadowQualitySwitcher);
		OptionsVerticalBox->AddChild(ShadowQualitySpacer);
		OptionsVerticalBox->AddChild(ShadingQualitySwitcher);
		OptionsVerticalBox->AddChild(ShadingQualitySpacer);
		OptionsVerticalBox->AddChild(AntiAliasingQualitySwitcher);
		OptionsVerticalBox->AddChild(AntiAliasingQualitySpacer);
		OptionsVerticalBox->AddChild(PostProcessQualitySwitcher);
		OptionsVerticalBox->AddChild(PostProcessQualitySpacer);
		OptionsVerticalBox->AddChild(ViewDistanceQualitySwitcher);
		OptionsVerticalBox->AddChild(ViewDistanceQualitySpacer);
		OptionsVerticalBox->AddChild(VisualEffectsQualitySwitcher);
		OptionsVerticalBox->AddChild(VisualEffectsQualitySpacer);
		OptionsVerticalBox->AddChild(FoliageQualitySwitcher);
		OptionsVerticalBox->AddChild(FoliageQualitySpacer);
		OptionsVerticalBox->AddChild(FocalDistanceSwitcher);
		OptionsVerticalBox->AddChild(FocalDistanceSpacer);
	}
}

void USettingsGraphics::BindEvents()
{
	if (TextureQualitySwitcher)
	{
		TextureQualitySwitcher->OnLeftButtonClickedDelegate.AddDynamic(this, &USettingsGraphics::OnTextureQualitySwitcherLeftButtonClicked);
		TextureQualitySwitcher->OnRightButtonClickedDelegate.AddDynamic(this, &USettingsGraphics::OnTextureQualitySwitcherRightButtonClicked);
	}
	if (ShadowQualitySwitcher)
	{
		ShadowQualitySwitcher->OnLeftButtonClickedDelegate.AddDynamic(this, &USettingsGraphics::OnShadowQualitySwitcherLeftButtonClicked);
		ShadowQualitySwitcher->OnRightButtonClickedDelegate.AddDynamic(this, &USettingsGraphics::OnShadowQualitySwitcherRightButtonClicked);
	}
	if (ShadingQualitySwitcher)
	{
		ShadingQualitySwitcher->OnLeftButtonClickedDelegate.AddDynamic(this, &USettingsGraphics::OnShadingQualitySwitcherLeftButtonClicked);
		ShadingQualitySwitcher->OnRightButtonClickedDelegate.AddDynamic(this, &USettingsGraphics::OnShadingQualitySwitcherLeftButtonClicked);
	}
	if (AntiAliasingQualitySwitcher)
	{
		AntiAliasingQualitySwitcher->OnLeftButtonClickedDelegate.AddDynamic(this, &USettingsGraphics::OnAntiAliasingQualitySwitcherLeftButtonClicked);
		AntiAliasingQualitySwitcher->OnRightButtonClickedDelegate.AddDynamic(this, &USettingsGraphics::OnAntiAliasingQualitySwitcherRightButtonClicked);
	}
	if (PostProcessQualitySwitcher)
	{
		PostProcessQualitySwitcher->OnLeftButtonClickedDelegate.AddDynamic(this, &USettingsGraphics::OnPostProcessQualitySwitcherLeftButtonClicked);
		PostProcessQualitySwitcher->OnRightButtonClickedDelegate.AddDynamic(this, &USettingsGraphics::OnPostProcessQualitySwitcherRightButtonClicked);
	}
	if (ViewDistanceQualitySwitcher)
	{
		ViewDistanceQualitySwitcher->OnLeftButtonClickedDelegate.AddDynamic(this, &USettingsGraphics::OnViewDistanceQualitySwitcherLeftButtonClicked);
		ViewDistanceQualitySwitcher->OnRightButtonClickedDelegate.AddDynamic(this, &USettingsGraphics::OnViewDistanceQualitySwitcherRightButtonClicked);
	}
	if (VisualEffectsQualitySwitcher)
	{
		VisualEffectsQualitySwitcher->OnLeftButtonClickedDelegate.AddDynamic(this, &USettingsGraphics::OnVisualEffectsQualitySwitcherLeftButtonClicked);
		VisualEffectsQualitySwitcher->OnRightButtonClickedDelegate.AddDynamic(this, &USettingsGraphics::OnVisualEffectsQualitySwitcherRightButtonClicked);
	}
	if (FoliageQualitySwitcher)
	{
		FoliageQualitySwitcher->OnLeftButtonClickedDelegate.AddDynamic(this, &USettingsGraphics::OnFoliageQualitySwitcherLeftButtonClicked);
		FoliageQualitySwitcher->OnRightButtonClickedDelegate.AddDynamic(this, &USettingsGraphics::OnFoliageQualitySwitcherRightButtonClicked);
	}
	if (FocalDistanceSwitcher)
	{
		FocalDistanceSwitcher->OnLeftButtonClickedDelegate.AddDynamic(this, &USettingsGraphics::OnFocalDistanceSwitcherLeftButtonClicked);
		FocalDistanceSwitcher->OnRightButtonClickedDelegate.AddDynamic(this, &USettingsGraphics::OnFocalDistanceSwitcherRightButtonClicked);
	}
	if (ApplySettingsButton)
	{
		ApplySettingsButton->OnButtonClickedDelegate.AddDynamic(this, &USettingsGraphics::OnApplyGraphicsSettingsButtonClicked);
	}
}

bool USettingsGraphics::QualityAsText(FText& OutText, int32 Index)
{
	if (QualityIndexToTextMap.Contains(Index))
	{
		OutText = QualityIndexToTextMap[Index];
		return true;
	}
	else return false;
}

void USettingsGraphics::SetQualitySwitcherWidget(int32 QualityIndex, USettingsSwitcher* Switcher)
{
	if (Switcher)
	{
		FText QualityText;
		if (QualityAsText(QualityText, QualityIndex))
		{
			TextureQualitySwitcher->SetOptionsTextBlock(QualityText);
		}
	}
}

void USettingsGraphics::SetSwitcherBoolText(bool State, USettingsSwitcher* Switcher)
{
	if (Switcher)
	{
		State ? Switcher->SetOptionsTextBlock(FText::FromString(TEXT("On"))) : Switcher->SetOptionsTextBlock(FText::FromString(TEXT("Off")));
	}
}

void USettingsGraphics::OnTextureQualitySwitcherLeftButtonClicked()
{
	TextureQualityIndex = (TextureQualityIndex - 1 + 5) % 5;
	SetQualitySwitcherWidget(TextureQualityIndex, TextureQualitySwitcher);
}

void USettingsGraphics::OnTextureQualitySwitcherRightButtonClicked()
{
	TextureQualityIndex = (TextureQualityIndex + 1) % 5;
	SetQualitySwitcherWidget(TextureQualityIndex, TextureQualitySwitcher);
}

void USettingsGraphics::OnShadowQualitySwitcherLeftButtonClicked()
{
	ShadowQualityIndex = (ShadowQualityIndex - 1 + 5) % 5;
	SetQualitySwitcherWidget(ShadowQualityIndex, ShadowQualitySwitcher);
}

void USettingsGraphics::OnShadowQualitySwitcherRightButtonClicked()
{
	ShadowQualityIndex = (ShadowQualityIndex + 1) % 5;
	SetQualitySwitcherWidget(ShadowQualityIndex, ShadowQualitySwitcher);
}

void USettingsGraphics::OnShadingQualitySwitcherLeftButtonClicked()
{
	ShadingQualityIndex = (ShadingQualityIndex - 1 + 5) % 5;
	SetQualitySwitcherWidget(ShadingQualityIndex, ShadingQualitySwitcher);
}

void USettingsGraphics::OnShadingQualitySwitcherRightButtonClicked()
{
	ShadingQualityIndex = (ShadingQualityIndex + 1) % 5;
	SetQualitySwitcherWidget(ShadingQualityIndex, ShadingQualitySwitcher);
}

void USettingsGraphics::OnAntiAliasingQualitySwitcherLeftButtonClicked()
{
	AntiAliasingQualityIndex = (AntiAliasingQualityIndex - 1 + 5) % 5;
	SetQualitySwitcherWidget(AntiAliasingQualityIndex, AntiAliasingQualitySwitcher);
}

void USettingsGraphics::OnAntiAliasingQualitySwitcherRightButtonClicked()
{
	AntiAliasingQualityIndex = (AntiAliasingQualityIndex + 1) % 5;
	SetQualitySwitcherWidget(AntiAliasingQualityIndex, AntiAliasingQualitySwitcher);
}

void USettingsGraphics::OnPostProcessQualitySwitcherLeftButtonClicked()
{
	PostProcessQualityIndex = (PostProcessQualityIndex - 1 + 5) % 5;
	SetQualitySwitcherWidget(PostProcessQualityIndex, PostProcessQualitySwitcher);
}

void USettingsGraphics::OnPostProcessQualitySwitcherRightButtonClicked()
{
	PostProcessQualityIndex = (PostProcessQualityIndex + 1) % 5;
	SetQualitySwitcherWidget(PostProcessQualityIndex, PostProcessQualitySwitcher);
}

void USettingsGraphics::OnViewDistanceQualitySwitcherLeftButtonClicked()
{
	ViewDistanceQualityIndex = (ViewDistanceQualityIndex - 1 + 5) % 5;
	SetQualitySwitcherWidget(ViewDistanceQualityIndex, ViewDistanceQualitySwitcher);
}

void USettingsGraphics::OnViewDistanceQualitySwitcherRightButtonClicked()
{
	ViewDistanceQualityIndex = (ViewDistanceQualityIndex + 1) % 5;
	SetQualitySwitcherWidget(ViewDistanceQualityIndex, ViewDistanceQualitySwitcher);
}

void USettingsGraphics::OnVisualEffectsQualitySwitcherLeftButtonClicked()
{
	VisualEffectsQualityIndex = (VisualEffectsQualityIndex - 1 + 5) % 5;
	SetQualitySwitcherWidget(VisualEffectsQualityIndex, VisualEffectsQualitySwitcher);
}

void USettingsGraphics::OnVisualEffectsQualitySwitcherRightButtonClicked()
{
	VisualEffectsQualityIndex = (VisualEffectsQualityIndex + 1) % 5;
	SetQualitySwitcherWidget(VisualEffectsQualityIndex, VisualEffectsQualitySwitcher);
}

void USettingsGraphics::OnFoliageQualitySwitcherLeftButtonClicked()
{
	FoliageQualityIndex = (FoliageQualityIndex - 1 + 5) % 5;
	SetQualitySwitcherWidget(FoliageQualityIndex, FoliageQualitySwitcher);
}

void USettingsGraphics::OnFoliageQualitySwitcherRightButtonClicked()
{
	FoliageQualityIndex = (FoliageQualityIndex + 1) % 5;
	SetQualitySwitcherWidget(FoliageQualityIndex, FoliageQualitySwitcher);
}

void USettingsGraphics::OnFocalDistanceSwitcherLeftButtonClicked()
{
	bUseFocalDistance = false;
	SetSwitcherBoolText(bUseFocalDistance, FocalDistanceSwitcher);
}

void USettingsGraphics::OnFocalDistanceSwitcherRightButtonClicked()
{
	bUseFocalDistance = true;
	SetSwitcherBoolText(bUseFocalDistance, FocalDistanceSwitcher);
}

void USettingsGraphics::OnApplyGraphicsSettingsButtonClicked()
{
	UCustomGameUserSettings* CustomSettings = UCustomGameUserSettings::GetCustomGameUserSettings();
	if (CustomSettings)
	{
		CustomSettings->SetTextureQuality(TextureQualityIndex);
		CustomSettings->SetShadowQuality(ShadowQualityIndex);
		CustomSettings->SetShadingQuality(ShadingQualityIndex);
		CustomSettings->SetAntiAliasingQuality(AntiAliasingQualityIndex);
		CustomSettings->SetPostProcessingQuality(PostProcessQualityIndex);
		CustomSettings->SetViewDistanceQuality(ViewDistanceQualityIndex);
		CustomSettings->SetVisualEffectQuality(VisualEffectsQualityIndex);
		CustomSettings->SetFoliageQuality(FoliageQualityIndex);
		CustomSettings->SetUseFocalDistanse(bUseFocalDistance);
		CustomSettings->ApplySettings(false);
	}
}


