// Copyright Epic Games, Inc. All Rights Reserved.

#include "AbilitySystem/CombatGameplayTags.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_Attack_Light, "Ability.Attack.Light")
UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_Attack_Heavy, "Ability.Attack.Heavy")
UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_Dodge, "Ability.Dodge")
UE_DEFINE_GAMEPLAY_TAG(TAG_State_Dead, "State.Dead")
UE_DEFINE_GAMEPLAY_TAG(TAG_State_Stunned, "State.Stunned")
UE_DEFINE_GAMEPLAY_TAG(TAG_State_Attacking, "State.Attacking")
UE_DEFINE_GAMEPLAY_TAG(TAG_Effect_Damage, "Effect.Damage")
UE_DEFINE_GAMEPLAY_TAG(TAG_Effect_StaminaCost, "Effect.StaminaCost")
UE_DEFINE_GAMEPLAY_TAG(TAG_Cooldown_Attack_Light, "Cooldown.Attack.Light")
UE_DEFINE_GAMEPLAY_TAG(TAG_Cooldown_Attack_Heavy, "Cooldown.Attack.Heavy")

FCombatGameplayTags FCombatGameplayTags::GameplayTags;

const FCombatGameplayTags& FCombatGameplayTags::Get()
{
	return GameplayTags;
}

void FCombatGameplayTags::InitializeNativeTags()
{
	GameplayTags.Ability_Attack_Light = TAG_Ability_Attack_Light;
	GameplayTags.Ability_Attack_Heavy = TAG_Ability_Attack_Heavy;
	GameplayTags.Ability_Dodge = TAG_Ability_Dodge;

	GameplayTags.State_Dead = TAG_State_Dead;
	GameplayTags.State_Stunned = TAG_State_Stunned;
	GameplayTags.State_Attacking = TAG_State_Attacking;

	GameplayTags.Effect_Damage = TAG_Effect_Damage;
	GameplayTags.Effect_StaminaCost = TAG_Effect_StaminaCost;

	GameplayTags.Cooldown_Attack_Light = TAG_Cooldown_Attack_Light;
	GameplayTags.Cooldown_Attack_Heavy = TAG_Cooldown_Attack_Heavy;
}

namespace
{
	struct FCombatGameplayTagsInitializer
	{
		FCombatGameplayTagsInitializer()
		{
			FCombatGameplayTags::InitializeNativeTags();
		}
	};

	const FCombatGameplayTagsInitializer CombatGameplayTagsInitializer;
}
