// Copyright (c) 2026 CrimsonVRFramework. See LICENSE.

#pragma once

#include "CoreMinimal.h"
#include "CollisionQueryParams.h"
#include "Engine/EngineTypes.h"

class UPrimitiveComponent;
class UWorld;

/** Provenance of the earliest blocking hit, reported for diagnostics only. */
struct VREXPANSIONPLUGIN_API FSkeletalSweepFirstHit
{
	int32 BodyIndex = -1;
	int32 ShapeType = -1;
	FTransform Bi0;
	FTransform Bend;
	bool bHit = false;
};

/**
 * Sweeps every convex shape of a skeletal mesh in its own body frame.
 *
 * The stock component sweep submits every skeletal shape with the shared
 * component-level start/end/rotation, so articulated shapes are tested near the
 * component origin instead of where they actually are. Here Li places body i's
 * geometry from the rigid actual component frame C0, then the sweep runs from
 * the VRE base Cbase to the requested root frame Crequest.
 *
 * Non-skeletal or non-unit-scale callers keep the stock component sweep. No state
 * is cached across ticks; all reads stay under the engine RAII read lock.
 */
VREXPANSIONPLUGIN_API bool SkeletalHybridSweep(
	UWorld* World,
	UPrimitiveComponent* PrimComp,
	const FTransform& Cbase,
	const FTransform& Crequest,
	const FComponentQueryParams& Params,
	TArray<FHitResult>& OutHits,
	FSkeletalSweepFirstHit* OutFirstHit = nullptr);
