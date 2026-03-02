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

	wEnding->PlayAnimation(wEnding->fade);
}

void AgmbEnding::PressButton()
{
	// アニメーション再生中は入力を受け付けない
	if (!(wEnding->IsPlayingAnimation()))
	{
		// 左クリックでタイトルのレベルへ移動
		// フェードアウトのアニメーションとレベル移動の関数をバインド
		wEnding->finAnim.BindDynamic(this, &AgmbEnding::ChangeLevel);
		wEnding->BindToAnimationFinished(wEnding->fade, wEnding->finAnim);

		// アニメーション実行
		wEnding->PlayAnimationReverse(wEnding->fade);
	}
}

void AgmbEnding::ChangeLevel()
{
	// バインド解除
	wEnding->finAnim.Clear();

	// 遷移するLevelをLoadする
	UGameplayStatics::OpenLevel(GetWorld(), FName("title"));
}