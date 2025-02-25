#include "ManageServerWidget.h"
#include "PT_ConfigManager.h"


void UManageServerWidget::SaveServerAddress(const FString& IPAddress, const FString& Port)
{
    // Construct the new address
    FString NewAddress = FString::Printf(TEXT("http://%s:%s"), *IPAddress, *Port);

    // Update the server address in PT_ConfigManager
    UPT_ConfigManager::SetServerAddress(NewAddress);

    // Log for debugging
    UE_LOG(LogTemp, Log, TEXT("Server address updated to: %s"), *NewAddress);
}

FString UManageServerWidget::GetServerReachedAddress()
{
	return UPT_ConfigManager::GetReachedAddress();
}

FString UManageServerWidget::GetServerRunSimulationsAddress()
{
    return UPT_ConfigManager::GetRunSimulationsAddress();
}

void UManageServerWidget::ProcessReachedResponseData(const UPT_HTTPComponent* InHttpComponent, bool& OutReached)
{
    if (!InHttpComponent || !InHttpComponent->GetResponseObject().IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid HTTP Component or Response Object"));
        OutReached = false; // Ensure a failure state
        return;
    }

    // Try to get the "status" field from the JSON response
    if (InHttpComponent->GetResponseObject()->TryGetBoolField(TEXT("status"), OutReached))
    {
        if (OutReached)
        {
            UE_LOG(LogTemp, Display, TEXT("Server reached successfully"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Server unreachable"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to parse 'status' from response object"));
        OutReached = false; // Set default failure state
    }
}

void UManageServerWidget::ProcessRunResponseData(const UPT_HTTPComponent* InHttpComponent, bool& OutSuccess, FString& OutMessage)
{
    if (!InHttpComponent || !InHttpComponent->GetResponseObject().IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid HTTP Component or Response Object"));
        OutSuccess = false;
        OutMessage = "No response from server.";
        return;
    }
    // Extract the "status" and "message" fields from the JSON response
    TSharedPtr<FJsonObject> ResponseObject = InHttpComponent->GetResponseObject();
    FString Status;

    if (ResponseObject->TryGetStringField(TEXT("status"), Status) && ResponseObject->TryGetStringField(TEXT("message"), OutMessage))
    {
        if (Status.Equals("success", ESearchCase::IgnoreCase))
        {
            OutSuccess = true;
            UE_LOG(LogTemp, Display, TEXT("Success: %s"), *OutMessage);
        }
        else if (Status.Equals("warning", ESearchCase::IgnoreCase))
        {
            OutSuccess = false;
            UE_LOG(LogTemp, Warning, TEXT("Warning: %s"), *OutMessage);
        }
        else {
            OutSuccess = false;
			UE_LOG(LogTemp, Error, TEXT("Error: %s"), *OutMessage);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to parse 'status' or 'message' from response object"));
        OutSuccess = false;
        OutMessage = "Unexpected response format.";
    }
}
