// Copyright 2025 Sherwin Espela. All rights reserved.


#include "KNKCharacters/KNKCPlayerKosuke.h"

void AKNKCPlayerKosuke::BeginPlay()
{
	Super::BeginPlay();

	PlayerMovementState = EPlayerMovementStates::EPMS_Default;
}
