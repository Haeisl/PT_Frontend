// Copyright (C) 2024 Jan-Vincent Mock - All Rights Reserved


#include "PT_SimulationComponent.h"
#include "PT_ConfigManager.h"
#include "PT_JSONConverter.h"

// Sets default values for this component's properties
UPT_SimulationComponent::UPT_SimulationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPT_SimulationComponent::BeginPlay()
{
	Super::BeginPlay();

	this->InterpolatedMagnitudeDataPerTagArray.SetNumZeroed(UPT_ConfigManager::GetDataTagIndexArray().Num());
	this->InterpolatedVectorfieldDataPerTagArray.SetNumZeroed(UPT_ConfigManager::GetDataTagIndexArray().Num());
	this->DataColorArrayPerTag.SetNumZeroed(UPT_ConfigManager::GetDataTagIndexArray().Num());
	this->MeanMagnitudePerTag.SetNumZeroed(UPT_ConfigManager::GetDataTagIndexArray().Num());
	this->MeanVectorFieldPerTag.SetNumZeroed(UPT_ConfigManager::GetDataTagIndexArray().Num());

	// ...
	
}


// Called every frame
void UPT_SimulationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

#include "CoreMinimal.h"
#include "Algo/Sort.h" // For sorting the array

static const TArray<FLinearColor> PlasmaColormap = {
	FLinearColor(0.050383, 0.029803, 0.527975),
	FLinearColor(0.063536, 0.028426, 0.533124),
	FLinearColor(0.075353, 0.027206, 0.538007),
	FLinearColor(0.086222, 0.026125, 0.542658),
	FLinearColor(0.096379, 0.025165, 0.547103),
	FLinearColor(0.105980, 0.024309, 0.551368),
	FLinearColor(0.115124, 0.023556, 0.555468),
	FLinearColor(0.123903, 0.022878, 0.559423),
	FLinearColor(0.132381, 0.022258, 0.563250),
	FLinearColor(0.140603, 0.021687, 0.566959),
	FLinearColor(0.148607, 0.021154, 0.570562),
	FLinearColor(0.156421, 0.020651, 0.574065),
	FLinearColor(0.164070, 0.020171, 0.577478),
	FLinearColor(0.171574, 0.019706, 0.580806),
	FLinearColor(0.178950, 0.019252, 0.584054),
	FLinearColor(0.186213, 0.018803, 0.587228),
	FLinearColor(0.193374, 0.018354, 0.590330),
	FLinearColor(0.200445, 0.017902, 0.593364),
	FLinearColor(0.207435, 0.017442, 0.596333),
	FLinearColor(0.214350, 0.016973, 0.599239),
	FLinearColor(0.221197, 0.016497, 0.602083),
	FLinearColor(0.227983, 0.016007, 0.604867),
	FLinearColor(0.234715, 0.015502, 0.607592),
	FLinearColor(0.241396, 0.014979, 0.610259),
	FLinearColor(0.248032, 0.014439, 0.612868),
	FLinearColor(0.254627, 0.013882, 0.615419),
	FLinearColor(0.261183, 0.013308, 0.617911),
	FLinearColor(0.267703, 0.012716, 0.620346),
	FLinearColor(0.274191, 0.012109, 0.622722),
	FLinearColor(0.280648, 0.011488, 0.625038),
	FLinearColor(0.287076, 0.010855, 0.627295),
	FLinearColor(0.293478, 0.010213, 0.629490),
	FLinearColor(0.299855, 0.009561, 0.631624),
	FLinearColor(0.306210, 0.008902, 0.633694),
	FLinearColor(0.312543, 0.008239, 0.635700),
	FLinearColor(0.318856, 0.007576, 0.637640),
	FLinearColor(0.325150, 0.006915, 0.639512),
	FLinearColor(0.331426, 0.006261, 0.641316),
	FLinearColor(0.337683, 0.005618, 0.643049),
	FLinearColor(0.343925, 0.004991, 0.644710),
	FLinearColor(0.350150, 0.004382, 0.646298),
	FLinearColor(0.356359, 0.003798, 0.647810),
	FLinearColor(0.362553, 0.003243, 0.649245),
	FLinearColor(0.368733, 0.002724, 0.650601),
	FLinearColor(0.374897, 0.002245, 0.651876),
	FLinearColor(0.381047, 0.001814, 0.653068),
	FLinearColor(0.387183, 0.001434, 0.654177),
	FLinearColor(0.393304, 0.001114, 0.655199),
	FLinearColor(0.399411, 0.000859, 0.656133),
	FLinearColor(0.405503, 0.000678, 0.656977),
	FLinearColor(0.411580, 0.000577, 0.657730),
	FLinearColor(0.417642, 0.000564, 0.658390),
	FLinearColor(0.423689, 0.000646, 0.658956),
	FLinearColor(0.429719, 0.000831, 0.659425),
	FLinearColor(0.435734, 0.001127, 0.659797),
	FLinearColor(0.441732, 0.001540, 0.660069),
	FLinearColor(0.447714, 0.002080, 0.660240),
	FLinearColor(0.453677, 0.002755, 0.660310),
	FLinearColor(0.459623, 0.003574, 0.660277),
	FLinearColor(0.465550, 0.004545, 0.660139),
	FLinearColor(0.471457, 0.005678, 0.659897),
	FLinearColor(0.477344, 0.006980, 0.659549),
	FLinearColor(0.483210, 0.008460, 0.659095),
	FLinearColor(0.489055, 0.010127, 0.658534),
	FLinearColor(0.494877, 0.011990, 0.657865),
	FLinearColor(0.500678, 0.014055, 0.657088),
	FLinearColor(0.506454, 0.016333, 0.656202),
	FLinearColor(0.512206, 0.018833, 0.655209),
	FLinearColor(0.517933, 0.021563, 0.654109),
	FLinearColor(0.523633, 0.024532, 0.652901),
	FLinearColor(0.529306, 0.027747, 0.651586),
	FLinearColor(0.534952, 0.031217, 0.650165),
	FLinearColor(0.540570, 0.034950, 0.648640),
	FLinearColor(0.546157, 0.038954, 0.647010),
	FLinearColor(0.551715, 0.043136, 0.645277),
	FLinearColor(0.557243, 0.047331, 0.643443),
	FLinearColor(0.562738, 0.051545, 0.641509),
	FLinearColor(0.568201, 0.055778, 0.639477),
	FLinearColor(0.573632, 0.060028, 0.637349),
	FLinearColor(0.579029, 0.064296, 0.635126),
	FLinearColor(0.584391, 0.068579, 0.632812),
	FLinearColor(0.589719, 0.072878, 0.630408),
	FLinearColor(0.595011, 0.077190, 0.627917),
	FLinearColor(0.600266, 0.081516, 0.625342),
	FLinearColor(0.605485, 0.085854, 0.622686),
	FLinearColor(0.610667, 0.090204, 0.619951),
	FLinearColor(0.615812, 0.094564, 0.617140),
	FLinearColor(0.620919, 0.098934, 0.614257),
	FLinearColor(0.625987, 0.103312, 0.611305),
	FLinearColor(0.631017, 0.107699, 0.608287),
	FLinearColor(0.636008, 0.112092, 0.605205),
	FLinearColor(0.640959, 0.116492, 0.602065),
	FLinearColor(0.645872, 0.120898, 0.598867),
	FLinearColor(0.650746, 0.125309, 0.595617),
	FLinearColor(0.655580, 0.129725, 0.592317),
	FLinearColor(0.660374, 0.134144, 0.588971),
	FLinearColor(0.665129, 0.138566, 0.585582),
	FLinearColor(0.669845, 0.142992, 0.582154),
	FLinearColor(0.674522, 0.147419, 0.578688),
	FLinearColor(0.679160, 0.151848, 0.575189),
	FLinearColor(0.683758, 0.156278, 0.571660),
	FLinearColor(0.688318, 0.160709, 0.568103),
	FLinearColor(0.692840, 0.165141, 0.564522),
	FLinearColor(0.697324, 0.169573, 0.560919),
	FLinearColor(0.701769, 0.174005, 0.557296),
	FLinearColor(0.706178, 0.178437, 0.553657),
	FLinearColor(0.710549, 0.182868, 0.550004),
	FLinearColor(0.714883, 0.187299, 0.546338),
	FLinearColor(0.719181, 0.191729, 0.542663),
	FLinearColor(0.723444, 0.196158, 0.538981),
	FLinearColor(0.727670, 0.200586, 0.535293),
	FLinearColor(0.731862, 0.205013, 0.531601),
	FLinearColor(0.736019, 0.209439, 0.527908),
	FLinearColor(0.740143, 0.213864, 0.524216),
	FLinearColor(0.744232, 0.218288, 0.520524),
	FLinearColor(0.748289, 0.222711, 0.516834),
	FLinearColor(0.752312, 0.227133, 0.513149),
	FLinearColor(0.756304, 0.231555, 0.509468),
	FLinearColor(0.760264, 0.235976, 0.505794),
	FLinearColor(0.764193, 0.240396, 0.502126),
	FLinearColor(0.768090, 0.244817, 0.498465),
	FLinearColor(0.771958, 0.249237, 0.494813),
	FLinearColor(0.775796, 0.253658, 0.491171),
	FLinearColor(0.779604, 0.258078, 0.487539),
	FLinearColor(0.783383, 0.262500, 0.483918),
	FLinearColor(0.787133, 0.266922, 0.480307),
	FLinearColor(0.790855, 0.271345, 0.476706),
	FLinearColor(0.794549, 0.275770, 0.473117),
	FLinearColor(0.798216, 0.280197, 0.469538),
	FLinearColor(0.801855, 0.284626, 0.465971),
	FLinearColor(0.805467, 0.289057, 0.462415),
	FLinearColor(0.809052, 0.293491, 0.458870),
	FLinearColor(0.812612, 0.297928, 0.455338),
	FLinearColor(0.816144, 0.302368, 0.451816),
	FLinearColor(0.819651, 0.306812, 0.448306),
	FLinearColor(0.823132, 0.311261, 0.444806),
	FLinearColor(0.826588, 0.315714, 0.441316),
	FLinearColor(0.830018, 0.320172, 0.437836),
	FLinearColor(0.833422, 0.324635, 0.434366),
	FLinearColor(0.836801, 0.329105, 0.430905),
	FLinearColor(0.840155, 0.333580, 0.427455),
	FLinearColor(0.843484, 0.338062, 0.424013),
	FLinearColor(0.846788, 0.342551, 0.420579),
	FLinearColor(0.850066, 0.347048, 0.417153),
	FLinearColor(0.853319, 0.351553, 0.413734),
	FLinearColor(0.856547, 0.356066, 0.410322),
	FLinearColor(0.859750, 0.360588, 0.406917),
	FLinearColor(0.862927, 0.365119, 0.403519),
	FLinearColor(0.866078, 0.369660, 0.400126),
	FLinearColor(0.869203, 0.374212, 0.396738),
	FLinearColor(0.872303, 0.378774, 0.393355),
	FLinearColor(0.875376, 0.383347, 0.389976),
	FLinearColor(0.878423, 0.387932, 0.386600),
	FLinearColor(0.881443, 0.392529, 0.383229),
	FLinearColor(0.884436, 0.397139, 0.379860),
	FLinearColor(0.887402, 0.401762, 0.376494),
	FLinearColor(0.890340, 0.406398, 0.373130),
	FLinearColor(0.893250, 0.411048, 0.369768),
	FLinearColor(0.896131, 0.415712, 0.366407),
	FLinearColor(0.898984, 0.420392, 0.363047),
	FLinearColor(0.901807, 0.425087, 0.359688),
	FLinearColor(0.904601, 0.429797, 0.356329),
	FLinearColor(0.907365, 0.434524, 0.352970),
	FLinearColor(0.910098, 0.439268, 0.349610),
	FLinearColor(0.912800, 0.444029, 0.346251),
	FLinearColor(0.915471, 0.448807, 0.342890),
	FLinearColor(0.918109, 0.453603, 0.339529),
	FLinearColor(0.920714, 0.458417, 0.336166),
	FLinearColor(0.923287, 0.463251, 0.332801),
	FLinearColor(0.925825, 0.468103, 0.329435),
	FLinearColor(0.928329, 0.472975, 0.326067),
	FLinearColor(0.930798, 0.477867, 0.322697),
	FLinearColor(0.933232, 0.482780, 0.319325),
	FLinearColor(0.935630, 0.487712, 0.315952),
	FLinearColor(0.937990, 0.492667, 0.312575),
	FLinearColor(0.940313, 0.497642, 0.309197),
	FLinearColor(0.942598, 0.502639, 0.305816),
	FLinearColor(0.944844, 0.507658, 0.302433),
	FLinearColor(0.947051, 0.512699, 0.299049),
	FLinearColor(0.949217, 0.517763, 0.295662),
	FLinearColor(0.951344, 0.522850, 0.292275),
	FLinearColor(0.953428, 0.527960, 0.288883),
	FLinearColor(0.955470, 0.533093, 0.285490),
	FLinearColor(0.957469, 0.538250, 0.282096),
	FLinearColor(0.959424, 0.543431, 0.278701),
	FLinearColor(0.961336, 0.548636, 0.275305),
	FLinearColor(0.963203, 0.553865, 0.271909),
	FLinearColor(0.965024, 0.559118, 0.268513),
	FLinearColor(0.966798, 0.564396, 0.265118),
	FLinearColor(0.968526, 0.569700, 0.261721),
	FLinearColor(0.970205, 0.575028, 0.258325),
	FLinearColor(0.971835, 0.580382, 0.254931),
	FLinearColor(0.973416, 0.585761, 0.251540),
	FLinearColor(0.974947, 0.591165, 0.248151),
	FLinearColor(0.976428, 0.596595, 0.244767),
	FLinearColor(0.977856, 0.602051, 0.241387),
	FLinearColor(0.979233, 0.607532, 0.238013),
	FLinearColor(0.980556, 0.613039, 0.234646),
	FLinearColor(0.981826, 0.618572, 0.231287),
	FLinearColor(0.983041, 0.624131, 0.227937),
	FLinearColor(0.984199, 0.629718, 0.224595),
	FLinearColor(0.985301, 0.635330, 0.221265),
	FLinearColor(0.986345, 0.640969, 0.217948),
	FLinearColor(0.987332, 0.646633, 0.214648),
	FLinearColor(0.988260, 0.652325, 0.211364),
	FLinearColor(0.989128, 0.658043, 0.208100),
	FLinearColor(0.989935, 0.663787, 0.204859),
	FLinearColor(0.990681, 0.669558, 0.201642),
	FLinearColor(0.991365, 0.675355, 0.198453),
	FLinearColor(0.991985, 0.681179, 0.195295),
	FLinearColor(0.992541, 0.687030, 0.192170),
	FLinearColor(0.993032, 0.692907, 0.189084),
	FLinearColor(0.993456, 0.698810, 0.186041),
	FLinearColor(0.993814, 0.704741, 0.183043),
	FLinearColor(0.994103, 0.710698, 0.180097),
	FLinearColor(0.994324, 0.716681, 0.177208),
	FLinearColor(0.994474, 0.722691, 0.174381),
	FLinearColor(0.994553, 0.728728, 0.171622),
	FLinearColor(0.994561, 0.734791, 0.168938),
	FLinearColor(0.994495, 0.740880, 0.166335),
	FLinearColor(0.994355, 0.746995, 0.163821),
	FLinearColor(0.994141, 0.753137, 0.161404),
	FLinearColor(0.993851, 0.759304, 0.159092),
	FLinearColor(0.993482, 0.765499, 0.156891),
	FLinearColor(0.993033, 0.771720, 0.154808),
	FLinearColor(0.992505, 0.777967, 0.152855),
	FLinearColor(0.991897, 0.784239, 0.151042),
	FLinearColor(0.991209, 0.790537, 0.149377),
	FLinearColor(0.990439, 0.796859, 0.147870),
	FLinearColor(0.989587, 0.803205, 0.146529),
	FLinearColor(0.988648, 0.809579, 0.145357),
	FLinearColor(0.987621, 0.815978, 0.144363),
	FLinearColor(0.986509, 0.822401, 0.143557),
	FLinearColor(0.985314, 0.828846, 0.142945),
	FLinearColor(0.984031, 0.835315, 0.142528),
	FLinearColor(0.982653, 0.841812, 0.142303),
	FLinearColor(0.981190, 0.848329, 0.142279),
	FLinearColor(0.979644, 0.854866, 0.142453),
	FLinearColor(0.977995, 0.861432, 0.142808),
	FLinearColor(0.976265, 0.868016, 0.143351),
	FLinearColor(0.974443, 0.874622, 0.144061),
	FLinearColor(0.972530, 0.881250, 0.144923),
	FLinearColor(0.970533, 0.887896, 0.145919),
	FLinearColor(0.968443, 0.894564, 0.147014),
	FLinearColor(0.966271, 0.901249, 0.148180),
	FLinearColor(0.964021, 0.907950, 0.149370),
	FLinearColor(0.961681, 0.914672, 0.150520),
	FLinearColor(0.959276, 0.921407, 0.151566),
	FLinearColor(0.956808, 0.928152, 0.152409),
	FLinearColor(0.954287, 0.934908, 0.152921),
	FLinearColor(0.951726, 0.941671, 0.152925),
	FLinearColor(0.949151, 0.948435, 0.152178),
	FLinearColor(0.946602, 0.955190, 0.150328),
	FLinearColor(0.944152, 0.961916, 0.146861),
	FLinearColor(0.941896, 0.968590, 0.140956),
	FLinearColor(0.940015, 0.975158, 0.131326)
};


