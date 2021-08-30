// Fill out your copyright notice in the Description page of Project Settings.


#include "OneWayTeleport.h"

#include "PersonajeDelJugador.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AOneWayTeleport::AOneWayTeleport()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ComponenteDeEscena = CreateDefaultSubobject<USceneComponent>(TEXT("Componente de escena"));
	RootComponent = ComponenteDeEscena;
	
	CajaDeActivaciones = CreateDefaultSubobject<UBoxComponent>(TEXT("Caja de activaciones"));
	CajaDeActivaciones->SetupAttachment(RootComponent);
	
	MallaEstaticaOrigen = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla estática"));	
	MallaEstaticaOrigen->SetupAttachment(RootComponent);
}


// Called when the game starts or when spawned
void AOneWayTeleport::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AOneWayTeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


/* INTERFAZ */

void AOneWayTeleport::AnteAccion_Implementation(AActor* Caller) 
{
	APersonajeDelJugador* PersonajeDelJugador = Cast<APersonajeDelJugador>(Caller);
	if (PersonajeDelJugador)
	{
		PersonajeDelJugador->SetActorRotation(TeletransportadorDestino->GetActorRotation());
        PersonajeDelJugador->GetController()->SetControlRotation(PersonajeDelJugador->GetActorRotation());
        PersonajeDelJugador->SetActorLocation(TeletransportadorDestino->GetActorLocation());
	}
	if (EfectoDeSonido) {
		FVector EfectoDeSonidoUbicacion = MallaEstaticaOrigen->GetComponentLocation();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), EfectoDeSonido, EfectoDeSonidoUbicacion, FRotator::ZeroRotator);
	}
}