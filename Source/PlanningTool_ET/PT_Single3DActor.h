// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved
// Modifications (C) 2025 David Hasse - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PT_StructContainer.h"
#include <LidarPointCloudShared.h>
#include "PT_Single3DActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMeshDataCallbackEventDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVolumeDataCallbackEventDelegate);

/**
 * @brief A class representing a single 3D actor in the Planning Tool.
 *
 * This class inherits from AActor and provides functionality for handling 3D mesh and volume data.
 * It includes methods for getting vertex, color, triangle index, and normal arrays, as well as methods for converting JSON responses to mesh and volume data.
 * The class also provides delegates for mesh and volume data loaded events, which can be assigned in Blueprint.
 */
UCLASS()
class PLANNINGTOOL_ET_API APT_Single3DActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APT_Single3DActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * @brief A delegate for the mesh data loaded callback event.
	 *
	 * This property is a delegate that can be assigned in Blueprint.
	 * It belongs to the "PT_3D_Event" category.
	 * The delegate is called when the mesh data has been loaded.
	 * It allows other parts of the code or other Blueprints to react to the event of the mesh data being loaded.
	 *
	 * @property MeshDataLoadedCallbackEvent The delegate for the mesh data loaded callback event.
	 */
	UPROPERTY(BlueprintAssignable, Category = "PT_3D_Event")
	FMeshDataCallbackEventDelegate MeshDataLoadedCallbackEvent;

	/**
	 * @brief A delegate for the volume data loaded callback event.
	 *
	 * This property is a delegate that can be assigned in Blueprint.
	 * It belongs to the "PT_3D_Event" category.
	 * The delegate is called when the volume data has been loaded.
	 * It allows other parts of the code or other Blueprints to react to the event of the volume data being loaded.
	 *
	 * @property VolumeDataLoadedCallbackEvent The delegate for the volume data loaded callback event.
	 */
	UPROPERTY(BlueprintAssignable, Category = "PT_3D_Event")
	FVolumeDataCallbackEventDelegate VolumeDataLoadedCallbackEvent;

	/**
	 * @brief Gets the vertex array.
	 *
	 * This function is a BlueprintCallable function that belongs to the "PT_3D_DATA" category.
	 * It returns the vertex array of the actor.
	 * The vertex array is a member variable of the actor and contains the vertices of the 3D model represented by the actor.
	 *
	 * @return The vertex array of the actor.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_3D_DATA")
	TArray<FVector> GetVertexArray() const;

	/**
	 * @brief Gets the vertex color array.
	 *
	 * This function is a BlueprintCallable function that belongs to the "PT_3D_DATA" category.
	 * It returns the vertex color array of the actor.
	 * The vertex color array is a member variable of the actor and contains the colors of the vertices of the 3D model represented by the actor.
	 *
	 * @return The vertex color array of the actor.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_3D_DATA")
	TArray<FLinearColor> GetVertexColorArray() const;

	/**
	 * @brief Gets the triangle index array.
	 *
	 * This function is a BlueprintCallable function that belongs to the "PT_3D_DATA" category.
	 * It returns the triangle index array of the actor.
	 * The triangle index array is a member variable of the actor and contains the indices of the vertices that form the triangles of the 3D model represented by the actor.
	 *
	 * @return The triangle index array of the actor.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_3D_DATA")
	TArray<int32> GetTriangleIndexArray() const;

	/**
	 * @brief Gets the normal array.
	 *
	 * This function is a BlueprintCallable function that belongs to the "PT_3D_DATA" category.
	 * It returns the normal array of the actor.
	 * The normal array is a member variable of the actor and contains the normal vectors of the vertices of the 3D model represented by the actor.
	 *
	 * @return The normal array of the actor.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_3D_DATA")
	TArray<FVector> GetNormalArray() const;

	/**
	 * @brief Creates an array of FLidarPointCloudPoint from given vertex indices, vertex array, and vertex color array.
	 *
	 * This function is a BlueprintCallable function that belongs to the "PT_3D_DATA" category.
	 * It takes an array of vertex indices, an array of vertices, and an array of vertex colors as input.
	 * It iterates over the vertex indices array and for each index, it creates a new FLidarPointCloudPoint.
	 * The X, Y, and Z coordinates of the FLidarPointCloudPoint are set to the X, Y, and Z coordinates of the vertex at the current index in the vertex array.
	 * The R, G, and B color values of the FLidarPointCloudPoint are set to the R, G, and B color values of the vertex color at the current index in the vertex color array.
	 * The FLidarPointCloudPoint is then added to the OutPointCloudArray.
	 * Before the function starts adding new points, it empties the OutPointCloudArray.
	 *
	 * @param InVertexIndexArray An array of indices to the vertices.
	 * @param InVertexArray An array of vertices.
	 * @param InVertexColorArray An array of vertex colors.
	 * @param OutPointCloudArray An array of FLidarPointCloudPoint to which the function will add new points.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_3D_DATA")
	void CreatePointCloudArray(const TArray<int32>& InVertexIndexArray, const TArray<FVector>& InVertexArray, const TArray<FLinearColor>& InVertexColorArray, TArray<FLidarPointCloudPoint>& OutPointCloudArray);

	/**
	 * @brief Updates the color of a Lidar point cloud.
	 *
	 * This function is a BlueprintCallable function that belongs to the "PT_3D_DATA" category.
	 * It takes an array of Lidar points, an array of colors, and an array of vertex indices as input.
	 * It updates the color of each Lidar point based on the corresponding color in the color array.
	 *
	 * @param InPointCloud An array of Lidar points.
	 * @param InColorArray An array of colors.
	 * @param InVertexIndexArray An array of vertex indices.
	 * @param OutPointCloud An array of Lidar points with updated colors.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_3D_DATA")
	void UpdateLidarPointCloudColor(const TArray<FLidarPointCloudPoint>& InPointCloud, const TArray<FLinearColor>& InColorArray, const TArray<int32>& InVertexIndexArray, TArray<FLidarPointCloudPoint>& OutPointCloud);

	/**
	 * @brief Converts a JSON response body to a mesh.
	 *
	 * This function is a BlueprintCallable function that belongs to the "PT_3D_DATA" category.
	 * It takes a HTTP component and output arrays for vertex and triangle index data as input.
	 * It gets the vertex coordinates and triangle indices from the response body of the HTTP component and assigns them to the output arrays and the corresponding member variables.
	 * It also initializes the vertex color array with white color for each vertex.
	 *
	 * @param InHTTPComponent The HTTP component from which to get the response body.
	 * @param OutVertexArray The output array for the vertex data.
	 * @param OutTriangleIndexArray The output array for the triangle index data.
	 * @param OutNormalArray The output array for the normal data.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_3D_DATA")
	void ConvertJSONResponseBodyToMesh(const UPT_HTTPComponent* InHTTPComponent, TArray<FVector>& OutVertexArray, TArray<int32>& OutTriangleIndexArray, TArray<FVector>& OutNormalArray);

	/**
	 * @brief Converts a JSON response body to a volume.
	 *
	 * This function is a BlueprintCallable function that belongs to the "PT_3D_DATA" category.
	 * It takes a HTTP component and an output array for point cloud data as input.
	 * It gets the vertex coordinates from the response body of the HTTP component, initializes the vertex color array with white color for each vertex, and creates a point cloud array from the vertex and color arrays and the volume data in the response body.
	 * It assigns the point cloud array to the output array.
	 *
	 * @param InHTTPComponent The HTTP component from which to get the response body.
	 * @param OutPointCloudArray The output array for the point cloud data.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_3D_DATA")
	void ConvertJSONResponseBodyToVolume(const UPT_HTTPComponent* InHTTPComponent, TArray<FLidarPointCloudPoint>& OutPointCloudArray);

	/**
	 * @brief Sets the vertex array from a JSON response body.
	 *
	 * This function is a BlueprintCallable function that belongs to the "PT_3D_DATA" category.
	 * It takes a HTTP component and a field name as input and an output array for the vertex data.
	 * It gets the vertex data from the response body of the HTTP component and assigns it to the output array and the corresponding member variable.
	 *
	 * @param InHTTPComponent The HTTP component from which to get the response body.
	 * @param InFieldName The name of the field to get from the JSON object.
	 * @param OutVertexArray The output array for the vertex data.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_3D_DATA")
	void SetVertexArrayFromJSONResponseBody(const UPT_HTTPComponent* InHTTPComponent, const FString& InFieldName, TArray<FVector>& OutVertexArray);

	/**
	 * @brief Sets the vertex color array from a JSON response body.
	 *
	 * This function is a BlueprintCallable function that belongs to the "PT_3D_DATA" category.
	 * It takes a HTTP component and a field name as input and an output array for the vertex color data.
	 * It gets the vertex color data from the response body of the HTTP component and assigns it to the output array and the corresponding member variable.
	 *
	 * @param InHTTPComponent The HTTP component from which to get the response body.
	 * @param InFieldName The name of the field to get from the JSON object.
	 * @param InVertexColorArray The output array for the vertex color data.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_3D_DATA")
	void SetVertexColorArrayFromJSONResponseBody(const UPT_HTTPComponent* InHTTPComponent, const FString& InFieldName, TArray<FLinearColor>& InVertexColorArray);

	/**
	 * @brief Calculates the normals of the vertices of a 3D model.
	 *
	 * This function is a BlueprintCallable function that belongs to the "PT_3D_DATA" category.
	 * It takes an array of vertices, an array of triangle indices, and an output array for the normal vectors as input.
	 * It calculates the normals of the vertices based on the triangle indices and assigns them to the output array.
	 *
	 * @param InVertexArray The array of vertices.
	 * @param InTriangleIndexArray The array of triangle indices.
	 * @param OutNormalArray The output array for the normal vectors.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_3D_DATA")
	void CalculateNormals(const TArray<FVector>& InVertexArray, const TArray<int32> InTriangleIndexArray, TArray<FVector>& OutNormalArray);

	/**
	 * @brief Calculates the inverted normals of the vertices of a 3D model.
	 *
	 * This function is a BlueprintCallable function that belongs to the "PT_3D_DATA" category.
	 * It takes an array of vertices, an array of triangle indices, and an output array for the inverted normal vectors as input.
	 * It calculates the inverted normals of the vertices based on the triangle indices and assigns them to the output array.
	 *
	 * @param InVertexArray The array of vertices.
	 * @param InTriangleIndexArray The array of triangle indices.
	 * @param OutInvertedNormalArray The output array for the inverted normal vectors.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_3D_DATA")
	void CalculateInvertedNormals(const TArray<FVector>& InVertexArray, const TArray<int32> InTriangleIndexArray, TArray<FVector>& OutInvertedNormalArray);

	/**
	 * @brief Resets the arrays of the single 3D actor.
	 *
	 * This function is a BlueprintCallable function that belongs to the "PT_3D_DATA" category.
	 * It resets the vertex array, vertex color array, normal array, and triangle index array of the actor.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_3D_DATA")
	void ResetSingle3DActorArrays();

	/**
	 * @brief Gets the length of the vertex array.
	 *
	 * This function is a BlueprintPure function that belongs to the "PT_3D_DATA" category.
	 * It returns the number of vertices in the vertex array.
	 *
	 * @return The length of the vertex array.
	 */
	UFUNCTION(BlueprintPure, Category = "PT_3D_DATA")
	int32 GetVertexArrayLength() { return this->VertexArray.Num(); }