TArray<FLinearColor> UPT_SimulationComponent::MapToPlasmaColormap(
	const TArray<double>& InData,
	const int32& InDataTagIndex,
	const double& InPercentileMinValue,
	const double& InPercentileMaxValue
) {
	double Range = InPercentileMaxValue - InPercentileMinValue;

	if (FMath::IsNearlyZero(Range)) {
		UE_LOG(LogTemp, Error, TEXT("[MapToPlasmaColormap] Range is zero!"));
		Range = 1.0; // Avoid division by zero
	}

	if (InPercentileMaxValue <= InPercentileMinValue) {
		UE_LOG(LogTemp, Warning, TEXT("[MapToPlasmaColormap] Invalid range: Min (%f) is not less than Max (%f)"), InPercentileMinValue, InPercentileMaxValue);
	}

	// Create an array for plasma colormap
	TArray<FLinearColor> OutputColormap;
	OutputColormap.Init(FLinearColor::Black, InData.Num());

	for (const int32 CurrentCellIndex : this->RoiIndexMappingPerTagArray[InDataTagIndex]) {
		if (!InData.IsValidIndex(CurrentCellIndex)) {
			UE_LOG(LogTemp, Warning, TEXT("[MapToPlasmaColormap] Invalid index: %d in RoiIndexMappingPerTagArray[%d]"), CurrentCellIndex, InDataTagIndex);
			continue;
		}

		double NormalizedValue = FMath::Clamp((InData[CurrentCellIndex] - InPercentileMinValue) / Range, 0.0, 1.0);

		// Mapping NormalizedValue to the Plasma colormap index
		int32 ColorIndex = FMath::Clamp(FMath::RoundToInt(NormalizedValue * 255), 0, 255);
		FLinearColor PlasmaColor = PlasmaColormap[ColorIndex];

		OutputColormap[CurrentCellIndex] = PlasmaColor;
	}
	return OutputColormap;
}

