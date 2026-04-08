// Fill out your copyright notice in the Description page of Project Settings.


#include "soundPlay.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AsoundPlay::AsoundPlay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AsoundPlay::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AsoundPlay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::LeftMouseButton))
	{
		UGameplayStatics::PlaySoundAtLocation(this, soundToPlay, GetActorLocation());
	}

}



