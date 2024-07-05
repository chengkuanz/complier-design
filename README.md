# Compiler Design

This project is part of the Compilers course (CST8152 Winter 2023) at Algonquin College. It includes implementations for a reader, scanner, and parser for a hypothetical programming language named Jupiter.

## Developed Components

The project involves developing the front-end stage of a compiler in C, consisting of a Reader, Scanner, and Parser for a custom programming language.

### Reader
- Handles reading source code files, storing content, and managing buffer operations.
- Creates and manages buffers for storing source code.
- Reads source code from files.
- Handles different buffer modes: fixed, additive, and multiplicative.
- Prints buffer contents and properties.

### Scanner
- Tokenizes source code into predefined token classes.
- Implements a Finite State Machine (FSM) for token recognition.
- Handles special cases like comments and end-of-file.
- Tokenizes input data, incorporating finite state machines, token attributes, and error handling for lexical analysis.

### Parser
- Analyzes tokenized source code for syntactic correctness.
- Implements various non-terminal functions for grammar rules.
- Provides error handling and synchronization during parsing.
- Uses recursive descent parsing and Backus-Naur Form (BNF) to validate the grammar and structure of the source code.

## File Structure

### Main Files
- **Compilers.h**: Defines functions and includes necessary headers.
- **Compilers.c**: Contains the main function to drive the compilation process.
- **MainReader.c**: Main code for the Reader module.
- **MainScanner.c**: Main code for the Scanner module.
- **MainParser.c**: Main code for the Parser module.

### Headers and Implementations
- **reader.h**: Header for the Reader module.
- **Reader.c**: Implementation of the Reader module.
- **scanner.h**: Header for the Scanner module.
- **Scanner.c**: Implementation of the Scanner module.
- **parser.h**: Header for the Parser module.
- **Parser.c**: Implementation of the Parser module.

## Development Environment

- **Programming Languages**: C
- **Development Environment**: MS Visual Studio 2022

## Usage

To run the project, navigate to the `complier-design/out/build/x64-debug` directory, and run the `A32.bat` file in Windows.

## Authors

This game was developed by [Chengkuan Zhao](https://github.com/chengkuanz) and [Chang Liu](https://github.com/lyalc542), between January 2023 and April 2023. Feel free to reach out for any questions.

last update: July 5 2024
