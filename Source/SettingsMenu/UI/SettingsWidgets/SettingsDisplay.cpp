// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/SettingsWidgets/SettingsDisplay.h"
#include "SettingsMenu/UI/Elements/SettingsSwitcher.h"
#include "SettingsMenu/UI/Elements/BaseButton.h"
#include "Components/VerticalBox.h"
#include "Components/ScrollBox.h"
#include "Components/Spacer.h"
#include "Application/SlateApplicationBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Internationalization/Internationalization.h"
#include "Internationalization/Culture.h"
#include "Internationalization/TextLocalizationManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogSettingsDisplay, All, All);

USettingsDisplay::USettingsDisplay(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DefaultResolutions.Add(FIntPoint(1366, 768));
	DefaultResolutions.Add(FIntPoint(1440, 900));
	DefaultResolutions.Add(FIntPoint(1660, 900));
	DefaultResolutions.Add(FIntPoint(1920, 1080));
	DefaultResolutions.Add(FIntPoint(2560, 1440));
	DefaultResolutions.Add(FIntPoint(2560, 1600));
	DefaultResolutions.Add(FIntPoint(3440, 1440));
	DefaultResolutions.Add(FIntPoint(3840, 1440));

	SupportedFrameRates.Add(30.0f);
	SupportedFrameRates.Add(60.0f);
	SupportedFrameRates.Add(120.0f);
	SupportedFrameRates.Add(144.0f);
	SupportedFrameRates.Add(240.0f);
} 

void USettingsDisplay::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void USettingsDisplay::NativeConstruct()
{
	Super::NativeConstruct();
	SetupUIHierarchy();
	BindEvents();
	HandleLanguageSwitcher();
	UCustomGameUserSettings* CustomSettings = UCustomGameUserSettings::GetCustomGameUserSettings();
	if (CustomSettings)
	{
		HandleWindowModeSwitcher(CustomSettings);
		HandleResolutionSwitcher(CustomSettings);
		HandleFrameRateSwitcher(CustomSettings);
		HandleVSyncSwitcher(CustomSettings);
	}
	DefaultResolutions = GetSupportedResolutions(WindowMode);
}

void USettingsDisplay::SetupUIHierarchy()
{
	if (GeneralVerticalBox)
	{
		GeneralVerticalBox->AddChild(GeneralScrollBox);
		GeneralVerticalBox->AddChild(ApplySettingsButton);
	}
	if (GeneralScrollBox) GeneralScrollBox->AddChild(OptionsVerticalBox);
	if (OptionsVerticalBox)
	{
		OptionsVerticalBox->AddChild(LanguageSwitcher);
		OptionsVerticalBox->AddChild(LanguageSpacer);
		OptionsVerticalBox->AddChild(WindowModeSwitcher);
		OptionsVerticalBox->AddChild(WindowModeSpacer);
		OptionsVerticalBox->AddChild(ResolutionSwitcher);
		OptionsVerticalBox->AddChild(ResolutionSpacer);
		OptionsVerticalBox->AddChild(FrameRateSwitcher);
		OptionsVerticalBox->AddChild(FrameRateSpacer);
		OptionsVerticalBox->AddChild(VSyncSwitcher);
		OptionsVerticalBox->AddChild(VSyncSpacer);
	}
}

