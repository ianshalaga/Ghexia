// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Potenciador.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "InterfazDeInteraccion.h"

#include "EngendrarPotenciador.generated.h"

class USoundBase;

UCLASS()
class UE_JUEGO1CPP_API AEngendrarPotenciador : public AActor
{
	GENERATED_BODY()

	/* VARIABLES */
	bool bRegenerando;

public:	
	// Sets default values for this actor's properties
	AEngendrarPotenciador();

	/* PROPIEDADES */
	UPROPERTY(EditAnywhere, Category = "Potenciador")
	TSubclassOf<APotenciador> Potenciador;

	UPROPERTY(EditAnywhere)
	USceneComponent* UbicacionDeAparicion; // Lugar de aparición y reaparición del potenciador

	UPROPERTY(EditAnywhere)
	UBoxComponent* CajaDeActivacion;

	UPROPERTY(EditAnywhere, Category = "Potenciador")
	float TiempoDeReaparicion;

	UPROPERTY(EditAnywhere, Category = "Efecto de sonido")
	USoundBase* EfectoDeSonido;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* FUNCIONES */
	UFUNCTION()
	void EngendrarPotenciador();

	UFUNCTION()
	void EngendrarPotenciadorTiempo(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};