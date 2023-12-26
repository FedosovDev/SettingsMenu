// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/Menu/InGameMenu.h"
#include "SettingsMenu/UI/Elements/BaseButton.h"
#include "Kismet/GameplayStatics.h"
#include "SettingsMenu/GameModes/BaseGameMode.h"
#include "Kismet/KismetSystemLibrary.h"

UInGameMenu::UInGameMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UInGameMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UInGameMenu::NativeConstruct()
{
	Super::NativeConstruct();
	BindEvents();
}

void UInGameMenu::BindEvents()
{
	if (ContinueButton)
	{
		ContinueButton->OnButtonClickedDelegate.AddDynamic(this, &UInGameMenu::OnContinueButtonClicked);
	}
	if (RestartButton)
	{
		RestartButton->OnButtonClickedDelegate.AddDynamic(this, &UInGameMenu::OnRestartButtonClicked);
	}
	if (SettingsButton)
	{
		SettingsButton->OnButtonClickedDelegate.AddDynamic(this, &UInGameMenu::OnSettingsButtonClicked);
	}
	if (ExitButton)
	{
		ExitButton->OnButtonClickedDelegate.AddDynamic(this, &UInGameMenu::OnExitButtonClicked);
	}
}

void UInGameMenu::OnContinueButtonClicked()
{
	UWorld* World = GetWorld();
	if (World)
	{
		ABaseGameMode* GameMode = Cast<ABaseGameMode>(UGameplayStatics::GetGameMode(World));
		if (GameMode)
		{
			GameMode->ClearPause();
		}
	}
}

void UInGameMenu::OnRestartButtonClicked()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(World);
		if (!CurrentLevelName.IsEmpty())
		{
			UGameplayStatics::OpenLevel(World, FName(*CurrentLevelName));
		}
	}
}

void UInGameMenu::OnSettingsButtonClicked()
{
}

void UInGameMenu::OnMainMenuButtonClicked()
{
	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, FName("MainMenuLevel"));
	}
}

void UInGameMenu::OnExitButtonClicked()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		UKismetSystemLibrary::QuitGame(World, nullptr, EQuitPreference::Quit, false);
	}
}
