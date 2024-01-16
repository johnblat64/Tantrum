// Copyright Epic Games, Inc. All Rights Reserved.


#include "TantrumGameModeBase.h"

ATantrumGameModeBase::ATantrumGameModeBase()
{
}

void ATantrumGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentGameState = EGameState::Waiting;
	DisplayCountdown();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATantrumGameModeBase::StartGame, GameCountdownDuration, false);
}

EGameState ATantrumGameModeBase::GetCurrentGameState()
{
	return CurrentGameState;
}

void ATantrumGameModeBase::PlayerReachedEnd()
{
	CurrentGameState = EGameState::GameOver;
}

void ATantrumGameModeBase::DisplayCountdown()
{

}

void ATantrumGameModeBase::StartGame()
{
	CurrentGameState = EGameState::Playing;
}

