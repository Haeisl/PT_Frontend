// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved


#include "PT_Single3DActor.h"
#include "PT_JSONConverter.h"

// Sets default values
APT_Single3DActor::APT_Single3DActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APT_Single3DActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APT_Single3DActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<FVector> APT_Single3DActor::GetVertexArray() const
{
	return this->VertexArray;
}

TArray<FLinearColor> APT_Single3DActor::GetVertexColorArray() const
{
	return this->VertexColorArray;
}

TArray<int32> APT_Single3DActor::GetTriangleIndexArray() const
{
	return this->TriangleIndexArray;
}

TArray<FVector> APT_Single3DActor::GetNormalArray() const
{
	return this->NormalArray;
}

void APT_Single3DActor::CreatePointCloudArray(const TArray<int32>& InVertexIndexArray, const TArray<FVector>& InVertexArray, const TArray<FLinearColor>& InVertexColorArray, TArray<FLidarPointCloudPoint>& OutPointCloudArray)
{
	OutPointCloudArray.Empty();

	for (int32 Index : InVertexIndexArray)
	{
		OutPointCloudArray.Add(FLidarPointCloudPoint(InVertexArray[Index].X, InVertexArray[Index].Y, InVertexArray[Index].Z, InVertexColorArray[Index].R, InVertexColorArray[Index].G, InVertexColorArray[Index].B));
	}
}

void APT_Single3DActor::UpdateLidarPointCloudColor(const TArray<FLidarPointCloudPoint>& InPointCloud, const TArray<FLinearColor>& InColorArray, const TArray<int32>& InVertexIndexArray, TArray<FLidarPointCloudPoint>& OutPointCloud)
{
	OutPointCloud.SetNumZeroed(InVertexIndexArray.Num());
	for (int32 Index = 0; Index < InVertexIndexArray.Num(); Index++)
	{
		FLinearColor NewColor = InColorArray[InVertexIndexArray[Index]];
		OutPointCloud[Index] = FLidarPointCloudPoint(InPointCloud[Index].Location, NewColor.R, NewColor.G, NewColor.B); //DAS WARS?!?!?!?
	}
}

void APT_Single3DActor::ConvertJSONResponseBodyToMesh(const UPT_HTTPComponent* InHTTPComponent, TArray<FVector>& OutVertexArray, TArray<int32>& OutTriangleIndexArray, TArray<FVector>& OutNormalArray)
{
	OutVertexArray.Empty();
	OutTriangleIndexArray.Empty();

	this->VertexArray.Empty();

	UPT_JSONConverter::ConvertJSONResponseBodyToVectorArray(InHTTPComponent, "vertices", this->VertexArray);
	OutVertexArray = this->VertexArray;
	this->InitWhiteVertexColor(this->VertexArray.Num(), 0.5f);
	UPT_JSONConverter::ConvertJSONResponseBodyToTriangleIndexArray(InHTTPComponent, "triangles", this->TriangleIndexArray);
	OutTriangleIndexArray = this->TriangleIndexArray;
	
	this->CalculateInvertedNormals(this->VertexArray, this->TriangleIndexArray, OutNormalArray);

	this->MeshDataLoadedCallbackEvent.Broadcast();
}

void APT_Single3DActor::ConvertJSONResponseBodyToVolume(const UPT_HTTPComponent* InHTTPComponent, TArray<FLidarPointCloudPoint>& OutPointCloudArray)
{
	OutPointCloudArray.Empty();

	this->VertexArray.Empty();

	UPT_JSONConverter::ConvertJSONResponseBodyToVectorArray(InHTTPComponent, "vertices", this->VertexArray);
	this->InitWhiteVertexColor(this->VertexArray.Num(), 0.5f);

	TArray<int32> VertexIndexArray;
	UPT_JSONConverter::ConvertJSONResponseBodyToIntegerArray(InHTTPComponent, "volume", VertexIndexArray);

	this->CreatePointCloudArray(VertexIndexArray, this->VertexArray, this->VertexColorArray, OutPointCloudArray);

	this->VolumeDataLoadedCallbackEvent.Broadcast();
}

