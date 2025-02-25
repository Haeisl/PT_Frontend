// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved
// Modifications (C) 2025 David Hasse - All Rights Reserved

/**
 * @file PT_ConfigManager.h
 * @brief Header file for the UPT_ConfigManager class.
 * 
 * This file contains the declaration of the UPT_ConfigManager class, which is responsible for managing configuration settings
 * and providing various URLs for server communication.
 * 
 */

#pragma once

#include "CoreMinimal.h"
#include "PT_ConfigManager.generated.h"

/**
 * @class UPT_ConfigManager
 * @brief A class that manages configuration settings and provides various URLs for server communication.
 */
UCLASS()
class PLANNINGTOOL_ET_API UPT_ConfigManager : public UObject
{
    GENERATED_BODY()

public:
    /**
     * @brief Constructor for UPT_ConfigManager.
     */
    UPT_ConfigManager();

    /**
     * @brief Destructor for UPT_ConfigManager.
     */
    ~UPT_ConfigManager();

    /**
     * @brief Sets the server address.
     * @param NewAddress The new server address.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_ConfigManager")
    static void SetServerAddress(const FString& NewAddress);

    /**
     * @brief Gets the reached address URL.
     * @return The reached address URL.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_ConfigManager")
    static FString GetReachedAddress();

    /**
     * @brief Gets the run simulations address URL.
     * @return The run simulations address URL.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_ConfigManager")
    static FString GetRunSimulationsAddress();

    /**
     * @brief Gets the configuration mesh address URL for a given patient ID.
     * @param InPatientId The patient ID.
     * @return The configuration mesh address URL.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_ConfigManager")
    static FString GetConfigurationMeshAddress(const FString& InPatientId);

    /**
     * @brief Gets the skin mesh address URL for a given patient ID.
     * @param InPatientId The patient ID.
     * @return The skin mesh address URL.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_ConfigManager")
    static FString GetSkinMeshAddress(const FString& InPatientId);

    /**
     * @brief Gets the electrodes position address URL for a given patient ID and configuration ID.
     * @param InPatientId The patient ID.
     * @param InConfigId The configuration ID.
     * @return The electrodes position address URL.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_ConfigManager")
    static FString GetElectrodesPositionAddress(const FString& InPatientId, const FString& InConfigId);

    /**
     * @brief Gets the data validation address URL for a given patient ID and configuration ID.
     * @param InPatientId The patient ID.
     * @param InConfigId The configuration ID.
     * @return The data validation address URL.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_ConfigManager")
    static FString GetDataVallidationAddress(const FString& InPatientId, const FString& InConfigId);

    /**
     * @brief Gets the ROI address URL for a given patient ID and ROI ID.
     * @param InPatientId The patient ID.
     * @param InRoiId The ROI ID.
     * @return The ROI address URL.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_ConfigManager")
    static FString GetRoiAddress(const FString& InPatientId, const FString& InRoiId);

    /**
     * @brief Gets the simulated 3D address URL for a given patient ID and configuration ID.
     * @param InPatientId The patient ID.
     * @param InConfigId The configuration ID.
     * @return The simulated 3D address URL.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_ConfigManager")
    static FString GetSimulated3DAddress(const FString& InPatientId, const FString& InConfigId);

    /**
     * @brief Gets the simulated data address URL for a given patient ID, configuration ID, and ROI ID.
     * @param InPatientId The patient ID.
     * @param InConfigId The configuration ID.
     * @param InRoiId The ROI ID.
     * @return The simulated data address URL.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_ConfigManager")
    static FString GetSimulatedDataAddress(const FString& InPatientId, const FString& InConfigId, const FString& InRoiId);

    /**
     * @brief Gets the interpolated data address URL for a given patient ID, configuration ID, ROI ID, and interpolation ID.
     * @param InPatientId The patient ID.
     * @param InConfigId The configuration ID.
     * @param InRoiId The ROI ID.
     * @param InInterpolationId The interpolation ID.
     * @return The interpolated data address URL.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_ConfigManager")
    static FString GetInterpolatedDataAddress(const FString& InPatientId, const FString& InConfigId, const FString& InRoiId, const FString& InInterpolationId);

    /**
     * @brief Gets the server address.
     * @return The server address.
     */
    UFUNCTION(BlueprintPure, Category = "PT_ConfigManager")
    static FString GetServerAddress() { return SERVER_ADDRESS; }

    /**
     * @brief Gets the URL for the configuration mesh.
     * @return The URL for the configuration mesh.
     */
    UFUNCTION(BlueprintPure, Category = "PT_ConfigManager")
    static FString GetUrlConfigurationMesh() { return URL_CONFIGURATION_MESH; }

