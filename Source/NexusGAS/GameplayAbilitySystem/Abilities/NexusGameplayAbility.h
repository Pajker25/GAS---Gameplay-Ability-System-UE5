// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "NexusGameplayAbility.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	None UMETA(DisplayName = "None"), // 0
	PrimaryAbility UMETA(DisplayName = "Primary Ability"), // 1
	SecondaryAbility UMETA(DisplayName = "Secondary Ability"), // 2
	DefensiveAbility UMETA(DisplayName = "Defensive Ability"), // 3
	MovementAbility UMETA(DisplayName = "Movement Ability"), // 4
};

UCLASS()
class NEXUSGAS_API UNexusGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	
	UNexusGameplayAbility();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	bool ShouldShowInAbilitiesBar = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	EAbilityInputID AbilityInputID = EAbilityInputID::None;
	
private:
	UFUNCTION(BlueprintCallable, Category = "Helpers")
	bool HasPC() const;
};
