// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"

/**
 * 
 */
class ZOMBHEADS_API ActorUtility
{
public:
	ActorUtility();
	~ActorUtility();

	static bool IsMeshRenderedByCamera(USkeletalMeshComponent* MeshComponent, UCameraComponent* CameraComponent);

private:
	static FMatrix GetCameraProjectionMatrix(UCameraComponent* CameraComponent);
};
