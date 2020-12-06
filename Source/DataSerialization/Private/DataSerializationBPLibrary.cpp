// Copyright Incanta Games 2020. All Rights Reserved.

#include "DataSerializationBPLibrary.h"

UDataSerializationBPLibrary::UDataSerializationBPLibrary(
  const FObjectInitializer& ObjectInitializer
) : Super(ObjectInitializer) {
  //
}

UCSVObject * UDataSerializationBPLibrary::ParseCSVRows(
  FString CSVString,
  TArray<FString> ColumnNames,
  FString DelimiterCharacter,
  FString QuoteCharacter,
  int HeaderRow,
  int KeysColumn,
  int FirstColumn
) {
  UCSVObject * csvObject = NewObject<UCSVObject>();
  csv::CSVFormat format;

  if (DelimiterCharacter.Len() == 0) {
    format.delimiter(',');
  } else {
    char * c = TCHAR_TO_ANSI(*DelimiterCharacter);
    format.delimiter(c[0]);
  }

  if (QuoteCharacter.Len() == 0) {
    format.quote(false);
  } else {
    char * c = TCHAR_TO_ANSI(*QuoteCharacter);
    format.quote(c[0]);
  }

  if (HeaderRow < 0) {
    format.no_header();
  } else {
    format.header_row(HeaderRow);
  }

  if (ColumnNames.Num() > 0) {
    std::vector<std::string> stdColNames;

    for (FString name : ColumnNames) {
      stdColNames.push_back(TCHAR_TO_ANSI(*name));
    }

    format.column_names(stdColNames);
  }

  auto inputString = static_cast<std::string>(TCHAR_TO_ANSI(*CSVString));
  std::stringstream stream(inputString.data());
  csvObject->parser = new csv::CSVReader(stream, format);

  // fill column names
  if (HeaderRow >= 0) {
    auto rowColumnNames = csvObject->parser->get_col_names();
    if (rowColumnNames.size() > 0) {
      for (std::string name : rowColumnNames) {
        csvObject->ColumnNames.Push(name.c_str());
      }
    }
  }

  for (auto & row : *csvObject->parser) {
    if (row.size() > static_cast<unsigned int>(csvObject->ColumnCount)) {
      csvObject->ColumnCount = row.size();
    }

    if (KeysColumn >= 0 && row.size() > static_cast<unsigned int>(KeysColumn)) {
      std::string value = row[KeysColumn].get();
      csvObject->RowKeys.Push(value.c_str());
    }

    csvObject->rows.push_back(row);

    csvObject->RowCount++;
  }

  return csvObject;
}
