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

	// Called in WallHug Component Blueprint
	UFUNCTION(BlueprintCallable)
	void HandleAdjustTakeCoverPosition(bool IsLeftSideWall);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void WallPeek(const FInputActionValue& Value);
	void Climb(const FInputActionValue& Value);
	void Restart();
	void ToggleCrouch();
	void CrouchHold();
	void CrouchRelease();
	//void Jump();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Player Character")
	TObjectPtr<AKNKPlayer> PlayerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Player Anim Instance")
	TObjectPtr<UKNKAnimInstancePlayer> PlayerAnimInstance;

	UPROPERTY(BlueprintReadWrite, Category = Movement)
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
	UInputAction* InputActionClimb;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input")
	UInputAction* InputActionCrouch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input")
	UInputAction* InputActionCrouchPress;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input")
	UInputAction* InputActionJump;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wall Hug Speed")
	float MovementSpeedX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wall Hug Speed")
	float MovementSpeedY;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wall Hug Speed")
	float WallHugMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall Edge")
	bool bIsWallLeftEdgeReached = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall Edge")
	bool bIsWallRightEdgeReached = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Max Run Speed")
	float MaxRunSpeed = 450.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Max Run Speed")
	float MaxCrouchSpeed = 220.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Max Run Speed")
	float MaxWallHugWalkSpeed = 200.f;

	UPROPERTY(BlueprintReadWrite, Category = "Wall Hug Facing")
	bool bIsWallHugFacingLeft = false;

	UPROPERTY(BlueprintReadWrite, Category = "Can Wall Peek")
	bool bCanWallPeek = false;

private:
	UEnhancedInputComponent* EnhancedInputComponent;
	bool bIsCrouchTransitioning = false;
};