void USettingsDisplay::BindEvents()
{
	if (LanguageSwitcher)
	{
		LanguageSwitcher->OnLeftButtonClickedDelegate.AddDynamic(this, &USettingsDisplay::OnLanguageSwitcherLeftButtonClicked);
		LanguageSwitcher->OnRightButtonClickedDelegate.AddDynamic(this, &USettingsDisplay::OnLanguageSwitcherRightButtonClicked);
	}
	if (WindowModeSwitcher)
	{
		WindowModeSwitcher->OnLeftButtonClickedDelegate.AddDynamic(this, &USettingsDisplay::OnWindowModeSwitcherLeftButtonClicked);
		WindowModeSwitcher->OnRightButtonClickedDelegate.AddDynamic(this, &USettingsDisplay::OnWindowModeSwitcherRightButtonClicked);
	}
	if (ResolutionSwitcher)
	{
		ResolutionSwitcher->OnLeftButtonClickedDelegate.AddDynamic(this, &USettingsDisplay::OnResolutionSwitcherLeftButtonClicked);
		ResolutionSwitcher->OnRightButtonClickedDelegate.AddDynamic(this, &USettingsDisplay::OnResolutionSwitcherRightButtonClicked);
	}
	if (FrameRateSwitcher)
	{
		FrameRateSwitcher->OnLeftButtonClickedDelegate.AddDynamic(this, &USettingsDisplay::OnFrameRateSwitcherLeftButtonClicked);
		FrameRateSwitcher->OnRightButtonClickedDelegate.AddDynamic(this, &USettingsDisplay::OnFrameRateSwitcherRightButtonClicked);
	}
	if (VSyncSwitcher)
	{
		VSyncSwitcher->OnLeftButtonClickedDelegate.AddDynamic(this, &USettingsDisplay::OnVSyncSwitcherLeftButtonClicked);
		VSyncSwitcher->OnRightButtonClickedDelegate.AddDynamic(this, &USettingsDisplay::OnVSyncSwitcherRightButtonClicked);
	}
}

FText USettingsDisplay::GetWindowModeText() const
{
	switch (WindowMode)
	{
	case EWindowMode::Fullscreen:
		return FText::FromString(TEXT("Fullscreen"));
	case EWindowMode::WindowedFullscreen:
		return FText::FromString(TEXT("Full Window"));
	case EWindowMode::Windowed:
		return FText::FromString(TEXT("Windowed"));
	default:
		UE_LOG(LogSettingsDisplay, Error, TEXT("Unknown window mode. Check window modes"));
		return FText::FromString(TEXT("Unknown"));
	}
}

void USettingsDisplay::SetSwitcherResolutionText(FIntPoint InScreenResolution, USettingsSwitcher* Switcher)
{
	if (Switcher)
	{
		FText XResText = FText::AsNumber(InScreenResolution.X);
		FText YResText = FText::AsNumber(InScreenResolution.Y);
		FText ResolutionText = FText::Format(NSLOCTEXT("UI", "Resolution", "{0} x {1}"), XResText, YResText);
		Switcher->SetOptionsTextBlock(ResolutionText);
	}
}

void USettingsDisplay::SetSwitcherBoolText(bool State, USettingsSwitcher* Switcher)
{
	if (Switcher)
	{
		State ? Switcher->SetOptionsTextBlock(FText::FromString(TEXT("On"))) : Switcher->SetOptionsTextBlock(FText::FromString(TEXT("Off")));
	}
}

void USettingsDisplay::HandleLanguageSwitcher()
{
	if (LanguageSwitcher)
	{
		FInternationalization& Internationalization = FInternationalization::Get();
		TArray<FCultureRef> AvailableCulturesRef = Internationalization.GetAvailableCultures(AvailableCultureCodes, false);
		CurrentLanguageCode = Internationalization.GetCurrentCulture()->GetName();
		FString DisplayName = Internationalization.GetCurrentCulture()->GetDisplayName();
		FText DisplayText = FText::FromString(DisplayName);
		LanguageSwitcher->SetOptionsTextBlock(DisplayText);
	}
}

void USettingsDisplay::HandleWindowModeSwitcher(UCustomGameUserSettings* CustomSettings)
{
	if (LanguageSwitcher)
	{
		WindowMode = CustomSettings->GetFullscreenMode();
		LanguageSwitcher->SetOptionsTextBlock(GetWindowModeText());
	}
}

void USettingsDisplay::HandleResolutionSwitcher(UCustomGameUserSettings* CustomSettings)
{
	if (ResolutionSwitcher)
	{
		ScreenResolution = CustomSettings->GetScreenResolution();
		SetSwitcherResolutionText(ScreenResolution, ResolutionSwitcher);
	}
}

