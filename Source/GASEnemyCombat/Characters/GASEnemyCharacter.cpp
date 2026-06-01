// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/GASEnemyCharacter.h"

#include "AbilitySystem/CombatAttributeSet.h"
#include "AbilitySystem/CombatGameplayTags.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/CombatHealthBarWidget.h"

AGASEnemyCharacter::AGASEnemyCharacter()
{
	HealthBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarComponent"));
	HealthBarComponent->SetupAttachment(RootComponent);
	HealthBarComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
	HealthBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarComponent->SetDrawSize(FVector2D(160.0f, 20.0f));
}

void AGASEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	UpdateHealthBar();
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

void AGASEnemyCharacter::UpdateHealthBar()
{
	if (!HealthBarComponent)
	{
		return;
	}

	UCombatHealthBarWidget* HealthBarWidget = Cast<UCombatHealthBarWidget>(HealthBarComponent->GetUserWidgetObject());
	if (!HealthBarWidget)
	{
		return;
	}

	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (!ASC)
	{
		return;
	}

	const UCombatAttributeSet* CombatAttributeSet = ASC->GetSet<UCombatAttributeSet>();
	if (!CombatAttributeSet)
	{
		return;
	}

	const float MaxHealth = CombatAttributeSet->GetMaxHealth();
	const float HealthPercent = MaxHealth > 0.0f ? CombatAttributeSet->GetHealth() / MaxHealth : 0.0f;
	HealthBarWidget->SetHealthPercent(HealthPercent);
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
