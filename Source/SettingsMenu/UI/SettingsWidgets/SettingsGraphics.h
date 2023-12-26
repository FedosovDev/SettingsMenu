// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsMenu/GameUserSettings/CustomGameUserSettings.h"
#include "SettingsGraphics.generated.h"

class UVerticalBox;
class USpacer;
class USettingsSwitcher;

UCLASS()
class SETTINGSMENU_API USettingsGraphics : public UUserWidget
{
	GENERATED_BODY()
	
public:
	USettingsGraphics(const FObjectInitializer& ObjectInitializer);
	void NativePreConstruct() override;

protected:
	virtual void NativeConstruct() override;
	void SetupUIHierarchy();
	void BindEvents();
	bool QualityAsText(FText& OutText, int32 Index);
	void SetQualitySwitcherWidget(int32 QualityIndex, USettingsSwitcher* Switcher);
	void SetSwitcherBoolText(bool State, USettingsSwitcher* Switcher);

	UFUNCTION()
	void OnTextureQualitySwitcherLeftButtonClicked();
	UFUNCTION()
	void OnTextureQualitySwitcherRightButtonClicked();
	UFUNCTION()
	void OnShadowQualitySwitcherLeftButtonClicked();
	UFUNCTION()
	void OnShadowQualitySwitcherRightButtonClicked();
	UFUNCTION()
	void OnShadingQualitySwitcherLeftButtonClicked();
	UFUNCTION()
	void OnShadingQualitySwitcherRightButtonClicked();
	UFUNCTION()
	void OnAntiAliasingQualitySwitcherLeftButtonClicked();
	UFUNCTION()
	void OnAntiAliasingQualitySwitcherRightButtonClicked();
	UFUNCTION()
	void OnPostProcessQualitySwitcherLeftButtonClicked();
	UFUNCTION()
	void OnPostProcessQualitySwitcherRightButtonClicked();
	UFUNCTION()
	void OnViewDistanceQualitySwitcherLeftButtonClicked();
	UFUNCTION()
	void OnViewDistanceQualitySwitcherRightButtonClicked();
	UFUNCTION()
	void OnVisualEffectsQualitySwitcherLeftButtonClicked();
	UFUNCTION()
	void OnVisualEffectsQualitySwitcherRightButtonClicked();
	UFUNCTION()
	void OnFoliageQualitySwitcherLeftButtonClicked();
	UFUNCTION()
	void OnFoliageQualitySwitcherRightButtonClicked();
	UFUNCTION()
	void OnFocalDistanceSwitcherLeftButtonClicked();
	UFUNCTION()
	void OnFocalDistanceSwitcherRightButtonClicked();
	UFUNCTION()
	void OnApplyGraphicsSettingsButtonClicked();

	int32 TextureQualityIndex;
	int32 ShadowQualityIndex;
	int32 ShadingQualityIndex;
	int32 AntiAliasingQualityIndex;
	int32 PostProcessQualityIndex;
	int32 ViewDistanceQualityIndex;
	int32 VisualEffectsQualityIndex;
	int32 FoliageQualityIndex;
	bool bUseFocalDistance;
	TMap<int32, FText> QualityIndexToTextMap;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* GeneralVerticalBox;
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* GeneralScrollBox;
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* OptionsVerticalBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* TextureQualitySwitcher;
	UPROPERTY(meta = (BindWidget))
	USpacer* TextureQualitySpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* ShadowQualitySwitcher;
	UPROPERTY(meta = (BindWidget))
	USpacer* ShadowQualitySpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* ShadingQualitySwitcher;
	UPROPERTY(meta = (BindWidget))
	USpacer* ShadingQualitySpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* AntiAliasingQualitySwitcher;
	UPROPERTY(meta = (BindWidget))
	USpacer* AntiAliasingQualitySpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* PostProcessQualitySwitcher;
	UPROPERTY(meta = (BindWidget))
	USpacer* PostProcessQualitySpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* ViewDistanceQualitySwitcher;
	UPROPERTY(meta = (BindWidget))
	USpacer* ViewDistanceQualitySpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* VisualEffectsQualitySwitcher;
	UPROPERTY(meta = (BindWidget))
	USpacer* VisualEffectsQualitySpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* FoliageQualitySwitcher;
	UPROPERTY(meta = (BindWidget))
	USpacer* FoliageQualitySpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* FocalDistanceSwitcher;
	UPROPERTY(meta = (BindWidget))
	USpacer* FocalDistanceSpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBaseButton* ApplySettingsButton;
};
