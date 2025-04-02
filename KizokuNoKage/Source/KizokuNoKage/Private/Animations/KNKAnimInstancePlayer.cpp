// Copyright 2025 Sherwin Espela. All rights reserved.


#include "Animations/KNKAnimInstancePlayer.h"
#include "KNKCharacters/KNKCPlayerKosuke.h"

void UKNKAnimInstancePlayer::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PlayerCharacter = Cast<AKNKCPlayerKosuke>(TryGetPawnOwner());
	PlayerStance = ECharacterStances::ECS_Stand;
	PlayerMovementState = EPlayerMovementStates::EPMS_Idling;
}

void UKNKAnimInstancePlayer::PlayIdleStandToCrouchAnimation()
{
	if (!MontageCrouch) return;
	Montage_Play(MontageCrouch);
	Montage_JumpToSection("StandToCrouch");
}

void UKNKAnimInstancePlayer::PlayIdleCrouchToStand()
{
	if (!MontageCrouch) return;
	Montage_Play(MontageCrouch);
	Montage_JumpToSection("CrouchToStand");
}

void UKNKAnimInstancePlayer::PlayWallHugStandToCrouch()
{
	if (!MontageCrouch) return;
	Montage_Play(MontageCrouch);
	Montage_JumpToSection("WallHugStandToCrouch");
}

void UKNKAnimInstancePlayer::PlayWallHugCrouchToStand()
{
	if (!MontageCrouch) return;
	Montage_Play(MontageCrouch);
	Montage_JumpToSection(FName("WallHugCrouchToStand"), MontageCrouch);
}

void UKNKAnimInstancePlayer::PlayWallPeekCancel()
{
	if (!MontageTakeCover) return;

	//UE_LOG(LogTemp, Warning, TEXT("UKNKAnimInstancePlayer::PlayWallPeekCancel"));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("UKNKAnimInstancePlayer::PlayWallPeekCancel"));

	Montage_Play(MontageTakeCover);
	Montage_JumpToSection(FName("WallpeekCancelLeft"), MontageTakeCover);
}
