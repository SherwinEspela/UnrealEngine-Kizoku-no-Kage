// Copyright 2025 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KNKCharacterBase.generated.h"

UCLASS()
class KIZOKUNOKAGE_API AKNKCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AKNKCharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
