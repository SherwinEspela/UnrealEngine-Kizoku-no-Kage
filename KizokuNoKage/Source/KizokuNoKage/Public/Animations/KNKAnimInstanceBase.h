// Copyright 2025 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "KNKAnimInstanceBase.generated.h"

class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class KIZOKUNOKAGE_API UKNKAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Character Movement Component")
	UCharacterMovementComponent* CharacterMovementComp;

	UPROPERTY(BlueprintReadOnly, Category = "Movement Speed 2D")
	float MovementSpeed2D = 0.f;
};
