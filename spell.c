//Andrew Vittetoe
//Assignment #1
//Application Security
//Fall 2019
    
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>

//FOR DEBUGGING
#define DICTIONARY "wordlist.txt"
#define TEST1 "test1.txt"
#define TESTDICT "test_worlist.txt"
#define TESTLIST "test_listrun.txt" 

    
//Main Program--------------------------------------------------------------
/*int main()
{

    hashmap_t hashtable[HASH_SIZE];
    char* wrong_words[MAX_MISSPELLED * LENGTH];

    //bool success = load_dictionary(TESTDICT, hashtable);
    bool success = load_dictionary(DICTIONARY, hashtable);
    if  (success == true)int main()
{

    hashmap_t hashtable[HASH_SIZE];
    char* wrong_words[MAX_MISSPELLED * LENGTH];

    //bool success = load_dictionary(TESTDICT, hashtable);
    bool success = load_dictionary(DICTIONARY, hashtable);
    if  (success == true)
    {
        //Pointer to the file
        FILE *file0;

        //Open dictionary_file from path stored in dictionary
        //file0 = fopen (TESTLIST, "r");
        file0 = fopen (TEST1, "r");

        int num_wrong = check_words(file0, hashtable, wrong_words);
        printf("misspelled %d \n", num_wrong);

        printf("Misspelled words: %s \n", wrong_words); 
    }
    else
    {
        printf("Failed to load %d \n", success);
    }
     
 
    return 0;
}   
    {
        //Pointer to the file
        FILE *file0;

        //Open dictionary_file from path stored in dictionary
        //file0 = fopen (TESTLIST, "r");
        file0 = fopen (TEST1, "r");

        int num_wrong = check_words(file0, hashtable, wrong_words);
        printf("misspelled %d \n", num_wrong);

        printf("Misspelled words: %s \n", wrong_words); 
    }
    else
    {
        printf("Failed to load %d \n", success);
    }
     
 
    return 0;
}   */  

//Function Definitions------------------------------------------------------
bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[])
{
    char data[LENGTH + 1];
    int bucket = 0;
    int j =0;
    int size_Loaded = 0;
    int size_word = 0;
    

    //Initialize all values in hash table to NULL
    for (int i = 0; i < HASH_SIZE; i++)
    {
        &hashtable[i] == NULL;
    }

    //Check that a dictionary file was provided
    if (dictionary_file == NULL)
    {
        //FOR DEBUGGING
        //printf("FAILED DICT FILE \n");

        //Return unsuccessful
        return false;
    }

    //Pointer to the file
    FILE *file1;

    //Open dictionary_file from path stored in dictionary
    file1= fopen (dictionary_file, "r");

    //Check that file loaded correctly
    if (file1 == NULL)
    {
        //FOR DEBUGGING
        //printf("FAILED LOAD FILE1 \n");

        //Return unsuccessful
        return false;
    }

    //Load words from file
    while( fgets (data, LENGTH+1, file1) != NULL ) 
    {
        
        //Check that we have room to load more words
/*         if ((size_Loaded + strlen(data)) > HASH_SIZE)
        {
            //FOR DEBUGGING
            printf("File too large \n");
        
            //Close file
            fclose(file1);

            //Return unsuccessful
            return false;
        } */
        

        //FOR DEBUGGING
        //printf("Size_Loaded: %d \n", size_Loaded);
        //printf("Data: %s \n", data);
        
        //Create a node
        hashmap_t new_node = (hashmap_t)malloc(sizeof(node));

        //Check if did not successfully created new node
        if(new_node == NULL)
        {
            //FOR DEBUGGING
            //printf("Error creating a new node\n");

            //Free memory
            free(new_node);

            //Close file
            fclose(file1);

            //Return unsuccessful
            return false;
        }
        
        //Make next NULL
        new_node->next = NULL;

        //Make sure j is 0
        j = 0;

        //Strip-out newline and spaces
        while (data[j] != '\0')
        {
                if ((data[j] == '\n') || (data[j] == ' '))
                {
                    data[j] = '\0';
                }
                else
                {
                    //add word to node letter by letter
                    new_node->word[j] = data[j];
                    j++;
                }
    
        }
        
        //Add word to total size loaded so far
        size_Loaded += strlen(data);

        //Get hash of word
        bucket = hash_function(new_node->word);

        //If not already in table, add new node
        if (hashtable[bucket] == NULL)
        {            
            hashtable[bucket] = new_node;

            //For Debugging
            //printf("HEAD Word = %s \n", hashtable[bucket]->word);
            //printf("HEAD Bucket = %d \n", bucket);
        }
        //If it is already in table, add to linked list
        else
        {   
            //For Debugging
            //printf("BEFORE Word = %s \n", new_node->word);
            //printf("BEFORE Bucket = %d \n", bucket);

            new_node->next = hashtable[bucket];
            hashtable[bucket] = new_node;

            //For Debugging
            //printf("AFTER Word = %s \n", hashtable[bucket]->word);
            //printf("AFTER Bucket = %d \n", bucket);
        }   

    }

    //Close file
    fclose(file1);

    //Return successful
    return true;
}
 
