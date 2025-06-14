cmake_minimum_required(VERSION 3.10)
project(BSTBankingApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#Executable files (source)
add_executable(BSTBankingApp
    src/BankingAppMain.cpp
    src/Account.cpp
    src/SavingsAccount.cpp
    src/CheckingAccount.cpp
    src/BankingApp.cpp
)

# Header file directory
target_include_directories(BSTBankingApp PRIVATE include)