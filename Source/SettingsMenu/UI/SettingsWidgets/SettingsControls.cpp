// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/SettingsWidgets/SettingsControls.h"
#include "SettingsMenu/UI/Elements/SettingsSwitcher.h"
#include "SettingsMenu/UI/Elements/SettingsKeySetter.h"
#include "SettingsMenu/UI/Elements/SettingsSlider.h"
#include "SettingsMenu/UI/Elements/BaseButton.h"
#include "Components/VerticalBox.h"
#include "Components/ScrollBox.h"
#include "Components/Spacer.h"
#include "Components/InputKeySelector.h"

USettingsControls::USettingsControls(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MouseSensitivitySliderValue = 0.5f;
	bMouseXInvertation = false;
	bMouseYInvertation = false;
	MoveForwardMapping.AxisName = TEXT("MoveForward");
	MoveForwardMapping.Scale = 1.f;
	MoveForwardMapping.Key = EKeys::W;
	MoveBackwardMapping.AxisName = TEXT("MoveForward");
	MoveBackwardMapping.Scale = -1.f;
	MoveBackwardMapping.Key = EKeys::S;
	MoveRightMapping.AxisName = TEXT("MoveRight");
	MoveRightMapping.Scale = 1.f;
	MoveRightMapping.Key = EKeys::D;
	MoveLeftMapping.AxisName = TEXT("MoveRight");
	MoveLeftMapping.Scale = -1.f;
	MoveLeftMapping.Key = EKeys::A;
	JumpMappting.ActionName = TEXT("Jump");
	JumpMappting.Key = EKeys::A;
}

void USettingsControls::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void USettingsControls::NativeConstruct()
{
	Super::NativeConstruct();
	
	UCustomGameUserSettings* CustomSettings = UCustomGameUserSettings::GetCustomGameUserSettings();
	if (CustomSettings)
	{
		if (MouseSensitivitySlider)
		{
			MouseSensitivitySliderValue = CustomSettings->GetMouseSensitivityMultiplier();
			MouseSensitivitySlider->SetSliderValue(MouseSensitivitySliderValue);
		}
		if (MouseXInvertSwitcher)
		{
			bMouseXInvertation = CustomSettings->GetMouseXInvertation();
			SetSwitcherBoolOptionsText(MouseXInvertSwitcher, bMouseXInvertation);
		}
		if (MouseYInvertSwitcher)
		{
			bMouseYInvertation = CustomSettings->GetMouseYInvertation();
			SetSwitcherBoolOptionsText(MouseYInvertSwitcher, bMouseYInvertation);
		}
		SetKeySetterDefaultText(CustomSettings, MoveForwardKeySetter, MoveForwardMapping, TEXT("MoveForward"), 1.f);
		SetKeySetterDefaultText(CustomSettings, MoveBackwardKeySetter, MoveBackwardMapping, TEXT("MoveForward"), -1.f);
		SetKeySetterDefaultText(CustomSettings, MoveRightKeySetter, MoveRightMapping, TEXT("MoveRight"), 1.f);
		SetKeySetterDefaultText(CustomSettings, MoveLeftKeySetter, MoveLeftMapping, TEXT("MoveRight"), -1.f);
		SetKeySetterDefaultText(CustomSettings, JumpKeySetter, JumpMappting, TEXT("Jump"));
	}
}

void USettingsControls::SetupUIHierarchy()
{
	if (GeneralVerticalBox)
	{
		GeneralVerticalBox->AddChild(GeneralScrollBox);
		GeneralVerticalBox->AddChild(ApplySettingsButton);
	}
	if (GeneralScrollBox) GeneralScrollBox->AddChild(OptionsVerticalBox);
	if (OptionsVerticalBox)
	{
		OptionsVerticalBox->AddChild(MouseSensitivitySlider);
		OptionsVerticalBox->AddChild(MouseSensitivitySpacer);
		OptionsVerticalBox->AddChild(MouseXInvertSwitcher);
		OptionsVerticalBox->AddChild(MouseXInvertSpacer);
		OptionsVerticalBox->AddChild(MouseYInvertSwitcher);
		OptionsVerticalBox->AddChild(MouseYInvertSpacer);
		OptionsVerticalBox->AddChild(MoveForwardKeySetter);
		OptionsVerticalBox->AddChild(MoveForwardKeySpacer);
		OptionsVerticalBox->AddChild(MoveBackwardKeySetter);
		OptionsVerticalBox->AddChild(MoveBackwardKeySpacer);
		OptionsVerticalBox->AddChild(MoveRightKeySetter);
		OptionsVerticalBox->AddChild(MoveRightKeySpacer);
		OptionsVerticalBox->AddChild(MoveLeftKeySetter);
		OptionsVerticalBox->AddChild(MoveLeftKeySpacer);
		OptionsVerticalBox->AddChild(JumpKeySetter);
		OptionsVerticalBox->AddChild(JumpKeySpacer);
	}
}

