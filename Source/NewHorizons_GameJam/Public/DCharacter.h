// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "DCharacter.generated.h"

UCLASS()
class NEWHORIZONS_GAMEJAM_API ADCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADCharacter();

protected:
	FTimeline CurveTimeline;

	UPROPERTY(EditAnywhere, Category = "Rotation Timeline")
	UCurveFloat* CurveFloat;

	bool bIsRotating = false;

	bool bIsLookingRight = true;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveRight(float Value);
	
	UFUNCTION()
	void RotationTimelineProgress(float Value);

	UFUNCTION()
	void RotationTimelineFinished();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
