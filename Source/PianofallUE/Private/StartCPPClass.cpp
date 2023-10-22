#include "StartCPPClass.h"
#include "Utils/Random.h"
#include <string>
#include <sstream>

float SpawnTime = 0.0f;

AStartCPPClass::AStartCPPClass()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AStartCPPClass::BeginPlay()
{
	Super::BeginPlay();
}

void AStartCPPClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (lastNoteSpawnedAgo <= 0.025f)
	{
		lastNoteSpawnedAgo += DeltaTime;
		return;
	}

	UWorld* const StartWorld = GetWorld();

	FVector location = RandomVector(200.0f, 1500.0f, 0.0f);
	location.Z = 500.0f;

	FRotator rotation = RandomRotator();
	
	AStaticMeshActor* spawnedNote = SpawnMovableStaticMesh(GetWorld(), BackgroundNoteToSpawn, location, rotation);

	if (currentNote > MAX_NOTES) currentNote = 0;
	if (notes.IsValidIndex(currentNote) && IsValid(notes[currentNote]))
	{
		notes[currentNote]->Destroy();
		notes[currentNote] = spawnedNote;
	}
	else
	{
		notes.Add(spawnedNote);
	}

	currentNote++;
	lastNoteSpawnedAgo = 0;
}
