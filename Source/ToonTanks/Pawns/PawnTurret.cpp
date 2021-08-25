// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FiraRate, true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APawnTurret::CheckFireCondition() 
{
	if (PlayerPawn)
	{
		if (GetDistanceToPlayer() <= RangeToStartFire)
		{
			UE_LOG(LogTemp, Warning, TEXT("FIRING!!!"));
		}
	}	
}

float APawnTurret::GetDistanceToPlayer()
{
	if (PlayerPawn)
	{
		return FVector::Dist(PlayerPawn->GetActorLocation(), this->GetActorLocation());		
	}

	return 0.f;
}
