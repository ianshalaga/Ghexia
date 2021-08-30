// Fill out your copyright notice in the Description page of Project Settings.


#include "EngendrarPotenciador.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AEngendrarPotenciador::AEngendrarPotenciador()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bRegenerando = false;

	UbicacionDeAparicion = CreateDefaultSubobject<USceneComponent>(TEXT("Ubicacion de aparicion"));
	RootComponent = UbicacionDeAparicion;
	CajaDeActivacion = CreateDefaultSubobject<UBoxComponent>(TEXT("Capsula de activacion"));
	CajaDeActivacion->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEngendrarPotenciador::BeginPlay()
{
	Super::BeginPlay();

	CajaDeActivacion->OnComponentBeginOverlap.AddDynamic(this, &AEngendrarPotenciador::EngendrarPotenciadorTiempo);

	EngendrarPotenciador();
}

// Called every frame
void AEngendrarPotenciador::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AEngendrarPotenciador::EngendrarPotenciador() 
{
	FVector Ubicacion = GetActorLocation();
	FRotator Rotacion = GetActorRotation();
	GetWorld()->SpawnActor(Potenciador, &Ubicacion, &Rotacion);
	bRegenerando = false;
	if (EfectoDeSonido) {
		FVector EfectoDeSonidoUbicacion = GetActorLocation();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), EfectoDeSonido, EfectoDeSonidoUbicacion, FRotator::ZeroRotator);
	}
}


void AEngendrarPotenciador::EngendrarPotenciadorTiempo(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	if (OtherActor->ActorHasTag("Jugador") && !bRegenerando)
	{
		bRegenerando = true;
		FTimerHandle Temporizador;
		GetWorldTimerManager().SetTimer(Temporizador, this, &AEngendrarPotenciador::EngendrarPotenciador, TiempoDeReaparicion, false);
	}
}