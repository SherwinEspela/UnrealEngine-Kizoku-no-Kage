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
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetDead();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Is Dead")
	bool bIsDead = false;
};
