// Copyright 2025 Sherwin Espela. All rights reserved.


#include "KNKCharacters/KNKPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ArrowComponent.h"

AKNKPlayer::AKNKPlayer()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bInheritPitch = true;
	CameraBoom->bInheritYaw = true;
	CameraBoom->bInheritRoll = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	ArrowWallDetector = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Wall Detector"));
	ArrowWallDetector->SetupAttachment(GetMesh(), FName("root"));

	ArrowWallDetectorLeft = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Wall Detector Left"));
	ArrowWallDetectorLeft->SetupAttachment(GetMesh(), FName("root"));

	ArrowWallDetectorRight = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Wall Detector Right"));
	ArrowWallDetectorRight->SetupAttachment(GetMesh(), FName("root"));
}

void AKNKPlayer::BeginPlay()
{
	Super::BeginPlay();

	PlayerMovementState = EPlayerMovementStates::EPMS_Idling;
}
