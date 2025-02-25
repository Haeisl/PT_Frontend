// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved
// Modifications (C) 2025 David Hasse - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PT_SlicingActor.generated.h"

/**
 * @brief A class representing a slicing actor.
 * 
 * This actor is responsible for handling slicing operations within the program.
 */
UCLASS()
class PLANNINGTOOL_ET_API APT_SlicingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	/**
	* @brief Sets default values for this actor's properties.
	*/
	APT_SlicingActor();

protected:
	/**
	* @brief Called when the game starts or when spawned.
	*/
	virtual void BeginPlay() override;

public:	
	/**
	* @brief Called every frame.
	* 
	* @param DeltaTime The time elapsed since the last frame.
	*/
	virtual void Tick(float DeltaTime) override;

};
