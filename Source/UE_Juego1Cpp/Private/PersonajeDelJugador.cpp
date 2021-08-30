// Fill out your copyright notice in the Description page of Project Settings.
// editor win64 development build

/* BIBLIOTECAS */
#include "PersonajeDelJugador.h"

#include "GameFramework/SpringArmComponent.h" // Brazo de la cámara
#include "Camera/CameraComponent.h" // Cámara
#include "Components/CapsuleComponent.h" // Cápsula de colisión
#include "GameFramework/CharacterMovementComponent.h" // Movimiento del personaje
#include "Components/InputComponent.h" // Entradas de usuario
#include "GameFramework/Controller.h" // Mando
#include "Engine.h" // Mensaje de depuración
#include "Potenciador.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GM_Nivel1.h"
#include "OneWayTeleport.h"
#include "Components/StaticMeshComponent.h"
#include "OneWayTeleport.h"

/* PREPROCESSOR DIRECTIVES */
#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Cyan, String)


// Sets default values
APersonajeDelJugador::APersonajeDelJugador() // CONSTRUCTOR
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bJugadorMuerto = false;
	bBotonDeSaltoMantenido = false;
	bPermitirSalto = true;
	bSaltoPotenciado = false;
	bPermitirMovimiento = false;

	TiempoDePotenciadorSalto = 5.0f;
	TiempoDePotenciadorVelocidad = 5.0f;
	// TiempoDeFrutoVenenoso = 2.0f;

	// Tamaño inicial de la cápsula de colisión
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// // set our turn rates for input
	// BaseTurnRate = 45.f;
	// BaseLookUpRate = 45.f;

	// Esto es para impedir que el personaje rote en cualquiera de los tres ejes (X/Roll, Y/Pitch, Z/Yaw).
	// Lo que rotará será la cámara.
	bUseControllerRotationPitch = false; // Sobre el eje Y
	bUseControllerRotationYaw = false; // Sobre el eje Z
	bUseControllerRotationRoll = false; // Sobre el eje X

	// Movimiento del personaje
	GetCharacterMovement()->bOrientRotationToMovement = true; // Permite al personaje rotar en la dirección del movimiento
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // Velocidad de rotación
	GetCharacterMovement()->JumpZVelocity = 600.f; // Velocidad al saltar
	GetCharacterMovement()->AirControl = 0.2f; // Cantidad permitida de control aéreo

	// Brazo de la cámara
	BrazoDeLaCamara = CreateDefaultSubobject<USpringArmComponent>(TEXT("BrazoDeLaCamara"));
	BrazoDeLaCamara->SetupAttachment(RootComponent);
	BrazoDeLaCamara->TargetArmLength = 600.0f; // Longitud del brazo de la cámara
	BrazoDeLaCamara->bUsePawnControlRotation = true; // Será el mando quien controle la rotación de la cámara

	// Cámara de seguimiento
	CamaraDeSeguimiento = CreateDefaultSubobject<UCameraComponent>(TEXT("CamaraDeSeguimiento"));
	CamaraDeSeguimiento->SetupAttachment(BrazoDeLaCamara, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	CamaraDeSeguimiento->bUsePawnControlRotation = false; // No quiero que se mueva la cámara si no solo el brazo que la sostiene

	// Cápsula de activaciones
	CapsulaDeActivacion = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsulaDeActivacion"));
	CapsulaDeActivacion->SetCollisionProfileName(TEXT("Trigger"));
	CapsulaDeActivacion->SetupAttachment(RootComponent);
}


// Called when the game starts or when spawned
void APersonajeDelJugador::BeginPlay()
{
	Super::BeginPlay();

	// CapsulaDeActivacion->OnComponentBeginOverlap.AddDynamic(this, &APersonajeDelJugador::ObtenerPotenciador);

	CapsulaDeActivacion->OnComponentBeginOverlap.AddDynamic(this, &APersonajeDelJugador::AlInicioDelSolapamiento);
	CapsulaDeActivacion->OnComponentEndOverlap.AddDynamic(this, &APersonajeDelJugador::AlFinalDelSolapamiento);

	// PrintString(GetActorLocation().ToString());
}