TArray<FLinearColor> UPT_SimulationComponent::MapToJetColormap(
	const TArray<double>& InData,
	const int32& InDataTagIndex,
	const double& InPercentileMinValue,
	const double& InPercentileMaxValue
)
{
	// Festlegen der Größen und Grenzen
	double Range = InPercentileMaxValue - InPercentileMinValue;

	// Erstellen eines Farbarrays
	TArray<FLinearColor> Colormap;
	Colormap.Init(FLinearColor::White, InData.Num());

	// Zuordnung der Werte zu den Farben basierend auf der Jet-Colormap
	for (const int32 CurrentCellIndex : this->RoiIndexMappingPerTagArray[InDataTagIndex])
	{	
		double ClampedValue = FMath::Clamp(InData[CurrentCellIndex], InPercentileMinValue, InPercentileMaxValue);
		double NormalizedValue = 0.0;
		if (Range != 0) {
			NormalizedValue = (ClampedValue - InPercentileMinValue) / Range;
		}
		UE_LOG(LogTemp, Log, TEXT("ClampedValue = %f, NormalizedValue = %f"), ClampedValue, NormalizedValue);

		double R = FMath::Clamp(1.5 - FMath::Abs(2.0 * NormalizedValue - 1.0), 0.0, 1.0);
		double G = FMath::Clamp(1.5 - FMath::Abs(2.0 * NormalizedValue - 0.5), 0.0, 1.0);
		double B = FMath::Clamp(1.5 - FMath::Abs(2.0 * NormalizedValue), 0.0, 1.0);

		UE_LOG(LogTemp, Log, TEXT("[MapToJetColormap] Color[%d] = [%f, %f, %f]"), CurrentCellIndex, R, G, B);

		// Zuordnung zu einem Farbwert
		Colormap[CurrentCellIndex].R = R;
		Colormap[CurrentCellIndex].G = G;
		Colormap[CurrentCellIndex].B = B;
		Colormap[CurrentCellIndex].A = 1.f; // Alpha-Kanal auf maximale Transparenz setzen
	}
	return Colormap;
}

