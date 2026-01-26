// Fill out your copyright notice in the Description page of Project Settings.


#include "gmbEnding.h"
#include "wEnding.h"
#include "Kismet/GameplayStatics.h"
#include <UObject/UObjectGlobals.h>

void AgmbEnding::BeginPlay()
{

	if (IsValid(WidgetClass))
	{
		wEnding = Cast<UwEnding>(CreateWidget(GetWorld(), WidgetClass));

		if (wEnding != nullptr)
		{
			wEnding->AddToViewport();
		}
	}

	// Input設定
// 入力を有効にする
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	// 左クリック
	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &AgmbEnding::PressButton);
}

void AgmbEnding::PressButton()
{
	// 左クリックでタイトルのレベルへ移動
	// まずはフェードアウト入れたい

	// 遷移するLevelをLoadする
	UGameplayStatics::OpenLevel(GetWorld(), FName("title"));

}