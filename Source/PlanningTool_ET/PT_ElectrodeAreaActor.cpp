// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved


#include "PT_ElectrodeAreaActor.h"
#include "PT_JSONConverter.h"

// Sets default values
APT_ElectrodeAreaActor::APT_ElectrodeAreaActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APT_ElectrodeAreaActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APT_ElectrodeAreaActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APT_ElectrodeAreaActor::ProcessResponseData(
    const UPT_HTTPComponent* InHttpComponent,
    FVector& OutCenter,
    FVector& OutA, FVector& OutB, FVector& OutC, FVector& OutD,
    FRotator& OutRotation,
    int& OutRows, int& outColumns,
    double& outCellSize,
    int& OutNumber,
    TArray<FVector>& OutElectrodePositions
)
{
    const FString MetadataFieldName = "Metadata";
    const FString CornerPointsFieldName = "CornerPoints";
    const FString RotationFieldName = "Rotation";
    const FString ElectrodesFieldName = "Electrodes";

    const TSharedPtr<FJsonObject>* MetadataObject;
    if (InHttpComponent->GetResponseObject()->TryGetObjectField(MetadataFieldName, MetadataObject))
    {
        UPT_JSONConverter::ConvertJSONObjectToVector(MetadataObject, TEXT("CenterPoint"), OutCenter);
        UPT_JSONConverter::ConvertJSONToInteger(MetadataObject, TEXT("Rows"), OutRows);
        UPT_JSONConverter::ConvertJSONToInteger(MetadataObject, TEXT("Columns"), outColumns);
        UPT_JSONConverter::ConvertJSONToDouble(MetadataObject, TEXT("CellSize"), outCellSize);
        UPT_JSONConverter::ConvertJSONToInteger(MetadataObject, TEXT("Number"), OutNumber);

        const TSharedPtr<FJsonObject>* CornerPointsObject;
        if ((*MetadataObject)->TryGetObjectField(CornerPointsFieldName, CornerPointsObject))
        {
            UPT_JSONConverter::ConvertJSONObjectToVector(CornerPointsObject, TEXT("A"), OutA);
            UPT_JSONConverter::ConvertJSONObjectToVector(CornerPointsObject, TEXT("B"), OutB);
            UPT_JSONConverter::ConvertJSONObjectToVector(CornerPointsObject, TEXT("C"), OutC);
            UPT_JSONConverter::ConvertJSONObjectToVector(CornerPointsObject, TEXT("D"), OutD);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("[APT_ElectrodeAreaActor::ProcessResponseData] Field %s not found."), *CornerPointsFieldName);
        }

        const TSharedPtr<FJsonObject>* RotationObject;
        if ((*MetadataObject)->TryGetObjectField(RotationFieldName, RotationObject))
        {
            UPT_JSONConverter::ConvertJSONToDouble(RotationObject, TEXT("P"), OutRotation.Pitch);
            UPT_JSONConverter::ConvertJSONToDouble(RotationObject, TEXT("Y"), OutRotation.Yaw);
            UPT_JSONConverter::ConvertJSONToDouble(RotationObject, TEXT("R"), OutRotation.Roll);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("[APT_ElectrodeAreaActor::ProcessResponseData] Field %s not found."), *RotationFieldName);
        }

    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[APT_ElectrodeAreaActor::ProcessResponseData] Field %s not found."), *MetadataFieldName);
    }

    const TSharedPtr<FJsonObject>* ElectrodesObject;
    if (InHttpComponent->GetResponseObject()->TryGetObjectField(ElectrodesFieldName, ElectrodesObject))
    {
        for (int32 i = 0; i < OutNumber; i++)
        {
            FVector ElectrodePosition;
            UPT_JSONConverter::ConvertJSONObjectToVector(ElectrodesObject, FString::Printf(TEXT("Electrode_%d"), i), ElectrodePosition);
            OutElectrodePositions.Add(ElectrodePosition);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[APT_ElectrodeAreaActor::ProcessResponseData] Field %s not found."), *ElectrodesFieldName);
    }
}

