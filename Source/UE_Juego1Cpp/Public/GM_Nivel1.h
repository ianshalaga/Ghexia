// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GM_Nivel1.generated.h"

/**
 * 
 */
UCLASS()
class UE_JUEGO1CPP_API AGM_Nivel1 : public AGameMode
{
	GENERATED_BODY()

public:
	/* CONSTRUCTOR */
	AGM_Nivel1();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ReiniciarNivel();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void GameOver();

	float TiempoDeReinicio = 2.0f;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> HUD_Clase;
	UUserWidget* HUD;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> HUDGameOverClase;
	UUserWidget* HUDGameOver; // Objeto

	bool bFreezeTime;
	bool bTiempoDeJuego;

	UPROPERTY(BlueprintReadOnly)
	float FreezeTime = 4.0f;

	UPROPERTY(BlueprintReadOnly)
	int TiempoSegundos = 0;
	UPROPERTY(BlueprintReadOnly)
	int TiempoMinutos = 0;

	float UnSegundo = 1.0f;
};