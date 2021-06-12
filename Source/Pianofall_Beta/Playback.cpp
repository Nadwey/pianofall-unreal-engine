#include "PlayBack.h"
#include "Midiparser/MidiFile.h"
#include <string>
#include <sstream>
#include "Utils/Global.h"

smf::MidiFile PlayBackMidiFile;

bool PlayBackMidiLoaded = false;
bool started = false;

float MidiReadStep = -1.0f;
uint32 startFrame = 0;

std::string outFolder;

APlayback::APlayback()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void APlayback::InitRender(const FString& MidiPath, const FString& OutFolder) {
	outFolder = TCHAR_TO_UTF8(*OutFolder);
	PlayBackMidiFile.read(TCHAR_TO_UTF8(*MidiPath));
	PlayBackMidiFile.doTimeAnalysis();
	PlayBackMidiFile.sortTracks();
	PlayBackMidiLoaded = true;
}

void APlayback::BeginPlay()
{
	Super::BeginPlay();
	startFrame = GFrameNumber;
	if (PlayBackMidiLoaded)	started = true;
}

void APlayback::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UWorld* const PlaybackWorld = GetWorld();

	if (!started) return;
	int tracks = PlayBackMidiFile.getTrackCount();

	for (int track = 0; track < tracks; track++) {
		for (int mEvent = PlayBackMidiFile[track].GetReadStep() || 0; mEvent < PlayBackMidiFile[track].size(); mEvent++) {
			smf::MidiEvent& midiEvent = PlayBackMidiFile[track][mEvent];

			if (midiEvent.seconds > MidiReadStep) break;
			if (midiEvent.seconds < MidiReadStep && midiEvent.isNoteOn()) {
				if (!midiEvent.GetPlayedArleady()) {
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = this;
					SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

					FVector location(0.0f, map(midiEvent.getKeyNumber(), 24, 95, -1.0f, 1.0f) * 200.0f, 600.0f);
					PlaybackWorld->SpawnActor<AActor>(NoteToSpawn, location, FRotator::ZeroRotator, SpawnParams);

					PlayBackMidiFile[track].SetReadStep(mEvent);
					midiEvent.SetPlayedArleady(true);
				}
			}
		}

		std::stringstream ss;
		ss << outFolder << "/Frame" << ZeroPadNumber(GFrameNumber - startFrame, 6) << ".png";
		FScreenshotRequest::RequestScreenshot(ss.str().c_str(), false, false);

		MidiReadStep += started ? (1.0f / 3600.0f) : 0;
	}
}