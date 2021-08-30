// Fill out your copyright notice in the Description page of Project Settings.


#include "WG_HUD.h"

#include "GS_Nivel1_1.h"


void UWG_HUD::NativeOnInitialized() 
{
    Super::NativeOnInitialized();
    auto* GameState = GetWorld()->GetGameState<AGS_Nivel1_1>();
    if (GameState)
    {
        GameState->OnItemsChanged().AddUObject(this, &UWG_HUD::OnItemsChanged);
    }
}