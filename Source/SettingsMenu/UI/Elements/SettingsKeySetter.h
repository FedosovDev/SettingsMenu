// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsKeySetter.generated.h"

class UOverlay;
class UHorizontalBox;
class UBorder;
class UTextBlock;
class UInputKeySelector;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKeySelectedDelegate, FInputChord, SelectedKey);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnIsSelectedKeyChangedDelegate);

UCLASS()
class SETTINGSMENU_API USettingsKeySetter : public UUserWidget
{
	GENERATED_BODY()
	
public:
    USettingsKeySetter(const FObjectInitializer& ObjectInitializer);
	void NativePreConstruct() override;
    UInputKeySelector* GetKeySelector() const { return KeySelector; }

    UPROPERTY(BlueprintAssignable)
    FOnKeySelectedDelegate OnKeySelectedDelegate;
    UPROPERTY(BlueprintAssignable)
    FOnIsSelectedKeyChangedDelegate OnIsSelectedKeyChangedDelegate;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText OptionTextToDisplay;

protected:
    virtual void NativeConstruct() override;
    void SetupUIHierarchy();
    void BindEvents();
    UFUNCTION()
    void OnKeySelectedHandler(FInputChord InSelectedKey);
    UFUNCTION()
    void OnIsSelectedKeyChangedHandler();

    UPROPERTY(meta = (BindWidget))
    UOverlay* GeneralOverlay;
    UPROPERTY(meta = (BindWidget))
    UBorder* InnerBorder;
    UPROPERTY(meta = (BindWidget))
    UBorder* OuterBorder;
    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* OptionHorizontalBox;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* OptionTextBlock;
    UPROPERTY(meta = (BindWidget))
    UBorder* OptionBorder;
    UPROPERTY(meta = (BindWidget))
    UOverlay* KeySelectorOverlay;
    UPROPERTY(meta = (BindWidget))
    UBorder* KeySelectorBorder;
    UPROPERTY(meta = (BindWidget))
    UInputKeySelector* KeySelector;
};
