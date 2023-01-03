// MIT License - Copyright (c) 2022 Nghia Lam

#include "Actors/TDFFishingRod.h"

#include "Actors/TDFFish.h"
#include "Blueprint/UserWidget.h"
#include "Components/TDFFishPondComponent.h"
#include "Player/TDFPlayerCharacter.h"
#include "UI/TDFFishAnnounceWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogTDFFishingRod, All, All);

ATDFFishingRod::ATDFFishingRod()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATDFFishingRod::BeginPlay()
{
	Super::BeginPlay();

	if (!FishAnnounceWidget)
	{
		APlayerController* MyPlayerController = GetWorld()->GetFirstPlayerController();
		FishAnnounceWidget = CreateWidget<UTDFFishAnnounceWidget>(MyPlayerController, FishAnnounceWidgetClass);
	}
}

void ATDFFishingRod::BeginAction()
{
	Super::BeginAction();

	switch (RodState)
	{
		case EFishingRodState::NotUsed:
		{
			CurrentCastOffset = 0.0f;
			StartPlayerMontage(FName("FishingStart"));
			RodState = EFishingRodState::Casting;
			break;
		}
		case EFishingRodState::Waiting:
		{
			bCaughtFish = false;
			OnFinish();
			break;
		}
		case EFishingRodState::Pulling:
		{
			bCaughtFish = true;
			OnFinish();
			break;
		}
		default: break;
	}
}

void ATDFFishingRod::EndAction()
{
	if (RodState == EFishingRodState::Casting)
	{
		FHitResult Result;
		if (GetFishingLocation(OUT Result))
		{
			StartPlayerMontage(FName("FishingCast"));
			ThrowCast(Result.ImpactPoint);

			CurrentPond = Result.GetActor()->FindComponentByClass<UTDFFishPondComponent>();
			if (CurrentPond)
			{
				CurrentPond->SetCastLocation(Result.ImpactPoint);
				CurrentPond->SpawnFish();
				CurrentPond->GetFishBiteEvent().AddUObject(this, &ATDFFishingRod::OnFishBite);
			}

			RodState = EFishingRodState::Waiting;
		}
		else
		{
			bCaughtFish = false;
			OnFinish();
		}
	}
}

void ATDFFishingRod::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (RodState)
	{
		case EFishingRodState::Casting:
		{
			if (!bCastBackward)
				CurrentCastOffset += CastingSpeed * DeltaSeconds;
			else
				CurrentCastOffset -= CastingSpeed * DeltaSeconds;

			if (CurrentCastOffset > MaxCastDistance || CurrentCastOffset < 0.0f)
			{
				bCastBackward = !bCastBackward;
			}
			break;
		}
		default: break;
	}
}

bool ATDFFishingRod::GetFishingLocation(FHitResult& Result)
{
	if (!GetWorld()) return false;

	const FVector CastDirection = GetToolOwner()->GetActorForwardVector();
	const FVector CastLocation = GetToolOwner()->GetActorLocation() + CastDirection * CurrentCastOffset;

	if (GetWorld()->LineTraceSingleByChannel(OUT Result, CastLocation, CastLocation + CastLocation.DownVector * 200.0f, FishingChannel))
	{
		return true;
	}

	return false;
}

void ATDFFishingRod::ThrowCast(const FVector Location)
{
	if (!FishingCastClass) return;

	FishingCast = GetWorld()->SpawnActor<AActor>(FishingCastClass);
	if (FishingCast)
	{
		FishingCast->SetActorLocation(Location);
	}
}

void ATDFFishingRod::StartPlayerMontage(const FName MontageName, const float Rate)
{
	if (!ToolMontage) return;
	if (!PlayerOwner)
	{
		PlayerOwner = Cast<ATDFPlayerCharacter>(GetToolOwner());
		if (!PlayerOwner)
		{
			UE_LOG(LogTDFFishingRod, Error, TEXT("Cannot find the player !!"));
			return;
		}
	}
	PlayerOwner->PlayAnimMontage(ToolMontage, Rate, MontageName);
}

void ATDFFishingRod::StopPlayerMontage()
{
	if (ToolMontage && PlayerOwner)
	{
		PlayerOwner->StopAnimMontage();
	}
}

void ATDFFishingRod::OnFishBite()
{
	// Set Cast a bit lower
	FVector CastLocation = FishingCast->GetActorLocation();
	CastLocation.Z -= 10.0f;
	FishingCast->SetActorLocation(CastLocation);

	RodState = EFishingRodState::Pulling;
}

void ATDFFishingRod::OnFinish()
{
	if (bCaughtFish)
	{
		// NOTE(Nghia Lam): We only show UI for now, but in real game, we might have some stuff to do here, like add
		// the fish to player's inventory.
		UE_LOG(LogTDFFishingRod, Display, TEXT("Catch Fish %s!!"), *CurrentPond->CurrentFish->FishName);
		if (FishAnnounceWidget) FishAnnounceWidget->UpdateFishName(FName(CurrentPond->CurrentFish->FishName));
	}
	else
	{
		UE_LOG(LogTDFFishingRod, Display, TEXT("No Fish !!"));
		if (FishAnnounceWidget) FishAnnounceWidget->UpdateFishName("No Fish !!");
	}
	
	if (FishAnnounceWidget) FishAnnounceWidget->AddToViewport();

	// Cleanup
	
	StopPlayerMontage();
	bIsToolInUse = false;
	RodState = EFishingRodState::NotUsed;
	bCaughtFish = false;

	if (FishingCast)
	{
		FishingCast->Destroy();
		FishingCast = nullptr;
	}
	if (CurrentPond)
	{
		CurrentPond->DestroyFish();
		CurrentPond = nullptr;
	}
}
