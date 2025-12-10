// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "loadData.generated.h"

/**
 * 
 */
UCLASS()

class ADVGAME_API AloadData : public AGameStateBase
{
	GENERATED_BODY()

public:
	AloadData();
	~AloadData();

	// csv�ǂݍ���
	static void LoadCsv(TArray<FString>& row, FString fileName);
	
};

class loadTest
{
public:
	loadTest();
	~loadTest();

	void LoadCsv(TArray<FString>& row, FString fileName);
};
