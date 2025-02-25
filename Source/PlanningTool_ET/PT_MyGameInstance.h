// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved
// Modifications (C) 2025 David Hasse - All Rights Reserved

/**
 * @file PT_MyGameInstance.h
 * @brief Header file for the UPT_MyGameInstance class, which provides game instance functionality.
 *
 * This file contains the declaration of the UPT_MyGameInstance class, which includes methods for initializing the game instance,
 * setting and getting interpolated data, and managing HTTP components.
 */

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PT_HTTPComponent.h"
#include "PT_MyGameInstance.generated.h"

/**
 * @brief A game instance class for managing game-wide systems and data.
 * 
 * This class provides functionality to initialize the game instance, manage HTTP components, and handle interpolated data.
 */
UCLASS()
class PLANNINGTOOL_ET_API UPT_MyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	/**
  * @brief Initializes the game instance.
  * 
  * This function is called to initialize the game instance.
  */
	virtual void Init() override;

	/** 
  * @brief The HTTP component used for making HTTP requests.
  */
	UPROPERTY(BlueprintReadOnly, Category = "HTTP")
	UPT_HTTPComponent* HTTPComponent;

	/** 
  * @brief The array of interpolated data.
  */
	UPROPERTY(BlueprintReadWrite, Category = "Interpolated Data")
	TArray<double> InterpolatedData;

	/**
  * @brief Sets the interpolated data.
  * 
  * This function sets the interpolated data array with the provided data.
  * 
  * @param InData The input data array to set.
  */
	UFUNCTION(BlueprintCallable, Category = "Interpolated Data")
	void SetInterpolatedData(const TArray<double>& InData);

	/**
  * @brief Gets the interpolated data.
  * 
  * This function returns the current interpolated data array.
  * 
  * @return TArray<double> The current interpolated data array.
  */
	UFUNCTION(BlueprintCallable, Category = "Interpolated Data")
	TArray<double> GetInterpolatedData();
};