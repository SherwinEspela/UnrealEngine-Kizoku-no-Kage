// Copyright 2025 Sherwin Espela. All rights reserved.


#include "Animations/KNKAnimInstanceBase.h"
#include "KNKCharacters/KNKCharacterBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

void UKNKAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AKNKCharacterBase* CharacterBase = Cast<AKNKCharacterBase>(TryGetPawnOwner());

	if (CharacterBase)
	{
		CharacterMovementComp = CharacterBase->GetCharacterMovement();
	}
}

void UKNKAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (CharacterMovementComp)
	{
		MovementSpeed2D = UKismetMathLibrary::VSizeXY(CharacterMovementComp->Velocity);
	}
}
