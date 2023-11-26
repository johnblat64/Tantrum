// Fill out your copyright notice in the Description page of Project Settings.


#include "TantrumPlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void ATantrumPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ATantrumPlayerController::RequestJump);
		InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, & ATantrumPlayerController::RequestStopJump);

		InputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &ATantrumPlayerController::RequestCrouchStart);
		InputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Released, this, &ATantrumPlayerController::RequestCrouchEnd);
		InputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &ATantrumPlayerController::RequestSprintStart);
		InputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &ATantrumPlayerController::RequestSprintEnd);

		InputComponent->BindAxis(TEXT("MoveForward"), this, &ATantrumPlayerController::RequestMoveForward);
		InputComponent->BindAxis(TEXT("MoveRight"), this, &ATantrumPlayerController::RequestMoveRight);
	
		InputComponent->BindAxis(TEXT("LookUp"), this, &ATantrumPlayerController::RequestLookUp);
		InputComponent->BindAxis(TEXT("LookRight"), this, &ATantrumPlayerController::RequestLookRight);
	}
}


void ATantrumPlayerController::RequestJump()
{
	if (GetCharacter())
	{
		GetCharacter()->Jump();
	}
}

void ATantrumPlayerController::RequestStopJump()
{
	if (GetCharacter())
	{
		GetCharacter()->StopJumping();
	}
}

void ATantrumPlayerController::RequestCrouchStart()
{
	if (!GetCharacter()->GetCharacterMovement()->IsMovingOnGround())
	{
		return;
	}

	if (GetCharacter())
	{
		GetCharacter()->Crouch();
	}
}

void ATantrumPlayerController::RequestCrouchEnd()
{
	if (GetCharacter())
	{
		GetCharacter()->UnCrouch();
	}
}

void ATantrumPlayerController::RequestSprintStart()
{
	if (GetCharacter())
	{
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void ATantrumPlayerController::RequestSprintEnd()
{
	if (GetCharacter())
	{
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	}
}

void ATantrumPlayerController::RequestMoveForward(float AxisValue)
{
	if (AxisValue != 0.f)
	{
		FRotator const ControlSpaceRot = GetControlRotation();
		GetPawn()->AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), AxisValue);
	}
}

void ATantrumPlayerController::RequestMoveRight(float AxisValue)
{
	if (AxisValue != 0.f)
	{
		FRotator const ControlSpaceRot = GetControlRotation();
		GetPawn()->AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), AxisValue);
	}
}

void ATantrumPlayerController::RequestLookUp(float AxisValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("AxisValueUp %.2f"), AxisValue);	
	AddPitchInput(AxisValue * BaseLookUpRate * GetWorld()->GetDeltaSeconds());

	//UE_LOG(LogTemp, Warning, TEXT("ControlRotationPitch %.2f"), GetPawn()->GetControlRotation().Pitch);
}

void ATantrumPlayerController::RequestLookRight(float AxisValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("AxisValueRight %.2f"), AxisValue);
	AddYawInput(AxisValue * BaseLookRightRate * GetWorld()->GetDeltaSeconds());
	//UE_LOG(LogTemp, Warning, TEXT("AxisValueRightAfterCalculation %.2f"), AxisValue * BaseLookRightRate * GetWorld()->GetDeltaSeconds());

}

