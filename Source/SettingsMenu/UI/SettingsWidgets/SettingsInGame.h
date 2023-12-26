// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsInGame.generated.h"

class UBaseButton;

UCLASS()
class SETTINGSMENU_API USettingsInGame : public UUserWidget
{
	GENERATED_BODY()
	
public:
	USettingsInGame(const FObjectInitializer& ObjectInitializer);
	void NativePreConstruct() override;

protected:
	virtual void NativeConstruct() override;
	void SetupUIHierarchy();
	void BindEvents();
	UBaseButton* GetBackButton() const { return BackButton; }

	UFUNCTION()
	void OnDisplayButtonClicked();
	UFUNCTION()
	void OnGraphicsButtonClicked();
	UFUNCTION()
	void OnControlsButtonClicked();
	UFUNCTION()
	void OnAudioButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UOverlay* GeneralOverlay;
	UPROPERTY(meta = (BindWidget))
	class UBackgroundBlur* BackgroundBackgroundBlur;
	UPROPERTY(meta = (BindWidget))
	class UBorder* BackgroundBorder;
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* OptionsVerticalBox;
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* SettingsButtonsBox;
	UPROPERTY(meta = (BindWidget))
	UBaseButton* DisplayButton;
	UPROPERTY(meta = (BindWidget))
	UBaseButton* GraphicsButton;
	UPROPERTY(meta = (BindWidget))
	UBaseButton* ControlsButton;
	UPROPERTY(meta = (BindWidget))
	UBaseButton* AudioButton;
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* SettingsSwitcher;
	UPROPERTY(meta = (BindWidget))
	class USettingsDisplay* DisplaySettings;
	UPROPERTY(meta = (BindWidget))
	class USettingsGraphics* GraphicsSettings;
	UPROPERTY(meta = (BindWidget))
	class USettingsGraphics* ControlsSettings;
	UPROPERTY(meta = (BindWidget))
	class USettingsGraphics* AudioSettings;
	UPROPERTY(meta = (BindWidget))
	UBaseButton* BackButton;
};
