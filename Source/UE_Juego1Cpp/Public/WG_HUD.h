// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_HUD.generated.h"

/**
 * 
 */
UCLASS()
class UE_JUEGO1CPP_API UWG_HUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnItemsChanged(int ItemCounter);

	virtual void NativeOnInitialized() override;
};