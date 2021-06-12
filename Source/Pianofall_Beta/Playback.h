// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Playback.generated.h"


/**
 * 
 */
UCLASS()
class PIANOFALL_BETA_API APlayback : public ALevelScriptActor
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	APlayback();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> NoteToSpawn;

	UFUNCTION(BlueprintCallable, Category = "Midi")
		void InitRender(const FString& MidiPath, const FString& OutFolder);
};
