#include "PlayBack.h"
#include "Midiparser/MidiFile.h"
#include <string>
#include <sstream>
#include <time.h>
#include "Utils/Global.h"
#include "Utils/Playback.h"


smf::MidiFile PlayBackMidiFile;

bool started = false;

float MidiReadStep = 0.0f;
uint32 Frame = 0;
int32 PlaybackMode = 0;
int32 PlaybackColorMode = 0;

std::string outFolder;

APlayback::APlayback()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void APlayback::InitRender(const FString& MidiPath, const FString& OutFolder, const int32& playbackMode, const int32& playbackColorMode) {
	outFolder = TCHAR_TO_UTF8(*OutFolder);
	PlayBackMidiFile.read(TCHAR_TO_UTF8(*MidiPath));
	PlayBackMidiFile.doTimeAnalysis();
	PlayBackMidiFile.sortTracks();
	PlaybackMode = playbackMode;
	PlaybackColorMode = playbackColorMode;
	started = true;
}

void APlayback::BeginPlay()
{
	Super::BeginPlay();
}

void APlayback::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UWorld* const PlaybackWorld = GetWorld();
	
	if (!started) return;
	int tracks = PlayBackMidiFile.getTrackCount();

	for (int track = 0; track < tracks; track++) {
		for (int mEvent = PlayBackMidiFile[track].GetReadStep(); mEvent < PlayBackMidiFile[track].size(); mEvent++) {
			smf::MidiEvent& midiEvent = PlayBackMidiFile[track][mEvent];

			if (midiEvent.seconds > MidiReadStep) break;

			if (midiEvent.seconds < MidiReadStep && midiEvent.isNoteOn()) {
				if (!midiEvent.GetPlayedArleady()) {
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = this;
					SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

					FVector location(0.0f, map(midiEvent.getKeyNumber(), 24, 95, -1.0f, 1.0f) * 200.0f, 600.0f);
					AActor * SpawnedNote = PlaybackWorld->SpawnActor<AActor>(NoteToSpawn, location, FRotator::ZeroRotator, SpawnParams);

					TArray<UStaticMeshComponent*> Components;
					SpawnedNote->GetComponents<UStaticMeshComponent>(Components);
					UStaticMeshComponent* StaticMeshComponent = Components[0];
					UMaterialInstanceDynamic * NoteMaterialInstance = StaticMeshComponent->CreateDynamicMaterialInstance(0);

					

					if (NoteMaterialInstance != nullptr)
					{
						switch (PlaybackColorMode)
						{
						case PlaybackColorModes::RAINBOWHUE: {
							double range = 128;

							RGB color = rgb((double)midiEvent.getKeyNumber() / range);

							NoteMaterialInstance->SetScalarParameterValue(FName("R"), (float)color.r / 255.0f);
							NoteMaterialInstance->SetScalarParameterValue(FName("G"), (float)color.g / 255.0f);
							NoteMaterialInstance->SetScalarParameterValue(FName("B"), (float)color.b / 255.0f);
							break;
						}
						case PlaybackColorModes::RANDOMCOLOR: {
							RGB color = RandomColor();

							NoteMaterialInstance->SetScalarParameterValue(FName("R"), (float)color.r / 255.0f);
							NoteMaterialInstance->SetScalarParameterValue(FName("G"), (float)color.g / 255.0f);
							NoteMaterialInstance->SetScalarParameterValue(FName("B"), (float)color.b / 255.0f);

							break;
						}
						case PlaybackColorModes::BLACK: {
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
	
	if (PlaybackMode == 0)
	{
		std::stringstream ss;
		ss << outFolder << "/Frame" << ZeroPadNumber(Frame, 6) << ".png";
		FScreenshotRequest::RequestScreenshot(ss.str().c_str(), false, false);
	}

	MidiReadStep = (float)Frame / 60.0f;
	Frame++;
}