TArray<FLinearColor> UPT_SimulationComponent::MapToGreyscaleColormap(
	const TArray<double>& InData,
	const int32& InDataTagIndex,
	const double& InPercentileMinValue,
	const double& InPercentileMaxValue
)
{
	UE_LOG(LogTemp, Log, TEXT("[MapToGreyscaleColormap] InData length = %d"), InData.Num());
	//UE_LOG(LogTemp, Log, TEXT("[MapToGreyscaleColormap] InDataTagIndex: %d"), InDataTagIndex);
	double Range = InPercentileMaxValue - InPercentileMinValue;

	if (FMath::IsNearlyZero(Range)) {
		UE_LOG(LogTemp, Error, TEXT("[MapToGreyscaleColormap] Range is zero!"));
		Range = 1.0; // Avoid division by zero
	}

	// Create an array for greyscale colormap
	TArray<FLinearColor> GreyscaleColormap;
	GreyscaleColormap.Init(FLinearColor::Blue, InData.Num());

	// Map values to colors based on greyscale
	for (const int32 CurrentCellIndex : this->RoiIndexMappingPerTagArray[InDataTagIndex])
	{
		if (CurrentCellIndex < 0 || CurrentCellIndex >= InData.Num()) {
			continue; // Skip invalid indices
		}
		//double ClampedData = FMath::Clamp(InData[CurrentCellIndex], InPercentileMinValue, InPercentileMaxValue);
		//double NormalizedValue = (ClampedData - InPercentileMinValue) / Range;
		//double GreyValue = FMath::Clamp(NormalizedValue, 0.0, 1.0);
		double GrayValue = FMath::Clamp((InData[CurrentCellIndex] - InPercentileMinValue) / Range, 0.0, 1.0);

		// Assign to a color value
		GreyscaleColormap[CurrentCellIndex].R = GrayValue;
		GreyscaleColormap[CurrentCellIndex].G = GrayValue;
		GreyscaleColormap[CurrentCellIndex].B = GrayValue;
		GreyscaleColormap[CurrentCellIndex].A = 1.f; // Full opacity
	}

	return GreyscaleColormap;
}

static void LogVertexTagCellMapping(TMap<int32, TArray<FJsonSerializableArrayInt>> VertexTagCellMapping)
{
	for (const auto& MapEntry : VertexTagCellMapping)
	{
		int32 Key = MapEntry.Key;
		const TArray<FJsonSerializableArrayInt>& Array = MapEntry.Value;

		UE_LOG(LogTemp, Log, TEXT("Key: %d"), Key);

		for (int32 Index = 0; Index < Array.Num(); ++Index)
		{
			const FJsonSerializableArrayInt& InnerArray = Array[Index]; // This is a TArray<int32>

			FString SerializedArray;
			for (int32 InnerValue : InnerArray) // Loop through each int32 in the inner array
			{
				SerializedArray += FString::FromInt(InnerValue) + TEXT(", ");
			}

			// Trim the trailing comma and space
			if (!SerializedArray.IsEmpty())
			{
				SerializedArray.RemoveAt(SerializedArray.Len() - 2, 2);
			}

			UE_LOG(LogTemp, Log, TEXT("    Array[%d]: %s"), Index, *SerializedArray);
		}
	}
}
TArray<FLinearColor> UPT_SimulationComponent::CalculateVertexColors(const int32& InVertexArrayLength)
{
	TArray<FLinearColor> OutVertexColors;
	OutVertexColors.Init(FLinearColor(0.9f, 0.9f, 0.9f), InVertexArrayLength);
	this->VectorfieldInRoi.Empty();

	LogVertexTagCellMapping(this->VertexTagCellMapping);
	int32 GoodCounter = 0;
	int32 BadCounter = 0;
	int32 EmptyCellIndices = 0;
	int32 InvalidIndices = 0;
	int32 InvalidMappingIndices = 0;
	for (const int32 CurrentVertexIndex : this->VerticesInRoiArray)
	{
		if (!OutVertexColors.IsValidIndex(CurrentVertexIndex))
		{
			InvalidIndices++;
			continue;
		}

		int32 MeanCounter = 0;
		//double R = 0.0, G = 0.0, B = 0.0;
		FLinearColor NewColor = FLinearColor(0.f, 0.f, 0.f);
		FVector Vectorfield = FVector::ZeroVector;

		for (const int32 CurrentTagIndex : UPT_ConfigManager::GetDataTagVolumeIndexArray())
		{
			if (!this->VertexTagCellMapping.Contains(CurrentVertexIndex) ||
				!this->VertexTagCellMapping[CurrentVertexIndex].IsValidIndex(CurrentTagIndex))
			{
				InvalidMappingIndices++;
				continue;
			}

			const TArray<int32>& CurrentCellIndices = this->VertexTagCellMapping[CurrentVertexIndex][CurrentTagIndex];

			if (CurrentCellIndices.IsEmpty())
			{
				UE_LOG(LogTemp, Warning, TEXT("CurrentCellIndices Empty for Vertex Index: %d, andCurrent Tag Index: %d"), CurrentVertexIndex, CurrentTagIndex);
				EmptyCellIndices++;
				continue;
			}

			for (const int32 CurrentCellIndex : CurrentCellIndices)
			{
				const FLinearColor& Color = this->DataColorArrayPerTag[CurrentTagIndex][CurrentCellIndex];
				//UE_LOG(LogTemp, Log, TEXT("[CalculateVertexColors] Color: [%f, %f, %f]"), Color.R, Color.G, Color.B);
				NewColor += Color;

				/*R += Color.R;
				G += Color.G;
				B += Color.B;*/

				MeanCounter++;
				Vectorfield += this->InterpolatedVectorfieldDataPerTagArray[CurrentTagIndex][CurrentCellIndex];
			}
		}
		if (MeanCounter > 0)
		{
			GoodCounter++;
			//const float InvMeanCounter = 1.0f / MeanCounter;
			OutVertexColors[CurrentVertexIndex] = NewColor / MeanCounter;
			/*OutVertexColors[CurrentVertexIndex].R = R / MeanCounter;
			OutVertexColors[CurrentVertexIndex].G = G / MeanCounter;
			OutVertexColors[CurrentVertexIndex].B = B / MeanCounter;*/
			this->VectorfieldInRoi.Add(Vectorfield / MeanCounter);
		}
		else
		{
			BadCounter++;
			//UE_LOG(LogTemp, Error, TEXT("[CalculateVertexColors] No Color Values for Vertex, assigning fallback color"));
			OutVertexColors[CurrentVertexIndex] = FLinearColor::Red; // Fallback color
			this->VectorfieldInRoi.Add(FVector::ZeroVector);
		}
		
	}
	UE_LOG(LogTemp, Log, TEXT("Goods: %d, Bads: %d"), GoodCounter, BadCounter);
	UE_LOG(LogTemp, Log, TEXT("Empty Cell Indices: %d"), EmptyCellIndices);
	UE_LOG(LogTemp, Log, TEXT("Invalid Indices: %d"), InvalidIndices);
	UE_LOG(LogTemp, Log, TEXT("Invalid Mapping Indices: %d"), InvalidMappingIndices);
	return OutVertexColors;
}

