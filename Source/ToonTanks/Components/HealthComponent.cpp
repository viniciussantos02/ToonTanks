// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanks/GameModes/TanksGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = DefaultHealth;
	
	TanksGameMode = Cast<ATanksGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage != 0 && Health > 0)
	{
		Health = FMath::Clamp(Health - Damage, 0.f, DefaultHealth);

		UE_LOG(LogTemp, Warning, TEXT("Health remaning: %f"), Health)
		if (Health <= 0)
		{
			if (TanksGameMode)
			{
				TanksGameMode->ActorDied(GetOwner());
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Health Component has no GameMode reference."));
			}
		}
	}
}

