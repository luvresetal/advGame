// Fill out your copyright notice in the Description page of Project Settings.


#include "loadData.h"
#include "Kismet/KismetSystemLibrary.h"

loadData::loadData()
{
}

loadData::~loadData()
{
}
// CSV読み込み
void loadData::LoadCsv(TArray<FString>& row, FString fileName)
{
	FString dir = FPaths::ProjectDir() + "Content\\Script\\" + fileName;
	//UKismetSystemLibrary::PrintString(this, dir, true, true, FColor::Cyan, 2.f, TEXT("None"));
	// ファイル名
	FString csvData;
	FFileHelper::LoadFileToString(csvData, *dir);

	// 改行コードで区切って配列にする
	csvData.ParseIntoArray(row, TEXT("\r\n"), true);
}

// 台本読み込み
void loadData::loadScript(TMap<FString, TArray<FString>>& scriptData, TArray<FString>& scriptKey, FString fileName)
{
	TArray<FString> row;
	LoadCsv(row, fileName);

	//キー以外の各要素をRowDataにキーと関連付けて登録
	TArray<FString> element;

	// 最初の行の内容をキーとする
	row[0].ParseIntoArray(scriptKey, TEXT(","), true);
	for (int i = 0; i != scriptKey.Num(); i++)
	{
		scriptData.Add(scriptKey[i]);
	}

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
}
// キャラデータ読み込み
void loadData::loadChara(TMap<FString, UTexture2D*>& charaData, FString fileName)
{
	TArray<FString> row;
	LoadCsv(row, fileName);

	// キャラCSVは1行目をキーにしない(台本CSVのimageをキーにするから)

	//キー以外の各要素をRowDataにキーと関連付けて登録
	TArray<FString> element;
	FString elementTexAddr;
	UTexture2D* elementTex;
	// 1行ずつ読み込む
	for (int i = 1; i != row.Num(); i++)
	{
		// 分解
		row[i].ParseIntoArray(element, TEXT(","), true);
		//UKismetSystemLibrary::PrintString(this, row[i], true, true, FColor::Cyan, 2.f, TEXT("None"));
		// テクスチャを読み込んでTMapに格納

		// キャラ画像の読み込み
		if (element[cClassified].Equals("chara", ESearchCase::CaseSensitive))
		{
			elementTexAddr = TEXT("/Game/assets/charactor/") + element[cTexture];
		}
		// 背景画像の読み込み
		else if(element[cClassified].Equals("background", ESearchCase::CaseSensitive))
		{
			elementTexAddr = TEXT("/Game/assets/backGround/") + element[cTexture];
		}

		//elementTexAddr = TEXT("/Game/assets/") + element[cTexture];
		elementTex = LoadObject<UTexture2D>(NULL, *elementTexAddr, NULL, LOAD_None, NULL);
		charaData.Add(element[cName], elementTex);
		//if (charaData.Add(element[cName], elementTex) == nullptr) {
		//	UKismetSystemLibrary::PrintString(this, "Falure....", true, true, FColor::Cyan, 2.f, TEXT("None"));
		//}
	}
}