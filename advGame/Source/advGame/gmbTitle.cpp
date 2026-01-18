// Fill out your copyright notice in the Description page of Project Settings.


#include "gmbTitle.h"
#include "wTitle.h"
#include <UObject/UObjectGlobals.h>

void AgmbTitle::BeginPlay()
{

	if (IsValid(WidgetClass))
	{
		wTitle = Cast<UwTitle>(CreateWidget(GetWorld(), WidgetClass));

		if (wTitle != nullptr)
		{
			wTitle->AddToViewport();
		}
	}
}