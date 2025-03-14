// Copyright 2025 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "KNKPlayerController/KNKPCBase.h"
#include "KNKPCKosuke.generated.h"

class AKNKCPlayerKosuke;
class UInputMappingContext;
class UInputAction;
class UEnhancedInputComponent;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class KIZOKUNOKAGE_API AKNKPCKosuke : public AKNKPCBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetLookingAwayFromWallWhileWallHugging(bool Value) { bIsLookingAwayFromWallWhileWallHugging = Value; }

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void Interact();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Player Character")
	TObjectPtr<AKNKCPlayerKosuke> PlayerCharacter;	
	
	// Player Inputs
	UPROPERTY(EditDefaultsOnly, Category = "Player Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input")
	UInputAction* InputActionInteract;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input")
	UInputAction* InputActionMove;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input")
	UInputAction* InputActionLook;

private:
	UEnhancedInputComponent* EnhancedInputComponent;
	bool bIsLookingAwayFromWallWhileWallHugging = false;
};
