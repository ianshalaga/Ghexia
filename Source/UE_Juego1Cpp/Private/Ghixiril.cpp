// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghixiril.h"

#include "PersonajeDelJugador.h"
#include "GS_Nivel1_1.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGhixiril::AGhixiril()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ComponenteDeEscena = CreateDefaultSubobject<USceneComponent>(TEXT("Componente de escena"));
	RootComponent = ComponenteDeEscena;
	CajaDeActivaciones = CreateDefaultSubobject<UBoxComponent>(TEXT("Caja de activaciones"));
	CajaDeActivaciones->SetupAttachment(RootComponent);
	MallaEstatica = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla Estática"));	
	MallaEstatica->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGhixiril::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGhixiril::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(VelocidadDeRotacion * DeltaTime);
}


void AGhixiril::AnteAccion_Implementation(AActor* Caller) 
{
	APersonajeDelJugador* PersonajeDelJugador = Cast<APersonajeDelJugador>(Caller);
	if (PersonajeDelJugador)
	{
		auto* GameState = GetWorld()->GetGameState<AGS_Nivel1_1>();
		GameState->HandleItems();

		if (this->Color == "Red")
		{
			GameState->HandleGhixirilRed();
		}

		if (this->Color == "Green")
		{
			GameState->HandleGhixirilGreen();
		}

		if (this->Color == "Blue")
		{
			GameState->HandleGhixirilBlue();
		}

		if (this->Color == "Cyan")
		{
			GameState->HandleGhixirilCyan();
		}

		if (this->Color == "Magenta")
		{
			GameState->HandleGhixirilMagenta();
		}

		if (this->Color == "Yellow")
		{
			GameState->HandleGhixirilYellow();
		}
		this->Destroy();
	}
	if (EfectoDeSonido) {
		FVector EfectoDeSonidoUbicacion = MallaEstatica->GetComponentLocation();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), EfectoDeSonido, EfectoDeSonidoUbicacion, FRotator::ZeroRotator);
	}
}