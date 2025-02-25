// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved
// Modifications (C) 2025 David Hasse - All Rights Reserved

/**
 * @file PT_ConfigurationWidget.h
 * @brief Header file for the UPT_ConfigurationWidget class, which provides functionality for server configuration management.
 *
 * This file contains the declaration of the UPT_ConfigurationWidget class, which includes methods for retrieving server addresses
 * for specific interactions.
 */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PT_HTTPComponent.h"
#include "Misc/Optional.h"
#include "PT_ConfigurationWidget.generated.h"

/**
 * @brief A widget class for managing server configuration.
 * 
 * This class provides functionality to retrieve server addresses for specific server interactions.
 */
UCLASS()
class PLANNINGTOOL_ET_API UPT_ConfigurationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
  * @brief Gets the server run simulations address.
  * 
  * This function returns the address used to run simulations on the server.
  * 
  * @return FString The server run simulations address.
  */
	UFUNCTION(BlueprintCallable, Category = "Server Management")
	FString GetServerRunSimulationsAddress();
};
