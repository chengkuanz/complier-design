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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Jan 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main code for Reader (.c)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

/*
***********************************************************
* Function name: readerCreate
* Purpose: Creates the buffer reader according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: S22
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to reader)
* Algorithm: Allocation of memory according to inicial (default) values.
* TODO ......................................................
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
*************************************************************
*/

ReaderPointer readerCreate(jupiter_intg size, jupiter_intg increment, jupiter_intg mode) {
	ReaderPointer readerPointer;
	/* TO_DO: Defensive programming */
	if (!increment) {
		increment = READER_DEFAULT_INCREMENT;
		mode = MODE_FIXED;
	}
	if (!size) {
		size = READER_DEFAULT_SIZE;
	}
	if (!mode || ((mode != "F") && (mode != "A") && (mode != "M"))){
		mode = MODE_FIXED;
		//return NULL;//not being used due to causing errors
		
	}
	/* TO_DO: Adjust the values according to parameters */
	if (size < 0 || size > READER_MAX_SIZE)
		return NULL;
	if (increment < 0 ) {
		return READER_DEFAULT_INCREMENT;
	}
	
	//size = READER_DEFAULT_SIZE;
	//increment = READER_DEFAULT_INCREMENT;
	//mode = MODE_FIXED;
	readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NULL;
	readerPointer->content = (jupiter_char*)malloc(size);
	/* TO_DO: Defensive programming */
	if (!readerPointer->content) {
		free(readerPointer);
		return NULL;
	}
	readerPointer->size = size;
	readerPointer->increment = increment;
	readerPointer->mode = mode;
	/* TO_DO: Initialize the histogram */
	for (int i = 0; i < NCHAR; i++) {
		readerPointer->histogram[i] = 0;
	}
	/* TO_DO: Initialize flags */
	/* TO_DO: The created flag must be signalized as EMP */
	readerPointer->flags = SETEMPBIT;
	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

ReaderPointer readerAddChar(ReaderPointer const readerPointer, jupiter_char ch) {
	jupiter_char* tempReader = NULL;
	jupiter_intg newSize = 0;
	/* TO_DO: Defensive programming: check buffer and valid char (increment numReaderErrors) */
	if (!readerPointer) {
		return NULL;
	}
	if (ch>=NCHAR-1 || ch < 0) {
		readerPointer->numReaderErrors++;
		return readerPointer;
	}
	/* TO_DO: Reset Realocation */
	readerPointer->flags = RSTFULLBIT;//from prof Feb02
	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->position.wrte * (jupiter_intg)sizeof(jupiter_char) < readerPointer->size) {
		//delete this todo From Prof feb02/* TO_DO: This buffer is NOT full */
		//readerPointer->flags = SETFULBIT;
	} else {
		/* TO_DO: Reset Full flag */
		readerPointer->flags = RSTFULLBIT;
		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT:
			/* TO_DO: Adjust new size */
			/* TO_DO: Defensive programming */
			newSize = readerPointer->size + readerPointer->increment;
			if (newSize < 0 || newSize > READER_MAX_SIZE) {// check if the result is valid(not negative and lower than READER_MAX_SIZE)
				return NULL;
			}
			break;
		case MODE_MULTI:
			/* TO_DO: Adjust new size */
			/* TO_DO: Defensive programming */
			newSize = readerPointer->size * readerPointer->increment;//use * instead of + after size because the assg specification says so
			if (newSize < 0|| newSize > READER_MAX_SIZE) {
				return NULL;
			}
			break;
		default:
			return NULL;
		}
		/* TO_DO: New reader allocation */
		tempReader = (jupiter_char*)realloc(readerPointer->content, newSize);
		/* TO_DO: Defensive programming */
		if (!tempReader) {
			return NULL;
		}
		/* TO_DO: Check Relocation */
		if (tempReader != readerPointer->content) {
			readerPointer->content = tempReader;
		}//?check this
		
	}
	/* TO_DO: Add the char */
	readerPointer->content[readerPointer->position.wrte++] = ch;
	/* TO_DO: Updates histogram */
	readerPointer->histogram[ch]++;
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_boln readerClear(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return JUPITER_FALSE;
	/* TO_DO: Adjust flags original */
	readerPointer->position.wrte = readerPointer->position.mark = readerPointer->position.read = 0;
	
	return JUPITER_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_boln readerFree(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return JUPITER_FALSE;
	/* TO_DO: Free pointers */
	free(readerPointer->content);
	free(readerPointer);
	return JUPITER_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_boln readerIsFull(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return JUPITER_FALSE;
	/* TO_DO: Check flag if buffer is FUL */
	if (readerPointer->flags = CHKFULLBIT) {
		return JUPITER_TRUE;
	}
	return JUPITER_FALSE;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_boln readerIsEmpty(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return JUPITER_FALSE;
	/* TO_DO: Check flag if buffer is EMP */
	if (readerPointer->flags = CHKEMPBIT) {
		return JUPITER_TRUE;
	}
	return JUPITER_FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_boln readerSetMark(ReaderPointer const readerPointer, jupiter_intg mark) {
	/* TO_DO: Defensive programming */
	if (!readerPointer || mark <= 0 || mark > readerPointer->position.wrte) {
		return JUPITER_FALSE;
	}	
	else if (mark < readerPointer->position.wrte) {
		/* TO_DO: Adjust mark */
		readerPointer->position.mark = mark;
		return JUPITER_TRUE;
	}
	else {
		return JUPITER_FALSE;
	}//usable,value must be between 0 and the posWrte
		
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_intg readerPrint(ReaderPointer const readerPointer) {
	jupiter_intg cont = 0;
	jupiter_char c;
	/* TO_DO: Defensive programming (including invalid chars) */
	c = readerGetChar(readerPointer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	while (cont < readerPointer->position.wrte) {
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
		//if (readerPointer->flags = CHKENDBIT){//checking the flags (END - End Of the Reader) can print the content. 
		//	break;
		//}
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_intg readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	jupiter_intg size = 0;//number of characters read from the file stream
	jupiter_char c;
	/* TO_DO: Defensive programming */
	if (!readerPointer || !fileDescriptor)
		return READER_ERROR;
	c = (jupiter_char)fgetc(fileDescriptor);//read one character at a time
	while (!feof(fileDescriptor)) { //repeated until the standard macro feof(fi) detects end-of-file on the input file
		if (!readerAddChar(readerPointer, c)) {// add the character to the reader
			ungetc(c, fileDescriptor);//atest char could not be included into the reader
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor); // fgetc () reads the next character from the stream
		/*reference: https://www.tutorialspoint.com/c_standard_library/c_function_fgetc.htm*/
		size++;
	}
	/* TO_DO: Defensive programming */
	return size;
	//this function may cause the content be truncated (unintenttionally)
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_boln readerRecover(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return JUPITER_FALSE;
	/* TO_DO: Recover positions */
	//so that the reader can be reread again. 
	readerPointer->position.read = 0;
	readerPointer->position.mark = 0;
	return JUPITER_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_boln readerRetract(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return JUPITER_FALSE;
	/* TO_DO: Retract (return 1 pos read) */
	//decrements read offset by 1
	readerPointer->position.read--;
	return JUPITER_TRUE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_boln readerRestore(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return JUPITER_FALSE;
	/* TO_DO: Restore positions (read/mark) */
	// sets read offset to the value of the current mark offset.
	readerPointer->position.read = readerPointer->position.mark;
	return JUPITER_TRUE;
}



/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_char readerGetChar(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check condition to read/wrte */
	if (readerPointer->position.read == readerPointer->position.wrte) {//if read and wrte positions are equal
		return EOF;
	}
	/* TO_DO: Set EOB flag */
	//supposed to set END when you have reached the end of the reader
	
	/* TO_DO: Reset EOB flag */
	return readerPointer->content[readerPointer->position.read++];//The character located at read position
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_char* readerGetContent(ReaderPointer const readerPointer, jupiter_intg pos) {
	/* TO_DO: Defensive programming */
	if (!readerPointer || readerPointer->position.wrte < pos|| pos<0)
		return READER_ERROR;//
	
	/* TO_DO: Return content (string) */
	return readerPointer->content+pos;
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_intg readerGetPosRead(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;//?or null
	/* TO_DO: Return read */
	return readerPointer->position.read;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_intg readerGetPosWrte(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;//?or null
	/* TO_DO: Return wrte */
	return readerPointer->position.wrte;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_intg readerGetPosMark(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;//?or null
	/* TO_DO: Return mark */
	return readerPointer->position.mark;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_intg readerGetSize(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;//
	/* TO_DO: Return size */
	return readerPointer->size;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_intg readerGetInc(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;// JUPITER_FALSE;//null?
	/* TO_DO: Return increment */
	return readerPointer->increment;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_intg readerGetMode(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;//JUPITER_FALSE;//
	/* TO_DO: Return mode */
	return readerPointer->mode;
}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_byte readerGetFlags(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return flags */
	return readerPointer->flags;
}


/*
***********************************************************
* Function name: readerShowStat
* Purpose: Returns the number of chars used.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_intg readerShowStat(ReaderPointer const readerPointer) {
	int totalUniqueChar = 0;
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;//? or null / false
	/* TO_DO: Updates the histogram */
	for (int i = 0; i < NCHAR; i++) {
		if (readerPointer->histogram[i] > 0)
			totalUniqueChar++;
	}
	return totalUniqueChar;
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
jupiter_intg readerNumErrors(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	
	if (!readerPointer) {
		return READER_ERROR;
	}
	/* TO_DO: Updates the histogram */
	int totalChar = 0;

	for (int i = 0; i < NCHAR; i++) {
		if (readerPointer->histogram[i] > 0)
			totalChar += readerPointer->histogram[i];
	}
	
	
	//readerPointer->numReaderErrors = readerPointer->size - totalChar;
	//return strlen(readerPointer->content) - totalChar + 1;//+1 for null char ;(total char in testing file 14. 254 for readme.txt,)
	//reference: https://www.tutorialandexample.com/null-character-in-c
	

	//return  totalChar; //14 250
	
	//return 0;
	return readerPointer->numReaderErrors;
}
