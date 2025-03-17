// Copyright 2025 Sherwin Espela. All rights reserved.


#include "KNKCharacters/KNKCPlayerKosuke.h"
#include "Components/ArrowComponent.h"

AKNKCPlayerKosuke::AKNKCPlayerKosuke()
{
	ArrowWallDetector = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Wall Detector"));
	ArrowWallDetector->SetupAttachment(GetMesh(), FName("root"));
}

void AKNKCPlayerKosuke::BeginPlay()
{
	Super::BeginPlay();

	PlayerMovementState = EPlayerMovementStates::EPMS_Default;
}
