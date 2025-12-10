// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
//#include "loadData.generated.h"



class loadData
{
public:
	loadData();
	~loadData();

	void LoadCsv(TArray<FString>& row, FString fileName);
};
