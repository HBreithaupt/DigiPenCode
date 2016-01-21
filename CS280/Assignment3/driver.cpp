#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <stddef.h>

#if defined(__GNUC__)
#if defined(__clang__)
//typedef long int off64_t; // Clang/MinGW
//typedef long int off_t;   // Clang/MinGW
#endif
#include <unistd.h>
#include <getopt.h>
#else
#include "getopt.h"
#endif

#include "Sudoku.h"

  // TODO: allocate dynamically
const int MAX_BOARD_SIZE = 10000;

  // These values control the amount of output
namespace
{
  bool SHOW_BOARDS = false;
  size_t SHOW_BOARDS_EVERY = 1;
  bool CLEAR_SCREEN = false;
  bool SHOW_MESSAGES = false;
  bool PAUSE = false;
  bool SHOW_SOLUTION = true;
  bool ABORTED = false;
  bool SHOW_STATS = false;
}

char gFile[FILENAME_MAX];
char *gBoard = 0;
int BASESIZE = 3;
Sudoku::SymbolType SYMBOL_TYPE = Sudoku::SYM_NUMBER;

void usage(void)
{
  std::cout << "Usage: sudoku [options] input_file\n";
  std::cout << "\n";
  std::cout << "Options:\n";
  std::cout << " -a  --show_solution=X       show final board (0-OFF, 1-ON, default is ON).\n";
  std::cout << " -b  --basesize=X            the size of the board (e.g. 3, 4, 5, etc. Default is 3)\n";
  std::cout << " -c  --clear_screen          clear the screen between boards.\n";
  std::cout << " -e  --show_boards_every=X   only show boards after every X iterations.\n";
  std::cout << " -h  --help                  display this information.\n";
  std::cout << " -m  --show_messages         show all messages (placing, removing, backtracking, etc.\n";
  std::cout << " -p  --pause                 pause between moves (press a key to continue).\n";
  std::cout << " -s  --show_boards           show boards after placing/removing.\n";
  std::cout << " -t  --symbol_type=X         the type of symbols to use, numbers or letters (0 is numbers, 1 is letters)\n";
  std::cout << " -w  --show_stats=X          show statistics after each move.\n";
  std::cout << "\n";
}

void dump_options(void)
{
  std::cout << "     show_solution: " << (SHOW_SOLUTION ? "true" : "false") << std::endl;
  std::cout << "          basesize: " << BASESIZE << std::endl;
  std::cout << "      clear_screen: " << (CLEAR_SCREEN ? "true" : "false") << std::endl;
  std::cout << " show_boards_every: " << SHOW_BOARDS_EVERY << std::endl;
  std::cout << "     show_messages: " << (SHOW_MESSAGES ? "true" : "false") << std::endl;
  std::cout << "             pause: " << (PAUSE ? "true" : "false") << std::endl;
  std::cout << "       show_boards: " << (SHOW_BOARDS ? "true" : "false") << std::endl;
  std::cout << "       symbol_type: " << (SYMBOL_TYPE == Sudoku::SYM_NUMBER ? "Numbers" : "Letters") << std::endl;
  std::cout << "        show_stats: " << (SHOW_STATS ? "true" : "false") << std::endl;
  std::cout << "          filename: " << gFile << std::endl;
}

void parse_commandline(int argc, char **argv)
{
  int fail = 0;
  int option_index = 0;

  static struct option long_options[] = 
  {

    {"show_solution",     required_argument, NULL, 'a'},
    {"basesize",          required_argument, NULL, 'b'},
    {"clear_screen",      no_argument,       NULL, 'c'},
    {"show_boards_every", required_argument, NULL, 'e'},
    {"help",              no_argument,       NULL, 'h'},
    {"show_messages",     no_argument,       NULL, 'm'},
    {"pause",             no_argument,       NULL, 'p'},
    {"show_boards",       no_argument,       NULL, 's'},
    {"symbol_type",       required_argument, NULL, 't'},
    {"show_stats",        no_argument,       NULL, 'w'},
    {NULL,                 0,                NULL, 0}
  };

  optind = 1;
  for(;;)
  {
    int opt = getopt_long(argc, argv, "-:a:b:ce:hmpst:w", long_options, &option_index);

    if (opt == -1)
      break;

    switch (opt) 
    {
      case 0: /* long option */
        /*
        printf("long option %s", long_options[option_index].name);
        if (optarg)
           printf(" with arg %s", optarg);
        printf("\n");
        */
        break;

      case 'a':
        if (std::atoi(optarg))
          SHOW_SOLUTION = true;
        break;
      case 'b':
        BASESIZE = std::atoi(optarg);
        break;
      case 'c':
        CLEAR_SCREEN = true;
        break;
      case 'e':
        if (std::atoi(optarg))
          SHOW_BOARDS_EVERY = true;
        else
          SHOW_BOARDS_EVERY = false;
        break;
      case 'h':
        usage();
        std::exit(0);
      case 'm':
        SHOW_MESSAGES = true;
        break;
      case 'p':
        PAUSE = true;
        break;
      case 's':
        SHOW_BOARDS = true;
        break;
      case 't':
        if (std::atoi(optarg))
          SYMBOL_TYPE = Sudoku::SYM_LETTER;
        else
          SYMBOL_TYPE = Sudoku::SYM_NUMBER;
        break;
      case 'w':
        SHOW_STATS = true;
        break;
      case '?':
        std::cout << "Unknown option: " << optopt << std::endl;
        fail = 1;
        break;
      case ':':
        std::cout << "Missing option for " << optopt << std::endl;
        fail = 1;
        break;
      case 1:
        std::strcpy(gFile, optarg);
        break;
    }
  }

  if (fail)
  {
    usage();
    std::exit(-1);
  }
}

