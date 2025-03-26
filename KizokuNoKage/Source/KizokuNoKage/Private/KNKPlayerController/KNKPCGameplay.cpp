// Copyright 2025 Sherwin Espela. All rights reserved.


#include "KNKPlayerController/KNKPCGameplay.h"
#include "KNKCharacters/KNKPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"

void AKNKPCGameplay::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AKNKPlayer>(GetPawn());

	UEnhancedInputLocalPlayerSubsystem* PlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	PlayerSubsystem->AddMappingContext(InputMappingContext, 0);
}

void AKNKPCGameplay::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(InputActionMove, ETriggerEvent::Triggered, this, &AKNKPCGameplay::Move);
	EnhancedInputComponent->BindAction(InputActionLook, ETriggerEvent::Triggered, this, &AKNKPCGameplay::Look);
	EnhancedInputComponent->BindAction(InputActionRestart, ETriggerEvent::Triggered, this, &AKNKPCGameplay::Restart);
	//EnhancedInputComponent->BindAction(InputActionWallPeek, ETriggerEvent::Triggered, this, &AKNKPCGameplay::WallPeek);
}

void AKNKPCGameplay::Move(const FInputActionValue& Value)
{
	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_TakingCover) return;

	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	float MovementX = MovementVector.X;
	float MovementY = MovementVector.Y;

	if (bIsWallLeftEdgeReached && MovementX > 0.f)
	{
		MovementX = 0.f;
		MovementY = 0.f;
	}
	else if (bIsWallRightEdgeReached && MovementX < 0.f)
	{
		MovementX = 0.f;
		MovementY = 0.f;
	}

	/*if (MovementX > 0.f)
	{
		MovementX = 1.f;
	}
	else if (MovementX < 0.f)
	{
		MovementX = -1.f;
	}

	if (MovementY > 0.f)
	{
		MovementY = 1.f;
	}
	else if (MovementY < 0.f)
	{
		MovementY = -1.f;
	}*/

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	PlayerCharacter->AddMovementInput(RightDirection, MovementX);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	PlayerCharacter->AddMovementInput(ForwardDirection, MovementY);
}

void AKNKPCGameplay::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	PlayerCharacter->AddControllerYawInput(LookAxisVector.X);
	PlayerCharacter->AddControllerPitchInput(LookAxisVector.Y);
}

void AKNKPCGameplay::WallPeek(const FInputActionValue& Value)
{
	if (!bCanWallPeek) return;
	if (PlayerCharacter->GetPlayerMovementState() != EPlayerMovementStates::EPMS_WallHugging) return;

	const FVector2D MovementVector = Value.Get<FVector2D>();
	float MovementVectorX = MovementVector.X;
	float MovementVectorY = MovementVector.Y;

	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_WallPeeking)
	{

	}
	else {
		if (bIsWallRightEdgeReached)
		{
			if (!bIsWallHugFacingLeft)
			{
				// facing right
				UE_LOG(LogTemp, Warning, TEXT("Wall Peek Right......"));
				PlayerCharacter->SetPlayerMovementState(EPlayerMovementStates::EPMS_WallPeeking);
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Wall Peek cancelled......"));
				PlayerCharacter->SetPlayerMovementState(EPlayerMovementStates::EPMS_WallHugging);
				bCanWallPeek = false;
				bIsWallLeftEdgeReached = false;
				bIsWallRightEdgeReached = false;
			}
		}
		else if (bIsWallLeftEdgeReached)
		{
			if (bIsWallHugFacingLeft)
			{
				UE_LOG(LogTemp, Warning, TEXT("Wall Peek Left......"));
				PlayerCharacter->SetPlayerMovementState(EPlayerMovementStates::EPMS_WallPeeking);
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Wall Peek cancelled......"));
				PlayerCharacter->SetPlayerMovementState(EPlayerMovementStates::EPMS_WallHugging);
				bCanWallPeek = false;
				bIsWallLeftEdgeReached = false;
				bIsWallRightEdgeReached = false;
			}
		}
	}
}

void AKNKPCGameplay::Restart()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AKNKPCGameplay::HandleWallHugWalkStopAnimStarted()
{
	bCanWallPeek = false;
}

void AKNKPCGameplay::HandleWallHugWalkStopAnimCompleted()
{
	bCanWallPeek = true;
}

void AKNKPCGameplay::HandleWallHugWalkStoppedAtFacing(bool IsFacingLeft)
{
	bIsWallHugFacingLeft = IsFacingLeft;
}
