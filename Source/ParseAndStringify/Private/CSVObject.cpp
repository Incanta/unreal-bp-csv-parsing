// Copyright Incanta Games 2020. All Rights Reserved.

#include "CSVObject.h"

UCSVObject::UCSVObject(
  const FObjectInitializer& ObjectInitializer
) : Super(ObjectInitializer) {
  //
}

TArray<FString> UCSVObject::GetColumnByName(FString ColumnName) {
  TArray<FString> columnValues;

  int columnIndex = this->ColumnNames.Find(ColumnName);

  if (columnIndex == INDEX_NONE) {
    return columnValues;
  }

  for (auto & row : this->rows) {
    if (row.size() > static_cast<unsigned int>(columnIndex)) {
      std::string value = row[columnIndex].get();
      columnValues.Push(value.c_str());
    }
  }

  return columnValues;
}

TArray<FString> UCSVObject::GetColumnByIndex(int ColumnIndex) {
  TArray<FString> columnValues;

  if (ColumnIndex < 0 || ColumnIndex >= this->ColumnCount) {
    return columnValues;
  }

  for (auto & row : this->rows) {
    if (row.size() > static_cast<unsigned int>(ColumnIndex)) {
      std::string value = row[ColumnIndex].get();
      columnValues.Push(value.c_str());
    }
  }

  return columnValues;
}

TArray<FString> UCSVObject::GetRowByKey(FString RowKey) {
  TArray<FString> rowValues;

  int rowIndex = this->RowKeys.Find(RowKey);

  if (rowIndex == INDEX_NONE) {
    return rowValues;
  }

  auto row = this->rows.at(rowIndex);

  for (auto & cell : row) {
    std::string value = cell.get();
    rowValues.Push(value.c_str());
  }

  return rowValues;
}

TArray<FString> UCSVObject::GetRowByIndex(int RowIndex) {
  TArray<FString> rowValues;

  if (RowIndex < 0 || RowIndex >= this->RowCount) {
    return rowValues;
  }

  auto row = this->rows.at(RowIndex);

  for (auto & cell : row) {
    std::string value = cell.get();
    rowValues.Push(value.c_str());
  }

  return rowValues;
}

FString UCSVObject::GetCellByNameAndKey(FString ColumnName, FString RowKey) {
  int columnIndex = this->parser->index_of(TCHAR_TO_ANSI(*ColumnName));

  if (columnIndex == csv::CSV_NOT_FOUND) {
    return FString();
  }

  TArray<FString> rowValues = this->GetRowByKey(RowKey);

  if (columnIndex >= rowValues.Num()) {
    return FString();
  }

  return rowValues[columnIndex];
}

FString UCSVObject::GetCellByIndices(int ColumnIndex, int RowIndex) {
  if (ColumnIndex < 0 || ColumnIndex >= this->ColumnCount) {
    return FString();
  }

  TArray<FString> rowValues = this->GetRowByIndex(RowIndex);

  if (ColumnIndex >= rowValues.Num()) {
    return FString();
  }

  return rowValues[ColumnIndex];
}

int UCSVObject::GetColumnIndexForName(FString Name) {
  return this->ColumnNames.Find(Name);
}

int UCSVObject::GetRowIndexForKey(FString Key) {
  return this->RowKeys.Find(Key);
}
