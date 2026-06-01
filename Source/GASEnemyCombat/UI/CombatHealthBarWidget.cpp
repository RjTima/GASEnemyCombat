// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/CombatHealthBarWidget.h"

#include "Components/ProgressBar.h"

void UCombatHealthBarWidget::SetHealthPercent(float Percent)
{
	const float ClampedPercent = FMath::Clamp(Percent, 0.0f, 1.0f);

	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(ClampedPercent);
	}
}
