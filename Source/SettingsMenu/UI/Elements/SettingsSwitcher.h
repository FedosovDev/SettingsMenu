// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsSwitcher.generated.h"

class UHorizontalBox;
class UBorder;
class UTextBlock;
class UBaseButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRightButtonClickedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeftButtonClickedDelegate);

UCLASS()
class SETTINGSMENU_API USettingsSwitcher : public UUserWidget
{
	GENERATED_BODY()

public:
    USettingsSwitcher(const FObjectInitializer& ObjectInitializer);
    void NativePreConstruct() override;
    void SetOptionsTextBlock(FText TextToDisplay);

    UPROPERTY(BlueprintAssignable)
    FOnRightButtonClickedDelegate OnRightButtonClickedDelegate;
    UPROPERTY(BlueprintAssignable)
    FOnLeftButtonClickedDelegate OnLeftButtonClickedDelegate;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText OptionTextToDisplay;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText OptionsTextToDisplay;

protected:
    virtual void NativeConstruct() override;
    void SetupUIHierarchy();
    void BindEvents();

    UFUNCTION()
    void OnRightButtonClicked();
    UFUNCTION()
    void OnLeftButtonClicked();

    UPROPERTY(meta = (BindWidget))
    class UOverlay* GeneralOverlay;
    UPROPERTY(meta = (BindWidget))
    UBorder* InnerBorder;
    UPROPERTY(meta = (BindWidget))
    UBorder* OuterBorder;
    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* OuterHorizontalBox;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* OptionTextBlock;
    UPROPERTY(meta = (BindWidget))
    UBorder* OptionBorder;
    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* InnerHorizontalBox;
    UPROPERTY(meta = (BindWidget))
    UBaseButton* LeftButton;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* OptionsTextBlock;
    UPROPERTY(meta = (BindWidget))
    UBaseButton* RightButton;

};
