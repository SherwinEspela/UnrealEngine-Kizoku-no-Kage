// Copyright 2025 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "KNKPlayerController/KNKPCBase.h"
#include "KNKPCGameplay.generated.h"

class AKNKPlayer;
class UInputMappingContext;
class UInputAction;
class UEnhancedInputComponent;
class UKNKAnimInstancePlayer;
class UCharacterMovementComponent;
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
	// Called in Blueprints

	UFUNCTION(BlueprintCallable)
	void HandleWallHugWalkStopAnimStarted();

	UFUNCTION(BlueprintCallable)
	void HandleWallHugWalkStopAnimCompleted();

	UFUNCTION(BlueprintCallable)
	void HandlePeekToWallHugIdleCompleted();

	UFUNCTION(BlueprintCallable)
	void HandleWallPeekAnimCompleted();

	UFUNCTION(BlueprintCallable)
	void HandleWallHugWalkStoppedAtFacing(bool IsFacingLeft);

	UFUNCTION(BlueprintCallable)
	void HandleCrouchTransitionCompleted();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void WallPeek(const FInputActionValue& Value);
	void Restart();
	//void ToggleCrouch();
	void CrouchHold();
	void CrouchRelease();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Player Character")
	TObjectPtr<AKNKPlayer> PlayerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Player Anim Instance")
	TObjectPtr<UKNKAnimInstancePlayer> PlayerAnimInstance;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	UCharacterMovementComponent* MovementComponent;

protected:
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input")
	UInputAction* InputActionCrouch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input")
	UInputAction* InputActionCrouchPress;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Max Run Speed")
	float MaxRunSpeed = 500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Max Run Speed")
	float MaxCrouchSpeed = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Max Run Speed")
	float MaxWallHugWalkSpeed = 200.f;

private:
	UEnhancedInputComponent* EnhancedInputComponent;
	bool bCanWallPeek = false;
	bool bIsWallHugFacingLeft = false;
	bool bIsCrouchTransitioning = false;
};
