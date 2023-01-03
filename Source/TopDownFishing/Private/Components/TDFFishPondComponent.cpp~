// MIT License - Copyright (c) 2022 Nghia Lam

#include "Components/TDFFishPondComponent.h"

#include "Components/BoxComponent.h"
#include "Actors/TDFFish.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UTDFFishPondComponent::UTDFFishPondComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTDFFishPondComponent::BeginPlay()
{
	Super::BeginPlay();

	// Setup Spawn Box
	SpawnBox = GetOwner()->FindComponentByClass<UBoxComponent>();
}

void UTDFFishPondComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentFish != nullptr && !IsFishWithinReach())
	{
		const FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(CurrentFish->GetActorLocation(), CastLocation);
		const FRotator NewRotation = FMath::RInterpTo(CurrentFish->GetActorRotation(), TargetRotation, DeltaTime, 1.0f);
		const FVector NewLocation = FMath::VInterpTo(CurrentFish->GetActorLocation(), CastLocation, DeltaTime, .2f);

		CurrentFish->SetActorLocation(NewLocation);
		CurrentFish->SetActorRotation(NewRotation);

		if (IsFishWithinReach())
		{
			FishBiteEvent.Broadcast();
		}
	}
}

bool UTDFFishPondComponent::IsFishWithinReach() const
{
	return FVector::Distance(CurrentFish->GetActorLocation(), CastLocation) <= 50.0f;
}

bool UTDFFishPondComponent::SpawnFish()
{
	if (FishList.Num() == 0 || !GetWorld() || SpawnBox == nullptr) return false;

	const FBoxSphereBounds BoxBounds = SpawnBox->CalcBounds(GetOwner()->GetActorTransform());

	FVector SpawnLocation = BoxBounds.Origin;
	SpawnLocation.X += -BoxBounds.BoxExtent.X + 2 * BoxBounds.BoxExtent.X * FMath::FRand();
	SpawnLocation.Y += -BoxBounds.BoxExtent.Y + 2 * BoxBounds.BoxExtent.Y * FMath::FRand();

	const uint32 SpawnIndex = FMath::RandRange(0, FishList.Num() - 1);

	CurrentFish = Cast<ATDFFish>(GetWorld()->SpawnActor(FishList[SpawnIndex], &SpawnLocation));
	return CurrentFish != nullptr;
}

void UTDFFishPondComponent::DestroyFish()
{
	if (CurrentFish)
	{
		CurrentFish->Destroy();
		CurrentFish = nullptr;
	}
}