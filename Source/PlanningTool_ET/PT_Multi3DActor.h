// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved
// Modifications (C) 2025 David Hasse - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PT_Single3DActor.h"
#include "PT_SimulationComponent.h"
#include "PT_Multi3DActor.generated.h"

/**
 * @class APT_Multi3DActor
 * @brief A class that extends APT_Single3DActor to handle multiple 3D meshes and volumes.
 *
 * This class provides functionality to convert JSON response bodies and objects into multiple 3D meshes and volumes.
 * It also provides methods to extract mesh and volume data from JSON response bodies.
 */
UCLASS()
class PLANNINGTOOL_ET_API APT_Multi3DActor : public APT_Single3DActor
{
	GENERATED_BODY()

public:
	/**
	 * @brief Sets default values for this actor's properties.
	 */
	APT_Multi3DActor();

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
	 * @brief Converts a JSON response body to multiple meshes.
	 *
	 * This function is a BlueprintCallable function that belongs to the "PT_3D_DATA" category.
	 * It takes a HTTP component, a field name, an array of tags, and an output array of mesh data as input.
	 * It gets the response object from the HTTP component and calls the ConvertJSONObjectToMultiMesh function with the response object and the other parameters.
	 *
	 * @param InHTTPComponent The HTTP component from which to get the response object.
	 * @param InFieldName The name of the field to get from the JSON object.
	 * @param InTagArray An array of tags.
	 * @param InDescriptionArray An array of descriptions.
	 * @param OutMeshArray An array of mesh data to which the function will add new meshes.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_3D_DATA")
	void ConvertJSONResponseBodyToMultiMesh(const UPT_HTTPComponent* InHTTPComponent, const FString& InFieldName, const TArray<FString>& InTagArray, const TArray<FString>& InDescriptionArray, TArray<FPT_MeshData>& OutMeshArray);

	/**
	 * @brief Converts a JSON object to multiple meshes.
	 *
	 * This function takes a JSON object, a field name, an array of tags, and an output array of mesh data as input.
	 * It tries to get an object field from the JSON object with the given field name.
	 * If the field is found, it iterates over the tag array and for each tag, it creates a new mesh data object.
	 * It sets the ID of the mesh data object to the current tag.
	 * It converts the JSON object to a triangle index array and assigns it to the mesh data object.
	 * It then adds the mesh data object to the mesh array.
	 * If the field is not found, it logs an error message.
	 *
	 * @param InJsonObjectPtr A pointer to the JSON object to convert.
	 * @param InFieldName The name of the field to get from the JSON object.
	 * @param InTagArray An array of tags.
	 * @param InDescriptionArray An array of descriptions.
	 * @param OutMeshArray An array of mesh data to which the function will add new meshes.
	 */
	void ConvertJSONObjectToMultiMesh(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InFieldName, const TArray<FString>& InTagArray, const TArray<FString>& InDescriptionArray, TArray<FPT_MeshData>& OutMeshArray);

	/**
	 * @brief Converts a JSON response body to multiple volumes.
	 *
	 * This function is a BlueprintCallable function that belongs to the "PT_3D_DATA" category.
	 * It takes a HTTP component, a field name, an array of tags, an array of vertices, an array of vertex colors, and an output array of volume data as input.
	 * It gets the response object from the HTTP component and calls the ConvertJSONObjectToMultiVolume function with the response object and the other parameters.
	 *
	 * @param InHTTPComponent The HTTP component from which to get the response object.
	 * @param InFieldName The name of the field to get from the JSON object.
	 * @param InTagArray An array of tags.
	 * @param InVertexArray An array of vertices.
	 * @param InVertexColorArray An array of vertex colors.
	 * @param OutVolumeArray An array of volume data to which the function will add new volumes.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_3D_DATA")
	void ConvertJSONResponseBodyToMultiVolume(const UPT_HTTPComponent* InHTTPComponent, const FString& InFieldName, const TArray<FString>& InTagArray, const TArray<FVector>& InVertexArray, const TArray<FLinearColor>& InVertexColorArray, TArray<FPT_VolumeData>& OutVolumeArray);

	/**
	 * @brief Converts a JSON object to multiple volumes.
	 *
	 * This function takes a JSON object, a field name, an array of tags, an array of vertices, an array of vertex colors, and an output array of volume data as input.
	 * It tries to get an object field from the JSON object with the given field name.
	 * If the field is found, it iterates over the tag array and for each tag, it creates a new volume data object.
	 * It sets the ID of the volume data object to the current tag.
	 * It converts the JSON object to an integer array and creates a point cloud array from the integer array, the vertex array, and the vertex color array.
	 * It then adds the volume data object to the volume array.
	 * If the field is not found, it logs an error message.
	 *
	 * @param InJsonObjectPtr A pointer to the JSON object to convert.
	 * @param InFieldName The name of the field to get from the JSON object.
	 * @param InTagArray An array of tags.
	 * @param InVertexArray An array of vertices.
	 * @param InVertexColorArray An array of vertex colors.
	 * @param OutVolumeArray An array of volume data to which the function will add new volumes.
	 */
	void ConvertJSONObjectToMultiVolume(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InFieldName, const TArray<FString>& InTagArray, const TArray<FVector>& InVertexArray, const TArray<FLinearColor>& InVertexColorArray, TArray<FPT_VolumeData>& OutVolumeArray);

