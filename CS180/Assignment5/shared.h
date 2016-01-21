#ifndef SHARED_H
#define SHARED_H

#include "memmgr.h" /* block_info, MMPolicy */


/* conveniences for casting and declarations */
typedef block_info* (*MM_CREATE)(size_t, MMPolicy);
typedef void* (*MM_ALLOCATE)(block_info *, size_t, char *);
typedef int (*MM_DEALLOCATE)(block_info *, void *);
typedef void (*MM_DESTROY)(block_info *);

/* Function pointers retrieved from the shared library */
typedef struct LibraryFunctions
{
  MM_CREATE create;
  MM_DESTROY destroy;
  MM_ALLOCATE allocate;
  MM_DEALLOCATE deallocate;
}LibraryFunctions;

/* Loads a shared library and returns a pointer to it in libhandle */
/* Returns SUCCESS, if it successful, otherwise, FAILURE           */
int load_library(const char *libname, void **libhandle);

/*******************************************************************************
  The function names in the fn_names array correspond to the functions in
  this strict order:

    mm_create
    mm_destroy
    mm_allocate
    mm_deallocate

  Make sure to set the corresponding function pointer in the LibraryFunctions
  struct to the appropriate value (address).

  Returns SUCCESS, if it successfully retrieves all function pointers. 
  Otherwise, it returns FAILURE. If any one of the functions can't be found, 
  you must return FAILURE immediately. DO NOT CALL ANY OTHER FUNCTION UPON A 
  FAILURE!!
*******************************************************************************/
int get_functions(void *libhandle, 
                   LibraryFunctions *functions, 
                   const char **fn_names);

#endif
