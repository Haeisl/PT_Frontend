// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved
// Modifications (C) 2025 David Hasse - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PT_HTTPComponent.h"
#include "PT_JSONConverter.generated.h"

/**
 * @class UPT_JSONConverter
 * @brief A utility class for converting JSON data to various Unreal Engine data types.
 */
UCLASS()
class PLANNINGTOOL_ET_API UPT_JSONConverter : public UObject
{
    GENERATED_BODY()

public:

    /**
     * @brief Default constructor.
     */
    UPT_JSONConverter();

    /**
     * @brief Destructor.
     */
    ~UPT_JSONConverter();

    /**
     * @brief Converts a JSON response body to an array of FVector.
     * @param InHTTPComponent A pointer to the UPT_HTTPComponent that contains the HTTP response.
     * @param InArrayFieldName The name of the field in the JSON object to convert.
     * @param OutVectorArray [out] An array of FVector representing the specified field in the JSON object.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_JSON")
    static void ConvertJSONResponseBodyToVectorArray(const UPT_HTTPComponent* InHTTPComponent, const FString& InArrayFieldName, TArray<FVector>& OutVectorArray);

    /**
     * @brief Converts a JSON object to an array of FVector.
     * @param InJsonObjectPtr A pointer to the JSON object to convert.
     * @param InArrayFieldName The name of the field to get from the JSON object.
     * @param OutVectorArray [out] A TArray of FVector representing the converted JSON object.
     */
    static void ConvertJSONObjectToVectorArray(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InArrayFieldName, TArray<FVector>& OutVectorArray);

    /**
    * @brief Converts a JSON response body to an array of FString.
    * @param InHTTPComponent A pointer to the UPT_HTTPComponent that contains the HTTP response.
    * @param InArrayFieldName The name of the field in the JSON object to convert.
    * @param OutStringArray [out] An array of FString representing the specified field in the JSON object.
    */
    UFUNCTION(BlueprintCallable, Category = "PT_JSON")
    static void ConvertJSONResponseBodyToStringArray(const UPT_HTTPComponent* InHTTPComponent, const FString& InArrayFieldName, TArray<FString>& OutStringArray);

    /**
    * @brief Converts a JSON object to an array of FString.
    * @param InJsonObjectPtr A pointer to the JSON object to convert.
    * @param InArrayFieldName The name of the field to get from the JSON object.
    * @param OutStringArray [out] A TArray of FString representing the converted JSON object.
    */
    static void ConvertJSONObjectToStringArray(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InArrayFieldName, TArray<FString>& OutStringArray);

    /**
    * @brief Converts a JSON response body to an array of FLinearColor.
    * @param InHTTPComponent A pointer to the UPT_HTTPComponent that contains the HTTP response.
    * @param InArrayFieldName The name of the field in the JSON object to convert.
    * @param OutColorArray [out] An array of FLinearColor representing the specified field in the JSON object.
    */
    UFUNCTION(BlueprintCallable, Category = "PT_JSON")
    static void ConvertJSONResponseBodyToColorArray(const UPT_HTTPComponent* InHTTPComponent, const FString& InArrayFieldName, TArray<FLinearColor>& OutColorArray);

    /**
    * @brief Converts a JSON object to an array of FLinearColor.
    * @param InJsonObjectPtr A pointer to the JSON object to convert.
    * @param InArrayFieldName The name of the field to get from the JSON object.
    * @param OutColorArray [out] A TArray of FLinearColor representing the converted JSON object.
    */
    static void ConvertJSONObjectToColorArray(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InArrayFieldName, TArray<FLinearColor>& OutColorArray);

    /**
    * @brief Converts a JSON response body to an array of triangle indices.
    * @param InHTTPComponent A pointer to the UPT_HTTPComponent that contains the HTTP response.
    * @param InArrayFieldName The name of the field in the JSON object to convert.
    * @param OutTriangleIndexArray [out] An array of int32 representing the specified field in the JSON object.
    */
    UFUNCTION(BlueprintCallable, Category = "PT_JSON")
    static void ConvertJSONResponseBodyToTriangleIndexArray(const UPT_HTTPComponent* InHTTPComponent, const FString& InArrayFieldName, TArray<int32>& OutTriangleIndexArray);

    /**
    * @brief Converts a JSON object to an array of triangle indices.
    * @param InJsonObjectPtr A pointer to the JSON object to convert.
    * @param InArrayFieldName The name of the field to get from the JSON object.
    * @param OutTriangleIndexArray [out] A TArray of int32 representing the converted JSON object.
    */
    static void ConvertJSONObjectToTriangleIndexArray(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InArrayFieldName, TArray<int32>& OutTriangleIndexArray);

    /**
    * @brief Converts a JSON response body to an array of FPT_TetraData.
    * @param InHTTPComponent A pointer to the UPT_HTTPComponent that contains the HTTP response.
    * @param InArrayFieldName The name of the field in the JSON object to convert.
    * @param OutTetraDataArray [out] An array of FPT_TetraData representing the specified field in the JSON object.
    */
    UFUNCTION(BlueprintCallable, Category = "PT_JSON")
    static void ConvertJSONResponseBodyToTetraArray(const UPT_HTTPComponent* InHTTPComponent, const FString& InArrayFieldName, TArray<FPT_TetraData>& OutTetraDataArray);

