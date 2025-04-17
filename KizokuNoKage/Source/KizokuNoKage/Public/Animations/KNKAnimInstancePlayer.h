// Copyright 2025 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animations/KNKAnimInstanceBase.h"
#include "Enums/EnumPlayerMovementStates.h"
#include "Enums/EnumStances.h"
#include "KNKAnimInstancePlayer.generated.h"

class AKNKPlayer;
class UAnimMontage;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class KIZOKUNOKAGE_API UKNKAnimInstancePlayer : public UKNKAnimInstanceBase
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	// Play Animations
	void PlayIdleStandToCrouchAnimation();
	void PlayIdleCrouchToStand();
	void PlayWallHugStandToCrouch();
	void PlayWallHugCrouchToStand();
	void PlayWallPeekCancel(bool IsFacingLeft);

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE ECharacterStances GetPlayerStance() const { return PlayerStance; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetPlayerStance(ECharacterStances Value) { PlayerStance = Value; }

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Player Character")
	AKNKPlayer* PlayerCharacter;

	UPROPERTY(BlueprintReadWrite, Category = "Player Movement States")
	EPlayerMovementStates PlayerMovementState;

	UPROPERTY(BlueprintReadWrite, Category = "Player Movement States")
	ECharacterStances PlayerStance = ECharacterStances::ECS_Stand;

	/*UPROPERTY(BlueprintReadOnly, Category = "Player Character")
	UCharacterMovementComponent* CharacterMovementComp;*/

protected:
	// Montages
	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage* MontageCrouch;

	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage* MontageTakeCover;

	
};
