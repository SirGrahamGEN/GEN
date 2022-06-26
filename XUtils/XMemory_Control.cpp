/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XMemory_Control.cpp
*
* @class      XMEMORY_CONTROL
* @brief      eXtended Memory Control class
* @ingroup    XUTILS
*
* @copyright  GEN Group. All rights reserved.
*
* @cond
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
* documentation files(the "Software"), to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense, and/ or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of
* the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* @endcond
*
* --------------------------------------------------------------------------------------------------------------------*/


/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


#ifdef XMEMORY_CONTROL_ACTIVE

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdlib.h>
#include <string.h>

#include "XFactory.h"
#include "XString.h"
#include "XTrace.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

XMEMORY_CONTROL XMemory_Control;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XMEMORY_CONTROL::XMEMORY_CONTROL()
* @brief      Constructor
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XMEMORY_CONTROL::XMEMORY_CONTROL()
{
  Clean();

//int index = 0;

  #ifdef WINDOWS
  mutexhandle = (XQWORD)CreateMutex( NULL, FALSE, NULL );
  if(!mutexhandle) return;
  #endif

  #ifdef LINUX
  pthread_mutexattr_init(&attr);

  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

  if(!pthread_mutex_init(&mutex, &attr)) mutexhandle = 1;
  #endif

  ResizeAssignList();

  active = true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XMEMORY_CONTROL::~XMEMORY_CONTROL()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XMEMORY_CONTROL::~XMEMORY_CONTROL()
{
  active = false;

  FreeAll();

  #ifdef WINDOWS
  if(mutexhandle)
    {
      CloseHandle((HANDLE)mutexhandle);
      mutexhandle = NULL;
    }
  #endif

  #ifdef LINUX
  if(mutexhandle)
    {
      pthread_mutex_destroy(&mutex);
      mutexhandle = 0;
    }
  #endif

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XMEMORY_CONTROL::IsActive()
* @brief      IsActive
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XMEMORY_CONTROL::IsActive()
{
  return active;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* XMEMORY_CONTROL::Assign(size_t size,char* pathfile,int line)
* @brief      Assign
* @ingroup    XUTILS
*
* @param[in]  size :
* @param[in]  pathfile :
* @param[in]  line :
*
* @return     void* :
*
* --------------------------------------------------------------------------------------------------------------------*/
void* XMEMORY_CONTROL::Assign(XDWORD size, char* pathfile, int line)
{
  if(!size) return NULL;

  Lock();

  void* ptr = NULL;
  ptr = malloc(size);
  if(!ptr)
    {
      UnLock();
      return NULL;
    }

  if(!RegisterAssign(ptr, size, pathfile, line))
    {
      //XTRACE_PRINTCOLOR(4, __L("XMEMORY ALERT: Make Malloc -> The memory allocation could not be registered!"));
    }

  nassigns++;
  maxnassigns    = __MAX(nassigns, maxnassigns);

  used          += size;
  maxused        = __MAX(used, maxused);

  UnLock();

  return ptr;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XMEMORY_CONTROL::Free(void* ptr)
* @brief      Free
* @ingroup    XUTILS
*
* @param[in]  ptr :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XMEMORY_CONTROL::Free(void* ptr)
{
  if(!ptr) return;

  Lock();

  free(ptr);

  XDWORD size;

  if(!DeRegisterAssign(ptr, size))
    {
      //XTRACE_PRINTCOLOR(4, __L("XMEMORY ALERT: Make Free -> The memory allocation has not been registered!"));
    }
   else
    {
      nassigns--;
      used -= size;
    }

  UnLock();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XMEMORY_CONTROL::FreeAll()
* @brief      FreeAll
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XMEMORY_CONTROL::FreeAll()
{
  Lock();

  memset(assignlist, 0, sizeof(XMEMORY_CONTROL_ASSIGN*)*nregisterelements);

  free(assignlist);

  UnLock();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XMEMORY_CONTROL::GetMemoryUsed()
* @brief      GetMemoryUsed
* @ingroup    XUTILS
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XMEMORY_CONTROL::GetUsed()
{
  return used;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XMEMORY_CONTROL::GetMemoryNAssigns()
* @brief      GetMemoryNAssigns
* @ingroup    XUTILS
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XMEMORY_CONTROL::GetNAssigns()
{
  return nassigns;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XMEMORY_CONTROL::DisplayAll(bool displaydata)
* @brief      DisplayAll
* @ingroup    XUTILS
*
* @param[in]  displaydata :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XMEMORY_CONTROL::DisplayAll(bool displaydata)
{
  int nassigned = 0;

  for(XDWORD c=0; c<nregisterelements; c++)
    {
      if(assignlist[c].ptr) nassigned++;
    }

  #ifdef XTRACE_ACTIVE

  XTRACE_PRINTHEADER((!nassigned)?__L("ALL FREE MEMORY RESOURCES"):__L("NOT FREE MEMORY RESOURCES"));
  XTRACE_PRINT(__L(" "));
  XTRACE_PRINT(__L("Maximum allocated blocks at a time : %d") , maxnassigns);
  XTRACE_PRINT(__L("Maximum memory used at a time      : %dk"), maxused/1024);

  if(nassigned)
    {
      XTRACE_PRINT(__L("Number memory blocks not free      : %d"), nassigned);
      XTRACE_PRINT(__L(" "));
      XTRACE_PRINT(__L("         Address  Size    Line  Module"));

      XDWORD count = 0;

      for(XDWORD c=0; c<nregisterelements; c++)
        {
          if(assignlist[c].ptr)
            {
              XSTRING namemodule;

              namemodule = assignlist[c].namemodule;

              size_t ptr = (size_t)assignlist[c].ptr;
              XDWORD address = (XDWORD)ptr;

              XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("%08d %08X %07d %05d %s")   , c
                                                                                  , address
                                                                                  , assignlist[c].size
                                                                                  , assignlist[c].linemodule
                                                                                  , namemodule.Get());

              //-----------------------------------------------------------------


              int datablocksize  = assignlist[c].size;
              if(datablocksize > XMEMORY_CONTROL_SHOWDATABLOCKSIZE) datablocksize = XMEMORY_CONTROL_SHOWDATABLOCKSIZE;

              if(displaydata)
                {
                  XTRACE_PRINTDATABLOCK(XDEBUGLEVELCOLOR(XTRACE_COLOR_RED), (XBYTE*)assignlist[c].ptr, datablocksize, 1);
                }

              //-----------------------------------------------------------------

              count++;
              if(count > XMEMORY_CONTROL_MAXIMUNLEAKSTODISPLAY)
                {
                  XTRACE_PRINTCOLOR(XTRACE_LEVEL_COLOR(XTRACE_COLOR_RED), __L("Too many leaks: > %d and have %d. "), XMEMORY_CONTROL_MAXIMUNLEAKSTODISPLAY, nassigned);
                  break;
                }
            }
        }

      XTRACE_PRINTHEADER(NULL);
    }

  #endif

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XMEMORY_CONTROL::Lock()
* @brief      Lock
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XMEMORY_CONTROL::Lock()
{
  #ifdef WINDOWS
  if(!mutexhandle) return false;
  if(WaitForSingleObject((HANDLE)mutexhandle, INFINITE) == WAIT_FAILED) return false;
  #endif

  #ifdef LINUX
  if(!mutexhandle)               return false;
  if(pthread_mutex_lock(&mutex)) return false;
  #endif

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XMEMORY_CONTROL::UnLock()
* @brief      UnLock
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XMEMORY_CONTROL::UnLock()
{
  #ifdef WINDOWS
  if(!mutexhandle)                       return false;
  if(!ReleaseMutex((HANDLE)mutexhandle)) return false;
  #endif

  #ifdef LINUX
  if(!mutexhandle)                       return false;
  if(pthread_mutex_unlock(&mutex))       return false;
  #endif

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XMEMORY_CONTROL::CRC32ForByte(XDWORD ini)
* @brief      CRC32ForByte
* @ingroup    XUTILS
*
* @param[in]  ini :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XMEMORY_CONTROL::CRC32ForByte(XDWORD ini)
{
  for(int c = 0; c<8; ++c)
    {
      ini = (ini & 1? 0: (XDWORD)0xEDB88320L) ^ ini >> 1;
    }

  return ini ^ (XDWORD)0xFF000000L;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XMEMORY_CONTROL::CRC32(XBYTE* data, XWORD size)
* @brief      CRC32
* @ingroup    XUTILS
*
* @param[in]  data :
* @param[in]  size :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XMEMORY_CONTROL::CRC32(XBYTE* data, XWORD size)
{
  static XDWORD table[0x100];
  XDWORD        crc = 0;

  if(!*table)
    {
      for(XWORD c=0; c<0x100; ++c)
        {
          table[c] = CRC32ForByte(c);
        }
    }

  for(XDWORD c=0; c<size; ++c)
    {
      crc = table[(XBYTE)crc ^ ((XBYTE*)data)[c]] ^ crc >> 8;
    }

  return crc;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XMEMORY_CONTROL::RegisterAssign(void* ptr, size_t size, char* pathfile, int line)
* @brief      RegisterAssign
* @ingroup    XUTILS
*
* @param[in]  ptr :
* @param[in]  size :
* @param[in]  pathfile :
* @param[in]  line :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XMEMORY_CONTROL::RegisterAssign(void* ptr, XDWORD size, char* pathfile, int line)
{
  XDWORD index = 0;

  if(!SearchAssignIndex(true, ptr, index))
    {
      if(!ResizeAssignList())             return false;
      if(!SearchAssignIndex(true, NULL, index)) return false;
    }

  assignlist[index].ptr         = ptr;
  assignlist[index].size        = size;

  XDWORD sizenamemodule = (XDWORD)strlen(pathfile)+1;
  int    c              = (int)sizenamemodule;

  while(c>=0)
    {
      if((pathfile[c] == '\\')  || (pathfile[c] == '/')) break;
      c--;
    }

  sizenamemodule    -= c;
  if(sizenamemodule >= XMEMORY_CONTROL_MAXNAMEMODULESIZE) sizenamemodule = (XMEMORY_CONTROL_MAXNAMEMODULESIZE-1);

  memcpy(assignlist[index].namemodule, &pathfile[c+1], sizenamemodule);

  assignlist[index].linemodule  = line;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XMEMORY_CONTROL::DeRegisterAssign(void* ptr, XDWORD& size)
* @brief      DeRegisterAssign
* @ingroup    XUTILS
*
* @param[in]  ptr :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XMEMORY_CONTROL::DeRegisterAssign(void* ptr, XDWORD& size)
{
  XDWORD index = 0;

  if(!SearchAssignIndex(false, ptr, index))
    {
      return false;
    }

  size = assignlist[index].size;

  assignlist[index].ptr         = NULL;
  assignlist[index].size        = 0;
  memset(assignlist[index].namemodule, 0, XMEMORY_CONTROL_MAXNAMEMODULESIZE);
  assignlist[index].linemodule  = 0;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XMEMORY_CONTROL::ResizeAssignList(XDWORD newnregisterelements)
* @brief      ResizeAssignList
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XMEMORY_CONTROL::ResizeAssignList()
{
  nblockregisterelements++;

  XDWORD newnregisterelements = (nblockregisterelements * XMEMORY_CONTROL_MAXBLOCKASSIGN);

  assignlist = (XMEMORY_CONTROL_ASSIGN*)realloc(assignlist, (sizeof(XMEMORY_CONTROL_ASSIGN) * newnregisterelements));
  if(!assignlist)  return false;

  XDWORD sizeextra  = (sizeof(XMEMORY_CONTROL_ASSIGN) *  (newnregisterelements - nregisterelements));

  // Erase new block
  memset(&assignlist[nregisterelements], 0, sizeextra);

  nregisterelements = newnregisterelements;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XMEMORY_CONTROL::SearchIndex(void* ptr, XDWORD& index)
* @brief      SearchIndex
* @ingroup    XUTILS
*
* @param[in]  ptr :
* @param[in]  index :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XMEMORY_CONTROL::SearchAssignIndex(bool free, void* ptr, XDWORD& index)
{
  XDWORD  start   = 0;
  XDWORD  counter = 0;
  XDWORD  limit   = 0;
  bool    found   = false;

  index   = 0;

  #ifdef MICROCONTROLLER
  start = 0;
  #else
  start = CRC32((XBYTE*)&ptr, sizeof(XDWORD));
  start &= (nregisterelements -1);
  #endif

  counter = start;
  if(counter >= nregisterelements-1)  counter = 0;

  limit = (nregisterelements-1);

  for(int c=0; c<2; c++)
    {
      while(counter < limit)
        {
          if(free)
            {
              if(!assignlist[counter].ptr)
                {
                  index = counter;
                  found = true;
                  break;
                }
            }
           else
            {
              if(assignlist[counter].ptr == ptr)
                {
                  index = counter;
                  found = true;
                  break;
                }
            }

          counter++;
        }

     if(found) return true;

     counter = 0;
     limit   = start;
   }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XMEMORY_CONTROL::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XMEMORY_CONTROL::Clean()
{
  active                  = false;

  assignlist              = NULL;

  nregisterelements       = 0;
  nblockregisterelements  = 0;

  nassigns                = 0;
  maxnassigns             = 0;

  used                    = 0;
  maxused                 = 0;

  mutexhandle             = 0;
}



#undef new

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* operator new(std::size_t size, char const* namefile, int line)
* @brief      perator new
* @ingroup    XUTILS
*
* @param[in]  size :
* @param[in]  const* namefile :
* @param[in]  line :
*
* @return     void* :
*
* --------------------------------------------------------------------------------------------------------------------*/
void* operator new(size_t size, char const* namefile, int line)
{
  if(XMemory_Control.IsActive())
    {
      return XMemory_Control.Assign((XDWORD)size, (char*)namefile, line);
    }
   else
    {
      return malloc(size);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* operator new[](std::size_t size, char const* namefile, int line)
* @brief      perator new[]
* @ingroup    XUTILS
*
* @param[in]  size :
* @param[in]  const* namefile :
* @param[in]  line :
*
* @return     void* :
*
* --------------------------------------------------------------------------------------------------------------------*/
void* operator new[](size_t size, char const* namefile, int line)
{
  if(XMemory_Control.IsActive())
    {
      return XMemory_Control.Assign((XDWORD)size, (char*)namefile, line);
    }
   else
    {
      return malloc(size);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void operator delete(void* ptr) noexcept
* @brief      perator delete
* @ingroup    XUTILS
*
* @param[in]  ptr) noexcep :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void operator delete(void* ptr) throw ()
{
  if(XMemory_Control.IsActive())
    {
      XMemory_Control.Free(ptr);
    }
   else
    {
      free(ptr);
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void operator delete[] (void* ptr) noexcept
* @brief      perator delete[]
* @ingroup    XUTILS
*
* @param[in]  ptr) noexcep :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void operator delete[] (void* ptr) throw ()
{
  if(XMemory_Control.IsActive())
    {
      XMemory_Control.Free(ptr);
    }
   else
    {
      free(ptr);
    }
}


#define new new(__FILE__, __LINE__)


#endif
