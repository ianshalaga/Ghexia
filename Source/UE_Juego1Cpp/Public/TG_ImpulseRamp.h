// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"

#include "TG_ImpulseRamp.generated.h"

class USoundBase;

/**
 * 
 */
UCLASS()
class UE_JUEGO1CPP_API ATG_ImpulseRamp : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	/* CONSTRUCTOR */
	ATG_ImpulseRamp();

	UPROPERTY(EditAnywhere, Category = "Efecto de sonido")
	USoundBase* EfectoDeSonido;

// protected:

private:
	/* FUNCIONES */
	UFUNCTION()
	void Impulsar(AActor* OverlappedActor, AActor* OtherActor);

	/* PROPIEDADES */
	UPROPERTY(EditAnywhere, Category = "Impulso")
	float FuerzaDelImpulso = 50.0f;
};