// Called every frame
void APersonajeDelJugador::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// VidaActual -= DeltaTime;

	if (bSaltoPotenciado)
	{
		if (TiempoDePotenciadorSalto > 0)
		{
			TiempoDePotenciadorSalto -= DeltaTime;
		} else {
			bSaltoPotenciado = false;
			WidgetPotenciadorSalto->RemoveFromViewport();
			TiempoDePotenciadorSalto = 5.0f;
			GetCharacterMovement()->JumpZVelocity = 600.0f;
		}
	}

	if (bVelocidadPotenciada)
	{
		if (TiempoDePotenciadorVelocidad > 0)
		{
			TiempoDePotenciadorVelocidad -= DeltaTime;
		} else {
			bVelocidadPotenciada = false;
			WidgetPotenciadorVelocidad->RemoveFromViewport();
			TiempoDePotenciadorVelocidad = 5.0f;
			GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed / 2;
		}
	}

	// TiempoDeFrutoVenenoso -= DeltaTime;

	if (GetActorLocation().Z <= -300.0f && !bMuerte)
	{
		bMuerte = true;
		RecibirDamage(1.0f);
	}
}


// Called to bind functionality to input
void APersonajeDelJugador::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/* Asociación de ejes */
	PlayerInputComponent->BindAxis("MovimientoAdelanteAtras", this, &APersonajeDelJugador::MovimientoAdelanteAtras);
	PlayerInputComponent->BindAxis("MovimientoDerechaIzquierda", this, &APersonajeDelJugador::MovimientoDerechaIzquierda);
	PlayerInputComponent->BindAxis("MirarArribaAbajo", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("MirarDerechaIzquierda", this, &APawn::AddControllerYawInput);

	/* Asociación de acciones */
	PlayerInputComponent->BindAction("Saltar", IE_Pressed, this, &APersonajeDelJugador::Saltar);
	PlayerInputComponent->BindAction("Saltar", IE_Released, this, &APersonajeDelJugador::DejarDeSaltar);
	PlayerInputComponent->BindAction("Teletransportarse", IE_Pressed, this, &APersonajeDelJugador::UsarTeletransportador);
	PlayerInputComponent->BindAction("Accion", IE_Pressed, this, &APersonajeDelJugador::Accion);
}


void APersonajeDelJugador::MovimientoAdelanteAtras(float Value)
{
	if (bPermitirMovimiento)
	{
		if ((Controller != nullptr) && (Value != 0.0f))
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}	
}


void APersonajeDelJugador::MovimientoDerechaIzquierda(float Value)
{
	if (bPermitirMovimiento)
	{	
		if ( (Controller != nullptr) && (Value != 0.0f) )
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
		
			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value);
		}
	}
}


void APersonajeDelJugador::Saltar()
{
	if (bPermitirMovimiento)
	{
		if (bPermitirSalto)
		{	
			Super::Jump();
			bBotonDeSaltoMantenido = true;
			// PrintString(bBotonDeSaltoMantenido ? TEXT("Salto presionado") : TEXT("Salto liberado"));
		}
	}
}


void APersonajeDelJugador::DejarDeSaltar()
{
	if (bPermitirSalto)
	{
		Super::StopJumping();
		bBotonDeSaltoMantenido = false;
		// PrintString(bBotonDeSaltoMantenido ? TEXT("Salto presionado") : TEXT("Salto liberado"));
	}
	
}


void APersonajeDelJugador::RecibirDamage(float Damage) 
{
	VidaActual -= Damage;
	// if (SE_Muerte) {
	// 		FVector EfectoDeSonidoUbicacion = GetMesh()->GetComponentLocation();
	// 		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SE_Muerte, EfectoDeSonidoUbicacion, FRotator::ZeroRotator);
	// }
	if (SE_Dolor) {
			FVector EfectoDeSonidoUbicacion = GetMesh()->GetComponentLocation();
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SE_Dolor, EfectoDeSonidoUbicacion, FRotator::ZeroRotator);
	}
	if (VidaActual <= 0)
	{
		if (SE_Muerte) {
			FVector EfectoDeSonidoUbicacion = GetMesh()->GetComponentLocation();
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SE_Muerte, EfectoDeSonidoUbicacion, FRotator::ZeroRotator);
		}
		this->GetMesh()->SetSimulatePhysics(true);
		bPermitirMovimiento = false;
		Reaparecer();
	}
}


