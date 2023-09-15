// Fill out your copyright notice in the Description page of Project Settings.


#include "FileDialogs.h"

void UFileDialogs::OpenFileDialog(FString DialogTitle, TArray<FString> FileTypes, TArray<FString>& OutFilenames, bool& ReturnValue)
{
	std::vector<std::string> fileTypesVec;

	for (const auto& fileType : FileTypes)
	{
		fileTypesVec.push_back(TCHAR_TO_UTF8(*fileType));
	}

	auto selection = pfd::open_file(TCHAR_TO_UTF8(*DialogTitle), "", fileTypesVec).result();

	if (selection.empty())
	{
		OutFilenames = {};
		ReturnValue = false;
		return;
	}

	for (const auto& file : selection)
		OutFilenames.Add(UTF8_TO_TCHAR(file.c_str()));

	ReturnValue = true;
}

void UFileDialogs::OpenFolderDialog(FString DialogTitle, FString& OutFolderName, bool& ReturnValue)
{
	auto selection = pfd::select_folder(TCHAR_TO_UTF8(*DialogTitle)).result();

	if (selection.empty())
	{
		ReturnValue = false;
		return;
	}

	OutFolderName = UTF8_TO_TCHAR(selection.c_str());
	ReturnValue = true;
}
