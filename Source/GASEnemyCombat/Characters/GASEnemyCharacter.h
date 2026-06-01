// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GASCharacterBase.h"
#include "GASEnemyCharacter.generated.h"

/**
 * Base GAS enemy character, ready for AIController integration.
 */
UCLASS()
class GASENEMYCOMBAT_API AGASEnemyCharacter : public AGASCharacterBase
{
	GENERATED_BODY()

public:
	AGASEnemyCharacter();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void TryActivateAttackAbility();

	virtual void Die() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Combat")
	void OnEnemyDeath();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float AttackRange = 180.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float AcceptanceRadius = 150.0f;
};
