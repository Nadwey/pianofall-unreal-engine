// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Engine/StaticMeshActor.h>

/// <summary>
/// Spawns a static mesh with movable mobility
/// </summary>
/// <param name="world">World to spawn mesh in</param>
/// <param name="mesh">Mesh to spawn</param>
/// <param name="location">Location of the mesh to spawn</param>
/// <param name="rotation">Rotation of the mesh to spawn</param>
/// <returns>The static mesh actor reference</returns>
AStaticMeshActor* SpawnMovableStaticMesh(UWorld* world, UStaticMesh* mesh, FVector& location, FRotator& rotation);
