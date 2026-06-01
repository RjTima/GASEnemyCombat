// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/GASEnemyCharacter.h"

#include "AbilitySystem/CombatGameplayTags.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AGASEnemyCharacter::AGASEnemyCharacter()
{
}

void AGASEnemyCharacter::TryActivateAttackAbility()
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (!ASC)
	{
		return;
	}

	FGameplayTagContainer AbilityTags;
	AbilityTags.AddTag(FCombatGameplayTags::Get().Ability_Attack_Light);

	ASC->TryActivateAbilitiesByTag(AbilityTags);
}

void AGASEnemyCharacter::Die()
{
	if (IsDead())
	{
		return;
	}

	Super::Die();

	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->StopMovementImmediately();
		MovementComponent->DisableMovement();
	}

	if (UCapsuleComponent* CharacterCapsule = GetCapsuleComponent())
	{
		CharacterCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	SetLifeSpan(5.0f);
	OnEnemyDeath();
}

void AGASEnemyCharacter::OnEnemyDeath_Implementation()
{
}
