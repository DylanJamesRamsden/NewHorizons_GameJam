// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DDestroyedLight.generated.h"

UCLASS()
class NEWHORIZONS_GAMEJAM_API ADDestroyedLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADDestroyedLight();

protected:

	//UPROPERTY(VisibleAnywhere)
	//UGeometryCollectionComponent* GeometryCollectionComp;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
