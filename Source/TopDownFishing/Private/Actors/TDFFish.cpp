// MIT License - Copyright (c) 2022 Nghia Lam

#include "Actors/TDFFish.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATDFFish::ATDFFish()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FishMesh = CreateDefaultSubobject<UStaticMeshComponent>("Fish Mesh");
	FishMesh->SetupAttachment(RootComponent);
}