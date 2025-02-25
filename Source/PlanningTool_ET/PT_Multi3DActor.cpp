// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved


#include "PT_Multi3DActor.h"
#include "PT_JSONConverter.h"

// Sets default values
APT_Multi3DActor::APT_Multi3DActor()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APT_Multi3DActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APT_Multi3DActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APT_Multi3DActor::ConvertJSONResponseBodyToMultiMesh(const UPT_HTTPComponent* InHTTPComponent, const FString& InFieldName, const TArray<FString>& InTagArray, const TArray<FString>& InDescriptionArray, TArray<FPT_MeshData>& OutMeshArray)
{
	TSharedPtr<FJsonObject> ResponseObject = InHTTPComponent->GetResponseObject();
	return this->ConvertJSONObjectToMultiMesh(&ResponseObject, InFieldName, InTagArray, InDescriptionArray, OutMeshArray);
}

void APT_Multi3DActor::ConvertJSONObjectToMultiMesh(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InFieldName, const TArray<FString>& InTagArray, const TArray<FString>& InDescriptionArray, TArray<FPT_MeshData>& OutMeshArray)
{
	const TSharedPtr<FJsonObject>* JsonObjectPtr;
	OutMeshArray.Empty();

	if (InJsonObjectPtr->Get()->TryGetObjectField(InFieldName, JsonObjectPtr))
	{
		for (int32 i = 0; i < InTagArray.Num(); i++)
		{
			FPT_MeshData MeshData = FPT_MeshData();

			MeshData.Id = InTagArray[i];
			MeshData.Description = InDescriptionArray[i];

			UPT_JSONConverter::ConvertJSONObjectToTriangleIndexArray(JsonObjectPtr, InTagArray[i], MeshData.TriangleIndexArray);

			OutMeshArray.Add(MeshData);
		}

		//for (FString Tag : InTagArray)
		//{
		//	FPT_MeshData MeshData = FPT_MeshData();

		//	MeshData.Id = Tag;

		//	UPT_JSONConverter::ConvertJSONObjectToTriangleIndexArray(JsonObjectPtr, Tag, MeshData.TriangleIndexArray);

		//	OutMeshArray.Add(MeshData);
		//}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[APT_Multi3DActor::ConvertJSONObjectToMultiMesh] Field %s not found!"), *InFieldName);
	}
}

void APT_Multi3DActor::ConvertJSONResponseBodyToMultiVolume(const UPT_HTTPComponent* InHTTPComponent, const FString& InFieldName, const TArray<FString>& InTagArray, const TArray<FVector>& InVertexArray, const TArray<FLinearColor>& InVertexColorArray, TArray<FPT_VolumeData>& OutVolumeArray)
{
	TSharedPtr<FJsonObject> ResponseObject = InHTTPComponent->GetResponseObject();
	return this->ConvertJSONObjectToMultiVolume(&ResponseObject, InFieldName, InTagArray, InVertexArray, InVertexColorArray, OutVolumeArray);
}

