#include <check.h>
#include "dictionary.h"
#include <stdlib.h>
#include <stdio.h>


int main( int argc, char *argv[] )  {

   
        hashmap_t hashtable[HASH_SIZE];
        printf("Test words: %s\n", argv[1]);
        printf("With dictionary: %s\n", argv[2]);
        
        load_dictionary(argv[2], hashtable);

        char *misspelled[MAX_MISSPELLED];
        FILE *fp = fopen(argv[1], "r");

        int num_misspelled = check_words(fp, hashtable, misspelled);
   

   return 0;

}

