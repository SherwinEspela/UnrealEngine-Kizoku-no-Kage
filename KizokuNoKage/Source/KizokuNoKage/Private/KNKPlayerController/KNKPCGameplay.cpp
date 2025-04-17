// Copyright 2025 Sherwin Espela. All rights reserved.


#include "KNKPlayerController/KNKPCGameplay.h"
#include "KNKCharacters/KNKPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "Animations/KNKAnimInstancePlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

void AKNKPCGameplay::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AKNKPlayer>(GetPawn());

	if (PlayerCharacter)
	{
		PlayerAnimInstance = Cast<UKNKAnimInstancePlayer>(PlayerCharacter->GetMesh()->GetAnimInstance());
		MovementComponent = PlayerCharacter->GetCharacterMovement();
	}
	
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
	EnhancedInputComponent->BindAction(InputActionWallPeek, ETriggerEvent::Triggered, this, &AKNKPCGameplay::WallPeek);
	EnhancedInputComponent->BindAction(InputActionCrouchPress, ETriggerEvent::Started, this, &AKNKPCGameplay::CrouchHold);
	EnhancedInputComponent->BindAction(InputActionCrouchPress, ETriggerEvent::Triggered, this, &AKNKPCGameplay::CrouchRelease);
	EnhancedInputComponent->BindAction(InputActionCrouchPress, ETriggerEvent::Canceled, this, &AKNKPCGameplay::CrouchRelease);
	//EnhancedInputComponent->BindAction(InputActionJump, ETriggerEvent::Triggered, this, &AKNKPCGameplay::Jump);
	EnhancedInputComponent->BindAction(InputActionClimb, ETriggerEvent::Triggered, this, &AKNKPCGameplay::Climb);
}

void AKNKPCGameplay::Move(const FInputActionValue& Value)
{
	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_WallPeeking) return;
	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_TakingCover) return;
	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_Climbing) return;
	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_WallJumping) return;
	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_ClimbingUp) return;
	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_StealthAttacking) return;

	if (bIsCrouchTransitioning) return;

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

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	PlayerCharacter->AddMovementInput(RightDirection, MovementX);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	PlayerCharacter->AddMovementInput(ForwardDirection, MovementY);
}

void AKNKPCGameplay::Look(const FInputActionValue& Value)
{
	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_UnHuggingWall) return;
	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_StealthAttacking) return;

	FVector2D LookAxisVector = Value.Get<FVector2D>();
	PlayerCharacter->AddControllerYawInput(LookAxisVector.X);
	PlayerCharacter->AddControllerPitchInput(LookAxisVector.Y);
}

void AKNKPCGameplay::WallPeek(const FInputActionValue& Value)
{
	if (!(bIsWallRightEdgeReached || bIsWallLeftEdgeReached)) return;

	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_WallHugging ||
		PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_WallPeeking) {

		

		const FVector2D MovementVector = Value.Get<FVector2D>();
		float MovementX = MovementVector.X;

		if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_WallPeeking)
		{
			if (bIsWallRightEdgeReached && !bIsWallHugFacingLeft && MovementX > 0.f)
			{
				UE_LOG(LogTemp, Warning, TEXT("AKNKPCGameplay::Facing Right...."));

				// facing right
				PlayerCharacter->HandlePlayerWallPeekCancel();
				//bCanWallPeek = false;
				bIsWallRightEdgeReached = false;
				bIsWallLeftEdgeReached = false;
			}
			else if (bIsWallLeftEdgeReached && bIsWallHugFacingLeft && MovementX < 0.f)
			{
				UE_LOG(LogTemp, Warning, TEXT("AKNKPCGameplay::Facing Left...."));

				// facing left
				PlayerCharacter->HandlePlayerWallPeekCancel();
				//bCanWallPeek = false;
				bIsWallRightEdgeReached = false;
				bIsWallLeftEdgeReached = false;
			}
		}
		else {
			if (bIsWallRightEdgeReached && !bIsWallHugFacingLeft && MovementX < 0.f)
			{
				// facing right
				PlayerCharacter->SetPlayerMovementState(EPlayerMovementStates::EPMS_WallPeeking);
				PlayerCharacter->HandlePlayerWallPeekRight();
				//bCanWallPeek = false;
			}
			else if (bIsWallLeftEdgeReached && bIsWallHugFacingLeft && MovementX > 0.f)
			{
				// facing left
				PlayerCharacter->SetPlayerMovementState(EPlayerMovementStates::EPMS_WallPeeking);
				PlayerCharacter->HandlePlayerWallPeekLeft();
				//bCanWallPeek = false;
			}
		}
	}
}

