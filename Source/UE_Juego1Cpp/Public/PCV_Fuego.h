// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PainCausingVolume.h"
#include "PCV_Fuego.generated.h"

class USoundBase;

/**
 * 
 */
UCLASS()
class UE_JUEGO1CPP_API APCV_Fuego : public APainCausingVolume
{
	GENERATED_BODY()
	
protected:
	virtual void CausePainTo(class AActor* Other) override;

	// UPROPERTY(EditDefaultOnly, Category = "Efecto de sonido")
	// USoundBase* SE_Fuego;
};