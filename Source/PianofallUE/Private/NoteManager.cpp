// Fill out your copyright notice in the Description page of Project Settings.


#include "NoteManager.h"

AStaticMeshActor* SpawnMovableStaticMesh(UWorld* world, UStaticMesh* mesh, FVector& location, FRotator& rotation)
{
	AStaticMeshActor* spawnedNote = world->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
	spawnedNote->SetMobility(EComponentMobility::Movable);
	spawnedNote->SetActorLocation(location);
	spawnedNote->SetActorRotation(rotation);
	UStaticMeshComponent* MeshComponent = spawnedNote->GetStaticMeshComponent();
	if (MeshComponent)
	{
		MeshComponent->SetStaticMesh(mesh);
		MeshComponent->SetMobility(EComponentMobility::Movable);
		MeshComponent->SetSimulatePhysics(true);
	}

	return spawnedNote;
}
