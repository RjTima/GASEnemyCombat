// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatHealthBarWidget.generated.h"

class UProgressBar;

/**
 * Simple health bar widget for GAS characters.
 */
UCLASS()
class GASENEMYCOMBAT_API UCombatHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetHealthPercent(float Percent);

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar;
};
