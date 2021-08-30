// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SE_Fuego.generated.h"

class USoundBase;

UCLASS()
class UE_JUEGO1CPP_API ASE_Fuego : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASE_Fuego();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// UPROPERTY(EditDefaultOnly, Category = "Efecto de sonido")
	// USoundBase* SE_Fuego;

};
