# Change Log
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.3.2] - UNRELEASED

### Added

- Better input validation in CSVprocessor and CSVwindow.
- Try Catch statement in FileSelectionWindow for CSVwindow that informs the user if something is wrong with their chosen file.

### Fixed

- The program now prevents invalid .csv input files with too many parts (commas) from being loaded into CSVprocessor.
- Invalid dates can no longer be added via the CRUD Update function in CSVwindow.
- Invalid prices no longer crash the program when used in the CSVwindow.

### Changed

- Moved date validation for the CRUD add function in CSVwindow from the add function into the fetchUserInput() function.
- .gitignore now ignores Sample.csv.backup file in the res folder, which is generated automatically upon using the Sample.csv file.

### Removed

- Functionality to convert entryDate in csvProcessor and csvWindow to a std::string.

## [0.3.1] - 2026-06-08

### Added

- Builds now output to bin/Linux or bin/Windows folder, depending on the operating system, rather than directly to the bin folder. 
- win32 folder with sqlite3.c and slite3.h files to enable the program to build on Windows.
- .gitattributes folder with linguist-vendored=true for the win32 folder to prevent GitHub from listing the project as almost entirely made in C because of the sqlite3.h and sqlite3.c files.

### Fixed

- Date now displays properly on windows with no ? values.
- Create button in CSVprocessor now validates date as yyyy-mm-dd format when adding a new entry.

### Changed

- Background color to a shade of black.
- Stock entryDate in CSVprocessor from std::time_t to std::string.
- Stock price in CSVprocessor from int to double.

### Removed

- Functionality to convert entryDate in csvProcessor and csvWindow to a std::string.

## [0.3.0] - 2026-06-02

### Added

- Full SQL .db file CRUD functionality with input validation and parameterized queries.
- Table called 'stocks' to Sample.db with several entries.
- SQL .db file validation in SQLprocessor's constructor.

### Fixed

- Nothing of note.

### Changed

- Stocks std::time_t variable entryDate to std::string in CSVprocessor - using std::time_t wasn't actually needed, and std::string makes things drastically simpler.
- SQLprocessor.ui component order - similar to CSVprocessor.ui, ordering now reflects the name (e.g., pushButton_2 comes before pushButton_3 in the Qt GUI).
- Price in SQLprocessor from an int to a double.

### Removed

- Nothing of note.

## [0.2.0] - 2026-05-31

### Added

- Full CSV CRUD functionality with input validation.
- EditText fields for Stock ID, Name, Price, and entryDate.
- Fully functional CRUD buttons in CSVwindow.

### Fixed

- Nothing.

### Changed

- Item ordering in CSVwindow.ui - numbering is now representative of the actual ordering of the files.
- Privacy of Stock in CSVprocessor - Stock is now public so it can be easily accesed from CSVwindow.
- Updated Sample.csv

### Removed
- Redundant files GUImanager.cpp and GUImanager.hpp.
- Redundant "Enter" button in CSVwindow.

## [0.1.0] - 2026-05-21

### Added

- Proper folder structure, including inc (header files), res (resources), src (.cpp files), ui (Qt .ui files).
- Qt GUI with three separate windows, one window to select a file in, one window to process .db files, and one window to process .csv files. 
- App icon with res.qrc.
- Appropriate levels of commenting in newly added files.
- Small Sample.csv file.
- Incomplete Sample.db file.
- CHANGELOG.md.

### Fixed
- Nothing - This is the first version.

### Changed
- Nothing - This is the first version.

### Removed
- Nothing - This is the first version.

