/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XLINUXSharedMemoryManager.cpp
*
* @class      XLINUXSHAREDMEMORYMANAGER
* @brief      eXtended LINUX Shared Memory Manager (Exchange between applications)
* @ingroup    PLATFORM_LINUX
*
* @copyright  GEN Group. All right reserved.
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
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "XBase.h"
#include "XString.h"
#include "XTrace.h"

#include "XLINUXSharedMemoryManager.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLINUXSHAREDMEMORYMANAGER::XLINUXSHAREDMEMORYMANAGER()
* @brief      Constructor
* @ingroup    PLATFORM_LINUX
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XLINUXSHAREDMEMORYMANAGER::XLINUXSHAREDMEMORYMANAGER()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLINUXSHAREDMEMORYMANAGER::~XLINUXSHAREDMEMORYMANAGER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XLINUXSHAREDMEMORYMANAGER::~XLINUXSHAREDMEMORYMANAGER()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE* XLINUXSHAREDMEMORYMANAGER::Create(XCHAR* ID, XDWORD size, bool ispublic)
* @brief      Create
* @ingroup    PLATFORM_LINUX
*
* @param[in]  ID :
* @param[in]  size :
* @param[in]  ispublic :
*
* @return     XBYTE* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XBYTE* XLINUXSHAREDMEMORYMANAGER::Create(XCHAR* ID, XDWORD size, bool ispublic)
{
  this->ID   = ID;
  this->size = (size +  sizeof(XDWORD));

  // create the shared memory segment
  XSTRING_CREATEOEM(this->ID, namefile);
  handlefile = shm_open(namefile, O_CREAT | O_RDWR, 0755);
  XSTRING_DELETEOEM(this->ID, namefile);

  if(handlefile < 0) return NULL;

  // configure the size of the shared memory segment
  ftruncate(handlefile, size);

  // now map the shared memory segment in the address space of the process
  base = (XBYTE*)mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, handlefile, 0);
  if(base)
    {
      XDWORD* ptrsize = (XDWORD*)base;
      (*ptrsize) = this->size;

      pointer  = base;
      pointer += sizeof(XDWORD);
    }

  isserver = true;

  return pointer;
}



/**-------------------------------------------------------------------------------------------------------------------
*
*  @fn         XLINUXSHAREDMEMORYMANAGER::Open
*  @brief      Open Shared Memory, created by other process
*  @ingroup    PLATFORM_LINUX
*
*  ""
*  ""
*
*  @param[in]  ID : Identificador unique of the shared memory
*  @param[out] size : return size of this shared memory
*
*  @return     XBYTE* : Pointer to shared memory
*
*---------------------------------------------------------------------------------------------------------------------*/
XBYTE* XLINUXSHAREDMEMORYMANAGER::Open(XCHAR* ID, XDWORD& size)
{
  this->ID   = ID;
  this->size = 0;

  // open the shared memory segment as if it was a file
  XSTRING_CREATEOEM(this->ID, namefile);
  handlefile = shm_open(namefile, O_RDWR, 0755);
  XSTRING_DELETEOEM(this->ID, namefile);

  if(handlefile < 0) return NULL;

  // map the shared memory segment to the address space of the process */
  base = (XBYTE*)mmap(0, sizeof(XDWORD), PROT_READ | PROT_WRITE, MAP_SHARED, handlefile, 0);

  if(base)
    {
       size = (XDWORD)(*base);
       munmap(pointer, sizeof(XDWORD));

       base = (XBYTE*)mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, handlefile, 0);
       if(base)
         {

           this->size = size;

           size -= sizeof(XDWORD);

           pointer  = base;
           pointer += sizeof(XDWORD);
         }
    }

   isserver = false;

  return pointer;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLINUXSHAREDMEMORYMANAGER::Close
* @brief      Close Shared Memory for this instance
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXSHAREDMEMORYMANAGER::Close()
{
  if(!pointer)       return false;
  if(handlefile < 0) return false;

  if(!isserver) munmap(base, size);
  close(handlefile);

  /*
  if(!isserver)
    {
      XSTRING_CREATEOEM(ID, namefile);
      shm_unlink(namefile);
      XSTRING_DELETEOEM(ID, namefile);
    }
  */

  handlefile = -1;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLINUXSHAREDMEMORYMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XLINUXSHAREDMEMORYMANAGER::Clean()
{
  handlefile = -1;
}
