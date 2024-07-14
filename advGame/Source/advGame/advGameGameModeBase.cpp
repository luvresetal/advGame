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

// �O����
void AadvGameGameModeBase::SetupPlay()
{
	// ��{CSV�̓ǂݍ���
	TArray<FString> row;
	LoadCsv(row, "script2.csv");

	scriptCountMax = row.Num();
	//UKismetSystemLibrary::PrintString(this, FString::FromInt(row.Num()), true, true, FColor::Cyan, 2.f, TEXT("None"));

	// �ŏ��̍s�̓��e���L�[�Ƃ���
	row[0].ParseIntoArray(scriptKey, TEXT(","), true);

	for (int i = 0; i != scriptKey.Num(); i++)
	{
		scriptData.Add(scriptKey[i]);
	}

	//�L�[�ȊO�̊e�v�f��RowData�ɃL�[�Ɗ֘A�t���ēo�^
	TArray<FString> element;
	// 1�s���ǂݍ���
	for (int i = 1; i != row.Num(); i++)
	{
		// ����
		row[i].ParseIntoArray(element, TEXT(","), true);
		//UKismetSystemLibrary::PrintString(this, row[i], true, true, FColor::Cyan, 2.f, TEXT("None"));
		// �o�^
		for (int j = 0; j != element.Num(); j++)
		{
			// �󔒋L��
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

	// �L����CSV�A�摜�̓ǂݍ���
	LoadCsv(row, "chara.csv");

	// �L����CSV��1�s�ڂ��L�[�ɂ��Ȃ�(��{CSV��image���L�[�ɂ��邩��)

	//�L�[�ȊO�̊e�v�f��RowData�ɃL�[�Ɗ֘A�t���ēo�^
	FString elementTexAddr;
	UTexture2D* elementTex;
	// 1�s���ǂݍ���
	for (int i = 1; i != row.Num(); i++)
	{
		// ����
		row[i].ParseIntoArray(element, TEXT(","), true);
		//UKismetSystemLibrary::PrintString(this, row[i], true, true, FColor::Cyan, 2.f, TEXT("None"));
		// �e�N�X�`����ǂݍ����TMap�Ɋi�[
		FString aaa = element[cTexture];
		elementTexAddr = TEXT("/Game/assets/") + element[cTexture];
		elementTex = LoadObject<UTexture2D>(NULL, *elementTexAddr, NULL, LOAD_None, NULL);
		charaData.Add(element[cName], elementTex);
		if (charaData.Add(element[cName], elementTex) == nullptr) {
			UKismetSystemLibrary::PrintString(this, "Falure....", true, true, FColor::Cyan, 2.f, TEXT("None"));
		}
	}

	// �E�C���h�E�̍쐬
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

// CSV�ǂݍ���
void AadvGameGameModeBase::LoadCsv(TArray<FString>& row, FString fileName)
{
	FString dir = FPaths::ProjectDir() + "Content\\Script\\" + fileName;
	UKismetSystemLibrary::PrintString(this, dir, true, true, FColor::Cyan, 2.f, TEXT("None"));
	// �t�@�C����
	FString csvData;
	FFileHelper::LoadFileToString(csvData, *dir);

	// ���s�R�[�h�ŋ�؂��Ĕz��ɂ���
	csvData.ParseIntoArray(row, TEXT("\r\n"), true);
}

// Input�ݒ�
void AadvGameGameModeBase::SetupInput()
{
	// ���͂�L���ɂ���
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	// ���N���b�N
	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &AadvGameGameModeBase::PressButton);
}

// �L�[����
void AadvGameGameModeBase::PressButton()
{
	scriptCounter++;
	NextPage(scriptCounter);
}

// �y�[�W�߂���
void AadvGameGameModeBase::NextPage(int page)
{	// �E�C���h�E�ɕ�����\��
	if (page < scriptData[scriptKey[sNo]].Num())
	{
		// ���O�\���؂�ւ�
		messageWindow->tName->SetText(FText::FromString(scriptData[scriptKey[sName]][page]));
		//UKismetSystemLibrary::PrintString(this, scriptData[scriptKey[name]][page], true, true, FColor::Cyan, 2.f, TEXT("None"));
		// �e�N�X�`���؂�ւ�
		if (scriptData[scriptKey[sImage]][page] != " ")
		{
			messageWindow->iChara->SetBrushFromTexture(charaData[scriptData[scriptKey[sImage]][page]]);
		}
		messageWindow->tText->SetText(FText::FromString(scriptData[scriptKey[sText]][page]));
	}
}
