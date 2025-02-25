// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved
// Modifications (C) 2025 David Hasse - All Rights Reserved

/**
*
* @file ManageServerWidget.h
* @brief Header file for the UManageServerWidget class, which provides functionality for managing server interactions on the "Server Management" screen.
*
* This file contains the declaration of the UManageServerWidget class, which includes methods for saving server addresses, 
* retrieving server addresses for specific interactions, and processing server response data.
*
*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PT_HTTPComponent.h"
#include "Misc/Optional.h"
#include "ManageServerWidget.generated.h"

/**
 * @brief A widget class for managing server interactions specifically for the "Server Management" screen.
 * 
 * This class provides functionality to save server addresses and process server responses for specific server interactions.
 */
UCLASS()
class PLANNINGTOOL_ET_API UManageServerWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    /**
     * @brief Saves the server address.
     * 
     * This function saves the server IP address and port.
     * 
     * @param IPAddress The IP address of the server.
     * @param Port The port of the server.
     */
    UFUNCTION(BlueprintCallable, Category = "Server Management")
    void SaveServerAddress(const FString& IPAddress, const FString& Port);

    /**
     * @brief Gets the server reached address.
     * 
     * This function returns the address used to check if the server is reachable.
     * 
     * @return FString The server reached address.
     */
    UFUNCTION(BlueprintCallable, Category = "Server Management")
    FString GetServerReachedAddress();

    /**
     * @brief Gets the server run simulations address.
     * 
     * This function returns the address used to run simulations on the server.
     * 
     * @return FString The server run simulations address.
     */
    UFUNCTION(BlueprintCallable, Category = "Server Management")
    FString GetServerRunSimulationsAddress();

    /**
     * @brief Processes the response data for the reached server check.
     * 
     * This function processes the response data from the server to check if it is reachable.
     * 
     * @param InHttpComponent The HTTP component used for the request.
     * @param OutReached A boolean indicating if the server was reached.
     */
    UFUNCTION(BlueprintCallable, Category = "Server Management")
    void ProcessReachedResponseData(const UPT_HTTPComponent* InHttpComponent, bool& OutReached);

    /**
     * @brief Processes the response data for the run simulations request.
     * 
     * This function processes the response data from the server for the run simulations request.
     * 
     * @param InHttpComponent The HTTP component used for the request.
     * @param OutSuccess A boolean indicating if the request was successful.
     * @param OutMessage A message returned from the server.
     */
    UFUNCTION(BlueprintCallable, Category = "Server Management")
    void ProcessRunResponseData(const UPT_HTTPComponent* InHttpComponent, bool& OutSuccess, FString& OutMessage);
};