# Change Log
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

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

