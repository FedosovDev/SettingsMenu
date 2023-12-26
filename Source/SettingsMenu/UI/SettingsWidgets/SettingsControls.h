// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/InputSettings.h"
#include "SettingsMenu/GameUserSettings/CustomGameUserSettings.h"
#include "SettingsControls.generated.h"

class UVerticalBox;
class USettingsSlider;
class USpacer;
class USettingsSwitcher;
class USettingsKeySetter;

UCLASS()
class SETTINGSMENU_API USettingsControls : public UUserWidget
{
	GENERATED_BODY()

public:
	USettingsControls(const FObjectInitializer& ObjectInitializer);
	void NativePreConstruct() override;

protected:
	virtual void NativeConstruct() override;
	void SetupUIHierarchy();
	void BindEvents();
	void SetKeySetterDefaultText(UCustomGameUserSettings* CustomSettings, USettingsKeySetter* KeySetter, FInputAxisKeyMapping& Mapping, const FName& AxisName, float Scale);
	void SetKeySetterDefaultText(UCustomGameUserSettings* CustomSettings, USettingsKeySetter* KeySetter, FInputActionKeyMapping& Mapping, const FName& ActionName);
	void SetSwitcherBoolOptionsText(USettingsSwitcher* Switcher, bool Condition);
	bool GetInputAxisMappingByName(FName MappingName, float Scale, FInputAxisKeyMapping& OutMapping);
	bool GetInputActionMappingByName(FName MappingName, FInputActionKeyMapping& OutMapping);
	void ChangeInputAxisMapping(const FInputAxisKeyMapping& InSelectedKey);
	void ChangeInputActionMapping(const FInputActionKeyMapping& InSelectedKey);

	UFUNCTION()
	void OnMouseSensSliderValueChanged(float NewValue);
	UFUNCTION()
	void OnMouseXInvertSwitcherLeftButtonClicked();
	UFUNCTION()
	void OnMouseXInvertSwitcherRightButtonClicked();
	UFUNCTION()
	void OnMouseYInvertSwitcherLeftButtonClicked();
	UFUNCTION()
	void OnMouseYInvertSwitcherRightButtonClicked();
	UFUNCTION()
	void OnMoveForwardKeySelected(FInputChord InSelectedKey);
	UFUNCTION()
	void OnMoveBackwardKeySelected(FInputChord InSelectedKey);
	UFUNCTION()
	void OnMoveRightKeySelected(FInputChord InSelectedKey);
	UFUNCTION()
	void OnMoveLeftKeySelected(FInputChord InSelectedKey);
	UFUNCTION()
	void OnJumpKeySelected(FInputChord InSelectedKey);
	UFUNCTION()
	void OnApplySettingsButtonClicked();

	float MouseSensitivitySliderValue;
	bool bMouseXInvertation;
	bool bMouseYInvertation;
	FInputAxisKeyMapping MoveForwardMapping;
	FInputAxisKeyMapping MoveBackwardMapping;
	FInputAxisKeyMapping MoveRightMapping;
	FInputAxisKeyMapping MoveLeftMapping;
	FInputActionKeyMapping JumpMappting;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* GeneralVerticalBox;
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* GeneralScrollBox;
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* OptionsVerticalBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSlider* MouseSensitivitySlider;
	UPROPERTY(meta = (BindWidget))
	USpacer* MouseSensitivitySpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* MouseXInvertSwitcher;
	UPROPERTY(meta = (BindWidget))
	USpacer* MouseXInvertSpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* MouseYInvertSwitcher;
	UPROPERTY(meta = (BindWidget))
	USpacer* MouseYInvertSpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsKeySetter* MoveForwardKeySetter;
	UPROPERTY(meta = (BindWidget))
	USpacer* MoveForwardKeySpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsKeySetter* MoveBackwardKeySetter;
	UPROPERTY(meta = (BindWidget))
	USpacer* MoveBackwardKeySpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsKeySetter* MoveRightKeySetter;
	UPROPERTY(meta = (BindWidget))
	USpacer* MoveRightKeySpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsKeySetter* MoveLeftKeySetter;
	UPROPERTY(meta = (BindWidget))
	USpacer* MoveLeftKeySpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsKeySetter* JumpKeySetter;
	UPROPERTY(meta = (BindWidget))
	USpacer* JumpKeySpacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBaseButton* ApplySettingsButton;
};
