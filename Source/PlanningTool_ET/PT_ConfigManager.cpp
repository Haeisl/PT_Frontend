#include "PT_ConfigManager.h"

FString UPT_ConfigManager::SERVER_ADDRESS = TEXT("http://127.0.0.1:5000");
FString UPT_ConfigManager::URL_REACHED = SERVER_ADDRESS + TEXT("/reached");
FString UPT_ConfigManager::URL_RUN_SIMULATIONS = SERVER_ADDRESS + TEXT("/run_simulations");
FString UPT_ConfigManager::URL_CONFIGURATION_MESH = SERVER_ADDRESS + TEXT("/3d/configuration");
FString UPT_ConfigManager::URL_SKIN_MESH = SERVER_ADDRESS + TEXT("/3d/configuration/skin");
FString UPT_ConfigManager::URL_ELECTRODES_POSITION = SERVER_ADDRESS + TEXT("/data/elect_pos");
FString UPT_ConfigManager::URL_DATA_VALIDATION = SERVER_ADDRESS + TEXT("/data/validation");
FString UPT_ConfigManager::URL_ROI = SERVER_ADDRESS + TEXT("/data/roi");
FString UPT_ConfigManager::URL_SIMULATED_3D = SERVER_ADDRESS + TEXT("/3d/simulated");
FString UPT_ConfigManager::URL_SIMULATED_DATA = SERVER_ADDRESS + TEXT("/data/simulated");
FString UPT_ConfigManager::URL_INTERPOLATED_DATA = SERVER_ADDRESS + TEXT("/data/interpolated");

const TArray<FString> UPT_ConfigManager::DATA_TAG_ARRAY = { TEXT("1001"), TEXT("1002"), TEXT("1003"), TEXT("1006"), TEXT("1008"), TEXT("1009"), TEXT("1010"), TEXT("1"), TEXT("2"), TEXT("3"), TEXT("6"), TEXT("8"), TEXT("9"), TEXT("10") };
//const TArray<FString> UPT_ConfigManager::DATA_TAG_ARRAY = { TEXT("1001"), TEXT("1002"), TEXT("1003"), TEXT("1008"), TEXT("1"), TEXT("2"), TEXT("3"), TEXT("8")};
const TArray<FString> UPT_ConfigManager::DATA_TAG_NAME_ARRAY;
const TArray<int32> UPT_ConfigManager::DATA_TAG_INDEX_ARRAY = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
const TArray<int32> UPT_ConfigManager::DATA_TAG_VOLUME_INDEX_ARRAY = { 7, 8, 9, 10, 11, 12, 13 };
const TArray<int32> UPT_ConfigManager::DATA_TAG_MESH_INDEX_ARRAY = { 0, 1, 2, 3, 4, 5, 6 };

UPT_ConfigManager::UPT_ConfigManager()
{
    // Constructor logic here
}

UPT_ConfigManager::~UPT_ConfigManager()
{
    // Destructor logic here
}

void UPT_ConfigManager::SetServerAddress(const FString& NewAddress)
{
    SERVER_ADDRESS = NewAddress;
    // Update all dependent URLs
    URL_REACHED = SERVER_ADDRESS + TEXT("/reached");
    URL_RUN_SIMULATIONS = SERVER_ADDRESS + TEXT("/run_simulations");
    URL_CONFIGURATION_MESH = SERVER_ADDRESS + TEXT("/3d/configuration");
    URL_SKIN_MESH = SERVER_ADDRESS + TEXT("/3d/configuration/skin");
    URL_ELECTRODES_POSITION = SERVER_ADDRESS + TEXT("/data/elect_pos");
    URL_DATA_VALIDATION = SERVER_ADDRESS + TEXT("/data/validation");
    URL_ROI = SERVER_ADDRESS + TEXT("/data/roi");
    URL_SIMULATED_3D = SERVER_ADDRESS + TEXT("/3d/simulated");
    URL_SIMULATED_DATA = SERVER_ADDRESS + TEXT("/data/simulated");
    URL_INTERPOLATED_DATA = SERVER_ADDRESS + TEXT("/data/interpolated");
    UE_LOG(LogTemp, Display, TEXT("Set new server address and updated URLs to %s"), *NewAddress);
}

FString UPT_ConfigManager::GetReachedAddress()
{
	return URL_REACHED;
}

FString UPT_ConfigManager::GetRunSimulationsAddress()
{
    return URL_RUN_SIMULATIONS;
}

FString UPT_ConfigManager::GetConfigurationMeshAddress(const FString& InPatientId)
{
    return GetUrlConfigurationMesh() + TEXT("/") + InPatientId;
}

FString UPT_ConfigManager::GetSkinMeshAddress(const FString& InPatientId)
{
    return GetUrlSkinMesh() + TEXT("/") + InPatientId;
}

FString UPT_ConfigManager::GetElectrodesPositionAddress(const FString& InPatientId, const FString& InConfigId)
{
    return GetUrlElectrodesPosition() + TEXT("/") + InPatientId + TEXT("/") + InConfigId;
}

FString UPT_ConfigManager::GetDataVallidationAddress(const FString& InPatientId, const FString& InConfigId)
{
    return GetUrlDataValidation() + TEXT("/") + InPatientId + TEXT("/") + InConfigId;
}

FString UPT_ConfigManager::GetRoiAddress(const FString& InPatientId, const FString& InRoiId)
{
    return GetUrlROI() + TEXT("/") + InPatientId + TEXT("/") + InRoiId;
}

FString UPT_ConfigManager::GetSimulated3DAddress(const FString& InPatientId, const FString& InConfigId)
{
    return GetUrlSimulated3D() + TEXT("/") + InPatientId + TEXT("/") + InConfigId;
}

FString UPT_ConfigManager::GetSimulatedDataAddress(const FString& InPatientId, const FString& InConfigId, const FString& InRoiId)
{
    return GetUrlSimulatedData() + TEXT("/") + InPatientId + TEXT("/") + InConfigId + TEXT("/") + InRoiId;
}

FString UPT_ConfigManager::GetInterpolatedDataAddress(const FString& InPatientId, const FString& InConfigId, const FString& InRoiId, const FString& InInterpolationId)
{
    return GetUrlInterpolatedData() + TEXT("/") + InPatientId + TEXT("/") + InConfigId + TEXT("/") + InRoiId + TEXT("/") + InInterpolationId;
}