    /**
    * @brief Converts a JSON object to an array of FPT_TetraData.
    * @param InJsonObjectPtr A pointer to the JSON object to convert.
    * @param InArrayFieldName The name of the field to get from the JSON object.
    * @param OutTetraDataArray [out] A TArray of FPT_TetraData representing the converted JSON object.
    */
    static void ConvertJSONObjectToTetraArray(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InArrayFieldName, TArray<FPT_TetraData>& OutTetraDataArray);

    /**
     * @brief Converts a JSON response body to an array of doubles.
     * @param InHTTPComponent A pointer to the UPT_HTTPComponent that contains the HTTP response.
     * @param InArrayFieldName The name of the field in the JSON object to convert.
     * @param OutDoubleArray [out] An array of doubles representing the specified field in the JSON object.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_JSON")
    static void ConvertJSONResponseBodyToDoubleArray(const UPT_HTTPComponent* InHTTPComponent, const FString& InArrayFieldName, TArray<double>& OutDoubleArray);

    /**
     * @brief Converts a JSON object to an array of doubles.
     * @param InJsonObjectPtr The JSON object to convert.
     * @param InArrayFieldName The name of the field in the JSON object to convert.
     * @param OutDoubleArray [out] An array of doubles representing the specified field in the JSON object.
     */
    static void ConvertJSONObjectToDoubleArray(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InArrayFieldName, TArray<double>& OutDoubleArray);

    /**
     * @brief Converts a JSON response body to an array of integers.
     * @param InHTTPComponent A pointer to the UPT_HTTPComponent that contains the HTTP response.
     * @param InArrayFieldName The name of the field in the JSON object to convert.
     * @param OutIntegerArray [out] An array of integers representing the specified field in the JSON object.
     */
    UFUNCTION(BlueprintCallable, Category = "PT_JSON")
    static void ConvertJSONResponseBodyToIntegerArray(const UPT_HTTPComponent* InHTTPComponent, const FString& InArrayFieldName, TArray<int32>& OutIntegerArray);

    /**
     * @brief Converts a JSON object to an array of integers.
     * @param InJsonObjectPtr The JSON object to convert.
     * @param InArrayFieldName The name of the field in the JSON object to convert.
     * @param OutIntegerArray [out] An array of integers representing the specified field in the JSON object.
     * @param bPrintErrorMessage Whether to print an error message if the field is not found.
     */
    static void ConvertJSONObjectToIntegerArray(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InArrayFieldName, TArray<int32>& OutIntegerArray, const bool& bPrintErrorMessage = true);

    /**
     * @brief Converts a JSON object to a double.
     * @param InJsonObjectPtr A pointer to the JSON object to convert.
     * @param InFieldName The name of the field to get from the JSON object.
     * @param OutNumber [out] The double value representing the specified field in the JSON object.
     */
    static void ConvertJSONToDouble(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InFieldName, double& OutNumber);

    /**
     * @brief Converts a JSON object to an integer.
     * @param InJsonObjectPtr A pointer to the JSON object to convert.
     * @param InFieldName The name of the field to get from the JSON object.
     * @param OutNumber [out] The integer value representing the specified field in the JSON object.
     */
    static void ConvertJSONToInteger(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InFieldName, int32& OutNumber);

    /**
     * @brief Converts a JSON object to a string.
     * @param InJsonObjectPtr A pointer to the JSON object to convert.
     * @param InFieldName The name of the field to get from the JSON object.
     * @param OutString [out] The string value representing the specified field in the JSON object.
     */
    static void ConvertJSONToString(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const FString& InFieldName, FString& OutString);

    /**
     * @brief Converts a JSON response body to a FVector.
     * @param InHTTPComponent A pointer to the UPT_HTTPComponent that contains the HTTP response.
     * @param InFieldName The name of the field in the JSON object to convert.
     * @param OutVector [out] The FVector representing the specified field in the JSON object.
     */
    static void ConvertJSONResponseBodyToVector(const UPT_HTTPComponent* InHTTPComponent, const FString& InFieldName, FVector& OutVector);

    /**
     * @brief Converts a JSON object to a FVector.
     * @param jsonObj A pointer to the JSON object to convert.
     * @param InFieldName The name of the field to get from the JSON object.
     * @param OutVector [out] The FVector representing the specified field in the JSON object.
     */
    static void ConvertJSONObjectToVector(const TSharedPtr<FJsonObject>* jsonObj, const FString& InFieldName, FVector& OutVector);

    /**
     * @brief Converts a FVector to a JSON object.
     * @param InVector The FVector to convert.
     * @return A JSON object representing the FVector.
     */
    static TSharedPtr<FJsonObject> CreateJsonObjectFromVector(const FVector& InVector);

    /**
     * @brief Converts an array of FVectors to a JSON array.
     * @param InVectorArray The array of FVectors to convert.
     * @return A JSON array where each element is a JSON array representing a FVector from the input array.
     */
    static TArray<TSharedPtr<FJsonValue>> CreateJsonArrayFromVectorArray(const TArray<FVector>& InVectorArray);

    /**
     * @brief Converts an array of doubles to a JSON array.
     * @param InDoubleArray The array of doubles to convert.
     * @return A JSON array where each element is a JSON value representing a double from the input array.
     */
    static TArray<TSharedPtr<FJsonValue>> CreateJsonArrayFromDoubleArray(const TArray<double>& InDoubleArray);

    /**
     * @brief Converts a JSON object to a string.
     * @param InJsonObject The JSON object to serialize.
     * @return The serialized JSON object as a string.
     */
    static FString SerializeJsonObjectToString(const TSharedPtr<FJsonObject>& InJsonObject);

};
