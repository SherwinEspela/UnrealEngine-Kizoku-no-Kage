#pragma once
// Copyright 2025 Sherwin Espela. All rights reserved.
#pragma once

UENUM(BlueprintType)
enum class EPlayerMovementStates : uint8
{
	EPMS_Idling			UMETA(DisplayName = "Idling"),
	EPMS_Moving			UMETA(DisplayName = "Moving"),
	EPMS_Running		UMETA(DisplayName = "Running"),
	EPMS_TakingCover	UMETA(DisplayName = "Taking Cover"),
	EPMS_WallHugging	UMETA(DisplayName = "Wall Hugging"),
	EPMS_WallPeeking	UMETA(DisplayName = "Wall Peeking"),
	EPMS_Jumping		UMETA(DisplayName = "Jumping"),
	EPMS_Climbing		UMETA(DisplayName = "Climbing"),
	EPMS_Crouching		UMETA(DisplayName = "Crouching"),
	EPMS_Default		UMETA(DisplayName = "Default")
};