void APT_Multi3DActor::ConvertJSONObjectToMultiVolume(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InFieldName, const TArray<FString>& InTagArray, const TArray<FVector>& InVertexArray, const TArray<FLinearColor>& InVertexColorArray, TArray<FPT_VolumeData>& OutVolumeArray)
{
	const TSharedPtr<FJsonObject>* JsonObjectPtr;
	OutVolumeArray.Empty();

	if (InJsonObjectPtr->Get()->TryGetObjectField(InFieldName, JsonObjectPtr))
	{
		for (FString Tag : InTagArray)
		{
			FPT_VolumeData VolumeData = FPT_VolumeData();

			VolumeData.Id = Tag;

			UPT_JSONConverter::ConvertJSONObjectToIntegerArray(JsonObjectPtr, Tag, VolumeData.VertexIndexArray);
			this->CreatePointCloudArray(VolumeData.VertexIndexArray, InVertexArray, InVertexColorArray, VolumeData.PointCloudArray);

			OutVolumeArray.Add(VolumeData);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[APT_Multi3DActor::ConvertJSONObjectToMultiVolumes] Field %s not found!"), *InFieldName);
	}
}

void APT_Multi3DActor::ConvertJSONResponseBodyToTetraArray(const UPT_HTTPComponent* InHTTPComponent, const FString& InFieldName, const TArray<FString>& InTagArray, TArray<TArray<FPT_TetraData>>& OutTetraDataArray)
{
	TSharedPtr<FJsonObject> ResponseObject = InHTTPComponent->GetResponseObject();
	return this->ConvertJSONObjectToTetraArray(&ResponseObject, InFieldName, InTagArray, OutTetraDataArray);
}

void APT_Multi3DActor::ConvertJSONObjectToTetraArray(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InFieldName, const TArray<FString>& InTagArray, TArray<TArray<FPT_TetraData>>& OutTetraDataArray)
{
	const TSharedPtr<FJsonObject>* JsonObjectPtr;
	OutTetraDataArray.Empty();

	if (InJsonObjectPtr->Get()->TryGetObjectField(InFieldName, JsonObjectPtr))
	{
		for (FString Tag : InTagArray)
		{
			TArray<FPT_TetraData> TetraDataArray;
			UPT_JSONConverter::ConvertJSONObjectToTetraArray(JsonObjectPtr, Tag, TetraDataArray);
			OutTetraDataArray.Add(TetraDataArray);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[APT_Multi3DActor::ConvertJSONObjectToTetraData] Field %s not found!"), *InFieldName);
	}
}

void APT_Multi3DActor::CalculateNormalsForMultiMesh(TArray<FVector>& OutNormalArray)
{
	OutNormalArray.Init(FVector(0.0f, 0.0f, 0.0f), this->VertexArray.Num());

	for(const FPT_MeshData MeshData : this->MeshDataPerTagArray)
	{
		for (int32 i = 0; i < MeshData.TriangleIndexArray.Num(); i += 3)
		{
			FVector Vertex0 = this->VertexArray[MeshData.TriangleIndexArray[i]];
			FVector Vertex1 = this->VertexArray[MeshData.TriangleIndexArray[i + 1]];
			FVector Vertex2 = this->VertexArray[MeshData.TriangleIndexArray[i + 2]];

			FVector Edge1 = Vertex1 - Vertex0;
			FVector Edge2 = Vertex2 - Vertex0;

			FVector Normal = FVector::CrossProduct(Edge1, Edge2);

			OutNormalArray[MeshData.TriangleIndexArray[i]] -= Normal;
			OutNormalArray[MeshData.TriangleIndexArray[i + 1]] -= Normal;
			OutNormalArray[MeshData.TriangleIndexArray[i + 2]] -= Normal;
		}
	}

	for (int32 i = 0; i < OutNormalArray.Num(); i++)
	{
		OutNormalArray[i].Normalize();
	}
}

void APT_Multi3DActor::GetMultiMeshAndMultiVolumeFromJSONResponseBody(const UPT_HTTPComponent* InHTTPComponent, TArray<FVector>& OutVertexArray, TArray<FVector>& OutNormalArray, TArray<FString>& OutMeshTagArray, TArray<FString>& OutVolumeTagArray, TArray<FString>& OutMeshDescriptionArray, TArray<FString>& OutVolumeDescriptionArray, TArray<FPT_MeshData>& OutMeshDataArray, TArray<FPT_VolumeData>& OutVolumeDataArray)
{
	OutVertexArray.Empty();
	OutMeshTagArray.Empty();
	OutMeshDescriptionArray.Empty();
	OutVolumeTagArray.Empty();
	OutVolumeDescriptionArray.Empty();
	OutMeshDataArray.Empty();
	OutVolumeDataArray.Empty();
	OutNormalArray.Empty();

	this->VertexArray.Empty();
	this->TetraDataPerTagArray.Empty();
	this->MeshDataPerTagArray.Empty();

	UPT_JSONConverter::ConvertJSONResponseBodyToVectorArray(InHTTPComponent, "vertices", OutVertexArray);
	this->VertexArray = OutVertexArray;
	this->VertexColorArray.Init(FLinearColor().White, this->VertexArray.Num());

	UPT_JSONConverter::ConvertJSONResponseBodyToStringArray(InHTTPComponent, "mesh_tags", OutMeshTagArray);
	UPT_JSONConverter::ConvertJSONResponseBodyToStringArray(InHTTPComponent, "mesh_descriptions", OutMeshDescriptionArray);
	this->ConvertJSONResponseBodyToMultiMesh(InHTTPComponent, "meshes", OutMeshTagArray, OutMeshDescriptionArray, OutMeshDataArray);
	this->MeshDataPerTagArray = OutMeshDataArray;

	this->CalculateNormalsForMultiMesh(OutNormalArray);

	MeshDataLoadedCallbackEvent.Broadcast();

	UPT_JSONConverter::ConvertJSONResponseBodyToStringArray(InHTTPComponent, "volume_tags", OutVolumeTagArray);
	this->ConvertJSONResponseBodyToMultiVolume(InHTTPComponent, "volumes", OutVolumeTagArray, OutVertexArray, this->VertexColorArray, OutVolumeDataArray);
	UPT_JSONConverter::ConvertJSONResponseBodyToStringArray(InHTTPComponent, "volume_descriptions", OutVolumeDescriptionArray);
	this->ConvertJSONResponseBodyToTetraArray(InHTTPComponent, "volumes_raw", OutVolumeTagArray, this->TetraDataPerTagArray);

	VolumeDataLoadedCallbackEvent.Broadcast();
}

void APT_Multi3DActor::GetMultiMeshFromJSONResponseBody(const UPT_HTTPComponent* InHTTPComponent, TArray<FVector>& OutVertexArray, TArray<FVector>& OutNormalArray, TArray<FString>& OutMeshTagArray, TArray<FString>& OutMeshDescriptionArray, TArray<FPT_MeshData>& OutMeshDataArray)
{
	OutVertexArray.Empty();
	OutMeshTagArray.Empty();
	OutMeshDescriptionArray.Empty();
	OutMeshDataArray.Empty();
	OutNormalArray.Empty();

	this->VertexArray.Empty();
	this->MeshDataPerTagArray.Empty();

	UPT_JSONConverter::ConvertJSONResponseBodyToVectorArray(InHTTPComponent, "vertices", OutVertexArray);
	this->VertexArray = OutVertexArray;
	this->VertexColorArray.Init(FLinearColor().White, this->VertexArray.Num());

	UPT_JSONConverter::ConvertJSONResponseBodyToStringArray(InHTTPComponent, "mesh_tags", OutMeshTagArray);
	UPT_JSONConverter::ConvertJSONResponseBodyToStringArray(InHTTPComponent, "mesh_descriptions", OutMeshDescriptionArray);
	this->ConvertJSONResponseBodyToMultiMesh(InHTTPComponent, "meshes", OutMeshTagArray, OutMeshDescriptionArray, OutMeshDataArray);
	this->MeshDataPerTagArray = OutMeshDataArray;

	this->CalculateNormalsForMultiMesh(OutNormalArray);

	MeshDataLoadedCallbackEvent.Broadcast();
}

void APT_Multi3DActor::GetMultiVolumeFromJSONResponseBody(const UPT_HTTPComponent* InHTTPComponent, TArray<FVector>& OutVertexArray, TArray<FString>& OutVolumeTagArray, TArray<FString>& OutVolumeDescriptionArray, TArray<FPT_VolumeData>& OutVolumeDataArray)
{
	OutVertexArray.Empty();
	OutVolumeTagArray.Empty();
	OutVolumeDescriptionArray.Empty();
	OutVolumeDataArray.Empty();

	this->VertexArray.Empty();
	this->TetraDataPerTagArray.Empty();

	UPT_JSONConverter::ConvertJSONResponseBodyToVectorArray(InHTTPComponent, "vertices", OutVertexArray);
	this->VertexArray = OutVertexArray;
	this->VertexColorArray.Init(FLinearColor().White, this->VertexArray.Num());

	UPT_JSONConverter::ConvertJSONResponseBodyToStringArray(InHTTPComponent, "volume_tags", OutVolumeTagArray);
	this->ConvertJSONResponseBodyToMultiVolume(InHTTPComponent, "volumes", OutVolumeTagArray, OutVertexArray, this->VertexColorArray, OutVolumeDataArray);
	UPT_JSONConverter::ConvertJSONResponseBodyToStringArray(InHTTPComponent, "volume_descriptions", OutVolumeDescriptionArray);
	this->ConvertJSONResponseBodyToTetraArray(InHTTPComponent, "volumes_raw", OutVolumeTagArray, this->TetraDataPerTagArray);

	VolumeDataLoadedCallbackEvent.Broadcast();
}

void APT_Multi3DActor::ResetMulti3DActorArrays()
{
	this->ResetSingle3DActorArrays();
	this->TetraDataPerTagArray.Empty();
	this->MeshDataPerTagArray.Empty();
}