void UPT_SimulationComponent::BarycentricInterpolation(
	const int32& InElectrodeIndexA,
	const int32& InElectrodeIndexB,
	const int32& InElectrodeIndexC,
	const int32& InDataTagIndex,
	const double& InWeightA,
	const double& InWeightB,
	const double& InWeightC,
	TArray<double>& OutInterpolatedSimulationMagnitudeDataArray,
	TArray<FVector>& OutInterpolatedSimulationVectorfieldDataArray,
	double& OutMeanMagnitude, FVector& OutMeanVectorField
)
{

	//UE_LOG(LogTemp, Warning, TEXT("WeightA = %f, WeightB = %f, WeightC = %f, Added = %f"), InWeightA, InWeightB, InWeightC, InWeightA+InWeightB+InWeightC);
	OutMeanMagnitude = 0.0;
	OutMeanVectorField = FVector::ZeroVector;
	// Prüfung der Gewichtungen
	const double WeightSum = InWeightA + InWeightB + InWeightC;
	check(FMath::IsNearlyEqual(WeightSum, 1.0, KINDA_SMALL_NUMBER));

	// Daten für Elektroden A, B und C
	TArray<double> SimulationMagnitudeDataArrayA, SimulationMagnitudeDataArrayB, SimulationMagnitudeDataArrayC;
	TArray<FVector> SimulationVectorfieldDataArrayA, SimulationVectorfieldDataArrayB, SimulationVectorfieldDataArrayC;


	this->GetSimulationDataPerElectrodePerTag(InElectrodeIndexA, InDataTagIndex, SimulationMagnitudeDataArrayA, SimulationVectorfieldDataArrayA);
	this->GetSimulationDataPerElectrodePerTag(InElectrodeIndexB, InDataTagIndex, SimulationMagnitudeDataArrayB, SimulationVectorfieldDataArrayB);
	this->GetSimulationDataPerElectrodePerTag(InElectrodeIndexC, InDataTagIndex, SimulationMagnitudeDataArrayC, SimulationVectorfieldDataArrayC);

	// Prüfung der Datenlängen
	check(SimulationMagnitudeDataArrayA.Num() == SimulationMagnitudeDataArrayB.Num() && SimulationMagnitudeDataArrayB.Num() == SimulationMagnitudeDataArrayC.Num());
	check(SimulationVectorfieldDataArrayA.Num() == SimulationVectorfieldDataArrayB.Num() && SimulationVectorfieldDataArrayB.Num() == SimulationVectorfieldDataArrayC.Num());
	check(SimulationMagnitudeDataArrayA.Num() == SimulationVectorfieldDataArrayA.Num());

	// Initialisierung des Ausgabearrays
	OutInterpolatedSimulationMagnitudeDataArray.SetNumZeroed(SimulationMagnitudeDataArrayA.Num());
	OutInterpolatedSimulationVectorfieldDataArray.SetNumZeroed(SimulationMagnitudeDataArrayA.Num());

	for(const int32 CurrentCellIndex : this->RoiIndexMappingPerTagArray[InDataTagIndex])
	{
		OutInterpolatedSimulationMagnitudeDataArray[CurrentCellIndex] = InWeightA * SimulationMagnitudeDataArrayA[CurrentCellIndex] + InWeightB * SimulationMagnitudeDataArrayB[CurrentCellIndex] + InWeightC * SimulationMagnitudeDataArrayC[CurrentCellIndex];
		OutInterpolatedSimulationVectorfieldDataArray[CurrentCellIndex] = InWeightA * SimulationVectorfieldDataArrayA[CurrentCellIndex] + InWeightB * SimulationVectorfieldDataArrayB[CurrentCellIndex] + InWeightC * SimulationVectorfieldDataArrayC[CurrentCellIndex];

		OutMeanMagnitude += OutInterpolatedSimulationMagnitudeDataArray[CurrentCellIndex];
		OutMeanVectorField += OutInterpolatedSimulationVectorfieldDataArray[CurrentCellIndex];
	}

	const double InvMeanCounter = 1.0 / this->RoiIndexMappingPerTagArray[InDataTagIndex].Num();


	if (InvMeanCounter > 0.0)
	{
		OutMeanMagnitude *= InvMeanCounter;
		OutMeanVectorField *= InvMeanCounter;
		return;
	}

	OutMeanMagnitude = 0.0;
	OutMeanVectorField = FVector::ZeroVector;
	return;
}

void UPT_SimulationComponent::ProcessInterpolation(const int32& InElectrodeIndexA, const int32& InElectrodeIndexB, const int32& InElectrodeIndexC, const double& InWeightA, const double& InWeightB, const double& InWeightC)
{
	for (int32 CurrentTagIndex = 0; CurrentTagIndex < UPT_ConfigManager::GetDataTagIndexArray().Num(); CurrentTagIndex++)
	{
		this->BarycentricInterpolation(InElectrodeIndexA, InElectrodeIndexB, InElectrodeIndexC, UPT_ConfigManager::GetDataTagIndexArray()[CurrentTagIndex], InWeightA, InWeightB, InWeightC, this->InterpolatedMagnitudeDataPerTagArray[CurrentTagIndex], this->InterpolatedVectorfieldDataPerTagArray[CurrentTagIndex], this->MeanMagnitudePerTag[CurrentTagIndex], this->MeanVectorFieldPerTag[CurrentTagIndex]);		
	}
}

double UPT_SimulationComponent::CalculatePercentile(const TArray<double>& InData, const double& InPercentile)
{
	if (InData.Num() == 0)
	{
		return 0.0f; // Rückgabe von 0, wenn Daten leer sind
	}

	TArray<double> SortedData = InData;
	SortedData.Sort(); // Sortieren der Daten

	double Index = (InPercentile / 100.0f) * (SortedData.Num() - 1);
	int32 LowerIndex = FMath::FloorToInt(Index);
	int32 UpperIndex = FMath::CeilToInt(Index);

	if (LowerIndex == UpperIndex)
	{
		return SortedData[LowerIndex]; // Rückgabe des Werts, wenn Index ganzzahlig ist
	}
	else
	{
		// Interpolation zwischen den beiden Indizes
		double LowerValue = SortedData[LowerIndex];
		double UpperValue = SortedData[UpperIndex];
		double InterpolatedValue = LowerValue + (UpperValue - LowerValue) * (Index - LowerIndex);
		return InterpolatedValue;
	}
}

double UPT_SimulationComponent::CalculatePercentileForInterpolatedMagnitudeDataPerTagArray(const double& InPercentile)
{
	TArray<double> SortedData;

	if (this->InterpolatedMagnitudeDataPerTagArray.Num() == 0)
	{
		return 0.0f; // Rückgabe von 0, wenn Daten leer sind
	}

	auto IsAllZeros = [](const TArray<double>& DataArray) -> bool{
		for (double Value : DataArray) {
			if (Value != 0.0) {
				return false;
			}
		}
		return true;
	};

	for(int32 CurrentTagIndex : UPT_ConfigManager::GetDataTagVolumeIndexArray())
	{
		TArray<double> CurrentMagnitudeDataArray = this->InterpolatedMagnitudeDataPerTagArray[CurrentTagIndex];

		// Skip arrays that are empty or contain only zeros
		if(CurrentMagnitudeDataArray.Num() == 0 || IsAllZeros(CurrentMagnitudeDataArray))
		{
			continue;
		}

		for(int32 CurrentCellIndex : this->RoiIndexMappingPerTagArray[CurrentTagIndex])
		{
			if (CurrentMagnitudeDataArray[CurrentCellIndex] != 0.0) {
				SortedData.Add(CurrentMagnitudeDataArray[CurrentCellIndex]);
			}
		}
	}

	if (SortedData.Num() == 0) {
		return 0.0f; // Return 0 if no valid data was added
	}
	

	SortedData.Sort(); // Sort the data

	double Index = (InPercentile / 100.0f) * (SortedData.Num() - 1);
	int32 LowerIndex = FMath::FloorToInt(Index);
	int32 UpperIndex = FMath::CeilToInt(Index);

	UE_LOG(LogTemp, Log, TEXT("[CalculatePercentileForInterpolatedMagnitudeDataPerTagArray] Data Length: %d"), SortedData.Num());
	UE_LOG(LogTemp, Log, TEXT("[CalculatePercentileForInterpolatedMagnitudeDataPerTagArray] Overall Minimum: %f"), SortedData[0]);
	UE_LOG(LogTemp, Log, TEXT("[CalculatePercentileForInterpolatedMagnitudeDataPerTagArray] Overall Maximum: %f"), SortedData[SortedData.Num() - 1]);


	if (LowerIndex == UpperIndex)
	{
		return SortedData[LowerIndex]; // Return the value if index is an integer
	}
	else
	{
		// Interpolate between the two indices
		double LowerValue = SortedData[LowerIndex];
		double UpperValue = SortedData[UpperIndex];
		double InterpolatedValue = LowerValue + (UpperValue - LowerValue) * (Index - LowerIndex);
		return InterpolatedValue;
	}
}

