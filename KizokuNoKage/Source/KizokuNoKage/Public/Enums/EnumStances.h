// Copyright 2025 Sherwin Espela. All rights reserved.
#pragma once

UENUM(BlueprintType)
enum class ECharacterStances : uint8
{
	ECS_Stand		UMETA(DisplayName = "Stand"),
	ECS_Crouch		UMETA(DisplayName = "Crouch"),
	ECS_Crawl		UMETA(DisplayName = "Crawl")
};

FORCEINLINE void PrintCharacterStance(ECharacterStances Value) {
	UE_LOG(LogTemp, Log, TEXT("Character Stance: %s"), *UEnum::GetValueAsName(Value).ToString());
}
