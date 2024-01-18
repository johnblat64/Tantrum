// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "../TantrumGameModeBase.h"
#include "TantrumGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class TANTRUM_API UTantrumGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void StartCountdown(float CountdownTime, class ATantrumGameModeBase* GameMode);

	UFUNCTION(BlueprintImplementableEvent)
	void LevelComplete();
	
};
