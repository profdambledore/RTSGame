// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/WidgetSwitcher.h"
#include "Components/EditableText.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "PlayerWidget.generated.h"


UCLASS()
class RTSGAME_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	// Called to show the winner
	void ShowWinner(bool bBlueWin);

protected:
	// Button event to start the simulation
	UFUNCTION()
	void OnPlayReleased();

	// Button event to end the active simulation
	UFUNCTION()
	void OnEndReleased();

protected:
	/// -- Player Pointer --
	// Pointer to the player class which uses this UI
	class APlayer_Character* PC = nullptr;

	/// -- Components --
	// Widget switcher that allows the UI to swap between different states
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidgetSwitcher* StateSwitcher = nullptr;

	// Buttons
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* SimStartButton = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* WinnerBox;

	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Grid Snapping")
	//UButton* SimEndButton = nullptr;
	
};
