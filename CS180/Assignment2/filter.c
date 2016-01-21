/*****************************************************************************/
/*!
\file filter.c
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS180
\par Assignment 2  
\date 5/28/15

\brief
  Implementation of a text filter by parsing the command line using getopt.
  
  Filter options include:
    - help screen
    - removing blank lines
    - deleting a certain character
    - turning everything lower/upper case
    - display line numbers
    - replace characters
    - expanding tabs
    
  Function List:
    - parse_line : grabs options set and number of files to be filtered
    - assign_files : if files provided grab them from comment line and store
                     in array
    - to_upper : uppercases a character
    - to_lower : lowercases a character
    - tab_expand : expands a tab character into desired number of spaces
    - delete_chars : deletes all occurences of a character in the file
    - filter_file : takes a file pointer to filter the file according to 
                    options provided

Hours spent on assignment: 6

Specific portions that gave you the most trouble: 
  - overall understanding of get opt took longer to acclimate to than expected.
  
*/
/*****************************************************************************/

#include <unistd.h> /* exit */
#include <getopt.h> /* getopt */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */

  /*! macro for tab to use in comparison */
#define TAB '\t'

  /*! macro for newline to use in comparison*/
#define NEWLINE '\n'

  /*! macro for default number of spaces to use if expand tabs flag is set
   * and no arguments were provided */
#define DEFAULT_TABS 8

  /* flag for remove blank lines */
static int f_remove_blank;

  /* flag for delete, and what char to delete */
static int f_delete;
static char delete_char;

  /* flag for help screen */
static int f_help;

  /* flag for lower case option */
static int f_tolower;

  /* flag for displaying line numbers */
static int f_line_num;

  /* flag for replace, and the characters to use in replace */
static int f_replace;

  /* replace[0] is character to replace, replace[1] is the char
     to put in it's place */
static char *replace_chars;

  /* flag for upper case */
static int f_toupper;

  /* flag for expanding tabs and number of spaces to replace tabs w/ */
static int f_tab_expand;
static int tab_expand_num;

  /* number of non_options (potential files) */
static int non_options;

  /* array of files to filter, dynamically allocated if files passed */
static const char **files;

/* STATIC FUNCTIONS WITH COMMENTS */

/*****************************************************************************/
/*!

\brief
  Displays the help screen.

*/
/*****************************************************************************/
static void help_info(void)
{
    /* prints out help screen as defined by assignment */
  printf("Usage: filter [options] [file1 file2 ...] \n\n");
  printf("Options:\n");
  printf(" -b  --remove-blank-lines  removes empty lines.\n");
  printf(" -d  --delete=X            deletes all occurrences of char X.\n");
  printf(" -h  --help                display this information.\n");
  printf(" -l  --tolower             convert all characters to lower case.\n");
  printf(" -n  --line-numbers        prepend line numbers to each line.\n");
  printf(" -r  --replace=XY          replace all char X with char Y.\n");
  printf(" -u  --toupper             convert all characters to upper case.\n");
  printf(" -x  --expand-tabs[=X]     convert tabs to X spaces (default is 8).");
  printf("\n\n");
}

