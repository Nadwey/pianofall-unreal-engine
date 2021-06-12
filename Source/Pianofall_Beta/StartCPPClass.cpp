// Fill out your copyright notice in the Description page of Project Settings.


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
	UWorld* const StartWorld = GetWorld();

	if (GFrameNumber % 3) return;


	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector location = RandomVector(200.0f, 1500.0f, 0.0f);
	location.Z = 500.0f;
	StartWorld->SpawnActor<AActor>(BackgroundNoteToSpawn, location, RandomRotator(), SpawnParams);

}