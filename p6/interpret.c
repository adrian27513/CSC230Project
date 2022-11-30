/**
  @file interpret.c
  @author Adrian Chan (amchan)
  Interprets and executes a given program file.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "value.h"
#include "syntax.h"
#include "parse.h"

/** Length of argc with one user input from the command line */
#define ONE_CMD_INPUT 2
/** Print a usage message then exit unsuccessfully. */
void usage()
{
  fprintf( stderr, "usage: interpret <program-file>\n" );
  exit( EXIT_FAILURE );
}

/** Program staring point Interprets and executes a given program file.
    @param argc number of command line arguments
    @param argv list of command line arguments
    @return exit status of program
*/
int main( int argc, char *argv[] )
{
  // Open the program's source.
  if ( argc != ONE_CMD_INPUT )
    usage();
  
  FILE *fp = fopen( argv[ 1 ], "r" );
  if ( !fp ) {
    perror( argv[ 1 ] );
    exit( EXIT_FAILURE );
  }

  // Environment, for storing variable values.
  Environment *env = makeEnvironment();
  
  // Parse one statement at a time, then run each statement
  // using the same Environment.
  char tok[ MAX_TOKEN + 1 ];
  while ( parseToken( tok, fp ) ) {
    // Parse the next input statement.
    Stmt *stmt = parseStmt( tok, fp );

    // Run the statement.
    stmt->execute( stmt, env );

    // Delete the statement.
    stmt->destroy( stmt );
  }
  
  // We're done, close the input file and free the environment.
  fclose( fp );
  freeEnvironment( env );

  return EXIT_SUCCESS;
}
