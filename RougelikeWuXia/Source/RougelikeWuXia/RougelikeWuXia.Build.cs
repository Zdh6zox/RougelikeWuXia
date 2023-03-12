// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RougelikeWuXia : ModuleRules
{
	public RougelikeWuXia(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Paper2D", "MapGenerator" });

        PrivateDependencyModuleNames.AddRange(new string[] { "UMG" });

        PublicIncludePaths.AddRange(new string[] { "RougelikeWuXia", "Paper2D", "MapGenerator" });

        PrivateIncludePaths.AddRange(new string[] { "RougelikeWuXia", "Paper2D" });

        if(Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "DetailCustomizations", "PropertyEditor", "EditorStyle" });
            PublicDependencyModuleNames.AddRange(new string[] { "UnrealEd" });
        }
    }
}
