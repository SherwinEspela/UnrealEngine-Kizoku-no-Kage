// Copyright 2025 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "KNKPlayerController/KNKPCBase.h"
#include "KNKPCGameplay.generated.h"

class AKNKPlayer;
class UInputMappingContext;
class UInputAction;
class UEnhancedInputComponent;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class KIZOKUNOKAGE_API AKNKPCGameplay : public AKNKPCBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetWallLeftEdgeReached(bool Value) { bIsWallLeftEdgeReached = Value; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetWallRightEdgeReached(bool Value) { bIsWallRightEdgeReached = Value; }
	
public:
	UFUNCTION(BlueprintCallable)
	void HandleWallHugWalkStopAnimStarted();

	UFUNCTION(BlueprintCallable)
	void HandleWallHugWalkStopAnimCompleted();

	UFUNCTION(BlueprintCallable)
	void HandleWallHugWalkStoppedAtFacing(bool IsFacingLeft);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void WallPeek(const FInputActionValue& Value);
	void Restart();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Player Character")
	TObjectPtr<AKNKPlayer> PlayerCharacter;
	
	// Player Inputs
	UPROPERTY(EditDefaultsOnly, Category = "Player Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input")
	UInputAction* InputActionMove;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input")
	UInputAction* InputActionLook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input")
	UInputAction* InputActionRestart;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input")
	UInputAction* InputActionWallPeek;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wall Hug Speed")
	float MovementSpeedX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wall Hug Speed")
	float MovementSpeedY;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wall Hug Speed")
	float WallHugMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wall Edge")
	bool bIsWallLeftEdgeReached = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wall Edge")
	bool bIsWallRightEdgeReached = false;

private:
	UEnhancedInputComponent* EnhancedInputComponent;
	bool bCanWallPeek = false;
	bool bIsWallHugFacingLeft = false;
};
