// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved
// Modifications (C) 2025 David Hasse - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PT_GridActor.generated.h"

UCLASS()
class PLANNINGTOOL_ET_API APT_GridActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APT_GridActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	* Creates a JSON representation of the grid configuration.
	*
	* @param InConfigId The configuration ID.
	* @param InPatientId The patient ID.
	* @param InElectrodePositionArray An array of electrode positions.
	* @param InElectrodeNameArray An array of electrode names.
	* @param InCenterPoint The center point of the grid.
	* @param InCellSize The size of each cell in the grid.
	* @param InCornerPointArray An array of corner points of the grid.
	* @param InRotation The rotation of the grid.
	* @param InRowCount The number of rows in the grid.
	* @param InColumnCount The number of columns in the grid.
	* @return A JSON string representing the grid configuration.
	*/
	UFUNCTION(BlueprintCallable, Category = "GRID_SELECTOR")
	FString CreateGridJSON(const FString& InConfigId, const FString& InPatientId, const TArray<FVector>& InElectrodePositionArray, const TArray<FString>& InElectrodeNameArray, const FVector& InCenterPoint, const double& InCellSize, const TArray<FVector>& InCornerPointArray, const FRotator& InRotation, const int& InRowCount, const int& InColumnCount);

};
