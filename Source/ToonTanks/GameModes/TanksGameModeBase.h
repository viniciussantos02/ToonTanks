// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TanksGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATanksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

public:
	void ActorDied(AActor* DeadActor);
};
