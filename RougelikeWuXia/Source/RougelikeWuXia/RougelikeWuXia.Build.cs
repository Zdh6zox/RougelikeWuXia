// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RougelikeWuXia : ModuleRules
{
	public RougelikeWuXia(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });

        PrivateDependencyModuleNames.AddRange(new string[] { "UMG" });

        PublicIncludePaths.AddRange(new string[] { "RougelikeWuXia" });

        PrivateIncludePaths.AddRange(new string[] { "RougelikeWuXia" });
    }
}
