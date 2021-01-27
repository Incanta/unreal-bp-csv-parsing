// Copyright Incanta Games 2020. All Rights Reserved.

using UnrealBuildTool;

public class DataSerialization : ModuleRules {
  public DataSerialization(ReadOnlyTargetRules Target) : base(Target) {
    PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
    CppStandard = CppStandardVersion.Cpp17;

    PublicIncludePaths.AddRange(
      new string[] {
      }
      );


    PrivateIncludePaths.AddRange(
      new string[] {
      }
      );


    PublicDependencyModuleNames.AddRange(
      new string[]
      {
        "Core",
      }
      );


    PrivateDependencyModuleNames.AddRange(
      new string[]
      {
        "CoreUObject",
        "Engine",
        "Slate",
        "SlateCore",
      }
      );


    DynamicallyLoadedModuleNames.AddRange(
      new string[]
      {
      }
      );
  }
}
