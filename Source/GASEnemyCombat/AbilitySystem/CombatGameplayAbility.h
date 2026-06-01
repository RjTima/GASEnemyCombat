// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "CombatGameplayAbility.generated.h"

class AGASCharacterBase;
class UAbilitySystemComponent;

/**
 * Base Gameplay Ability for combat actions.
 */
UCLASS()
class GASENEMYCOMBAT_API UCombatGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UCombatGameplayAbility();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	FGameplayTag AbilityInputTag;

	UFUNCTION(BlueprintPure, Category = "Ability")
	AGASCharacterBase* GetCombatCharacterFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "Ability")
	UAbilitySystemComponent* GetCombatAbilitySystemComponentFromActorInfo() const;

	virtual bool CanActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags = nullptr,
		const FGameplayTagContainer* TargetTags = nullptr,
		FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
};
