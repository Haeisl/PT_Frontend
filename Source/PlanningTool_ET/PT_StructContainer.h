// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved
// Modifications (C) 2025 David Hasse - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include <LidarPointCloudShared.h>
#include "PT_StructContainer.generated.h"

/**
 * @brief A structure that represents tetrahedron data.
 *
 * This structure is defined as a BlueprintType, which means it can be used in Blueprints.
 * It contains four double values (A, B, C, D) representing the vertices of a tetrahedron,
 * a string (Tag) for tagging or labeling the tetrahedron, and an index for identification.
 */
USTRUCT(BlueprintType)
struct FPT_TetraData
{
	GENERATED_USTRUCT_BODY()

	/** A double value representing the first vertex of the tetrahedron. */
	UPROPERTY(BlueprintReadWrite, Category = "PT_TetraData")
	double A;

	/** A double value representing the second vertex of the tetrahedron. */
	UPROPERTY(BlueprintReadWrite, Category = "PT_TetraData")
	double B;

	/** A double value representing the third vertex of the tetrahedron. */
	UPROPERTY(BlueprintReadWrite, Category = "PT_TetraData")
	double C;

	/** A double value representing the fourth vertex of the tetrahedron. */
	UPROPERTY(BlueprintReadWrite, Category = "PT_TetraData")
	double D;

	/** A string value used for tagging or labeling the tetrahedron. */
	UPROPERTY(BlueprintReadWrite, Category = "PT_TetraData")
	FString Tag;

	/** A double value used for identifying the tetrahedron. */
	UPROPERTY(BlueprintReadWrite, Category = "PT_TetraData")
	double Index;
};

/**
 * @brief A structure to hold mesh data.
 *
 * This structure is BlueprintType, meaning it can be used in Blueprint.
 * It contains an ID of type FString, a description of type FString, and a triangle index array of type TArray<int32>.
 * The ID is used to uniquely identify the mesh data.
 * The triangle index array is used to store the indices of the triangles that make up the mesh.
 */
USTRUCT(BlueprintType)
struct FPT_MeshData
{
	GENERATED_USTRUCT_BODY()

	/** The ID used to uniquely identify the mesh data. */
	UPROPERTY(BlueprintReadWrite, Category = "PT_MeshData")
	FString Id;

	/** The description of the mesh data. */
	UPROPERTY(BlueprintReadWrite, Category = "PT_MeshData")
	FString Description;

	/** The array of triangle indices that make up the mesh. */
	UPROPERTY(BlueprintReadWrite, Category = "PT_MeshData")
	TArray<int32> TriangleIndexArray;
};

/**
 * @brief A structure to hold volume data.
 *
 * This structure is BlueprintType, meaning it can be used in Blueprint.
 * It contains an ID of type FString, a vertex index array of type TArray<int32>, and a point cloud array of type TArray<FLidarPointCloudPoint>.
 * The ID is used to uniquely identify the volume data.
 * The vertex index array is used to store the indices of the vertices that make up the volume.
 * The point cloud array is used to store the points that make up the point cloud representation of the volume.
 */
USTRUCT(BlueprintType)
struct FPT_VolumeData
{
	GENERATED_USTRUCT_BODY()

	/** The ID used to uniquely identify the volume data. */
	UPROPERTY(BlueprintReadWrite, Category = "PT_VolumeData")
	FString Id;

	/** The array of vertex indices that make up the volume. */
	UPROPERTY(BlueprintReadWrite, Category = "PT_VolumeData")
	TArray<int32> VertexIndexArray;

	/** The array of points that make up the point cloud representation of the volume. */
	UPROPERTY(BlueprintReadWrite, Category = "PT_VolumeData")
	TArray<FLidarPointCloudPoint> PointCloudArray;
};

/**
 * @brief A container class for various structures.
 *
 * This class provides a container for the FPT_TetraData, FPT_MeshData, and FPT_VolumeData structures.
 */
class PLANNINGTOOL_ET_API PT_StructContainer
{
public:
	/**
  * @brief Default constructor.
  */
	PT_StructContainer();

	/**
  * @brief Destructor.
  */
	~PT_StructContainer();
};
