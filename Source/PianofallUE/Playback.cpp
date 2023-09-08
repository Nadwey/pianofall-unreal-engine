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
		for (int mEvent = PlayBackMidiFile[track].GetReadStep(); mEvent < PlayBackMidiFile[track].size(); mEvent++) {
			smf::MidiEvent& midiEvent = PlayBackMidiFile[track][mEvent];

			if (midiEvent.seconds >= MidiReadStep) break;
			if (midiEvent.seconds < MidiReadStep && midiEvent.isNoteOn()) {
				if (!midiEvent.GetPlayedArleady()) {
					FVector location(0.0f, map(midiEvent.getKeyNumber(), 24, 95, -1.0f, 1.0f) * 200.0f, 600.0f);
					FRotator rotation = FRotator::ZeroRotator;
					AStaticMeshActor* spawnedNote = SpawnNote(location, rotation);

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
					UMaterialInstanceDynamic * NoteMaterialInstance = StaticMeshComponent->CreateDynamicMaterialInstance(0);

					if (NoteMaterialInstance != nullptr)
					{
						switch (playbackColorMode)
						{
						case EPlaybackColorMode::RainbowHue: {
							double range = 128;

							RGB color = rgb((double)midiEvent.getKeyNumber() / range);

							NoteMaterialInstance->SetScalarParameterValue(FName("R"), (float)color.r / 255.0f);
							NoteMaterialInstance->SetScalarParameterValue(FName("G"), (float)color.g / 255.0f);
							NoteMaterialInstance->SetScalarParameterValue(FName("B"), (float)color.b / 255.0f);
							break;
						}
						case EPlaybackColorMode::Random: {
							RGB color = RandomColor();

							NoteMaterialInstance->SetScalarParameterValue(FName("R"), (float)color.r / 255.0f);
							NoteMaterialInstance->SetScalarParameterValue(FName("G"), (float)color.g / 255.0f);
							NoteMaterialInstance->SetScalarParameterValue(FName("B"), (float)color.b / 255.0f);

							break;
						}
						case EPlaybackColorMode::Black: {
							NoteMaterialInstance->SetScalarParameterValue(FName("R"), 0.0f);
							NoteMaterialInstance->SetScalarParameterValue(FName("G"), 0.0f);
							NoteMaterialInstance->SetScalarParameterValue(FName("B"), 0.0f);

							break;
						}
						default: {
							NoteMaterialInstance->SetScalarParameterValue(FName("R"), 0.0f);
							NoteMaterialInstance->SetScalarParameterValue(FName("G"), 0.0f);
							NoteMaterialInstance->SetScalarParameterValue(FName("B"), 0.0f);

							break;
						}
						}
					}

					PlayBackMidiFile[track].SetReadStep(mEvent);
					midiEvent.SetPlayedArleady(true);
				}
			}
		}
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

		MidiReadStep = (float)frame / 60.0f;
		break;
	}
	
	frame++;
}

AStaticMeshActor* APlayback::SpawnNote(FVector& location, FRotator& rotation)
{
	AStaticMeshActor* spawnedNote = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
	spawnedNote->SetMobility(EComponentMobility::Movable);
	spawnedNote->SetActorLocation(location);
	spawnedNote->SetActorRotation(rotation);
	UStaticMeshComponent* MeshComponent = spawnedNote->GetStaticMeshComponent();
	if (MeshComponent)
	{
		MeshComponent->SetStaticMesh(NoteToSpawn);
		MeshComponent->SetMobility(EComponentMobility::Movable);
		MeshComponent->SetSimulatePhysics(true);
	}

	return spawnedNote;
}