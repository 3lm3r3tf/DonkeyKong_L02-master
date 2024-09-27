// Fill out your copyright notice in the Description page of Project Settings.


#include "componentePlataforma.h"

// Sets default values
AcomponentePlataforma::AcomponentePlataforma()
{
    PrimaryActorTick.bCanEverTick = true;

    ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
    meshPlataforma = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    meshPlataforma->SetStaticMesh(MeshAsset.Object);
    RootComponent = meshPlataforma;

    FVector NewScale(2.0f, 2.0f, 0.5f); // Cambia estos valores según tus necesidades
    SetActorScale3D(NewScale);

    // Inicializar variables
    bEsMovil = false;
    Movimiento = FVector(0.0f, 100.0f, 0.0f); // Movimiento en el eje Y
    DireccionMovimiento = FVector(0.0f, 1.0f, 0.0f); // Dirección inicial del movimiento
    LimiteMovimiento = 500.0f; // Limite de movimiento en el eje Y

}

// Called when the game starts or when spawned
void AcomponentePlataforma::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AcomponentePlataforma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (bEsMovil)
    {
        FVector NuevaPosicion = GetActorLocation() + DireccionMovimiento * Movimiento * DeltaTime;
        SetActorLocation(NuevaPosicion);

        // Cambiar dirección si se alcanza el límite
        if (FMath::Abs(GetActorLocation().Y - GetActorLocation().Y) >= LimiteMovimiento)
        {
            DireccionMovimiento *= -1;
        }
    }

}

