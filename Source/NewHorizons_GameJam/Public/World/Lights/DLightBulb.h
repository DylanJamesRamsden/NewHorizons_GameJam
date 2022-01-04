// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "DLightBulb.generated.h"

UCLASS()
class NEWHORIZONS_GAMEJAM_API ADLightBulb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADLightBulb();

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;
	
	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* PointLightComp;

	UPROPERTY(EditAnywhere)
	int StartingPower;

	UPROPERTY()
	int CurrentPower;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> DestroyedLight;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void RemoveEnergy(int Amount);

	void DestroyLight();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
