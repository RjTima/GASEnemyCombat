// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GASCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAnimMontage;
class UCombatAttributeSet;
class UGameplayAbility;
class UGameplayEffect;

/**
 * Base character with Gameplay Ability System support.
 */
UCLASS()
class GASENEMYCOMBAT_API AGASCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGASCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "GAS")
	virtual void GiveDefaultAbilities();

	UFUNCTION(BlueprintCallable, Category = "GAS")
	virtual void ApplyDefaultEffects();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void Die();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void PlayHitReact();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void PlayDeathMontage();

	UFUNCTION(BlueprintNativeEvent, Category = "Combat")
	void OnDeath();

	UFUNCTION(BlueprintPure, Category = "Combat")
	bool IsDead() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	UCombatAttributeSet* AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TArray<TSubclassOf<UGameplayEffect>> DefaultEffects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	UAnimMontage* DeathMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bIsDead;
};
