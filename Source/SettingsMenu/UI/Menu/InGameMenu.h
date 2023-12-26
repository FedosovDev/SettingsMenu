// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameMenu.generated.h"

UCLASS()
class SETTINGSMENU_API UInGameMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UInGameMenu(const FObjectInitializer& ObjectInitializer);
	void NativePreConstruct() override;

protected:
	virtual void NativeConstruct() override;
	void BindEvents();

	UFUNCTION()
	void OnContinueButtonClicked();
	UFUNCTION()
	void OnRestartButtonClicked();
	UFUNCTION()
	void OnSettingsButtonClicked();
	UFUNCTION()
	void OnMainMenuButtonClicked();
	UFUNCTION()
	void OnExitButtonClicked();

	UPROPERTY(meta = (BindWidget))
	UBaseButton* ContinueButton;
	UPROPERTY(meta = (BindWidget))
	UBaseButton* RestartButton;
	UPROPERTY(meta = (BindWidget))
	UBaseButton* SettingsButton;
	UPROPERTY(meta = (BindWidget))
	UBaseButton* MainMenuButton;
	UPROPERTY(meta = (BindWidget))
	UBaseButton* ExitButton;
};
