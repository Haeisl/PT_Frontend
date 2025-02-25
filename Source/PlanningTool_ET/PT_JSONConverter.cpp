// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved


#include "PT_JSONConverter.h"

UPT_JSONConverter::UPT_JSONConverter()
{
}

UPT_JSONConverter::~UPT_JSONConverter()
{
}

void UPT_JSONConverter::ConvertJSONResponseBodyToVectorArray(const UPT_HTTPComponent* InHTTPComponent, const FString& InArrayFieldName, TArray<FVector>& OutVectorArray)
{
	TSharedPtr<FJsonObject> ResponseObject = InHTTPComponent->GetResponseObject();
	UPT_JSONConverter::ConvertJSONObjectToVectorArray(&ResponseObject, InArrayFieldName, OutVectorArray);
}

void UPT_JSONConverter::ConvertJSONObjectToVectorArray(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InArrayFieldName, TArray<FVector>& OutVectorArray)
{
	const TArray<TSharedPtr<FJsonValue>>* JsonValueArrayPtr;
	OutVectorArray.Empty();

	if (InJsonObjectPtr->Get()->TryGetArrayField(InArrayFieldName, JsonValueArrayPtr))
	{
		for (auto& JsonValuePtr : *JsonValueArrayPtr)
		{
			auto& JsonVectorArray = JsonValuePtr->AsArray();

			FVector NewVector;

			NewVector.X = JsonVectorArray[0]->AsNumber();
			NewVector.Y = JsonVectorArray[1]->AsNumber();
			NewVector.Z = JsonVectorArray[2]->AsNumber();

			OutVectorArray.Add(NewVector);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_JSONConverter::ConvertJSONObjectToVectorArray] Field %s not found."), *InArrayFieldName);
	}
}

void UPT_JSONConverter::ConvertJSONResponseBodyToStringArray(const UPT_HTTPComponent* InHTTPComponent, const FString& InArrayFieldName, TArray<FString>& OutStringArray)
{
	TSharedPtr<FJsonObject> ResponseObject = InHTTPComponent->GetResponseObject();
	UPT_JSONConverter::ConvertJSONObjectToStringArray(&ResponseObject, InArrayFieldName, OutStringArray);
}

void UPT_JSONConverter::ConvertJSONObjectToStringArray(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InArrayFieldName, TArray<FString>& OutStringArray)
{
	const TArray<TSharedPtr<FJsonValue>>* JsonValueArrayPtr;
	OutStringArray.Empty();

	if (InJsonObjectPtr->Get()->TryGetArrayField(InArrayFieldName, JsonValueArrayPtr))
	{
		for (auto& JsonValuePtr : *JsonValueArrayPtr)
		{
			OutStringArray.Add(JsonValuePtr->AsString());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_JSONConverter::ConvertJSONObjectToStringArray] Field %s not found."), *InArrayFieldName);
	}
}

void UPT_JSONConverter::ConvertJSONResponseBodyToColorArray(const UPT_HTTPComponent* InHTTPComponent, const FString& InArrayFieldName, TArray<FLinearColor>& OutColorArray)
{
	TSharedPtr<FJsonObject> ResponseObject = InHTTPComponent->GetResponseObject();
	UPT_JSONConverter::ConvertJSONObjectToColorArray(&ResponseObject, InArrayFieldName, OutColorArray);
}

void UPT_JSONConverter::ConvertJSONObjectToColorArray(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InArrayFieldName, TArray<FLinearColor>& OutColorArray)
{
	const TArray<TSharedPtr<FJsonValue>>* JsonValueArrayPtr;
	OutColorArray.Empty();

	if (InJsonObjectPtr->Get()->TryGetArrayField(InArrayFieldName, JsonValueArrayPtr))
	{
		for (auto JsonValuePtr : *JsonValueArrayPtr)
		{
			auto JsonColorValues = JsonValuePtr->AsArray();

			OutColorArray.Add(FLinearColor(JsonColorValues[0]->AsNumber(), JsonColorValues[1]->AsNumber(), JsonColorValues[2]->AsNumber()));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_JSONConverterComponent::ConvertJSONObjectToVertexColorArray] Field %s not found!"), *InArrayFieldName);
	}
}

void UPT_JSONConverter::ConvertJSONResponseBodyToTriangleIndexArray(const UPT_HTTPComponent* InHTTPComponent, const FString& InArrayFieldName, TArray<int32>& OutTriangleIndexArray)
{
	TSharedPtr<FJsonObject> ResponseObject = InHTTPComponent->GetResponseObject();
	UPT_JSONConverter::ConvertJSONObjectToTriangleIndexArray(&ResponseObject, InArrayFieldName, OutTriangleIndexArray);
}

