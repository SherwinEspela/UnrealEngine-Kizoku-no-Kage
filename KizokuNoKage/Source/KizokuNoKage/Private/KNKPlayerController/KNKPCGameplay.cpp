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
}

void AKNKPCGameplay::Move(const FInputActionValue& Value)
{
	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_TakingCover) return;

	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	if (PlayerCharacter->GetPlayerMovementState() != EPlayerMovementStates::EPMS_WallHugging)
	{
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		PlayerCharacter->AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	float MovementVectorX = MovementVector.X;
	UE_LOG(LogTemp, Warning, TEXT("Movement Vector X ==== %f"), MovementVector.X);
	
	if (bIsWallRightEdgeReached && MovementVectorX < 0.f)
	{
		MovementVectorX = 0.f;
	}
	else if (bIsWallLeftEdgeReached && MovementVectorX > 0.f)
	{
		MovementVectorX = 0.f;
	}

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	PlayerCharacter->AddMovementInput(RightDirection, MovementVectorX);
}

void AKNKPCGameplay::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	PlayerCharacter->AddControllerYawInput(LookAxisVector.X);
	PlayerCharacter->AddControllerPitchInput(LookAxisVector.Y);
}

void AKNKPCGameplay::Restart()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
