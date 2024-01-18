// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TantrumGameWidget.h"
#include "TantrumGameModeBase.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	None UMETA(DisplayName = "None"),
	Waiting UMETA(DisplayName = "Waiting"),
	Playing UMETA(DisplayName = "Playing"),
	Paused UMETA(DisplayName = "Paused"),
	GameOver UMETA(DisplayName = "GameOver"),
};


/**
 * 
 */
UCLASS()
class TANTRUM_API ATantrumGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATantrumGameModeBase();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	EGameState GetCurrentGameState() const;
	void PlayerReachedEnd();

private:
	UPROPERTY(VisibleAnywhere, Category="States")
	EGameState CurrentGameState = EGameState::None;

	UPROPERTY(EditAnywhere, Category="Game Details")
	float GameCountdownDuration = 2.0f;

	FTimerHandle TimerHandle;

	UPROPERTY()
	UTantrumGameWidget* GameWidget;
	UPROPERTY(EditAnywhere, Category="Widget")
	TSubclassOf<UTantrumGameWidget> GameWidgetClass;

	APlayerController* PC = nullptr;

	void DisplayCountdown();
	void StartGame();
	
};
