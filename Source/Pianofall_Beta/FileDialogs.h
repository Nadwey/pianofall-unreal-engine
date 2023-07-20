// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "portable-file-dialogs.h"

#include "FileDialogs.generated.h"


/**
 * 
 */
UCLASS()
class PIANOFALL_BETA_API UFileDialogs : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "File Dialogs")
		static void OpenFileDialog(FString DialogTitle, TArray<FString> FileTypes, TArray<FString>& OutFilenames, bool& ReturnValue);
	UFUNCTION(BlueprintCallable, Category = "File Dialogs")
		static void OpenFolderDialog(FString DialogTitle, FString& OutFolderName, bool& ReturnValue);
};