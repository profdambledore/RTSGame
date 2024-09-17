// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerWidget.h"
#include "Game/SimulationController.h"
#include "Kismet/GameplayStatics.h"

void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SimStartButton->OnReleased.AddDynamic(this, &UPlayerWidget::OnPlayReleased);
	//SimEndButton->OnReleased.AddDynamic(this, &UPlayerWidget::OnEndReleased);
}

void UPlayerWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UPlayerWidget::ShowWinner(bool bBlueWin)
{
	StateSwitcher->SetActiveWidgetIndex(3);
	if (bBlueWin) {
		WinnerBox->SetText(FText::FromString(FString::Printf(TEXT("BLU WIN!"))));
	}
	else {
		WinnerBox->SetText(FText::FromString(FString::Printf(TEXT("RED WIN!"))));
	}
}

void UPlayerWidget::OnPlayReleased()
{
	Cast< ASimulationController>(UGameplayStatics::GetActorOfClass(GetWorld(), ASimulationController::StaticClass()))->StartSimulation(this);
	StateSwitcher->SetActiveWidgetIndex(2);
}

void UPlayerWidget::OnEndReleased()
{
}
