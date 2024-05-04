// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "messageWindow.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "advGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ADVGAME_API AadvGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	// �J�n���̐ݒ�
	void BeginPlay() override;

	// �{�^������
	void PressButton();

	// �y�[�W�߂���
	void NextPage(int page);

protected:
	// Input�ݒ�
	void SetupInput();

	UPROPERTY(EditAnywhere, Category = "Class Types")
	TSubclassOf<UUserWidget> widgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UmessageWindow* messageWindow;

	// ��{�f�[�^
	TMap<FString, TArray<FString>> scriptData;
	TArray<FString> scriptKey;

	// ��{CSV�̃J������
	enum scriptName {
		sNo,
		sName,
		sText,
		sImage,
		sPos
	};

	TMap<FString, UTexture2D*> charaData;
	TArray<FString> charaKey;
	// �L����CSV�̃J������
	enum charaName {
		cNo,
		cName,
		cTexture
	};

	UTexture2D* luluwa;
	UTexture2D* cain;

	int scriptCountMax;
	int scriptCounter;
};
