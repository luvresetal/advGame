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

	void BeginPlay() override;

	void PressButton();

	TObjectPtr<UWorld> LoadLevel;
	
};
