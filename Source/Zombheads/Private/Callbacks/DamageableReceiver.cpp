// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Callbacks/DamageableReceiver.h"

#include "Utility/DebugUtility.h"
/*
DamageableReceiver::DamageableReceiver()
{
}

DamageableReceiver::~DamageableReceiver()
{
}
*/
void DamageableReceiver::DamageTaken_Receiver(TWeakInterfacePtr<IVitalityComponent> VitalityComponent)
{
	UE_LOG(LogTemp , Log, TEXT("DamageableReceiver method not implemented"))
	GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("DamageableReceiver not implemented")));
}
