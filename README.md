# CRUD for Financial Data

Loads stock data from .csv or .db input files to allow the user to access full CRUD functionality.

## Table of Contents

- [Project Structure](#project-structure)
- [Required Software](#required-software)
- [Installation](#installation)
- [Usage](#usage)

## Project Structure

```text
CRUD-for-Finacial-Data
├── CHANGELOG.md
├── CRUD for Financial Data.pro
├── README.md
├── inc
│   ├── CSVprocessor.hpp
│   ├── CSVwindow.hpp
│   ├── FileSelectionWindow.hpp
│   ├── SQLprocessor.hpp
│   └── SQLwindow.hpp
├── res
│   ├── Sample.csv
│   ├── Sample.db
│   ├── appIcon.ico
│   └── res.qrc
├── src
│   ├── CSVprocessor.cpp
│   ├── CSVwindow.cpp
│   ├── FileSelectionWindow.cpp
│   ├── SQLprocessor.cpp
│   ├── SQLwindow.cpp
│   └── main.cpp
├── ui
│   ├── CSVwindow.ui
│   ├── FileSelectionWindow.ui
│   └── SQLwindow.ui
└── win32
    ├── sqlite3.c
    └── sqlite3.h
```

## Required Software

Any software listed here is required to compile the program. However, if you use one of the pre-compiled releases, you won't have to download this software. Unless you are running this program on Linux, in which case you will need to download Qt.

- Qt:
    * Linux & Windows: https://www.qt.io/development/download
    * MacOS: This program has not been configured to run on MacOS. However, if you want to try, you can download Qt from the same link: https://www.qt.io/development/download

- SQLite
    * Linux: 
        * Pacman: sudo pacman sqlite
        * Advanced Package Tool (APT): sudo apt install sqlite3
        * X Binary Package System (XBPS): sudo xbps-install sqlite-devel
    * Windows: You do not need to install this software on Windows. Instead, the sqlite3.c and sqlite3.h files in the win32 folder will be used when you compile the program.
    * MacOS: This program has not been configured to run on MacOS 

## Installation

If you want to compile the program manually on Linux:

1. On the GitHub repository for this project. Click the button "Code" and then click "Download ZIP".
2. Unzip the downloaded zip file.
3. Open Qt Creator. 
4. Select the button that says "Open Project" and select the .pro file inside the unzipped folder.
5. Once inside the project, click the Run button at the bottom left side of the screen. This will compile and run the program.
6. To run the program again outside of Qt Creator, locate the bin folder in the unzipped folder and select your compiled executable that will be in the "Linux" subdirectory. 

If you want to compile the program manually on Windows:

1. On the GitHub repository for this project. Click the button "Code" and then click "Download ZIP".
2. Unzip the downloaded zip file.
3. Open Qt Creator. 
4. Select the button that says "Open Project" and select the .pro file inside the unzipped folder.
5. Once inside the project, click the Run button at the bottom left side of the screen. This will build and run the program.
6. In the file explorer, enter the folder in which you installed Qt.
7. Enter the folder that has your current Qt version number as its name.
8. Enter either the MSVC or MinGW folder, depending on which option you chose to compile the program.
9. Enter the bin folder. 
10. Open a PowerShell in this folder. 
11. Run the following command, but replace "(YOUR FOLDER HERE)" with the absolute or relative path to the executable file that Qt generated, which, in the folder you unzipped, will be at \bin\Windows\"CRUD for Financial Data.exe":
    * .\windeployqt.exe (YOUR FOLDER HERE)
12. To run the program, enter the \bin\Windows folder inside the folder you unzipped and click the "CRUD for Financial Data.exe" executable. 


If you want to use one of the pre-compiled releases:

1. Download either the Windows or Linux version from the releases segment on the right side of this project's GitHub page.
2. Unzip the downloaded file. To do this, you can use a tool like 7-Zip or WinRAR.
3. To run the program, enter the unzipped folder and double-click the 'CRUD for Financial Data' executable file.

## Usage

1. Run the program. Upon opening the program, you will be greeted by a screen with one text input field.
2. Put the relative or absolute location of the comma-separated values (.csv) or SQLite (.db) file you want to access.
3. Press the Enter button. This will put you into either the SQL window or the CSV window.
4. If you chose a CSV file:
    * To CREATE a new stock: Input the day the stock was purchased, the name of the stock, and the price of the stock. Do NOT enter the stock ID, as the program will select it automatically. Press the "Create" button to finalize this operation.
    * To READ a stock or stocks: If you want to read an individual stock, input the stock's ID. However, do not input any other fields. Then, press the "Read" button. If you want to read all the stocks, leave all input fields empty and press the "Read" button.
    * To UPDATE a stock: Input the ID of the stock you want to update and any input fields you want to modify. Then, press the "Update" button to finalize this operation.
    * To DELETE a stock: Input the ID of the stock you want to delete and press the "Delete" button to finalize the operation.
5. If you chose an SQL file
    * To CREATE a new stock: Input the day the stock was purchased, the name of the stock, and the price of the stock. Do NOT enter the stock ID, as the program will select it automatically. Press the "Create" button to finalize this operation.
    * To READ a stock or stocks: Place input into any fields that you want to search with (e.g., "Stock Price" as 300 and "Date Purchased" as 2025-01-01). Then, press the "Read" button to display the stocks.
    * To UPDATE a stock: Input the ID of the stock you want to update and any input fields you want to modify. Then, press the "Update" button to finalize this operation.
    * To DELETE a stock: Input the ID of the stock you want to delete and press the "Delete" button to finalize the operation.
6. To exit the program, click the close button at the top right. Any files will be saved automatically.
