// Fill out your copyright notice in the Description page of Project Settings.


#include "TG_ImpulseRamp.h"

#include "PersonajeDelJugador.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Math/Vector.h"
#include "Kismet/GameplayStatics.h"


/* PREPROCESSOR DIRECTIVES */
#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Green, String)


/* CONSTRUCTOR */
ATG_ImpulseRamp::ATG_ImpulseRamp() 
{
	OnActorBeginOverlap.AddDynamic(this, &ATG_ImpulseRamp::Impulsar);
}


/* FUNCIONES */
void ATG_ImpulseRamp::Impulsar(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		// PrintString("Rampa");
		APersonajeDelJugador* PersonajeDelJugador = Cast<APersonajeDelJugador>(OtherActor);
		FVector Direccion = this->GetActorForwardVector();
		Direccion.Z = 1.0f;
		float multiplicador = 1000.0f;
		// PrintString(Direccion.ToString());
		// PrintString((multiplicador*Direccion).ToString());
		
		PersonajeDelJugador->GetCharacterMovement()->UCharacterMovementComponent::AddImpulse(multiplicador * Direccion, true);
	}
	if (EfectoDeSonido) {
		FVector EfectoDeSonidoUbicacion = GetActorLocation();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), EfectoDeSonido, EfectoDeSonidoUbicacion, FRotator::ZeroRotator);
	}
}