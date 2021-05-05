// Fill out your copyright notice in the Description page of Project Settings.


#include "MapData.h"


void UMapData::GatherMapStaticData(FMapDataStatic& staticMapData)
{
	staticMapData.MapNodeCount = Nodes.Num();

	for (UMapNode* node : Nodes)
	{
		staticMapData.NodeStaticArray.Add(node->StaticData);
	}

	for (UMapNodeLink* link : Links)
	{
		staticMapData.NodeLinkStaticArray.Add(link->StaticData);
	}
}