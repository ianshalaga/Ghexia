// Fill out your copyright notice in the Description page of Project Settings.


#include "PlataformaTransportadora.h"

#include "PersonajeDelJugador.h"
#include "Kismet/GameplayStatics.h"

#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Blue, String)

// Sets default values
APlataformaTransportadora::APlataformaTransportadora()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bEnMovimiento = false;

	/* COMPONENTES */
	ComponenteDeEscena = CreateDefaultSubobject<USceneComponent>(TEXT("Componente de escena"));
	RootComponent = ComponenteDeEscena;
	MallaEstatica = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla estática"));
	MallaEstatica->SetupAttachment(RootComponent);
	CajaDeActivaciones = CreateDefaultSubobject<UBoxComponent>(TEXT("Caja de activaciones"));
	CajaDeActivaciones->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlataformaTransportadora::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlataformaTransportadora::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimelineCurva.TickTimeline(DeltaTime);
}


void APlataformaTransportadora::TimelineProgreso(float valor) 
{
	FVector SiguienteUbicacion = FMath::Lerp(TimelineInicio, TimelineFinal, valor);
	SetActorLocation(SiguienteUbicacion);
	if (SiguienteUbicacion == TimelineFinal)
	{
		bEnMovimiento = false;
	}
}


void APlataformaTransportadora::AnteAccion_Implementation(AActor* Caller) 
{
	APersonajeDelJugador* PersonajeDelJugador = Cast<APersonajeDelJugador>(Caller);
	if (PersonajeDelJugador)
	{
		if (!bEnMovimiento)
		{
			// PrintString("Plataforma transportadora");
			if (CurvaFloat && TimelineDestino)
			{
				FOnTimelineFloat TimelineProgreso;
				TimelineProgreso.BindUFunction(this, FName("TimelineProgreso"));

				TimelineCurva.AddInterpFloat(CurvaFloat, TimelineProgreso);
				// TimelineCurva.SetLooping(true);

				TimelineInicio = GetActorLocation();
				TimelineFinal = TimelineDestino->GetActorLocation();
				TimelineDestino->SetActorLocation(GetActorLocation());
				TimelineCurva.PlayFromStart();

				bEnMovimiento = true;
			}
		}
	}
	if (EfectoDeSonido) {
		FVector EfectoDeSonidoUbicacion = GetActorLocation();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), EfectoDeSonido, EfectoDeSonidoUbicacion, FRotator::ZeroRotator);
	}
}