// Copyright 2025 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "KNKCharacters/KNKCharacterBase.h"
#include "Enums/EnumPlayerMovementStates.h"
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
	UFUNCTION(BlueprintCallable)
	FORCEINLINE EPlayerMovementStates GetPlayerMovementState() const { return PlayerMovementState; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetPlayerMovementState(EPlayerMovementStates Value) { PlayerMovementState = Value; }

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Camera Setup")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Setup")
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(BlueprintReadWrite, Category = "Player Movement States")
	EPlayerMovementStates PlayerMovementState = EPlayerMovementStates::EPMS_Default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arrow Wall Detector")
	TObjectPtr<UArrowComponent> ArrowWallDetector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arrow Wall Detector")
	TObjectPtr<UArrowComponent> ArrowWallDetectorLeft;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arrow Wall Detector")
	TObjectPtr<UArrowComponent> ArrowWallDetectorRight;
};
