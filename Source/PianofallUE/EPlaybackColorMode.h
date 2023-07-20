// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPlaybackColorMode : uint8
{
	Black		UMETA(DisplayName = "Black"),
	RainbowHue	UMETA(DisplayName = "RainbowHue"),
	Random		UMETA(DisplayName = "Random"),
};