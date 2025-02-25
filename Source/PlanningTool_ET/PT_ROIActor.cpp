// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved


#include "PT_ROIActor.h"
#include "PT_JSONConverter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

APT_ROIActor::APT_ROIActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    this->PrimaryActorTick.bCanEverTick = true;

    this->ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
    this->RootComponent = this->ProceduralMesh;

    this->CurrentROISize = FVector(100.0f, 100.0f, 100.0f);
    this->CurrentROIPosition = FVector(0.0f, 0.0f, 0.0f);
    this->CurrentROIRotation = FRotator(0.0f, 0.0f, 0.0f);
}

void APT_ROIActor::BeginPlay()
{
    Super::BeginPlay();

    // Define initial vertices for a 100x100x100 box
    this->ResetVertexArrayToStandardSize();

    //this->VertexArray = {
    //    FVector(-15.000, -14.000, 52.000), FVector(15.000, -14.000, 52.000), FVector(15.000, 16.000, 52.000), FVector(-15.000, 16.000, 52.000),
    //    FVector(-15.000, -14.000, 82.000), FVector(15.000, -14.000, 82.000), FVector(15.000, 16.000, 82.000), FVector(-15.000, 16.000, 82.000)
    //};

    // Define the triangles (two per face)
    this->TriangleIndexArray.Append({ 0, 1, 2, 0, 2, 3 }); // Bottom face
    this->TriangleIndexArray.Append({ 4, 6, 5, 4, 7, 6 }); // Top face
    this->TriangleIndexArray.Append({ 0, 4, 1, 1, 4, 5 }); // Front face
    this->TriangleIndexArray.Append({ 1, 5, 2, 2, 5, 6 }); // Right face
    this->TriangleIndexArray.Append({ 2, 6, 3, 3, 6, 7 }); // Back face
    this->TriangleIndexArray.Append({ 3, 7, 0, 0, 7, 4 }); // Left face

    //this->CalculateNormals(this->VertexArray, this->TriangleIndexArray, this->NormalArray);
    this->CalculateNormalsManually();

    this->GenerateBoxMesh();

    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            InputSubsystem->AddMappingContext(this->IMC_PT_ROIActor, 1);
        }

        if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
        {
            EnhancedInputComponent->BindAction(this->IA_MoveBox, ETriggerEvent::Triggered, this, &APT_ROIActor::OnMoveROI);
        }
    }
}

void APT_ROIActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

TArray<FVector> APT_ROIActor::getROIBoundsToWorldSpace()
{
    TArray<FVector> TransformedVertices;

    // Iteriere durch alle Vertices und transformiere sie in den neuen Raum
    for (const FVector& Vertex : this->VertexArray)
    {
        FVector TransformedVertex = this->GetActorTransform().TransformPosition(Vertex);
        TransformedVertices.Add(TransformedVertex);
    }

    return TransformedVertices;
}

void APT_ROIActor::PrintCornerPoints()
{
    UE_LOG(LogTemp, Log, TEXT("================================================================"));
    for (const FVector& Vertex : this->VertexArray)
	{
        UE_LOG(LogTemp, Log, TEXT("Vertex: %s"), *Vertex.ToString());
	}
}

void APT_ROIActor::InitCurrentCameraManager()
{
    this->CameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
    
    if (!CameraManager)
    {
        UE_LOG(LogTemp, Error, TEXT("CameraManager not found!"));
    }
}

FString APT_ROIActor::ConvertRoiToJson(const FString& InPatientId, const FString& InRoiId, const TArray<FVector>& InVectorArray, const FVector& InCenterPosition)
{
    TSharedPtr<FJsonObject> MetadataJson = MakeShareable(new FJsonObject);
    MetadataJson->SetStringField(TEXT("Patient_ID"), InPatientId);
    MetadataJson->SetStringField(TEXT("ROI_ID"), InRoiId);
    TSharedPtr<FJsonObject> CenterPoint = UPT_JSONConverter::CreateJsonObjectFromVector(InCenterPosition);
    MetadataJson->SetObjectField(TEXT("CenterPosition"), CenterPoint);

    TArray<TSharedPtr<FJsonValue>> BoundsArray = UPT_JSONConverter::CreateJsonArrayFromVectorArray(InVectorArray);

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetObjectField(TEXT("Metadata"), MetadataJson);
    JsonObject->SetArrayField(TEXT("Bounds"), BoundsArray);

    return UPT_JSONConverter::SerializeJsonObjectToString(JsonObject);
}

void APT_ROIActor::GenerateBoxMesh()
{
    TArray<FVector2D> UV0;
    TArray<FLinearColor> VertexColors;
    TArray<FProcMeshTangent> Tangents;

    //this->CalculateNormals(this->VertexArray, this->TriangleIndexArray, this->NormalArray);
    this->CalculateNormalsManually();
    // Update the ProceduralMesh
    this->ProceduralMesh->CreateMeshSection_LinearColor(0, this->VertexArray, this->TriangleIndexArray, this->NormalArray, UV0, VertexColors, Tangents, true);
    this->ProceduralMesh->SetMaterial(0, this->Material);
    this->RoiChangedEvent.Broadcast();
}

