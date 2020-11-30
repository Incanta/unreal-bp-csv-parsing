// Copyright Incanta Games 2020. All Rights Reserved.

#include "Parser.h"

#define LOCTEXT_NAMESPACE "FParserModule"

DEFINE_LOG_CATEGORY(LogParser);

void FParserModule::StartupModule() {
  // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FParserModule::ShutdownModule() {
  // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
  // we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FParserModule, Parser)