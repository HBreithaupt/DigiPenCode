#define NUM_LETTERS 26
#define SPACE ' '

int GetCounts(const char *string, int letters[], int *spaces, int *other);
void PrintHistogram(const int letters[]);
void GetStatistics(const int letters[], double *average, char *max_letter, int *max_count);
