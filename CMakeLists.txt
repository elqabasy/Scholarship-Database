cmake_minimum_required(VERSION 3.10)

# Project name and language
project(DATABASE VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(
    SOURCES  
    source/Database.cpp
    source/Applications.cpp
    source/BankAccounts.cpp
    source/Fields.cpp
    source/Nationalities.cpp
    source/Payments.cpp
    source/Persons.cpp
    source/ScholarsAccounts.cpp
    source/Scholarships.cpp
    source/StatusCategories.cpp
)

# Create executable
add_executable(${PROJECT_NAME} 
    main.cpp 
    ${SOURCES}
)

# Include header files
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/source)


link_directories(/source)
include_directories(/include)
target_link_libraries(${PROJECT_NAME} sqlite3)