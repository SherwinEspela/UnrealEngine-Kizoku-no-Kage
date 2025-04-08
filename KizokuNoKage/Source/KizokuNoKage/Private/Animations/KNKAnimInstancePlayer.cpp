// Copyright 2025 Sherwin Espela. All rights reserved.


#include "Animations/KNKAnimInstancePlayer.h"
//#include "KNKCharacters/KNKCPlayerKosuke.h"
#include "KNKCharacters/KNKPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UKNKAnimInstancePlayer::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PlayerCharacter = Cast<AKNKPlayer>(TryGetPawnOwner());
	PlayerStance = ECharacterStances::ECS_Stand;
	PlayerMovementState = EPlayerMovementStates::EPMS_Idling;

	UE_LOG(LogTemp, Warning, TEXT("UKNKAnimInstancePlayer::NativeInitializeAnimation...."));

	if (PlayerCharacter)
	{
		CharacterMovementComp = PlayerCharacter->GetCharacterMovement();
	}
}

void UKNKAnimInstancePlayer::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (CharacterMovementComp)
	{
		MovementSpeed2D = UKismetMathLibrary::VSizeXY(CharacterMovementComp->Velocity);
	}
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
