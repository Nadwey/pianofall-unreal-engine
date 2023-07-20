// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Engine/LevelScriptActor.h>
#include <Engine/StaticMeshActor.h>
#include "StartCPPClass.generated.h"

/**
 * 
 */
UCLASS()
class PIANOFALLUE_API AStartCPPClass : public ALevelScriptActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AStartCPPClass();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UStaticMesh* BackgroundNoteToSpawn = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Midi")
		void GetTrackStrings(const FString& MidiPath, FString& OutTracks);
	
	AStaticMeshActor* SpawnNote(FVector& location, FRotator& rotation);
	TArray<AStaticMeshActor*> notes;
	int currentNote;
	const int MAX_NOTES = 100;
};