void PrintStats(const Sudoku& board)
{
  Sudoku::SudokuStats stats = board.GetStats();
  std::cout << "  Basesize: " << stats.basesize << std::endl;
  std::cout << "     Moves: " << stats.moves << std::endl;
  std::cout << "    Placed: " << stats.placed << std::endl;
  std::cout << "Backtracks: " << stats.backtracks << std::endl;
  std::cout << "  Filename: " << gFile << std::endl;
}

void DumpBoard(const char *board, int basesize, size_t moves)
{
  int blocksize = basesize * basesize;
  std::cout << "Moves: " << moves << std::endl;

    // two spaces for each symbol
  int len = (blocksize * 2) + (basesize * 2) + 1;

    // print top horizontal line with - and + in the appropriate locations
  for (int k = 0; k < len; k++)
  {
    if ( (k == 0) || !(k % (2 * basesize + 2)))
      std::cout << "+";
    else
      std::cout << "-";
  }
  std::cout << std::endl;

  int count = 0;
  for (int i = 0; i < blocksize * blocksize - 1; i += blocksize)
  {
    std::cout << "|";
    for (int j = 0; j < basesize; j++)
    {
      for (int k = 0; k < basesize; k++)
      {
        std::cout << std::setw(2) << board[i + j * basesize + k + 0];
      }
      std::cout << " |";
      //if (j && ((j == 2) || (j == 5) || (j == 8)) )
    }
    std::cout << std::endl;

    count++;

      // print horizontal lines with - and + in the appropriate locations
      // after each 'set' of symbols
    if (!(count % basesize))
    {
      for (int k = 0; k < len; k++)
      {
        if ( (k == 0) || !(k % (2 * basesize + 2)))
          std::cout << "+";
        else
          std::cout << "-";
      }
      std::cout << std::endl;
    }
  }
}

void Pause(void)
{
  if (ABORTED)
    return;

  if (std::fgetc(stdin) == 'x')
  {
    std::cout << "User abort.\n";
    ABORTED = true;
    std::exit(1);
  }
}

struct RowCol
{
  int row;
  int col;
};

int index_to_row(int index, int basesize)
{
  return index / (basesize * basesize);
}

int index_to_col(int index, int basesize)
{
  return index % (basesize * basesize);
}


RowCol IndexToRowCol(int index, int basesize)
{
  RowCol rc;
  rc.row = index_to_row(index, basesize);
  rc.col = index_to_col(index, basesize);
  return rc;
}

void DisplayDuplicates(int *duplicates, int basesize)
{
  //std::cout << duplicates[0] << "," << duplicates[1] << "," << duplicates[2] << std::endl;
  if (duplicates[0] == -1 && duplicates[1] == -1 && duplicates[2] == -1)
    return;

  RowCol rc;
  std::cout << "Duplicates: ";
  int count = 0;
  if (duplicates[0] != -1)
  {
    rc = IndexToRowCol(duplicates[0], basesize);
    std::cout << "#" << ++count << " at cell " << duplicates[0] << " (" << rc.row + 1 << "," << rc.col + 1 << ") ";
  }
  if (duplicates[1] != -1)
  {
    rc = IndexToRowCol(duplicates[1], basesize);
    std::cout << "#" << ++count << " at cell " << duplicates[1] << " (" << rc.row + 1 << "," << rc.col + 1 << ") ";
  }
  if (duplicates[2] != -1)
  {
    rc = IndexToRowCol(duplicates[2], basesize);
    std::cout << "#" << ++count << " at cell " << duplicates[2] << " (" << rc.row + 1 << "," << rc.col + 1 << ") ";
  }
}

