// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_Nivel1.h"

#include "Blueprint/UserWidget.h"
#include "PersonajeDelJugador.h"
#include "Kismet/GameplayStatics.h"
#include "GS_Nivel1_1.h"


#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Green, String)


AGM_Nivel1::AGM_Nivel1() 
{
	PrimaryActorTick.bCanEverTick = true;

    bTiempoDeJuego = false;
}


void AGM_Nivel1::BeginPlay() 
{
    Super::BeginPlay();

    if (HUD_Clase)
    {
        HUD = CreateWidget(GetWorld(), HUD_Clase);
        HUD->AddToViewport();
        bFreezeTime = true;
    }
}


void AGM_Nivel1::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

    if (bTiempoDeJuego)
    {
        if (TiempoSegundos > 59)
        {
            TiempoSegundos = 0;
            TiempoMinutos++;
        }
        else
        {
            UnSegundo -= DeltaTime;
            if (UnSegundo <= 0)
            {
                UnSegundo = 1.0f;
                TiempoSegundos++;
            }
        }
    }
    else if (bFreezeTime)
    {
        FreezeTime -= DeltaTime;
        if (FreezeTime <= 0)
        {
            bFreezeTime = false;
            bTiempoDeJuego = true;
            APersonajeDelJugador* PersonajeDelJugador = Cast<APersonajeDelJugador>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
            if (PersonajeDelJugador)
            {
                PersonajeDelJugador->bPermitirMovimiento = true;
            }
        }
    }

    // auto* GameState = GetWorld()->GetGameState<AGS_Nivel1_1>();
    // if (GameState)
    // {
    //     if (GameState->ItemsCollected == 6)
    //     {
    //         HUD->RemoveFromViewport();
    //         HUDGameOver = CreateWidget(GetWorld(), HUDGameOverClase);
    //         HUDGameOver->AddToViewport();
    //         bFreezeTime = true;
    //     }
    // }
}