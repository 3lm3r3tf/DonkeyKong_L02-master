// Fill out your copyright notice in the Description page of Project Settings.


#include "MoverPlataforma.h"

// Sets default values
AMoverPlataforma::AMoverPlataforma()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//
	MovementSpeed = 100.0f;
	MovementRange = 500.0f;
	bMovingForward = true;

}

// Called when the game starts or when spawned
void AMoverPlataforma::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

// Called every frame
void AMoverPlataforma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = CurrentLocation + (MovementDirection * MovementSpeed * DeltaTime);

	if (FVector::Dist(StartLocation, NewLocation) >= MovementRange)
	{
		bMovingForward = !bMovingForward;
		MovementDirection *= -1;
	}

	SetActorLocation(NewLocation);

}

