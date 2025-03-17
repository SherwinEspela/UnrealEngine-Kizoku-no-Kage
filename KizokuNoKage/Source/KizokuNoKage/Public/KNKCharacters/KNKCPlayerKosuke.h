// Copyright 2025 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "KNKCharacters/KNKCharacterBase.h"
#include "Enums/EnumPlayerMovementStates.h"
#include "KNKCPlayerKosuke.generated.h"

class UArrowComponent;

/**
 * 
 */
UCLASS()
class KIZOKUNOKAGE_API AKNKCPlayerKosuke : public AKNKCharacterBase
{
	GENERATED_BODY()
public:
	AKNKCPlayerKosuke();

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE EPlayerMovementStates GetPlayerMovementState() const { return PlayerMovementState; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetPlayerMovementState(EPlayerMovementStates Value) { PlayerMovementState = Value; }

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HealthTest;

	UPROPERTY(BlueprintReadWrite, Category = "Player Movement States")
	EPlayerMovementStates PlayerMovementState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arrow Wall Detector")
	TObjectPtr<UArrowComponent> ArrowWallDetector;
};
