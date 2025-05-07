// Copyright 2025 Sherwin Espela. All rights reserved.
#pragma once

UENUM(BlueprintType)
enum class EWeaponStates : uint8
{
	EWS_Equipped	UMETA(DisplayName = "Weapon Equipped"),
	EWS_Unequipped	UMETA(DisplayName = "Weapon Unequipped"),
	EWS_Updating	UMETA(DisplayName = "Weapon State Updating")
};
