// Fill out your copyright notice in the Description page of Project Settings.


#include "GS_Nivel1_1.h"


// void AGS_Nivel1_1::HandleDeaths() 
// {
// 	DeathsCounter++;
//     DeathsChanged.Broadcast(DeathsCounter);
// }


void AGS_Nivel1_1::HandleItems() 
{
	ItemsCollected++;
    ItemsChanged.Broadcast(ItemsCollected);
}


void AGS_Nivel1_1::HandleGhixirilRed() 
{
	bGhixirilRed = true;
}


void AGS_Nivel1_1::HandleGhixirilGreen() 
{
	bGhixirilGreen = true;
}


void AGS_Nivel1_1::HandleGhixirilBlue() 
{
	bGhixirilBlue = true;
}


void AGS_Nivel1_1::HandleGhixirilCyan() 
{
	bGhixirilCyan = true;
}


void AGS_Nivel1_1::HandleGhixirilMagenta() 
{
	bGhixirilMagenta = true;
}


void AGS_Nivel1_1::HandleGhixirilYellow() 
{
	bGhixirilYellow = true;
}