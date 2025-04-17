// Copyright 2025 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "KNKCharacters/KNKCharacterBase.h"
#include "Enums/EnumPlayerMovementStates.h"
#include "Enums/EnumStances.h"
#include "KNKPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;

/**
 * 
 */
UCLASS()
class KIZOKUNOKAGE_API AKNKPlayer : public AKNKCharacterBase
{
	GENERATED_BODY()
public:
	AKNKPlayer();

public:
	UFUNCTION(BlueprintImplementableEvent)
	void HandlePlayerWallPeekRight();

	UFUNCTION(BlueprintImplementableEvent)
	void HandlePlayerWallPeekLeft();

	UFUNCTION(BlueprintImplementableEvent)
	void HandlePlayerWallPeekCancel();

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE EPlayerMovementStates GetPlayerMovementState() const { return PlayerMovementState; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetPlayerMovementState(EPlayerMovementStates Value) { PlayerMovementState = Value; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE ECharacterStances GetPlayerStance() const { return PlayerStance; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetPlayerStance(ECharacterStances Value) { PlayerStance = Value; }

protected:
	virtual void BeginPlay() override;

protected:
	// Player States
	UPROPERTY(BlueprintReadWrite, Category = "Player Movement States")
	EPlayerMovementStates PlayerMovementState = EPlayerMovementStates::EPMS_Default;

	UPROPERTY(BlueprintReadWrite, Category = "Player Movement States")
	ECharacterStances PlayerStance = ECharacterStances::ECS_Stand;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Setup")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Setup")
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arrow Wall Detector")
	TObjectPtr<UArrowComponent> ArrowWallDetector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arrow Wall Detector")
	TObjectPtr<UArrowComponent> ArrowWallDetectorLeft;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arrow Wall Detector")
	TObjectPtr<UArrowComponent> ArrowWallDetectorRight;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Can Stealth Attack")
	bool bCanStealthAttack = false;
};
