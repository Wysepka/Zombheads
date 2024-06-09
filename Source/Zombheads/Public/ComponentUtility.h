// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "UObject/WeakInterfacePtr.h"

/**
 * 
 */
class ZOMBHEADS_API ComponentUtility
{
public:
	ComponentUtility();
	~ComponentUtility();

	template <typename InterfaceType , typename InterfaceUObject>
	static TWeakInterfacePtr<InterfaceType> FindActorWithInterface(UWorld* World);

	template <typename ActorType>
	static TWeakObjectPtr<ActorType> FindActorOfType(UWorld* World);

	template <typename ComponentType>
	static TWeakObjectPtr<ComponentType> FindComponentOfType(AActor* Actor);
};

template <typename InterfaceType, typename InterfaceUObject>
TWeakInterfacePtr<InterfaceType> ComponentUtility::FindActorWithInterface(UWorld* World)
{
	TArray<AActor*> ActorsWithInterface;
	UGameplayStatics::GetAllActorsWithInterface(World, InterfaceUObject::StaticClass(), ActorsWithInterface);

	if (ActorsWithInterface.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actors with interface %s are empty! Try another interface lookup"), *InterfaceUObject::StaticClass()->GetName());
		return nullptr;
	}
        
	TWeakInterfacePtr<InterfaceType> InterfacePtr = Cast<InterfaceType>(ActorsWithInterface[0]);
	if (!InterfacePtr.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Incorrect cast from %s to %s"), *ActorsWithInterface[0]->GetName(), *InterfaceUObject::StaticClass()->GetName());
		return nullptr;
	}

	return InterfacePtr;
}

template <typename ActorType>
TWeakObjectPtr<ActorType> ComponentUtility::FindActorOfType(UWorld* World)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(World, ActorType::StaticClass(), FoundActors);

	if (FoundActors.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actors of type %s are empty! Try another actor lookup"), *ActorType::StaticClass()->GetName());
		return nullptr;
	}
        
	ActorType* FoundActor = Cast<ActorType>(FoundActors[0]);
	if (!FoundActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Incorrect cast from %s to %s"), *FoundActors[0]->GetName(), *ActorType::StaticClass()->GetName());
		return nullptr;
	}

	return TWeakObjectPtr<ActorType>(FoundActor);
}

template <typename ComponentType>
TWeakObjectPtr<ComponentType> ComponentUtility::FindComponentOfType(AActor* Actor)
{
	if (!Actor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor is null! Cannot find component."));
		return nullptr;
	}

	ComponentType* FoundComponent = Actor->FindComponentByClass<ComponentType>();

	if (!FoundComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Component of type %s not found in actor %s!"), *ComponentType::StaticClass()->GetName(), *Actor->GetName());
		return nullptr;
	}

	return TWeakObjectPtr<ComponentType>(FoundComponent);
}