void AKNKPCGameplay::Climb(const FInputActionValue& Value)
{
	if (PlayerCharacter->GetPlayerMovementState() != EPlayerMovementStates::EPMS_Climbing) return;
	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_ClimbingUp) return;
	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_StealthAttacking) return;

	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	float MovementX = MovementVector.X;
	float MovementY = MovementVector.Y;

	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), MovementX);
}

void AKNKPCGameplay::Restart()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

//void AKNKPCGameplay::ToggleCrouch()
//{
//	if (bIsCrouchTransitioning) return;
//
//	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_Idling)
//	{
//		bIsCrouchTransitioning = true;
//	}
//
//	if (PlayerAnimInstance->GetPlayerStance() == ECharacterStances::ECS_Stand)
//	{
//		PlayerAnimInstance->SetPlayerStance(ECharacterStances::ECS_Crouch);
//		
//		switch (PlayerCharacter->GetPlayerMovementState())
//		{
//			case EPlayerMovementStates::EPMS_Idling:
//			PlayerAnimInstance->PlayIdleStandToCrouchAnimation();
//			MovementComponent->MaxWalkSpeed = MaxCrouchSpeed;
//			MovementComponent->MinAnalogWalkSpeed = MaxCrouchSpeed;
//			break;
//
//			case EPlayerMovementStates::EPMS_Moving:
//				MovementComponent->MaxWalkSpeed = MaxCrouchSpeed;
//				MovementComponent->MinAnalogWalkSpeed = MaxCrouchSpeed;
//				break;
//
//			case EPlayerMovementStates::EPMS_WallHugging:
//			PlayerAnimInstance->PlayWallHugStandToCrouch();
//			MovementComponent->MaxWalkSpeed = MaxWallHugWalkSpeed;
//			MovementComponent->MinAnalogWalkSpeed = MaxWallHugWalkSpeed;
//			break;
//
//			default:
//			break;
//		}
//	}
//	else if (PlayerAnimInstance->GetPlayerStance() == ECharacterStances::ECS_Crouch) {
//		PlayerAnimInstance->SetPlayerStance(ECharacterStances::ECS_Stand);
//		
//		switch (PlayerCharacter->GetPlayerMovementState())
//		{
//		case EPlayerMovementStates::EPMS_Idling:
//			MovementComponent->MaxWalkSpeed = MaxRunSpeed;
//			MovementComponent->MinAnalogWalkSpeed = MaxRunSpeed;
//			PlayerAnimInstance->PlayIdleCrouchToStand();
//			break;
//
//		case EPlayerMovementStates::EPMS_Moving:
//			MovementComponent->MaxWalkSpeed = MaxRunSpeed;
//			MovementComponent->MinAnalogWalkSpeed = MaxRunSpeed;
//			break;
//
//		case EPlayerMovementStates::EPMS_WallHugging:
//			PlayerAnimInstance->PlayWallHugCrouchToStand();
//			MovementComponent->MaxWalkSpeed = MaxWallHugWalkSpeed;
//			MovementComponent->MinAnalogWalkSpeed = MaxWallHugWalkSpeed;
//			break;
//
//		default:
//			break;
//		}
//	}
//}

