// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Managers/Statistics/StateStatInfo.h"

StateStatInfo::StateStatInfo()
{
	CurrentPoints = 0;
}

StateStatInfo::StateStatInfo(TWeakInterfacePtr<IIEnemySpawnerInfo> EnemySpawnerInfoTemp)
{
	CurrentPoints = 0;
	EnemySpawnerInfo = EnemySpawnerInfoTemp;
	OnPointsChanged = MakeShareable(new FOnPointsChanged());
	auto EnemyDiedDlgt = EnemySpawnerInfo->GetOnEnemyDiedDelegate(); 
	OnEnemyDiedHandle = EnemyDiedDlgt->AddRaw(this , &StateStatInfo::OnEnemyDied_Receiver);
}

StateStatInfo::~StateStatInfo()
{
}

void StateStatInfo::Dispose()
{
	EnemySpawnerInfo.Reset();
	OnEnemyDiedHandle.Reset();
}

TSharedPtr<FOnPointsChanged> StateStatInfo::GetOnPointsChangedDelegate()
{
	return OnPointsChanged;
	
}

void StateStatInfo::OnEnemyDied_Receiver(TWeakObjectPtr<AEnemyBase> EnemyDied)
{
	CurrentPoints += EnemyDied.Get()->GetKillingPoints();
	if(OnPointsChanged.Get()->IsBound())
	{
		OnPointsChanged.Get()->Broadcast(CurrentPoints);
	}
}
