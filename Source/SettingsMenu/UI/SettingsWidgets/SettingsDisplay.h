// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameUserSettings.h"
#include "SettingsMenu/GameUserSettings/CustomGameUserSettings.h"
#include "SettingsDisplay.generated.h"

class UVerticalBox;
class USpacer;
class USettingsSwitcher;

UCLASS()
class SETTINGSMENU_API USettingsDisplay : public UUserWidget
{
	GENERATED_BODY()

public:
	USettingsDisplay(const FObjectInitializer& ObjectInitializer);
	void NativePreConstruct() override;

protected:
	virtual void NativeConstruct() override;
	void SetupUIHierarchy();
	void BindEvents();
	FText GetWindowModeText() const;
	void SetSwitcherResolutionText(FIntPoint ScreenResolution, USettingsSwitcher* Switcher);
	void SetSwitcherBoolText(bool State, USettingsSwitcher* Switcher);
	void HandleLanguageSwitcher();
	void HandleWindowModeSwitcher(UCustomGameUserSettings* CustomSettings);
	void HandleResolutionSwitcher(UCustomGameUserSettings* CustomSettings);
	void HandleFrameRateSwitcher(UCustomGameUserSettings* CustomSettings);
	void HandleVSyncSwitcher(UCustomGameUserSettings* CustomSettings);
	FText ConvertLanguageCodeToDisplayText(const FString& LanguageCode);
	TArray<FIntPoint> GetSupportedResolutions(EWindowMode::Type WindowMode);

	UFUNCTION()
	void OnLanguageSwitcherLeftButtonClicked();
	UFUNCTION()
	void OnLanguageSwitcherRightButtonClicked();
	UFUNCTION()
	void OnWindowModeSwitcherLeftButtonClicked();
	UFUNCTION()
	void OnWindowModeSwitcherRightButtonClicked();
	UFUNCTION()
	void OnResolutionSwitcherLeftButtonClicked();
	UFUNCTION()
	void OnResolutionSwitcherRightButtonClicked();
	UFUNCTION()
	void OnFrameRateSwitcherLeftButtonClicked();
	UFUNCTION()
	void OnFrameRateSwitcherRightButtonClicked();
	UFUNCTION()
	void OnVSyncSwitcherLeftButtonClicked();
	UFUNCTION()
	void OnVSyncSwitcherRightButtonClicked();
	UFUNCTION()
	void OnApplySettingsButtonClicked();

	EWindowMode::Type WindowMode;
	TArray<FIntPoint> DefaultResolutions;
	FIntPoint ScreenResolution;
	TArray<FIntPoint> SupportedResolutions;
	float FrameRateLimit;
	TArray<float> SupportedFrameRates;
	bool bEnableVSync;
	FString CurrentLanguageCode;
	TArray<FString> AvailableCultureCodes;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* GeneralVerticalBox;
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* GeneralScrollBox;
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* OptionsVerticalBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* LanguageSwitcher;
	UPROPERTY(meta = (BindWidget))
	USpacer* LanguageSpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* WindowModeSwitcher;
	UPROPERTY(meta = (BindWidget))
	USpacer* WindowModeSpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* ResolutionSwitcher;
	UPROPERTY(meta = (BindWidget))
	USpacer* ResolutionSpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* FrameRateSwitcher;
	UPROPERTY(meta = (BindWidget))
	USpacer* FrameRateSpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* VSyncSwitcher;
	UPROPERTY(meta = (BindWidget))
	USpacer* VSyncSpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBaseButton* ApplySettingsButton;
};
