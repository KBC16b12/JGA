#include "stdafx.h"
#include "Map.h"
#include "MapChip.h"

namespace
{
	std::vector<SMapInfo> map_dat =
	{
#include "../Map/MapData/"
	};
}

Map::Map()
{
}

Map::~Map()
{
}

bool Map::Start()
{
	return true;
}

void Map::Update()
{

}

void Map::PostRender(CRenderContext& renderContext)
{

}