// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved
// Modifications (C) 2025 David Hasse - All Rights Reserved

/**
 * @file PT_ElectrodeAreaActor.h
 * @brief Header file for the APT_ElectrodeAreaActor class.
 *
 * This file contains the declaration of the APT_ElectrodeAreaActor class, which is responsible for handling electrode area operations.
 * It includes methods for processing HTTP response data, finding nearest neighbors, and calculating barycentric weights.
 *
 * @author Jan-Vincent Mock
 * @date 2024
 */

#pragma once

#include "CoreMinimal.h"
#include "PT_HTTPComponent.h"
#include "GameFramework/Actor.h"
#include "PT_ElectrodeAreaActor.generated.h"

/**
 * @class APT_ElectrodeAreaActor
 * @brief A class that represents an electrode area actor.
 *
 * This class is responsible for handling various operations related to electrode areas, such as processing HTTP response data,
 * finding nearest neighbors, and calculating barycentric weights.
 */
UCLASS()
class PLANNINGTOOL_ET_API APT_ElectrodeAreaActor : public AActor
{
	GENERATED_BODY()

public:
	/**
  * @brief Sets default values for this actor's properties.
  */
	APT_ElectrodeAreaActor();

	/**
  * @brief Called every frame.
  * @param DeltaTime The time elapsed since the last frame.
  */
	virtual void Tick(float DeltaTime) override;

	/**
  * @brief Processes the response data from an HTTP component and extracts various parameters.
  *
  * @param InHttpComponent The HTTP component containing the response data.
  * @param OutCenter The center point extracted from the response data.
  * @param OutA The first corner point extracted from the response data.
  * @param OutB The second corner point extracted from the response data.
  * @param OutC The third corner point extracted from the response data.
  * @param OutD The fourth corner point extracted from the response data.
  * @param OutRotation The rotation extracted from the response data.
  * @param OutRows The number of rows extracted from the response data.
  * @param outColumns The number of columns extracted from the response data.
  * @param outCellSize The cell size extracted from the response data.
  * @param OutNumber The number of electrodes extracted from the response data.
  * @param OutElectrodePositions The positions of the electrodes extracted from the response data.
  */
	UFUNCTION(BlueprintCallable, Category = "ELECTRODE_AREA")
	void ProcessResponseData(const UPT_HTTPComponent* InHttpComponent, FVector& OutCenter, FVector& OutA, FVector& OutB, FVector& OutC, FVector& OutD, FRotator& OutRotation, int& OutRows, int& outColumns, double& outCellSize, int& OutNumber, TArray<FVector>& OutElectrodePositions);

	/**
  * @brief Processes the validation response data from an HTTP component and extracts various parameters.
  *
  * @param InHttpComponent The HTTP component containing the response data.
  * @param OutElectrodeCount The number of electrodes extracted from the response data.
  * @param OutSuccessfullElectrodeIndex The indices of successfully simulated electrodes.
  * @param OutIsCorrupted Indicates whether the data is corrupted.
  */
	UFUNCTION(BlueprintCallable, Category = "ELECTRODE_AREA")
	void ProcessValidationResponseData(const UPT_HTTPComponent* InHttpComponent, int32& OutElectrodeCount, TArray<int32>& OutSuccessfullElectrodeIndex, bool& OutIsCorrupted);

	/**
  * @brief Finds the nearest neighbors to a given point within a grid.
  *
  * @param InPoint The point for which to find the nearest neighbors.
  * @param InGrid The grid of points to search within.
  * @param OutNearestNeighborsGridIndicies The indices of the nearest neighbors within the grid.
  * @return An array of the nearest neighbor points.
  */
	UFUNCTION(BlueprintCallable, Category = "ELECTRODE_AREA")
	TArray<FVector> FindNearestNeighbors(const FVector& InPoint, const TArray<FVector>& InGrid, TArray<int>& OutNearestNeighborsGridIndicies);

	/**
  * @brief Calculates the barycentric weights for a point within a triangle.
  *
  * @param InPoint The point for which to calculate the weights.
  * @param InA The first vertex of the triangle.
  * @param InB The second vertex of the triangle.
  * @param InC The third vertex of the triangle.
  * @param OutWeightA The weight corresponding to the first vertex.
  * @param OutWeightB The weight corresponding to the second vertex.
  * @param OutWeightC The weight corresponding to the third vertex.
  */
	UFUNCTION(BlueprintCallable, Category = "ELECTRODE_AREA")
	void BarycentricWeightCalculation(const FVector& InPoint, const FVector& InA, const FVector& InB, const FVector& InC, double& OutWeightA, double& OutWeightB, double& OutWeightC);

protected:
	/**
  * @brief Called when the game starts or when spawned.
  */
	virtual void BeginPlay() override;

private:
	/**
  * @struct FDistanceAndPoint
  * @brief A structure to hold distance and point information.
  */
	struct FDistanceAndPoint
	{
		double Distance; ///< The distance value.
		FVector Point; ///< The point value.
		int gridIndex; ///< The index of the point in the grid.
	};

};