void APT_Single3DActor::SetVertexArrayFromJSONResponseBody(const UPT_HTTPComponent* InHTTPComponent, const FString& InFieldName, TArray<FVector>& OutVertexArray)
{
	this->VertexArray.Empty();
	UPT_JSONConverter::ConvertJSONResponseBodyToVectorArray(InHTTPComponent, InFieldName, this->VertexArray);
	OutVertexArray = this->VertexArray;
}

void APT_Single3DActor::SetVertexColorArrayFromJSONResponseBody(const UPT_HTTPComponent* InHTTPComponent, const FString& InFieldName, TArray<FLinearColor>& InVertexColorArray)
{
	this->VertexColorArray.Empty();
	UPT_JSONConverter::ConvertJSONResponseBodyToColorArray(InHTTPComponent, InFieldName, this->VertexColorArray);
	InVertexColorArray = this->VertexColorArray;
}

//Function which calculates the normals from the VertexArray
void APT_Single3DActor::CalculateNormals(const TArray<FVector>& InVertexArray, const TArray<int32> InTriangleIndexArray, TArray<FVector>& OutNormalArray)
{
	OutNormalArray.Init(FVector(0.0f, 0.0f, 0.0f), InVertexArray.Num());

	for (int32 i = 0; i < InTriangleIndexArray.Num(); i += 3)
	{									
		FVector Vertex0 = InVertexArray[InTriangleIndexArray[i]];
		FVector Vertex1 = InVertexArray[InTriangleIndexArray[i + 1]];
		FVector Vertex2 = InVertexArray[InTriangleIndexArray[i + 2]];

		FVector Edge1 = Vertex1 - Vertex0;
		FVector Edge2 = Vertex2 - Vertex0;

		FVector Normal = FVector::CrossProduct(Edge1, Edge2);

		OutNormalArray[InTriangleIndexArray[i]] += Normal;
		OutNormalArray[InTriangleIndexArray[i + 1]] += Normal;
		OutNormalArray[InTriangleIndexArray[i + 2]] += Normal;
	}

	for (int32 i = 0; i < OutNormalArray.Num(); i++)
	{
		OutNormalArray[i].Normalize();
	}
}

//Function which calculates the inverted normals from the VertexArray
void APT_Single3DActor::CalculateInvertedNormals(const TArray<FVector>& InVertexArray, const TArray<int32> InTriangleIndexArray, TArray<FVector>& OutInvertedNormalArray)
{
	OutInvertedNormalArray.Init(FVector(0.0f, 0.0f, 0.0f), InVertexArray.Num());


	for (int32 i = 0; i < InTriangleIndexArray.Num(); i += 3)
	{
		FVector Vertex0 = InVertexArray[InTriangleIndexArray[i]];
		FVector Vertex1 = InVertexArray[InTriangleIndexArray[i + 1]];
		FVector Vertex2 = InVertexArray[InTriangleIndexArray[i + 2]];

		FVector Edge1 = Vertex1 - Vertex0;
		FVector Edge2 = Vertex2 - Vertex0;

		FVector Normal = FVector::CrossProduct(Edge1, Edge2);

		OutInvertedNormalArray[InTriangleIndexArray[i]] -= Normal;
		OutInvertedNormalArray[InTriangleIndexArray[i + 1]] -= Normal;
		OutInvertedNormalArray[InTriangleIndexArray[i + 2]] -= Normal;
	}

	for (int32 i = 0; i < OutInvertedNormalArray.Num(); i++)
	{
		OutInvertedNormalArray[i].Normalize();
	}
}

void APT_Single3DActor::ResetSingle3DActorArrays()
{
	this->VertexArray.Empty();
	this->VertexColorArray.Empty();
	this->TriangleIndexArray.Empty();
	this->NormalArray.Empty();
}

void APT_Single3DActor::InitWhiteVertexColor(const int32& InVertexArrayLength, const float& InAlphaValue)
{
	this->VertexColorArray.Init(FLinearColor(255.f, 255.f, 255.f, InAlphaValue), InVertexArrayLength);
}