void USettingsControls::BindEvents()
{
	if (MouseSensitivitySlider)
	{
		MouseSensitivitySlider->OnSliderValueChangedDelegate.AddDynamic(this, &USettingsControls::OnMouseSensSliderValueChanged);
	}
	if (MouseXInvertSwitcher)
	{
		MouseXInvertSwitcher->OnLeftButtonClickedDelegate.AddDynamic(this, &USettingsControls::OnMouseXInvertSwitcherLeftButtonClicked);
		MouseXInvertSwitcher->OnRightButtonClickedDelegate.AddDynamic(this, &USettingsControls::OnMouseXInvertSwitcherRightButtonClicked);
	}
	if (MouseYInvertSwitcher)
	{
		MouseXInvertSwitcher->OnLeftButtonClickedDelegate.AddDynamic(this, &USettingsControls::OnMouseYInvertSwitcherLeftButtonClicked);
		MouseXInvertSwitcher->OnRightButtonClickedDelegate.AddDynamic(this, &USettingsControls::OnMouseYInvertSwitcherRightButtonClicked);
	}
	if (MoveForwardKeySetter)
	{
		MoveForwardKeySetter->OnKeySelectedDelegate.AddDynamic(this, &USettingsControls::OnMoveForwardKeySelected);
	}
	if (MoveBackwardKeySetter)
	{
		MoveBackwardKeySetter->OnKeySelectedDelegate.AddDynamic(this, &USettingsControls::OnMoveBackwardKeySelected);
	}
	if (MoveRightKeySetter)
	{
		MoveRightKeySetter->OnKeySelectedDelegate.AddDynamic(this, &USettingsControls::OnMoveRightKeySelected);
	}
	if (MoveLeftKeySetter)
	{
		MoveLeftKeySetter->OnKeySelectedDelegate.AddDynamic(this, &USettingsControls::OnMoveLeftKeySelected);
	}
	if (JumpKeySetter)
	{
		JumpKeySetter->OnKeySelectedDelegate.AddDynamic(this, &USettingsControls::OnJumpKeySelected);
	}
	if (ApplySettingsButton)
	{
		ApplySettingsButton->OnButtonClickedDelegate.AddDynamic(this, &USettingsControls::OnApplySettingsButtonClicked);
	}
}

void USettingsControls::SetKeySetterDefaultText(UCustomGameUserSettings* CustomSettings, USettingsKeySetter* KeySetter, FInputAxisKeyMapping& Mapping, const FName& AxisName, float Scale)
{
	if (!CustomSettings) return;
	if (KeySetter)
	{
		if (GetInputAxisMappingByName(AxisName, Scale, Mapping))
		{
			UInputKeySelector* InputKeySelector = KeySetter->GetKeySelector();
			if (InputKeySelector)
			{
				InputKeySelector->SetNoKeySpecifiedText(Mapping.Key.GetDisplayName());
			}
		}
	}
}

void USettingsControls::SetKeySetterDefaultText(UCustomGameUserSettings* CustomSettings, USettingsKeySetter* KeySetter, FInputActionKeyMapping& Mapping, const FName& ActionName)
{
	if (!CustomSettings) return;
	if (KeySetter)
	{
		if (GetInputActionMappingByName(ActionName, Mapping))
		{
			UInputKeySelector* InputKeySelector = KeySetter->GetKeySelector();
			if (InputKeySelector)
			{
				InputKeySelector->SetNoKeySpecifiedText(Mapping.Key.GetDisplayName());
			}
		}
	}
}

void USettingsControls::SetSwitcherBoolOptionsText(USettingsSwitcher* Switcher, bool Condition)
{
	if (Switcher)
	{
		Condition ? Switcher->SetOptionsTextBlock(FText::FromString(TEXT("On"))) : Switcher->SetOptionsTextBlock(FText::FromString(TEXT("Off")));
	}
}

bool USettingsControls::GetInputAxisMappingByName(FName MappingName, float Scale, FInputAxisKeyMapping& OutMapping)
{
	UInputSettings* InputSettings = UInputSettings::GetInputSettings();
	if (InputSettings)
	{
		TArray<FInputAxisKeyMapping> Mappings;
		InputSettings->GetAxisMappingByName(MappingName, Mappings);
		for (const FInputAxisKeyMapping& AxisMapping : Mappings)
		{
			if (AxisMapping.Scale == Scale)
			{
				OutMapping = AxisMapping;
				return true;
			}
		}
	}
	return false;
}

bool USettingsControls::GetInputActionMappingByName(FName MappingName, FInputActionKeyMapping& OutMapping)
{
	UInputSettings* InputSettings = UInputSettings::GetInputSettings();
	if (InputSettings)
	{
		TArray<FInputActionKeyMapping> Mappings;
		InputSettings->GetActionMappingByName(MappingName, Mappings);
		if (Mappings.Num() > 0)
		{
			OutMapping = Mappings[0];
			return true;
		}
	}
	return false;
}