void USettingsDisplay::HandleFrameRateSwitcher(UCustomGameUserSettings* CustomSettings)
{
	if (FrameRateSwitcher)
	{
		FrameRateLimit = CustomSettings->GetFrameRateLimit();
		FrameRateSwitcher->SetOptionsTextBlock(FText::AsNumber(FrameRateLimit));
	}
}

void USettingsDisplay::HandleVSyncSwitcher(UCustomGameUserSettings* CustomSettings)
{
	if (VSyncSwitcher)
	{
		bEnableVSync = CustomSettings->IsVSyncEnabled();
		SetSwitcherBoolText(bEnableVSync, VSyncSwitcher);
	}
}

FText USettingsDisplay::ConvertLanguageCodeToDisplayText(const FString& LanguageCode)
{
	FCulturePtr CulturePtr = FInternationalization::Get().GetCulture(LanguageCode);
	if (CulturePtr.IsValid())
	{
		FString DisplayName = CulturePtr->GetDisplayName();
		return FText::FromString(DisplayName);
	}
	else
	{
		UE_LOG(LogSettingsDisplay, Error, TEXT("ConvertLanguageCodeToDisplayName() fail, check language code"));
		return FText::FromString(TEXT("English"));
	}
}

TArray<FIntPoint> USettingsDisplay::GetSupportedResolutions(EWindowMode::Type InWindowMode)
{
	TArray<FIntPoint> DisplaySupportedResolutions;
	switch (InWindowMode)
	{
	case EWindowMode::Fullscreen:
		UKismetSystemLibrary::GetSupportedFullscreenResolutions(DisplaySupportedResolutions);
		break;
	case EWindowMode::WindowedFullscreen:
		UKismetSystemLibrary::GetConvenientWindowedResolutions(DisplaySupportedResolutions);
		break;
	case EWindowMode::Windowed:
		UKismetSystemLibrary::GetConvenientWindowedResolutions(DisplaySupportedResolutions);
		break;
	default:
		DisplaySupportedResolutions = DefaultResolutions;
		UE_LOG(LogSettingsDisplay, Error, TEXT("Unknown window mode. Check window modes."));
		break;
	}
	return DisplaySupportedResolutions;
}

void USettingsDisplay::OnLanguageSwitcherLeftButtonClicked()
{
	if (LanguageSwitcher)
	{
		int32 Index = AvailableCultureCodes.Find(CurrentLanguageCode);
		if (Index != INDEX_NONE && Index > 0)
		{
			FString PreviousLanguageCode = AvailableCultureCodes[Index - 1];
			CurrentLanguageCode = PreviousLanguageCode;
			FText NewLanguageDisplayText = ConvertLanguageCodeToDisplayText(PreviousLanguageCode);
			LanguageSwitcher->SetOptionsTextBlock(NewLanguageDisplayText);
		}
	}
}

void USettingsDisplay::OnLanguageSwitcherRightButtonClicked()
{
	if (LanguageSwitcher)
	{
		int32 Index = AvailableCultureCodes.Find(CurrentLanguageCode);
		int32 NumElements = AvailableCultureCodes.Num();

		if (Index != INDEX_NONE && Index < NumElements - 1)
		{
			FString NextLanguageCode = AvailableCultureCodes[Index + 1];
			CurrentLanguageCode = NextLanguageCode;
			FText NewLanguageDisplayText = ConvertLanguageCodeToDisplayText(NextLanguageCode);
			LanguageSwitcher->SetOptionsTextBlock(NewLanguageDisplayText);
		}
	}
}

void USettingsDisplay::OnWindowModeSwitcherLeftButtonClicked()
{
	if (WindowModeSwitcher)
	{
		int32 Index = static_cast<int32>(WindowMode);
		if (Index > static_cast<int32>(EWindowMode::Fullscreen))
		{
			WindowMode = static_cast<EWindowMode::Type>(Index - 1);
			WindowModeSwitcher->SetOptionsTextBlock(GetWindowModeText());
		}
	}
}

