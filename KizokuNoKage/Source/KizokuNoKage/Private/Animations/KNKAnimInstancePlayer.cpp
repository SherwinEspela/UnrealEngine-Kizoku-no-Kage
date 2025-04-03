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

void UKNKAnimInstancePlayer::PlayWallPeekCancel(bool IsFacingLeft)
{
	if (!MontageTakeCover) return;

	FName SectionName = IsFacingLeft ? FName("WallpeekCancelLeft") : FName("WallpeekCancelRight");
	Montage_Play(MontageTakeCover);
	Montage_JumpToSection(SectionName, MontageTakeCover);
}
