﻿using UnrealBuildTool;

public class FSGameFramework : ModuleRules
{
	public FSGameFramework(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"UMG" // ← required for UUserWidget
		});

		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"Engine",
				"Slate",
				"SlateCore",
				"FSCore"
				// ... add private dependencies that you statically link with here ...	
			}
		);
	}
}