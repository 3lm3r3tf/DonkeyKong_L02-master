// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong_L02GameMode.h"
#include "DonkeyKong_L02Character.h"
#include "UObject/ConstructorHelpers.h"
#include "ObstaculoMuro.h"
#include "Capsula.h"
#include "componentePlataforma.h"
#include "Barril.h"
#include "Esfera.h"

ADonkeyKong_L02GameMode::ADonkeyKong_L02GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ADonkeyKong_L02GameMode::BeginPlay()
{
    Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, TEXT("Creando plataf0.orma"));
	// Spawn an instance of the AMyFirstActor class at the
	//default location.
	FTransform SpawnLocation;
	SpawnLocation.SetLocation(FVector(1160.0f, -210.0f, 140.0f));
	SpawnLocation.SetRotation(FQuat(FRotator(0.0f, 0.0f, 0.0f)));
	obstaculo01 = GetWorld()->SpawnActor<AObstaculoMuro>(AObstaculoMuro::StaticClass(), SpawnLocation);
	/*if (player01 != nullptr)
	{
		player01->SetObstaculo(obstaculo01);
	}*/

	//FVector posicionInicial(1160.0f, -1100.0f, 400.f);
	//FRotator rotacionInicial(0.0f, 0.0f, 10.0f);
	//float anchoComponentePlataforma = 600.0f;
	//float incrementoAltoComponentePlataforma = -105.0f;
	//float incrementoAltoEntrePisos = 800.0f;
	//float incrementoInicioPiso = 100.0f;
	// Posición y rotación inicial
	FVector posicionInicial(1160.0f, -1100.0f, 400.0f);
	FRotator rotacionInicial(0.0f, 0.0f, 10.0f);

	// Parámetros ajustados
	float anchoPlataforma = 200.0f;
	float ajusteAlturaPlataforma = -40.0f;
	float ajusteAlturaEntrePisos = 800.0f;
	float ajusteLateralPiso = 50.0f;

	for (int piso = 0; piso < 5; piso++) {
		// Alterna inclinación y desplazamiento lateral entre pisos
		rotacionInicial.Roll *= -1;
		ajusteLateralPiso *= -1;
		ajusteAlturaPlataforma *= -1;

		for (int plataforma = 0; plataforma < 10; plataforma++) {
			// Calcula la posición de la plataforma actual
			FVector posicionPlataforma = posicionInicial + FVector(0, anchoPlataforma * plataforma, 0);
			FTransform transformPlataforma(rotacionInicial, posicionPlataforma);

			// Crea la plataforma
			componentesPlataforma.Add(GetWorld()->SpawnActor<AcomponentePlataforma>(AcomponentePlataforma::StaticClass(), transformPlataforma));

			// Ajusta la altura si no es la última plataforma
			if (plataforma < 9) {
				posicionInicial.Z += ajusteAlturaPlataforma;
			}
		}

		// Ajusta la altura y el desplazamiento lateral para el siguiente piso
		posicionInicial.Z += ajusteAlturaEntrePisos;
		posicionInicial.Y += ajusteLateralPiso;
	}

	//for (int npp = 0; npp < 5; npp++) {
	//	rotacionInicial.Roll *= -1;
	//	incrementoInicioPiso *= -1;
	//	incrementoAltoComponentePlataforma *= -1;

	//	for (int ncp = 0; ncp < 5; ncp++) {
	//		FVector posicionPlataforma = posicionInicial + FVector(0.0f, anchoComponentePlataforma * ncp, 0.0f);
	//		FTransform SpawnLocationCP(rotacionInicial, posicionPlataforma);
	//		AcomponentePlataforma* NuevaPlataforma = GetWorld()->SpawnActor<AcomponentePlataforma>(AcomponentePlataforma::StaticClass(), SpawnLocationCP);

	//		// Configurar la plataforma como móvil o estática
	//		if (ncp == 0 || ncp == 4) {
	//			NuevaPlataforma->bEsMovil = false; // Plataformas estáticas en las posiciones inicial y final
	//		}
	//		else {
	//			NuevaPlataforma->bEsMovil = true; // Plataformas móviles en las posiciones intermedias
	//		}

	//		componentesPlataforma.Add(NuevaPlataforma);

	//		if (ncp < 4) {
	//			posicionInicial.Z += incrementoAltoComponentePlataforma;
	//		}
	//	}

	//	posicionInicial.Z += incrementoAltoEntrePisos;
	//	posicionInicial.Y += incrementoInicioPiso;
	//}

	GetWorld()->GetTimerManager().SetTimer(SpawnBarrilTimerHandle, this, &ADonkeyKong_L02GameMode::SpawnBarril, 3.0f, true);
	
	//Crear una esfera en la parte superior del primer piso que baje rebotando hasta llegar al suelo
	
	for (int nes = 0; nes < 5; nes++) {
		FTransform SpawnLocationEsfera;
		SpawnLocationEsfera.SetLocation(FVector(1300.0f, -200.0f, 1060.0f));
		SpawnLocationEsfera.SetRotation(FQuat(FRotator(0.0f, 0.0f, 0.0f)));
		esferasMap.Add(nes, GetWorld()->SpawnActor<AEsfera>(AEsfera::StaticClass(), SpawnLocationEsfera));
	}
}

void ADonkeyKong_L02GameMode::SpawnBarril()
{
	//if (barriles.Num() >= numeroMaximoBarriles) {
	if (contadorBarriles < numeroMaximoBarriles) {
		//Spawn de un objeto barril en la escena sobre la primera plataforma
		FTransform SpawnLocationBarril;
		SpawnLocationBarril.SetLocation(FVector(1160.0f, 900.0f, 860.0f));
		SpawnLocationBarril.SetRotation(FQuat(FRotator(90.0f, 0.0f, 0.0f)));
		//ABarril* barril01 = GetWorld()->SpawnActor<ABarril>(ABarril::StaticClass(), SpawnLocationBarril);
		barriles.Add(GetWorld()->SpawnActor<ABarril>(ABarril::StaticClass(), SpawnLocationBarril));
		contadorBarriles++;

		if (contadorBarriles >= numeroMaximoBarriles) {
			GetWorld()->GetTimerManager().ClearTimer(SpawnBarrilTimerHandle);
		}
	}
}
