// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"

#include "DFollowCamera.generated.h"

UCLASS()
class NEWHORIZONS_GAMEJAM_API ADFollowCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADFollowCamera();

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY()
	AActor* Target;

	UPROPERTY(EditAnywhere, Category = "FollowParams")
	bool bFollowTarget;
	
	UPROPERTY(EditAnywhere, Category = "FollowParams")
	float FollowSpeed;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void FollowTarget(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetTarget(AActor* TargetActor);
};
