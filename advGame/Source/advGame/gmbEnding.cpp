// Fill out your copyright notice in the Description page of Project Settings.


#include "gmbEnding.h"
#include "wEnding.h"
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
}