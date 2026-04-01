// Fill out your copyright notice in the Description page of Project Settings.


#include "AssignmentAttributeSet.h"

#include "Net/UnrealNetwork.h"

UAssignmentAttributeSet::UAssignmentAttributeSet()
{
	Armor = 50.f;
	MaxArmor = 50.f;
}

void UAssignmentAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UAssignmentAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAssignmentAttributeSet, MaxArmor, COND_None, REPNOTIFY_Always);
}