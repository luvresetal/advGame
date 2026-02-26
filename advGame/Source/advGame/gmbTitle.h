// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "gmbTitle.generated.h"

/**
 * 
 */
UCLASS()
class ADVGAME_API AgmbTitle : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Class Types")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UwTitle* wTitle;

	// 下準備
	void BeginPlay() override;

	// 左クリックの処理
	void PressButton();

	// レベル移動
	UFUNCTION(BlueprintCallable)
	void ChangeLevel();

	TObjectPtr<UWorld> LoadLevel;
	
};
