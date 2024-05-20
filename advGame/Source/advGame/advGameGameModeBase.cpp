// Copyright Epic Games, Inc. All Rights Reserved.


#include "advGameGameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include <UObject/UObjectGlobals.h>
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"


void AadvGameGameModeBase::BeginPlay()
{
	// 台本CSVの読み込み
	// CurrentDirectory取得
	FString dir = FPaths::ProjectDir();
	// ファイル名
	FString scriptDir = dir + "Content\\Script\\script.csv";

	FString scriptCsvData;
	FFileHelper::LoadFileToString(scriptCsvData, *scriptDir);

	// 行ごとに分ける
	TArray<FString> row;
	scriptCsvData.ParseIntoArray(row, TEXT("\n"), true);
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
			scriptData[scriptKey[j]].Add(element[j]);

		}
	}

	// キャラCSV、画像の読み込み
	FString charaDir = dir + "Content\\Script\\chara.csv";
	FString charaCsvData;

	FFileHelper::LoadFileToString(charaCsvData, *charaDir);

	// 行ごとに分ける
	charaCsvData.ParseIntoArray(row, TEXT("\r\n"), true);
	//UKismetSystemLibrary::PrintString(this, FString::FromInt(row.Num()), true, true, FColor::Cyan, 2.f, TEXT("None"));

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
	
	scriptCounter = 0;
	NextPage(scriptCounter);
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
		if (scriptData[scriptKey[sName]][page] != " ")
		{
			messageWindow->tName->SetText(FText::FromString(scriptData[scriptKey[sName]][page]));
			//UKismetSystemLibrary::PrintString(this, scriptData[scriptKey[name]][page], true, true, FColor::Cyan, 2.f, TEXT("None"));
		}
		// テクスチャ切り替え
		if (scriptData[scriptKey[sImage]][page] != " ")
		{
			messageWindow->iChara->SetBrushFromTexture(charaData[scriptData[scriptKey[sImage]][page]]);
		}
		messageWindow->tText->SetText(FText::FromString(scriptData[scriptKey[sText]][page]));
	}
}
