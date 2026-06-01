// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/CombatGameplayAbility.h"
#include "GA_LightAttack.generated.h"

class UAnimMontage;
class UGameplayEffect;

/**
 * Basic light melee attack ability.
 */
UCLASS()
class GASENEMYCOMBAT_API UGA_LightAttack : public UCombatGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_LightAttack();

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	virtual bool CanActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags = nullptr,
		const FGameplayTagContainer* TargetTags = nullptr,
		FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Light Attack")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Light Attack")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Light Attack")
	float AttackRange = 180.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Light Attack")
	float AttackRadius = 60.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Light Attack")
	float StaminaCost = 15.0f;

	void ApplyDamageToTarget(AActor* TargetActor);
	AActor* FindTargetInFront() const;
};
