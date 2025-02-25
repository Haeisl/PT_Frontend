// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved
// Modifications (C) 2025 David Hasse - All Rights Reserved

/**
 * @file PT_Camera.h
 * @brief Header file for the APT_Camera class.
 * 
 * This file contains the declaration of the APT_Camera class, which is responsible for handling camera character behavior.
 * 
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PT_Camera.generated.h"

/**
 * @class APT_Camera
 * @brief A class that represents a camera character.
 * 
 * This class is responsible for handling the behavior of the camera character within the game.
 */
UCLASS()
class PLANNINGTOOL_ET_API APT_Camera : public ACharacter
{
	GENERATED_BODY()

public:
	/**
  * @brief Sets default values for this character's properties.
  */
	APT_Camera();

protected:
	/**
  * @brief Called when the game starts or when spawned.
  */
	virtual void BeginPlay() override;

public:	
	/**
  * @brief Called every frame.
  * @param DeltaTime The time elapsed since the last frame.
  */
	virtual void Tick(float DeltaTime) override;

	/**
  * @brief Called to bind functionality to input.
  * @param PlayerInputComponent The input component to bind functionality to.
  */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

};
