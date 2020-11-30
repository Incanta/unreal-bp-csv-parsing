// Copyright Incanta Games 2020. All Rights Reserved.

#include "ParseAndStringify.h"

#define LOCTEXT_NAMESPACE "FParseAndStringifyModule"

DEFINE_LOG_CATEGORY(LogParseAndStringify);

void FParseAndStringifyModule::StartupModule() {
  // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FParseAndStringifyModule::ShutdownModule() {
  // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
  // we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FParseAndStringifyModule, ParseAndStringify)