	/**
	 * @brief Converts a JSON response body to tetrahedral data.
	 *
	 * This function is a BlueprintCallable function that belongs to the "PT_3D_DATA" category.
	 * It takes a HTTP component, a field name, an array of tags, and an output array of tetrahedral data as input.
	 * It gets the response object from the HTTP component and calls the ConvertJSONObjectToTetraData function with the response object and the other parameters.
	 *
	 * @param InHTTPComponent The HTTP component from which to get the response object.
	 * @param InFieldName The name of the field to get from the JSON object.
	 * @param InTagArray An array of tags.
	 * @param OutTetraDataArray An array of tetrahedral data to which the function will add new data.
	 */
	 //UFUNCTION(BlueprintCallable, Category = "PT_3D_DATA")
	void ConvertJSONResponseBodyToTetraArray(const UPT_HTTPComponent* InHTTPComponent, const FString& InFieldName, const TArray<FString>& InTagArray, TArray<TArray<FPT_TetraData>>& OutTetraDataArray);

	/**
	 * @brief Converts a JSON object to tetrahedral data.
	 *
	 * This function takes a JSON object, a field name, an array of tags, and an output array of tetrahedral data as input.
	 * It tries to get an object field from the JSON object with the given field name.
	 * If the field is found, it iterates over the tag array and for each tag, it converts the JSON object to a tetrahedral array and adds it to the output array.
	 * If the field is not found, it logs an error message.
	 *
	 * @param InJsonObjectPtr A pointer to the JSON object to convert.
	 * @param InFieldName The name of the field to get from the JSON object.
	 * @param InTagArray An array of tags.
	 * @param OutTetraDataArray An array of tetrahedral data to which the function will add new data.
	 */
	void ConvertJSONObjectToTetraArray(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InFieldName, const TArray<FString>& InTagArray, TArray<TArray<FPT_TetraData>>& OutTetraDataArray);

	/**
	 * @brief Calculates normals for multiple meshes.
	 *
	 * This function takes an output array of normals and calculates the normals for multiple meshes.
	 *
	 * @param OutNormalArray An array of normals to which the function will add new normals.
	 */
	void CalculateNormalsForMultiMesh(TArray<FVector>& OutNormalArray);

