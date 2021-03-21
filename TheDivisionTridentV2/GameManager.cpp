#include "GameManager.h"


TheDivisionSDK::Snowdrop::IndexModule::IndexInfo  TheDivisionSDK::Snowdrop::IndexModule::IndexInfo::s_Instance;

bool TheDivisionSDK::Snowdrop::IndexModule::IndexInfo::GetAttribute(int index, uint32_t& Index)
{
	TheDivisionSDK::Snowdrop::IndexModule::IndexModuleClass* indexModule = TheDivisionSDK::Snowdrop::IndexModule::IndexModuleClass::Get();
	for (int i = 0; i < 488; i++)
	{
		if (i != index) continue;
		Index = indexModule->IndexList->Indices[i]->Index;
		return true;
	}
	return false;
};