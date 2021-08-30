// Fill out your copyright notice in the Description page of Project Settings.


#include "Potenciador.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APotenciador::APotenciador()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// TiempoDeAparicion = 5.0f;

	ComponenteDeEscena = CreateDefaultSubobject<USceneComponent>(TEXT("Componente de escena"));
	RootComponent = ComponenteDeEscena;
	CajaDeActivaciones = CreateDefaultSubobject<UBoxComponent>(TEXT("Caja de activaciones"));
	CajaDeActivaciones->SetupAttachment(RootComponent);
	MallaEstatica = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla Estática"));	
	MallaEstatica->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APotenciador::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APotenciador::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetActorLocation().Z <= -300.0f)
	{
		this->Destroy();
	}
}