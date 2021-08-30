// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "InterfazDeInteraccion.h"

#include "Ghixiril.generated.h"

class USoundBase;

UCLASS()
class UE_JUEGO1CPP_API AGhixiril : public AActor, public IInterfazDeInteraccion
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGhixiril();

	/* PROPIEDADES */
	UPROPERTY(EditAnyWhere)
	USceneComponent* ComponenteDeEscena;

	UPROPERTY(EditAnyWhere, Category = "Malla estática")
	UStaticMeshComponent* MallaEstatica;

	UPROPERTY(EditAnyWhere)
	UBoxComponent* CajaDeActivaciones;

	UPROPERTY(EditAnyWhere, Category = "Rotación local")
	FRotator VelocidadDeRotacion = FRotator(0.0f, 90.0f, 0.0f);

	UPROPERTY(EditAnyWhere)
	FString Color;

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