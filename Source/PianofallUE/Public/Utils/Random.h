#include "CoreMinimal.h"

float MRand() {
	return FMath::FRand() - 0.5f;
}

FRotator RandomRotator()
{
	FRotator RRot;
	RRot.Yaw = FMath::FRand() * 360.0f;
	RRot.Pitch = FMath::FRand() * 360.0f;
	RRot.Roll = FMath::FRand() * 360.0f;
	return RRot;	
}

FVector RandomVector(float Xoffset, float Yoffset, float Zoffset)
{
	FVector Vec;
	Vec.X = MRand() * Xoffset;
	Vec.Y = MRand() * Yoffset;
	Vec.Z = MRand() * Zoffset;
	return Vec;
}