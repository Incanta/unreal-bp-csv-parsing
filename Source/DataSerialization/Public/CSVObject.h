// Copyright Incanta Games 2020. All Rights Reserved.

#pragma once

#include "UObject/Object.h"
#include "csv.hpp"
#include <sstream>

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

  UFUNCTION(
    BlueprintCallable,
    meta = (
      DisplayName = "Generate CSV String",
      Keywords = "serialization get to generate csv tsv comma tab separated value string serialize"
    ),
    Category = "Serialization | CSV"
  )
  FString GenerateCSVString(
    bool IncludeHeaderRow = true,
    FString DelimiterCharacter = ",",
    FString QuoteCharacter = "\""
  );

  UFUNCTION(
    BlueprintCallable,
    meta = (
      DisplayName = "Set Column Names",
      Keywords = "serialization set column header names row"
    ),
    Category = "Serialization | CSV"
  )
  void SetColumnNames(
    TArray<FString> ColumnNames
  );

  UFUNCTION(
    BlueprintCallable,
    meta = (
      DisplayName = "Add Column Name",
      Keywords = "serialization add column header name row"
    ),
    Category = "Serialization | CSV"
  )
  void AddColumnName(
    FString ColumnName
  );

  UFUNCTION(
    BlueprintCallable,
    meta = (
      DisplayName = "Add Row",
      Keywords = "serialization add row"
    ),
    Category = "Serialization | CSV"
  )
  void AddRow(
    TArray<FString> Cells
  );

  UFUNCTION(
    BlueprintCallable,
    meta = (
      DisplayName = "Insert Row",
      Keywords = "serialization insert row"
    ),
    Category = "Serialization | CSV"
  )
  void InsertRow(
    TArray<FString> Cells,
    int RowIndex
  );

  UFUNCTION(
    BlueprintCallable,
    meta = (
      DisplayName = "Add Cell",
      Keywords = "serialization add cell"
    ),
    Category = "Serialization | CSV"
  )
  void AddCell(
    FString Value,
    int RowIndex
  );

  UFUNCTION(
    BlueprintCallable,
    meta = (
      DisplayName = "Insert Cell",
      Keywords = "serialization insert cell"
    ),
    Category = "Serialization | CSV"
  )
  void InsertCell(
    FString Value,
    int RowIndex,
    int ColumnIndex
  );

  UFUNCTION(
    BlueprintCallable,
    meta = (
      DisplayName = "Delete Row",
      Keywords = "serialization delete row"
    ),
    Category = "Serialization | CSV"
  )
  void DeleteRow(
    int RowIndex
  );

  UFUNCTION(
    BlueprintCallable,
    meta = (
      DisplayName = "Delete Cell",
      Keywords = "serialization delete cell"
    ),
    Category = "Serialization | CSV"
  )
  void DeleteCell(
    int RowIndex,
    int ColumnIndex
  );

  UFUNCTION(
    BlueprintCallable,
    meta = (
      DisplayName = "Set Cell",
      Keywords = "serialization set cell"
    ),
    Category = "Serialization | CSV"
  )
  void SetCell(
    FString Value,
    int RowIndex,
    int ColumnIndex
  );

  UFUNCTION(
    BlueprintCallable,
    meta = (
      DisplayName = "Clear CSV Object",
      Keywords = "serialization clear csv object"
    ),
    Category = "Serialization | CSV"
  )
  void Clear();

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
  std::vector<std::vector<std::string>> rows;

  friend class UDataSerializationBPLibrary;
};
