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
	// 台本データ
	void loadScript(TMap<FString, TArray<FString>>& scriptData, TArray<FString>& scriptKey, FString fileName);
	// キャラデータ
	void loadChara(TMap<FString, UTexture2D*>& charaData, FString fileName);

private:
	// CSV読み込み
	void LoadCsv(TArray<FString>& row, FString fileName);

	// キャラCSVのカラム名
	enum charaName {
		cNo,
		cName,
		cTexture
	};
};