void APT_ROIActor::ApplyTransformations(const FVector& NewSize, const FVector& NewPosition, const FRotator& NewRotation)
{
    //// Setzen der Standardwerte
    //FVector StandardSize(100.0f, 100.0f, 100.0f);
    //FVector StandardPosition(0.0f, 0.0f, 0.0f);
    //FRotator StandardRotation(0.0f, 0.0f, 0.0f);

    //// Berechnen der Differenz zwischen der Standardgröße und der neuen Größe
    //FVector DeltaSize = NewSize - StandardSize;

    //// Berechnen der Verschiebung, die auf alle Vertices angewendet werden soll, relativ zur Standardposition
    //FVector Translation = NewPosition - StandardPosition;

    //// Umwandlung der Rotationswinkel von Grad in Radiant und Erstellen der Rotationsmatrix basierend auf der neuen Rotation
    //FMatrix RotationMatrix = FRotationMatrix::Make(NewRotation);

    //// Zurücksetzen der VertexArray auf die Standardgröße, bevor die neuen Transformationen angewendet werden
    //ResetVertexArrayToStandardSize();

    //for (FVector& Vertex : this->VertexArray)
    //{
    //    // Anpassen der Vertex-Positionen basierend auf der Größenänderung
    //    Vertex.X = (Vertex.X / StandardSize.X) * NewSize.X;
    //    Vertex.Y = (Vertex.Y / StandardSize.Y) * NewSize.Y;
    //    Vertex.Z = (Vertex.Z / StandardSize.Z) * NewSize.Z;

    //    // Anwenden der Verschiebung
    //    Vertex += Translation;

    //    // Anwenden der Rotation
    //    Vertex = RotationMatrix.TransformPosition(Vertex - StandardPosition) + StandardPosition;
    //}

    //// Aktualisieren des Meshes mit den neuen Vertex-Positionen
    //this->GenerateBoxMesh();

        // Setzen der Standardwerte
    FVector StandardSize(100.0f, 100.0f, 100.0f);

    // Berechnen der Differenz zwischen der Standardgröße und der neuen Größe
    FVector DeltaSize = NewSize - StandardSize;

    // Zurücksetzen der VertexArray auf die Standardgröße, bevor die neuen Transformationen angewendet werden
    ResetVertexArrayToStandardSize();

    // Berechnen des neuen Mittelpunkts nach der Skalierung und vor der Translation
    FVector NewCenter = FVector(0.f, 0.f, 0.f);
    for (FVector& Vertex : this->VertexArray)
    {
        // Anpassen der Vertex-Positionen basierend auf der Größenänderung
        Vertex.X = (Vertex.X / StandardSize.X) * NewSize.X;
        Vertex.Y = (Vertex.Y / StandardSize.Y) * NewSize.Y;
        Vertex.Z = (Vertex.Z / StandardSize.Z) * NewSize.Z;

        NewCenter += Vertex;
    }
    NewCenter /= this->VertexArray.Num();

    // Berechnen der Verschiebung, die auf alle Vertices angewendet werden soll, relativ zum neuen Mittelpunkt
    FVector Translation = NewPosition - NewCenter;

    // Anwenden der Verschiebung
    for (FVector& Vertex : this->VertexArray)
    {
        Vertex += Translation;
    }

    // Umwandlung der Rotationswinkel von Grad in Radiant und Erstellen der Rotationsmatrix basierend auf der neuen Rotation
    FMatrix RotationMatrix = FRotationMatrix::Make(NewRotation);

    // Anwenden der Rotation um den neuen Mittelpunkt
    for (FVector& Vertex : this->VertexArray)
    {
        Vertex = RotationMatrix.TransformPosition(Vertex - NewPosition) + NewPosition;
    }

    // Aktualisieren des Meshes mit den neuen Vertex-Positionen
    this->GenerateBoxMesh();
}

void APT_ROIActor::ResetVertexArrayToStandardSize()
{
    // Setzen der VertexArray zurück auf die Standardgröße (100x100x100 Box)
    this->VertexArray = {
        FVector(-50, -50, -50), FVector(50, -50, -50), FVector(50, 50, -50), FVector(-50, 50, -50),
        FVector(-50, -50, 50), FVector(50, -50, 50), FVector(50, 50, 50), FVector(-50, 50, 50)
    };
}

void APT_ROIActor::SetROISize(const float& InSizeX, const float& InSizeY, const float& InSizeZ)
{
    this->CurrentROISize = FVector(InSizeX, InSizeY, InSizeZ);
    ApplyTransformations(this->CurrentROISize, this->CurrentROIPosition, this->CurrentROIRotation);
}

