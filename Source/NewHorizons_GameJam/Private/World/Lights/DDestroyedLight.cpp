// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Lights/DDestroyedLight.h"

// Sets default values
ADDestroyedLight::ADDestroyedLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//GeometryCollectionComp = CreateDefaultSubobject<UGeometryCollectionComponent>("GeometryCollectionComp");
}

// Called when the game starts or when spawned
void ADDestroyedLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADDestroyedLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

