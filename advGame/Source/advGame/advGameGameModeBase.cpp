// Copyright Epic Games, Inc. All Rights Reserved.


#include "advGameGameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include <UObject/UObjectGlobals.h>
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"


void AadvGameGameModeBase::BeginPlay()
{
	// ��{CSV�̓ǂݍ���
	// CurrentDirectory�擾
	FString dir = FPaths::ProjectDir();
	// �t�@�C����
	FString scriptDir = dir + "Content\\Script\\script.csv";

	FString scriptCsvData;
	FFileHelper::LoadFileToString(scriptCsvData, *scriptDir);

	// �s���Ƃɕ�����
	TArray<FString> row;
	scriptCsvData.ParseIntoArray(row, TEXT("\n"), true);
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
			scriptData[scriptKey[j]].Add(element[j]);

		}
	}

	// �L����CSV�A�摜�̓ǂݍ���
	FString charaDir = dir + "Content\\Script\\chara.csv";
	FString charaCsvData;

	FFileHelper::LoadFileToString(charaCsvData, *charaDir);

	// �s���Ƃɕ�����
	charaCsvData.ParseIntoArray(row, TEXT("\r\n"), true);
	//UKismetSystemLibrary::PrintString(this, FString::FromInt(row.Num()), true, true, FColor::Cyan, 2.f, TEXT("None"));

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
	
	scriptCounter = 0;
	NextPage(scriptCounter);
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
		if (scriptData[scriptKey[sName]][page] != " ")
		{
			messageWindow->tName->SetText(FText::FromString(scriptData[scriptKey[sName]][page]));
			//UKismetSystemLibrary::PrintString(this, scriptData[scriptKey[name]][page], true, true, FColor::Cyan, 2.f, TEXT("None"));
		}
		// �e�N�X�`���؂�ւ�
		if (scriptData[scriptKey[sImage]][page] != " ")
		{
			messageWindow->iChara->SetBrushFromTexture(charaData[scriptData[scriptKey[sImage]][page]]);
		}
		messageWindow->tText->SetText(FText::FromString(scriptData[scriptKey[sText]][page]));
	}
}
