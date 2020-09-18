// Fill out your copyright notice in the Description page of Project Settings.


#include "AcceleratingPawn.h"

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

}

bool AAcceleratingPawn::hasAStaticMesh()
{
	return meshComponent? true : false;
}

float AAcceleratingPawn::acceleration()
{
	return accelerationValue;
}

