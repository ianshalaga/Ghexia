// Fill out your copyright notice in the Description page of Project Settings.


#include "PlataformaMovil.h"


// Sets default values
APlataformaMovil::APlataformaMovil()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* COMPONENTES */
	ComponenteDeEscena = CreateDefaultSubobject<USceneComponent>(TEXT("Componente de escena"));
	RootComponent = ComponenteDeEscena;
	MallaEstatica = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla estática"));
	MallaEstatica->SetupAttachment(RootComponent);
}


// Called when the game starts or when spawned
void APlataformaMovil::BeginPlay()
{
	Super::BeginPlay();
	
	if (CurvaFloat && TimelineDestino)
	{
		FOnTimelineFloat TimelineProgreso;
		TimelineProgreso.BindUFunction(this, FName("TimelineProgreso"));

		TimelineCurva.AddInterpFloat(CurvaFloat, TimelineProgreso);
		TimelineCurva.SetLooping(true);

		TimelineInicio = GetActorLocation();
		TimelineFinal = TimelineDestino->GetActorLocation();
		TimelineDestino->SetActorLocation(GetActorLocation());
		TimelineCurva.PlayFromStart();
	}
}


// Called every frame
void APlataformaMovil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimelineCurva.TickTimeline(DeltaTime);
}


void APlataformaMovil::TimelineProgreso(float valor) 
{
	FVector SiguienteUbicacion = FMath::Lerp(TimelineInicio, TimelineFinal, valor);
	SetActorLocation(SiguienteUbicacion);
}