    /**
     * @brief Gets the URL for the skin mesh.
     * @return The URL for the skin mesh.
     */
    UFUNCTION(BlueprintPure, Category = "PT_ConfigManager")
    static FString GetUrlSkinMesh() { return URL_SKIN_MESH; }

    /**
     * @brief Gets the URL for the electrodes position.
     * @return The URL for the electrodes position.
     */
    UFUNCTION(BlueprintPure, Category = "PT_ConfigManager")
    static FString GetUrlElectrodesPosition() { return URL_ELECTRODES_POSITION; }

    /**
     * @brief Gets the URL for data validation.
     * @return The URL for data validation.
     */
    UFUNCTION(BlueprintPure, Category = "PT_ConfigManager")
    static FString GetUrlDataValidation() { return URL_DATA_VALIDATION; }

    /**
     * @brief Gets the URL for ROI.
     * @return The URL for ROI.
     */
    UFUNCTION(BlueprintPure, Category = "PT_ConfigManager")
    static FString GetUrlROI() { return URL_ROI; }

    /**
     * @brief Gets the URL for simulated 3D data.
     * @return The URL for simulated 3D data.
     */
    UFUNCTION(BlueprintPure, Category = "PT_ConfigManager")
    static FString GetUrlSimulated3D() { return URL_SIMULATED_3D; }

    /**
     * @brief Gets the URL for simulated data.
     * @return The URL for simulated data.
     */
    UFUNCTION(BlueprintPure, Category = "PT_ConfigManager")
    static FString GetUrlSimulatedData() { return URL_SIMULATED_DATA; }

    /**
     * @brief Gets the URL for interpolated data.
     * @return The URL for interpolated data.
     */
    UFUNCTION(BlueprintPure, Category = "PT_ConfigManager")
    static FString GetUrlInterpolatedData() { return URL_INTERPOLATED_DATA; }

    /**
     * @brief Gets the data tag array.
     * @return The data tag array.
     */
    UFUNCTION(BlueprintPure, Category = "PT_ConfigManager")
    static TArray<FString> GetDataTagArray() { return DATA_TAG_ARRAY; }

    /**
     * @brief Gets the data tag name array.
     * @return The data tag name array.
     */
    UFUNCTION(BlueprintPure, Category = "PT_ConfigManager")
    static TArray<FString> GetDataTagNameArray() { return DATA_TAG_NAME_ARRAY; }

    /**
     * @brief Gets the data tag index array.
     * @return The data tag index array.
     */
    UFUNCTION(BlueprintPure, Category = "PT_ConfigManager")
    static TArray<int32> GetDataTagIndexArray() { return DATA_TAG_INDEX_ARRAY; }

    /**
     * @brief Gets the data tag volume index array.
     * @return The data tag volume index array.
     */
    UFUNCTION(BlueprintPure, Category = "PT_ConfigManager")
    static TArray<int32> GetDataTagVolumeIndexArray() { return DATA_TAG_VOLUME_INDEX_ARRAY; }

    /**
     * @brief Gets the data tag mesh index array.
     * @return The data tag mesh index array.
     */
    UFUNCTION(BlueprintPure, Category = "PT_ConfigManager")
    static TArray<int32> GetDataTagMeshIndexArray() { return DATA_TAG_MESH_INDEX_ARRAY; }

private:
    static FString SERVER_ADDRESS; ///< The server address.
    static FString URL_REACHED; ///< The reached address URL.
    static FString URL_RUN_SIMULATIONS; ///< The run simulations address URL.
    static FString URL_CONFIGURATION_MESH; ///< The configuration mesh address URL.
    static FString URL_SKIN_MESH; ///< The skin mesh address URL.
    static FString URL_ELECTRODES_POSITION; ///< The electrodes position address URL.
    static FString URL_DATA_VALIDATION; ///< The data validation address URL.
    static FString URL_ROI; ///< The ROI address URL.
    static FString URL_SIMULATED_3D; ///< The simulated 3D address URL.
    static FString URL_SIMULATED_DATA; ///< The simulated data address URL.
    static FString URL_INTERPOLATED_DATA; ///< The interpolated data address URL.

    static const TArray<FString> DATA_TAG_ARRAY; ///< The data tag array.
    static const TArray<FString> DATA_TAG_NAME_ARRAY; ///< The data tag name array.
    static const TArray<int32> DATA_TAG_INDEX_ARRAY; ///< The data tag index array.
    static const TArray<int32> DATA_TAG_VOLUME_INDEX_ARRAY; ///< The data tag volume index array.
    static const TArray<int32> DATA_TAG_MESH_INDEX_ARRAY; ///< The data tag mesh index array.
};
