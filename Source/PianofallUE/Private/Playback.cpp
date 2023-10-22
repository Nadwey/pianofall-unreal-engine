#include "Playback.h"
#include <sstream>
#include <time.h>
#include "Utils/Global.h"

APlayback::APlayback()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void APlayback::InitRender(const FPlaybackSettings& playbackSettings) {
	PlayBackMidiFile.read(TCHAR_TO_UTF8(*playbackSettings.MidiPath));
	PlayBackMidiFile.doTimeAnalysis();
	PlayBackMidiFile.sortTracks();
	
	this->outFolder = TCHAR_TO_UTF8(*playbackSettings.RenderOutputPath);
	this->playbackType = playbackSettings.PlaybackType;
	this->playbackColorMode = playbackSettings.PlaybackColorMode;
	this->MaxNotes = playbackSettings.MaxNotes;

	running = true;
}

void APlayback::BeginPlay()
{
	Super::BeginPlay();
}

void APlayback::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UWorld* const PlaybackWorld = GetWorld();
	
	if (!running) return;
	int tracks = PlayBackMidiFile.getTrackCount();

	for (int track = 0; track < tracks; track++) {
		int mEvent = PlayBackMidiFile[track].readStep;
		for (; mEvent < PlayBackMidiFile[track].size(); mEvent++) {

			if (mEvent >= PlayBackMidiFile[track].getEventCount() - 1) break;

			smf::MidiEvent& midiEvent = PlayBackMidiFile[track][mEvent];

			if (midiEvent.seconds > MidiReadStep) break;
			if (!midiEvent.isNoteOn()) continue;

			FVector location(0.0f, (midiEvent.getKeyNumber() - 60) * NoteToSpawn->GetBounds().BoxExtent.Y * 2.05f, 600.0f);
			FRotator rotation = FRotator::ZeroRotator;
			AStaticMeshActor* spawnedNote = SpawnMovableStaticMesh(GetWorld(), NoteToSpawn, location, rotation);

			if (currentNote > MaxNotes) currentNote = 0;
			if (notes.IsValidIndex(currentNote) && IsValid(notes[currentNote])) {
				notes[currentNote]->Destroy();
				notes[currentNote] = spawnedNote;
			}
			else {
				notes.Add(spawnedNote);
			}

			currentNote++;

			TArray<UStaticMeshComponent*> Components;
			spawnedNote->GetComponents<UStaticMeshComponent>(Components);
			UStaticMeshComponent* StaticMeshComponent = Components[0];
			UMaterialInstanceDynamic* NoteMaterialInstance = StaticMeshComponent->CreateDynamicMaterialInstance(0);

			if (NoteMaterialInstance != nullptr)
			{
				switch (playbackColorMode)
				{
				case EPlaybackColorMode::RainbowHue: {
					FLinearColor color = MakeRGB((double)midiEvent.getKeyNumber() / 128.0);

					NoteMaterialInstance->SetVectorParameterValue(FName("Color"), color);
					break;
				}
				case EPlaybackColorMode::Random: {
					NoteMaterialInstance->SetVectorParameterValue(FName("Color"), FLinearColor::MakeRandomColor());

					break;
				}
				case EPlaybackColorMode::Black:
				default:
					NoteMaterialInstance->SetVectorParameterValue(FName("Color"), FLinearColor::Black);

					break;
				}
			}

			
		}
		PlayBackMidiFile[track].readStep = mEvent;

	}
	
	switch (playbackType)
	{
	case EPlaybackTypes::Realtime:
		MidiReadStep += DeltaTime;
		break;
	case EPlaybackTypes::Render:
		std::stringstream ss;
		ss << outFolder << "/Frame" << ZeroPadNumber(frame, 6) << ".png";
		FScreenshotRequest::RequestScreenshot(ss.str().c_str(), false, false);

		MidiReadStep = (double)frame / 60.0;
		break;
	}
	
	frame++;
}
