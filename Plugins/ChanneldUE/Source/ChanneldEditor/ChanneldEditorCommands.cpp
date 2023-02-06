// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ChanneldEditorCommands.h"

#define LOCTEXT_NAMESPACE "FChanneldEditorModule"

void FChanneldEditorCommands::RegisterCommands()
{
	UI_COMMAND(PluginCommand, "Channeld", "Tools and utilities provided by ChanneldUE", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(LaunchChanneldCommand, "Launch Channeld", "Launch channeld in a separate process", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(StopChanneldCommand, "Stop Channeld", "Stop launched channeld service", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(LaunchServersCommand, "Launch Servers", "Launch PIE servers using current map in separate processes", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(ServerSettingsCommand, "Server Settings...", "Configure server numbers, map, view, and additioanl args", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(StopServersCommand, "Stop Servers", "Stop launched PIE servers", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(GenerateReplicatorCommand, "Generate Replicator", "Generate all replicators", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(AddReplicationComponentCommand, "Add replication component to blueprint actor", "Add replication component to blueprint actor", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
