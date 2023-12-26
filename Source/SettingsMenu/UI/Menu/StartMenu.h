// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenu.generated.h"

class UBaseButton;

UCLASS()
class SETTINGSMENU_API UStartMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UStartMenu(const FObjectInitializer& ObjectInitializer);
	void NativePreConstruct() override;

protected:
	virtual void NativeConstruct() override;
	void BindEvents();

	UFUNCTION()
	void OnPlayButtonClicked();
	UFUNCTION()
	void OnSettingsButtonClicked();
	UFUNCTION()
	void OnExitButtonClicked();

	UPROPERTY(meta = (BindWidget))
	UBaseButton* PlayButton;
	UPROPERTY(meta = (BindWidget))
	UBaseButton* SettingsButton;
	UPROPERTY(meta = (BindWidget))
	UBaseButton* ExitButton;
};
