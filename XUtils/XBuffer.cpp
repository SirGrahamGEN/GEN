/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XBuffer.cpp
*
* @class      XBUFFER
* @brief      eXtended buffer functions class
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

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "XFactory.h"
#include "XRand.h"
#include "XTimer.h"
#include "XVariant.h"
#include "XSystem.h"

#include "XBuffer.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

bool XBUFFER::hardwareuselittleendian = true;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBUFFER::XBUFFER(bool threadsafe)
* @brief      Constructor
* @ingroup    XUTILS
*
* @param[in]  bool : Is thread safe buffer functions
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER::XBUFFER(bool threadsafe)
{
  Clean();

  if(threadsafe) 
    {
      GEN_XFACTORY_CREATE(xmutex, Create_Mutex())
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBUFFER::XBUFFER(XDWORD size, bool threadsafe)
* @brief      Constructor
* @ingroup    XUTILS
*
* @param[in]  size : initial size of the buffer
* @param[in]  threadsafe : true is thread safe operative buffer
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER::XBUFFER(XDWORD size, bool threadsafe)
{
  Clean();

  if(threadsafe) 
    {
      GEN_XFACTORY_CREATE(xmutex, Create_Mutex())
    }

  Resize(size);
  FillBuffer();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBUFFER::~XBUFFER()
* @brief      Destructor
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER::~XBUFFER()
{
  Delete();

  if(xmutex) GEN_XFACTORY.Delete_Mutex(xmutex);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XBUFFER::GetSize()
* @brief      Get actual size of buffer
* @ingroup    XUTILS
*
* @return     XDWORD : size actual of buffer
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XBUFFER::GetSize()
{
  SetBlocked(true);

  XDWORD rsize = size;

  SetBlocked(false);

  return rsize;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::SetSize(XDWORD size)
* @brief      Set size of buffer (not allocated space)
* @ingroup    XUTILS
*
* @param[in]  size : new size of buffer
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::SetSize(XDWORD size)
{
  SetBlocked(true);

  this->size = size;

  SetBlocked(false);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::IsEmpty()
* @brief      Check If buffer is empty
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::IsEmpty()
{
  return (!GetSize())?true:false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XBUFFER::ResetPosition()
* @brief      Set pointer position of buffer to zero.
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XBUFFER::ResetPosition()
{
  SetPosition(0);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XBUFFER::GetPosition()
* @brief      Get Pointer position of buffer
* @ingroup    XUTILS
*
* @return     XDWORD : Pointer position of buffer
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XBUFFER::GetPosition()
{
  return position;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::SetPosition(XDWORD position)
* @brief      Set Pointer to position
* @ingroup    XUTILS
*
* @param[in]  position : new position of pointer.
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::SetPosition(XDWORD position)
{
  this->position = position;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::IsBlocked()
* @brief      Get if this buffer is blocked
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::IsBlocked()
{
  if(!xmutex) return false;

  return xmutex->IsLock();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::SetBlocked(bool blocked)
* @brief      Set Blocked buffer
* @ingroup    XUTILS
*
* @param[in]  blocked : true to blocked buffer.
*
* @return     bool : true if is blocked
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::SetBlocked(bool blocked)
{
  if(!xmutex) return false;

  return (blocked)?xmutex->Lock():xmutex->UnLock();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Add(XBYTE* pbuffer, XDWORD psize)
* @brief      Add array of bytes to buffer
* @ingroup    XUTILS
*
* @param[in]  pbuffer : pointer of bytes to add
* @param[in]  psize : size of array of bytes
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Add(XBYTE* pbuffer, XDWORD psize)
{
  if(!pbuffer)  return false;
  if(!psize)    return false;

  SetBlocked(true);

  XDWORD ppos     = size;
  bool   status   = true;

  if(!Resize(size+psize,false))
    {
      SetBlocked(false);
      return false;
    }

  if(buffer && (size+psize))
         memcpy(&buffer[ppos], pbuffer, psize);
    else status = false;

  SetBlocked(false);

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Add(XBUFFER* buffer)
* @brief      Add buffer to buffer
* @ingroup    XUTILS
*
* @param[in]  buffer : pointer of buffer to add
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Add(XBUFFER* buffer)
{
  return Add(buffer->buffer, buffer->size);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Add(XBUFFER& buffer)
* @brief      Add buffer to buffer
* @ingroup    XUTILS
*
* @param[in]  buffer : buffer to add
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Add(XBUFFER& buffer)
{
  return Add(buffer.buffer, buffer.size);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Add(XBYTE data)
* @brief      Add one byte to buffer
* @ingroup    XUTILS
*
* @param[in]  data : byte to add
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Add(XBYTE data)
{
  return Add((XBYTE*)&data, sizeof(XBYTE));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Add(bool data)
* @brief      Add one boolean to buffer
* @ingroup    XUTILS
*
* @param[in]  data : boolean to add
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Add(bool data)
{
  XBYTE _data = data?1:0;

  return Add((XBYTE*)&_data, sizeof(XBYTE));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Add(XWORD data)
* @brief      Add one WORD to buffer (16 bits)
* @ingroup    XUTILS
*
* @param[in]  data : WORD to add.
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Add(XWORD data)
{
  if(hardwareuselittleendian) SWAPWORD(data);

  return Add((XBYTE*)&data,sizeof(XWORD));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Add(XDWORD data)
* @brief      Add one Doble WORD to buffer (32 bits)
* @ingroup    XUTILS
*
* @param[in]  data : DWORD to Add
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Add(XDWORD data)
{
  if(hardwareuselittleendian) SWAPDWORD(data);

  return Add((XBYTE*)&data, sizeof(XDWORD));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Add(XQWORD data)
* @brief      Add one Quad WORD to buffer (64 bits)
* @ingroup    XUTILS
*
* @param[in]  data : QWORD to add
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Add(XQWORD data)
{
  if(hardwareuselittleendian) SWAPQWORD(data);

  return Add((XBYTE*)&data, sizeof(XQWORD));
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Add(float data)
* @brief      Add one float to buffer
* @ingroup    XUTILS
*
* @param[in]  data : float to add
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Add(float data)
{
  return Add((XBYTE*)&data, sizeof(XDWORD));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Add(double data)
* @brief      Add one double to buffer
* @ingroup    XUTILS
*
* @param[in]  data : double to add
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Add(double data)
{
  return Add((XBYTE*)&data, sizeof(XQWORD));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Add(XSTRING& string, bool normalize)
* @brief      Add
* @ingroup    XUTILS
*
* @param[in]  string :
* @param[in]  normalize :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Add(XSTRING& string, bool normalize)
{
  if(string.IsEmpty()) return false;

  for(XDWORD c=0; c<string.GetSize(); c++)
    {
      if(normalize)
        {
          XWORD data = (XWORD)string.Get()[c];
          if(hardwareuselittleendian) SWAPWORD(data);
          Add((XWORD)data);
        }
       else
        {
          XDWORD data = (XDWORD)string.Get()[c];
          if(hardwareuselittleendian) SWAPDWORD(data);
          Add((XDWORD)data);
        }
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::AddWithMaskArg(XCHAR* mask, va_list& arg)
* @brief      AddWithMaskArg
* @ingroup    XUTILS
*
* @param[in]  mask :
* @param[in]  arg :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::AddWithMaskArg(XCHAR* mask, va_list& arg)
{
  return AddXBufferWithMask((*this), mask, arg);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::AddWithMaskArg(XSTRING* mask, va_list& arg)
* @brief      AddWithMask
* @ingroup    XUTILS
*
* @param[in]  mask :
* @param[in]  arg :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::AddWithMaskArg(XSTRING* mask, va_list& arg)
{
  return AddXBufferWithMask((*this), mask, arg);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::AddWithMask(XCHAR* mask, ...)
* @brief      Add variant data with a mask
* @ingroup    XUTILS
*
* @param[in]  mask : pointer XCHAR with a mask to use in add
* @param[in]  ... : params with a variant data
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::AddWithMask(XCHAR* mask, ...)
{
  if(!mask) return false;

  va_list arg;

  va_start(arg, mask);

  bool status = AddXBufferWithMask((*this), mask, arg);

  va_end(arg);

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::AddWithMask(XSTRING* mask, ...)
* @brief      Add variant data with a mask
* @ingroup    XUTILS
*
* @param[in]  mask : string with a mask to use in add
* @param[in]  ... : params with a variant data
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::AddWithMask(XSTRING* mask, ...)
{
  if(!mask) return false;

  va_list arg;

  va_start(arg, mask);

  bool status = AddXBufferWithMask((*this), mask, arg);

  va_end(arg);

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Insert(XBYTE* pbuffer, XDWORD psize, int frompos)
* @brief      Insert array of bytes into buffer
* @ingroup    XUTILS
*
* @param[in]  pbuffer : pointer to bytes to add
* @param[in]  psize : size of bytes to add
* @param[in]  frompos : position in buffer to insert
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Insert(XBYTE* pbuffer, XDWORD psize, int frompos)
{
  if(!pbuffer)                  return false;
  if(!psize)                    return false;

  if(frompos < 0)               return false;
  if(frompos >= (int)GetSize()) return false;

  XBUFFER xbuffertempo;

  if(frompos) xbuffertempo.Add(Get(), frompos);

  xbuffertempo.Add(pbuffer, psize);
  xbuffertempo.Add(&Get()[frompos], (GetSize()-frompos));

  Empty();

  Add(xbuffertempo);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Insert(XBUFFER* xbuffer, int frompos)
* @brief      Insert to buffer into buffer
* @ingroup    XUTILS
*
* @param[in]  xbuffer : pointer of buffer to insert into buffer
* @param[in]  frompos : position to insert
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Insert(XBUFFER* xbuffer, int frompos)
{
  if(!xbuffer)  return false;

  return Insert(xbuffer->Get(), xbuffer->GetSize(), frompos);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Insert(XBUFFER& xbuffer, int frompos)
* @brief      Insert to buffer into buffer
* @ingroup    XUTILS
*
* @param[in]  xbuffer : buffer to insert into buffer
* @param[in]  frompos : position to insert
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Insert(XBUFFER& xbuffer, int frompos)
{
  return Insert(xbuffer.Get(), xbuffer.GetSize(), frompos);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Insert(XBYTE data, int frompos)
* @brief      Insert one byte into buffer
* @ingroup    XUTILS
*
* @param[in]  data : byte to insert
* @param[in]  frompos : position of insert
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Insert(XBYTE data, int frompos)
{
  return Insert(&data, 1, frompos);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Insert(bool data, int frompos)
* @brief      Insert one boolean into buffer
* @ingroup    XUTILS
*
* @param[in]  data : boolean to insert
* @param[in]  frompos : position of insert
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Insert(bool data, int frompos)
{
  XBYTE _data = data?1:0;

  return Insert(&_data, 1, frompos);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Insert(XWORD data, int frompos)
* @brief      Insert one WORD into buffer (16 bits)
* @ingroup    XUTILS
*
* @param[in]  data : WORD to insert
* @param[in]  frompos : position of insert
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Insert(XWORD data, int frompos)
{
  if(hardwareuselittleendian) SWAPWORD(data);

  return Insert((XBYTE*)&data, sizeof(XWORD), frompos);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Insert(XDWORD data, int frompos)
* @brief      Insert one doble WORD into buffer (32 bits)
* @ingroup    XUTILS
*
* @param[in]  data : Double word to insert
* @param[in]  frompos : position of insert
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Insert(XDWORD data, int frompos)
{
  if(hardwareuselittleendian) SWAPDWORD(data);

  return Insert((XBYTE*)&data, sizeof(XDWORD), frompos);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Insert(XQWORD data, int frompos)
* @brief      Insert quad WORD into buffer (64 bits)
* @ingroup    XUTILS
*
* @param[in]  data : Quad word to insert
* @param[in]  frompos : position of insert
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Insert(XQWORD data, int frompos)
{
  if(hardwareuselittleendian) SWAPQWORD(data);

  return Insert((XBYTE*)&data, sizeof(XQWORD), frompos);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Insert(float data, int frompos)
* @brief      Insert float into buffer
* @ingroup    XUTILS
*
* @param[in]  data : float to insert
* @param[in]  frompos : position of insert
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Insert(float data, int frompos)
{
  return Insert((XBYTE*)&data, sizeof(XDWORD), frompos);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Insert(double data, int frompos)
* @brief      Insert double into buffer
* @ingroup    XUTILS
*
* @param[in]  data : double to insert
* @param[in]  frompos : position of insert
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Insert(double data, int frompos)
{
  return Insert((XBYTE*)&data, sizeof(XQWORD), frompos);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Insert(XSTRING& string, int frompos)
* @brief      Insert string into buffer
* @ingroup    XUTILS
*
* @param[in]  string : string to insert
* @param[in]  frompos : position of insert
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Insert(XSTRING& string, int frompos)
{
  if(string.IsEmpty()) return false;

  for(XDWORD c=0; c<string.GetSize(); c++)
    {
      XDWORD data = (XDWORD)string.Get()[c];

      if(hardwareuselittleendian) SWAPDWORD(data);

      Insert((XDWORD)data, frompos+c);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::InsertWithMaskArg(XCHAR* mask, int frompos, va_list& arg)
* @brief      InsertWithMaskArg
* @ingroup    XUTILS
*
* @param[in]  mask :
* @param[in]  frompos :
* @param[in]  arg :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::InsertWithMaskArg(XCHAR* mask, int frompos, va_list& arg)
{
  XBUFFER xbuffer;

  AddXBufferWithMask(xbuffer, mask, arg);

  return Insert(xbuffer, frompos);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::InsertWithMaskArg(XSTRING* mask, int frompos, va_list& arg)
* @brief      InsertWithMask
* @ingroup    XUTILS
*
* @param[in]  mask :
* @param[in]  frompos :
* @param[in]  arg :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::InsertWithMaskArg(XSTRING* mask, int frompos, va_list& arg)
{
  return InsertWithMaskArg(mask->Get(), frompos, arg);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::InsertWithMask(XCHAR* mask, int frompos, ...)
* @brief      Add variant data with a mask
* @ingroup    XUTILS
*
* @param[in]  mask : pointer XCHAR with a mask to use in insert
* @param[in]  frompos : position of insert
* @param[in]  ... : params with a variant data
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::InsertWithMask(XCHAR* mask, int frompos, ...)
{
  if(!mask) return false;

  va_list  arg;

  va_start(arg, frompos);

  bool status = InsertWithMaskArg(mask, frompos, arg);

  va_end(arg);

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::InsertWithMask(XSTRING* mask, int frompos, ...)
* @brief      Add variant data with a mask
* @ingroup    XUTILS
*
* @param[in]  mask : string with a mask to use in insert
* @param[in]  frompos : position of insert
* @param[in]  ... : params with a variant data
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::InsertWithMask(XSTRING* mask, int frompos, ...)
{
  if(!mask) return false;

  va_list  arg;

  va_start(arg, frompos);

  bool status = InsertWithMaskArg(mask, frompos, arg);

  va_end(arg);

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XBUFFER::Extract(XBYTE* pbuffer, XDWORD ppos, XDWORD psize)
* @brief      Extract to array of bytes from buffer
* @ingroup    XUTILS
*
* @param[out] pbuffer : pointer to array of bytes.
* @param[in]  ppos : position of buffer to extract
* @param[in]  psize : size bytes to extract
*
* @return     XDWORD : number bytes extracted.
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XBUFFER::Extract(XBYTE* pbuffer, XDWORD ppos, XDWORD psize)
{
  SetBlocked(true);

  if((ppos>=size)||(!size))
    {
      SetBlocked(false);
      return 0;
    }

  int esize = psize;

  if((ppos+psize)>=size) esize = (size-ppos);

  if(pbuffer) memcpy(pbuffer, &buffer[ppos],esize);

  // #Imanol changed to avoid copyng overlapped memory, as that's undefined
  memmove(&buffer[ppos], &buffer[ppos+esize], size-(ppos+esize));

  //memcpy(&buffer[ppos],&buffer[ppos+esize],size-(ppos+esize));

  Resize(size-esize,false);

  SetBlocked(false);

  return esize;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Extract(XBYTE& data, XDWORD ppos)
* @brief      Extract one byte from buffer
* @ingroup    XUTILS
*
* @param[out] data : byte extracted
* @param[in]  ppos : position of buffer to extract
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Extract(XBYTE& data, XDWORD ppos)
{
  XDWORD size = Extract((XBYTE*)&data, ppos, sizeof(XBYTE));
  if(size!=sizeof(XBYTE)) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Extract(bool& data, XDWORD ppos)
* @brief      Extract one boolean from buffer
* @ingroup    XUTILS
*
* @param[out] data : boolean extracted
* @param[in]  ppos : position of buffer to extract
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Extract(bool& data, XDWORD ppos)
{
  XBYTE _data = 0;

  XDWORD size = Extract((XBYTE*)&_data, ppos, sizeof(XBYTE));
  if(size!=sizeof(XBYTE)) return false;

  data = _data?true:false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Extract(XWORD& data, XDWORD ppos)
* @brief      Extract one WORD from buffer (16 bits)
* @ingroup    XUTILS
*
* @param[out] data : WORD extracted
* @param[in]  ppos : position of buffer to extract
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Extract(XWORD& data, XDWORD ppos)
{
  XDWORD size = Extract((XBYTE*)&data, ppos, sizeof(XWORD));
  if(size!=sizeof(XWORD)) return false;

  if(hardwareuselittleendian) SWAPWORD(data);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Extract(XDWORD& data, XDWORD ppos)
* @brief      Extract one Double WORD from buffer (32 bits)
* @ingroup    XUTILS
*
* @param[out] data : DWORD extracted
* @param[in]  ppos : position of buffer to extract
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Extract(XDWORD& data, XDWORD ppos)
{
  XDWORD size = Extract((XBYTE*)&data, ppos, sizeof(XDWORD));
  if(size!=sizeof(XDWORD)) return false;

  if(hardwareuselittleendian) SWAPDWORD(data);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Extract(XQWORD& data, XDWORD ppos)
* @brief      Extract one Quad WORD from buffer (64 bits)
* @ingroup    XUTILS
*
* @param[out] data : QWORD extracted
* @param[in]  ppos : position of buffer to extract
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Extract(XQWORD& data, XDWORD ppos)
{
  XDWORD size = Extract((XBYTE*)&data, ppos, sizeof(XQWORD));
  if(size!=sizeof(XQWORD)) return false;

  if(hardwareuselittleendian) SWAPQWORD(data);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Extract(float& data,XDWORD ppos)
* @brief      Extract one float from buffer
* @ingroup    XUTILS
*
* @param[out] data : float extracted
* @param[in]  ppos : position of buffer to extract
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Extract(float& data,XDWORD ppos)
{
  XDWORD size = Extract((XBYTE*)&data, ppos, sizeof(XDWORD));
  if(size!=sizeof(XDWORD)) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Extract(double& data, XDWORD ppos)
* @brief      Extract one double from buffer
* @ingroup    XUTILS
*
* @param[out] data : double extracted
* @param[in]  ppos : position of buffer to extract
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Extract(double& data, XDWORD ppos)
{
  XDWORD size = Extract((XBYTE*)&data, ppos, sizeof(XQWORD));
  if(size!=sizeof(XQWORD)) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Extract(XSTRING& string, XDWORD ppos, XDWORD psize)
* @brief      Extract one string from buffer
* @ingroup    XUTILS
*
* @param[in]  string : string extracted
* @param[in]  ppos : position of buffer to extract
* @param[in]  psize : size of string to extract
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Extract(XSTRING& string, XDWORD ppos, XDWORD psize)
{
  string.Empty();

  XDWORD* _string = new XDWORD[psize];
  int     _size   = psize * sizeof(XDWORD);

  if(!_string) return false;

  int rsize = Extract((XBYTE*)_string, ppos, _size);
  if(rsize == _size)
    {
      for(int c=0; c<(int)psize; c++)
        {
          XDWORD data = (XDWORD)_string[c];
          string.Add((XCHAR)data);
        }
    }

  delete [] _string;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::ExtractWithMaskArg(XCHAR* mask, int frompos, va_list& arg)
* @brief      ExtractWithMaskArg
* @ingroup    XUTILS
*
* @param[in]  mask :
* @param[in]  frompos :
* @param[in]  arg :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::ExtractWithMaskArg(XCHAR* mask, int frompos, va_list& arg)
{
  #ifndef BUILDER

  if(!mask)                         return false;
  if(frompos<0)                     return false;
  if((XDWORD)frompos >= GetSize())  return false;

  XBUFFER buffer;
  va_list arg2;
  XDWORD  sizearg = 0;

  va_copy(arg2, arg);

  sizearg = CalculeExtractSizeArgWithMask((*this), frompos, mask, arg2);

  va_end(arg2);

  if(!sizearg) return false;

  buffer.Add(&Get()[frompos], sizearg);

  bool status = ExtractXBufferWithMask(buffer, mask, arg);
  if(status) Extract(NULL, frompos, sizearg);

  return status;
  #else
  return false;
  #endif
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::ExtractWithMaskArg(XSTRING* mask, int frompos, va_list& arg)
* @brief      ExtractWithMaskArg
* @ingroup    XUTILS
*
* @param[in]  mask :
* @param[in]  frompos :
* @param[in]  arg :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::ExtractWithMaskArg(XSTRING* mask, int frompos, va_list& arg)
{
  return ExtractWithMaskArg(mask->Get(), frompos, arg);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::ExtractWithMask(XCHAR* mask, int frompos, ...)
* @brief      Extract variant data with a mask
* @ingroup    XUTILS
*
* @param[in]  mask : pointer XCHAR with a mask to use in extract
* @param[in]  frompos : position of buffer to extract
* @param[out] ... : params with a variant data
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::ExtractWithMask(XCHAR* mask, int frompos, ...)
{
  if(!mask) return false;

  va_list  arg;

  va_start(arg, frompos);

  bool status = ExtractWithMaskArg(mask, frompos, arg);

  va_end(arg);

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::ExtractWithMask(XSTRING* mask, int frompos, ...)
* @brief      Extract variant data with a mask
* @ingroup    XUTILS
*
* @param[in]  mask : string with a mask to use in extract
* @param[in]  frompos : position of buffer to extract
* @param[in]  ... : params with a variant data
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::ExtractWithMask(XSTRING* mask, int frompos, ...)
{
  if(!mask) return false;

  va_list  arg;

  va_start(arg, frompos);

  bool status = ExtractWithMaskArg(mask, frompos, arg);

  va_end(arg);

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE* XBUFFER::Get()
* @brief      Get Pointer to array of bytes of buffer
* @ingroup    XUTILS
*
* @return     XBYTE* : Array of bytes of buffer
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE* XBUFFER::Get()
{
  if(!size) return NULL;

  return buffer;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE XBUFFER::GetByte(XDWORD index)
* @brief      Get a byte from buffer
* @ingroup    XUTILS
*
* @param[in]  index : index of byte into buffer
*
* @return     XBYTE :
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE XBUFFER::GetByte(XDWORD index)
{
  SetBlocked(true);

  XBYTE data;

  if(index > size)
    {
      SetBlocked(false);
      return 0;
    }

  data = buffer[index];

  position++;

  SetBlocked(false);

  return data;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE XBUFFER::GetLastByte()
* @brief      GetLastByte
* @ingroup    XUTILS
*
* @return     XBYTE :
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE XBUFFER::GetLastByte()
{
  SetBlocked(true);

  XBYTE data = buffer[size-1];

  SetBlocked(false);

  return data;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Get(XBYTE* pbuffer,int psize,int frompos)
* @brief      Get array of bytes from buffer
* @ingroup    XUTILS
*
* @param[out] pbuffer : byte array obtained
* @param[in]  psize : size of array
* @param[in]  frompos : position of buffer to get
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Get(XBYTE* pbuffer,int psize,int frompos)
{
  if(!pbuffer) return false;

  SetBlocked(true);

  int pos = frompos;
  if(frompos == XBUFFER_INVALIDPOSITION) pos = position;

  if((!buffer) || (pos>(int)size))
    {
      SetBlocked(false);
      return false;
    }

  if(buffer)
    {
      memcpy(pbuffer,&buffer[pos],psize);
      position = pos + psize;
    }

  SetBlocked(false);

  if(!buffer) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Get(XBYTE& data, int frompos)
* @brief      Get byte from buffer
* @ingroup    XUTILS
*
* @param[out] data : byte obtained
* @param[in]  frompos : position of buffer to get
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Get(XBYTE& data, int frompos)
{
  SetBlocked(true);

  int pos = frompos;
  if(frompos == XBUFFER_INVALIDPOSITION) pos = position;

  if(pos>(int)size)
    {
      SetBlocked(false);
      return false;
    }

  data = buffer[pos];

  position = pos + 1;

  SetBlocked(false);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Get(bool& data, int frompos)
* @brief      Get boolean from buffer
* @ingroup    XUTILS
*
* @param[in]  data : boolean obtained
* @param[in]  frompos : position of buffer to get
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Get(bool& data, int frompos)
{
  XBYTE _data = 0;
  bool  status;

  status = Get(_data, frompos);

  if(status) data = _data?true:false;

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Get(XWORD& data, int frompos)
* @brief      Get WORD from buffer. (16 bits)
* @ingroup    XUTILS
*
* @param[in]  data : WORD obtained
* @param[in]  frompos : position of buffer to get
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Get(XWORD& data, int frompos)
{
  if(!Get((XBYTE*)&data,sizeof(XWORD), frompos)) return false;

  if(hardwareuselittleendian) SWAPWORD(data);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Get(XDWORD& data, int frompos)
* @brief      Get doble WORD from buffer. (32 bits)
* @ingroup    XUTILS
*
* @param[in]  data : double WORD obtained
* @param[in]  frompos : position of buffer to get
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Get(XDWORD& data, int frompos)
{
  if(!Get((XBYTE*)&data, sizeof(XDWORD), frompos)) return false;

  if(hardwareuselittleendian) SWAPDWORD(data);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Get(XQWORD& data, int frompos)
* @brief      Get quad WORD from buffer. (64 bits)
* @ingroup    XUTILS
*
* @param[in]  data : quad WORD obtained
* @param[in]  frompos : position of buffer to get
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Get(XQWORD& data, int frompos)
{
  if(!Get((XBYTE*)&data, sizeof(XQWORD), frompos)) return false;

  if(hardwareuselittleendian) SWAPQWORD(data);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Get(float& data, int frompos)
* @brief      Get float from buffer.
* @ingroup    XUTILS
*
* @param[in]  data : float obtained
* @param[in]  frompos : position of buffer to get
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Get(float& data, int frompos)
{
  if(!Get((XBYTE*)&data, sizeof(XDWORD), frompos)) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Get(double& data, int frompos)
* @brief      Get double from buffer.
* @ingroup    XUTILS
*
* @param[in]  data : double obtained.
* @param[in]  frompos : position of buffer to get
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Get(double& data, int frompos)
{
  if(!Get((XBYTE*)&data, sizeof(XQWORD), frompos)) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Get(XSTRING& data,  int psize, int frompos)
* @brief      Get string from buffer.
* @ingroup    XUTILS
*
* @param[out] data : strint obtained
* @param[in]  psize : size n bytes to obtain
* @param[in]  frompos : position of buffer to get
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Get(XSTRING& data, int psize, int frompos)
{
  XDWORD pos = frompos;
  if(frompos == XBUFFER_INVALIDPOSITION) pos = position;

  XDWORD c;

  for(XDWORD i = 0; i < (XDWORD)psize; i++)
    {
      if(!Get(c, pos)) return false;

      if(hardwareuselittleendian) SWAPDWORD(c);

      data.Add((XCHAR)c);

      pos += sizeof(XDWORD);
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::GetWithMaskArg(XCHAR* mask, int frompos, va_list& arg)
* @brief      GetWithMaskArg
* @ingroup    XUTILS
*
* @param[in]  mask :
* @param[in]  frompos :
* @param[in]  arg :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::GetWithMaskArg(XCHAR* mask, int frompos, va_list& arg)
{
  XBUFFER xbuffer;

  if(!mask)                         return false;
  if(frompos<0)                     return false;
  if((XDWORD)frompos >= GetSize())  return false;

  xbuffer.Add(&Get()[frompos], (GetSize()-frompos));

  bool status = ExtractXBufferWithMask(xbuffer, mask, arg);

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::GetWithMaskArg(XSTRING* mask, int frompos, va_list& arg)
* @brief      GetWithMask
* @ingroup    XUTILS
*
* @param[in]  mask :
* @param[in]  frompos :
* @param[in]  arg :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::GetWithMaskArg(XSTRING* mask, int frompos, va_list& arg)
{
  if(!mask) return false;

  return GetWithMaskArg(mask->Get(), frompos, arg);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::GetWithMask(XCHAR* mask, int frompos, ...)
* @brief      Get variant data with a mask
* @ingroup    XUTILS
*
* @param[in]  mask : pointer to string with a mask to use in get
* @param[in]  frompos : position of buffer to get
* @param[in]  ... : params with a variant data
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::GetWithMask(XCHAR* mask, int frompos, ...)
{
  if(!mask) return false;

  va_list  arg;

  va_start(arg, frompos);

  bool status = GetWithMaskArg(mask, frompos, arg);

  va_end(arg);

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::GetWithMask(XSTRING* mask, int frompos, ...)
* @brief      Get variant data with a mask
* @ingroup    XUTILS
*
* @param[in]  mask : pointer to string with a mask to use in get
* @param[in]  frompos : position of buffer to get
* @param[in]  ... : params with a variant data
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::GetWithMask(XSTRING* mask, int frompos, ...)
{
  if(!mask) return false;

  va_list  arg;

  va_start(arg, frompos);

  bool status = GetWithMaskArg(mask, frompos, arg);

  va_end(arg);

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Set(XBYTE* pbuffer, int psize, int topos)
* @brief      Set array of bytes into buffer
* @ingroup    XUTILS
*
* @param[in]  pbuffer : pointer of buffer to set
* @param[in]  psize : size of buffer to set.
* @param[in]  topos : position of buffer to set
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Set(XBYTE* pbuffer, int psize, int topos)
{
  SetBlocked(true);

  int pos = topos;
  if(topos == XBUFFER_INVALIDPOSITION) pos = position;

  if((pos+psize) > (int)size)
    {
      SetBlocked(false);
      return false;
    }

  if(pbuffer)
          memcpy(&buffer[pos], pbuffer, psize);
    else  memset(&buffer[pos], 0, psize);

  if(pos==(int)position)  position += psize;

  SetBlocked(false);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Set(XBYTE data, int topos)
* @brief      Set byte to buffer
* @ingroup    XUTILS
*
* @param[in]  data : byte to set
* @param[in]  topos : position of buffer to set
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Set(XBYTE data, int topos)
{
  SetBlocked(true);

  int pos = topos;
  if(topos == XBUFFER_INVALIDPOSITION) pos = position;

  if(pos>(int)size)
    {
      SetBlocked(false);
      return false;
    }

  buffer[pos]= data;

  if(pos==(int)position) position++;

  SetBlocked(false);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Set(bool data, int topos)
* @brief      Set boolean to buffer
* @ingroup    XUTILS
*
* @param[in]  data : boolean to set
* @param[in]  topos : position of buffer to set
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Set(bool data, int topos)
{
  XBYTE _data = data?1:0;

  return Set(_data, topos);

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Set(XWORD data, int topos)
* @brief      Set WORD to buffer. (16 bits)
* @ingroup    XUTILS
*
* @param[in]  data : WORD to set
* @param[in]  topos : position of buffer to set
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Set(XWORD data, int topos)
{
  if(hardwareuselittleendian) SWAPWORD(data);

  return Set((XBYTE*)&data, sizeof(XWORD), topos);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Set(XDWORD data, int topos)
* @brief      Set double WORD to buffer. (32 bits)
* @ingroup    XUTILS
*
* @param[in]  data : DWORD to set
* @param[in]  topos : position of buffer to set
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Set(XDWORD data, int topos)
{
  if(hardwareuselittleendian) SWAPDWORD(data);

  return Set((XBYTE*)&data, sizeof(XDWORD), topos);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Set(XQWORD data, int topos)
* @brief      Set quad WORD to buffer. (64 bits)
* @ingroup    XUTILS
*
* @param[in]  data : QWORD to set
* @param[in]  topos : position of buffer to set
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Set(XQWORD data, int topos)
{
  if(hardwareuselittleendian) SWAPQWORD(data);

  return Set((XBYTE*)&data, sizeof(XQWORD), topos);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Set(float data, int topos)
* @brief      Set float buffer.
* @ingroup    XUTILS
*
* @param[in]  data : float to set
* @param[in]  topos : position of buffer to set
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Set(float data, int topos)
{
  return Set((XBYTE*)&data, sizeof(XDWORD), topos);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Set(double data, int topos)
* @brief      Set double to set
* @ingroup    XUTILS
*
* @param[in]  data : double to set
* @param[in]  topos : position of buffer to set
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Set(double data, int topos)
{
  return Set((XBYTE*)&data, sizeof(XQWORD), topos);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Set(XSTRING& data, int topos)
* @brief      Set string to buffer (normalizes string before set)
* @ingroup    XUTILS
*
* @param[in]  data : string to set
* @param[in]  topos : position of buffer to set
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Set(XSTRING& data, int topos)
{
  // should create temporary array and then put that
  // but on stack it's too much?

  XDWORD* tmp = new XDWORD[data.GetSize()];
  if(!tmp) return false;

  for(XDWORD i = 0; i < data.GetSize(); i++)
    {
      XDWORD _data = data[i];
      if(hardwareuselittleendian) SWAPDWORD(_data);
      tmp[i] = _data;
    }

  if(!Set((XBYTE*)tmp, data.GetSize()*sizeof(XDWORD), topos)) return false;

  delete [] tmp;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XBUFFER::SetWithMaskArg(XCHAR* mask, int topos, va_list& arg)
* @brief      SetWithMaskArg
* @ingroup    XUTILS
*
* @param[in]  mask :
* @param[in]  topos :
* @param[in]  arg :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XBUFFER::SetWithMaskArg(XCHAR* mask, int topos, va_list& arg)
{
  XBUFFER xbuffer;

  AddXBufferWithMask(xbuffer, mask, arg);

  Set(xbuffer.Get(), xbuffer.GetSize(), topos);

  return xbuffer.GetSize();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XBUFFER::SetWithMaskArg(XSTRING* mask, int topos, va_list& arg)
* @brief      SetWithMask
* @ingroup    XUTILS
*
* @param[in]  mask :
* @param[in]  topos :
* @param[in]  arg :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XBUFFER::SetWithMaskArg(XSTRING* mask, int topos, va_list& arg)
{
  if(!mask) return false;

  return SetWithMaskArg(mask->Get(), topos, arg);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XBUFFER::SetWithMask(XCHAR* mask, int topos, ...)
* @brief      Set variant data with a mask
* @ingroup    XUTILS
*
* @param[in]  mask : pointer XCHAR with a mask to use in extract
* @param[in]  topos : position of buffer to set
* @param[in]  ... : params with a variant data
*
* @return     XDWORD : size of byte set
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XBUFFER::SetWithMask(XCHAR* mask, int topos, ...)
{
  if(!mask) return 0;

  va_list  arg;

  va_start(arg, topos);

  XDWORD result = SetWithMaskArg(mask, topos, arg);

  va_end(arg);

  return result;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XBUFFER::SetWithMask(XSTRING* mask, int topos, ...)
* @brief      Set variant data with a mask
* @ingroup    XUTILS
*
* @param[in]  mask : string with a mask to use in extract
* @param[in]  topos : position of buffer to set
* @param[in]  ... : params with a variant data
*
* @return     XDWORD : size of byte set
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XBUFFER::SetWithMask(XSTRING* mask, int topos, ...)
{
  if(!mask) return 0;

  va_list  arg;

  va_start(arg, topos);

  XDWORD result = SetWithMaskArg(mask, topos, arg);

  va_end(arg);

  return result;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Resize(XDWORD newsize, bool setblocked)
* @brief      Resize buffer
* @ingroup    XUTILS
*
* @param[in]  newsize : new size of bufffer.
* @param[in]  setblocked : blocked this operation.
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Resize(XDWORD newsize, bool setblocked)
{
  bool status = true;

  if(setblocked) SetBlocked(true);

  if(!newsize)
    {
      size     = 0;
      position = 0;

      if(sizeassign) memset(buffer, 0,  sizeassign);
    }
   else
    {     
      if(newsize > sizeassign)
        { 
          XBYTE* newbuffer = NULL;         

          sizeassign = (newsize + XBUFFER_BLOCKMEM); 

          newbuffer = new XBYTE[sizeassign];
          if(newbuffer)
            {             
              memset(newbuffer , 0,  sizeassign);

              if(buffer)
                {
                  memcpy(newbuffer , buffer, size);

                  delete[] buffer;

                  buffer   = NULL;
                  size     = 0;
                  position = 0;
                }

              buffer      = newbuffer;              
              size        = newsize;
              position    = 0;
            }
           else
            {
              status = false;
            }
        }
       else
        {
          size        = newsize;
          position    = 0;

          if(sizeassign > size)
            {
              memset(&buffer[size], 0, (sizeassign-size));
            }
        }

      if(size)
        {
          if(position>=size) position = (size-1);
        }
   }

  if(setblocked) SetBlocked(false);

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Delete(bool setblocked)
* @brief      Delete buffer
* @ingroup    XUTILS
*
* @param[in]  setblocked : blocked this operation.
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Delete(bool setblocked)
{
  if(setblocked) SetBlocked(true);

  if(buffer) delete [] buffer;

  buffer        = NULL;
  size          = 0;
  sizeassign    = 0;
  position      = 0;

  if(setblocked) SetBlocked(false);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::FillBuffer(XBYTE fillchar)
* @brief      Fill the buffer with a byte
* @ingroup    XUTILS
*
* @param[in]  fillchar : byte to fill buffer
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::FillBuffer(XBYTE fillchar)
{
  SetBlocked(true);

  bool status = false;

  if(buffer && size)
    {
      memset(buffer, fillchar,  size);
      status = true;
    }

  SetBlocked(false);

  return status;
}



 /**-------------------------------------------------------------------------------------------------------------------
 *
 *  @fn         bool XBUFFER::Empty()
 *  @brief      Delete Buffer (set blocked default)
 *  @ingroup    UTILS
 *
 *  ""
 *  ""
 *
 *  @return     bool : true if is succesful.
 *
 * --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Empty()
 {
   return Delete();
 }



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Swap()
* @brief      Swap buffer (last to first byte and viceversa)
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Swap()
{
  SetBlocked(true);

  for(int c=0; c<(int)(size/2); c++)
    {
      XBYTE tembyte;

      tembyte          = buffer[c];
      buffer[c]        = buffer[size-c-1];
      buffer[size-c-1] = tembyte;
    }

  SetBlocked(false);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Compare(XBYTE* pbuffer,XDWORD psize)
* @brief      Compare buffer to array of bytes
* @ingroup    XUTILS
*
* @param[in]  pbuffer : pointer to buffer to compare
* @param[in]  psize : size of buffer to compare
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Compare(XBYTE* pbuffer,XDWORD psize)
{
  if(!pbuffer)  return false;
  if(!psize)    return false;

  bool status;

  SetBlocked(true);

  if(psize != size)
    {
      SetBlocked(false);
      return false;
    }

  status = (memcmp(pbuffer, buffer, psize) == 0);

  SetBlocked(false);

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Compare(XBUFFER* buffer)
* @brief      Compare buffer to buffer
* @ingroup    XUTILS
*
* @param[in]  buffer : pointer to buffer
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Compare(XBUFFER* buffer)
{
  if(!buffer) return false;

  return Compare(buffer->Get(), buffer->GetSize());
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XBUFFER::Find(XBUFFER* buffer, int startindex)
* @brief      Find
* @ingroup    XUTILS
*
* @param[in]  buffer :
* @param[in]  startindex :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XBUFFER::Find(XBUFFER* buffer, int startindex)
{
  if(!buffer)                        return NOTFOUND;

  if(IsEmpty())                      return NOTFOUND;
  if(!buffer->GetSize())             return NOTFOUND;

  XBYTE* _buffer = buffer->Get();
  XDWORD _size   = buffer->GetSize();

  if(_size > size)                    return NOTFOUND;
  if(startindex>=(int)(size-_size)+1) return NOTFOUND;
  if(startindex<0)                    return NOTFOUND;

  bool found;

  for(XDWORD c=startindex; c<(size-_size)+1; c++)
    {
      found = true;

      for(XDWORD d=0; d<_size; d++)
        {
          if(this->buffer[c+d] != _buffer[d])
            {
              found = false;
              break;
            }
        }

      if(found) return c;
    }

  return NOTFOUND;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XBUFFER::Find(XSTRING& string, bool normalize, int startindex)
* @brief      Find
* @ingroup    XUTILS
*
* @param[in]  string :
* @param[in]  normalize :
* @param[in]  startindex :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XBUFFER::Find(XSTRING& string, bool normalize, int startindex)
{
  XBUFFER buffer;

  buffer.Add(string, normalize);

  return XBUFFER::Find(&buffer, startindex);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Padding_Add(XBYTE bitsadjust, XBUFFER_PADDINGTYPE type)
* @brief      Add Padding (bits) to buffer
* @ingroup    XUTILS
*
* @param[in]  bitsadjust : n bits of padding
* @param[in]  type : type of padding
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Padding_Add(XBYTE bitsadjust, XBUFFER_PADDINGTYPE type)
{
  if(paddinghas) return false;

  paddingbitadjust = bitsadjust;
  paddingsize     = bitsadjust - (size % bitsadjust);

  switch(type)
    {
      case XBUFFER_PADDINGTYPE_ZEROS        :
      case XBUFFER_PADDINGTYPE_SPACES       :
      case XBUFFER_PADDINGTYPE_PKCS7        :
      case XBUFFER_PADDINGTYPE_PKCS5        : for(int c=0;c<paddingsize;c++)
                                                {
                                                  switch(type)
                                                    {
                                                      case XBUFFER_PADDINGTYPE_ZEROS        : Add((XBYTE)0x00);
                                                                                              break;

                                                      case XBUFFER_PADDINGTYPE_SPACES       : Add((XBYTE)0x20);
                                                                                              break;

                                                      case XBUFFER_PADDINGTYPE_PKCS7        :
                                                      case XBUFFER_PADDINGTYPE_PKCS5        : Add((XBYTE)paddingsize);
                                                                                              break;
                                                      default: break;
                                                    }
                                                }
                                              break;

      case XBUFFER_PADDINGTYPE_ANSIX923     : for(int c=0;c<paddingsize-1;c++)
                                                {
                                                  Add((XBYTE)0x00);
                                                }
                                              Add((XBYTE)paddingsize);
                                              break;

      case XBUFFER_PADDINGTYPE_ISO10126     : { XRAND* GEN_XFACTORY_CREATE(xrand, CreateRand())
                                                if(!xrand) return false;

                                                for(int c=0;c<paddingsize-1;c++)
                                                  {
                                                    Add((XBYTE)0x00);
                                                  }

                                                Add((XBYTE)paddingsize);
                                                GEN_XFACTORY.DeleteRand(xrand);
                                              }
                                              break;

      case XBUFFER_PADDINGTYPE_ISOIEC7816_4 : Add((XBYTE)0x80);
                                              for(int c=0;c<paddingsize-1;c++)
                                                {
                                                  Add((XBYTE)0x00);
                                                }
                                              break;
      default: break;
    }

  paddinghas      = true;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Padding_Has()
* @brief      Check if buffer has padding
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Padding_Has()
{
  return paddinghas;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBUFFER_PADDINGTYPE XBUFFER::Padding_GetType()
* @brief      GetType of padding
* @ingroup    XUTILS
*
* @return     XBUFFER_PADDINGTYPE : type of padding
*
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER_PADDINGTYPE XBUFFER::Padding_GetType()
{
  return paddingtype;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE XBUFFER::Padding_GetSize()
* @brief      Get size of padding
* @ingroup    XUTILS
*
* @return     XBYTE : size of padding
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE XBUFFER::Padding_GetSize()
{
  return paddingsize;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Padding_Delete()
* @brief      Delete padding
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Padding_Delete()
{
  if(!paddinghas) return false;

  int newsize = GetSize() - Padding_GetSize();

  Resize(newsize , true);

  if((int)GetSize() != newsize)  return false;

  paddinghas        = false;
  paddingbitadjust    = 0;
  paddingsize       = 0;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE XBUFFER::Bit_GetNBits()
* @brief      Bit_GetNBits
* @ingroup    XUTILS
*
* @return     XBYTE :
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE XBUFFER::Bit_GetNBits()
{
  return nbits;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Bit_SetNBits(int nbits)
* @brief      Bit_SetNBits
* @ingroup    XUTILS
*
* @param[in]  nbits :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Bit_SetNBits(int nbits)
{
  if(nbits > (int)(sizeof(XDWORD)*8)) return false;

  this->nbits = nbits;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Bit_AddData(XDWORD data, int nbits)
* @brief      Bit_AddData
* @ingroup    XUTILS
*
* @param[in]  data :
* @param[in]  nbits :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Bit_AddData(XDWORD data, int nbits)
{
  int _nbits = nbits;

  if(_nbits == XBUFFER_MASTER_NBITS)  _nbits = this->nbits;
  if(_nbits > (int)(sizeof(XDWORD)*8)) return false;

  if(_nbits > nbitsfree)
    {
      XBYTE missingbits   = (_nbits - nbitsfree);
      XBYTE missingbytes  = (missingbits / 8);

      if(missingbits % 8)  missingbytes++;

       for(int c=0; c<missingbytes; c++)
        {
           Add((XBYTE)0);
        }

       nbitsfree +=  (missingbytes * 8);
    }

  int     posbyte;
  int     posbit        = GetSize() * 8;
  int     possubbyte;
  //int     nbytes        = (_nbits / 8);
  XDWORD  mask          = 0;
  bool    status;

  //if(_nbits % 8)  nbytes++;

  posbit     -= nbitsfree;
  posbyte     = (posbit / 8);
  possubbyte  = (posbit % 8);

  for(int c=0; c<_nbits; c++)
    {
       mask  |= 0x01;
       if(c != _nbits-1) mask <<= 0x01;
    }

  XQWORD  _data = data;
  XQWORD  _dataorg      = 0;

  _data &= (XQWORD)mask;
  _data <<= ((sizeof(XQWORD)*8) - _nbits);
  _data >>= possubbyte;

  int nbytescpy = ((_nbits + possubbyte) / 8);

  if((_nbits + possubbyte) % 8) nbytescpy++;

  if((posbyte + nbytescpy) >= (int)GetSize())
    {
      nbytescpy = GetSize() - posbyte;
    }

  status = Get((XBYTE*)&_dataorg, nbytescpy, posbyte);
  _dataorg = SwapQWORD(_dataorg);

  _data |= _dataorg;

  _data = SwapQWORD(_data);
  status = Set((XBYTE*)&_data, nbytescpy, posbyte);

  if(status) nbitsfree -= _nbits;

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XBUFFER::Bit_GetData(int indexbit, int nbits)
* @brief      Bit_GetData
* @ingroup    XUTILS
*
* @param[in]  indexbit :
* @param[in]  nbits :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XBUFFER::Bit_GetData(int indexbit, int nbits)
{
  int _nbits = nbits;

  if(_nbits == XBUFFER_MASTER_NBITS)  _nbits = this->nbits;
  if(_nbits > (int)(sizeof(XDWORD)*8)) return false;

  XDWORD  data      = 0;
  int     posbyte   = (indexbit / 8);
  int     posbit    = (indexbit % 8);
  XDWORD  mask      = 0;
  int     nbytescpy = (_nbits / 8);

  if(_nbits % 8)  nbytescpy++;

  nbytescpy++;

  if(posbyte + nbytescpy > (int)size)
    {
      nbytescpy = (size - posbyte);
    }

  if(!Get((XBYTE*)&data, nbytescpy, posbyte)) return 0;

  data = SwapDWORD(data);

  for(int c=0; c<_nbits; c++)
    {
       mask  |= 0x01;
       if(c != _nbits-1) mask <<= 0x01;
    }

  int displacement = (posbit + _nbits);
  if(displacement > (int)(sizeof(XDWORD)*8))  displacement = (sizeof(XDWORD)*8);

  data >>= ((sizeof(XDWORD)*8) - displacement);

  data &= mask;

  return data;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Bit_SetData(XDWORD data, int indexbit, int nbits)
* @brief      Bit_SetData
* @ingroup    XUTILS
*
* @param[in]  data :
* @param[in]  indexbit :
* @param[in]  nbits :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Bit_SetData(XDWORD data, int indexbit, int nbits)
{
  int _nbits = nbits;

  if(_nbits == XBUFFER_MASTER_NBITS)  _nbits = this->nbits;
  if(_nbits > (int)(sizeof(XDWORD)*8))   return false;

  int     posbyte   = (indexbit / 8);
  int     posbit    = (indexbit % 8);
  XDWORD  mask      = 0;
  int     nbytescpy = (_nbits / 8);

  if(_nbits % 8)  nbytescpy++;

  if(posbyte + nbytescpy > (int)size)
    {
      nbytescpy = (size - posbyte);
    }

  for(int c=0; c<_nbits; c++)
    {
       mask  |= 0x01;
       if(c != _nbits-1) mask <<= 0x01;
    }

  data &= mask;

  data <<= ((sizeof(XDWORD)*8) - (posbit + _nbits));

  data = SwapDWORD(data);

  return Set((XBYTE*)&data, nbytescpy, posbyte);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE XBUFFER::Bit_GetBitsFree()
* @brief      Bit_GetBitsFree
* @ingroup    XUTILS
*
* @return     XBYTE :
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE XBUFFER::Bit_GetBitsFree()
{
  return nbitsfree;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::Bit_SetBitsFree(XBYTE nbitsfree)
* @brief      Bit_SetBitsFree
* @ingroup    XUTILS
*
* @param[in]  nbitsfree :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::Bit_SetBitsFree(XBYTE nbitsfree)
{
  this->nbitsfree = nbitsfree;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::ConvertFromBase64(XSTRING& stringbase64)
* @brief      Convert from string in Base 64.
* @ingroup    XUTILS
*
* @param[in]  stringbase64 : string origin to convert.
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::ConvertFromBase64(XSTRING& stringbase64)
{
  /*
  XSTRING stringbin;

  Delete();

  stringbin.ConvertFromBase64(stringbase64);

  if(stringbin.IsEmpty()) return false;

  for(int c=0; c<(int)stringbin.GetSize(); c++)
    {
      XBYTE data = (XBYTE)stringbin.Get()[c];

      Add(data);
    }

  return true;
*/


  XDWORD  data;
  int     size  = stringbase64.GetSize();
  int     c     = 0;
  int     d;

  Delete();

  if(!size) return false;

  XSTRING_CREATEOEM(stringbase64, charstr)

  do{ data = 0;

      for(d=0;d<4;d++)
        {
          data |= XSTRING::ConvertXCHARToBase64((char)charstr[c+d]);
          if(d!=3) data<<=6;
        }

      data<<=8;

      SWAPDWORD(data);

      XBYTE* ptr = (XBYTE*)&data;
   
      Add(ptr, 3);

      c+=4;
      
    } while(c<size);

  XSTRING_DELETEOEM(stringbase64, charstr)

  return true;


}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::ConvertToBase64(XSTRING& stringbase64)
* @brief      Set String to base 64 from buffer
* @ingroup    XUTILS
*
* @param[out] stringbase64 : string in base 64.
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::ConvertToBase64(XSTRING& stringbase64)
{
  XSTRING stringbin;

  stringbase64.Empty();

  stringbin.Add((*this));
  stringbin.ConvertToBase64(stringbase64);

  return stringbase64.GetSize()?true:false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XBUFFER::DecodeBCD(XDWORD ppos, XDWORD psize)
* @brief      Decode DWORD from buffer BCD
* @ingroup    XUTILS
*
* @param[in]  ppos : position of DWORD
* @param[in]  psize : size of decode
*
* @return     XDWORD : result od decode.
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XBUFFER::DecodeBCD(XDWORD ppos, XDWORD psize)
{
  XDWORD result   = 0;
  int    position = ppos;

  while(psize--)
    {
      XBYTE nibble1 = ( buffer[position] & 0x0F);
      XBYTE nibble2 = ((buffer[position] & 0xF0)>>4);

      if(nibble1 > 9)  return 0;
      if(nibble2 > 9)  return 0;

      result = (result * 100) + ((buffer[position] >> 4) * 10) + (buffer[position] & 0x0F);
      position++;
    }

  return result;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XBUFFER::DecodeBCDLong(XDWORD ppos,XDWORD psize)
* @brief      Decode long from buffer BCD
* @ingroup    XUTILS
*
* @param[in]  ppos :
* @param[in]  psize :
*
* @return     XQWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD XBUFFER::DecodeBCDLong(XDWORD ppos,XDWORD psize)
{
  XQWORD result   = 0;
  int    position = ppos;

  while(psize--)
    {
      XBYTE nibble1 = ( buffer[position] & 0x0F);
      XBYTE nibble2 = ((buffer[position] & 0xF0)>>4);

      if(nibble1 > 9)  return 0;
      if(nibble2 > 9)  return 0;

      result  = (result * 100);
      result += ((buffer[position] >> 4) * 10);
      result += (buffer[position] & 0x0F);

      position++;
    }

  return result;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::GetHardwareUseLittleEndian()
* @brief      GetHardwareUseLittleEndian
* @ingroup    XUTILS
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::GetHardwareUseLittleEndian()
{
 return  XBUFFER::hardwareuselittleendian;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XBUFFER::SetHardwareUseLittleEndian(bool hardwareuselittleendian)
* @brief      Set Hardware Use Little Endian
              Use static solution to eliminate depends of XSYSTEM
* @ingroup    XUTILS
*
* @param[in]  hardwareuselittleendian : true little endian
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XBUFFER::SetHardwareUseLittleEndian(bool hardwareuselittleendian)
{
  XBUFFER::hardwareuselittleendian = hardwareuselittleendian;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::AddXBufferWithMask(XBUFFER& xbuffer, XCHAR* mask, va_list& arg)
* @brief      AddXBufferWithMask
* @ingroup    XUTILS
*
* @param[in]  xbuffer :
* @param[in]  mask :
* @param[in]  arg :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::AddXBufferWithMask(XBUFFER& xbuffer, XCHAR* mask, va_list& arg)
{
  if(!mask)    return false;
  if(!mask[0]) return false;

  int c = 0;

  while(mask[c])
    {
      switch(mask[c])
        {
          case 'B': { XBYTE bvar  = (XBYTE)va_arg(arg, int);
                      xbuffer.Add((XBYTE)bvar);
                    }
                    break;

          case 'W': { XWORD wvar  = (XWORD)va_arg(arg, int);
                      xbuffer.Add((XWORD)wvar);
                    }
                    break;

          case 'D': { XDWORD dvar = va_arg(arg, XDWORD);
                      xbuffer.Add((XDWORD)dvar);
                    }
                    break;

          case 'Q': { XQWORD dvar = va_arg(arg, XQWORD);
                      xbuffer.Add((XQWORD)dvar);
                    }
                    break;

          case 'F': { float fvar = (float)va_arg(arg, double);
                      xbuffer.Add((float)fvar);
                    }
                    break;

          case 'L': { double lvar = va_arg(arg, double);
                      xbuffer.Add((double)lvar);
                    }
                    break;

          case 'O': { int _bvar = va_arg(arg, int);
                      XBYTE bvar  = (_bvar?1:0);
                      xbuffer.Add((XBYTE)bvar);
                    }
                    break;

          case 'A': { XBYTE* avar = va_arg(arg, XBYTE*);
                      int    size;
                      c++;

                      if(mask[c]==__C('X'))
                        {
                          size = va_arg(arg, XDWORD);
                        }
                       else
                        {
                          XSTRING sizestr;

                          while((mask[c]>=__C('0')) && (mask[c]<=__C('9')))
                            {
                              sizestr.Add(mask[c]);
                              c++;
                            }

                          c--;

                          size = sizestr.ConvertToInt();
                        }

                      if(size && avar) xbuffer.Add(avar, size);
                    }
                    break;

          case 'S': { XSTRING* svar = va_arg(arg, XSTRING*);
                      XDWORD size = (svar->GetSize()+1)*sizeof(XWORD);

                      XSTRING_CREATENORMALIZE((*svar), buffnormalize, false)
                      xbuffer.Add((XBYTE*)buffnormalize, size);
                      XSTRING_DELETENORMALIZE((*svar), buffnormalize)
                    }
                    break;

          case 'V': { XVARIANT* svar        = va_arg(arg, XVARIANT*);
                      XDWORD    type        = svar->GetType();
                      XBYTE     isnull      = svar->IsNull();
                      XDWORD    sizevariant = svar->GetSize();

                      xbuffer.Add((XDWORD)type);
                      xbuffer.Add((XBYTE)isnull);
                      xbuffer.Add((XDWORD)sizevariant);

                      if(svar->GetData() && sizevariant) xbuffer.Add((XBYTE*)svar->GetData(), sizevariant);
                    }
                    break;

        }

       c++;
    }

  return xbuffer.GetSize()?true:false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::AddXBufferWithMask(XBUFFER& xbuffer, XSTRING* mask, va_list& arg)
* @brief      AddXBufferWithMask
* @ingroup    XUTILS
*
* @param[in]  xbuffer :
* @param[in]  mask :
* @param[in]  arg :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::AddXBufferWithMask(XBUFFER& xbuffer, XSTRING* mask, va_list& arg)
{
  if(!mask) return false;

  return AddXBufferWithMask(xbuffer, mask->Get(), arg);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XBUFFER::CalculeExtractSizeArgWithMask(XBUFFER& xbuffer, int frompos, XCHAR* mask, va_list& arg)
* @brief      CalculeExtractSizeArgWithMask
* @ingroup    XUTILS
*
* @param[in]  xbuffer :
* @param[in]  frompos :
* @param[in]  mask :
* @param[in]  arg :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XBUFFER::CalculeExtractSizeArgWithMask(XBUFFER& xbuffer, int frompos, XCHAR* mask, va_list& arg)
{
  if(!mask)    return false;
  if(!mask[0]) return false;

  int size = 0;
  int c    = 0;

  while(mask[c])
    {
      switch(mask[c])
        {
          case 'B': { //XBYTE* bvar  = va_arg(arg, XBYTE*);
                      size += sizeof(XBYTE);
                    }
                    break;

          case 'W': { //XWORD wvar  = (XWORD)va_arg(arg, int);
                      size += sizeof(XWORD);
                    }
                    break;

          case 'D': { //XDWORD dvar = va_arg(arg, XDWORD);
                      size += sizeof(XDWORD);
                    }
                    break;

          case 'Q': { //XQWORD dvar = va_arg(arg, XQWORD);
                      size += sizeof(XQWORD);
                    }
                    break;

          case 'F': { //float fvar = (float)va_arg(arg, double);
                      size += sizeof(double);
                    }
                    break;

          case 'L': { //double lvar = va_arg(arg, double);
                      size += sizeof(double);
                    }
                    break;

          case 'O': { //int bvar = va_arg(arg, int);
                      size += sizeof(XBYTE);
                    }
                    break;

          case 'A': { //XBYTE* avar = va_arg(arg, XBYTE*);
                      XDWORD sizearray = 0;
                      c++;

                      if(mask[c]==__C('X'))
                        {
                          XDWORD dvar = va_arg(arg, XDWORD);
                          if(dvar) sizearray = dvar;
                        }
                       else
                        {
                          XSTRING sizestr;

                          while((mask[c]>=__C('0')) && (mask[c]<=__C('9')))
                            {
                              sizestr.Add(mask[c]);
                              c++;
                            }
                          c--;
                          sizearray = sizestr.ConvertToInt();
                        }

                      size += sizearray;
                    }
                    break;

          case 'S': { XSTRING* svar       = va_arg(arg, XSTRING*);
                      XDWORD   sizestring = 0;

                      if(svar)
                        {
                          sizestring  = XSTRING::GetSize((XWORD*)(&xbuffer.Get()[frompos + size]));
                          sizestring += 1;
                          sizestring *= sizeof(XWORD);
                        }

                      size += sizestring;
                    }
                    break;

          case 'V': { XVARIANT* svar        = va_arg(arg, XVARIANT*);
                      XDWORD    sizevariant = 0;

                      sizevariant += sizeof(XDWORD);
                      sizevariant += sizeof(XBYTE);
                      sizevariant += sizeof(XDWORD);

                      if(svar) sizevariant += svar->GetSize();
                      size += sizevariant;
                    }
                    break;
        }

       c++;
    }

  return size;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::ExtractXBufferWithMask(XBUFFER& xbuffer, XCHAR* mask, va_list& arg)
* @brief      ExtractXBufferWithMask
* @ingroup    XUTILS
*
* @param[in]  xbuffer :
* @param[in]  mask :
* @param[in]  arg :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::ExtractXBufferWithMask(XBUFFER& xbuffer, XCHAR* mask, va_list& arg)
{
  if(!mask)    return false;
  if(!mask[0]) return false;

  int c = 0;

  while(mask[c])
    {
      switch(mask[c])
        {
          case 'B': { XBYTE* bvar  = va_arg(arg, XBYTE*);
                      xbuffer.Extract((XBYTE&)(*bvar));
                    }
                    break;

          case 'W': { XWORD* wvar  = va_arg(arg, XWORD*);
                      xbuffer.Extract((XWORD&)(*wvar));
                    }
                    break;

          case 'D': { XDWORD* dvar = va_arg(arg, XDWORD*);
                      xbuffer.Extract((XDWORD&)(*dvar));
                    }
                    break;

          case 'Q': { XQWORD* dvar = va_arg(arg, XQWORD*);
                      xbuffer.Extract((XQWORD&)(*dvar));
                    }
                    break;

          case 'F': { double* fvar = va_arg(arg, double*);
                      xbuffer.Extract((float&)(*fvar), 0);
                    }
                    break;

          case 'L': { double* dvar = va_arg(arg, double*);
                      xbuffer.Extract((double&)(*dvar), 0);
                    }
                    break;

          case 'O': { bool*  bvar  = va_arg(arg, bool*);
                      XBYTE _bvar  = 0;
                      xbuffer.Extract(_bvar);
                      (*bvar) = _bvar?true:false;
                    }
                    break;

          case 'A': { XBYTE* avar = va_arg(arg, XBYTE*);

                      XDWORD size = 0;
                      c++;

                      if(mask[c]==__C('X'))
                        {
                          XDWORD dvar = va_arg(arg, XDWORD);
                          if(dvar) size = dvar;
                        }
                       else
                        {
                          XSTRING sizestr;

                          while((mask[c]>=__C('0')) && (mask[c]<=__C('9')))
                            {
                              sizestr.Add(mask[c]);
                              c++;
                            }
                          c--;
                          size = sizestr.ConvertToInt();
                        }

                      if(size && avar) xbuffer.Extract(avar, 0, size);
                    }
                    break;

          case 'S': { XSTRING* svar = va_arg(arg, XSTRING*);

                      svar->Set((XWORD*)(xbuffer.Get()));
                      XDWORD size = (svar->GetSize()+1)*sizeof(XWORD);

                      xbuffer.Extract(NULL, 0, size);
                    }
                    break;

          case 'V': { XVARIANT* svar        = va_arg(arg, XVARIANT*);
                      XDWORD    type        = 0;
                      XBYTE     isnull      = svar->IsNull();
                      XDWORD    sizevariant = 0;

                      xbuffer.Extract(type);
                      xbuffer.Extract(isnull);
                      xbuffer.Extract(sizevariant);

                      // Imanol : if xbuffer.GetSize() - 9 != sizevariant something went wront and this variant might not be complete(but a full data array is allocated anyways)
                      svar->Set((XVARIANT_TYPE)type, xbuffer.Get(), sizevariant);
                      if(sizevariant) xbuffer.Extract(NULL, 0, sizevariant);
                    }
                    break;
        }

       c++;
    }

  return xbuffer.IsEmpty();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFER::ExtractXBufferWithMask(XBUFFER& xbuffer, XSTRING* mask, va_list& arg)
* @brief      ExtractXBufferWithMask
* @ingroup    XUTILS
*
* @param[in]  xbuffer :
* @param[in]  mask :
* @param[in]  arg :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFER::ExtractXBufferWithMask(XBUFFER& xbuffer, XSTRING* mask, va_list& arg)
{
  if(!mask) return false;

  return ExtractXBufferWithMask(xbuffer, mask->Get(), arg);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XBUFFER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XBUFFER::Clean()
{
  buffer              = NULL;
  size                = 0;
  sizeassign          = 0;
  position            = 0;

  nbits               = 0;
  nbitsfree           = 0;

  paddingtype         = XBUFFER_PADDINGTYPE_NONE;
  paddinghas          = false;
  paddingbitadjust    = 0;
  paddingsize         = 0;

  xmutex              = NULL;
}


