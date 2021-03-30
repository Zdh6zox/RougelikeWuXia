// Fill out your copyright notice in the Description page of Project Settings.


#include "TerrainConstructor.h"
#include "TerrainBase.h"

// Sets default values
ATerrainConstructor::ATerrainConstructor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATerrainConstructor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATerrainConstructor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATerrainConstructor::ConstructTerrain(int rowNum, int columnNum)
{
	//1, 根据地形格数多少以及整体信息来使用 基础地形(预设地形)铺满整个地图
	//2, 根据基础信息来生成高点，坡，坑
	//3. 生成道路或者河流
	//4. 地形根据自身周遭地形改变自身样式
	for (int rowIt = 0;rowIt<rowNum;rowIt++)
	{
		for (int columnIt = 0; columnIt < columnNum; columnNum++)
		{

		}
	}
}

//Test
void ATerrainConstructor::Test_ConstrctTerrain(int rowNum, int columnNum)
{
	ConstructTerrain(rowNum, columnNum);
}