void UPT_SimulationComponent::GetSimulationDataFromJSONResponseBody(const UPT_HTTPComponent* InHttpComponent, const TArray<FString>& InDataTagArray, const int32& InNumberOfElectrodes)
{
	const TSharedPtr<FJsonObject> ResponseObject = InHttpComponent->GetResponseObject();
	this->GetSimulationDataFromJSONObject(&ResponseObject, InDataTagArray, InNumberOfElectrodes);
}

void UPT_SimulationComponent::CreateInterpolatedDataJson(const FString& InPatientId, const FString& InConfigId, const FString& InRoiId, const FString& InInterpolationId, const FVector& InElectrodePosition, const double& InGridSpacing, FString& OutJsonString)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	TSharedPtr<FJsonObject> MetadataJson = MakeShareable(new FJsonObject);
	MetadataJson->SetStringField(TEXT("patient_id"), InPatientId);
	MetadataJson->SetStringField(TEXT("config_id"), InConfigId);
	MetadataJson->SetStringField(TEXT("roi_id"), InRoiId);
	MetadataJson->SetStringField(TEXT("interpolation_id"), InInterpolationId);
	MetadataJson->SetNumberField(TEXT("grid_spacing"), InGridSpacing);

	MetadataJson->SetObjectField(TEXT("ElectrodePosition"), UPT_JSONConverter::CreateJsonObjectFromVector(InElectrodePosition));

	JsonObject->SetObjectField(TEXT("Metadata"), MetadataJson);
	TSharedPtr<FJsonObject> FieldData = MakeShareable(new FJsonObject);
	TSharedPtr<FJsonObject> MagnitudeData = MakeShareable(new FJsonObject);

	if (this->InterpolatedVectorfieldDataPerTagArray.Num() == UPT_ConfigManager::GetDataTagArray().Num() && this->InterpolatedMagnitudeDataPerTagArray.Num() == UPT_ConfigManager::GetDataTagArray().Num())
	{
		for (int32 CurrentTagIndex = 0; CurrentTagIndex < UPT_ConfigManager::GetDataTagArray().Num(); CurrentTagIndex++)
		{
			FString CurrentTagName = UPT_ConfigManager::GetDataTagArray()[CurrentTagIndex];
			TArray<FVector> CurrentFieldData;
			TArray<double> CurrentMagnitudeData;

			for(const int32 CurrentIndex : this->RoiIndexMappingPerTagArray[CurrentTagIndex])
			{
				CurrentFieldData.Add(this->InterpolatedVectorfieldDataPerTagArray[CurrentTagIndex][CurrentIndex]);
				CurrentMagnitudeData.Add(this->InterpolatedMagnitudeDataPerTagArray[CurrentTagIndex][CurrentIndex]);
			}

			FieldData->SetArrayField(CurrentTagName, UPT_JSONConverter::CreateJsonArrayFromVectorArray(CurrentFieldData));
			MagnitudeData->SetArrayField(CurrentTagName, UPT_JSONConverter::CreateJsonArrayFromDoubleArray(CurrentMagnitudeData));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_SimulationComponent::CreateInterpolatedDataJson] Interpolated data arrays and tag array have different sizes!"));
	}

	JsonObject->SetObjectField(TEXT("Vector"), FieldData);
	JsonObject->SetObjectField(TEXT("Magnitude"), MagnitudeData);

	OutJsonString = UPT_JSONConverter::SerializeJsonObjectToString(JsonObject);
}

void UPT_SimulationComponent::ResetSimulationDataArrays()
{
	this->SimulationMagnitudeDataPerElectrodePerTagArray.Empty();
	this->SimulationVectorfieldDataPerElectrodePerTagArray.Empty();

	this->InterpolatedMagnitudeDataPerTagArray.Empty();
	this->InterpolatedMagnitudeDataPerTagArray.SetNumZeroed(UPT_ConfigManager::GetDataTagIndexArray().Num());
	this->InterpolatedVectorfieldDataPerTagArray.Empty();
	this->InterpolatedVectorfieldDataPerTagArray.SetNumZeroed(UPT_ConfigManager::GetDataTagIndexArray().Num());
	this->PerVertexDataArray.Empty();
	this->RawTetraDataArray.Empty();
	this->ElectrodeIndexArray.Empty();
	this->RoiIndexMappingPerTagArray.Empty();
	this->TagLengthArray.Empty();
	this->MeanMagnitudePerTag.Empty();
	this->MeanMagnitudePerTag.SetNumZeroed(UPT_ConfigManager::GetDataTagIndexArray().Num());
	this->MeanVectorFieldPerTag.Empty();
	this->MeanVectorFieldPerTag.SetNumZeroed(UPT_ConfigManager::GetDataTagIndexArray().Num());
	this->MeanMagnitude = 0.0;
	this->MeanVectorField = FVector::ZeroVector;
	this->VertexTagCellMapping.Empty();
	this->VerticesInRoiArray.Empty();
	this->DataColorArrayPerTag.Empty();
	this->DataColorArrayPerTag.SetNumZeroed(UPT_ConfigManager::GetDataTagIndexArray().Num());
	this->VectorfieldInRoi.Empty();
}

void UPT_SimulationComponent::CalculateMeanAngleBetweenNormalAndVectorField(const TArray<FVector>& InNormalArray, const TArray<FVector>& InVectorFieldArray, double& OutMeanAngle)
{
	//// Ensure the arrays have the same size
	//if (InNormalArray.Num() != InVectorFieldArray.Num() || InNormalArray.Num() == 0)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("[CalculateMeanAngleBetweenNormalAndVectorField] Input NormalArray and VectorFieldArray are mismatched! Lengths are Normal: %f, VF: %f"), InNormalArray.Num(), InVectorFieldArray.Num());
	//	OutMeanAngle = 0.0;
	//	return;
	//}

	//double TotalAngle = 0.0;
	//int32 Count = InNormalArray.Num();

	//for (int32 i = 0; i < Count; ++i)
	//{
	//	const FVector& Normal = InNormalArray[i].GetSafeNormal();
	//	const FVector& VectorField = InVectorFieldArray[i].GetSafeNormal();

	//	// Calculate the dot product
	//	double DotProduct = FVector::DotProduct(Normal, VectorField);

	//	// Clamp the dot product to the valid range for acos
	//	DotProduct = FMath::Clamp(DotProduct, -1.0, 1.0);

	//	// Compute the angle in radians and convert to degrees
	//	double Angle = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

	//	// Accumulate the angle
	//	TotalAngle += Angle;
	//}

	//// Calculate the mean angle
	//OutMeanAngle = TotalAngle / Count;
	OutMeanAngle = 0.0;
}

