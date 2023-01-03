// MIT License - Copyright (c) 2022 Nghia Lam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDFBaseTool.generated.h"

class UStaticMeshComponent;

UCLASS()
class TOPDOWNFISHING_API ATDFBaseTool : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	ATDFBaseTool();

	virtual void BeginAction();
	virtual void EndAction();

	UFUNCTION(BlueprintCallable)
	void SetToolOwner(AActor* Actor)
	{
		ToolOwner = Actor;
	}

	UFUNCTION(BlueprintCallable)
	AActor* GetToolOwner()
	{
		return ToolOwner;
	}

	UFUNCTION(BlueprintCallable)
	bool IsToolInUse()
	{
		return bIsToolInUse;
	}

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tool")
	TObjectPtr<UAnimMontage> ToolMontage;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tool")
	TObjectPtr<UStaticMeshComponent> ToolMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tool")
	TObjectPtr<AActor> ToolOwner;

	bool bIsToolInUse = false;
};