// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "wEnding.generated.h"

/**
 * 
 */
UCLASS()
class ADVGAME_API UwEnding : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* fadeIn = nullptr;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* fadeOut = nullptr;

	// フェードアウト後にレベル移動するための処理
	// デリゲート
	FWidgetAnimationDynamicEvent finAnim;

	
};
