// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved
// Modifications (C) 2025 David Hasse - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PT_EnumContainer.generated.h"

/**
 * @brief Enum representing the faces of a box.
 */
UENUM(BlueprintType)
enum class EBoxFace : uint8
{
    None,   /**< No face */
    Front,  /**< Front face */
    Back,   /**< Back face */
    Left,   /**< Left face */
    Right,  /**< Right face */
    Top,    /**< Top face */
    Bottom  /**< Bottom face */
};

/**
 * @brief Enum representing the current UI state.
 */
UENUM(BlueprintType)
enum class ECurrentUI : uint8
{
    Main,           /**< Main UI */
    Configuration,  /**< Configuration UI */
    Interpolation   /**< Interpolation UI */
};

/**
 * @brief Enum representing the slicing type.
 */
UENUM(BlueprintType)
enum class ESlicingType : uint8
{
    X,  /**< Slicing along the X axis */
    Y,  /**< Slicing along the Y axis */
    Z   /**< Slicing along the Z axis */
};
