// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include "../EPlaybackTypes.h"
#include "../EPlaybackColorMode.h"
#include "FPlaybackSettings.generated.h"

USTRUCT(BlueprintType)
struct FPlaybackSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playback Settings")
    FString MidiPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playback Settings")
    FString RenderOutputPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playback Settings")
    EPlaybackTypes PlaybackType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playback Settings")
    EPlaybackColorMode PlaybackColorMode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playback Settings")
    int MaxNotes;
};
