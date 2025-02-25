// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved
// Modifications (C) 2025 David Hasse - All Rights Reserved

/**
 * @file PT_HistogramBlueprintLibrary.h
 * @brief Header file for the UPT_HistogramBlueprintLibrary class, which provides functionality for creating histogram textures.
 *
 * This file contains the declaration of the UPT_HistogramBlueprintLibrary class, which includes methods for creating histogram textures
 * from data arrays.
 */

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PT_HistogramBlueprintLibrary.generated.h"

/**
 * @brief A blueprint function library class for creating histogram textures.
 * 
 * This class provides functionality to create histogram textures from data arrays.
 */
UCLASS()
class PLANNINGTOOL_ET_API UPT_HistogramBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
  * @brief Creates a histogram texture from the given data.
  * 
  * This function creates a histogram texture from the provided data array and number of bins.
  * 
  * @param InData The input data array.
  * @param NumBins The number of bins for the histogram.
  * @return UTexture2D* The created histogram texture.
  */
	UFUNCTION(BlueprintCallable, Category = "Histogram")
	static UTexture2D* CreateHistogramTexture(const TArray<double>& InData, const int32 NumBins, bool bLogScale, bool bConstrainXMin, float XMin, bool bConstrainXMax, float XMax, bool bGridLines);

};