double UPT_SimulationComponent::GetAverageMagnitudePerTag(const int32& InTagIndex, bool& OutIsValid)
{
	if(this->MeanMagnitudePerTag.IsValidIndex(InTagIndex))
	{
		if(this->MeanMagnitudePerTag[InTagIndex] != 0.0)
		{
			OutIsValid = true;
			return this->MeanMagnitudePerTag[InTagIndex];
		}
		else
		{
			OutIsValid = false;
			return 0.0;
		}
	}

	OutIsValid = false;
	return 0.0;
}

FVector UPT_SimulationComponent::GetAverageVectorFieldPerTag(const int32& InTagIndex, bool& OutIsValid)
{
	if(this->MeanVectorFieldPerTag.IsValidIndex(InTagIndex))
	{
		if(!this->MeanVectorFieldPerTag[InTagIndex].IsZero())
		{
			OutIsValid = true;
			return this->MeanVectorFieldPerTag[InTagIndex];
		}
		else
		{
			OutIsValid = false;
			return FVector::ZeroVector;
		}
	}

	OutIsValid = false;
	return FVector::ZeroVector;
}

void UPT_SimulationComponent::GetSimulationDataPerElectrodePerTag(const int32& InElectrodeIndex, const int32& InTagIndex, TArray<double>& OutSimulationMagnitudeDataArray, TArray<FVector>& OutSimulationVectorfieldDataArray)
{
	OutSimulationMagnitudeDataArray = this->SimulationMagnitudeDataPerElectrodePerTagArray[InElectrodeIndex][InTagIndex];
	OutSimulationVectorfieldDataArray = this->SimulationVectorfieldDataPerElectrodePerTagArray[InElectrodeIndex][InTagIndex];
}

void UPT_SimulationComponent::GetInterpolatedSimulationDataPerTag(const int32& InTagIndex, TArray<double>& OutInterpolatedSimulationMagnitudeDataArray, TArray<FVector>& OutInterpolatedSimulationVectorfieldDataArray)
{
	OutInterpolatedSimulationMagnitudeDataArray = this->InterpolatedMagnitudeDataPerTagArray[InTagIndex];
	OutInterpolatedSimulationVectorfieldDataArray= this->InterpolatedVectorfieldDataPerTagArray[InTagIndex];
}

void UPT_SimulationComponent::GetSimulationDataFromJSONObject(
	const TSharedPtr<FJsonObject>* InJsonObjectPtr,
	const TArray<FString>& InDataTagArray,
	const int32& InNumberOfElectrodes
)
{
	this->TagLengthArray.Empty();
	this->TagLengthArray.SetNumZeroed(InDataTagArray.Num());
	this->RoiIndexMappingPerTagArray.Empty();
	this->RoiIndexMappingPerTagArray.SetNumZeroed(InDataTagArray.Num());

	const TSharedPtr<FJsonObject>* TagLengthObjectPtr;
	const TSharedPtr<FJsonObject>* IndexMappingObjectPtr;
	bool bTagLengthFound = InJsonObjectPtr->Get()->TryGetObjectField("Tag_Length", TagLengthObjectPtr);
	bool bIndexMappingFound = InJsonObjectPtr->Get()->TryGetObjectField("Index_Mapping", IndexMappingObjectPtr);

	if (!bTagLengthFound)
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_SimulationComponent::GetSimulationDataFromJSONObject] Field Tag_Length not found."));
		return;
	}

	if (!bIndexMappingFound)
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_SimulationComponent::GetSimulationDataFromJSONObject] Field Index_Mapping not found."));
		return;
	}

	for (int32 CurrentTagIndex = 0; CurrentTagIndex < InDataTagArray.Num(); CurrentTagIndex++)
	{
		int32 CurrentTagLength = 0;
		UPT_JSONConverter::ConvertJSONToInteger(TagLengthObjectPtr, InDataTagArray[CurrentTagIndex], CurrentTagLength);
		this->TagLengthArray[CurrentTagIndex] = CurrentTagLength;

		TArray<int32> CurrentRoiIndexMapping;
		UPT_JSONConverter::ConvertJSONObjectToIntegerArray(IndexMappingObjectPtr, InDataTagArray[CurrentTagIndex], CurrentRoiIndexMapping);
		this->RoiIndexMappingPerTagArray[CurrentTagIndex] = CurrentRoiIndexMapping;
	}

	this->SimulationMagnitudeDataPerElectrodePerTagArray.Empty();
	this->SimulationMagnitudeDataPerElectrodePerTagArray.SetNumZeroed(InNumberOfElectrodes);
	this->SimulationVectorfieldDataPerElectrodePerTagArray.Empty();
	this->SimulationVectorfieldDataPerElectrodePerTagArray.SetNumZeroed(InNumberOfElectrodes);

	const TSharedPtr<FJsonObject>* ElectrodesJsonObjectPtr;
	if (InJsonObjectPtr->Get()->TryGetObjectField("Electrodes", ElectrodesJsonObjectPtr))
	{
		for (int32 CurrentElectrodeIndex = 0; CurrentElectrodeIndex < InNumberOfElectrodes; CurrentElectrodeIndex++)
		{
			const TSharedPtr<FJsonObject>* ElectrodeDataJsonObjectPtr;
			if (ElectrodesJsonObjectPtr->Get()->TryGetObjectField(FString::Printf(TEXT("Electrode_%d"), CurrentElectrodeIndex), ElectrodeDataJsonObjectPtr))
			{
				this->ProcessElectrodeData(ElectrodeDataJsonObjectPtr, InDataTagArray, CurrentElectrodeIndex);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("[UPT_SimulationComponent::GetSimulationDataFromJSONObject] Field Electrode_%d not found. Adding Empty Array!"), CurrentElectrodeIndex);
				TArray<TArray<double>> SimulationMagnitudeDataPerTagArray;
				TArray<TArray<FVector>> SimulationVectorfieldDataPerTagArray;
				SimulationMagnitudeDataPerTagArray.SetNumZeroed(InDataTagArray.Num());
				SimulationVectorfieldDataPerTagArray.SetNumZeroed(InDataTagArray.Num());

				for(int32 CurrentTagIndex = 0; CurrentTagIndex < InDataTagArray.Num(); CurrentTagIndex++)
				{
					SimulationMagnitudeDataPerTagArray[CurrentTagIndex].SetNumZeroed(this->TagLengthArray[CurrentTagIndex]);
					SimulationVectorfieldDataPerTagArray[CurrentTagIndex].SetNumZeroed(this->TagLengthArray[CurrentTagIndex]);
				}

				this->SimulationMagnitudeDataPerElectrodePerTagArray[CurrentElectrodeIndex] = SimulationMagnitudeDataPerTagArray;
				this->SimulationVectorfieldDataPerElectrodePerTagArray[CurrentElectrodeIndex] = SimulationVectorfieldDataPerTagArray;
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_SimulationComponent::GetSimulationDataFromJSONObject] Field Electrodes not found."));
		return;
	}

	const TSharedPtr<FJsonObject>* MeshVertexTagCellMappingObjectPtr;
	const TSharedPtr<FJsonObject>* VolumeVertexTagCellMappingObjectPtr;
	bool bMeshVertexTagCellMapping = InJsonObjectPtr->Get()->TryGetObjectField("Mesh_Vertex_Tag_Mapping", MeshVertexTagCellMappingObjectPtr);
	bool bVolumeVertexTagCellMapping = InJsonObjectPtr->Get()->TryGetObjectField("Volume_Vertex_Tag_Mapping", VolumeVertexTagCellMappingObjectPtr);

	if (!bMeshVertexTagCellMapping)
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_SimulationComponent::GetSimulationDataFromJSONObject] Field Mesh_Vertex_Tag_Mapping not found."));
		return;
	}

	if (!bVolumeVertexTagCellMapping)
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_SimulationComponent::GetSimulationDataFromJSONObject] Field Volume_Vertex_Tag_Mapping not found."));
		return;
	}

	for (const auto& Elem : (*VolumeVertexTagCellMappingObjectPtr)->Values)
	{
		const int32 VertexIndex = FCString::Atoi(*Elem.Key);

		const TSharedPtr<FJsonObject>* TagMappingObjectPtr = nullptr;
		if (Elem.Value->TryGetObject(TagMappingObjectPtr))
		{
			TArray<TArray<int32>> CellIndicesPerTagArray;
			CellIndicesPerTagArray.SetNumZeroed(UPT_ConfigManager::GetDataTagIndexArray().Num());

			for (const int32 CurrentTagIndex : UPT_ConfigManager::GetDataTagVolumeIndexArray())
			{
				TArray<int32> VertexArray;
				UPT_JSONConverter::ConvertJSONObjectToIntegerArray(TagMappingObjectPtr, UPT_ConfigManager::GetDataTagArray()[CurrentTagIndex], VertexArray, false);

				CellIndicesPerTagArray[CurrentTagIndex] = VertexArray;
			}
			this->VertexTagCellMapping.Add(VertexIndex, CellIndicesPerTagArray);
			this->VerticesInRoiArray.AddUnique(VertexIndex);
		}
	}

	for (const auto& Elem : (*MeshVertexTagCellMappingObjectPtr)->Values)
	{
		const int32 VertexIndex = FCString::Atoi(*Elem.Key);
		const TSharedPtr<FJsonObject>* TagMappingObjectPtr = nullptr;
		if (Elem.Value->TryGetObject(TagMappingObjectPtr))
		{
			TArray<TArray<int32>> CellIndicesPerTagArray;
			// Prüfen, ob der VertexIndex bereits existiert
			bool bIsVertexIndexPresent = this->VertexTagCellMapping.Contains(VertexIndex);
			if (bIsVertexIndexPresent)
			{
				// Vorhandene TagMap für diesen VertexIndex abrufen
				CellIndicesPerTagArray = this->VertexTagCellMapping[VertexIndex];
			}
			else
			{
				CellIndicesPerTagArray.SetNumZeroed(UPT_ConfigManager::GetDataTagIndexArray().Num());
			}

			for (const int32 CurrentTagIndex : UPT_ConfigManager::GetDataTagMeshIndexArray())
			{
				TArray<int32> VertexArray;
				UPT_JSONConverter::ConvertJSONObjectToIntegerArray(TagMappingObjectPtr, UPT_ConfigManager::GetDataTagArray()[CurrentTagIndex], VertexArray, false);

				CellIndicesPerTagArray[CurrentTagIndex] = VertexArray;
			}

			if (bIsVertexIndexPresent)
			{
				this->VertexTagCellMapping[VertexIndex] = CellIndicesPerTagArray;
			}
			else
			{
				this->VertexTagCellMapping.Add(VertexIndex, CellIndicesPerTagArray);
				this->VerticesInRoiArray.AddUnique(VertexIndex);
			}
		}
	}

}

