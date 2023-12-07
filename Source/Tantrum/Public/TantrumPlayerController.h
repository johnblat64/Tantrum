// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Sound/SoundCue.h"
#include "TantrumPlayerController.generated.h"

class ATantrumGameModeBase;
class UUserWidget;

/**
 *
 */
UCLASS()
class TANTRUM_API ATantrumPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	void RequestMoveForward(float AxisValue);
	void RequestMoveRight(float AxisValue);
	void RequestLookUp(float AxisValue);
	void RequestLookRight(float AxisValue);
	void RequestJumpStart();
	void RequestJumpStop();

	void RequestCrouchStart();
	void RequestCrouchStop();

	void RequestSprintStart();
	void RequestSprintStop();

	void RequestThrowObject();

	void RequestThrowObject(float AxisValue);

	void RequestPullObjectStart();
	void RequestPullObjectStop();

	//UPROPERTY(EditAnywhere, Category = "HUD")
	//TSubclassOf<class UUserWidget> HUDClass;

	//UPROPERTY()
	//UUserWidget* HUDWidget;

	UPROPERTY(EditAnywhere, Category = "Look")
		float BaseLookUpRate = 90.0f;

	UPROPERTY(EditAnywhere, Category = "Look")
		float BaseLookRightRate = 90.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float SprintSpeed = 1800.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		float DefaultWalkSpeed = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundCue* JumpSound = nullptr;

	ATantrumGameModeBase* GameModeRef;

	// used to determine flick of axis
	float LastAxis = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Input")
		float FlickThreshold = 0.75f;
};
