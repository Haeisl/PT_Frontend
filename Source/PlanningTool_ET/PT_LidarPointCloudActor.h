// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved
// Modifications (C) 2025 David Hasse - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "LidarPointCloudActor.h"
#include <LidarPointCloudShared.h>
#include "PT_LidarPointCloudActor.generated.h"

/**
 * @class APT_LidarPointCloudActor
 * @brief A class that extends ALidarPointCloudActor to handle LIDAR point cloud operations.
 *
 * This class provides functionality to update the color of a LIDAR point cloud.
 */
UCLASS()
class PLANNINGTOOL_ET_API APT_LidarPointCloudActor : public ALidarPointCloudActor
{
	GENERATED_BODY()

public:
	/**
	 * @brief Updates the color of the LIDAR point cloud.
	 *
	 * This function takes an input point cloud, an array of colors, and an array of vertex indices.
	 * It updates the color of the points in the input point cloud based on the provided colors and vertex indices,
	 * and stores the updated point cloud in the output point cloud array.
	 *
	 * @param InPointCloud The input point cloud to be updated.
	 * @param InColorArray An array of colors to be applied to the points.
	 * @param InVertexIndexArray An array of vertex indices corresponding to the points to be colored.
	 * @param OutPointCloud The output point cloud with updated colors.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_LIDAR_POINT_CLOUD")
	void UpdateLidarPointCloudColor(const TArray<FLidarPointCloudPoint>& InPointCloud, const TArray<FLinearColor>& InColorArray, const TArray<int32>& InVertexIndexArray, TArray<FLidarPointCloudPoint>& OutPointCloud);
};
