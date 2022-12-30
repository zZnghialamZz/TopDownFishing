// MIT License - Copyright (c) 2022 Nghia Lam

#include "Player/TDFPlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Actors/TDFBaseTool.h"

// Sets default values
ATDFPlayerCharacter::ATDFPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
}

// Called when the game starts or when spawned
void ATDFPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SpawnTool();
}

// Called every frame
void ATDFPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATDFPlayerCharacter::SpawnTool()
{
	if (!GetWorld()) return;

	const auto Tool = GetWorld()->SpawnActor<ATDFBaseTool>(ToolClass);
	if (Tool)
	{
		const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
		Tool->AttachToComponent(GetMesh(), AttachmentRules, "ToolSocket");
	}
}