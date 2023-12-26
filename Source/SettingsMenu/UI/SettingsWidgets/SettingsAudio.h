// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsMenu/GameUserSettings/CustomGameUserSettings.h"
#include "SettingsAudio.generated.h"

class UVerticalBox;
class USettingsSlider;
class USpacer;

UCLASS()
class SETTINGSMENU_API USettingsAudio : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativePreConstruct() override;

protected:
	virtual void NativeConstruct() override;
	void SetupUIHierarchy();
	void BindEvents();
	void SetMasterVolumeDefaultValue(UCustomGameUserSettings* Settings);
	void SetMusicVolumeDefaultValue(UCustomGameUserSettings* Settings);
	void SetSFXVolumeDefaultValue(UCustomGameUserSettings* Settings);
	void SetUIVolumeDefaultValue(UCustomGameUserSettings* Settings);

	UFUNCTION()
	void OnMasterVolumeValueChanged(float NewValue);
	UFUNCTION()
	void OnMusicVolumeValueChanged(float NewValue);
	UFUNCTION()
	void OnSFXVolumeValueChanged(float NewValue);
	UFUNCTION()
	void OnUIVolumeValueChanged(float NewValue);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Audio Settings")
	float MasterVolumeValue;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Audio Settings")
	float MusicVolumeValue;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Audio Settings")
	float SFXVolumeValue;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Audio Settings")
	float UIVolumeValue;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* GeneralVerticalBox;
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* GeneralScrollBox;
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* OptionsVerticalBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSlider* MasterVolumeSlider;
	UPROPERTY(meta = (BindWidget))
	USpacer* MasterVolumeSpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSlider* MusicVolumeSlider;
	UPROPERTY(meta = (BindWidget))
	USpacer* MusicVolumeSpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSlider* SFXVolumeSlider;
	UPROPERTY(meta = (BindWidget))
	USpacer* SFXVolumeSpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSlider* UIVolumeSlider;
	UPROPERTY(meta = (BindWidget))
	USpacer* UIVolumeSpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBaseButton* ApplySettingsButton;
};
