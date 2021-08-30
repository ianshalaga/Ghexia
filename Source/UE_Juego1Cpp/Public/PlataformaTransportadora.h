// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "InterfazDeInteraccion.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"

#include "PlataformaTransportadora.generated.h"

class UBaseSound;

UCLASS()
class UE_JUEGO1CPP_API APlataformaTransportadora : public AActor, public IInterfazDeInteraccion
{
	GENERATED_BODY()

	/* VARIABLES */
	bool bEnMovimiento;

public:	
	// Sets default values for this actor's properties
	APlataformaTransportadora();

	/* PROPIEDADES */
	UPROPERTY(EditAnywhere, Category = "Componentes")
	USceneComponent* ComponenteDeEscena;

	UPROPERTY(EditAnywhere, Category = "Componentes")
	UStaticMeshComponent* MallaEstatica;

	UPROPERTY(EditAnywhere, Category = "Componentes")
	UBoxComponent* CajaDeActivaciones;

	UPROPERTY(EditAnywhere, Category = "Efecto de sonido")
	USoundBase* EfectoDeSonido;

	/* FUNCIONES */
	UFUNCTION()
	void TimelineProgreso(float valor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimeline TimelineCurva;
	UPROPERTY(EditAnywhere, Category = "Línea de tiempo")
	UCurveFloat* CurvaFloat;

	/* PROPIEDADES */
	UPROPERTY()
	FVector TimelineInicio;

	UPROPERTY(EditAnywhere, Category = "Línea de tiempo")
	AActor* TimelineDestino;

	FVector TimelineFinal;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* INTERFAZ */
	void AnteAccion(AActor* Caller);
	virtual void AnteAccion_Implementation(AActor* Caller) override;

	void AnteInicioDeSolapamiento();

	void AnteFinalDeSolapamiento();
};