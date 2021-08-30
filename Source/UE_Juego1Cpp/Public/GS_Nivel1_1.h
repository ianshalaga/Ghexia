// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GS_Nivel1_1.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FCounterChanged, int);


UCLASS()
class UE_JUEGO1CPP_API AGS_Nivel1_1 : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	// FCounterChanged& OnDeathChanged() { return DeathsChanged; }
	FCounterChanged& OnItemsChanged() { return ItemsChanged; }

	// void HandleDeaths();
	void HandleItems();

	void HandleGhixirilRed();
	void HandleGhixirilGreen();
	void HandleGhixirilBlue();
	void HandleGhixirilCyan();
	void HandleGhixirilMagenta();
	void HandleGhixirilYellow();

	// int DeathsCounter;
	UPROPERTY(BlueprintReadOnly)
	int ItemsCollected;

protected:
	// FCounterChanged DeathsChanged;
	FCounterChanged ItemsChanged;

	

	UPROPERTY(BlueprintReadOnly)
	bool bGhixirilRed = false;

	UPROPERTY(BlueprintReadOnly)
	bool bGhixirilGreen = false;

	UPROPERTY(BlueprintReadOnly)
	bool bGhixirilBlue = false;

	UPROPERTY(BlueprintReadOnly)
	bool bGhixirilCyan = false;

	UPROPERTY(BlueprintReadOnly)
	bool bGhixirilMagenta = false;
	
	UPROPERTY(BlueprintReadOnly)
	bool bGhixirilYellow = false;
};