// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsSlider.generated.h"

class UHorizontalBox;
class UBorder;
class UTextBlock;
class USlider;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSliderValueChangedDelegate, float, NewValue);

UCLASS()
class SETTINGSMENU_API USettingsSlider : public UUserWidget
{
	GENERATED_BODY()

public:
    USettingsSlider(const FObjectInitializer& ObjectInitializer);
    void NativePreConstruct() override;
    void SetSliderValue(float NewValue);

    UPROPERTY(BlueprintAssignable)
    FOnSliderValueChangedDelegate OnSliderValueChangedDelegate;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText OptionTextToDisplay;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slider")
    float SliderMinValue;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slider")
    float SliderMaxValue;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slider")
    float SliderStepSizeValue;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slider")
    UMaterialInterface* SliderMaterial;
    UMaterialInstanceDynamic* DynamicMaterial;

protected:
    virtual void NativeConstruct() override;
    void SetupUIHierarchy();
    void BindEvents();
    void SetupSliderStyle();

    UFUNCTION()
    void OnSliderValueChanged(float NewValue);

    UPROPERTY(meta = (BindWidget))
    class UOverlay* GeneralOverlay;
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
    USlider* OptionSlider;
};
