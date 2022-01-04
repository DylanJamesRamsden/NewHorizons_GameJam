// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Lights/DLightBulb.h"


#include "Kismet/GameplayStatics.h"

// Sets default values
ADLightBulb::ADLightBulb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComp");

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	PointLightComp = CreateDefaultSubobject<UPointLightComponent>("PointLightComp");

	StaticMeshComp->SetupAttachment(RootComponent);
	PointLightComp->SetupAttachment(StaticMeshComp);
}

// Called when the game starts or when spawned
void ADLightBulb::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADLightBulb::RemoveEnergy(int Amount)
{
	CurrentPower = FMath::Clamp(CurrentPower-Amount, 0, StartingPower);

	if (CurrentPower == 0)
	{
		DestroyLight();
	}
}

void ADLightBulb::DestroyLight()
{
	if (DestroyedLight)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(GetActorLocation());
		SpawnTransform.SetRotation(FQuat(GetActorRotation()));

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(DestroyedLight, SpawnTransform, SpawnParams);
	}

	Destroy();
}

// Called every frame
void ADLightBulb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

