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
	//1, ���ݵ��θ��������Լ�������Ϣ��ʹ�� ��������(Ԥ�����)����������ͼ
	//2, ���ݻ�����Ϣ�����ɸߵ㣬�£���
	//3. ���ɵ�·���ߺ���
	//4. ���θ�������������θı�������ʽ
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

