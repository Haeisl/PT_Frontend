// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved
// Modifications (C) 2025 David Hasse - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PT_StructContainer.h"
#include "PT_HTTPComponent.h"
#include "PT_SimulationComponent.generated.h"

/**
 * @brief Simulation component for the Epilepsy Therapy Planning Tool.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PLANNINGTOOL_ET_API UPT_SimulationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/**
	 * @brief Sets default values for this component's properties.
	 */
	UPT_SimulationComponent();

protected:
	/**
	 * @brief Called when the game starts.
	 */
	virtual void BeginPlay() override;

public:
	/**
	 * @brief Called every frame.
	 * @param DeltaTime Time since the last frame.
	 * @param TickType Type of tick.
	 * @param ThisTickFunction Tick function.
	 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @brief Maps input data to a Plasma colormap.
	 * @param InData Input data array.
	 * @param InDataTagIndex Index of the data tag.
	 * @param InPercentileMinValue Minimum percentile value.
	 * @param InPercentileMaxValue Maximum percentile value.
	 * @return TArray<FLinearColor> Array of colors mapped to the Plasma colormap.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_SIMULATION_DATA")
	TArray<FLinearColor> MapToPlasmaColormap(const TArray<double>& InData, const int32& InDataTagIndex, const double& InPercentileMinValue, const double& InPercentileMaxValue);

	/**
	 * @brief Maps input data to a Jet colormap.
	 * @param InData Input data array.
	 * @param InDataTagIndex Index of the data tag.
	 * @param InPercentileMinValue Minimum percentile value.
	 * @param InPercentileMaxValue Maximum percentile value.
	 * @return TArray<FLinearColor> Array of colors mapped to the Jet colormap.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_SIMULATION_DATA")
	TArray<FLinearColor> MapToJetColormap(const TArray<double>& Data, const int32& InDataTagIndex, const double& InPercentileMinValue, const double& InPercentileMaxValue);

	/**
	 * @brief Maps input data to a greyscale colormap.
	 * @param InData Input data array.
	 * @param InDataTagIndex Index of the data tag.
	 * @param InPercentileMinValue Minimum percentile value.
	 * @param InPercentileMaxValue Maximum percentile value.
	 * @return TArray<FLinearColor> Array of colors mapped to the greyscale colormap.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_SIMULATION_DATA")
	TArray<FLinearColor> MapToGreyscaleColormap(const TArray<double>& InData, const int32& InDataTagIndex, const double& InPercentileMinValue, const double& InPercentileMaxValue);

	/**
	 * @brief Calculates vertex colors.
	 * @param InVertexArrayLength Length of the vertex array.
	 * @return TArray<FLinearColor> Array of vertex colors.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_SIMULATION_DATA")
	TArray<FLinearColor> CalculateVertexColors(const int32& InVertexArrayLength);

	/**
	 * @brief Performs barycentric interpolation for simulation data.
	 * @param InElectrodeIndexA The index of the first electrode.
	 * @param InElectrodeIndexB The index of the second electrode.
	 * @param InElectrodeIndexC The index of the third electrode.
	 * @param InDataTagIndex The index of the data tag.
	 * @param InWeightA The weight for the first electrode.
	 * @param InWeightB The weight for the second electrode.
	 * @param InWeightC The weight for the third electrode.
	 * @param OutInterpolatedSimulationMagnitudeDataArray The output array for interpolated magnitude data.
	 * @param OutInterpolatedSimulationVectorfieldDataArray The output array for interpolated vector field data.
	 * @param OutMeanMagnitude The output mean magnitude.
	 * @param OutMeanVectorField The output mean vector field.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_SIMULATION_DATA")
	void BarycentricInterpolation(const int32& InElectrodeIndexA, const int32& InElectrodeIndexB, const int32& InElectrodeIndexC, const int32& InDataTagIndex, const double& InWeightA, const double& InWeightB, const double& InWeightC, TArray<double>& OutInterpolatedSimulationMagnitudeDataArray, TArray<FVector>& OutInterpolatedSimulationVectorfieldDataArray, double& OutMeanMagnitude, FVector& OutMeanVectorField);

	/**
	 * @brief Processes interpolation for simulation data.
	 * @param InElectrodeIndexA The index of the first electrode.
	 * @param InElectrodeIndexB The index of the second electrode.
	 * @param InElectrodeIndexC The index of the third electrode.
	 * @param InWeightA The weight for the first electrode.
	 * @param InWeightB The weight for the second electrode.
	 * @param InWeightC The weight for the third electrode.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_SIMULATION_DATA")
	void ProcessInterpolation(const int32& InElectrodeIndexA, const int32& InElectrodeIndexB, const int32& InElectrodeIndexC, const double& InWeightA, const double& InWeightB, const double& InWeightC);

	/**
	 * @brief Calculates the percentile value for the input data.
	 * @param InData The input data array.
	 * @param InPercentile The percentile to calculate.
	 * @return The calculated percentile value.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_SIMULATION_DATA")
	double CalculatePercentile(const TArray<double>& InData, const double& InPercentile);

	/**
	 * @brief Calculates the percentile value for the interpolated magnitude data per tag array.
	 * @param InPercentile The percentile to calculate.
	 * @return The calculated percentile value.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_SIMULATION_DATA")
	double CalculatePercentileForInterpolatedMagnitudeDataPerTagArray(const double& InPercentile);

	/**
	 * @brief Retrieves simulation data from a JSON response body.
	 * @param InHttpComponent The HTTP component containing the response.
	 * @param InDataTagArray The array of data tags.
	 * @param InNumberOfElectrodes The number of electrodes.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_SIMULATION_DATA")
	void GetSimulationDataFromJSONResponseBody(const UPT_HTTPComponent* InHttpComponent, const TArray<FString>& InDataTagArray, const int32& InNumberOfElectrodes);

	/**
	 * @brief Creates a JSON string for interpolated data.
	 * @param InPatientId The patient ID.
	 * @param InConfigId The configuration ID.
	 * @param InRoiId The ROI ID.
	 * @param InInterpolationId The interpolation ID.
	 * @param InElectrodePosition The position of the electrode.
	 * @param InGridSpacing The grid spacing.
	 * @param OutJsonString The output JSON string.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_SIMULATION_DATA")
	void CreateInterpolatedDataJson(const FString& InPatientId, const FString& InConfigId, const FString& InRoiId, const FString& InInterpolationId, const FVector& InElectrodePosition, const double& InGridSpacing, FString& OutJsonString);

	/**
	 * @brief Resets the simulation data arrays.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_SIMULATION_DATA")
	void ResetSimulationDataArrays();

	/**
	 * @brief Sets the data color array for a specific tag.
	 * @param InDataTagIndex The index of the data tag.
	 * @param InDataColorArray The data color array.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_SIMULATION_DATA")
	void SetDataColorArrayPerTag(const int32& InDataTagIndex, const TArray<FLinearColor>& InDataColorArray) { this->DataColorArrayPerTag[InDataTagIndex] = InDataColorArray; };

	/**
	 * @brief Calculates the mean angle between normal and vector field.
	 * @param InNormalArray The array of normal vectors.
	 * @param InVectorFieldArray The array of vector field vectors.
	 * @param OutMeanAngle The output mean angle.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_SIMULATION_DATA")
	void CalculateMeanAngleBetweenNormalAndVectorField(const TArray<FVector>& InNormalArray, const TArray<FVector>& InVectorFieldArray, double& OutMeanAngle);

	/**
	 * @brief Gets the tag length array.
	 * @return TArray<int32> The tag length array.
	 */
	UFUNCTION(BlueprintPure, Category = "PT_SIMULATION_DATA")
	TArray<int32> GetTagLengthArray() { return this->TagLengthArray; };

	/**
	 * @brief Gets the average magnitude per tag.
	 * @param InTagIndex The index of the tag.
	 * @param OutIsValid Output flag indicating if the value is valid.
	 * @return The average magnitude per tag.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_SIMULATION_DATA")
	double GetAverageMagnitudePerTag(const int32& InTagIndex, bool& OutIsValid);

	/**
	 * @brief Gets the average vector field per tag.
	 * @param InTagIndex The index of the tag.
	 * @param OutIsValid Output flag indicating if the value is valid.
	 * @return The average vector field per tag.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_SIMULATION_DATA")
	FVector GetAverageVectorFieldPerTag(const int32& InTagIndex, bool& OutIsValid);

	/**
	 * @brief Gets the average magnitude.
	 * @return The average magnitude.
	 */
	UFUNCTION(BlueprintPure, Category = "PT_SIMULATION_DATA")
	double GetAverageMagnitude() { return this->MeanMagnitude; };

	/**
	 * @brief Gets the average vector field.
	 * @return The average vector field.
	 */
	UFUNCTION(BlueprintPure, Category = "PT_SIMULATION_DATA")
	FVector GetAverageVectorField() { return this->MeanVectorField; };

	/**
	 * @brief Gets the interpolated magnitude data per tag.
	 * @param InTagIndex The index of the tag.
	 * @return TArray<double> The interpolated magnitude data per tag.
	 */
	UFUNCTION(BlueprintPure, Category = "PT_SIMULATION_DATA")
	TArray<double> GetInterpolatedMagnitudeDataPerTag(const int32& InTagIndex) { return this->InterpolatedMagnitudeDataPerTagArray[InTagIndex]; };

	/**
	 * @brief Gets the interpolated vector field data per tag.
	 * @param InTagIndex The index of the tag.
	 * @return TArray<FVector> The interpolated vector field data per tag.
	 */
	UFUNCTION(BlueprintPure, Category = "PT_SIMULATION_DATA")
	TArray<FVector> GetInterpolatedVectorfieldDataPerTag(const int32& InTagIndex) { return this->InterpolatedVectorfieldDataPerTagArray[InTagIndex]; };

	/**
	 * @brief Gets the data color array per tag.
	 * @param InTagIndex The index of the tag.
	 * @return TArray<FLinearColor> The data color array per tag.
	 */
	UFUNCTION(BlueprintPure, Category = "PT_SIMULATION_DATA")
	TArray<FLinearColor> GetDataColorArrayPerTag(const int32& InTagIndex) { return this->DataColorArrayPerTag[InTagIndex]; };

	/**
	 * @brief Gets the vertices in ROI array.
	 * @return TArray<int32> The vertices in ROI array.
	 */
	UFUNCTION(BlueprintPure, Category = "PT_SIMULATION_DATA")
	TArray<int32> GetVerticesInRoiArray() { return this->VerticesInRoiArray; };

	/**
	 * @brief Gets the vector field in ROI.
	 * @return TArray<FVector> The vector field in ROI.
	 */
	UFUNCTION(BlueprintPure, Category = "PT_SIMULATION_DATA")
	TArray<FVector> GetVectorfieldInRoi() { return this->VectorfieldInRoi; };

