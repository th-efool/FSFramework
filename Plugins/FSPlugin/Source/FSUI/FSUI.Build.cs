using UnrealBuildTool;

public class FSUI : ModuleRules
{
	public FSUI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				"UMG", "FSCore" // ← required for UUserWidget
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"FSCore",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore"
			}
		);
	}
}