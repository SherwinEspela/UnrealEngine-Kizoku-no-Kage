// Copyright 2025 Sherwin Espela. All rights reserved.


#include "Animations/KNKAnimInstancePlayer.h"
#include "KNKCharacters/KNKCPlayerKosuke.h"

void UKNKAnimInstancePlayer::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PlayerCharacter = Cast<AKNKCPlayerKosuke>(TryGetPawnOwner());
}