int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[])
{
    int num_misspelled = 0;
    int i_last_pos = 0;
    char ch;
    int i = 0;
    int j = 0;
    int k = 0;
    int k_limit = 0;
    int j_limit = 0;
    int size_Loaded = 0;
    bool result = true;
    //char* data_file[LENGTH + 1];
    //char* data_check_word[LENGTH + 1];

    //Check we have a valid file
    if (fp == NULL)
    {
        //printf("NO VALID FILE PROVIDED \n");
        return num_misspelled;
    }
    else
    {

        //Allcoate memory dynamically
        //hashmap_t new_node = (hashmap_t)malloc(sizeof(node));
        char* data_file = (char*)malloc(sizeof(LENGTH + 1));
        char* data_check_word = (char*)malloc(sizeof(LENGTH + 1));

        //Load words from file
        while( fgets (data_file, LENGTH+1, fp) != NULL ) 
        {
        
            if (size_Loaded + strlen(data_file) > HASH_SIZE)
            {
                //printf("File too large \n");
            
                //Close file
                //fclose(fp);
                return num_misspelled;
            }
            
            size_Loaded += strlen(data_file);
            //printf("Size_Loaded: %d \n", size_Loaded);
        
        
            //remove punctuation
            //i is for looping
            //i_pos is the next position to place a non-punctuation char
            j_limit = strlen(data_file);
            //printf("j_limit: %d \n", j_limit);
            i = 0;
            i_last_pos = 0;

            //go back through loaded word and check there's no punctuation in it
            //Loops through letter by letter
            for (i = 0; i < j_limit; i++)
            {

                //Get letter from loaded word
                ch = data_file[i];
                
                //If it is not a punctuation char or newline or null, add to word
                if (( ch != '.') && ( ch != '?') && ( ch != ';') && ( ch != ':') && ( ch != ',') && ( ch != ' ') && ( ch != '\n') && ( ch != '!') && ( ch != '_') && ( ch != '-' && ( ch != '\0')))
                {
                    //Add to new word
                    data_check_word[i_last_pos] = ch;
                    //Increment position
                    i_last_pos ++;

                    //FOR DEBUGGING
                    //printf("CH: %c \n", ch); 
                }
                
            } 

            //Check word spelling    
            //printf("DATA: %s \n", data_check_word);  
            result = check_word(data_check_word, hashtable);
            //printf("Result: %d \n", result); 
            
            //See if word was correctly spelled
            if (result == false)
            {
                //If word wasn't spelled correctly, add to misspelled array AFTER checking there is space
                if(num_misspelled < MAX_MISSPELLED)
                {
                    num_misspelled++;
                    int data_size = strlen(data_file);
                    //printf("Data Size: %d \n", data_size);
                    
                    int misspelled_size = strlen(misspelled);
                    //printf("Misspelled Size: %d \n", misspelled_size);

                    strncat(misspelled, data_file, data_size);

                    //printf("Misspelled: %s \n", misspelled);  
                }
                else
                {
                    //Close file
                    //fclose(fp);

                    return num_misspelled;
                }  
            }

            memset(data_check_word, '\0', strlen(data_check_word));
            memset(data_file, '\0', strlen(data_file));
        }
    
        //Close file
        //fclose(fp);
        free(data_file);
        free(data_check_word);
    }

    return num_misspelled;
}

bool check_word(const char* word, hashmap_t hashtable[])
{
    
    //Set-up original case version of word to check
    int bucket = hash_function(word);
    
    //create new node
    hashmap_t cursor = (node*)malloc(sizeof(node));

    //check memory was successsfully allcoated
    if (cursor == NULL)
    {
        //free memory
        free(cursor);
        //return unsuccessful
        return false;
    }
    
    //set node to node corresponding to hash
    cursor = hashtable[bucket];

    //FOR DEBUGGING
    //printf("bucket= %d \n", bucket);

    //Check original case
    while (cursor != NULL)
    {
        //FOR DEBUGGING
        //printf("word to Check = %s \n", word);
        //printf("Cursor Word = %s \n", cursor->word);

        if (0 == strcmp(word, cursor->word))
        {
            //FOR DEBUGGING
            //printf("SUCCESS \n");

            free(cursor);
            return true;
        }

        cursor = cursor->next;

        //FOR DEBUGGING
        //printf("Next Word = %s \n", cursor->word);
    }  

    //Release old node
    free(cursor);

   /*  //create new node
    hashmap_t cursor_lower = (node*)malloc(sizeof(node));

    //check memory was successsfully allcoated
    if (cursor_lower == NULL)
    {
        //free memory
        free(cursor_lower);
        //return unsuccessful
        return false;
    }
    
    //Set-up lower case version of word to check
    int word_size = strlen(word);
    const char* lower_word[word_size];
     
    //Loop through each letter and set to lowercase equiv
    for (int k = 0; k < word_size; k++)
    {
        lower_word[k] = tolower(word[k]);
    }

    //set node to node corresponding to lower case hash
    int lower = hash_function(lower_word);
    cursor_lower = hashtable[lower];

    //For debugging
    printf("Lower_Hash= %d \n", lower);
    
    //Check all lower case
    while (cursor_lower != NULL)
    {
        printf("word= %s \n", word);
        printf("cursor word = %s \n", cursor_lower->word);

        if (0 == strcmp(word, cursor_lower->word))
        {
            printf("SUCCESS \n");
            //free memory
            free(cursor_lower);
            //return success
            return true;
        }

        cursor_lower = cursor_lower->next;
        printf("next = %s \n", cursor_lower->word);
    }     
    
    free(cursor_lower); */
    return false;
} 


//Included so it compiles locally. I remove when I upload to autograder
/*int hash_function(const char* word)
{
    int sum = 0;
    int word_length = strlen(word);

    for (int i = 0; i < word_length; i++)
    {
        sum += word[i];
    }
    
    int bucket = sum % HASH_SIZE;
    return bucket;
}  */

