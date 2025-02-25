#include "PT_ConfigurationWidget.h"
#include "PT_ConfigManager.h"

FString UPT_ConfigurationWidget::GetServerRunSimulationsAddress()
{
	return UPT_ConfigManager::GetRunSimulationsAddress();
}
