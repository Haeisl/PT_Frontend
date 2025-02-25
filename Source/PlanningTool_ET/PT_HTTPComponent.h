// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved
// Modifications (C) 2025 David Hasse - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PT_StructContainer.h"
#include "Http.h"
#include "Json.h"
#include "PT_HTTPComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHttpCallbackEventDelegate);

/**
 * @class UPT_HTTPComponent
 * @brief A component for handling HTTP requests and responses in Unreal Engine.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PLANNINGTOOL_ET_API UPT_HTTPComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/**
	 * @brief Sets default values for this component's properties.
	 */
	UPT_HTTPComponent();

protected:
	/**
	 * @brief Called when the game starts.
	 */
	virtual void BeginPlay() override;

public:
	/**
	 * @brief Called every frame.
	 * @param DeltaTime The time since the last tick.
	 * @param TickType The type of tick this is.
	 * @param ThisTickFunction The tick function that is being executed.
	 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @brief Checks the server status at the specified address.
	 * @param InAddress The address of the server to check.
	 */
	UFUNCTION(BlueprintCallable, Category = "Server Status")
	void CheckServerStatus(const FString& InAddress);

	/**
	 * @brief Sends simulation data to the server.
	 * @param InAddress The address of the server.
	 * @param PatientID The ID of the patient.
	 * @param ConfigID The ID of the configuration.
	 * @param ROIID The ID of the region of interest.
	 */
	UFUNCTION(BlueprintCallable, Category = "Run Simulation")
	void SendRunSimulationData(const FString& InAddress, const FString& PatientID, const FString& ConfigID, const FString& ROIID);

	/**
	 * @brief A delegate that is called when an HTTP request is completed.
	 */
	UPROPERTY(BlueprintAssignable, Category = "PT_API_EVENT")
	FHttpCallbackEventDelegate HttpCallbackEvent;

	/**
	 * @brief Sends an HTTP request to the specified address using the specified HTTP verb.
	 * @param InAddress The URL to send the request to.
	 * @param InVerb The HTTP verb to use for the request (e.g., "GET", "POST").
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_API_CALL")
	void CallApi(const FString& InAddress, const FString& InVerb);

	/**
	 * @brief Sends an HTTP request to the specified address using the specified HTTP verb and expects a compressed response.
	 * @param InAddress The URL to send the request to.
	 * @param InVerb The HTTP verb to use for the request (e.g., "GET", "POST").
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_API_CALL")
	void CallApiWithCompressedResponse(const FString& InAddress, const FString& InVerb);

	/**
	 * @brief Sends an HTTP request with a JSON body to the specified address using the specified HTTP verb.
	 * @param InAddress The URL to send the request to.
	 * @param InVerb The HTTP verb to use for the request (e.g., "GET", "POST").
	 * @param InJsonString The JSON body to include in the request.
	 */
	UFUNCTION(BlueprintCallable, Category = "PT_API_CALL")
	void CallApiWithJSONBody(const FString& InAddress, const FString& InVerb, const FString& InJsonString);

	/**
	 * @brief Returns the JSON object received from the last HTTP request.
	 * @return The JSON object from the last HTTP request.
	 */
	TSharedPtr<FJsonObject> GetResponseObject() const;

private:

	/**
	 * @brief Handles the response for the CheckServerStatus request.
	 * @param Request The original HTTP request.
	 * @param Response The HTTP response.
	 * @param bConnectedSuccesfully Whether the request was successful.
	 */
	void OnCheckServerStatusResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully);

	/**
	 * @brief Handles the response received from an HTTP request.
	 * @param Request The original HTTP request.
	 * @param Response The HTTP response.
	 * @param bConnectedSuccesfully Whether the request was successful.
	 */
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully);

	/**
	 * @brief Handles the response received from an HTTP request that returned compressed data.
	 * @param Request The original HTTP request.
	 * @param Response The HTTP response.
	 * @param bConnectedSuccesfully Whether the request was successful.
	 */
	void OnResponseReceivedWithDecompressing(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully);

	/**
	 * @brief A shared pointer to a JSON object that stores the response from the last HTTP request.
	 */
	TSharedPtr<FJsonObject> ResponseObj;
};
