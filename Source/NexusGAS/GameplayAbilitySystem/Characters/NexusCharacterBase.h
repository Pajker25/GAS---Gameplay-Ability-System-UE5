// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "NexusCharacterBase.generated.h"

UCLASS()
class NEXUSGAS_API ANexusCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANexusCharacterBase();
	
	// Ability System Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySysyem")
	UAbilitySystemComponent * AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySysyem")
	class UBasicAttributeSet* BasicAttributeSet;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySysyem")
	class UBasicAttributeSet* AssignmentAttributeSet;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySysyem")
	EGameplayEffectReplicationMode ASCReplicationMode = EGameplayEffectReplicationMode::Mixed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySysyem")
	TArray<TSubclassOf<UGameplayAbility>> StartingAbilities;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void OnRep_PlayerState() override; 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual UAbilitySystemComponent * GetAbilitySystemComponent() const override;
	
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	TArray<FGameplayAbilitySpecHandle> GrantAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGrant);
	
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	void RemoveAbilities(TArray<FGameplayAbilitySpecHandle> AbilitiesHandlesToRemove);
	
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	void SendAbilitiesChangedEvent();
	
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Ability System")
	void ServerSendGameplayEventToSelf(FGameplayEventData EventData);
};
