/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2023
* Author: Chang Liu and Chengkuan Zhao
* Professors: Paulo Sousa
************************************************************

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@                                                               @@@@
@@          /       ==============================        /          @@
@         ////           @@       @@ #@                  ////         @
@         ////*          @@ @%  @ @@    @@  @ #@#       /////         @
@     ((( ////))))   @@  @% @%  @ @@ #@ @@  @ #@@#   ///////( ///     @
@     ((((,/ )))))    @@@@   @@@  @@ ##  @@@   #@#   ///// ,/////     @
@     (((((/)))((    ------------------------------    ((((./////*    @
@    //*./ /  .///   ---  PROGRAMMING LANGUAGE  ---  ////   / ( (//   @
@    ///// / /////   ==============================  * ////* / ////   @
@     ///// ///// ((                               (( ///// /////     @
@    ((((   / , (((((                             (((((  //   /(((    @
@    (((((((/ . (((((                          (((((* / (((((((       @
@      (((((( //((((/((((                    *((((/((((/( (((((/      @
@       .//,   * /   (((((                   (((((  ///    .//.       @
@     ,////////./(  (((((* ////         (///(((((( ,/(,////////       @
@         //////// ,// ((( /////,     ////// ((( //  /////// *        @
@            (((((((((,// * /////     /////   (//(((((((((            @
@            ((((((((((((/////         //.///  (((((((((((.           @
@                   (///////// //(   (//.//////////                   @
@                  (/////////             //////////                  @
@                                                                     @
@@          A L G O N Q U I N   C O L L E G E  -  2 0 2 3 W          @@
@@@@                                                               @@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

*/

/*
************************************************************
* File name: parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token lookahead;
extern BufferReader* stringLiteralTable;
extern jupiter_intg line;
extern Token tokenizer();
extern jupiter_char* keywordTable[];
jupiter_intg syntaxErrorNumber = 0;

#define STR_LANGNAME	"Jupiter"
#define LANG_WRTE		"print%"
#define LANG_READ		"input%"
#define LANG_MAIN		"main%"

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	KW_int,
	KW_real,
	KW_string,
	KW_if,
	KW_else,
	KW_elseif,
	KW_while,
	KW_do,
	KW_end,
	KW_and,
	KW_or,
	KW_not,
	KW_true,
	KW_false,
	KW_then,
};




/* Function definitions */
jupiter_void startParser();
jupiter_void matchToken(jupiter_intg, jupiter_intg);
jupiter_void syncErrorHandler(jupiter_intg);
jupiter_void printError();

/* TO_DO: Place ALL non-terminal function declarations */
jupiter_void codeSession();
jupiter_void dataSession();
jupiter_void optVarListDeclarations();
jupiter_void optionalStatements();
jupiter_void outputStatement();
jupiter_void outputVariableList();
jupiter_void program();
jupiter_void statement();
jupiter_void statements();
jupiter_void statementsPrime();
jupiter_void assignmentStatement();
jupiter_void assignmentExpression();
jupiter_void selectionStatement();
jupiter_void iterationStatement();
jupiter_void inputStatement();
jupiter_void inputVariableList();
jupiter_void variableList();
jupiter_void variableListPrime();
jupiter_void variableIdentifier();
jupiter_void conditionalExpressionPrime();
jupiter_void arithmeticExpression();
jupiter_void arithmeticExpressionPrime();
jupiter_void primaryArithmeticExpression();
jupiter_void stringExpression();
jupiter_void conditionalExpression();
jupiter_void logicalExpression();
jupiter_void relationalExpression();
jupiter_void additiveArithmeticExpression();
jupiter_void multiplicativeArithmeticExpression();
jupiter_void primaryAirthmeticRelationalExpressionOperator();
jupiter_void primaryAirthmeticRelationalExpression();

#endif
