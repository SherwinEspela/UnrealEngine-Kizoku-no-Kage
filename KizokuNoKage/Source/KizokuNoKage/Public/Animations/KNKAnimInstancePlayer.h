// Copyright 2025 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animations/KNKAnimInstanceBase.h"
#include "Enums/EnumStances.h"
#include "KNKAnimInstancePlayer.generated.h"

class AKNKCPlayerKosuke;
class UAnimMontage;

/**
 * 
 */
UCLASS()
class KIZOKUNOKAGE_API UKNKAnimInstancePlayer : public UKNKAnimInstanceBase
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

public:
	// Play Animations
	void PlayIdleStandToCrouchAnimation();
	void PlayIdleCrouchToStand();
	void PlayWallHugStandToCrouch();
	void PlayWallHugCrouchToStand();

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE ECharacterStances GetPlayerStance() const { return PlayerStance; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetPlayerStance(ECharacterStances Value) { PlayerStance = Value; }

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Player Character")
	TObjectPtr<AKNKCPlayerKosuke> PlayerCharacter;

	UPROPERTY(BlueprintReadWrite, Category = "Player Movement States")
	ECharacterStances PlayerStance = ECharacterStances::ECS_Stand;

protected:
	// Montages
	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage* MontageCrouch;
};
