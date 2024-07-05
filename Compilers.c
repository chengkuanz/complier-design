/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2023
* Author: TO_DO
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
* File name: compilers.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12, A22, A32.
* Date: Jan 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main program of Compilers Project
* Function list: main().
************************************************************
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

/*
 * ............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: This file must be updated according to each assignment
 * (see the progression: reader > scanner > parser).
 * ............................................................................
 */

/*
***********************************************************
* Function name: main
* Purpose: Main function
* Author: Paulo Sousa
* History/Versions: Ver F22
* Called functions: mainReader(), mainScanner(), mainParser()
* Parameters: Command line arguments - argc, argv
* Return value: Status
* Algorithm: -
*************************************************************
*/

jupiter_intg main(int argc, char** argv) {
	jupiter_intg i;
	jupiter_char option;
	printLogo();
	if (DEBUG) {
		for (i = 0; i < argc; ++i)
			printf("argv[%d] = %s\n", i, argv[i]);
	}
	if (argc < 2) {
		printf("%s%c%s%c%s%c%s", "OPTIONS:\n* [",
			PGM_READER, "] - Reader\n* [",
			PGM_SCANNER, "] - Scanner\n* [",
			PGM_PARSER, "] - Parser\n");
		return EXIT_FAILURE;
	}
	option = argv[1][0];
	//use the line below when starting from VS, and run in S model
	//option = PGM_SCANNER;
	switch (option) {
	case PGM_READER:
		printf("%s%c%s", "\n[Option '", PGM_READER, "': Starting READER .....]\n\n");
		mainReader(argc, argv);
		break;
		
	case PGM_SCANNER:
		printf("%s%c%s", "\n[Option '", PGM_SCANNER, "': Starting SCANNER ....]\n\n");
		mainScanner(argc, argv);
		break;
		
	case PGM_PARSER:
		printf("%s%c%s", "\n[Option '", PGM_PARSER, "': Starting PARSER .....]\n\n");
		mainParser(argc, argv);
		break;
	
	default:
		printf("%s%c%s%c%s%c%s", "* OPTIONS:\n- [",
			PGM_READER, "] - Reader\n- [",
			PGM_SCANNER, "] - Scanner\n- [",
			PGM_PARSER, "] - Parser\n");
		break;
	}
	return EXIT_SUCCESS;
}

/*
***********************************************************
* Function name: printLogo
* Purpose: pRINT lOGO
* Author: Paulo Sousa
* History/Versions: Ver F22
* Called functions: -
* Parameters: -
* Return value: (Null)
* Algorithm: -
*************************************************************
*/
jupiter_void printLogo() {
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
		"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n",
		"@@@@                                                               @@@@\n",
		"@@          /        ==============================        /         @@\n",
		"@         ////           @@       @@  #@                  ////        @\n",
		"@         ////*          @@ @%  @ @@     @@  @ #@#       /////        @\n",
		"@     ((( ////))))   @@  @% @%  @ @@  #@ @@  @ #@@#   ///////( ///    @\n",
		"@     ((((, / )))))   @@@@   @@@  @@  ##  @@@   #@#   ///// ,/////    @\n",
		"@     (((((/ )))((   ==============================   ((((./////*     @\n",
		"@   *//*./ /  .///   ===  PROGRAMMING LANGUAGE  ===  ////   / ( (//   @\n",
		"@    ///// / /////   ==============================  *////* / ////    @\n",
		"@     ///// ///// ((                               (( ///// /////     @\n",
		"@    ((((/ , (((((                                (((((  //   /(((    @\n",
		"@    (((((((/ . (((((                             ((((( */ (((((((    @\n",
		"@      (((((( //((((/((((                    *((((/((((/( (((((/      @\n",
		"@       .//,   */    (((((                   (((((  ///    .//.       @\n",
		"@      ,////////./(  (((((*////         (///(((((( ,/(,////////       @\n",
		"@         //////// ,// ((( /////,     ////// ((( //  ///////*         @\n",
		"@            (((((((((,//  */////     /////   (//(((((((((            @\n",
		"@            (((((((((((  (/////       //.///  (((((((((((.           @\n",
		"@                   (///////// //(   (//.//////////                   @\n",
		"@                  (/////////             //////////                  @\n",
		"@                                                                     @\n",
		"@@          A L G O N Q U I N   C O L L E G E  -  2 0 2 3 W          @@\n",
		"@@@@                                                               @@@@\n",
		"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
	);
}
