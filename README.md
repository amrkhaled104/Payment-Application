# Transaction Management System

Welcome to the **Transaction Management System**! This document will guide you through the installation, usage, and structure of the project.

## Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [File Structure](#file-structure)
- [Modules](#modules)
- [Future Enhancements](#future-enhancements)
- [Developer](#developer)

## Project Overview
The **Transaction Management System** is a robust application designed to handle and manage financial transactions and account data.

## Features
- **Transaction Handling**: Processes and stores transactions with various states.
- **Account Management**: Manages account data including balance and state.
- **Data Persistence**: Saves and loads data from CSV files.
- **Interactive Console Application**: Provides a console interface for operations.

## Installation
To set up the project, follow these steps:

1. **Clone the repository**:
    ```bash
    git clone https://github.com/yourusername/transaction-management-system.git
    ```

2. **Navigate to the project directory**:
    ```bash
    cd transaction-management-system
    ```

3. **Compile the project**:
    ```bash
    gcc -o transaction_management main.c app/app.c Handling/handling.c Server/server.c Terminal/terminal.c Card/card.c -I./include
    ```

4. **Run the application**:
    ```bash
    ./transaction_management
    ```

## Usage
1. **Start the Application**: Execute the compiled file to launch the system.
2. **Perform Transactions**: Follow the on-screen instructions.
3. **Save & Load Data**: Handled automatically.
4. **Exit the Application**: All data is securely saved.

## File Structure
```plaintext
transaction-management-system/
├── Handling/
│   ├── handling.c
│   ├── handling.h
├── app/
│   ├── app.c
│   ├── app.h
├── Server/
│   ├── server.c
│   ├── server.h
├── Terminal/
│   ├── terminal.c
│   ├── terminal.h
├── Card/
│   ├── card.c
│   ├── card.h
├── main.c
├── transactions.csv
├── accountDB.csv
└── README.md

```

## Modules
### Main Module
**File**: `main.c`

**Description**: Manages the application flow, initializes data, and handles user interactions.

### Handling Module
**File**: `handling.c`, `handling.h`

**Description**: Manages saving, loading, and manipulating transaction and account data.

### Application Module
**File**: `app.c`, `app.h`

**Description**: Handles core application logic such as transaction processing and card reporting.

## Future Enhancements
- **Improved Security**: Add encryption for CSV files.
- **Enhanced User Interface**: Develop a graphical UI.
- **Reporting & Analytics**: Add features for generating reports.

## Developer
This project was developed by [Amr Khaled](https://github.com/amrkhaled104). Visit my GitHub profile for more projects!

## Visuals
### ATM Machine
![ATM Machine](https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExZnp3bnd4dzJrenAwOGJiZzI0cm42ZDZnZmFleWowZ3U1b3ViOGdyZiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/9rwJNLBu8FMfixoIxL/giphy.gif)  
*Modern ATM machine.*

### Payment Terminal
![Payment Terminal](https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExZDg1aGI3cGVrcmx1ZHMzeno2OWFuMjFsOW8zMHk5M3lvMnc4NmE5OCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/TDyxBGZcViZnoye8iN/giphy.gif)  
*Electronic payment terminal.*

#If you've made it this far, dear reader, I'd like to share this with you:
(https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExM3BqZ3gxYmhqZWFzMnQ3d281NTRtZmN6bTRidXJnc3h1Y2Y3OWNpYiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/BYoRqTmcgzHcL9TCy1/giphy.gif)