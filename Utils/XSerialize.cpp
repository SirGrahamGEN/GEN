/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XSerialize.cpp
* 
* @class      XSERIALIZE
* @brief      eXtended Serializate class
* @ingroup    UTILS
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


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "XSerialize.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSERIALIZE::XSERIALIZE()
* @brief      Constructor
* @ingroup    UTILS
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSERIALIZE::XSERIALIZE()

{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSERIALIZE::~XSERIALIZE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSERIALIZE::~XSERIALIZE()

{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZE::SerializeData(XSERIALIZEPTR* ptr, int nptr,XBUFFER* buffer,bool load)
* @brief      SerializeData
* @ingroup    UTILS
* 
* @param[in]  ptr : 
* @param[in]  nptr : 
* @param[in]  buffer : 
* @param[in]  load : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZE::SerializeData(XSERIALIZEPTR* ptr, int nptr,XBUFFER* buffer,bool load)
{
  if(!ptr)    return false;
  if(!nptr)   return false;
  if(!buffer) return false;

  int c;

  if(load)
    {
      for(c=0;c<nptr;c++)
        {
          buffer->Get(ptr[c].buffer,ptr[c].size);
        }
    }
   else
    {
      XDWORD size = 0;

      for(c=0;c<nptr;c++)
        {
          size += ptr[c].size;
        }

      XBUFFER* newbuffer = new XBUFFER((XDWORD)size, true);
      if((!newbuffer)||(!newbuffer->Get()))
        {
          delete newbuffer;
          return false;
        }

      for(c=0;c<nptr;c++)
        {
          newbuffer->Set(ptr[c].buffer,ptr[c].size);
        }

      buffer->Add(newbuffer);

      delete newbuffer;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZE::Clean()
{

}
