// Fill out your copyright notice in the Description page of Project Settings.


#include "PCV_Fuego.h"

#include "PersonajeDelJugador.h"

void APCV_Fuego::CausePainTo(class AActor* Other) 
{
    APersonajeDelJugador* PersonajeDelJugador = Cast<APersonajeDelJugador>(Other);
    if (PersonajeDelJugador)
    {
        PersonajeDelJugador->RecibirDamage(DamagePerSec);
    }
}