void UPT_JSONConverter::ConvertJSONObjectToTriangleIndexArray(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InArrayFieldName, TArray<int32>& OutTriangleIndexArray)
{
	const TArray<TSharedPtr<FJsonValue>>* JsonValueArrayPtr;
	OutTriangleIndexArray.Empty();

	if (InJsonObjectPtr->Get()->TryGetArrayField(InArrayFieldName, JsonValueArrayPtr))
	{
		for (auto JsonValuePtr : *JsonValueArrayPtr)
		{
			auto JsonTriangleValues = JsonValuePtr->AsArray();

			OutTriangleIndexArray.Add(JsonTriangleValues[0]->AsNumber());
			OutTriangleIndexArray.Add(JsonTriangleValues[1]->AsNumber());
			OutTriangleIndexArray.Add(JsonTriangleValues[2]->AsNumber());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_JSONConverter::ConvertJSONBodyToTriangleIndexArray] Field %s not found!"), *InArrayFieldName);
	}
}

void UPT_JSONConverter::ConvertJSONResponseBodyToTetraArray(const UPT_HTTPComponent* InHTTPComponent, const FString& InArrayFieldName, TArray<FPT_TetraData>& OutTetraDataArray)
{
	TSharedPtr<FJsonObject> ResponseObject = InHTTPComponent->GetResponseObject();
	UPT_JSONConverter::ConvertJSONObjectToTetraArray(&ResponseObject, InArrayFieldName, OutTetraDataArray);
}

void UPT_JSONConverter::ConvertJSONObjectToTetraArray(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InArrayFieldName, TArray<FPT_TetraData>& OutTetraDataArray)
{
	const TArray<TSharedPtr<FJsonValue>>* JsonValueArrayPtr;
	OutTetraDataArray.Empty();

	if (InJsonObjectPtr->Get()->TryGetArrayField(InArrayFieldName, JsonValueArrayPtr))
	{
		for (auto JsonValuePtr : *JsonValueArrayPtr)
		{
			auto JsonTetraValues = JsonValuePtr->AsArray();

			FPT_TetraData TetraData = FPT_TetraData();

			TetraData.A = JsonTetraValues[0]->AsNumber();
			TetraData.B = JsonTetraValues[1]->AsNumber();
			TetraData.C = JsonTetraValues[2]->AsNumber();
			TetraData.D = JsonTetraValues[3]->AsNumber();

			TetraData.Tag = InArrayFieldName;
			TetraData.Index = OutTetraDataArray.Num();

			OutTetraDataArray.Add(TetraData);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_JSONConverter::ConvertJSONObjectToTetraIndexArray] Field %s not found!"), *InArrayFieldName);
	}
}

void UPT_JSONConverter::ConvertJSONResponseBodyToDoubleArray(const UPT_HTTPComponent* InHTTPComponent, const FString& InArrayFieldName, TArray<double>& OutDoubleArray)
{
	TSharedPtr<FJsonObject> ResponseObject = InHTTPComponent->GetResponseObject();
	UPT_JSONConverter::ConvertJSONObjectToDoubleArray(&ResponseObject, InArrayFieldName, OutDoubleArray);
}

void UPT_JSONConverter::ConvertJSONObjectToDoubleArray(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InArrayFieldName, TArray<double>& OutDoubleArray)
{
	const TArray<TSharedPtr<FJsonValue>>* JsonValueArrayPtr;
	OutDoubleArray.Empty();

	if (InJsonObjectPtr->Get()->TryGetArrayField(InArrayFieldName, JsonValueArrayPtr))
	{
		for (auto JsonValuePtr : *JsonValueArrayPtr)
		{
			OutDoubleArray.Add(JsonValuePtr->AsNumber());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_JSONConverter::ConvertJSONObjectToDoubleArray] FieldName %s does not exist!"), *InArrayFieldName);
	}
}

void UPT_JSONConverter::ConvertJSONResponseBodyToIntegerArray(const UPT_HTTPComponent* InHTTPComponent, const FString& InArrayFieldName, TArray<int32>& OutIntegerArray)
{
	TSharedPtr<FJsonObject> ResponseObject = InHTTPComponent->GetResponseObject();
	UPT_JSONConverter::ConvertJSONObjectToIntegerArray(&ResponseObject, InArrayFieldName, OutIntegerArray);
}

