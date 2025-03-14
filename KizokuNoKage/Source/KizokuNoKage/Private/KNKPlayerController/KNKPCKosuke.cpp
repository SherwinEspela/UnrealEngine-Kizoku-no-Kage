// Copyright 2025 Sherwin Espela. All rights reserved.


#include "KNKPlayerController/KNKPCKosuke.h"
#include "KNKCharacters/KNKCPlayerKosuke.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"

void AKNKPCKosuke::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AKNKCPlayerKosuke>(GetPawn());

	UEnhancedInputLocalPlayerSubsystem* PlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	PlayerSubsystem->AddMappingContext(InputMappingContext, 0);
}

void AKNKPCKosuke::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(InputActionMove, ETriggerEvent::Triggered, this, &AKNKPCKosuke::Move);
	EnhancedInputComponent->BindAction(InputActionLook, ETriggerEvent::Triggered, this, &AKNKPCKosuke::Look);
}

void AKNKPCKosuke::Interact()
{

}

void AKNKPCKosuke::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	if (bIsLookingAwayFromWallWhileWallHugging) return;
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	PlayerCharacter->AddMovementInput(RightDirection, MovementVector.X);

	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_WallHugging) return;
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	PlayerCharacter->AddMovementInput(ForwardDirection, MovementVector.Y);
}

void AKNKPCKosuke::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	PlayerCharacter->AddControllerYawInput(LookAxisVector.X);
	PlayerCharacter->AddControllerPitchInput(LookAxisVector.Y);
}
