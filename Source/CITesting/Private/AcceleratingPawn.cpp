// Fill out your copyright notice in the Description page of Project Settings.


#include "AcceleratingPawn.h"

#include "Components/InputComponent.h"

// Sets default values
AAcceleratingPawn::AAcceleratingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	RootComponent = meshComponent;

	meshComponent->SetSimulatePhysics(true);
	meshComponent->SetEnableGravity(true);
	meshComponent->SetCanEverAffectNavigation(false);

	UStaticMesh* Mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Engine/EditorMeshes/ArcadeEditorSphere")));
	meshComponent->SetStaticMesh(Mesh);

	accelerationValue = 5000.f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;//this should be changed when we start doing multiplayer. It won't work.
}

// Called when the game starts or when spawned
void AAcceleratingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAcceleratingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAcceleratingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("AccelerateAction", IE_Pressed,this,  &AAcceleratingPawn::accelerate);
	PlayerInputComponent->BindAction("AccelerateAction", IE_Repeat,this,  &AAcceleratingPawn::accelerate);

}

bool AAcceleratingPawn::hasAStaticMesh()
{
	return meshComponent? true : false;
}

float AAcceleratingPawn::acceleration()
{
	return accelerationValue;
}

void AAcceleratingPawn::accelerate()
{
	FVector forceToApply = FVector(acceleration(), 0, 0);
	meshComponent->AddForce(forceToApply,NAME_None, true);
}

float AAcceleratingPawn::currentSpeed()
{
	return meshComponent->GetComponentVelocity().X;
}

