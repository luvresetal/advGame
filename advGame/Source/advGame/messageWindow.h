// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "messageWindow.generated.h"

/**
 * 
 */
UCLASS()
class ADVGAME_API UmessageWindow : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* tName;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* tText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* iChara;
	
};
