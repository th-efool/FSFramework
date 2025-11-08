using UnrealBuildTool;

public class FSGameplay : ModuleRules
{
	public FSGameplay(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"UMG", "FSCore", // ← required for UUserWidget
			"OnlineSubsystem",
			"OnlineSubsystemUtils",
			"OnlineSubsystemEOS",
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