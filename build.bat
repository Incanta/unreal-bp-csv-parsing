echo off

set LINUX_MULTIARCH_ROOT=C:\UnrealToolchains\v16_clang-9.0.1-centos7\
%LINUX_MULTIARCH_ROOT%x86_64-unknown-linux-gnu\bin\clang++ -v

"C:\Program Files\Epic Games\UE_4.25\Engine\Build\BatchFiles\RunUAT.bat" ^
  BuildPlugin ^
  -Plugin=%CD%\Parser.uplugin ^
  -Package=%CD%\Dist ^
  -TargetPlatforms=Win64 ^
  -Rocket ^
  -VS2019
