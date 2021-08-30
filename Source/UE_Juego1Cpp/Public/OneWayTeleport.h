// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "InterfazDeInteraccion.h"

#include "OneWayTeleport.generated.h"

class USoundBase;

UCLASS()
class UE_JUEGO1CPP_API AOneWayTeleport : public AActor, public IInterfazDeInteraccion
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOneWayTeleport();

	/* PROPIEDADES */
	UPROPERTY(EditAnyWhere)
	USceneComponent* ComponenteDeEscena;

	UPROPERTY(EditAnyWhere)
	UBoxComponent* CajaDeActivaciones;

	UPROPERTY(EditAnyWhere, Category = "Malla estática")
	UStaticMeshComponent* MallaEstaticaOrigen;

	UPROPERTY(EditAnyWhere, Category = "Teletransportador destino")
	AActor* TeletransportadorDestino;

	UPROPERTY(EditAnywhere, Category = "Efecto de sonido")
	USoundBase* EfectoDeSonido;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* INTERFAZ */
	void AnteAccion(AActor* Caller);
	virtual void AnteAccion_Implementation(AActor* Caller) override;

	void AnteInicioDeSolapamiento();
	void AnteFinalDeSolapamiento();
};