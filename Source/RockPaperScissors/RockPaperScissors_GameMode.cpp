// Fill out your copyright notice in the Description page of Project Settings.


#include "RockPaperScissors_GameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ARockPaperScissors_GameMode::ARockPaperScissors_GameMode()
{
	PlayerScore = 0;
	EnemyScore = 0;
}

void ARockPaperScissors_GameMode::BeginPlay()
{
	if(Enemy_Class)
	{
		Enemy = Cast<APlayerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), Enemy_Class));
	}
}

FString ARockPaperScissors_GameMode::GetPlayerScore()
{
	return "You: " + FString::FromInt(PlayerScore);
}

FString ARockPaperScissors_GameMode::GetEnemyScore()
{
	return "Enemy: " + FString::FromInt(EnemyScore);
}

void ARockPaperScissors_GameMode::EnemyPlay()
{
	if (Enemy)
	{
		EnemySelection = Enemy->Play(FMath::RandRange(0, 2));
	}
}

void ARockPaperScissors_GameMode::GameResult(ESelection PlayerSelection)
{
	if (PlayerSelection == ESelection::Rock && EnemySelection == ESelection::Paper)
	{
		EnemyScore++;
		CurrentResult = "You chose Rock, Enemy chose Paper";
		Conclusion = "Paper covers Rock!";
	}
	else if (PlayerSelection == ESelection::Rock && EnemySelection == ESelection::Scissors)
	{
		PlayerScore++;
		CurrentResult = "You chose Rock, Enemy chose Scissors";
		Conclusion = "Rock Breaks Scissors!";
	}
	else if (PlayerSelection == ESelection::Paper && EnemySelection == ESelection::Rock)
	{
		PlayerScore++;
		CurrentResult = "You chose Paper, Enemy chose Rock";
		Conclusion = "Paper covers Rock!";
	}
	else if (PlayerSelection == ESelection::Paper && EnemySelection == ESelection::Scissors)
	{
		EnemyScore++;
		CurrentResult = "You chose Paper, Enemy chose Scissors";
		Conclusion = "Scissors cuts Paper!";
	}
	else if (PlayerSelection == ESelection::Scissors && EnemySelection == ESelection::Rock)
	{
		EnemyScore++;
		CurrentResult = "You chose Scissors, Enemy chose Rock";
		Conclusion = "Rock Breaks Scissors!";
	}
	else if (PlayerSelection == ESelection::Scissors && EnemySelection == ESelection::Paper)
	{
		PlayerScore++;
		CurrentResult = "You chose Scissors, Enemy chose Paper";
		Conclusion = "Scissors cuts Paper!";
	}
	else if (PlayerSelection == EnemySelection)
	{
		CurrentResult = "You and the enemy chose the same thing.";
		Conclusion = "";
	}


	if (PlayerScore == 3 || EnemyScore == 3)
	{
		FinalResult = (PlayerScore > EnemyScore) ? "You Win!" : "You Lose!";

		if (GameStateWidget_Class)
		{
			GameStateWidget = CreateWidget(GetWorld(), GameStateWidget_Class);
			GameStateWidget->AddToViewport();
			GetWorldTimerManager().SetTimer(Restart_Handle, this, &ARockPaperScissors_GameMode::RestartLevel, 5.0f, false);
		}
	}
}

void ARockPaperScissors_GameMode::RestartLevel() const
{
	UGameplayStatics::OpenLevel(this, FName(GetWorld()->GetName()), false);
}
