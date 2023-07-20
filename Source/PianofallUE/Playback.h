// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Engine/LevelScriptActor.h>
#include <Engine/StaticMeshActor.h>
#include <string>
#include "Midiparser/MidiFile.h"
#include "EPlaybackTypes.h"
#include "EPlaybackColorMode.h"
#include "Playback.generated.h"


/**
 * 
 */
UCLASS()
class PIANOFALLUE_API APlayback : public ALevelScriptActor
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	APlayback();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UStaticMesh* NoteToSpawn;

	UFUNCTION(BlueprintCallable, Category = "Midi")
		void InitRender(const FString& MidiPath, const FString& OutFolder, const EPlaybackTypes& PlaybackMode, const EPlaybackColorMode& PlaybackColorMode);

	AStaticMeshActor* SpawnNote(FVector& location, FRotator& rotation);
	TArray<AStaticMeshActor*> notes;
	int currentNote;
	const int MAX_NOTES = 10000;

	EPlaybackTypes playbackType;
	EPlaybackColorMode playbackColorMode;

	bool running = false;
	uint64 frame = 0;
	float MidiReadStep = 0.0f;
	
	std::string outFolder;
	smf::MidiFile PlayBackMidiFile;
	
};
