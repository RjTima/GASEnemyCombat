// Copyright Epic Games, Inc. All Rights Reserved.

#include "AbilitySystem/CombatAttributeSet.h"

#include "Characters/GASCharacterBase.h"
#include "Characters/GASEnemyCharacter.h"
#include "GameplayEffectExtension.h"

UCombatAttributeSet::UCombatAttributeSet()
{
	InitMaxHealth(100.0f);
	InitHealth(100.0f);
	InitMaxStamina(100.0f);
	InitStamina(100.0f);
	InitAttackPower(10.0f);
}

void UCombatAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
	else if (Attribute == GetMaxStaminaAttribute())
	{
		AdjustAttributeForMaxChange(Stamina, MaxStamina, NewValue, GetStaminaAttribute());
	}
}

void UCombatAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		AActor* OwningActor = GetOwningActor();

		UE_LOG(LogTemp, Warning, TEXT("Health changed for %s: Health=%.2f MaxHealth=%.2f"),
			*GetNameSafe(OwningActor),
			GetHealth(),
			GetMaxHealth());

		if (AGASEnemyCharacter* Enemy = Cast<AGASEnemyCharacter>(OwningActor))
		{
			Enemy->UpdateHealthBar();
		}

		if (GetHealth() <= 0.0f)
		{
			if (AGASCharacterBase* Character = Cast<AGASCharacterBase>(OwningActor))
			{
				Character->Die();
			}
		}
	}
	
	else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
		
		UE_LOG(LogTemp, Warning, TEXT("Stamina changed for %s: Stamina=%.2f MaxStamina=%.2f"),
	*GetNameSafe(GetOwningActor()),
	GetStamina(),
	GetMaxStamina());
	}
}

void UCombatAttributeSet::AdjustAttributeForMaxChange(
	const FGameplayAttributeData& AffectedAttribute,
	const FGameplayAttributeData& MaxAttribute,
	float NewMaxValue,
	const FGameplayAttribute& AffectedAttributeProperty) const
{
	UAbilitySystemComponent* AbilitySystemComponent = GetOwningAbilitySystemComponent();
	if (!AbilitySystemComponent)
	{
		return;
	}

	const float CurrentValue = AffectedAttribute.GetCurrentValue();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	const float NewDelta = CurrentMaxValue > 0.0f
		? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue
		: NewMaxValue;

	AbilitySystemComponent->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
}
