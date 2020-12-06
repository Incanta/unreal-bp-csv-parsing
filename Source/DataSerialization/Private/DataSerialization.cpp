// Copyright Incanta Games 2020. All Rights Reserved.

#include "DataSerialization.h"

#define LOCTEXT_NAMESPACE "FDataSerializationModule"

DEFINE_LOG_CATEGORY(LogDataSerialization);

void FDataSerializationModule::StartupModule() {
  // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FDataSerializationModule::ShutdownModule() {
  // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
  // we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDataSerializationModule, DataSerialization)