// MIT License - Copyright (c) 2022 Nghia Lam

#include "Actors/TDFBaseTool.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATDFBaseTool::ATDFBaseTool()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ToolMesh = CreateDefaultSubobject<UStaticMeshComponent>("Tool Mesh");
	ToolMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATDFBaseTool::BeginPlay()
{
	Super::BeginPlay();
}