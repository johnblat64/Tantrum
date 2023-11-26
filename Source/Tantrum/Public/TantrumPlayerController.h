// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TantrumPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANTRUM_API ATantrumPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Look")
	float BaseLookUpRate = 90.0f;
	UPROPERTY(EditAnywhere, Category = "Look")
	float BaseLookRightRate = 90.0f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float SprintSpeed = 1200.0f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float DefaultWalkSpeed = 600.0f;
	
public:
	//void BeginPlay() override;
	void SetupInputComponent() override;
	void OnJumpAction();


	void RequestMoveForward(float AxisValue);
	void RequestMoveRight(float AxisValue);
	void RequestLookUp(float AxisValue);
	void RequestLookRight(float AxisValue);
	void RequestJump();
	void RequestStopJump();

	void RequestCrouchStart();
	void RequestCrouchEnd();

	void RequestSprintStart();
	void RequestSprintEnd();
};

