#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ChanneldEditorStyle.h"

class FEditorStyle;

class FChanneldEditorCommands : public TCommands<FChanneldEditorCommands>
{
public:

	FChanneldEditorCommands()
		: TCommands<FChanneldEditorCommands>(TEXT("ChanneldEditor"), NSLOCTEXT("Contexts", "ChanneldEditor", "ChanneldEditor Plugin"), NAME_None, FChanneldEditorStyle::GetStyleSetName())
	{
	}

	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> PluginCommand;
	TSharedPtr<FUICommandInfo> ToggleNetworkingCommand;
	TSharedPtr<FUICommandInfo> LaunchChanneldCommand;
	TSharedPtr<FUICommandInfo> StopChanneldCommand;
	TSharedPtr<FUICommandInfo> LaunchServersCommand;
	TSharedPtr<FUICommandInfo> ServerSettingsCommand;
	TSharedPtr<FUICommandInfo> StopServersCommand;
	TSharedPtr<FUICommandInfo> GenerateReplicatorCommand;
	TSharedPtr<FUICommandInfo> AddRepComponentsToBPsCommand;
};
