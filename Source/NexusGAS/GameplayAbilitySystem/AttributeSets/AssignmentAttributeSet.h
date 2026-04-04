// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AssignmentAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSGAS_API UAssignmentAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	
	UAssignmentAttributeSet();
	
	// Armor Attributes
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS_BASIC(UAssignmentAttributeSet, Armor);	
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_MaxArmor)
	FGameplayAttributeData MaxArmor;
	ATTRIBUTE_ACCESSORS_BASIC(UAssignmentAttributeSet, MaxArmor);	
	
public:
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UAssignmentAttributeSet, Armor, OldValue);
	}
	
	UFUNCTION()
	void OnRep_MaxArmor(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UAssignmentAttributeSet, MaxArmor, OldValue);
	}	
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
