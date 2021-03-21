#include"includes.h"

CIndexInfo CIndexInfo::s_Instance;

bool CIndexInfo::GetAttribute(int index, uint32_t& Index)
{
	CIndexModule* indexModule = CIndexModule::Get();
	for (int i = 0; i < 488; i++)
	{
		/*if ((indexModule->IndexList->Indices[i]->Flag & 0x1000000) != 0)
		{
			if (i != index) continue;
			//if (strcmp(indexModule->IndexList->Indices[i]->Name, pName) != 0) continue;
			Index = indexModule->IndexList->Indices[i]->Index;
			return true;
		}
		*/
		if (i != index) continue;
		Index = indexModule->IndexList->Indices[i]->Index;
		return true;
	}
	return false;
};

uintptr_t IndexModule::Indexer::GetOffset()
{
	return index < 6;
}

std::string IndexModule::Indexer::GetName()
{
	return IsPointerName() ? namePtr : (char*)&namePtr;
}

bool IndexModule::Indexer::IsPointerName()
{
	return (flags & 0x1000000) != 0;
}
