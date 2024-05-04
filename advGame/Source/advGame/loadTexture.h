// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class ADVGAME_API loadTexture
{
public:
	loadTexture();
	~loadTexture();

	UFUNCTION(BlueprintCallable, Category = "Test")
	static bool LoadTextureAssetFromFile(const FString& FilePath, class UTexture2D*& LoadedTexture);
};
