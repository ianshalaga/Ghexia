// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "InterfazDeInteraccion.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"

#include "WG_Tutorial.generated.h"

UCLASS()
class UE_JUEGO1CPP_API AWG_Tutorial : public AActor, public IInterfazDeInteraccion
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWG_Tutorial();

	UPROPERTY(EditAnywhere)
	USceneComponent* ComponenteDeEscena;

	UPROPERTY(EditAnywhere)
	UBoxComponent* CajaDeActivaciones;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> WidgetTutorialClase; // Clase
	UUserWidget* WidgetTutorial; // Objeto

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* INTERFAZ */
	void AnteAccion(AActor* Caller);
	// virtual void AnteAccion_Implementation(AActor* Caller) override;

	void AnteInicioDeSolapamiento();
	virtual void AnteInicioDeSolapamiento_Implementation() override;

	void AnteFinalDeSolapamiento();
	virtual void AnteFinalDeSolapamiento_Implementation() override;
};