// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonHovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonUnhovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonReleased);

UCLASS()
class SETTINGSMENU_API UBaseButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UBaseButton(const FObjectInitializer& ObjectInitializer);
    void NativePreConstruct();
    UFUNCTION()
    void OnButtonClicked();
    UFUNCTION()
    void OnButtonHovered();
    UFUNCTION()
    void OnButtonUnhovered();
    UFUNCTION()
    void OnButtonPressed();
    UFUNCTION()
    void OnButtonReleased();

    UPROPERTY(BlueprintAssignable)
    FOnButtonClicked OnButtonClickedDelegate;
    UPROPERTY(BlueprintAssignable)
    FOnButtonHovered OnButtonHoveredDelegate;
    UPROPERTY(BlueprintAssignable)
    FOnButtonUnhovered OnButtonUnhoveredDelegate;
    UPROPERTY(BlueprintAssignable)
    FOnButtonPressed OnButtonPressedDelegate;
    UPROPERTY(BlueprintAssignable)
    FOnButtonReleased OnButtonReleasedDelegate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText ButtonTextToDisplay;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InnerBorderTopPadding;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InnerBorderBottomPadding;

protected:
    virtual void NativeConstruct() override;
    void SetupUIHierarchy();
    void BindEvents();

    UPROPERTY(meta = (BindWidget))
    class UButton* VolumeButton;
    UPROPERTY(meta = (BindWidget))
    class UOverlay* GeneralOverlay;
    UPROPERTY(meta = (BindWidget))
    class UBorder* InnerBorder;
    UPROPERTY(meta = (BindWidget))
    class UBorder* OuterBorder;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ButtonTextBlock;

};
