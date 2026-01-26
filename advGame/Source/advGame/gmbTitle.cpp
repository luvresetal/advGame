// Fill out your copyright notice in the Description page of Project Settings.


#include "gmbTitle.h"
#include "wTitle.h"
#include "Kismet/GameplayStatics.h"
#include <UObject/UObjectGlobals.h>

void AgmbTitle::BeginPlay()
{
	// 画面表示
	if (IsValid(WidgetClass))
	{
		wTitle = Cast<UwTitle>(CreateWidget(GetWorld(), WidgetClass));

		if (wTitle != nullptr)
		{
			wTitle->AddToViewport();
		}
	}

	// Input設定
	// 入力を有効にする
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	// 左クリック
	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &AgmbTitle::PressButton);
}

void AgmbTitle::PressButton()
{
	// 左クリックで本編のレベルへ移動
	// まずはフェードアウト入れたい

	// 遷移するLevelをLoadする
	UGameplayStatics::OpenLevel(GetWorld(), FName("adv"));

}