protected:
	/**
	 * @brief An array of vertices.
	 *
	 * This member variable is an array of FVector objects.
	 * Each FVector object represents a vertex in a 3D space.
	 * The array is used to store the vertices of the 3D model represented by the actor.
	 *
	 * @var VertexArray The array of vertices.
	 */
	TArray<FVector> VertexArray;

	/**
	 * @brief An array of vertex colors.
	 *
	 * This member variable is an array of FLinearColor objects.
	 * Each FLinearColor object represents a color in a linear color space.
	 * The array is used to store the colors of the vertices of the 3D model represented by the actor.
	 *
	 * @var VertexColorArray The array of vertex colors.
	 */
	TArray<FLinearColor> VertexColorArray;

	/**
	 * @brief An array of normals.
	 *
	 * This member variable is an array of FVector objects.
	 * Each FVector object represents a normal vector in a 3D space.
	 * The array is used to store the normals of the vertices of the 3D model represented by the actor.
	 *
	 * @var NormalArray The array of normals.
	 */
	TArray<FVector> NormalArray;

	/**
	 * @brief An array of triangle indices.
	 *
	 * This member variable is an array of int32 values.
	 * Each int32 value represents an index to a vertex in the VertexArray.
	 * The array is used to store the triangle indices of the 3D model represented by the actor.
	 *
	 * @var TriangleIndexArray The array of triangle indices.
	 */
	TArray<int32> TriangleIndexArray;

	/**
	 * @brief Initializes the vertex color array with white color.
	 *
	 * This function initializes the vertex color array with white color for each vertex.
	 * It takes the length of the vertex array and an optional alpha value as input.
	 *
	 * @param InVertexArrayLength The length of the vertex array.
	 * @param InAlphaValue The alpha value for the color (default is 1.0).
	 */
	void InitWhiteVertexColor(const int32& InVertexArrayLength, const float& InAlphaValue = 1.f);
};
