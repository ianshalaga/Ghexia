// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InterfazDeInteraccion.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterfazDeInteraccion : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UE_JUEGO1CPP_API IInterfazDeInteraccion
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// FUNCIONES
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interacciones")
	void AnteAccion(AActor* Caller); // Para acciones del jugador

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interacciones")
	void AnteInicioDeSolapamiento();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interacciones")
	void AnteFinalDeSolapamiento();
};
