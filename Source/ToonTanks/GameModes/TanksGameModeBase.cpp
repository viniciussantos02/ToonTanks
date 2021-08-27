// Fill out your copyright notice in the Description page of Project Settings.

#include "TanksGameModeBase.h"


void ATanksGameModeBase::BeginPlay()
{

}

void ATanksGameModeBase::ActorDied(AActor* DeadActor)
{
	UE_LOG(LogTemp, Warning, TEXT("The %s Died"), *DeadActor->GetName());
}

void ATanksGameModeBase::HandleGameStart()
{

}

void ATanksGameModeBase::HandleGameOver(bool PlayerWon)
{

}