/*****************************************************************************/
/*!

\brief
  Parses the command line, turning all options provided and 
  capturing number of non-options provided and dynamically allocates
  array to store them in.

\param argc
  Number of arguments passed.
  
\param argv
  Array of strings, nul-terminated, the options of argc.

*/
/*****************************************************************************/
static void parse_line(int argc, char **argv)
{
    /* int to store result of getopt */
  int c;
  
  while(1)
  {
    int option_index = 0;
    
      /* strings to use in comparison of result of getopt */
    const char* delete = "delete";
    const char* replace = "replace";
    const char* expand_tabs = "expand-tabs";
    
      /* struct to define long options and flags to set */
    static struct option long_options[] = 
    {
      {"remove-blank-lines", no_argument,       &f_remove_blank, 1},
      {"delete",             required_argument, &f_delete,       1},
      {"help",               no_argument,       &f_help,         1},
      {"tolower",            no_argument,       &f_tolower,      1},
      {"line-numbers",       no_argument,       &f_line_num,     1},
      {"replace",            required_argument, &f_replace,      1},
      {"toupper",            no_argument,       &f_toupper,      1},
      {"expand-tabs",        optional_argument, &f_tab_expand,   1},
      {NULL,                 0,                 NULL,            0}
    };
    
      /* get argument from command line */
    c = getopt_long(argc, argv, "-:bd:hlnr::ux:", long_options, &option_index);
    
      /* stop at end of command line */
    if(c == -1)
      break;
    
    switch(c)
    {
        /* long option returned */
      case 0:
      
          /* if delete capture argument to delete to global variable */
        if(long_options[option_index].name == delete)
          delete_char = *optarg;
      
          /* if replace, capture arguments in global variable */
        if(long_options[option_index].name == replace)
          replace_chars = optarg;
      
            /* if expand tabs capture argument to get number of spaces
             * to expand tabs w/ */
        if(long_options[option_index].name == expand_tabs)
        {
            /* if argument provided, capture it, else use default number of  */
          if(optarg)
            tab_expand_num = atoi(optarg);
          else
            tab_expand_num = DEFAULT_TABS;
        }
      
        break;
      
        /* remove blank lines short option, set the flag */
      case 'b':
        f_remove_blank = 1;
        break;
      
        /* delete character short option, set the flag 
         * and get character to delete */
      case 'd':
        f_delete = 1;
        delete_char = *optarg;
        break;
      
        /* help screen short option, set the flag */
      case 'h':
        f_help = 1;
        break;
      
        /* lower case short option, set the flag */
      case 'l':
        f_tolower = 1;
        break;
      
        /* line numbers short option, set the flag */
      case 'n':
        f_line_num = 1;
        break;
      
        /* replace character short option, set the flag and capture
         * characters to use in operation */
      case 'r':
        f_replace = 1;
        replace_chars = optarg;
        break;
      
        /* upper case short option, set the flag */
      case 'u':
        f_toupper = 1;
        break;
      
        /* expand tab short option, set the flag and get number of spaces
         * desired to use instead of tabs */
      case 'x':
        f_tab_expand = 1;
      
          /* if argument provided use that or use default number */
        if(optarg)
          tab_expand_num = atoi(optarg);
        else
          tab_expand_num = DEFAULT_TABS;
      
        break;
      
        /* case of unrecognised option */
      case '?':
        printf("invalid option\n");
        break;
      
        /* case of missing argument to an option */
      case ':':
        printf("missing argument for %c\n", optopt);
        break;
      
        /* case of non-option (file) */
      case 1:
          /* increment file counter */
        non_options++;
        break;
    }
  }
  
    /* if more than 0 non options provided allocate array of char * 
     * to exact amount of non-options */
  if(non_options != 0)
    files = malloc(sizeof(char *) * non_options);
  
    /* reset optind to parse line again */
  optind = 1;
}

/*****************************************************************************/
/*!

\brief
  Grabs file names from command line and inserts them into already allocated
  array.

\param argc
  Number of arguments passed to main.
  
\param argv
  Num terminated array of string, arguments to the command line.

*/
/*****************************************************************************/
static void assign_files(int argc, char **argv)
{
    /* stores result of get opt */
  int c;
  
    /* counter to fill in array */
  int file_num = 0;
  
  while(1)
  {
    int option_index = 0;
       
      /* struct defining long-options */
    static struct option long_options[] = 
    {
      {"remove-blank-lines", no_argument,       &f_remove_blank, 1},
      {"delete",             required_argument, &f_delete,       1},
      {"help",               no_argument,       &f_help,         1},
      {"tolower",            no_argument,       &f_tolower,      1},
      {"line-numbers",       no_argument,       &f_line_num,     1},
      {"replace",            required_argument, &f_replace,      1},
      {"toupper",            no_argument,       &f_toupper,      1},
      {"expand-tabs",        optional_argument, &f_tab_expand,   1},
      {NULL,                 0,                 NULL,            0}
    };
    
      /* get argument from command line */
    c = getopt_long(argc, argv, "-:bd:hlnr::ux:", long_options, &option_index);
    
      /* stop at end of command line */
    if(c == -1)
      break;
    
    /* in this function we only care about case 1 (non-options), 
     * do nothing for every other case */
    
    switch(c)
    {
      case 'b':
        break;
      
      case 'd':
        break;
      
      case 'h':
        break;
      
      case 'l':
        break;
      
      case 'n':
        break;
      
      case 'r':
        break;
      
      case 'u':
        break;
      
      case 'x':
        break;
        
        /* non-option encountered, store in array */
      case 1:
          
          /* store file in array */
        files[file_num] = argv[optind - 1];
      
          /* increment counter to fill in next spot */
        file_num++;
        break;
    }
  } 
 }

/*****************************************************************************/
/*!

\brief
  Uppercase a character, does nothing if characters isnt a letter.

\param c
  Pointer to character to modify.

*/
/*****************************************************************************/
static void to_upper(int *c)
{
    /* if character passed in is lowercase, make it upeprcase,
     * else do nothing */
  if('a' <= *c && *c <= 'z')
    *c -= 32;
  else
    return;
}

/*****************************************************************************/
/*!

\brief
  Lowercases a character, does nothing if character isnt a letter.

\param c
  Pointer to character being modified.

*/
/*****************************************************************************/
static void to_lower(int *c)
{
    /* if character is uppercase, make it lowercase, 
     * else do nothing */
  if('A' <= *c && *c <= 'Z')
    *c += 32;
  else
    return;
}

