// Fill out your copyright notice in the Description page of Project Settings.


#include "DFollowCamera.h"

// Sets default values
ADFollowCamera::ADFollowCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("SceneComp");

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void ADFollowCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADFollowCamera::FollowTarget(float DeltaTime)
{
	if (bFollowTarget)
	{
		if (Target)
		{
			SetActorLocation(FMath::InterpEaseOut(GetActorLocation(), Target->GetActorLocation(), FollowSpeed, 1));
		}
	}
}

// Called every frame
void ADFollowCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FollowTarget(DeltaTime);

}

void ADFollowCamera::SetTarget(AActor* TargetActor)
{
	Target = TargetActor;

	SetActorLocation(TargetActor->GetActorLocation());
}

