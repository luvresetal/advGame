// Copyright Epic Games, Inc. All Rights Reserved.


#include "advGameGameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include <UObject/UObjectGlobals.h>
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"


void AadvGameGameModeBase::BeginPlay()
{
	World = GEngine->GameViewport->GetWorld();

	SetupPlay();

	scriptCounter = 0;
	NextPage(scriptCounter);
}

// 前準備
void AadvGameGameModeBase::SetupPlay()
{
	// 台本CSVの読み込み
	load.loadScript(scriptData, scriptKey, "script2.csv");

	// キャラCSV、画像の読み込み
	load.loadChara(charaData, "chara2.csv");

	
	if (IsValid(widgetClass))
	{
		// ウインドウの作成
		messageWindow = Cast<UmessageWindow>(CreateWidget(GetWorld(), widgetClass));

		if (messageWindow != nullptr)
		{
			messageWindow->AddToViewport();

		}

	}
	// フェードインのあとにゲームが始まるようにアニメーションを関数をバインドさせる
	messageWindow->animEvent.BindDynamic(this, &AadvGameGameModeBase::SetupInput);
	messageWindow->BindToAnimationFinished(messageWindow->fade, messageWindow->animEvent);

	// フェードイン→Input設定
	messageWindow->PlayAnimation(messageWindow->fade);

	// フェードイン再生したらバインド解除しておく
	messageWindow->animEvent.Clear();
}


// Input設定
void AadvGameGameModeBase::SetupInput()
{
	// 入力を有効にする
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	// 左クリック
	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &AadvGameGameModeBase::PressButton);
}

// キー入力
void AadvGameGameModeBase::PressButton()
{
	scriptCounter++;
	timerCounter = 0;
	NextPage(scriptCounter);
}

// ページめくり
void AadvGameGameModeBase::NextPage(int page)
{	// ウインドウに文字を表示
	if (page < scriptData[scriptKey[sNo]].Num())
	{
		// 名前表示切り替え
		messageWindow->tName->SetText(FText::FromString(scriptData[scriptKey[sName]][page]));
		// テクスチャ切り替え
		if (scriptData[scriptKey[sChara]][page] != " ")
		{
			messageWindow->iChara->SetBrushFromTexture(charaData[scriptData[scriptKey[sChara]][page]]);
		}
		if (scriptData[scriptKey[sBg]][page] != " ")
		{
			//printf(scriptData[scriptKey[sBg]][page]);
			messageWindow->iBg->SetBrushFromTexture(charaData[scriptData[scriptKey[sBg]][page]]);
		}


		//UE_LOG(LogTemp, Log, TEXT("%s"), *scriptData[scriptKey[sText]][page].Left(10));
		nowText = scriptData[scriptKey[sText]][page];
		World->GetTimerManager().SetTimer(handle, this, &AadvGameGameModeBase::WaitScript, 0.008f, true);
		//UE_LOG(LogTemp, Log, TEXT("%s"), *scriptData[scriptKey[sText]][page].Left(i));
	}
	else
	{
		// 台本が最終行まで行ったのでエンディングに遷移

		// フェードアウトしてからエンディングに遷移するように関数をバインドさせる
		messageWindow->animEvent.BindDynamic(this, &AadvGameGameModeBase::ChangeLevel);
		messageWindow->BindToAnimationFinished(messageWindow->fade, messageWindow->animEvent);

		// フェードイン→Input設定
		messageWindow->PlayAnimationReverse(messageWindow->fade);

	}
}

void AadvGameGameModeBase::WaitScript()
{
	if (timerCounter <= nowText.Len()) {
		messageWindow->tText->SetText(FText::FromString(nowText.Left(timerCounter)));
		timerCounter++;
	}
}

// エンディングへ
void AadvGameGameModeBase::ChangeLevel()
{
	// バインド解除
	messageWindow->animEvent.Clear();

	// 遷移するLevelをLoadする
	UGameplayStatics::OpenLevel(GetWorld(), FName("ending"));
}
