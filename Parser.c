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
* File name: Parser.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
/* TO_DO: This is the function to start the parser - check your program definition */

jupiter_void startParser() {
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
/* TO_DO: This is the main code for match - check your definition */
jupiter_void matchToken(jupiter_intg tokenCode, jupiter_intg tokenAttribute) {
	jupiter_intg matchFlag = 1;
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
/* TO_DO: This is the function to handler error - adjust basically datatypes */
jupiter_void syncErrorHandler(jupiter_intg syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
/* TO_DO: This is the function to error printing - adjust basically datatypes */
jupiter_void printError() {
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case EOS_T:
		printf("NA\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> main& { <opt_statements> }
 * FIRST(<program>)= {MNID_T (main&)}.
 ***********************************************************
 */
jupiter_void program() {
	switch (lookahead.code) {
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_MAIN, 5) == 0) {
			
			matchToken(MNID_T, NO_ATTR);
			
			matchToken(LBR_T, NO_ATTR);
			
			dataSession();
			
			codeSession();
			
			matchToken(RBR_T, NO_ATTR);
			break;
		}
		else {
			//printf("program-else \n");
			printError();
		}
	case SEOF_T:
		//printf("program-SEOF_T\n");
		; // Empty
		break;
	default:
		//printf("program-default\n");
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/*
 ************************************************************
 * dataSession
 * BNF: <dataSession> -> data { <opt_varlist_declarations> }
 * FIRST(<program>)= {KW_T (KW_data)}.
 ***********************************************************
 */
jupiter_void dataSession() {
	//(KW_T, KW_data);
	//matchToken(LBR_T, NO_ATTR);
	optVarListDeclarations();
	//matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Data section parsed");
}

/*
 ************************************************************
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_real), KW_T (KW_string)}.
 ***********************************************************
 */
jupiter_void optVarListDeclarations() {
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType == KW_int || lookahead.attribute.codeType == KW_real || lookahead.attribute.codeType == KW_string) {
			if (lookahead.attribute.codeType == KW_int) {
				matchToken(KW_T, KW_int);
				variableList();//doing
				matchToken(EOS_T, NO_ATTR);
				printf("%s%s\n", STR_LANGNAME, ": Integer variable list declaration parsed");
				
			}
			else if (lookahead.attribute.codeType == KW_real) {
				matchToken(KW_T, KW_real);
				variableList();//doing
				matchToken(EOS_T, NO_ATTR);
				printf("%s%s\n", STR_LANGNAME, ": Float variable list declaration parsed");
				
			}
			else if (lookahead.attribute.codeType == KW_string) {
				matchToken(KW_T, KW_string);
				variableList();//doing
				matchToken(EOS_T, NO_ATTR);
				printf("%s%s\n", STR_LANGNAME, ": String variable list declaration parsed");
				
			}
			else {
				; // Empty
			}
			printf("%s%s\n", STR_LANGNAME, ": Variable List Declaration parsed");
			optVarListDeclarations();
			//printf("%s%s\n", STR_LANGNAME, ":  Variable List Declarations parsed");
		}
		
		else {
			//; // Empty
			printf(" Optional Variable List not 3 types\n");
		}
		//3 times
		//printf("%s%s\n", STR_LANGNAME, ": Variable List Declarations parsed");
		break;
		
	default:
		printf("%s%s\n", STR_LANGNAME, ": optional Variable List Declarations parsed");
		; // Empty
	}
	
	
	
}

/*
 ************************************************************
 * Variable List
 * BNF: <variable list> -> <variable identifier> <variable listPrime>
 * FIRST(<variable list>) = { IVID_T, FVID_T, SVID_T }
 ***********************************************************
 */
jupiter_void variableList() {
	variableIdentifier();
	variableListPrime();
}

jupiter_void variableListPrime() {
	switch (lookahead.code) {
	case COM_T:
		matchToken(COM_T, NO_ATTR);
		variableList();
		break;
	case RPR_T://
		//used in output statement
		//printf("RBR_T\n");
		break;
	case EOS_T:
		;
		//printf("%s%s\n", STR_LANGNAME, ": int or string or float Variable List parsed ");
		 // Empty
		break;
	default:
		//printf("variableListPrime\n");
		printError();
	}
	//printf("%s%s\n", STR_LANGNAME, ": Variable List Prime parsed");
}

/*
 ************************************************************
 * Variable Identifier
 * BNF: <variable identifier> -> IVID_T | SVID_T | FVID_T
 * FIRST(<variable identifier>) = { IVID_T, SVID_T, FVID_T }
 ***********************************************************
 */
jupiter_void variableIdentifier() {
	switch (lookahead.code) {
	case IVID_T:
		matchToken(IVID_T, NO_ATTR);
		printf("%s%s\n", STR_LANGNAME, ": Integer Variable Identifier parsed");
		break;
	case SVID_T:
		matchToken(SVID_T, NO_ATTR);
		printf("%s%s\n", STR_LANGNAME, ": String Variable Identifier parsed");
		break;
	case FVID_T:
		matchToken(FVID_T, NO_ATTR);
		printf("%s%s\n", STR_LANGNAME, ": Float Variable Identifier parsed");
		break;
	default:
		printf("variableIdentifier\n");
		printError();
	}
	//variableName();
	//printf("%s%s\n", STR_LANGNAME, ": Variable List Identifier parsed");
}



/*
 ************************************************************
 * codeSession statement
 * BNF: <codeSession> -> code { <opt_statements> }
 * FIRST(<codeSession>)= {KW_T (KW_code)}.
 ***********************************************************
 */
jupiter_void codeSession() {
	//matchToken(KW_T, KW_code);
	//matchToken(LBR_T, NO_ATTR);
	optionalStatements();
	//matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Code Session parsed");
}

/* TO_DO: Continue the development (all non-terminal functions) */

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print%), MNID_T(input%) }
 ***********************************************************
 */
jupiter_void optionalStatements() {
	switch (lookahead.code) {
	case IVID_T:
	case FVID_T:
	case SVID_T:
	case KW_T:
		statements();
		break;
	case MNID_T:
		if ((strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) ||
			(strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0)) {
			statements();
			break;
		}
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input%), MNID_T(print%) }
 ***********************************************************
 */
jupiter_void statements() {
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T, 
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input%), MNID_T(print%) }
 ***********************************************************
 */
