//Andrew Vittetoe
//Assignment #1 - Test Cases
//Application Security
//Fall 2019

#include <check.h>
#include "dictionary.h"
#include <stdlib.h>

#define DICTIONARY "wordlist2.txt"
#define TESTDICT "test_worlist.txt"
#define TEST7_8 "test_words1.txt"
#define TEST9_10 "test_words2.txt"

//#1 Test Dictionary Load
START_TEST(test_dictionary_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    ck_assert(load_dictionary(TESTDICT, hashtable));
}
END_TEST

//#2-6 Test single words - Normal (Correct & Wrong), Punctuation and Numeric
START_TEST(test_check_word_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char* correct_word = "Programmer";
    const char* incorrect_word = "Programmmer";
    const char* punctuation_word_2 = "Programmer?";
    const char* punctuation_word_3 = "¿Programmer?";
    const char* numeric_word = "10011001";
    ck_assert(check_word(correct_word, hashtable));
    ck_assert(!check_word(incorrect_word, hashtable));
    ck_assert(!check_word(punctuation_word_2, hashtable));
    ck_assert(!check_word(punctuation_word_3, hashtable));
    ck_assert(check_word(numeric_word, hashtable));
}
END_TEST

//#7-8 Check lists of words - Normal Correct and Wrong, from array and file
START_TEST(test_check_words_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char* expected[3];
    expected[0] = "firrst";
    expected[1] = "second";
    expected[2] = "tthird";
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen(TEST7_8, "r");
    
    int num_misspelled = check_words(fp, hashtable, misspelled);
    ck_assert(num_misspelled == 3);

    bool test = strlen(misspelled[0]) == strlen(expected[0]);
    int len1 = strlen(misspelled[0]);
    int len2 = strlen(expected[0]);
    ck_assert_msg(test, "%d!=%d", len1, len2);

    ck_assert_msg(strcmp(misspelled[0], expected[0]) == 0);
    ck_assert_msg(strcmp(misspelled[1], expected[1]) == 0);
    ck_assert_msg(strcmp(misspelled[2], expected[2]) == 0);
}
END_TEST

//#9-10 Check lists of words - weird Correct and Wrong, from array and file
START_TEST(test_check_words_weird)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char* expected[4];
    expected[0] = "fir st";
    expected[1] = "secon'\0'd";
    expected[2] = "'\n'third";
    expected[2] = "4our";
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen(TEST9_10, "r");
    
    int num_misspelled = check_words(fp, hashtable, misspelled);
    ck_assert(num_misspelled == 4);

    bool test = strlen(misspelled[0]) == strlen(expected[0]);
    int len1 = strlen(misspelled[0]);
    int len2 = strlen(expected[0]);
    ck_assert_msg(test, "%d!=%d", len1, len2);
    ck_assert_msg(strcmp(misspelled[0], expected[0]) == 0);
    ck_assert_msg(strcmp(misspelled[1], expected[1]) == 0);
    ck_assert_msg(strcmp(misspelled[2], expected[2]) == 0);
    ck_assert_msg(strcmp(misspelled[3], expected[3]) == 0);
}
END_TEST

//Test #11 - Uppercase
Suite *
check_word_suite(void)
{
    Suite * suite;
    TCase * check_word_case;
    suite = suite_create("check_word");
    check_word_case = tcase_create("Core");
    tcase_add_test(check_word_case, test_dictionary_normal);
    tcase_add_test(check_word_case, test_check_word_normal);
    tcase_add_test(check_word_case, test_check_words_normal);
    tcase_add_test(check_word_case, test_check_words_weird);
    suite_add_tcase(suite, check_word_case);

    return suite;
}

int
main(void)
{
    int failed;
    Suite *suite;
    SRunner *runner;
    
    suite = check_word_suite();
    runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

