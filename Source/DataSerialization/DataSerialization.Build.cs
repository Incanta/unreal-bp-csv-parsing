// Copyright Incanta Games 2020. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class DataSerialization : ModuleRules {
  public DataSerialization(ReadOnlyTargetRules Target) : base(Target) {
    PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
    CppStandard = CppStandardVersion.Cpp17;

    String CsvLibraryPath = Path.Combine(PluginDirectory, "Source", "ThirdParty", "csv-parser");

    PublicIncludePaths.AddRange(
      new string[] {
        Path.Combine(CsvLibraryPath, "include")
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
