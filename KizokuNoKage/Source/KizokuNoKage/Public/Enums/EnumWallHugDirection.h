// Copyright 2025 Sherwin Espela. All rights reserved.
#pragma once

UENUM(BlueprintType)
enum class EWallHugDirection : uint8
{
	EWHD_Middle		UMETA(DisplayName = "Middle"),
	EWHD_Left		UMETA(DisplayName = "Left"),
	EWHD_Right		UMETA(DisplayName = "Right")
};
