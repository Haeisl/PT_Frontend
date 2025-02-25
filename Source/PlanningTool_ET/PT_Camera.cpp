// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved


#include "PT_Camera.h"

// Sets default values
APT_Camera::APT_Camera()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APT_Camera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APT_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APT_Camera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

