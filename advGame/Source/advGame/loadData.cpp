// Fill out your copyright notice in the Description page of Project Settings.


#include "loadData.h"

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