/*****************************************************************************/
/*!

\brief
  Expands a tab into specified number of spaces.

*/
/*****************************************************************************/
static void tab_expand(void)
{
    /* counter */
  int i;

    /* replace tab with number of spaces, specified from commmand line */
  for(i = 0; i < tab_expand_num; i++)
    putc(' ', stdout);
  
}

/*****************************************************************************/
/*!

\brief
  Deletes character by simply jumping over it. Will delete chained occurences.
  Example: if deleting 'e' and there are two e's in a rowm the function will
  get rid of them both.

\param c
  Pointer to character being manipluated.
  
\param infile
  Pointer to file being filtered.

*/
/*****************************************************************************/
static void delete_chars(int *c, FILE *infile)
{
    /* while the character is the one to be deleted, get the next from the 
     * file */
  while(*c == delete_char)
    *c = fgetc(infile);
}

/*****************************************************************************/
/*!

\brief
  Takes in a file pointer and filters it based on flags set by command line
  prompt.

\param infile
  File pointer to file being filtered.

*/
/*****************************************************************************/
static void filter_file(FILE *infile)
{
    /* current char being used */
  int current_char = 0;
    
    /* previous character printed */
  int previous_char = 0;
  
    /* counter to print new linesm will persist through calls
     * to account for multiple files being processed */
  static int line_counter = 1;
  
    /* if line number flag set, start by printing the line number */
  if(f_line_num)
  {
    printf("%6i  ", line_counter);
    line_counter++;
  }
  
    /* while there are characters to print out */
  while(1)
  {
      /* set previous char to what was just printed */
    previous_char = current_char;
      
      /* get next character form the file */
    current_char  = fgetc(infile);
    
      /* stop at end of file */
    if(current_char == EOF)
      break;
    
      /* if delete flag set and the char is the one to be deleted, 
       * call delete helper function */
    if(f_delete && current_char == delete_char)
      delete_chars(&current_char, infile);
    
      /* if replace flag set and current char is the one to be replaced
       * (replace_chars[0]) replace it (replace_chars[1]) */
    if(f_replace && current_char == replace_chars[0])
      current_char = replace_chars[1];
    
      /* if uppercase flag is set, call uppercase helper function */
    if(f_toupper)
      to_upper(&current_char);
      
      /* if lower case flag is set call lower case flag helper function */
    if(f_tolower)
      to_lower(&current_char);
    
      /* if tab expand flag is set and current character is a tab */
    if(f_tab_expand && (current_char == TAB))
    {
        /* first check if we are at a new line and if line numbers are set,
         * print those out first */
      if(f_line_num && previous_char == NEWLINE)
      {
        printf("%6i  ", line_counter);
        line_counter++;
      }
      
        /* now call tab expand helper function */
      tab_expand();
      
        /* move on to next character in the file */
      continue;
    }
    
      /* if remove blank lines flag is set and both the current character
       * and the previous characters are newline, get the next character */
    if(f_remove_blank && current_char == NEWLINE && previous_char == NEWLINE)
      continue;
    
    /* by this point there is guranteed another 
     * character to printed to stdout */
    
    
      /* if previous character was a newline and line numbers flag is set
       * print out line number first */
    if(f_line_num && previous_char == NEWLINE)
    {
      printf("%6i  ", line_counter);
      line_counter++;
    }
    
      /* print out character to stdout */
    putc(current_char, stdout);
  }
  
}


/*****************************************************************************/
/*!

\brief
  Objective of main is to filter file(s) passed by command line.
  Offloads arguments to helper functions.

\param argc
  Number of arguments passed in command line.
  
\param argv
  Nul-terminated arrayof strings  of arguments from command line.

\return
  just returns 0 when operations are complete.
*/
/*****************************************************************************/
int main(int argc, char **argv)
{
    /* file pointer to file being filtered */
  FILE *infile;
  
    /* counter */
  int i;
  
    /* parse the command line, setting option flags and data */
  parse_line(argc, argv);
  
    /* if help screen desired just print that out and exit */
  if(f_help)
  {
      /* call function to print out help screen */
    help_info();
    return 0;
  }
  
    /* if there were more than 0 non-options provided call 
     * assign_files to get them into an array */
  if(non_options != 0)
    assign_files(argc, argv);
  
    /* if no files provided use stdin as file pointer */
  else
  {
      /* set file pointer to stdin */
    infile = stdin;
    
      /* filter stdin */
    filter_file(infile);
    
    return 0;
  }
  
    /* filter all files provided */
  for(i = 0; i < non_options; i++)
  {
      /* assign pointer */
    infile = fopen(files[i], "rt");
    
      /* validate pointer */
    if(!infile)
      continue;
    
      /* filter the file */
    filter_file(infile);
    
      /* close the files */
    fclose(infile);
  }
  
    /* free array os files */
  free(files);
  
  
  return 0;
}
