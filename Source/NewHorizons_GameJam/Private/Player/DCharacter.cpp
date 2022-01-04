// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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

	JumpMaxCount = 2;

	LandedDelegate.AddDynamic(this, &ADCharacter::LandedOnGround);

	//Falling
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

	PlayerInputComponent->BindAction("RunToggle", IE_Pressed, this, &ADCharacter::StartRun);
	PlayerInputComponent->BindAction("RunToggle", IE_Released, this, &ADCharacter::EndRun);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
}

void ADCharacter::StartRun()
{
	bIsRunning = true;
	
	UCharacterMovementComponent* CharacterMovementComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (CharacterMovementComp)
	{
		CharacterMovementComp->MaxWalkSpeed = 250;
	}
}

void ADCharacter::EndRun()
{
	bIsRunning = false;

	UCharacterMovementComponent* CharacterMovementComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (CharacterMovementComp)
	{
		CharacterMovementComp->MaxWalkSpeed = 130;
	}
}

void ADCharacter::Jump()
{
	Super::Jump();

	bIsJumping = true;
}

void ADCharacter::LandedOnGround(const FHitResult& Hit)
{
	bIsJumping = false;

	if (FallParticle)
	{
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FallParticle, FTransform(GetActorLocation()));4 
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FallParticle, Hit.ImpactPoint, FRotator::ZeroRotator, FVector(0.1));
	}
}