void APersonajeDelJugador::UsarTeletransportador() 
{
	if (InterfazActual)
	{
		AOneWayTeleport* OneWayTeleport = Cast<AOneWayTeleport>(InterfazActual);
		if (OneWayTeleport)
		{
			IInterfazDeInteraccion::Execute_AnteAccion(Cast<AActor>(InterfazActual), this);
		}
	}	
}


/* INTERFAZ */

void APersonajeDelJugador::Accion() 
{
	if (InterfazActual)
	{
		IInterfazDeInteraccion::Execute_AnteAccion(Cast<AActor>(InterfazActual), this);
	}
}


void APersonajeDelJugador::AlInicioDelSolapamiento(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	/* POTENCIADOR DE SALTO */
	if (OtherActor->ActorHasTag("PotenciadorSalto"))	
	{	
		GetCharacterMovement()->JumpZVelocity = 2000.0f;
		OtherActor->Destroy();

		if (WidgetPotenciadorSaltoClase && !bSaltoPotenciado)
		{
			WidgetPotenciadorSalto = CreateWidget(GetWorld(), WidgetPotenciadorSaltoClase);
			WidgetPotenciadorSalto->AddToViewport();
		}

		bSaltoPotenciado = true;
		TiempoDePotenciadorSalto = 5.0f;

		// PrintString("Potenciador obtenido");
	}

	/* POTENCIADOR DE VELOCIDAD */
	if (OtherActor->ActorHasTag("PotenciadorVelocidad"))	
	{	
		GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed * 2;
		OtherActor->Destroy();

		if (WidgetPotenciadorVelocidadClase && !bVelocidadPotenciada)
		{
			WidgetPotenciadorVelocidad = CreateWidget(GetWorld(), WidgetPotenciadorVelocidadClase);
			WidgetPotenciadorVelocidad->AddToViewport();
		}

		bVelocidadPotenciada = true;
		TiempoDePotenciadorVelocidad = 5.0f;

		// PrintString("Potenciador obtenido");
	}

	/* FRUTO VENENOSO */
	if (OtherActor->ActorHasTag("FrutoVenenoso"))	
	{	
		RecibirDamage(0.2);
		OtherActor->Destroy();
		// TiempoDeFrutoVenenoso = 2.0f;
	}

	/* TELETRANSPORTADOR */
	AOneWayTeleport* OneWayTeleport = Cast<AOneWayTeleport>(OtherActor);
	if (OneWayTeleport)
	{
		bPermitirSalto = false;
	}

	/* ACCIONES */
	IInterfazDeInteraccion* InterfazDeInteraccion = Cast<IInterfazDeInteraccion>(OtherActor);
	if (InterfazDeInteraccion)
	{
		IInterfazDeInteraccion::Execute_AnteInicioDeSolapamiento(OtherActor);
		InterfazActual = InterfazDeInteraccion;
	}
}


void APersonajeDelJugador::AlFinalDelSolapamiento(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	AOneWayTeleport* OneWayTeleport = Cast<AOneWayTeleport>(OtherActor);
	if (OneWayTeleport)
	{
		bPermitirSalto = true;
	}

	IInterfazDeInteraccion* InterfazDeInteraccion = Cast<IInterfazDeInteraccion>(OtherActor);
	if (InterfazDeInteraccion)
	{
		IInterfazDeInteraccion::Execute_AnteFinalDeSolapamiento(OtherActor);
		InterfazActual = nullptr;
	}
}


// Ghexia (Se lee Guexia)
// Ghixirils (Se lee Guixirils)