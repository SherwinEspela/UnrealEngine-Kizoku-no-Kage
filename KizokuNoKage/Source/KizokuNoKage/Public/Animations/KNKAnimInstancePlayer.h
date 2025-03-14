// Copyright 2025 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animations/KNKAnimInstanceBase.h"
#include "KNKAnimInstancePlayer.generated.h"

class AKNKCPlayerKosuke;

/**
 * 
 */
UCLASS()
class KIZOKUNOKAGE_API UKNKAnimInstancePlayer : public UKNKAnimInstanceBase
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Player Character")
	TObjectPtr<AKNKCPlayerKosuke> PlayerCharacter;
};
