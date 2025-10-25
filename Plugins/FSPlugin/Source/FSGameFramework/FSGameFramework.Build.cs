using UnrealBuildTool;

public class FSGameFramework : ModuleRules
{
    public FSGameFramework(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "UMG" // ← required for UUserWidget
        });
		
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Engine",
                "Slate",
                "SlateCore",
                "FSCore",
                // ... add private dependencies that you statically link with here ...	
            }
			
        );

    }
}