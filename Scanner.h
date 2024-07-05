/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2023
* Author: Chengkuan Zhao, Chang Liu
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
* File name: scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A22, A32.
* Date: Sep 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 100   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (start: &) */
	STR_T,		/*  2: String literal token */
	INT_T,		/*  3: Integer literal token*/
	FLT_T,		/*  4: Float literal token*/
	//STRV_T,		/*  5: string variable tokens*/
	//INTV_T,		/*  6: int variable tokens*/
	//FLTV_T,		/*  7: float variable tokens*/
	LPR_T,		/*  5: Left parenthesis token */
	RPR_T,		/*  6: Right parenthesis token */
	LBR_T,		/*  7: Left brace token */
	RBR_T,		/*  8: Right brace token */
	KW_T,		/*  9: Keyword token */
	EOS_T,		/*  10: End of statement (semicolon) */
	RTE_T,		/*  11: Run-time error token */
	//INL_T,		/* 15: Run-time error token */
	SEOF_T,		/* 16: Source end-of-file token */
	EQU_T,//=
	SVID_T,
	FVID_T,
	IVID_T,
	ART_OP_T,
	REL_OP_T,
	LOG_OP_T,
	COM_T
	
};

/* Define the number of ArithmeticOperators from the language */
#define ART_OP_SIZE 4

/* Define the list of ArithmeticOperators */
static jupiter_char* ArithmeticOperators_TABLE[ART_OP_SIZE] = {
	"OP_ADD","OP_SUB","OP_MUL","OP_DIV"
};

/* Define the number of RelationalOperators from the language */
#define REL_OP_SIZE 4

/* Define the list of RelationalOperators */
static jupiter_char* RelationalOperators_TABLE[REL_OP_SIZE] = {
	"OP_EQ","OP_NE","OP_GT","OP_LT"
};

/* Define the number of LogicalOperators from the language */
#define LOG_OP_SIZE 3

/* Define the list of LogicalOperators */
//static jupiter_char* LogicalOperators_TABLE[LOG_OP_SIZE] = {
//	"OP_AND","OP_OR","OP_NOT"
//};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;



