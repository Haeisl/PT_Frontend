#include "PT_MyGameInstance.h"

void UPT_MyGameInstance::Init()
{
	Super::Init();

	HTTPComponent = NewObject<UPT_HTTPComponent>(this, UPT_HTTPComponent::StaticClass());
	HTTPComponent->RegisterComponent();
}

void UPT_MyGameInstance::SetInterpolatedData(const TArray<double>& InData)
{
	UE_LOG(LogTemp, Log, TEXT("Called Set Interpolated Data! Interpolated Data size = %f"), this->InterpolatedData.Num());
	for (double Data : InData) {
		if (Data > 0.0) {
			this->InterpolatedData.Add(Data);
		}
	}
}
TArray<double> UPT_MyGameInstance::GetInterpolatedData()
{
	UE_LOG(LogTemp, Log, TEXT("Called Get Interpolated Data! Interpolated Data size = %f"), this->InterpolatedData.Num());
	return this->InterpolatedData;
};
