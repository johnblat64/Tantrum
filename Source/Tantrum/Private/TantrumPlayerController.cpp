// Fill out your copyright notice in the Description page of Project Settings.


#include "TantrumPlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TantrumCharacterBase.h"
#include "../TantrumGameModeBase.h"

static TAutoConsoleVariable<bool> CVarDisplayLaunchInputDelta(
	TEXT("Tantrum.Character.Debug.DisplayLaunchInputDelta"),
	false,
	TEXT("Display Launch Input Delta"),
	ECVF_Default);

void ATantrumPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
	{
		InputComponent->BindAxis(TEXT("MoveForward"),
			this,
			&ATantrumPlayerController::RequestMoveForward);
		InputComponent->BindAxis(TEXT("MoveRight"),
			this,
			&ATantrumPlayerController::RequestMoveRight);
		InputComponent->BindAxis(TEXT("LookUp"),
			this,
			&ATantrumPlayerController::RequestLookUp);
		InputComponent->BindAxis(TEXT("LookRight"),
			this,
			&ATantrumPlayerController::RequestLookRight);
		InputComponent->BindAction(TEXT("Jump"),
			EInputEvent::IE_Pressed,
			this,
			&ATantrumPlayerController::RequestJumpStart);
		InputComponent->BindAction(TEXT("Jump"),
			EInputEvent::IE_Released,
			this,
			&ATantrumPlayerController::RequestJumpStop);
		InputComponent->BindAction(TEXT("Crouch"),
			EInputEvent::IE_Pressed,
			this,
			&ATantrumPlayerController::RequestCrouchStart);
		InputComponent->BindAction(TEXT("Crouch"),
			EInputEvent::IE_Released,
			this,
			&ATantrumPlayerController::RequestCrouchStop);
		InputComponent->BindAction(TEXT("Sprint"),
			EInputEvent::IE_Pressed,
			this,
			&ATantrumPlayerController::RequestSprintStart);
		InputComponent->BindAction(TEXT("Sprint"),
			EInputEvent::IE_Released,
			this,
			&ATantrumPlayerController::RequestSprintStop);
		InputComponent->BindAction(TEXT("PullObject"),
			EInputEvent::IE_Pressed,
			this,
			&ATantrumPlayerController::RequestPullObjectStart);
		InputComponent->BindAction(TEXT("PullObject"),
			EInputEvent::IE_Released,
			this,
			&ATantrumPlayerController::RequestPullObjectStop);
		InputComponent->BindAction(TEXT("ThrowObjectMouse"),
			EInputEvent::IE_Pressed,
			this,
			&ATantrumPlayerController::RequestThrowObject);
		InputComponent->BindAxis(TEXT("ThrowObjectGP"),
			this,
			&ATantrumPlayerController::RequestThrowObject);
	}
}

void ATantrumPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GameModeRef = Cast<ATantrumGameModeBase>(GetWorld()->GetAuthGameMode());

	//if (HUDClass)
	//{
		//HUDWidget = CreateWidget(this, HUDClass);
		//if (HUDWidget)
		//{
			//HUDWidget->AddToViewport();
		//}
	//}

	if (GetCharacter())
	{
		DefaultWalkSpeed = GetCharacter()->GetCharacterMovement()->MaxWalkSpeed;
	}
}

void ATantrumPlayerController::RequestMoveForward(float AxisValue)
{
	if (!GameModeRef || GameModeRef->GetCurrentGameState() != EGameState::Playing) { return; }
	if (AxisValue == 0.0f) { return; }

	FRotator const ControlSpaceRot = GetControlRotation();
	GetPawn()->AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), AxisValue);
}

void ATantrumPlayerController::RequestMoveRight(float AxisValue)
{
	if (!GameModeRef || GameModeRef->GetCurrentGameState() != EGameState::Playing) { return; }
	if (AxisValue == 0.0f) { return; }

	FRotator const ControlSpaceRot = GetControlRotation();
	GetPawn()->AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), AxisValue);
}

void ATantrumPlayerController::RequestLookUp(float AxisValue)
{
	AddPitchInput(AxisValue * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATantrumPlayerController::RequestLookRight(float AxisValue)
{
	AddYawInput(AxisValue * BaseLookRightRate * GetWorld()->GetDeltaSeconds());
}

void ATantrumPlayerController::RequestJumpStart()
{
	if (!GameModeRef || GameModeRef->GetCurrentGameState() != EGameState::Playing) { return; }

	if (GetCharacter())
	{
		GetCharacter()->Jump();
	}
}

void ATantrumPlayerController::RequestJumpStop()
{
	if (GetCharacter())
	{
		GetCharacter()->StopJumping();
	}
}

void ATantrumPlayerController::RequestCrouchStart()
{
	if (!GameModeRef || GameModeRef->GetCurrentGameState() != EGameState::Playing) { return; }

	if (!GetCharacter()->GetCharacterMovement()->IsMovingOnGround()) { return; }
	if (GetCharacter())
	{
		GetCharacter()->Crouch();
	}
}

void ATantrumPlayerController::RequestCrouchStop()
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

void ATantrumPlayerController::RequestSprintStop()
{
	if (GetCharacter())
	{
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	}
}

void ATantrumPlayerController::RequestThrowObject()
{
	if (ATantrumCharacterBase* TantrumCharacterBase = Cast<ATantrumCharacterBase>(GetCharacter()))
	{
		TantrumCharacterBase->RequestThrowObject();
	}
}

void ATantrumPlayerController::RequestThrowObject(float AxisValue)
{
	if (ATantrumCharacterBase* TantrumCharacterBase = Cast<ATantrumCharacterBase>(GetCharacter()))
	{
		if (TantrumCharacterBase->CanThrowObject())
		{
			float currentDelta = AxisValue = LastAxis;

			//debug
			if (CVarDisplayLaunchInputDelta->GetBool())
			{
				if (fabs(currentDelta) > 0.0f)
				{
					UE_LOG(LogTemp, Warning, TEXT("Axis: %f currentDelta %f"), AxisValue, LastAxis);
				}
			}
			LastAxis = AxisValue;
			const bool IsFlick = fabs(currentDelta) > FlickThreshold;
			if (IsFlick)
			{
				TantrumCharacterBase->RequestThrowObject();
			}
		}
		else
		{
			LastAxis = 0.0f;
		}
	}
}

void ATantrumPlayerController::RequestPullObjectStart()
{
	if (ATantrumCharacterBase* TantrumCharacterBase = Cast<ATantrumCharacterBase>(GetCharacter()))
	{
		TantrumCharacterBase->RequestPullObjectStart();
	}
}

void ATantrumPlayerController::RequestPullObjectStop()
{
	if (ATantrumCharacterBase* TantrumCharacterBase = Cast<ATantrumCharacterBase>(GetCharacter()))
	{
		TantrumCharacterBase->RequestPullObjectStop();
	}
}
