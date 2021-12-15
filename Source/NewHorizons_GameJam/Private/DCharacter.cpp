// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"

// Sets default values
ADCharacter::ADCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADCharacter::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat TimelineProgressCallback;
	FOnTimelineEventStatic TimelineFinishedCallback;

	TimelineProgressCallback.BindUFunction(this, FName("RotationTimelineProgress"));
	TimelineFinishedCallback.BindUFunction(this, FName("RotationTimelineFinished"));

	CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgressCallback);
	CurveTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);	
}

void ADCharacter::MoveRight(float Value)
{
	AddMovementInput(FVector::RightVector, Value);

	if (Value > 0)
	{
		if (!bIsLookingRight && !bIsRotating)
		{
			CurveTimeline.ReverseFromEnd();
			bIsRotating = true;
		}
	}
	else if (Value < 0)
	{
		if (bIsLookingRight && !bIsRotating)
		{
			CurveTimeline.PlayFromStart();
			bIsRotating = true;
		}
	}
}

void ADCharacter::RotationTimelineProgress(float Value)
{
	SetActorRotation(FRotator(0, CurveFloat->GetFloatValue(CurveTimeline.GetPlaybackPosition()), 0));
}

void ADCharacter::RotationTimelineFinished()
{
	bIsRotating = false;

	if (bIsLookingRight)
	{
		bIsLookingRight = false;
	}
	else bIsLookingRight = true;
}

// Called every frame
void ADCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurveTimeline.IsPlaying())
	{
		CurveTimeline.TickTimeline(DeltaTime);
	}
}

// Called to bind functionality to input
void ADCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &ADCharacter::MoveRight);
}

