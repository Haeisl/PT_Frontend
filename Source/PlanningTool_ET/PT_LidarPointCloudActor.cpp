// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved


#include "PT_LidarPointCloudActor.h"
#include "LidarPointCloudComponent.h"
#include "LidarPointCloudShared.h"

void APT_LidarPointCloudActor::UpdateLidarPointCloudColor(const TArray<FLidarPointCloudPoint>& InPointCloud, const TArray<FLinearColor>& InColorArray, const TArray<int32>& InVertexIndexArray, TArray<FLidarPointCloudPoint>& OutPointCloud)
{
	OutPointCloud.SetNumZeroed(InVertexIndexArray.Num());
	for(int32 Index = 0; Index < InVertexIndexArray.Num(); Index++)
	{
		FLinearColor NewColor = InColorArray[InVertexIndexArray[Index]];
		OutPointCloud[Index] = FLidarPointCloudPoint(InPointCloud[Index].Location, NewColor.R, NewColor.G, NewColor.B);
	}
}
