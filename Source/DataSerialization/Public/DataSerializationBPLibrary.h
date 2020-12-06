// Copyright Incanta Games 2020. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "csv.hpp"
#include "CSVObject.h"

#include "DataSerializationBPLibrary.generated.h"

UCLASS()
class UDataSerializationBPLibrary : public UBlueprintFunctionLibrary {
  GENERATED_UCLASS_BODY()

  UFUNCTION(
    BlueprintCallable,
    meta = (
      DisplayName = "Parse CSV Rows",
      Keywords = "serialization parse CSV rows",
      AutoCreateRefTerm = "ColumnNames"
    ),
    Category = "Serialization | CSV"
  )
  static UCSVObject * ParseCSVRows(
    FString CSVString,
    TArray<FString> ColumnNames,
    FString DelimiterCharacter = ",",
    FString QuoteCharacter = "\"",
    int HeaderRow = -1,
    int KeysColumn = -1,
    int FirstColumn = 0
  );
};
