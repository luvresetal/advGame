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

	wTitle->PlayAnimation(wTitle->fadeIn);
}

void AgmbTitle::PressButton()
{
	// 左クリックで本編のレベルへ移動
	// フェードアウトのアニメーションとレベル移動の関数をバインド
	wTitle->finAnim.BindDynamic(this, &AgmbTitle::ChangeLevel);
	wTitle->BindToAnimationFinished(wTitle->fadeOut, wTitle->finAnim);
	
	// アニメーション実行
	wTitle->PlayAnimation(wTitle->fadeOut);
}

void AgmbTitle::ChangeLevel()
{
	// バインド解除
	wTitle->finAnim.Clear();

	// 遷移するLevelをLoadする
	UGameplayStatics::OpenLevel(GetWorld(), FName("adv"));
}