/**
 * @file orxTest.h
 * 
 * Test Module - Offers a basic interface to display a menu of registered test functions
 * 
 * @todo Improve the system with different sub-menu levels
 * @note Maybe that the system could be improved allowing to add other types of functions
 * @note Needs may appears with each module needs.
 * 
 * @note At the moment, each test modules will be staticly linked inside the Test program. (first version)
 * 
 * @note A good extension would be to only put test programs in the test directory.
 * @note Makefile can detect and Build it without modification. Each modules are compiled
 * @note in dynamic libraries. All dynamic libraries present in the test directory are
 * @note automatically used by the Main Test program.
 */
 
 /***************************************************************************
 orxTest.h
 Test Module
 
 begin                : 08/04/2005
 author               : (C) Arcallians
 email                : bestel@arcallians.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License           *
 *   as published by the Free Software Foundation; either version 2.1      *
 *   of the License, or (at your option) any later version.                *
 *                                                                         *
 ***************************************************************************/

#ifndef _orxTEST_H_
#define _orxTEST_H_

#include "orxInclude.h"

#ifdef __orxTEST__


typedef orxVOID (*orxTEST_FUNCTION)(orxVOID);

/** Test module setup
 */
extern orxDLLAPI orxVOID                orxTest_Setup();
/** Initialize the test module
 */
extern orxDLLAPI orxSTATUS              orxTest_Init();
/** Uninitialize the test module
 */
extern orxDLLAPI orxVOID                orxTest_Exit();

/** Register a new function
 * @param   (IN)  _zModuleName      Name of the module (to group a list of functions)
 * @param   (IN)  _zMenuEntry       Text displayed to describe the test function
 * @param   (IN)  _pfnFunction      Function executed when the menu entry is selected
 * @return Returns an Handle on the function
 */
extern orxDLLAPI orxHANDLE orxFASTCALL  orxTest_Register(orxCONST orxSTRING _zModuleName, orxCONST orxSTRING _zMenuEntry, orxCONST orxTEST_FUNCTION _pfnFunction);

/** Starts the test module if needed
 */
extern orxDLLAPI orxVOID orxFASTCALL    orxTest_Start();

/** Freeze test module (blocking menu display)
 * @param   (IN)  _bFreeze          Freeze/unfreeze choice
 */
extern orxDLLAPI orxVOID orxFASTCALL    orxTest_Freeze(orxBOOL _bFreeze);


/* Define test module registration MACRO (entry point of dynamic library) */
#if defined(__orxLINUX__) || defined(__orxMAC__)

  #define orxTEST_DEFINE_ENTRY_POINT(INIT, EXIT)    \
  void __attribute__ ((constructor)) module_init()  \
  {                                                 \
    INIT();                                         \
  }                                                 \
  void __attribute__ ((destructor)) module_exit()   \
  {                                                 \
    EXIT();                                         \
  }

#else /* __orxLINUX__ | __orxMAC__ */

  #ifdef __orxWINDOWS__

  #include <windows.h>

  #define orxTEST_DEFINE_ENTRY_POINT(INIT, EXIT)            \
                                                            \
    BOOL WINAPI DllMain(                                    \
    HINSTANCE hinstDLL,  /* handle to DLL module */         \
    DWORD dwReason,      /* reason for calling function */  \
    LPVOID lpReserved )  /* reserved */                     \
  {                                                         \
    /* Perform actions based on the reason for calling. */  \
    switch(dwReason)                                        \
    {                                                       \
      case DLL_PROCESS_ATTACH:                              \
        /* Initialize once for each new process. */         \
        INIT();                                             \
        break;                                              \
                                                            \
      case DLL_THREAD_ATTACH:                               \
        /* Do thread-specific initialization. */            \
        break;                                              \
                                                            \
      case DLL_THREAD_DETACH:                               \
        /* Do thread-specific cleanup. */                   \
        break;                                              \
                                                            \
      case DLL_PROCESS_DETACH:                              \
        /* Perform any necessary cleanup. */                \
        EXIT();                                             \
        break;                                              \
    }                                                       \
    return TRUE;  /* Successful DLL_PROCESS_ATTACH. */      \
}
  #else
    #define orxTEST_DEFINE_ENTRY_POINT(INIT, EXIT)
    #warning orxTEST Module can not be compiled on this platform, Entry points (#INIT, #EXIT) not defined
  #endif
#endif

#else /* __orxTEST__ */

  #define orxTest_Setup()
  #define orxTest_Init()
  #define orxTest_Exit()
  #define orxTest_Register(_zModuleName, _zMenuEntry, _pfnFunction)
  #define orxTest_Run(_u32NbParam, _azParams)
#endif /* __orxTEST__ */

#endif /* _orxTEST_H_ */
