// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/CapsuleComponent.h"
#include "InterfazDeInteraccion.h"
#include "GM_Nivel1.h"
#include "EngendrarPotenciador.h"

#include "PersonajeDelJugador.generated.h"

class USoundBase;

UCLASS()
class UE_JUEGO1CPP_API APersonajeDelJugador : public ACharacter, public IInterfazDeInteraccion
{
	/* PRIVATE */
	GENERATED_BODY()

	/* PROPIEDADES */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* BrazoDeLaCamara;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CamaraDeSeguimiento;

	UPROPERTY(EditAnywhere, Category = "Efecto de sonido")
	USoundBase* SE_Muerte;

	UPROPERTY(EditAnywhere, Category = "Efecto de sonido")
	USoundBase* SE_Dolor;

	bool bMuerte = false;

public:
	/* CONSTRUCTOR */
	APersonajeDelJugador();

	/* PROPIEDADES */
	UPROPERTY(EditAnywhere, Category = "Cápsula de activaciones")
	UCapsuleComponent* CapsulaDeActivacion;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* ACCIONES */
	void MovimientoAdelanteAtras(float Value);
	void MovimientoDerechaIzquierda(float Value);
	void Saltar();
	void DejarDeSaltar();

	bool bJugadorMuerto;
	
	/* FUNCIONES */
	UFUNCTION()
	void UsarTeletransportador();

	UFUNCTION()
	void Accion();

	UFUNCTION()
	void AlInicioDelSolapamiento(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void AlFinalDelSolapamiento(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* FUNCIONES */
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return BrazoDeLaCamara; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return CamaraDeSeguimiento; }

	void RecibirDamage(float Damage);

	UFUNCTION(BlueprintImplementableEvent)
	void Reaparecer();

	/* PROPIEDADES */
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> WidgetPotenciadorSaltoClase;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> WidgetPotenciadorVelocidadClase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TiempoDePotenciadorSalto;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TiempoDePotenciadorVelocidad;

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	// float TiempoDeFrutoVenenoso;

	UPROPERTY(BlueprintReadOnly)
	float VidaActual = 1.0f;

	/* VARIABLES */
	UUserWidget* WidgetPotenciadorSalto;
	UUserWidget* WidgetPotenciadorVelocidad;

	bool bSaltoPotenciado;
	bool bVelocidadPotenciada;

	bool bBotonDeSaltoMantenido;
	bool bPermitirSalto;

	bool bPermitirMovimiento;

	IInterfazDeInteraccion* InterfazActual;
};