jupiter_void statementsPrime() {
	switch (lookahead.code) {
	case IVID_T:
	case FVID_T:
	case SVID_T:
	case KW_T:
		statement();
		statementsPrime();
		break;
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0|| strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0) {
			statements();
			statementsPrime();
			break;
		}
		
	default:
		; //empty string
	}
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input%) MNID_T(print%) }
 ***********************************************************
 */
jupiter_void statement() {
	switch (lookahead.code) {
	case IVID_T:
	case FVID_T:
	case SVID_T:
		//printf("assignment\n");
		assignmentStatement();
		break;
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case KW_if:
			selectionStatement();
			break;
		case KW_while:
			iterationStatement();
			break;
		default:
			printf("statement\n");
			printError();
		}
		break;
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			outputStatement();
		}
		else if (strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0) {
			inputStatement();
		}
		break;
	case SEOF_T:
		break;
	default:
		printf("statement\n");
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}




/*
 ************************************************************
 * Assignment statement
 * BNF: <assignment statement> -> <assignment expression> ;
 * FIRST(<assignment statement>) = { IVID_T, FVID_T, SVID_T }
 ***********************************************************
 */
jupiter_void assignmentStatement() {
	assignmentExpression();
	//matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Assignment statement parsed");
}

/*
 ************************************************************
 * Assignment expression
 * BNF: <assignment expression> -> <arithmetic expression> | <string expression>
 * FIRST(<assignment expression>) = { IVID_T, FVID_T, SVID_T }
 ***********************************************************
 */
