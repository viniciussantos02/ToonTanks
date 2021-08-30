// Fill out your copyright notice in the Description page of Project Settings.

#include "TanksGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"


void ATanksGameModeBase::BeginPlay()
{
	Super::BeginPlay();		

	HandleGameStart();
}

void ATanksGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();

		HandleGameOver(false);

		if (TankController)
		{
			TankController->SetPlayerEnablaState(false);
		}
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();

		if (--TargetTurrets == 0)
		{
			HandleGameOver(true);
		}
	}
}

void ATanksGameModeBase::HandleGameStart()
{
	TargetTurrets = GetNumberOfTargetTurretsInPlay();

	TankController = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	GameStart();

	if (TankController)
	{
		TankController->SetPlayerEnablaState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegatel = FTimerDelegate::CreateUObject(TankController, 
			&APlayerControllerBase::SetPlayerEnablaState, true);

		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegatel, StartDelay, false);
	}
}

void ATanksGameModeBase::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);
}

int32 ATanksGameModeBase::GetNumberOfTargetTurretsInPlay()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), OUT TurretActors);

	return TurretActors.Num();
}
