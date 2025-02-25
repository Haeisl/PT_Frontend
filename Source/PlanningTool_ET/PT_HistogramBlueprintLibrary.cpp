#include "PT_HistogramBlueprintLibrary.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "HAL/PlatformProcess.h"
#include "Engine/Texture2D.h"
#include "Misc/Paths.h"
#include "Modules/ModuleManager.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Engine/Texture2D.h"
#include "Kismet/KismetRenderingLibrary.h"


UTexture2D* UPT_HistogramBlueprintLibrary::CreateHistogramTexture(const TArray<double>& InData, const int32 NumBins, bool bLogScale, bool bConstrainXMin, float XMin, bool bConstrainXMax, float XMax, bool bGridLines)
{
    // Create a temporary CSV file with the data
    FString TempDirectory = FPaths::ProjectSavedDir();  // <Project>/Saved/
    FString DataFileName = TEXT("HistogramData.csv");
    FString DataFilePath = FPaths::Combine(TempDirectory, DataFileName);

    UE_LOG(LogTemp, Log, TEXT("[CreateHistogramTexture] InData length = %d"), InData.Num());

    // Convert double array to CSV lines
    FString CSVContent;
    for (double Value : InData)
    {
        CSVContent += FString::SanitizeFloat(Value) + TEXT("\n");
    }

    // Write CSV to disk
    if (!FFileHelper::SaveStringToFile(CSVContent, *DataFilePath))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to write CSV data to %s"), *DataFilePath);
        return nullptr;
    }

    // Define the Python script path and arguments
    FString PythonScriptPath = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("Scripts"), TEXT("GenerateHistogram.py"));
    FString OutputImageName = TEXT("histogram_output.png");
    FString OutputImagePath = FPaths::Combine(TempDirectory, OutputImageName);

    // We'll pass the data file path, the output path, the number of bins, log scale, x_min, x_max, and grid lines to the python script
    FString Arguments = FString::Printf(TEXT("\"%s\" \"%s\" \"%s\" %d %s %s %f %s %f %s"),
        *PythonScriptPath,
        *DataFilePath,
        *OutputImagePath,
        NumBins,
        bLogScale ? TEXT("true") : TEXT("false"),
        bConstrainXMin ? TEXT("true") : TEXT("false"),
        XMin,
        bConstrainXMax ? TEXT("true") : TEXT("false"),
        XMax,
        bGridLines ? TEXT("true") : TEXT("false"));

    // Spawn Python process
    FString PythonExe = TEXT("python");

    // Create the process
    FProcHandle ProcHandle = FPlatformProcess::CreateProc(
        *PythonExe,
        *Arguments,
        true,           // bLaunchDetached
        false,          // bLaunchHidden
        false,          // bLaunchReallyHidden
        nullptr,        // OutProcessID
        0,              // PriorityModifier
        nullptr,        // OptionalWorkingDirectory
        nullptr         // PipeWrite
    );

    if (!ProcHandle.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to start Python process with command: %s %s"), *PythonExe, *Arguments);
        return nullptr;
    }

    // Wait until the python script finishes
    FPlatformProcess::WaitForProc(ProcHandle);
    FPlatformProcess::CloseProc(ProcHandle);

    // Load the resulting PNG image
    TArray<uint8> RawFileData;
    if (!FFileHelper::LoadFileToArray(RawFileData, *OutputImagePath))
    {
        UE_LOG(LogTemp, Error, TEXT("Could not load output image file: %s"), *OutputImagePath);
        return nullptr;
    }

    // Convert the PNG byte array into a UTexture2D
    IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
    TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);

    if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
    {
        TArray<uint8> UncompressedRGBA;
        if (ImageWrapper->GetRaw(ERGBFormat::RGBA, 8, UncompressedRGBA))
        {
            // Create the texture
            UTexture2D* Texture = UTexture2D::CreateTransient(
                ImageWrapper->GetWidth(),
                ImageWrapper->GetHeight(),
                PF_B8G8R8A8
            );
            if (!Texture) return nullptr;

            // Lock the texture so we can write to it
            void* TextureData = Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
            FMemory::Memcpy(TextureData, UncompressedRGBA.GetData(), UncompressedRGBA.Num());
            Texture->GetPlatformData()->Mips[0].BulkData.Unlock();

            // Update the rendering resource from data.
            Texture->UpdateResource();

            return Texture;
        }
    }

    UE_LOG(LogTemp, Error, TEXT("Failed to convert raw image data into texture!"));
    return nullptr;
}
