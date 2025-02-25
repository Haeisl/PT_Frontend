// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved


#include "PT_HTTPComponent.h"

// Sets default values for this component's properties
UPT_HTTPComponent::UPT_HTTPComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPT_HTTPComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPT_HTTPComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPT_HTTPComponent::CheckServerStatus(const FString& InAddress)
{
	// Create the HTTP request
	ResponseObj.Reset();
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();

	// Set the URL (use the server address + /reached)
	FString ServerURL = InAddress;
	Request->SetURL(ServerURL);

	// Set the HTTP method to GET
	Request->SetVerb("GET");

	// Bind a response callback
	Request->OnProcessRequestComplete().BindUObject(this, &UPT_HTTPComponent::OnCheckServerStatusResponse);

	// Send the request
	Request->ProcessRequest();
}

void UPT_HTTPComponent::SendRunSimulationData(const FString& InAddress, const FString& PatientID, const FString& ConfigID, const FString& ROIID) {
	FString FullAddress = InAddress + TEXT("/") + PatientID + TEXT("/") + ConfigID + TEXT("/") + ROIID;

	ResponseObj.Reset();

	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UPT_HTTPComponent::OnResponseReceived);

	Request->SetURL(FullAddress);
	Request->SetVerb("POST");
	Request->ProcessRequest();

	UE_LOG(LogTemp, Log, TEXT("[UPT_HTTPComponent::SendFormDataToServer] Sent request to %s with PatientID=%s, ConfigID=%s, ROIID=%s"), *InAddress, *PatientID, *ConfigID, *ROIID);
}

void UPT_HTTPComponent::CallApi(const FString& InAddress, const FString& InVerb)
{
	ResponseObj.Reset();
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UPT_HTTPComponent::OnResponseReceived);
	Request->SetURL(InAddress);
	Request->SetVerb(InVerb);
	Request->ProcessRequest();
	UE_LOG(LogTemp, Log, TEXT("[UPT_HTTPComponent::CallApi] Called... %s"), *InAddress);
}

void UPT_HTTPComponent::CallApiWithCompressedResponse(const FString& InAddress, const FString& InVerb)
{
	ResponseObj.Reset();
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UPT_HTTPComponent::OnResponseReceivedWithDecompressing);

	Request->SetURL(InAddress);
	Request->SetVerb(InVerb);
	Request->ProcessRequest();
	UE_LOG(LogTemp, Log, TEXT("[UPT_HTTPComponent::CallApiWithCompressedResponse] Called... %s"), *InAddress);
}

void UPT_HTTPComponent::CallApiWithJSONBody(const FString& InAddress, const FString& InVerb, const FString& InJsonString)
{
	ResponseObj.Reset();
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UPT_HTTPComponent::OnResponseReceived);
	Request->SetURL(InAddress);
	Request->SetVerb(InVerb);
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(InJsonString);

	Request->ProcessRequest();
	UE_LOG(LogTemp, Log, TEXT("[UPT_HTTPComponent::CallApiWithJSONBody] Called... %s"), *InAddress);
}

void UPT_HTTPComponent::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully)
{
	if (bConnectedSuccesfully)
	{
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		FJsonSerializer::Deserialize(Reader, ResponseObj);
		HttpCallbackEvent.Broadcast();
		//HttpCallbackEvent();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_HTTPComponent::OnResponseReceived] Not connected succesfully!"));
	}
}

void UPT_HTTPComponent::OnResponseReceivedWithDecompressing(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully)
{
	if (bConnectedSuccesfully)
	{
		// Dekomprimieren der erhaltenen Daten
		TArray<uint8> CompressedData = Response->GetContent();
		FString ContentLengthHeader = Response->GetHeader("Decompressed-Size");
		int32 SizeInBytesUncompressedData = FCString::Atoi(*ContentLengthHeader);
		TArray<uint8> UncompressedData;
		UncompressedData.SetNumZeroed(SizeInBytesUncompressedData);

		bool bDecompressionSuccessful = FCompression::UncompressMemory(NAME_Zlib, UncompressedData.GetData(), SizeInBytesUncompressedData, CompressedData.GetData(), CompressedData.Num());
		if (bDecompressionSuccessful)
		{
			ResponseObj.Reset();
			// Konvertiere Byte-Array in FString
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(UncompressedData.GetData()))));
			if (FJsonSerializer::Deserialize(Reader, ResponseObj))
			{
				HttpCallbackEvent.Broadcast();
				return;
			}
			UE_LOG(LogTemp, Error, TEXT("[UPT_HTTPComponent::OnResponseReceivedWithDecompressing] JSON Deserialization Error!"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[UPT_HTTPComponent::OnResponseReceivedWithDecompressing] Decompression Error!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_HTTPComponent::OnResponseReceivedWithDecompressing] Not connected succesfully!"));
	}
}

TSharedPtr<FJsonObject> UPT_HTTPComponent::GetResponseObject() const
{
	return ResponseObj;
}

void UPT_HTTPComponent::OnCheckServerStatusResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully)
{
	if (bConnectedSuccesfully && Response.IsValid() && Response->GetResponseCode() == 200)
	{
		// Parse the response JSON string into a JSON object
		FString ResponseContent = Response->GetContentAsString();
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(ResponseContent);

		if (FJsonSerializer::Deserialize(JsonReader, ResponseObj) && ResponseObj.IsValid())
		{
			// Log the response for debugging
			UE_LOG(LogTemp, Log, TEXT("Response received: %s"), *ResponseContent);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON response"));
			ResponseObj.Reset(); // Clear the response object on failure
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HTTP request failed or server unreachable"));
		ResponseObj.Reset(); // Clear the response object on failure
	}
}

