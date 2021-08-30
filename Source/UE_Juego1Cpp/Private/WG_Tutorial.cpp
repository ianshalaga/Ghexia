// Fill out your copyright notice in the Description page of Project Settings.


#include "WG_Tutorial.h"

#include "PersonajeDelJugador.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AWG_Tutorial::AWG_Tutorial()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* COMPONENTES */
	ComponenteDeEscena = CreateDefaultSubobject<USceneComponent>(TEXT("Componente de escena"));
	RootComponent = ComponenteDeEscena;

	CajaDeActivaciones = CreateDefaultSubobject<UBoxComponent>(TEXT("Caja de activaciones"));
	CajaDeActivaciones->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWG_Tutorial::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWG_Tutorial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// void AWG_Tutorial::AnteAccion_Implementation(AActor* Caller) 
// {
// 	APersonajeDelJugador* PersonajeDelJugador = Cast<APersonajeDelJugador>(Caller);
// 	if (PersonajeDelJugador)
// 	{
// 		this->Destroy();
// 	}
// }


void AWG_Tutorial::AnteInicioDeSolapamiento_Implementation() 
{
	if (WidgetTutorialClase)
	{
		WidgetTutorial = CreateWidget(GetWorld(), WidgetTutorialClase);
		WidgetTutorial->AddToViewport();
	}
}


void AWG_Tutorial::AnteFinalDeSolapamiento_Implementation() 
{
	if (WidgetTutorialClase)
	{
		WidgetTutorial->RemoveFromViewport();	
	}
}