// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

/**
 * 
 */
class ZOMBHEADSEDITORMODULE_API FCustomEnemySpawnerExtension : public IDetailCustomization
{
public:
	// Makes an instance of this class
	static TSharedRef<IDetailCustomization> MakeInstance();

	// IDetailCustomization interface
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	// Callback for when the button is clicked
	FReply OnStandaloneEditorButtonClick();
	FReply OnClearSpawnDatasButtonClick();

	// Reference to the detail layout builder to access actor properties
	IDetailLayoutBuilder* DetailBuilderRef;
};
