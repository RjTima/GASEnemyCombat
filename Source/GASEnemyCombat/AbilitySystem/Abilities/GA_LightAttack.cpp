// Copyright Epic Games, Inc. All Rights Reserved.

#include "AbilitySystem/Abilities/GA_LightAttack.h"

#include "AbilitySystem/CombatAttributeSet.h"
#include "AbilitySystem/CombatGameplayTags.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Animation/AnimInstance.h"
#include "Characters/GASCharacterBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameplayEffect.h"

UGA_LightAttack::UGA_LightAttack()
{
	AbilityInputTag = FCombatGameplayTags::Get().Ability_Attack_Light;

	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(FCombatGameplayTags::Get().Ability_Attack_Light);
	SetAssetTags(AssetTags);
}

bool UGA_LightAttack::CanActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (!ActorInfo || !ActorInfo->AvatarActor.IsValid())
	{
		return false;
	}

	const AGASCharacterBase* CombatCharacter = Cast<AGASCharacterBase>(ActorInfo->AvatarActor.Get());
	if (!CombatCharacter)
	{
		return false;
	}

	UAbilitySystemComponent* AbilitySystemComponent = CombatCharacter->GetAbilitySystemComponent();
	if (!AbilitySystemComponent)
	{
		return false;
	}

	const UCombatAttributeSet* CombatAttributeSet = AbilitySystemComponent->GetSet<UCombatAttributeSet>();
	if (!CombatAttributeSet)
	{
		return false;
	}

	if (CombatAttributeSet->GetStamina() < StaminaCost)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s does not have enough stamina for Light Attack: Stamina=%.2f Cost=%.2f"),
			*GetNameSafe(CombatCharacter),
			CombatAttributeSet->GetStamina(),
			StaminaCost);
		return false;
	}

	return true;
}

void UGA_LightAttack::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	AGASCharacterBase* CombatCharacter = GetCombatCharacterFromActorInfo();
	if (!CombatCharacter)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	if (AttackMontage)
	{
		if (USkeletalMeshComponent* MeshComponent = CombatCharacter->GetMesh())
		{
			if (UAnimInstance* AnimInstance = MeshComponent->GetAnimInstance())
			{
				AnimInstance->Montage_Play(AttackMontage);
			}
		}
	}

	if (AActor* TargetActor = FindTargetInFront())
	{
		ApplyDamageToTarget(TargetActor);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UGA_LightAttack::ApplyDamageToTarget(AActor* TargetActor)
{
	if (!TargetActor || !DamageEffectClass)
	{
		return;
	}

	UAbilitySystemComponent* SourceAbilitySystemComponent = GetCombatAbilitySystemComponentFromActorInfo();
	if (!SourceAbilitySystemComponent)
	{
		return;
	}

	UAbilitySystemComponent* TargetAbilitySystemComponent =
		UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);
	if (!TargetAbilitySystemComponent)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = SourceAbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle EffectSpecHandle =
		SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContext);
	if (!EffectSpecHandle.IsValid())
	{
		return;
	}

	SourceAbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
		*EffectSpecHandle.Data.Get(),
		TargetAbilitySystemComponent);
}

AActor* UGA_LightAttack::FindTargetInFront() const
{
	const AGASCharacterBase* CombatCharacter = GetCombatCharacterFromActorInfo();
	if (!CombatCharacter)
	{
		return nullptr;
	}

	UWorld* World = CombatCharacter->GetWorld();
	if (!World)
	{
		return nullptr;
	}

	const FVector Start = CombatCharacter->GetActorLocation();
	const FVector End = Start + CombatCharacter->GetActorForwardVector() * AttackRange;

	FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(GA_LightAttack), false);
	QueryParams.AddIgnoredActor(CombatCharacter);

	TArray<FHitResult> HitResults;
	const bool bHit = World->SweepMultiByChannel(
		HitResults,
		Start,
		End,
		FQuat::Identity,
		ECC_Pawn,
		FCollisionShape::MakeSphere(AttackRadius),
		QueryParams);

	if (!bHit)
	{
		return nullptr;
	}

	for (const FHitResult& HitResult : HitResults)
	{
		AActor* HitActor = HitResult.GetActor();
		if (!HitActor || HitActor == CombatCharacter)
		{
			continue;
		}

		if (UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(HitActor))
		{
			return HitActor;
		}
	}

	return nullptr;
}
