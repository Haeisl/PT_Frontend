// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved
// Modifications (C) 2025 David Hasse - All Rights Reserved

/**
 * @file PT_ROIActor.h
 * @brief Header file for the APT_ROIActor class.
 * 
 * This file contains the declaration of the APT_ROIActor class, which is responsible for handling
 * the Region of Interest (ROI) in the Planning Tool.
 * 
 */

#pragma once

#include "CoreMinimal.h"
#include "PT_Single3DActor.h"
#include "ProceduralMeshComponent.h"
#include "InputActionValue.h"
#include "PT_EnumContainer.h"
#include "PT_ROIActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRoiChangedEventDelegate);

/**
 * @class APT_ROIActor
 * @brief A class representing the Region of Interest (ROI) actor.
 * 
 * This class handles the ROI in the Planning Tool, including its position, size, rotation, and
 * other properties. It also provides methods for transforming the ROI bounds to world space
 * coordinates, logging corner points, and converting ROI data to JSON.
 */
UCLASS()
class PLANNINGTOOL_ET_API APT_ROIActor : public APT_Single3DActor
{
	GENERATED_BODY()
	
public:	
	/**
  * @brief Sets default values for this actor's properties.
  */
	APT_ROIActor();

protected:
	/**
  * @brief Called when the game starts or when spawned.
  */
	virtual void BeginPlay() override;

public:	
	/**
     * @brief Called every frame.
     * @param DeltaTime The time elapsed since the last frame.
     */
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere)
    UProceduralMeshComponent* ProceduralMesh;

    // Enhanced Input
    UPROPERTY(EditAnywhere, Category = "PT_Input")
    class UInputMappingContext* IMC_PT_ROIActor;

    UPROPERTY(EditAnywhere, Category = "PT_Input")
    class UInputAction* IA_MoveBox;

    /**
     * @brief Transforms the ROI bounds to world space coordinates.
     * @return Array of transformed vertices in world space.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_ROI")
    TArray<FVector> getROIBoundsToWorldSpace();

    /**
     * @brief Logs the corner points of the ROI to the console.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_ROI")
    void PrintCornerPoints();

    /**
     * @brief Initializes the current camera manager by getting the PlayerCameraManager from the first player controller.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_ROI")
    void InitCurrentCameraManager();

    /**
     * @brief Sets the position of the ROI.
     * @param InPosX Position in the X dimension.
     * @param InPosY Position in the Y dimension.
     * @param InPosZ Position in the Z dimension.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_ROI")
    void SetROIPosition(const float& InPosX, const float& InPosY, const float& InPosZ);

    /**
     * @brief Moves the ROI position by the specified amount.
     * @param InNewPosition New position to move the ROI to.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_ROI")
    void MoveROIPosition(const FVector& InNewPosition);

    /**
     * @brief Sets the size of the ROI and applies the transformation.
     * @param InSizeX Size in the X dimension.
     * @param InSizeY Size in the Y dimension.
     * @param InSizeZ Size in the Z dimension.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_ROI")
    void SetROISize(const float& InSizeX, const float& InSizeY, const float& InSizeZ);

    /**
     * @brief Sets the rotation of the ROI and applies the transformation.
     * @param InPitch Pitch rotation.
     * @param InYaw Yaw rotation.
     * @param InRoll Roll rotation.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_ROI")
    void SetROIRotation(const float& InPitch, const float& InYaw, const float& InRoll);

    /**
     * @brief Converts the ROI data to a JSON string.
     * @param InPatientId Patient ID.
     * @param InRoiId ROI ID.
     * @param InVectorArray Array of vectors representing the ROI bounds.
     * @param InCenterPosition Center position of the ROI.
     * @return JSON string representing the ROI data.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_ROI")
    FString ConvertRoiToJson(const FString& InPatientId, const FString& InRoiId, const TArray<FVector>& InVectorArray, const FVector& InCenterPosition);

    UPROPERTY(EditAnywhere, Category = "PT_ROI")
    UMaterialInterface* Material;

    UPROPERTY(BlueprintAssignable, Category = "PT_ROI_Event")
    FRoiChangedEventDelegate RoiChangedEvent;

    /**
     * @brief Gets the current size of the ROI.
     * @return Current size of the ROI.
     */
    UFUNCTION(BlueprintPure, Category = "PT_ROI")
    FVector GetCurrentROISize() { return CurrentROISize; }

    /**
     * @brief Gets the current position of the ROI.
     * @return Current position of the ROI.
     */
    UFUNCTION(BlueprintPure, Category = "PT_ROI")
    FVector GetCurrentROIPosition() { return CurrentROIPosition; };

    /**
     * @brief Gets the current rotation of the ROI.
     * @return Current rotation of the ROI.
     */
    UFUNCTION(BlueprintPure, Category = "PT_ROI")
    FRotator GetCurrentROIRotation() { return CurrentROIRotation; };

private:
    /**
     * @brief Generates the box mesh for the ROI.
     */
    void GenerateBoxMesh();

    /**
     * @brief Applies the transformations to the ROI.
     * @param NewSize New size of the ROI.
     * @param NewPosition New position of the ROI.
     * @param NewRotation New rotation of the ROI.
     */
    void ApplyTransformations(const FVector& NewSize, const FVector& NewPosition, const FRotator& NewRotation);

    /**
     * @brief Resets the vertex array to the standard size.
     */
    void ResetVertexArrayToStandardSize();

    /**
     * @brief Handles the input action to move the ROI.
     * @param Value Input action value representing the new position.
     */
    void OnMoveROI(const FInputActionValue& Value);

    /**
     * @brief Transforms the ROI bounds to world space coordinates relative to another actor.
     * @param OtherActor The actor to which the coordinates should be relative.
     * @return Array of transformed vertices in world space relative to the other actor.
     */
    TArray<FVector> GetROIBoundsToWorldSpaceRelativeTo(AActor* OtherActor);

    /**
     * @brief Manually calculates the normals for the current vertex and triangle index arrays.
     */
    void CalculateNormalsManually();

    FVector CurrentROISize;
    FVector CurrentROIPosition;
    FRotator CurrentROIRotation;

    APlayerCameraManager* CameraManager;
};