void AKNKPCGameplay::CrouchHold()
{
	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_WallHugging) return;
	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_Climbing) return;
	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_StealthAttacking) return;

	if (bIsCrouchTransitioning) return;
	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_Idling)
	{
		bIsCrouchTransitioning = true;
	}

	if (PlayerAnimInstance->GetPlayerStance() == ECharacterStances::ECS_Stand)
	{
		PlayerAnimInstance->SetPlayerStance(ECharacterStances::ECS_Crouch);

		switch (PlayerCharacter->GetPlayerMovementState())
		{
		case EPlayerMovementStates::EPMS_Idling:
			PlayerAnimInstance->PlayIdleStandToCrouchAnimation();
			MovementComponent->MaxWalkSpeed = MaxCrouchSpeed;
			MovementComponent->MinAnalogWalkSpeed = MaxCrouchSpeed;
			break;

		case EPlayerMovementStates::EPMS_Moving:
			MovementComponent->MaxWalkSpeed = MaxCrouchSpeed;
			MovementComponent->MinAnalogWalkSpeed = MaxCrouchSpeed;
			break;

		default:
			break;
		}
	}
}

void AKNKPCGameplay::CrouchRelease()
{	
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("AKNKPCGameplay::CrouchRelease...."));
	bIsWallRightEdgeReached = false;
	bIsWallLeftEdgeReached = false;

	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_WallPeeking)
	{
		PlayerCharacter->SetPlayerMovementState(EPlayerMovementStates::EPMS_UnpeekingWall);
		PlayerAnimInstance->PlayWallPeekCancel(bIsWallHugFacingLeft);
		PlayerCharacter->HandlePlayerWallPeekCancel();
		MovementComponent->MaxWalkSpeed = MaxRunSpeed;
		MovementComponent->MinAnalogWalkSpeed = MaxRunSpeed;
		return;
	}

	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_WallHugging) return;
	if (bIsCrouchTransitioning) return;
	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_Idling)
	{
		bIsCrouchTransitioning = true;
	}

	if (PlayerAnimInstance->GetPlayerStance() == ECharacterStances::ECS_Crouch) {
		PlayerAnimInstance->SetPlayerStance(ECharacterStances::ECS_Stand);

		switch (PlayerCharacter->GetPlayerMovementState())
		{
		case EPlayerMovementStates::EPMS_Idling:
			MovementComponent->MaxWalkSpeed = MaxRunSpeed;
			MovementComponent->MinAnalogWalkSpeed = MaxRunSpeed;
			PlayerAnimInstance->PlayIdleCrouchToStand();
			break;

		case EPlayerMovementStates::EPMS_Moving:
			MovementComponent->MaxWalkSpeed = MaxRunSpeed;
			MovementComponent->MinAnalogWalkSpeed = MaxRunSpeed;
			break;

		default:
			break;
		}
	}
}

//void AKNKPCGameplay::Jump()
//{
//	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_WallPeeking) return;
//	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_TakingCover) return;
//	if (PlayerCharacter->GetPlayerMovementState() == EPlayerMovementStates::EPMS_Crouching) return;
//
//	//PlayerCharacter->Jump();
//}

void AKNKPCGameplay::HandleWallHugWalkStopAnimStarted()
{
	bCanWallPeek = false;
}

void AKNKPCGameplay::HandleWallHugWalkStopAnimCompleted()
{
	//bCanWallPeek = true;
}

void AKNKPCGameplay::HandlePeekToWallHugIdleCompleted()
{
	//bCanWallPeek = true;
	PlayerCharacter->SetPlayerMovementState(EPlayerMovementStates::EPMS_WallHugging);
}

void AKNKPCGameplay::HandleWallPeekAnimCompleted()
{
	bCanWallPeek = true;
}

void AKNKPCGameplay::HandleWallHugWalkStoppedAtFacing(bool IsFacingLeft)
{
	bIsWallHugFacingLeft = IsFacingLeft;
}

void AKNKPCGameplay::HandleCrouchTransitionCompleted()
{
	bIsCrouchTransitioning = false;
}

void AKNKPCGameplay::HandleAdjustTakeCoverPosition(bool IsLeftSideWall)
{
	bIsWallHugFacingLeft = IsLeftSideWall;
	bIsWallRightEdgeReached = !IsLeftSideWall;
	bIsWallLeftEdgeReached = IsLeftSideWall;
}

// TODO: use this for setting the camera pitch limits
//void ASTPlayerCharacter::SetLimitsToCameraPitch()
//{
//	APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
//	PlayerCameraManager->ViewPitchMin = ViewPitchMin;
//	PlayerCameraManager->ViewPitchMax = ViewPitchMax;
//}