void UPT_SimulationComponent::ProcessElectrodeData(const TSharedPtr<FJsonObject>* InJsonObjectPtr, const TArray<FString>& InDataTagArray, const int32& InCurrentElectrodeIndex)
{
	const TSharedPtr<FJsonObject>* MagnitudeJsonObjectPtr;
	const TSharedPtr<FJsonObject>* VectorfieldJsonObjectPtr;
	bool bMagnitudeFieldFound = InJsonObjectPtr->Get()->TryGetObjectField("Magnitude", MagnitudeJsonObjectPtr);
	bool bVectorFieldFound = InJsonObjectPtr->Get()->TryGetObjectField("Vectorfield", VectorfieldJsonObjectPtr);

	if (!bMagnitudeFieldFound)
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_SimulationComponent::ProcessElectrodeData] Field Magnitude not found."));
		return;
	}

	if (!bVectorFieldFound)
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_SimulationComponent::ProcessElectrodeData] Field Vectorfield not found."));
		return;
	}

	TArray<TArray<double>> SimulationMagnitudeDataPerTagArray;
	SimulationMagnitudeDataPerTagArray.SetNumZeroed(InDataTagArray.Num());;
	TArray<TArray<FVector>> SimulationVectorfieldDataPerTagArray;
	SimulationVectorfieldDataPerTagArray.SetNumZeroed(InDataTagArray.Num());;

	for (int32 CurrentTagIndex = 0; CurrentTagIndex < InDataTagArray.Num(); CurrentTagIndex++)
	{
		TArray<double> SimulationMagnitudeDataNotMapped;
		TArray<double> SimulationMagnitudeDataMapped;
		SimulationMagnitudeDataMapped.SetNumZeroed(this->TagLengthArray[CurrentTagIndex]);
		UPT_JSONConverter::ConvertJSONObjectToDoubleArray(MagnitudeJsonObjectPtr, InDataTagArray[CurrentTagIndex], SimulationMagnitudeDataNotMapped);

		TArray<FVector> SimulationVectorfieldDataNotMapped;
		TArray<FVector> SimulationVectorfieldDataMapped;
		SimulationVectorfieldDataMapped.SetNumZeroed(this->TagLengthArray[CurrentTagIndex]);
		UPT_JSONConverter::ConvertJSONObjectToVectorArray(VectorfieldJsonObjectPtr, InDataTagArray[CurrentTagIndex], SimulationVectorfieldDataNotMapped);

		for(int32 CurrentCellIndex = 0; CurrentCellIndex < this->RoiIndexMappingPerTagArray[CurrentTagIndex].Num(); CurrentCellIndex++)
		{
			SimulationMagnitudeDataMapped[this->RoiIndexMappingPerTagArray[CurrentTagIndex][CurrentCellIndex]] = SimulationMagnitudeDataNotMapped[CurrentCellIndex];
			SimulationVectorfieldDataMapped[this->RoiIndexMappingPerTagArray[CurrentTagIndex][CurrentCellIndex]] = SimulationVectorfieldDataNotMapped[CurrentCellIndex];
		}

		SimulationMagnitudeDataPerTagArray[CurrentTagIndex] = SimulationMagnitudeDataMapped;
		SimulationVectorfieldDataPerTagArray[CurrentTagIndex] = SimulationVectorfieldDataMapped;

	}

	if (!SimulationMagnitudeDataPerTagArray.IsEmpty())
	{
		this->SimulationMagnitudeDataPerElectrodePerTagArray[InCurrentElectrodeIndex] = SimulationMagnitudeDataPerTagArray;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_SimulationComponent::ProcessResponseForSimulationData] Magnitude Data is empty!"));
		return;
	}

	if (!SimulationVectorfieldDataPerTagArray.IsEmpty())
	{
		this->SimulationVectorfieldDataPerElectrodePerTagArray[InCurrentElectrodeIndex] = SimulationVectorfieldDataPerTagArray;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[UPT_SimulationComponent::ProcessResponseForSimulationData] Vectorfield Data is empty!"));
		return;
	}
}

