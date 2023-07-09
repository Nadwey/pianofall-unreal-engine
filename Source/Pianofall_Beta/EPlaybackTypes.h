// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPlaybackTypes : uint8
{
	Realtime	UMETA(DisplayName = "Realtime"),
	Render		UMETA(DisplayName = "Render"),
};