public:
	/** @brief Array of electrode indices. */
	UPROPERTY(BlueprintReadOnly, Category = "PT_SIMULATION_DATA")
	TArray<int32> ElectrodeIndexArray;

private:
	/**
	 * @brief Retrieves simulation data per electrode per tag.
	 * @param InElectrodeIndex The index of the electrode.
	 * @param InTagIndex The index of the tag.
	 * @param OutSimulationMagnitudeDataArray The output array for simulation magnitude data.
	 * @param OutSimulationVectorfieldDataArray The output array for simulation vector field data.
	 */
	void GetSimulationDataPerElectrodePerTag(const int32& InElectrodeIndex, const int32& InTagIndex, TArray<double>& OutSimulationMagnitudeDataArray, TArray<FVector>& OutSimulationVectorfieldDataArray);

	/**
	 * @brief Retrieves interpolated simulation data per tag.
	 * @param InTagIndex The index of the tag.
	 * @param OutInterpolatedSimulationMagnitudeDataArray The output array for interpolated magnitude data.
	 * @param OutInterpolatedSimulationVectorfieldDataArray The output array for interpolated vector field data.
	 */
	void GetInterpolatedSimulationDataPerTag(const int32& InTagIndex, TArray<double>& OutInterpolatedSimulationMagnitudeDataArray, TArray<FVector>& OutInterpolatedSimulationVectorfieldDataArray);

	/**
	 * @brief Retrieves simulation data from a JSON object.
	 * @param InJsonObjectPtr The JSON object pointer.
	 * @param InDataTagArray The array of data tags.
	 * @param InNumberOfElectrodes The number of electrodes.
	 */
	void GetSimulationDataFromJSONObject(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const TArray<FString>& InDataTagArray, const int32& InNumberOfElectrodes);

	/**
	 * @brief Processes electrode data.
	 * @param InJsonObjectPtr The JSON object pointer.
	 * @param InDataTagArray The array of data tags.
	 * @param InCurrentElectrodeIndex The current electrode index.
	 */
	void ProcessElectrodeData(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const TArray<FString>& InDataTagArray, const int32& InCurrentElectrodeIndex);

	/** @brief Array of simulation magnitude data per electrode per tag. */
	TArray<TArray<TArray<double>>> SimulationMagnitudeDataPerElectrodePerTagArray;

	/** @brief Array of simulation vector field data per electrode per tag. */
	TArray<TArray<TArray<FVector>>> SimulationVectorfieldDataPerElectrodePerTagArray;

	/** @brief Array of interpolated magnitude data per tag. */
	TArray<TArray<double>> InterpolatedMagnitudeDataPerTagArray;

	/** @brief Array of interpolated vector field data per tag. */
	TArray<TArray<FVector>> InterpolatedVectorfieldDataPerTagArray;

	/** @brief Array of ROI index mappings per tag. */
	TArray<TArray<int32>> RoiIndexMappingPerTagArray;

	/** @brief Array of tag lengths. */
	TArray<int32> TagLengthArray;

	/** @brief Array of per-vertex data. */
	TArray<double> PerVertexDataArray;

	/** @brief Array of raw tetra data. */
	TArray<TArray<FPT_TetraData>> RawTetraDataArray;

	/** @brief Array of mean magnitudes per tag. */
	TArray<double> MeanMagnitudePerTag;

	/** @brief Array of mean vector fields per tag. */
	TArray<FVector> MeanVectorFieldPerTag;

	/** @brief Mean magnitude. */
	double MeanMagnitude;

	/** @brief Mean vector field. */
	FVector MeanVectorField;

	/** @brief Map of vertex tag cell mappings. */
	TMap<int32, TArray<TArray<int32>>> VertexTagCellMapping;

	/** @brief Array of vertices in ROI. */
	TArray<int32> VerticesInRoiArray;

	/** @brief Array of data color arrays per tag. */
	TArray<TArray<FLinearColor>> DataColorArrayPerTag;

	/** @brief Array of vector fields in ROI. */
	TArray<FVector> VectorfieldInRoi;
};
