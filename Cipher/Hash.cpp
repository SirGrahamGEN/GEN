/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Hash.cpp
* 
* @class      HASH
* @brief      Hash interface class
* @ingroup    CIPHER
* 
* @copyright  GEN Group All rights reserved.
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

#include "XFactory.h"
#include "XFile.h"

#include "Hash.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         HASH::HASH()
* @brief      Constructor
* @ingroup    CIPHER
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
HASH::HASH()
{
  Clean();

  result = new XBUFFER();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         HASH::~HASH()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    CIPHER
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
HASH::~HASH()
{
  delete result;

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         HASHTYPE HASH::GetType()
* @brief      GetType
* @ingroup    CIPHER
* 
* @return     HASHTYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
HASHTYPE HASH::GetType()
{ 
  return type;                  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* HASH::GetOUINoSign()
* @brief      GetOUINoSign
* @ingroup    CIPHER
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* HASH::GetOUINoSign()
{ 
  return &OUInosignstring;      
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool HASH::Do(XBYTE* input, XQWORD size)
* @brief      Do
* @ingroup    CIPHER
* 
* @param[in]  input : 
* @param[in]  size : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool HASH::Do(XBYTE* input, XQWORD size)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool HASH::Do(XBUFFER& input)
* @brief      Do
* @ingroup    CIPHER
* 
* @param[in]  input : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool HASH::Do(XBUFFER& input)
{
  return Do(input.Get(), input.GetSize());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool HASH::Do(XPATH& xpath, XQWORD size, XQWORD pos)
* @brief      Do
* @ingroup    CIPHER
* 
* @param[in]  xpath : 
* @param[in]  size : 
* @param[in]  pos : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool HASH::Do(XPATH& xpath, XQWORD size, XQWORD pos)
{
  XFILE* xfile;
  bool   status = false;

  GEN_XFACTORY_CREATE(xfile, Create_File())
  if(!xfile) return false;

  ResetResult();

  if(xfile->Open(xpath, true))
    {
      XQWORD _size;

      if(size == HASHALLFILESIZE) _size = xfile->GetSize(); else _size = size;

      status = Do(xfile, _size, pos);

      xfile->Close();
    }

  if(xfile) GEN_XFACTORY.Delete_File(xfile);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool HASH::Do(XFILE* xfile, XQWORD size, XQWORD pos)
* @brief      Do
* @ingroup    CIPHER
* 
* @param[in]  xfile : 
* @param[in]  size : 
* @param[in]  pos : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool HASH::Do(XFILE* xfile, XQWORD size, XQWORD pos)
{
  if(!xfile)           return false;
  if(!xfile->IsOpen()) return false;

  XBUFFER   xbuffer;
  XQWORD    block   = (((size==HASHALLFILESIZE)?xfile->GetSize():size) / HASHMAXFILESIZEBUFFER);
  XDWORD    mod     = (((size==HASHALLFILESIZE)?xfile->GetSize():size) % HASHMAXFILESIZEBUFFER);
  bool      status  = true;

  if(!xfile->SetPosition(pos)) return false;

  xbuffer.Resize((XDWORD)HASHMAXFILESIZEBUFFER);

  for(XDWORD c=0;c<block;c++)
    {
      if(xfile->Read(xbuffer.Get(), HASHMAXFILESIZEBUFFER))
        {
          if(!Do(xbuffer))
            {
              status = false;
              break;
            }
        }
       else
        {
          status = false;
          break;
        }
    }

  if(status)
    {
      xbuffer.Resize(mod);
      if(xfile->Read(xbuffer.Get(),mod))
        {
          if(!Do(xbuffer))
            {
              status = false;
            }
        }
       else
        {
          status = false;
        }
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool HASH::ResetResult()
* @brief      ResetResult
* @ingroup    CIPHER
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool HASH::ResetResult()
{
  if(!result) return false;

  result->Delete();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int HASH::GetDefaultSize()
* @brief      GetDefaultSize
* @ingroup    CIPHER
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int HASH::GetDefaultSize()
{
  return 0;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* HASH::GetResult()
* @brief      GetResult
* @ingroup    CIPHER
* 
* @return     XBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* HASH::GetResult()
{
  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE* HASH::GetResult(XDWORD& resultsize)
* @brief      GetResult
* @ingroup    CIPHER
* 
* @param[in]  resultsize : 
* 
* @return     XBYTE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE* HASH::GetResult(XDWORD& resultsize)
{
  resultsize = 0;

  if(!result) return NULL;

  resultsize  = result->GetSize();

  return result->Get();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool HASH::GetResultString(XSTRING& stringhex)
* @brief      GetResultString
* @ingroup    CIPHER
* 
* @param[in]  stringhex : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool HASH::GetResultString(XSTRING& stringhex)
{
  stringhex.Empty();

  XBUFFER* xbuffer = GetResult();
  if(!xbuffer) return false;

  if(!xbuffer->GetSize()) return false;

  for(int c=0;c<(int)xbuffer->GetSize();c++)
    {
      XSTRING strbyte;

      strbyte.Format(__L("%02x"), xbuffer->GetByte(c));

      stringhex += strbyte;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void HASH::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    CIPHER
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void HASH::Clean()
{
  type     = HASHTYPE_NONE;
  result   = NULL;
}