jupiter_void assignmentExpression() {
	switch (lookahead.code) {
	case IVID_T:
	case FVID_T:
		matchToken(lookahead.code, NO_ATTR);
		matchToken(REL_OP_T, 0);//equal sign
		arithmeticExpression();
		printf("%s%s\n", STR_LANGNAME, ": Assignment expression (Arithmetic Expression) parsed");
		break;
	case SVID_T:
		matchToken(SVID_T, NO_ATTR);
		matchToken(lookahead.code, lookahead.attribute.codeType);//equal sign
		stringExpression();
		//printf ("Assignment expression String Expression parsed\n");
		break;
	default:
		printf("assignment expression\n");
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Assignment expression parsed");
}

/*
 ************************************************************
 * Arithmetic expression
 * BNF: <arithmetic expression> -> <primary arithmetic expression><arithmetic expression prime>
 * FIRST(<arithmetic expression>) = { AVID_T, FPL_T, INL_T, ( }
 ***********************************************************
 */
jupiter_void arithmeticExpression() {
	primaryArithmeticExpression();
	arithmeticExpressionPrime();
	//additiveArithmeticExpression();
	//multiplicativeArithmeticExpression();
	
	switch (lookahead.code) {
	case EOS_T:
		matchToken(EOS_T, NO_ATTR);
		break;
	default:
		; 
	}
	printf("%s%s\n", STR_LANGNAME, ": Arithmetic expression parsed");
}

jupiter_void arithmeticExpressionPrime() {
	switch (lookahead.code) {
	case ART_OP_T:
		switch (lookahead.attribute.codeType) {
		case 0:
		case 1:
			// + and -
			additiveArithmeticExpression();
			arithmeticExpression();
			break;
		case 2:
		case 3:
			// * and /
			multiplicativeArithmeticExpression();
			arithmeticExpression();
			break;
		default:
			printf("arithmetic expression prime\n");
			printError();
		}
		 
		break;
	default:
		; //empty string
	}
}

jupiter_void additiveArithmeticExpression() {
	//printf("additive1\n");
	switch (lookahead.code) {
	case ART_OP_T:
		switch (lookahead.attribute.codeType) {
		case 0:
		case 1:// minus and plus
			matchToken(lookahead.code, lookahead.attribute.codeType);
			primaryArithmeticExpression();
			break;
		default:
			; 
		}
		printf("%s%s\n", STR_LANGNAME, ": Additive arithmetic expression parsed");
		break;
	default:
		
		;
	}
}


jupiter_void multiplicativeArithmeticExpression() {
	switch (lookahead.code) {
	case ART_OP_T:
		switch (lookahead.attribute.codeType) {
		case 2:
		case 3:// multiply and divide
			matchToken(lookahead.code, lookahead.attribute.codeType);
			primaryArithmeticExpression();
			break;
		default:
			;
		}
		printf("%s%s\n", STR_LANGNAME, ": Multiplicative arithmetic expression parsed");
		break;
	default:
		;
	}
}

jupiter_void primaryArithmeticExpression() {
	switch (lookahead.code) {
	
	case FLT_T:
	case INT_T:
	case IVID_T:
	case FVID_T:
		matchToken(lookahead.code, NO_ATTR);
		//matchToken(EOS_T, NO_ATTR);
		printf("%s%s\n", STR_LANGNAME, ": Primary arithmetic expression parsed");
		break;
	case LPR_T:// move to other places shouldnt here
		matchToken(LPR_T, NO_ATTR);
		arithmeticExpression();
		matchToken(RPR_T, NO_ATTR);
		break;
	default:
		;
	}
	//arithmeticExpression();
	
}

//jupiter_void secondaryArithmeticExpression() {
//	switch (lookahead.code) {
//	case ART_OP_T:
//		switch (lookahead.attribute.codeType) {
//		case ART_OP_ADD:
//		case ART_OP_SUB:
//		case ART_OP_MUL:
//		case ART_OP_DIV:
//			matchToken(lookahead.code, lookahead.attribute.codeType);
//			primaryArithmeticExpression();
//			secondaryArithmeticExpression();
//			break;
//		default:
//			; //empty string
//		}
//		break;
//	default:
//		; //empty string
//	}
//	printf("%s%s\n", STR_LANGNAME, ": Secondary arithmetic expression parsed");
//}


/*
************************************************************
 * String expression
 ***********************************************************
 */
jupiter_void stringExpression() {
	matchToken(STR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": String expression parsed");
}


jupiter_void iterationStatement() {
	matchToken(KW_T, KW_while);
	matchToken(LPR_T, NO_ATTR);
	conditionalExpression();
	//printf("condit\n");
	matchToken(RPR_T, NO_ATTR);
	//printf("rprt\n");
	matchToken(KW_T, KW_do);
	matchToken(LBR_T, NO_ATTR);
	optionalStatements();
	matchToken(RBR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Iteration statement parsed");
}

/*
 ************************************************************
 * Selection statement
 * BNF: <selection statement> -> if (<conditional expression>) then { <optional statements> } else { <optional statements> }
 * FIRST(<selection statement>) = { KW_T(KW_if) }
 ***********************************************************
 */
jupiter_void selectionStatement() {
	matchToken(KW_T, KW_if);
	matchToken(LPR_T, NO_ATTR);//if
	conditionalExpression();
	matchToken(RPR_T, NO_ATTR);
	//printf("here1\n");
	//matchToken(KW_T, KW_if);
	matchToken(KW_T, KW_then);//then
	//printf("here2\n");
	matchToken(LBR_T, NO_ATTR);
	optionalStatements();//
	matchToken(RBR_T, NO_ATTR);
	matchToken(KW_T,KW_else);//else
	matchToken(LBR_T, NO_ATTR);
	optionalStatements();//
	matchToken(RBR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Selection statement parsed");
}


jupiter_void conditionalExpression() {
	relationalExpression();
	conditionalExpressionPrime();
	//logicalExpression();
	//arithmeticExpression();
	//arithmeticExpressionPrime();
	printf("%s%s\n", STR_LANGNAME, ": Conditional expression parsed");
}

jupiter_void conditionalExpressionPrime() {
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case KW_and:
		case KW_or:
		case KW_not:
			logicalExpression();
			break;
		default:
			;
		}
	default:
		;
	}
}

jupiter_void logicalExpression() {
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case KW_and:
			matchToken(KW_T, KW_and);
			printf("%s%s\n", STR_LANGNAME, ": Logical expression AND parsed");
			conditionalExpression();
			break;
		case KW_or:
			matchToken(KW_T, KW_or);
			printf("%s%s\n", STR_LANGNAME, ": Logical expression OR parsed");
			conditionalExpression();
			break;
		case KW_not:
			matchToken(KW_T, KW_not);
			printf("%s%s\n", STR_LANGNAME, ": Logical expression NOT parsed");
			conditionalExpression();
			break;
		default:
			printf("logicalExpression\n");
			printError();
			
		}
		//printf("%s%s\n", STR_LANGNAME, ": Logical expression parsed");
		
	default:
		;
	}
	
}

