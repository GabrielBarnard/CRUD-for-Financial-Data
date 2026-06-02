# Change Log
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

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