void USettingsDisplay::OnWindowModeSwitcherRightButtonClicked()
{
	if (WindowModeSwitcher)
	{
		if (WindowModeSwitcher)
		{
			int32 Index = static_cast<int32>(WindowMode);
			int32 NumElements = static_cast<int32>(EWindowMode::WindowedFullscreen);

			if (Index < NumElements - 1)
			{
				WindowMode = static_cast<EWindowMode::Type>(Index + 1);
				WindowModeSwitcher->SetOptionsTextBlock(GetWindowModeText());
			}
		}
	}
}

void USettingsDisplay::OnResolutionSwitcherLeftButtonClicked()
{
	if (!ResolutionSwitcher) return;
	int32 NumElements = SupportedResolutions.Num();
	if (NumElements == 0)
	{
		UE_LOG(LogSettingsDisplay, Error, TEXT("Unable to access available screen resolutions."));
		SupportedResolutions = DefaultResolutions;
		NumElements = SupportedResolutions.Num();
	}
	int32 Index = SupportedResolutions.IndexOfByKey(ScreenResolution);
	if (Index != INDEX_NONE && Index > 0)
	{
		ScreenResolution = SupportedResolutions[Index - 1];
		SetSwitcherResolutionText(ScreenResolution, ResolutionSwitcher);
	}
}

void USettingsDisplay::OnResolutionSwitcherRightButtonClicked()
{
	if (!ResolutionSwitcher) return;
	int32 NumElements = SupportedResolutions.Num();
	if (NumElements == 0)
	{
		UE_LOG(LogSettingsDisplay, Error, TEXT("Unable to access available screen resolutions."));
		SupportedResolutions = DefaultResolutions;
		NumElements = SupportedResolutions.Num();
	}
	int32 Index = SupportedResolutions.IndexOfByKey(ScreenResolution);
	if (Index != INDEX_NONE && Index < NumElements - 1)
	{
		ScreenResolution = SupportedResolutions[Index + 1];
		SetSwitcherResolutionText(ScreenResolution, ResolutionSwitcher);
	}
}

void USettingsDisplay::OnFrameRateSwitcherLeftButtonClicked()
{
	if (FrameRateSwitcher)
	{
		int32 Index = SupportedFrameRates.Find(FrameRateLimit);
		if (Index != INDEX_NONE && Index > 0)
		{
			FrameRateLimit = SupportedFrameRates[Index - 1];
			FrameRateSwitcher->SetOptionsTextBlock(FText::AsNumber(FrameRateLimit));
		}
	}
}

void USettingsDisplay::OnFrameRateSwitcherRightButtonClicked()
{
	if (FrameRateSwitcher)
	{
		int32 NumElements = SupportedFrameRates.Num();
		int32 Index = SupportedFrameRates.Find(FrameRateLimit);
		if (Index != INDEX_NONE && Index < NumElements - 1)
		{
			FrameRateLimit = SupportedFrameRates[Index + 1];
			FrameRateSwitcher->SetOptionsTextBlock(FText::AsNumber(FrameRateLimit));
		}
	}
}

void USettingsDisplay::OnVSyncSwitcherLeftButtonClicked()
{
	if (VSyncSwitcher)
	{
		bEnableVSync = false;
		SetSwitcherBoolText(false, VSyncSwitcher);
	}
}

void USettingsDisplay::OnVSyncSwitcherRightButtonClicked()
{
	if (VSyncSwitcher)
	{
		bEnableVSync = true;
		SetSwitcherBoolText(true, VSyncSwitcher);
	}
}

void USettingsDisplay::OnApplySettingsButtonClicked()
{
	if (ApplySettingsButton)
	{
		UCustomGameUserSettings* CustomSettings = UCustomGameUserSettings::GetCustomGameUserSettings();
		if (CustomSettings)
		{
			CustomSettings->SetFullscreenMode(WindowMode);
			CustomSettings->SetScreenResolution(ScreenResolution);
			CustomSettings->SetFrameRateLimit(FrameRateLimit);
			CustomSettings->SetVSyncEnabled(bEnableVSync);
			CustomSettings->ApplySettings(false);
		}
	}
}
