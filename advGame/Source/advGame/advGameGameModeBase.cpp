// Copyright Epic Games, Inc. All Rights Reserved.


#include "advGameGameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include <UObject/UObjectGlobals.h>
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"


void AadvGameGameModeBase::BeginPlay()
{
	SetupPlay();
	
	World = GEngine->GameViewport->GetWorld();

	scriptCounter = 0;
	NextPage(scriptCounter);
}

// 前準備
void AadvGameGameModeBase::SetupPlay()
{
	UPROPERTY();
	//AloadData* setup = NewObject<AloadData>();
	// 台本CSVの読み込み
	TArray<FString> rowTxt;
	//setup->LoadCsv(row, "script2.csv");
	load.LoadCsv(rowTxt, "script2.csv");

	scriptCountMax = rowTxt.Num();
	//UKismetSystemLibrary::PrintString(this, FString::FromInt(row.Num()), true, true, FColor::Cyan, 2.f, TEXT("None"));

	// 最初の行の内容をキーとする
	rowTxt[0].ParseIntoArray(scriptKey, TEXT(","), true);

	for (int i = 0; i != scriptKey.Num(); i++)
	{
		scriptData.Add(scriptKey[i]);
	}

	//キー以外の各要素をRowDataにキーと関連付けて登録
	TArray<FString> element;
	// 1行ずつ読み込む
	for (int i = 1; i != rowTxt.Num(); i++)
	{
		// 分解
		rowTxt[i].ParseIntoArray(element, TEXT(","), true);
		//UKismetSystemLibrary::PrintString(this, row[i], true, true, FColor::Cyan, 2.f, TEXT("None"));
		// 登録
		for (int j = 0; j != element.Num(); j++)
		{
			// 空白記号
			if (element[j].Equals("<NONE>", ESearchCase::CaseSensitive))
			{
				scriptData[scriptKey[j]].Add(" ");
			}
			else
			{
				// 改行文字があったら改行コードに変換
				if (element[j].Find("\\n", ESearchCase::IgnoreCase, ESearchDir::FromStart, 0) != -1)
					element[j] = element[j].Replace(L"\\n", L"\n", ESearchCase::IgnoreCase);
				scriptData[scriptKey[j]].Add(element[j]);
			}
		}
	}

	// キャラCSV、画像の読み込み
 	TArray<FString> rowImg;
	//setup->LoadCsv(row, "chara2.csv");
	load.LoadCsv(rowImg, "chara2.csv");

	// キャラCSVは1行目をキーにしない(台本CSVのimageをキーにするから)

	//キー以外の各要素をRowDataにキーと関連付けて登録
	FString elementTexAddr;
	UTexture2D* elementTex;
	// 1行ずつ読み込む
	for (int i = 1; i != rowImg.Num(); i++)
	{
		// 分解
		rowImg[i].ParseIntoArray(element, TEXT(","), true);
		//UKismetSystemLibrary::PrintString(this, row[i], true, true, FColor::Cyan, 2.f, TEXT("None"));
		// テクスチャを読み込んでTMapに格納
		FString aaa = element[cTexture];
		elementTexAddr = TEXT("/Game/assets/") + element[cTexture];
		elementTex = LoadObject<UTexture2D>(NULL, *elementTexAddr, NULL, LOAD_None, NULL);
		charaData.Add(element[cName], elementTex);
		if (charaData.Add(element[cName], elementTex) == nullptr) {
			UKismetSystemLibrary::PrintString(this, "Falure....", true, true, FColor::Cyan, 2.f, TEXT("None"));
		}
	}

	// ウインドウの作成
	if (IsValid(widgetClass))
	{
		messageWindow = Cast<UmessageWindow>(CreateWidget(GetWorld(), widgetClass));

		if (messageWindow != nullptr)
		{
			messageWindow->AddToViewport();
		}
	}

	SetupInput();
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
}

void AadvGameGameModeBase::WaitScript()
{
	if (timerCounter <= nowText.Len()) {
		messageWindow->tText->SetText(FText::FromString(nowText.Left(timerCounter)));
		timerCounter++;
	}
}
