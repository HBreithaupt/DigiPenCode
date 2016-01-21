/*****************************************************************************/
/*!
\file shared.c
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS180
\par Assignment 5
\date 7/8/15

\brief
  Implementation to use a dll for memory manager.
  
  Functions Include :
    - load_library : assigns file to a library pointer to use the dll
    - get_functions : assigns function pointers to use

*/
/*****************************************************************************/

#include "shared.h"
#include <stdint.h> /* intptr_t             */
#include <dlfcn.h>  /* dl stuff             */

int load_library(const char *libname, void **libhandle)
{
    /* hold error string */
  char *error;
  
    /* assign libray to libhandle pointer */
  *libhandle = dlopen(libname, RTLD_LAZY);
  
    /* check for error */
  error = dlerror();
  
    /* if library wasnt found/error return failure */
  if(error)
    return FAILURE;
  
    /* library found and assigned to pointer
     * return success */
  return SUCCESS;
}



int get_functions(void *libhandle, 
                  LibraryFunctions *functions, 
                  const char **fn_names)
{
  
  char *error;
  
    /* get create function */
  functions->create = (MM_CREATE)(intptr_t)dlsym(libhandle, fn_names[0]);
  
    /* error checking */
  error = dlerror();
  
  if(error)
    return FAILURE;
  
  functions->destroy = (MM_DESTROY)(intptr_t)dlsym(libhandle, fn_names[1]);
  
    /* error checking */
  error = dlerror();
  
  if(error)
    return FAILURE;
  
  
  functions->allocate = (MM_ALLOCATE)(intptr_t)dlsym(libhandle, fn_names[2]);
  
    /* error checking */
  error = dlerror();
  
  if(error)
    return FAILURE;
  
  
  functions->deallocate = (MM_DEALLOCATE)(intptr_t)dlsym(libhandle, fn_names[3]);
  
    /* error checking */
  error = dlerror();
  
  if(error)
    return FAILURE;
  
  return SUCCESS;
}