	/**
	 * @brief Extracts both mesh and volume data from a JSON response body.
	 *
	 * This function takes a HTTP component and several output parameters. It uses the HTTP component to get the JSON response body,
	 * and then extracts the vertex array, mesh tags, volume tags, mesh descriptions, volume descriptions, mesh data, and volume data from the JSON.
	 * The extracted data is stored in the output parameters.
	 *
	 * @param InHTTPComponent The HTTP component that contains the JSON response body.
	 * @param OutVertexArray The output parameter where the vertex array will be stored.
	 * @param OutNormalArray The output parameter where the normal array will be stored.
	 * @param OutMeshTagArray The output parameter where the mesh tags will be stored.
	 * @param OutVolumeTagArray The output parameter where the volume tags will be stored.
	 * @param OutMeshDescriptionArray The output parameter where the mesh descriptions will be stored.
	 * @param OutVolumeDescriptionArray The output parameter where the volume descriptions will be stored.
	 * @param OutMeshDataArray The output parameter where the mesh data will be stored.
	 * @param OutVolumeDataArray The output parameter where the volume data will be stored.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_3D_DATA")
	void GetMultiMeshAndMultiVolumeFromJSONResponseBody(const UPT_HTTPComponent* InHTTPComponent, TArray<FVector>& OutVertexArray, TArray<FVector>& OutNormalArray, TArray<FString>& OutMeshTagArray, TArray<FString>& OutVolumeTagArray, TArray<FString>& OutMeshDescriptionArray, TArray<FString>& OutVolumeDescriptionArray, TArray<FPT_MeshData>& OutMeshDataArray, TArray<FPT_VolumeData>& OutVolumeDataArray);

	/**
	 * @brief Extracts mesh data from a JSON response body.
	 *
	 * This function takes a HTTP component and several output parameters. It uses the HTTP component to get the JSON response body,
	 * and then extracts the vertex array, mesh tags, mesh descriptions, and mesh data from the JSON.
	 * The extracted data is stored in the output parameters.
	 *
	 * @param InHTTPComponent The HTTP component that contains the JSON response body.
	 * @param OutVertexArray The output parameter where the vertex array will be stored.
	 * @param OutNormalArray The output parameter where the normal array will be stored.
	 * @param OutMeshTagArray The output parameter where the mesh tags will be stored.
	 * @param OutMeshDescriptionArray The output parameter where the mesh descriptions will be stored.
	 * @param OutMeshDataArray The output parameter where the mesh data will be stored.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_3D_DATA")
	void GetMultiMeshFromJSONResponseBody(const UPT_HTTPComponent* InHTTPComponent, TArray<FVector>& OutVertexArray, TArray<FVector>& OutNormalArray, TArray<FString>& OutMeshTagArray, TArray<FString>& OutMeshDescriptionArray, TArray<FPT_MeshData>& OutMeshDataArray);

	/**
	 * @brief Extracts volume data from a JSON response body.
	 *
	 * This function takes a HTTP component and several output parameters. It uses the HTTP component to get the JSON response body,
	 * and then extracts the vertex array, volume tags, volume descriptions, and volume data from the JSON.
	 * The extracted data is stored in the output parameters.
	 *
	 * @param InHTTPComponent The HTTP component that contains the JSON response body.
	 * @param OutVertexArray The output parameter where the vertex array will be stored.
	 * @param OutVolumeTagArray The output parameter where the volume tags will be stored.
	 * @param OutVolumeDescriptionArray The output parameter where the volume descriptions will be stored.
	 * @param OutVolumeDataArray The output parameter where the volume data will be stored.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_3D_DATA")
	void GetMultiVolumeFromJSONResponseBody(const UPT_HTTPComponent* InHTTPComponent, TArray<FVector>& OutVertexArray, TArray<FString>& OutVolumeTagArray, TArray<FString>& OutVolumeDescriptionArray, TArray<FPT_VolumeData>& OutVolumeDataArray);

	/**
	 * @brief Resets the arrays used by the multi 3D actor.
	 *
	 * This function is a BlueprintCallable function that belongs to the "PT_3D_DATA" category.
	 * It resets the arrays used by the multi 3D actor.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_3D_DATA")
	void ResetMulti3DActorArrays();

public:

private:
	/**
	 * @brief A two-dimensional dynamic array storing tetrahedral data.
	 *
	 * This private member variable named `TetraDataArray` is a two-dimensional dynamic array where each element is another TArray that holds objects of type `FPT_TetraData`.
	 * `FPT_TetraData` is a custom data type presumably representing some kind of tetrahedral data.
	 *
	 * As a private member, `TetraDataArray` can only be accessed directly from within methods of the `APT_Multi3DActor` class. Other classes must interact with `TetraDataArray` through public or protected methods provided by the `APT_Multi3DActor` class.
	 */
	TArray<TArray<FPT_TetraData>> TetraDataPerTagArray;

	/**
	 * @brief An array storing mesh data.
	 *
	 * This private member variable named `MeshDataPerTagArray` is a dynamic array that holds objects of type `FPT_MeshData`.
	 * `FPT_MeshData` is a custom data type presumably representing some kind of mesh data.
	 *
	 * As a private member, `MeshDataPerTagArray` can only be accessed directly from within methods of the `APT_Multi3DActor` class. Other classes must interact with `MeshDataPerTagArray` through public or protected methods provided by the `APT_Multi3DActor` class.
	 */
	TArray<FPT_MeshData> MeshDataPerTagArray;
};
