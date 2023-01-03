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

void ATDFBaseTool::BeginAction()
{
	bIsToolInUse = true;
}

void ATDFBaseTool::EndAction()
{
	bIsToolInUse = false;
}