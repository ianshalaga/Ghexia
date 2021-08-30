// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Potenciador.generated.h"

class USOundBase;

UCLASS()
class UE_JUEGO1CPP_API APotenciador : public AActor
{
	GENERATED_BODY()
	
	/* VARIABLES */
	// FVector UbicacionDeAparicion;
	// FRotator RotacionDeAparicion;
	// float TiempoDeAparicion;

public:	
	/* CONSTRUCTOR */
	APotenciador();

	/* PROPIEDADES */
	UPROPERTY(EditAnyWhere)
	USceneComponent* ComponenteDeEscena;

	UPROPERTY(EditAnyWhere, Category = "Malla estática")
	UStaticMeshComponent* MallaEstatica;

	UPROPERTY(EditAnyWhere)
	UBoxComponent* CajaDeActivaciones;

	UPROPERTY(EditAnywhere, Category = "Efecto de sonido")
	USoundBase* EfectoDeSonido;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};