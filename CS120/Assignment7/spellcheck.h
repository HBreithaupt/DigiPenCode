#define FILE_OK       -1 /* If the file was opened successfully         */
#define FILE_ERR_OPEN -2 /* If the file was unable to be opened         */
#define WORD_OK        1 /* If the word was found in the dictionary     */
#define WORD_BAD       2 /* If the word was not found in the dictionary */

#define LONGEST_WORD 50  /* This is the longest word you need to handle */

struct DICTIONARY_INFO
{
  int shortest; /* Length of the shortest word       */
  int longest;  /* Length of the longest word        */
  int count;    /* Number of words in the dictionary */
};

/* Function prototypes */
char *mystrupr(char *string);
int info(const char *dictionary, struct DICTIONARY_INFO *dinfo);
int spell_check(const char *dictionary, const char *word);
int word_lengths(const char *dictionary, int lengths[], int count);
int words_starting_with(const char *dictionary, char letter);

