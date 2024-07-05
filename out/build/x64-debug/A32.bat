:: COMPILERS COURSE - SCRIPT ---------------------------------------------
:: SCRIPT A32 - CST8152 - Winter 2023

CLS
SET COMPILER=JupiterCompiler.exe

SET FILE1=INPUT0_Empty
SET FILE2=INPUT1_Hello
SET FILE3=INPUT2_Volume
SET FILE4=INPUT3_Factorial
SET FILE5=INPUT4_Datatypes
SET FILE6=INPUT5_General

SET ASSIGNMENT=A32
SET EXTENSION=jup
SET OUTPUT=out
SET ERROR=err

SET PARAM=P

:: ---------------------------------------------------------------------
:: Begin of Tests (A32 - W22) ------------------------------------------
:: ---------------------------------------------------------------------

@echo off

ECHO "                                                                       "
ECHO "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
ECHO "@@@@                                                               @@@@"
ECHO "@@          /       ==============================        /          @@"
ECHO "@         ////           @@       @@ #@                  ////         @"
ECHO "@         ////*          @@ @%  @ @@    @@  @ #@#       /////         @"
ECHO "@     ((( ////))))   @@  @% @%  @ @@ #@ @@  @ #@@#   ///////( ///     @"
ECHO "@     ((((,/ )))))    @@@@   @@@  @@ ##  @@@   #@#   ///// ,/////     @"
ECHO "@     (((((/)))((    ------------------------------    ((((./////*    @"
ECHO "@    //*./ /  .///   ---  PROGRAMMING LANGUAGE  ---  ////   / ( (//   @"
ECHO "@    ///// / /////   ==============================  * ////* / ////   @"
ECHO "@     ///// ///// ((                               (( ///// /////     @"
ECHO "@    ((((   / , (((((                             (((((  //   /(((    @"
ECHO "@    (((((((/ . (((((                          (((((* / (((((((       @"
ECHO "@      (((((( //((((/((((                    *((((/((((/( (((((/      @"
ECHO "@       .//,   * /   (((((                   (((((  ///    .//.       @"
ECHO "@     ,////////./(  (((((* ////         (///(((((( ,/(,////////       @"
ECHO "@         //////// ,// ((( /////,     ////// ((( //  /////// *        @"
ECHO "@            (((((((((,// * /////     /////   (//(((((((((            @"
ECHO "@            ((((((((((((/////         //.///  (((((((((((.           @"
ECHO "@                   (///////// //(   (//.//////////                   @"
ECHO "@                  (/////////             //////////                  @"
ECHO "@                                                                     @"
ECHO "@@          A L G O N Q U I N   C O L L E G E  -  2 0 2 3 W          @@"
ECHO "@@@@                                                               @@@@"
ECHO "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
ECHO "                                                                       "
ECHO "[PARSER SCRIPT .......................................................]"
ECHO "                                                                       "

ren *.exe %COMPILER%

::
:: BASIC TESTS  ----------------------------------------------------------
::
:: Basic Tests (A32 - W22) - - - - - - - - - - - - - - - - - - - - - -

ECHO "BASIC TESTS"

::%COMPILER% %PARAM%  %FILE2%.jup

%COMPILER% %PARAM% %FILE1%.%EXTENSION%	> %FILE1%-%ASSIGNMENT%.%OUTPUT%	2> %FILE1%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE2%.%EXTENSION%	> %FILE2%-%ASSIGNMENT%.%OUTPUT%	2> %FILE2%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE3%.%EXTENSION%	> %FILE3%-%ASSIGNMENT%.%OUTPUT%	2> %FILE3%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE4%.%EXTENSION%	> %FILE4%-%ASSIGNMENT%.%OUTPUT%	2> %FILE4%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE5%.%EXTENSION%	> %FILE5%-%ASSIGNMENT%.%OUTPUT%	2> %FILE5%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE6%.%EXTENSION%	> %FILE6%-%ASSIGNMENT%.%OUTPUT%	2> %FILE6%-%ASSIGNMENT%.%ERROR%

:: SHOW OUTPUTS - - - - - - - - - - - - - - - - - - - - - - - - - - -
DIR *.OUT
DIR *.ERR

:: ---------------------------------------------------------------------
:: End of Tests (A32 - W22) --------------------------------------------
:: ---------------------------------------------------------------------
ECHO "end of TESTS"
pause