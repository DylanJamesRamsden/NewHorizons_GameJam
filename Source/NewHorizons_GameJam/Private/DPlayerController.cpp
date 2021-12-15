// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerController.h"

#include "DFollowCamera.h"
#include "Kismet/GameplayStatics.h"

ADPlayerController::ADPlayerController()
{
	
}

void ADPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ADFollowCamera::StaticClass());

	if (FoundActor)
	{
		SetViewTargetWithBlend(FoundActor, 0);

		ADFollowCamera* FollowCamera = Cast<ADFollowCamera>(FoundActor);
		FollowCamera->SetTarget(GetPawn());
	}
}
