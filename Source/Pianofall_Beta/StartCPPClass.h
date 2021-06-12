// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "StartCPPClass.generated.h"

/**
 * 
 */
UCLASS()
class PIANOFALL_BETA_API AStartCPPClass : public ALevelScriptActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AStartCPPClass();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> BackgroundNoteToSpawn;

	UFUNCTION(BlueprintCallable, Category = "Midi")
		void GetTrackStrings(const FString& MidiPath, FString& OutTracks);
	
};
