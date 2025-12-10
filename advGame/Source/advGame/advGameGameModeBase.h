// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "messageWindow.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "loadData.h"
#include "advGameGameModeBase.generated.h"



UCLASS()
class ADVGAME_API AadvGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	// 開始時の設定
	void BeginPlay() override;

	// 前準備
	void SetupPlay();

	// �{�^������

	// ボタン入力
	void PressButton();

	// ページめくり
	void NextPage(int page);

	// 
	void WaitScript();


protected:
	// Input設定
	void SetupInput();

	UPROPERTY(EditAnywhere, Category = "Class Types")
	TSubclassOf<UUserWidget> widgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UmessageWindow* messageWindow;

	UWorld* World;

	int timerCounter;
	FTimerHandle handle;

	// 台本データ
	TMap<FString, TArray<FString>> scriptData;
	TArray<FString> scriptKey;

	// 台本CSVのカラム名
	enum scriptName {
		sNo,
		sName,
		sText,
		sChara,
		sPos,
		sBg
	};

	TMap<FString, UTexture2D*> charaData;
	TArray<FString> charaKey;
	// キャラCSVのカラム名
	enum charaName {
		cNo,
		cName,
		cTexture
	};

	UTexture2D* luluwa;
	UTexture2D* cain;

	int scriptCountMax;
	int scriptCounter;

	FString nowText;

	loadTest test;
};
