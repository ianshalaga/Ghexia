// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"

#include "PlataformaMovil.generated.h"

UCLASS()
class UE_JUEGO1CPP_API APlataformaMovil : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlataformaMovil();

	/* PROPIEDADES */
	UPROPERTY(EditAnywhere)
	USceneComponent* ComponenteDeEscena;

	UPROPERTY(EditAnywhere, Category = "Malla estática")
	UStaticMeshComponent* MallaEstatica;

	/* FUNCIONES */
	UFUNCTION()
	void TimelineProgreso(float valor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Línea de tiempo")
	UCurveFloat* CurvaFloat;

	FTimeline TimelineCurva;

	UPROPERTY()
	FVector TimelineInicio;

	UPROPERTY(EditAnywhere, Category = "Línea de tiempo")
	AActor* TimelineDestino;

	FVector TimelineFinal;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};