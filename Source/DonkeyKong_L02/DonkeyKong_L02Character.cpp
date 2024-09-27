// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong_L02Character.h"
#include "Proyectil.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "componentePlataforma.h"



#include "Obstaculo.h"
#include "DonkeyKong_L02GameMode.h"


ADonkeyKong_L02Character::ADonkeyKong_L02Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	VelocidadNormal = 600.f;
	VelocidadCorrer = 1200.f;
	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 1500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1500.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ADonkeyKong_L02Character::Disparar()
{
	if (ProyectilClass)
	{
		FVector MuzzleLocation = GetActorLocation() + FTransform(GetControlRotation()).TransformVector(FVector(100.0f, 0.0f, 50.0f));
		FRotator MuzzleRotation = GetControlRotation();
		UWorld* World = GetWorld();
		if (World)
		{
			World->SpawnActor<AProyectil>(ProyectilClass, MuzzleLocation, MuzzleRotation);
		}
	}
}

void ADonkeyKong_L02Character::EmpezarCorrer()
{
	GetCharacterMovement()->MaxWalkSpeed = VelocidadCorrer;

}

void ADonkeyKong_L02Character::DejarCorrer()
{
	GetCharacterMovement()->MaxWalkSpeed = VelocidadNormal;
}

void ADonkeyKong_L02Character::MoverAUltimaPlataforma()
{

	ADonkeyKong_L02GameMode* GameMode = Cast<ADonkeyKong_L02GameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode && GameMode->componentesPlataforma.Num() > 0)
	{
		AActor* UltimaPlataforma = GameMode->componentesPlataforma.Last();
		if (UltimaPlataforma)
		{
			FVector NuevaPosicion = UltimaPlataforma->GetActorLocation();
			SetActorLocation(NuevaPosicion);
		}
	}
}

void ADonkeyKong_L02Character::BeginPlay()
{
	Super::BeginPlay();

	// Llama a la funci�n para mover el personaje a la �ltima plataforma
	MoverAUltimaPlataforma();

}

void ADonkeyKong_L02Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADonkeyKong_L02Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADonkeyKong_L02Character::MoveRight);
	//PlayerInputComponent->BindAction("Parar", IE_Pressed, this, &ADonkeyKong_L01Character::Parar);
	//PlayerInputComponent->BindAction("Parar", IE_Released, this, &ADonkeyKong_L01Character::Parar);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADonkeyKong_L02Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADonkeyKong_L02Character::TouchStopped);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Disparar", IE_Pressed, this, &ADonkeyKong_L02Character::Disparar);		
	PlayerInputComponent->BindAction("Correr", IE_Pressed, this, &ADonkeyKong_L02Character::EmpezarCorrer);
	PlayerInputComponent->BindAction("Correr", IE_Released, this, &ADonkeyKong_L02Character::DejarCorrer);

	/*PlayerInputComponent->BindAction("Disparar", IE_Pressed, this, &ADonkeyKong_L02Character::Disparar);*/
}

void ADonkeyKong_L02Character::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void ADonkeyKong_L02Character::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ADonkeyKong_L02Character::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void ADonkeyKong_L02Character::Parar()
{
	//obstaculo01->setIncrementoZ(0.0f);
	detener = !detener;
	obstaculo01->setDetener(detener);
}

