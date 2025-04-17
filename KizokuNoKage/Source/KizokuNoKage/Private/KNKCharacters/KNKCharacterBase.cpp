// Copyright 2025 Sherwin Espela. All rights reserved.


#include "KNKCharacters/KNKCharacterBase.h"
#include "Components/CapsuleComponent.h"

AKNKCharacterBase::AKNKCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AKNKCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	bIsDead = false;
}

void AKNKCharacterBase::SetDead()
{
	bIsDead = true;
	GetCapsuleComponent()->SetActive(false);
}

void AKNKCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