void UPT_JSONConverter::ConvertJSONObjectToIntegerArray(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InArrayFieldName, TArray<int32>& OutIntegerArray, const bool& bPrintErrorMessage)
{
	const TArray<TSharedPtr<FJsonValue>>* JsonValueArrayPtr;
	OutIntegerArray.Empty();

	if (InJsonObjectPtr->Get()->TryGetArrayField(InArrayFieldName, JsonValueArrayPtr))
	{
		for (auto JsonValuePtr : *JsonValueArrayPtr)
		{
			OutIntegerArray.Add(JsonValuePtr->AsNumber());
		}
	}
	else
	{
		if (bPrintErrorMessage)
		{
			UE_LOG(LogTemp, Error, TEXT("[UPT_JSONConverter::ConvertJSONObjectToIntegerArray] FieldName %s does not exist!"), *InArrayFieldName);
		}
	}
}

void UPT_JSONConverter::ConvertJSONToDouble(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InFieldName, double& OutNumber)
{
	OutNumber = -1.0;
	if (!InJsonObjectPtr->Get()->TryGetNumberField(InFieldName, OutNumber))
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_JSONConverter::ConvertJSONToDouble] Field %s not found."), *InFieldName);
	}
}

void UPT_JSONConverter::ConvertJSONToInteger(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InFieldName, int32& OutNumber)
{
	OutNumber = -1;
	if (!InJsonObjectPtr->Get()->TryGetNumberField(InFieldName, OutNumber))
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_JSONConverter::ConvertJSONToInteger] Field %s not found."), *InFieldName);
	}
}

void UPT_JSONConverter::ConvertJSONToString(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InFieldName, FString& OutString)
{
	OutString = "DEFAULT";
	if (!InJsonObjectPtr->Get()->TryGetStringField(InFieldName, OutString))
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_JSONConverter::ConvertJSONToInteger] Field %s not found."), *InFieldName);
	}
}

void UPT_JSONConverter::ConvertJSONResponseBodyToVector(const UPT_HTTPComponent* InHTTPComponent, const FString& InFieldName, FVector& OutVector)
{
	TSharedPtr<FJsonObject> ResponseObject = InHTTPComponent->GetResponseObject();
	UPT_JSONConverter::ConvertJSONObjectToVector(&ResponseObject, InFieldName, OutVector);
}

void UPT_JSONConverter::ConvertJSONObjectToVector(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InFieldName, FVector& OutVector)
{
	const TSharedPtr<FJsonObject>* VectorObject;
	if ((*InJsonObjectPtr)->TryGetObjectField(InFieldName, VectorObject))
	{;
		UPT_JSONConverter::ConvertJSONToDouble(VectorObject, TEXT("X"), OutVector.X);
		UPT_JSONConverter::ConvertJSONToDouble(VectorObject, TEXT("Y"), OutVector.Y);
		UPT_JSONConverter::ConvertJSONToDouble(VectorObject, TEXT("Z"), OutVector.Z);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_JSONConverter::ConvertJSONObjectToVector] Field %s not found."), *InFieldName);
	}
}

TSharedPtr<FJsonObject> UPT_JSONConverter::CreateJsonObjectFromVector(const FVector& InVector)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetNumberField(TEXT("X"), InVector.X);
	JsonObject->SetNumberField(TEXT("Y"), InVector.Y);
	JsonObject->SetNumberField(TEXT("Z"), InVector.Z);
	return JsonObject;
}

TArray<TSharedPtr<FJsonValue>> UPT_JSONConverter::CreateJsonArrayFromVectorArray(const TArray<FVector>& InVectorArray)
{
	TArray<TSharedPtr<FJsonValue>> JsonArray;
	for (const FVector& Vector : InVectorArray)
	{
		TArray<TSharedPtr<FJsonValue>> VectorJsonArray;
		VectorJsonArray.Add(MakeShareable(new FJsonValueNumber(Vector.X)));
		VectorJsonArray.Add(MakeShareable(new FJsonValueNumber(Vector.Y)));
		VectorJsonArray.Add(MakeShareable(new FJsonValueNumber(Vector.Z)));

		JsonArray.Add(MakeShareable(new FJsonValueArray(VectorJsonArray)));
	}
	return JsonArray;
}

TArray<TSharedPtr<FJsonValue>> UPT_JSONConverter::CreateJsonArrayFromDoubleArray(const TArray<double>& InDoubleArray)
{
	TArray<TSharedPtr<FJsonValue>> JsonArray;
	for (const double& value : InDoubleArray)
	{
		JsonArray.Add(MakeShareable(new FJsonValueNumber(value)));
	}
	return JsonArray;
}

FString UPT_JSONConverter::SerializeJsonObjectToString(const TSharedPtr<FJsonObject>& InJsonObject)
{
	FString OutputString;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(InJsonObject.ToSharedRef(), JsonWriter);
	return OutputString;
}
