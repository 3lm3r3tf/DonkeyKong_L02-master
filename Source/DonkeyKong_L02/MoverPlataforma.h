// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoverPlataforma.generated.h"

UCLASS()
class DONKEYKONG_L02_API AMoverPlataforma : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoverPlataforma();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
   
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    FVector MovementDirection;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MovementSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MovementRange;

private:
    FVector StartLocation;
    bool bMovingForward;

};
