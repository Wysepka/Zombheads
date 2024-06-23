// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Utility/ActorUtility.h"

ActorUtility::ActorUtility()
{
}

ActorUtility::~ActorUtility()
{
}

//This is not working and i dont have time to figure out what is going on wrong
bool ActorUtility::IsMeshRenderedByCamera(USkeletalMeshComponent* MeshComponent, UCameraComponent* CameraComponent)
{
	if (!MeshComponent || !CameraComponent)
	{
		return false;
	}

	/*
	// Get the bounding box of the mesh component in world space
	FBoxSphereBounds MeshBounds = MeshComponent->CalcBounds(MeshComponent->GetComponentTransform());

	// Get the view matrix from the camera's transform
	FTransform CameraTransform = CameraComponent->GetComponentTransform();
	FMatrix ViewMatrix = CameraTransform.ToInverseMatrixWithScale();

	// Get the projection matrix from the camera
	FMatrix ProjectionMatrix = GetCameraProjectionMatrix(CameraComponent);

	// Calculate the view-projection matrix
	FMatrix ViewProjectionMatrix = ViewMatrix * ProjectionMatrix;

	// Transform the mesh bounds to the camera's view space
	FBoxSphereBounds TransformedBounds = MeshBounds.TransformBy(ViewProjectionMatrix);

	// Check if the transformed bounds are within the normalized device coordinates (NDC) frustum [-1, 1]
	FBox TransformedBox = FBox(TransformedBounds.Origin - TransformedBounds.BoxExtent, TransformedBounds.Origin + TransformedBounds.BoxExtent);

	if (TransformedBox.Min.X <= 1.0f && TransformedBox.Max.X >= -1.0f &&
		TransformedBox.Min.Y <= 1.0f && TransformedBox.Max.Y >= -1.0f &&
		TransformedBox.Min.Z <= 1.0f && TransformedBox.Max.Z >= -1.0f)
	{
		return true;
	}

	return false;
	*/

	// Get the bounds of the skeletal mesh component in world space
	FBoxSphereBounds MeshBounds = MeshComponent->CalcBounds(MeshComponent->GetComponentTransform());

	// Get the view matrix from the camera's transform
	FTransform CameraTransform = CameraComponent->GetComponentTransform();
	FMatrix ViewMatrix = CameraTransform.ToInverseMatrixWithScale();

	// Get the projection matrix from the camera
	FMatrix ProjectionMatrix = GetCameraProjectionMatrix(CameraComponent);

	// Calculate the view-projection matrix
	FMatrix ViewProjectionMatrix = ViewMatrix * ProjectionMatrix;

	// Calculate the view frustum
	FConvexVolume ViewFrustum;
	GetViewFrustumBounds(ViewFrustum, ViewProjectionMatrix, false);

	// Check if the bounds of the skeletal mesh intersect with the view frustum
	return ViewFrustum.IntersectBox(MeshBounds.Origin, MeshBounds.BoxExtent);
}

//Idk if this is working
FMatrix ActorUtility::GetCameraProjectionMatrix(UCameraComponent* CameraComponent)
{
	float FOV = CameraComponent->FieldOfView;
	float AspectRatio = CameraComponent->AspectRatio;
	float NearClip = CameraComponent->OrthoNearClipPlane;
	float FarClip = CameraComponent->OrthoFarClipPlane;
	return FReversedZPerspectiveMatrix(FOV, AspectRatio, 1.0f, NearClip, FarClip);
}
