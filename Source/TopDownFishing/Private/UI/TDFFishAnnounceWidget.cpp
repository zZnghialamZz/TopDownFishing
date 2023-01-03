// MIT License - Copyright (c) 2022 Nghia Lam

#include "UI/TDFFishAnnounceWidget.h"

#include "Components/TextBlock.h"

void UTDFFishAnnounceWidget::UpdateFishName(const FName& NewName)
{
	if (FishNameTextBlock)
	{
		FishNameTextBlock->SetText(FText::FromName(NewName));
	}
}