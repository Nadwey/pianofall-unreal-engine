#include "StartCPPClass.h"
#include "Utils/Random.h"
#include "Midiparser/MidiFile.h"
#include <string>
#include <sstream>

float SpawnTime = 0.0f;

AStartCPPClass::AStartCPPClass()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AStartCPPClass::GetTrackStrings(const FString& MidiPath, FString& OutTracks)
{
	OutTracks = "";
	smf::MidiFile midifile(TCHAR_TO_UTF8(*MidiPath));
	
	int tracks = midifile.getTrackCount();
	for (int track = 0; track < tracks; track++) {
		std::stringstream TrackString;
		int trackSize = midifile[track].size();
		TrackString << "Track " << track << "  Events: " << trackSize;
		FString TrackFString(TrackString.str().c_str());
		OutTracks += TrackFString + "\n";
	}
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
	FRotator rotation = RandomRotator();
	location.Z = 500.0f;


	AStaticMeshActor* spawnedNote = SpawnNote(location, rotation);

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

AStaticMeshActor* AStartCPPClass::SpawnNote(FVector& location, FRotator& rotation)
{
	AStaticMeshActor* spawnedNote = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
	spawnedNote->SetMobility(EComponentMobility::Movable);
	spawnedNote->SetActorLocation(location);
	spawnedNote->SetActorRotation(rotation);
	UStaticMeshComponent* MeshComponent = spawnedNote->GetStaticMeshComponent();
	if (MeshComponent)
	{
		MeshComponent->SetStaticMesh(BackgroundNoteToSpawn);
		MeshComponent->SetMobility(EComponentMobility::Movable);
		MeshComponent->SetSimulatePhysics(true);
	}

	return spawnedNote;
}