/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	jupiter_intg codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	jupiter_intg intValue;						/* integer literal attribute (value) */
	jupiter_intg keywordIndex;					/* keyword index in the keyword table */
	jupiter_intg contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	jupiter_real floatValue;					/* floating-point literal attribute (value) */
	jupiter_char idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	jupiter_char errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	jupiter_byte flags;			/* Flags information */
	union {
		jupiter_intg intValue;				/* Integer value */
		jupiter_real floatValue;			/* Float value */
		jupiter_char* stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	jupiter_intg code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';', 
 *  white space, #comment\n , ',' , ';' , '-' , '+' , '*' , '/', # , 
 *  .&., .|. , .!. , SEOF.
 */



/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
/*L(0),  D(1), M(2), Q(3),P(4),I(5),S(6),F(7), E(8),  O(9)*/
#define CHRCOL2 '%'		// method
#define CHRCOL3 '\''	// quote
#define CHRCOL4 '.'		// period	
#define CHRCOL5 '^'		// int var
#define CHRCOL6 '#'		// string var id
#define CHRCOL7 '&'		// float vat id
#define CHRCOL8 '@'		// comment

/* These constants will be used on VID / MID function */
#define MNIDPREFIX '%'
#define IVIDPREFIX '^'
#define SVIDPREFIX '#'
#define FVIDPREFIX '&'


/* TO_DO: Error states and illegal state */
#define FS		100		/* Illegal state */
#define ESNR	21		/* Error state with no retract */
#define ESWR	22		/* Error state with retract */

 /* TO_DO: State transition table definition */
 /*Changed*/
#define TABLE_COLUMNS 11

/* TO_DO: Transition table - type of states defined in separate table */

// static jupiter_intg transitionTable[][TABLE_COLUMNS] = {
// 	/*[A-z], [0-9],    _,    &,    ', SEOF, other
// 	   L(0),  D(1), U(2), M(3), Q(4), E(5),  O(6) */
// 	{     1,  ESNR, ESNR, ESNR,    4, ESWR, ESNR}, // S0: NOAS
// 	{     1,     1,    1,    2, ESWR, ESWR,    3}, // S1: NOAS
// 	{    FS,    FS,   FS,   FS,   FS,   FS,   FS}, // S2: ASNR (MVID)
// 	{    FS,    FS,   FS,   FS,   FS,   FS,   FS}, // S3: ASWR (KEY)
// 	{     4,     4,    4,    4,    5, ESWR,    4}, // S4: NOAS
// 	{    FS,    FS,   FS,   FS,   FS,   FS,   FS}, // S5: ASNR (SL)
// 	{    FS,    FS,   FS,   FS,   FS,   FS,   FS}, // S6: ASNR (ES)
// 	{    FS,    FS,   FS,   FS,   FS,   FS,   FS}  // S7: ASWR (ER)
// };

static jupiter_intg transitionTable[][TABLE_COLUMNS] = {
	/*[A-z], [0-9],    &,    ',	     .,	intVar,	stringVar, floatVar,	comments,	SEOF, other
	   L(0),  D(1), M(2), Q(3),   P(4),	  I(5), 	S(6),	   F(7),	C(8)		E(9),  O(10) */
	{     1,     6, ESNR,    4,   ESNR,		10,		  13,		16,		19,			ESWR, ESNR}, // S0: NOAS
	{     1,     3,    2,	3,		3,		3,		3,		 	3,		3,		ESWR,    3}, // S1: NOAS
	{    FS,    FS,   FS,   FS,     FS,	   	FS,	  	  FS,	  	FS,		FS,			FS,   FS}, // S2: ASNR (MVID)
	{    FS,    FS,   FS,   FS,     FS,	   	FS,	  	  FS,	  	FS,		FS,			FS,   FS}, // S3: ASWR (KEY)
	{     4,     4,    4,    5,      4,	  	 4,	   	   4,		 4,		4,			ESWR,   4}, // S4: NOAS ?ESWR
	{    FS,    FS,   FS,   FS,     FS,		FS,	  	  FS,		FS,		FS,			FS,   FS}, // S5: ASNR (SL)
	{	  7,	 6,	   7,    7,      8,	   	 7,        7,   	 7,		7,			ESWR,    7}, // S6: NOAS ?ESWR
	{    FS,    FS,   FS,   FS,     FS,	 	FS,	  	  FS,		FS,		FS,			FS,   FS}, // S7: ASNR (IL)
	{     9,     8,    9,    9,   ESWR,	  	 9,	       9,		9,		9,			ESWR,    9}, // S8: NOAS
	{    FS,    FS,   FS,   FS,     FS,	 	FS,	      FS,		FS,		FS,			FS,   FS}, // S9: ASNR (FL)
	{	  11,  ESWR, ESWR, ESWR,  ESWR,   ESWR,	    ESWR,		ESWR,	ESWR,		ESWR, ESNR}, // S10: NOAS, ?ESNR not so sure
	{	  11,	 11, ESNR, ESNR,  ESWR,	 	12,	    ESNR,		ESWR,	ESWR,		ESNR, ESNR}, // S11: NOAS
	{    FS,    FS,   FS,   FS,     FS,	 	FS,	      FS,		FS,		FS,			FS,   FS}, // S12: IVID (integer variable)
	{	 14,  ESWR,	ESWR, ESWR,   ESNR,   ESWR,	    ESWR,		ESWR,	ESWR,		ESNR, ESNR}, // S13: NOAS
	{	 14,    14,	ESNR, ESNR,   ESNR,   ESNR,	      15,		ESWR,	ESWR,		ESNR, ESNR}, // S14: NOAS
	{    FS,    FS,   FS,   FS,     FS,	 	FS,	      FS,		FS,		FS,			FS,   FS}, // S15: SVID (string variable)
	{	 17,  ESNR,	ESNR, ESNR,   ESNR,	  ESNR,	    ESNR,		ESNR,	ESNR,		ESNR, ESNR}, // S16: NOAS
	{	 17,    17,	ESNR, ESNR,   ESNR,	  ESNR,	    ESNR,		18,		ESNR,		ESNR, ESNR}, // S17: NOAS
	{    FS,    FS,   FS,   FS,     FS,	    FS,	      FS,		FS,		FS,			FS,   FS}, // S18: FVID (float variable)
	{	 19,	19,	  19,   19,		19,		19,		  19,		19,		20,			19,	 19}, // S19: NOAS
	{    FS,    FS,   FS,   FS,     FS,	    FS,	      FS,		FS,		FS,			FS,   FS}, // S20: C comment
	{    FS,    FS,   FS,   FS,     FS,	    FS,	      FS,		FS,		FS,			FS,   FS}, // S21: ASNR (ES)
	{    FS,    FS,   FS,   FS,     FS,	    FS,	      FS,		FS,		FS,			FS,   FS}  // S22: ASWR (ER)
};

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
/*Changed*/
static jupiter_intg stateType[] = {
	NOFS, //S0 
	NOFS, //S1
	FSNR, //S2: MVID
	FSWR, //S3: KEY
	NOFS, //S4
	FSNR, //S5: SL
	NOFS, //S6
	FSNR, //S7: IL
	NOFS, //S8
	FSNR, //S9: FL
	NOFS, //S10
	NOFS, //S11
	FSNR, //S12: int variable
	NOFS, //S13
	NOFS, //S14
	FSNR, //S15: string varibale
	NOFS, //S16
	NOFS, //S17
	FSNR, //S18: float varibale
	NOFS, //S19
	FSNR, //S20: comment
	FSNR, //S21 ESNR
	FSWR  //S22 ESWR

	// NOFS, /* 00 */
	// NOFS, /* 01 */
	// FSNR, /* 02 (MID) - Methods */
	// FSWR, /* 03 (KEY) */
	// NOFS, /* 04 */
	// FSNR, /* 05 (SL) */
	// NOFS, /* 06 */
	// FSNR, /* 07 (IL)*/
	// NOFS, /* 08 */
	// NOFS, /* 09 */
	// FSNR, /* 10 (Int Var)*/
	// NOFS, /* 11 */
	// NOFS, /* 12 */
	// FSNR, /* 13 (String Var)*/
	// FSNR, /* 14 (Err1 - no retract) */
	// FSWR  /* 15 (Err2 - retract) */
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
jupiter_intg startScanner(ReaderPointer psc_buf);
Token tokenizer(jupiter_void);
static jupiter_intg nextClass(jupiter_char c);				/* character class function */
static jupiter_intg nextState(jupiter_intg, jupiter_char);		/* state machine function */
jupiter_void printToken(Token t);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(jupiter_char* lexeme);

/* Declare accepting states functions */
Token funcSL	(jupiter_char lexeme[]);
Token funcID	(jupiter_char lexeme[]);
Token funcKEY	(jupiter_char lexeme[]);
Token funcErr	(jupiter_char lexeme[]);
Token funcIL	(jupiter_char lexeme[]);
Token funcFL	(jupiter_char lexeme[]);
//Token funcSV(jupiter_char lexeme[]);
//Token funcIV(jupiter_char lexeme[]);
//Token funcFV(jupiter_char lexeme[]);
/* do we need fucntions for variables?*/

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcID,		/* MNID	[02] - Methods */
	funcKEY,	/* KEY  [03] - Keywords */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] - String Literal */
	NULL,//6
	funcIL,//7
	NULL,
	funcFL,//9
	NULL,
	NULL,//11
	funcID,
	NULL,//13
	NULL,
	funcID,//15
	NULL,
	NULL,//17
	funcID,
	NULL,//19
	NULL,
	funcErr,//21	/* ERR1 [06] - No retract */
	funcErr		/* ERR2 [07] - Retract */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 15

/* TO_DO: Define the list of keywords */
static jupiter_char* keywordTable[KWT_SIZE] = {
	"int",
	"real",
	"string",
	"if",
	"else",
	"elseif",
	"while",
	"do",
	"end",
	"and",
	"or",
	"not",
	"true",
	"false",
	"then",
};

/* About indentation (useful for positional languages (ex: Python, Cobol) */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	jupiter_char indentationCharType;
	jupiter_intg indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
jupiter_intg numScannerErrors;

#endif
