// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusCharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NexusGAS/GameplayAbilitySystem/AttributeSets/AssignmentAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "NexusGAS/GameplayAbilitySystem/NexusAbilitySystemComponent.h"
#include "NexusGAS/GameplayAbilitySystem/AttributeSets/BasicAttributeSet.h"

// Sets default values
ANexusCharacterBase::ANexusCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add the ability system component
	AbilitySystemComponent = CreateDefaultSubobject<UNexusAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(ASCReplicationMode);
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	// Add the basic attribute set
	BasicAttributeSet = CreateDefaultSubobject<UBasicAttributeSet>(TEXT("BasicAttributeSet"));
	
	// Add the assignment attribute set
	AssignmentAttributeSet = CreateDefaultSubobject<UAssignmentAttributeSet>(TEXT("AssignmentAttributeSet"));
}

// Called when the game starts or when spawned
void ANexusCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANexusCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANexusCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANexusCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		GrantAbilities(StartingAbilities);
	}
}

void ANexusCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

UAbilitySystemComponent* ANexusCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

TArray<FGameplayAbilitySpecHandle> ANexusCharacterBase::GrantAbilities(
	TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGrant)
{
	if (!AbilitySystemComponent || !HasAuthority())
	{
		return TArray<FGameplayAbilitySpecHandle>();
	}
	
	TArray<FGameplayAbilitySpecHandle> AbilityHandles;
	
	for (TSubclassOf<UGameplayAbility> Ability : AbilitiesToGrant)
	{
		FGameplayAbilitySpecHandle SpecHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(
			Ability, 1, -1, this
			));
		AbilityHandles.Add(SpecHandle);
	}
	
	SendAbilitiesChangedEvent();
	return AbilityHandles;
}

void ANexusCharacterBase::RemoveAbilities(TArray<FGameplayAbilitySpecHandle> AbilitiesHandlesToRemove)
{
	if (!AbilitySystemComponent || !HasAuthority())
	{
		return;
	}
	
	for (FGameplayAbilitySpecHandle AbilityHandle : AbilitiesHandlesToRemove)
	{
		AbilitySystemComponent->ClearAbility(AbilityHandle);
	}
	SendAbilitiesChangedEvent();
}

void ANexusCharacterBase::SendAbilitiesChangedEvent()
{
	FGameplayEventData EventData;
	EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Abilities.Changed"));
	EventData.Instigator = this;
	EventData.Target = this;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, EventData.EventTag, EventData);
}

