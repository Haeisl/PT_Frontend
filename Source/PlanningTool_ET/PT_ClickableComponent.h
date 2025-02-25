// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved
// Modifications (C) 2025 David Hasse - All Rights Reserved

/**
 * @file PT_ClickableComponent.h
 * @brief Header file for the UPT_ClickableComponent class.
 * 
 * This file contains the declaration of the UPT_ClickableComponent class, which is responsible for handling clickable component behavior.
 * 
 */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PT_ClickableComponent.generated.h"

/**
 * @class UPT_ClickableComponent
 * @brief A class that represents a clickable component.
 * 
 * This class is responsible for handling the behavior of clickable components within the game.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLANNINGTOOL_ET_API UPT_ClickableComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    /**
     * @brief Sets default values for this component's properties.
     */
    UPT_ClickableComponent();

protected:
    /**
     * @brief Called when the game starts.
     */
    virtual void BeginPlay() override;

public:    
    /**
     * @brief Called every frame.
     * @param DeltaTime The time elapsed since the last frame.
     * @param TickType The type of tick this is, for example, are we paused, or 'simulating'.
     * @param ThisTickFunction Internal tick function struct that caused this to run.
     */
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
