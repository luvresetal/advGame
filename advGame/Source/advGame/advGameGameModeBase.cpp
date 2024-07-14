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
	
	scriptCounter = 0;
	NextPage(scriptCounter);
}

// 前準備
void AadvGameGameModeBase::SetupPlay()
{
	// 台本CSVの読み込み
	TArray<FString> row;
	LoadCsv(row, "script2.csv");

	scriptCountMax = row.Num();
	//UKismetSystemLibrary::PrintString(this, FString::FromInt(row.Num()), true, true, FColor::Cyan, 2.f, TEXT("None"));

	// 最初の行の内容をキーとする
	row[0].ParseIntoArray(scriptKey, TEXT(","), true);

	for (int i = 0; i != scriptKey.Num(); i++)
	{
		scriptData.Add(scriptKey[i]);
	}

	//キー以外の各要素をRowDataにキーと関連付けて登録
	TArray<FString> element;
	// 1行ずつ読み込む
	for (int i = 1; i != row.Num(); i++)
	{
		// 分解
		row[i].ParseIntoArray(element, TEXT(","), true);
		//UKismetSystemLibrary::PrintString(this, row[i], true, true, FColor::Cyan, 2.f, TEXT("None"));
		// 登録
		for (int j = 0; j != element.Num(); j++)
		{
			// 空白記号
			if (element[j].Equals("<BLK>", ESearchCase::CaseSensitive))
			{
				scriptData[scriptKey[j]].Add(" ");
			}
			else
			{
				scriptData[scriptKey[j]].Add(element[j]);
			}
		}
	}

	// キャラCSV、画像の読み込み
	LoadCsv(row, "chara.csv");

	// キャラCSVは1行目をキーにしない(台本CSVのimageをキーにするから)

	//キー以外の各要素をRowDataにキーと関連付けて登録
	FString elementTexAddr;
	UTexture2D* elementTex;
	// 1行ずつ読み込む
	for (int i = 1; i != row.Num(); i++)
	{
		// 分解
		row[i].ParseIntoArray(element, TEXT(","), true);
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

// CSV読み込み
void AadvGameGameModeBase::LoadCsv(TArray<FString>& row, FString fileName)
{
	FString dir = FPaths::ProjectDir() + "Content\\Script\\" + fileName;
	UKismetSystemLibrary::PrintString(this, dir, true, true, FColor::Cyan, 2.f, TEXT("None"));
	// ファイル名
	FString csvData;
	FFileHelper::LoadFileToString(csvData, *dir);

	// 改行コードで区切って配列にする
	csvData.ParseIntoArray(row, TEXT("\r\n"), true);
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
	NextPage(scriptCounter);
}

// ページめくり
void AadvGameGameModeBase::NextPage(int page)
{	// ウインドウに文字を表示
	if (page < scriptData[scriptKey[sNo]].Num())
	{
		// 名前表示切り替え
		messageWindow->tName->SetText(FText::FromString(scriptData[scriptKey[sName]][page]));
		//UKismetSystemLibrary::PrintString(this, scriptData[scriptKey[name]][page], true, true, FColor::Cyan, 2.f, TEXT("None"));
		// テクスチャ切り替え
		if (scriptData[scriptKey[sImage]][page] != " ")
		{
			messageWindow->iChara->SetBrushFromTexture(charaData[scriptData[scriptKey[sImage]][page]]);
		}
		messageWindow->tText->SetText(FText::FromString(scriptData[scriptKey[sText]][page]));
	}
}