void APT_ROIActor::SetROIPosition(const float& InPosX, const float& InPosY, const float& InPosZ)
{
    this->CurrentROIPosition = FVector(InPosX, InPosY, InPosZ);
    ApplyTransformations(this->CurrentROISize, this->CurrentROIPosition, this->CurrentROIRotation);
}

void APT_ROIActor::SetROIRotation(const float& InPitch, const float& InYaw, const float& InRoll)
{
    this->CurrentROIRotation = FRotator(InPitch, InYaw, InRoll);
    ApplyTransformations(this->CurrentROISize, this->CurrentROIPosition, this->CurrentROIRotation);
}

void APT_ROIActor::OnMoveROI(const FInputActionValue& Value)
{
    this->MoveROIPosition(Value.Get<FVector>());
}

void APT_ROIActor::MoveROIPosition(const FVector& InNewPosition)
{

    //if (!this->CameraManager) // Ensure CameraManager is not null
    //{
    //    UE_LOG(LogTemp, Error, TEXT("CameraManager is null in MoveROIPosition"));
    //    return; // Early return to avoid dereferencing null
    //}

    //// Berechnen der Bewegung des Objekts relativ zur Kamera
    //FVector CameraForward = this->CameraManager->GetCameraRotation().Vector();
    //// Corrected usage of CrossProduct
    //FVector CameraRight = FVector::CrossProduct(CameraForward, FVector::UpVector).GetSafeNormal();
    //FVector CameraUp = FVector::CrossProduct(CameraRight, CameraForward).GetSafeNormal();

    //// Verwenden Sie CameraForward und CameraRight für Ihre Berechnungen
    //FVector ObjectMovement = CameraForward * InNewPosition.Z + CameraRight * InNewPosition.X + CameraUp * InNewPosition.Y;

    // Aktualisieren der CurrentROIPosition basierend auf der berechneten Bewegung
    this->CurrentROIPosition += InNewPosition;

    this->VertexArray[0] += InNewPosition;
    this->VertexArray[1] += InNewPosition;
    this->VertexArray[2] += InNewPosition;
    this->VertexArray[3] += InNewPosition;
    this->VertexArray[4] += InNewPosition;
    this->VertexArray[5] += InNewPosition;
    this->VertexArray[6] += InNewPosition;
    this->VertexArray[7] += InNewPosition;

    this->GenerateBoxMesh();
}


TArray<FVector> APT_ROIActor::GetROIBoundsToWorldSpaceRelativeTo(AActor* OtherActor)
{
    TArray<FVector> TransformedVertices;

    // Iterate through all vertices and transform them to the new space
    for (const FVector& Vertex : this->VertexArray)
    {
        FVector TransformedVertex = this->GetActorTransform().TransformPosition(Vertex);
        TransformedVertex -= OtherActor->GetActorLocation();  // Make coordinates relative to OtherActor
        TransformedVertices.Add(TransformedVertex);
    }

    return TransformedVertices;
}

void APT_ROIActor::CalculateNormalsManually()
{
    // Initialisieren des NormalArray mit Nullvektoren der gleichen Größe wie VertexArray
    this->NormalArray.Init(FVector(0.0f, 0.0f, 0.0f), this->VertexArray.Num());

    // Sicherstellen, dass die Anzahl der Indizes durch 3 teilbar ist
    if (this->TriangleIndexArray.Num() % 3 != 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("TriangleIndexArray hat keine gültige Anzahl von Indizes."));
        return;
    }

    // Durchlaufen jedes Dreiecks und Berechnen der Normalen
    for (int32 i = 0; i < this->TriangleIndexArray.Num(); i += 3)
    {
        // Holen der Indizes der Eckpunkte des Dreiecks
        int32 Index0 = this->TriangleIndexArray[i];
        int32 Index1 = this->TriangleIndexArray[i + 1];
        int32 Index2 = this->TriangleIndexArray[i + 2];

        // Holen der Eckpunkte des Dreiecks
        FVector Vertex0 = this->VertexArray[Index0];
        FVector Vertex1 = this->VertexArray[Index1];
        FVector Vertex2 = this->VertexArray[Index2];

        // Berechnen der Vektoren der Dreiecksseiten
        FVector Edge1 = Vertex0 - Vertex1;
        FVector Edge2 = Vertex0 - Vertex2;

        // Berechnen der Normalen durch das Kreuzprodukt der Kanten
        FVector Normal = FVector::CrossProduct(Edge1, Edge2);
        if (Normal.IsZero())
        {
            UE_LOG(LogTemp, Warning, TEXT("Normal is zero!"));
        }

        Normal.Normalize();

        // Akkumulieren der Normalen für jedes Eckpunkt des Dreiecks
        this->NormalArray[Index0] -= Normal;
        this->NormalArray[Index1] -= Normal;
        this->NormalArray[Index2] -= Normal;
    }

    // Normalisieren der akkumulierten Normalen für jedes Vertex
    for (FVector& Normal : this->NormalArray)
    {
        Normal.Normalize();
    }
}
