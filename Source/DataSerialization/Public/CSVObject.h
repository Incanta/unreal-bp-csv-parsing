// Copyright Incanta Games 2020. All Rights Reserved.

#pragma once

#include "UObject/Object.h"
#include "csv.hpp"

#include "CSVObject.generated.h"

class UDataSerializationBPLibrary;

UCLASS(BlueprintType, Blueprintable)
class UCSVObject : public UObject {
  GENERATED_UCLASS_BODY()

  UFUNCTION(
    BlueprintPure,
    meta = (
      DisplayName = "Get Column by Name",
      Keywords = "serialization get find retrieve column name string"
    ),
    Category = "Serialization | CSV"
  )
  TArray<FString> GetColumnByName(FString ColumnName);

  UFUNCTION(
    BlueprintPure,
    meta = (
      DisplayName = "Get Column by Index",
      Keywords = "serialization get find retrieve column index integer id"
    ),
    Category = "Serialization | CSV"
  )
  TArray<FString> GetColumnByIndex(int ColumnIndex);

  UFUNCTION(
    BlueprintPure,
    meta = (
      DisplayName = "Get Row by Key",
      Keywords = "serialization get find retrieve row key name string"
    ),
    Category = "Serialization | CSV"
  )
  TArray<FString> GetRowByKey(FString RowKey);

  UFUNCTION(
    BlueprintPure,
    meta = (
      DisplayName = "Get Row by Index",
      Keywords = "serialization get find retrieve row index integer id"
    ),
    Category = "Serialization | CSV"
  )
  TArray<FString> GetRowByIndex(int RowIndex);

  UFUNCTION(
    BlueprintPure,
    meta = (
      DisplayName = "Get Cell by Name and Key",
      Keywords = "serialization get find retrieve cell name key string"
    ),
    Category = "Serialization | CSV"
  )
  FString GetCellByNameAndKey(FString ColumnName, FString RowKey);

  UFUNCTION(
    BlueprintPure,
    meta = (
      DisplayName = "Get Cell by Indices",
      Keywords = "serialization get find retrieve cell index indices integer id"
    ),
    Category = "Serialization | CSV"
  )
  FString GetCellByIndices(int ColumnIndex, int RowIndex);

  UFUNCTION(
    BlueprintPure,
    meta = (
      DisplayName = "Get Column Index for Name",
      Keywords = "serialization get find retrieve column index name"
    ),
    Category = "Serialization | CSV"
  )
  int GetColumnIndexForName(FString Name);

  UFUNCTION(
    BlueprintPure,
    meta = (
      DisplayName = "Get Row Index for Key",
      Keywords = "serialization get find retrieve row index key name"
    ),
    Category = "Serialization | CSV"
  )
  int GetRowIndexForKey(FString Key);

  UPROPERTY(BlueprintReadOnly, Category = "Details")
  int ColumnCount;

  UPROPERTY(BlueprintReadOnly, Category = "Details")
  int RowCount;

  UPROPERTY(BlueprintReadOnly, Category = "Details")
  TArray<FString> ColumnNames;

  UPROPERTY(BlueprintReadOnly, Category = "Details")
  TArray<FString> RowKeys;

private:
  csv::CSVReader * parser;
  std::vector<csv::CSVRow> rows;

  friend class UDataSerializationBPLibrary;
};