bool Callback(const Sudoku& sudoku, const char *board, Sudoku::MessageType message, 
              size_t move, int basesize, int index, char symbol, int *duplicates)
{
  if (CLEAR_SCREEN && message != Sudoku::MSG_ABORT_CHECK)
    #if defined (__GNUC__)
    if (std::system("clear"))
    #else
    if (std::system("cls"))
    #endif
      std::exit(0);

  switch (message)
  {
    case Sudoku::MSG_STARTING:
      if (SHOW_MESSAGES)
        std::cout << "Starting... \n";
      DumpBoard(board, basesize, move);
      if (SHOW_STATS)
        PrintStats(sudoku);
      std::cout << std::endl;
    break;

    case Sudoku::MSG_PLACING:
      if (SHOW_MESSAGES)
      {
        RowCol rc = IndexToRowCol(index, basesize);
        std::cout << "Move: " << move << ", Placing " << symbol << " at " << rc.row + 1 
                  << "," << rc.col + 1 << " (cell: " << index + 1 << ").";
        std::cout << "  ";
        DisplayDuplicates(duplicates, basesize);
        std::cout << std::endl;
      }
      if (SHOW_BOARDS)
      {
        if (!(move % SHOW_BOARDS_EVERY))
        {
          DumpBoard(board, basesize, move);
          if (SHOW_STATS)
            PrintStats(sudoku);
          std::cout << std::endl;
        }
      }
      break;

    case Sudoku::MSG_REMOVING:
      if (SHOW_MESSAGES)
      {
        RowCol rc = IndexToRowCol(index, basesize);
        std::cout << "Move: " << move << ", Removing " << symbol << " from " << rc.row + 1 << "," 
                  << rc.col + 1 << " (cell: " << index + 1 << ").\n";
      }
      if (SHOW_BOARDS)
      {
        if (!(move % SHOW_BOARDS_EVERY))
        {
          DumpBoard(board, basesize, move);
          if (SHOW_STATS)
            PrintStats(sudoku);
          std::cout << std::endl;
        }
      }
      break;

    case Sudoku::MSG_FINISHED_OK:
      std::cout << "Solution found in " << move << " moves.\n";
      if (SHOW_SOLUTION)
        DumpBoard(board, basesize, move);
      break;

    case Sudoku::MSG_FINISHED_FAIL:
      std::cout << "No solution found after " << move << " moves\n";
      break;

    case Sudoku::MSG_ABORT_CHECK:
      if (ABORTED)
        return true;
      break;

    default:
      std::cout << "Unknown message.\n";
  }

  if (PAUSE)
    Pause();

  return false;
}

void stripnl(char *line)
{
  size_t len = std::strlen(line);
  line[len - 1] = 0;
}

void acquire_board(const char *filename)
{
  std::FILE *fp = std::fopen(filename, "rt");
  if (!fp)
  {
    std::cout << "Failed to open " << filename << " for input.\n";
    std::exit(-1);
  }

    // TODO: Allocate dynamically 
  char buffer[MAX_BOARD_SIZE];
  while (!std::feof(fp))
  {
    if (std::fgets(buffer, MAX_BOARD_SIZE, fp) == NULL)
      break;

      // skip comments (if any)
    if (buffer[0] == '#')
      continue;

    stripnl(buffer);
    gBoard = new char[strlen(buffer) + 1];
    std::strcpy(gBoard, buffer);

      // Currently, there is only 1 board per file
    break;
  }
  std::fclose(fp);
}

typedef void (*TestFn)(void);

void ExecuteTest(TestFn fn, int maxwait = 1000, int safewait = 1000)
{
  if (maxwait + safewait > 0)
    fn();
}

void RunTest()
{
  acquire_board(gFile);
  Sudoku board(BASESIZE, SYMBOL_TYPE, Callback);
  board.SetupBoard(gBoard, static_cast<int>(std::strlen(gBoard)));
  
  std::cout << "\n==================== ";
  std::cout << "Board: [" << BASESIZE << "x" << BASESIZE << "]" << gFile; 
  std::cout << " ====================\n";
  board.Solve();
  PrintStats(board);
  std::cout << std::endl;

  delete [] gBoard;
}


//****************************************************************************************************
//****************************************************************************************************
int main(int argc, char **argv)
{
  parse_commandline(argc, argv);
  //dump_options();
  if (!std::strlen(gFile))
  {
    usage();
    std::exit(1);
  }

  struct TimedTest
  {
    void (*test)(void);
    int maxwait;
    int safewait;
  };
  
  int max = 500;
  int safe = 500;
  TimedTest Test = {RunTest, max, safe};

  ExecuteTest(Test.test, Test.maxwait, Test.safewait);

  return 0;
}