void APT_ElectrodeAreaActor::ProcessValidationResponseData(
    const UPT_HTTPComponent* InHttpComponent,
    int32& OutElectrodeCount,
    TArray<int32>& OutSuccessfullElectrodeIndex,
    bool& OutIsCorrupted
)
{
    // Initialize output parameters
    OutIsCorrupted = false;
    OutSuccessfullElectrodeIndex.Empty();

    const TSharedPtr<FJsonObject>* MetadataObject;
    if (InHttpComponent->GetResponseObject()->TryGetObjectField(TEXT("metadata"), MetadataObject))
    {
        UPT_JSONConverter::ConvertJSONToInteger(MetadataObject, TEXT("electrode_count"), OutElectrodeCount);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Metadata field not found."));
    }

    // Check for the "successful_simulation_indices" array first as it simplifies the process
    TArray<int32> SuccessfulSimulationIndices;
    const TSharedPtr<FJsonObject> ResponseObject = InHttpComponent->GetResponseObject();
    UPT_JSONConverter::ConvertJSONObjectToIntegerArray(&ResponseObject, TEXT("successful_simulation_indices"), OutSuccessfullElectrodeIndex);

    // Iterate through all electrodes to check for any failure
    for (int32 i = 0; i < OutElectrodeCount; i++)
    {
        const TSharedPtr<FJsonObject>* ElectrodeObject;
        if (InHttpComponent->GetResponseObject()->TryGetObjectField(FString::Printf(TEXT("Electrode_%d"), i), ElectrodeObject))
        {
            FString SuccessValue;
            if ((*ElectrodeObject)->TryGetStringField(TEXT("success"), SuccessValue))
            {
                if (SuccessValue.Equals("false", ESearchCase::IgnoreCase))
                {
                    OutIsCorrupted = true;
                    break; // No need to check further if one failure is found
                }
            }
        }
    }
}


TArray<FVector> APT_ElectrodeAreaActor::FindNearestNeighbors(
    const FVector& InPoint, const TArray<FVector>& InGrid, TArray<int>& OutNearestNeighborsGridIndicies
)
{
    check(InGrid.Num() > 0);

    TArray<FDistanceAndPoint> DistancesAndPoints;
    DistancesAndPoints.SetNumZeroed(InGrid.Num());

    for (int32 i = 0; i < InGrid.Num(); i++)
    {
        double Distance = FVector::Dist(InPoint, InGrid[i]);
        DistancesAndPoints[i] = { Distance, InGrid[i], i };
    }

    DistancesAndPoints.Sort([](const FDistanceAndPoint& A, const FDistanceAndPoint& B)
    {
        return A.Distance < B.Distance;
    });

    TArray<FVector> NearestNeighbors;
    NearestNeighbors.SetNumZeroed(FMath::Min(3, InGrid.Num()));
    OutNearestNeighborsGridIndicies.SetNumZeroed(FMath::Min(3, InGrid.Num()));

    for (int32 i = 0; i < FMath::Min(3, InGrid.Num()); i++)
    {
        NearestNeighbors[i] = DistancesAndPoints[i].Point;
        OutNearestNeighborsGridIndicies[i] = DistancesAndPoints[i].gridIndex;
    }

    return NearestNeighbors;
}

void APT_ElectrodeAreaActor::BarycentricWeightCalculation(const FVector& InPoint, const FVector& InA, const FVector& InB, const FVector& InC, double& OutWeightA, double& OutWeightB, double& OutWeightC)
{
    FVector v0 = InB - InA;
    FVector v1 = InC - InA;
    FVector v2 = InPoint - InA;
    double d00 = FVector::DotProduct(v0, v0);
    double d01 = FVector::DotProduct(v0, v1);
    double d11 = FVector::DotProduct(v1, v1);
    double d20 = FVector::DotProduct(v2, v0);
    double d21 = FVector::DotProduct(v2, v1);
    double denom = d00 * d11 - d01 * d01;
    double invDenom = 1.0 / denom;

    OutWeightB = (d11 * d20 - d01 * d21) * invDenom;
    OutWeightC = (d00 * d21 - d01 * d20) * invDenom;
    OutWeightA = 1.0 - OutWeightB - OutWeightC;
}