/*
************************************************************
 * Relational expression
 * BNF: <relational expression> -> <primary arithmetic relational expression> <primary arithmetic relational expression operator> <primary arithmetic relational expression>
 * FIRST(<relational expression>) = { IVID_T, FVID_T, SVID_T, FLT_T, INT_T, STR_T }
 ***********************************************************
 */
jupiter_void relationalExpression() {
	switch (lookahead.code) {
	case IVID_T:
	case FVID_T:
	case SVID_T:
	case FLT_T:
	case INT_T:
	case STR_T:
		primaryAirthmeticRelationalExpression();
		primaryAirthmeticRelationalExpressionOperator();
		primaryAirthmeticRelationalExpression();
		break;
	default:
		printf("relationalExpression\n");
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Relational expression parsed");
}

/*
************************************************************
 * Primary arithmetic relational expression
 * BNF: <primary arithmetic relational expression> -> <int variable identifier> |<string variable identifier>|<float variable identifier> <float literal> | <integer literal> | <string literal>
 * FIRST(<primary arithmetic relational expression>) = { IVID_T, FVID_T, SVID_T, FLT_T, INT_T, STR_T }
 ***********************************************************
 */
jupiter_void primaryAirthmeticRelationalExpression() {
	switch (lookahead.code) {
	case IVID_T:
	case FVID_T:
	case SVID_T:
	case FLT_T:
	case INT_T:
	case STR_T:
		matchToken(lookahead.code, NO_ATTR);
		break;
	default:
		printf("primaryAirthmeticRelationalExpression\n");
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Primary arithmetic relational expression parsed");
}

/*
 ************************************************************
 * Primary arithmetic relational expression operator
 * BNF: <primary arithmetic relational expression operator> -> <relational operator>
 * FIRST(<primary arithmetic relational expression operator>) = { REL_OP_T }
 ***********************************************************
 */
jupiter_void primaryAirthmeticRelationalExpressionOperator() {
	switch (lookahead.code) {
	case REL_OP_T:
		matchToken(lookahead.code, lookahead.attribute.codeType);
		break;
	default:
		printf("primaryAirthmeticRelationalExpressionOperator\n");
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Primary arithmetic relational expression operator parsed");
}



/*
************************************************************
 * Input statement
 * BNF: <input statement> -> input (<input variable list>)
 * FIRST(<input statement>) = { KW_T(KW_input) }
 ***********************************************************
 */
jupiter_void inputStatement() {
	matchToken(MNID_T, NO_ATTR);
	matchToken(LPR_T, NO_ATTR);
	inputVariableList();
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Input statement parsed");
}

/*
 ************************************************************
 * Input Variable List
 * BNF: <input variable list> -> <variable identifier> <input variable listPrime>
 * FIRST(<input variable list>) = { IVID_T, FVID_T, SVID_T }
 ***********************************************************
 */
jupiter_void inputVariableList() {
	switch (lookahead.code) {
	case IVID_T:
	case FVID_T:
	case SVID_T:
		variableList();
		break;
	default:
		printf("inputVariableList\n");
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Input variable list parsed");
}



/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
jupiter_void outputStatement() {
	matchToken(MNID_T, NO_ATTR);
	matchToken(LPR_T, NO_ATTR);
	outputVariableList();
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ***********************************************************
 */
jupiter_void outputVariableList() {
	switch (lookahead.code) {
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	case IVID_T:
	case FVID_T:
	case SVID_T:
		variableList();
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}


