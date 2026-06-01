// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Ability_Attack_Light)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Ability_Attack_Heavy)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Ability_Dodge)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Dead)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Stunned)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Attacking)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Effect_Damage)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Effect_StaminaCost)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Cooldown_Attack_Light)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Cooldown_Attack_Heavy)

struct GASENEMYCOMBAT_API FCombatGameplayTags
{
public:
	static const FCombatGameplayTags& Get();
	static void InitializeNativeTags();

	FGameplayTag Ability_Attack_Light;
	FGameplayTag Ability_Attack_Heavy;
	FGameplayTag Ability_Dodge;

	FGameplayTag State_Dead;
	FGameplayTag State_Stunned;
	FGameplayTag State_Attacking;

	FGameplayTag Effect_Damage;
	FGameplayTag Effect_StaminaCost;

	FGameplayTag Cooldown_Attack_Light;
	FGameplayTag Cooldown_Attack_Heavy;

private:
	static FCombatGameplayTags GameplayTags;
};
