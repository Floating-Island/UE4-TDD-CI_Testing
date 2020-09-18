// Fill out your copyright notice in the Description page of Project Settings.


#include "AcceleratingPawnMOCK.h"

bool AAcceleratingPawnMOCK::isMeshTheRootComponent()
{
	return (RootComponent == meshComponent)? true : false;
}

bool AAcceleratingPawnMOCK::hasGravityEnabled()
{
	return meshComponent->IsGravityEnabled();
}

bool AAcceleratingPawnMOCK::isAffectingNavigation()
{
	return meshComponent->CanEverAffectNavigation();
}

bool AAcceleratingPawnMOCK::hasAStaticMeshAssigned()
{
	return meshComponent->GetStaticMesh()? true : false;
}
