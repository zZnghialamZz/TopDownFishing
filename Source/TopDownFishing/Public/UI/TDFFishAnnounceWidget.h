// MIT License - Copyright (c) 2022 Nghia Lam

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDFFishAnnounceWidget.generated.h"

UCLASS()
class TOPDOWNFISHING_API UTDFFishAnnounceWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) 
	UTextBlock* FishNameTextBlock;

	UFUNCTION(BlueprintCallable)
	void UpdateFishName(const FName& NewName);
};