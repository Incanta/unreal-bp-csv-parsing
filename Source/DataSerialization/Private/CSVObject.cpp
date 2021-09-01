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
      std::string value = row[columnIndex];
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
      std::string value = row[ColumnIndex];
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
    rowValues.Push(cell.c_str());
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
    rowValues.Push(cell.c_str());
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

FString UCSVObject::GenerateCSVString(
  bool IncludeHeaderRow,
  FString DelimiterCharacter,
  FString QuoteCharacter
) {
  std::stringstream ss;

  char delim = ',';
  char quote = '"';
  if (DelimiterCharacter.Len() != 0) {
    char * c = TCHAR_TO_ANSI(*DelimiterCharacter);
    delim = c[0];
  }

  if (QuoteCharacter.Len() != 0) {
    char * c = TCHAR_TO_ANSI(*QuoteCharacter);
    quote = c[0];
  }

  csv::DelimWriter<std::stringstream> writer(ss, delim, quote);

  if (IncludeHeaderRow) {
    std::vector<std::string> temp;
    for (auto & name : this->ColumnNames) {
      temp.push_back(TCHAR_TO_UTF8(*name));
    }
    writer << temp;
  }

  for (auto & row : this->rows) {
    writer << row;
  }

  return ss.str().c_str();
}

void UCSVObject::SetColumnNames(TArray<FString> _ColumnNames) {
  this->ColumnNames = _ColumnNames;
  if (this->ColumnNames.Num() > this->ColumnCount) {
    this->ColumnCount = this->ColumnNames.Num();
  }
}

void UCSVObject::AddColumnName(FString ColumnName) {
  this->ColumnNames.Add(ColumnName);
  if (this->ColumnNames.Num() > this->ColumnCount) {
    this->ColumnCount = this->ColumnNames.Num();
  }
}

void UCSVObject::AddRow(TArray<FString> Cells) {
  std::vector<std::string> row;
  for (auto & cell : Cells) {
    row.push_back(TCHAR_TO_ANSI(*cell));
  }
  this->rows.push_back(row);
  this->RowCount++;
}

void UCSVObject::InsertRow(TArray<FString> Cells, int RowIndex) {
  if (RowIndex < 0) {
    this->AddRow(Cells);
  } else if (RowIndex >= this->RowCount) {
    // Add empty rows until we're at the point where we can just append the row
    while (RowIndex > this->RowCount) {
      this->AddRow({});
    }
    this->AddRow(Cells);
  } else {
    std::vector<std::string> row;
    for (auto & cell : Cells) {
      row.push_back(TCHAR_TO_ANSI(*cell));
    }
    auto it = this->rows.begin() + RowIndex;
    this->rows.insert(it, row);
    this->RowCount++;
  }
}

void UCSVObject::AddCell(FString Value, int RowIndex) {
  if (RowIndex < 0) {
    this->AddRow({ Value });
  } else if (RowIndex >= this->RowCount) {
    // Add empty rows until we're at the point where we can just append the row
    while (RowIndex > this->RowCount) {
      this->AddRow({});
    }
    this->AddRow({ Value });
  } else {
    auto row = this->rows.at(RowIndex);
    row.push_back(TCHAR_TO_ANSI(*Value));
    if (row.size() > this->ColumnCount) {
      this->ColumnCount = row.size();
    }
  }
}

void UCSVObject::InsertCell(FString Value, int RowIndex, int ColumnIndex) {
  if (RowIndex < 0) {
    this->AddRow({});
  }

  // Add empty rows until we're at the point where we can just append the row
  while (RowIndex >= this->RowCount) {
    this->AddRow({});
  }

  auto row = this->rows.at(RowIndex);
  std::string valString(TCHAR_TO_ANSI(*Value));

  if (ColumnIndex < 0) {
    row.push_back(valString);
    if (row.size() > this->ColumnCount) {
      this->ColumnCount = row.size();
    }
    return;
  }

  if (ColumnIndex >= row.size()) {
    while (ColumnIndex > row.size()) {
      row.push_back("");
    }
    row.push_back(valString);
    if (row.size() > this->ColumnCount) {
      this->ColumnCount = row.size();
    }
    return;
  }

  auto it = row.begin() + ColumnIndex;
  row.insert(it, valString);

  if (row.size() > this->ColumnCount) {
    this->ColumnCount = row.size();
  }
}

void UCSVObject::DeleteRow(int RowIndex) {
  if (RowIndex < 0 || RowIndex >= this->RowCount) {
    return;
  }

  auto it = this->rows.begin() + RowIndex;
  this->rows.erase(it);
  this->RowCount--;
}

void UCSVObject::DeleteCell(int RowIndex, int ColumnIndex) {
  if (RowIndex < 0 || ColumnIndex < 0 || RowIndex >= this->RowCount) {
    return;
  }

  auto row = this->rows.at(RowIndex);

  if (ColumnIndex >= row.size()) {
    return;
  }

  auto it = row.begin() + ColumnIndex;
  row.erase(it);
}

void UCSVObject::SetCell(
  FString Value,
  int RowIndex,
  int ColumnIndex
) {
  if (RowIndex < 0) {
    this->AddRow({});
  }

  // Add empty rows until we're at the point where we can just append the row
  while (RowIndex >= this->RowCount) {
    this->AddRow({});
  }

  auto row = this->rows.at(RowIndex);
  std::string valString(TCHAR_TO_ANSI(*Value));

  if (ColumnIndex < 0) {
    row.push_back(valString);
    if (row.size() > this->ColumnCount) {
      this->ColumnCount = row.size();
    }
    return;
  }

  if (ColumnIndex >= row.size()) {
    while (ColumnIndex > row.size()) {
      row.push_back("");
    }
    row.push_back(valString);
    if (row.size() > this->ColumnCount) {
      this->ColumnCount = row.size();
    }
    return;
  }

  auto it = row.begin() + ColumnIndex;
  row.insert(it, valString);

  if (row.size() > this->ColumnCount) {
    this->ColumnCount = row.size();
  }
}

void UCSVObject::Clear() {
  // TODO: we probably should use the heap and delete things from memory
  this->rows.clear();
}