void USettingsControls::ChangeInputAxisMapping(const FInputAxisKeyMapping& InSelectedKey)
{
	UInputSettings* InputSettings = UInputSettings::GetInputSettings();
	if (InputSettings)
	{
		TArray<FInputAxisKeyMapping> AxisMappings;
		InputSettings->GetAxisMappingByName(InSelectedKey.AxisName, AxisMappings);

		for (const FInputAxisKeyMapping& AxisMapping : AxisMappings)
		{
			InputSettings->RemoveAxisMapping(AxisMapping);
		}
		InputSettings->AddAxisMapping(InSelectedKey);
		InputSettings->SaveKeyMappings();
		InputSettings->ForceRebuildKeymaps();
	}
}

void USettingsControls::ChangeInputActionMapping(const FInputActionKeyMapping& InSelectedKey)
{
	UInputSettings* InputSettings = UInputSettings::GetInputSettings();
	if (InputSettings)
	{
		TArray<FInputActionKeyMapping> ActionMappings;
		InputSettings->GetActionMappingByName(InSelectedKey.ActionName, ActionMappings);
		for (const FInputActionKeyMapping& ActionMapping : ActionMappings)
		{
			InputSettings->RemoveActionMapping(ActionMapping);
		}
		InputSettings->AddActionMapping(InSelectedKey);
		InputSettings->SaveKeyMappings();
		InputSettings->ForceRebuildKeymaps();
	}
}

void USettingsControls::OnMouseSensSliderValueChanged(float NewValue)
{
	MouseSensitivitySliderValue = NewValue;
}

void USettingsControls::OnMouseXInvertSwitcherLeftButtonClicked()
{
	bMouseXInvertation = false;
	SetSwitcherBoolOptionsText(MouseXInvertSwitcher, bMouseXInvertation);
}

void USettingsControls::OnMouseXInvertSwitcherRightButtonClicked()
{
	bMouseXInvertation = true;
	SetSwitcherBoolOptionsText(MouseXInvertSwitcher, bMouseXInvertation);
}

void USettingsControls::OnMouseYInvertSwitcherLeftButtonClicked()
{
	bMouseYInvertation = false;
	SetSwitcherBoolOptionsText(MouseYInvertSwitcher, bMouseYInvertation);
}

void USettingsControls::OnMouseYInvertSwitcherRightButtonClicked()
{
	bMouseYInvertation = true;
	SetSwitcherBoolOptionsText(MouseYInvertSwitcher, bMouseYInvertation);
}

void USettingsControls::OnMoveForwardKeySelected(FInputChord InSelectedKey)
{
	MoveForwardMapping.AxisName = TEXT("MoveForward");
	MoveForwardMapping.Scale = 1.f;
	MoveForwardMapping.Key = InSelectedKey.Key;
}

void USettingsControls::OnMoveBackwardKeySelected(FInputChord InSelectedKey)
{
	MoveBackwardMapping.AxisName = TEXT("MoveForward");
	MoveBackwardMapping.Scale = -1.f;
	MoveBackwardMapping.Key = InSelectedKey.Key;
}

void USettingsControls::OnMoveRightKeySelected(FInputChord InSelectedKey)
{
	MoveRightMapping.AxisName = TEXT("MoveRight");
	MoveRightMapping.Scale = 1.f;
	MoveRightMapping.Key = InSelectedKey.Key;
}

void USettingsControls::OnMoveLeftKeySelected(FInputChord InSelectedKey)
{
	MoveLeftMapping.AxisName = TEXT("MoveRight");
	MoveLeftMapping.Scale = -1.f;
	MoveLeftMapping.Key = InSelectedKey.Key;
}

void USettingsControls::OnJumpKeySelected(FInputChord InSelectedKey)
{
	JumpMappting.ActionName = TEXT("Jump");
	JumpMappting.Key = InSelectedKey.Key;
}

void USettingsControls::OnApplySettingsButtonClicked()
{
	UCustomGameUserSettings* CustomSettings = UCustomGameUserSettings::GetCustomGameUserSettings();
	if (CustomSettings)
	{
		CustomSettings->SetMouseSensitivityMultiplier(MouseSensitivitySliderValue);
		CustomSettings->SetMouseXInvertation(bMouseXInvertation);
		CustomSettings->SetMouseYInvertation(bMouseYInvertation);
		CustomSettings->ApplySettings(true);
	}
	ChangeInputAxisMapping(MoveForwardMapping);
	ChangeInputAxisMapping(MoveBackwardMapping);
	ChangeInputAxisMapping(MoveRightMapping);
	ChangeInputAxisMapping(MoveLeftMapping);
	ChangeInputActionMapping(JumpMappting);
}



