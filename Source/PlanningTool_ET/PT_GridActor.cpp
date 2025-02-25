// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved


#include "PT_GridActor.h"
#include "PT_JSONConverter.h"

// Sets default values
APT_GridActor::APT_GridActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APT_GridActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APT_GridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString APT_GridActor::CreateGridJSON(const FString& InConfigId, const FString& InPatientId, const TArray<FVector>& InElectrodePositionArray, const TArray<FString>& InElectrodeNameArray, const FVector& InCenterPoint, const double& InCellSize, const TArray<FVector>& InCornerPointArray, const FRotator& InRotation, const int& InRowCount, const int& InColumnCount)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	TSharedPtr<FJsonObject> MetadataJson = MakeShareable(new FJsonObject);
	MetadataJson->SetStringField(TEXT("Patient_ID"), InPatientId);
	MetadataJson->SetStringField(TEXT("Config_ID"), InConfigId);
	MetadataJson->SetNumberField(TEXT("Number"), InElectrodePositionArray.Num());
	MetadataJson->SetNumberField(TEXT("CellSize"), InCellSize);
	MetadataJson->SetNumberField(TEXT("Rows"), InRowCount);
	MetadataJson->SetNumberField(TEXT("Columns"), InColumnCount);

	TSharedPtr<FJsonObject> CenterPoint = UPT_JSONConverter::CreateJsonObjectFromVector(InCenterPoint);
	MetadataJson->SetObjectField(TEXT("CenterPoint"), CenterPoint);

	TSharedPtr<FJsonObject> Rotation = MakeShareable(new FJsonObject);
	Rotation->SetNumberField(TEXT("P"), InRotation.Pitch);
	Rotation->SetNumberField(TEXT("Y"), InRotation.Yaw);
	Rotation->SetNumberField(TEXT("R"), InRotation.Roll);
	MetadataJson->SetObjectField(TEXT("Rotation"), Rotation);

	TSharedPtr<FJsonObject> CornerPoints = MakeShareable(new FJsonObject);
	CornerPoints->SetObjectField(TEXT("A"), UPT_JSONConverter::CreateJsonObjectFromVector(InCornerPointArray[0]));
	CornerPoints->SetObjectField(TEXT("B"), UPT_JSONConverter::CreateJsonObjectFromVector(InCornerPointArray[1]));
	CornerPoints->SetObjectField(TEXT("C"), UPT_JSONConverter::CreateJsonObjectFromVector(InCornerPointArray[2]));
	CornerPoints->SetObjectField(TEXT("D"), UPT_JSONConverter::CreateJsonObjectFromVector(InCornerPointArray[3]));
	MetadataJson->SetObjectField(TEXT("CornerPoints"), CornerPoints);

	JsonObject->SetObjectField(TEXT("Metadata"), MetadataJson);

	TSharedPtr<FJsonObject> ElectrodesJson = MakeShareable(new FJsonObject);

	for (int32 i = 0; i < InElectrodePositionArray.Num(); ++i)
	{
		FVector Pos = InElectrodePositionArray[i];

		TSharedPtr<FJsonObject> ElectrodeJson = UPT_JSONConverter::CreateJsonObjectFromVector(Pos);

		ElectrodesJson->SetObjectField(InElectrodeNameArray[i], ElectrodeJson);
	}

	JsonObject->SetObjectField(TEXT("Electrodes"), ElectrodesJson);

	return UPT_JSONConverter::SerializeJsonObjectToString(JsonObject);;
}

