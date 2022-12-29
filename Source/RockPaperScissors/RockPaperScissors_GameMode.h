// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "GameFramework/GameMode.h"
#include "RockPaperScissors_GameMode.generated.h"

UCLASS()
class ROCKPAPERSCISSORS_API ARockPaperScissors_GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ARockPaperScissors_GameMode();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int PlayerScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int EnemyScore;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APlayerCharacter> Enemy_Class;
	TObjectPtr<APlayerCharacter> Enemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString CurrentResult;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString Conclusion;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString FinalResult;

	UFUNCTION(BlueprintCallable)
		FString GetPlayerScore();

	UFUNCTION(BlueprintCallable)
		FString GetEnemyScore();

	FTimerHandle Restart_Handle;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> GameStateWidget_Class;
	TObjectPtr<UUserWidget> GameStateWidget;

	ESelection EnemySelection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void EnemyPlay();

	UFUNCTION(BlueprintCallable)
		void GameResult(ESelection PlayerSelection);

	void RestartLevel() const;
};
