// Copyright 2025 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "KNKCharacters/KNKCharacterBase.h"
#include "KNKCPlayerKosuke.generated.h"

/**
 * 
 */
UCLASS()
class KIZOKUNOKAGE_API AKNKCPlayerKosuke : public AKNKCharacterBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HealthTest;
};
