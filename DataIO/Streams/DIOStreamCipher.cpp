/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOStreamCipher.cpp
* 
* @class      DIOSTREAMCIPHER
* @brief      Data Input/Output Stream with Cipher class
* @ingroup    DATAIO
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOStreamCipher.h"

#include "XFactory.h"
#include "XBuffer.h"

#include "DIOFactory.h"
#include "DIOStream.h"

#include "HashCRC32.h"
#include "Cipher.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMCIPHER::DIOSTREAMCIPHER(DIOSTREAMCONFIG* config, CIPHER* cipher)
* @brief      Constructor of class
* @ingroup    DATAIO
*
* @param[in]  config :
* @param[in]  cipher :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMCIPHER::DIOSTREAMCIPHER(DIOSTREAMCONFIG* config, CIPHER* cipher): DIOSTREAM()
{
  Clean();

  this->config      = config;
  this->cipher      = cipher;

  hashcrc32 = new HASHCRC32();
  if(hashcrc32)
    {
      diostream = (DIOSTREAM*)GEN_DIOFACTORY.CreateStreamIO(config);

      GEN_XFACTORY_CREATE(mutexread   , Create_Mutex())
      GEN_XFACTORY_CREATE(mutexwrite  , Create_Mutex())

      if(diostream && mutexread && mutexwrite)
        {
          xthreadconnection  = CREATEXTHREAD(XTHREADGROUPID_DIOSTREAMCIPHER, __L("DIOSTREAMCIPHER::DIOSTREAMCIPHER"), ThreadRunFunction, (void*)this);
          if(xthreadconnection)
            {
              xthreadconnection->Ini();
            }
        }
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMCIPHER::~DIOSTREAMCIPHER()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMCIPHER::~DIOSTREAMCIPHER()
{
  if(xthreadconnection)
    {
      xthreadconnection->End();
      DELETEXTHREAD(XTHREADGROUPID_DIOSTREAMCIPHER, xthreadconnection);
    }

  if(mutexread)   GEN_XFACTORY.Delete_Mutex(mutexread);
  if(mutexwrite)  GEN_XFACTORY.Delete_Mutex(mutexwrite);

  if(diostream) GEN_DIOFACTORY.DeleteStreamIO(diostream);

  if(hashcrc32) delete hashcrc32;

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMCONFIG* DIOSTREAMCIPHER::GetConfig()
* @brief      Get config
* @ingroup    DATAIO
*
* @return     DIOSTREAMCONFIG* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMCONFIG* DIOSTREAMCIPHER::GetConfig()
{
  return config;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMCIPHER::SetConfig(DIOSTREAMCONFIG* config)
* @brief      Set config
* @ingroup    DATAIO
*
* @param[in]  config :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMCIPHER::SetConfig(DIOSTREAMCONFIG* config)
{
  this->config = config;
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMSTATUS DIOSTREAMCIPHER::GetStatus()
* @brief      Get status
* @ingroup    DATAIO
*
* @return     DIOSTREAMSTATUS :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMSTATUS DIOSTREAMCIPHER::GetStatus()
{
  if(!diostream) 
    {
      return DIOSTREAMSTATUS_DISCONNECTED;
    }

  return diostream->GetStatus();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMCIPHER::Open()
* @brief      Open
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMCIPHER::Open()
{
  if(!diostream) return false;
  return diostream->Open();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMCIPHER::Disconnect()
* @brief      Disconnect
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMCIPHER::Disconnect()
{
  if(!diostream) return false;
  return diostream->Disconnect();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMCIPHER::Close()
* @brief      Close
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMCIPHER::Close()
{
  if(!diostream) return false;
  return diostream->Close();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSTREAMCIPHER::Read(XBYTE* buffer, XDWORD size)
* @brief      Read
* @ingroup    DATAIO
*
* @param[in]  buffer :
* @param[in]  size :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAMCIPHER::Read(XBYTE* buffer, XDWORD size)
{
  if(mutexread)   mutexread->Lock();

  XDWORD br = DIOSTREAM::Read(buffer, size);

  if(mutexread)   mutexread->UnLock();

  return br;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSTREAMCIPHER::Write(XBYTE* buffer, XDWORD size)
* @brief      Write
* @ingroup    DATAIO
*
* @param[in]  buffer :
* @param[in]  size :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAMCIPHER::Write(XBYTE* buffer, XDWORD size)
{
  if(mutexwrite)  mutexwrite->Lock();

  XDWORD wr = DIOSTREAM::Write(buffer, size);

  if(mutexwrite)  mutexwrite->UnLock();

  return wr;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAM* DIOSTREAMCIPHER::GetDIOStreamBase()
* @brief      Get DIO stream base
* @ingroup    DATAIO
*
* @return     DIOSTREAM* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAM* DIOSTREAMCIPHER::GetDIOStreamBase()
{
  return diostream;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         CIPHER* DIOSTREAMCIPHER::GetCipher()
* @brief      Get cipher
* @ingroup    DATAIO
*
* @return     CIPHER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
CIPHER* DIOSTREAMCIPHER::GetCipher()
{
  return cipher;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMCIPHER::ThreadRunFunction(void* param)
* @brief      Thread run function
* @ingroup    DATAIO
*
* @param[in]  param :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMCIPHER::ThreadRunFunction(void* param)
{
  DIOSTREAMCIPHER* diostreamcipher = (DIOSTREAMCIPHER*)param;
  if(!diostreamcipher) return;

  DIOSTREAM* diostream = diostreamcipher->diostream;
  if(!diostream) return;

  CIPHER* cipher   = diostreamcipher->cipher;
  if(!cipher) return;

  int br = diostream->GetInXBuffer()->GetSize();
  if(br>DIOSTREAMCIPHER_HEAD_SIZE)
    {
      if(diostreamcipher->mutexread)  diostreamcipher->mutexread->UnLock();

      XDWORD  magicnumber;
      XBYTE   ciphertype;
      XBYTE   cipherpadding;
      XDWORD  sizebuffer;
      XDWORD  CRC32[2];
      XBUFFER input;

      input.Resize(DIOSTREAMCIPHER_HEAD_SIZE);

      diostream->GetInXBuffer()->Get(input.Get(), DIOSTREAMCIPHER_HEAD_SIZE, 0);

      diostreamcipher->hashcrc32->ResetResult();
      CRC32[0] = diostreamcipher->hashcrc32->Do(input.Get(), DIOSTREAMCIPHER_HEAD_SIZE - sizeof(XDWORD));

      input.Extract(magicnumber   , 0);
      input.Extract(ciphertype    , 0);
      input.Extract(cipherpadding , 0);
      input.Extract(sizebuffer    , 0);
      input.Extract(CRC32[1]      , 0);

      if((magicnumber == DIOSTREAMCIPHER_HEAD_MAGICNUMBER) &&  (CRC32[0] == CRC32[1]))
        {
          if(diostream->GetInXBuffer()->GetSize() >= sizebuffer + DIOSTREAMCIPHER_HEAD_SIZE)
            {
              input.Empty();

              input.Resize(DIOSTREAMCIPHER_HEAD_SIZE + sizebuffer);

              diostream->GetInXBuffer()->Extract(input.Get(), 0, sizebuffer + DIOSTREAMCIPHER_HEAD_SIZE);
              input.Extract(NULL, 0, DIOSTREAMCIPHER_HEAD_SIZE);

              cipher->Uncipher(input);

              diostreamcipher->GetInXBuffer()->Add(cipher->GetResult()->Get(), cipher->GetResult()->GetSize() - cipherpadding);
            }
        }

      if(diostreamcipher->mutexread)  diostreamcipher->mutexread->UnLock();
    }


  int  bw = diostreamcipher->GetOutXBuffer()->GetSize();
  if(bw)
    {
      if(diostreamcipher->mutexwrite) diostreamcipher->mutexwrite->Lock();

      XBUFFER output;

      cipher->Cipher(diostreamcipher->GetOutXBuffer()->Get(), diostreamcipher->GetOutXBuffer()->GetSize());

      output.Add((XDWORD)DIOSTREAMCIPHER_HEAD_MAGICNUMBER);
      output.Add((XBYTE)cipher->GetType());
      output.Add((XBYTE)(cipher->GetResult()->GetSize() - bw));
      output.Add((XDWORD)cipher->GetResult()->GetSize());

      diostreamcipher->hashcrc32->ResetResult();
      output.Add((XDWORD)diostreamcipher->hashcrc32->Do(output));
      output.Add((XBYTE*)cipher->GetResult()->Get(), cipher->GetResult()->GetSize());

      if(diostream->Write(output) == output.GetSize())
        {
          //if(diostream->WaitToFlushOutXBuffer())
          diostreamcipher->GetOutXBuffer()->Extract(NULL, 0 , bw);
        }

      if(diostreamcipher->mutexwrite) diostreamcipher->mutexwrite->UnLock();
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMCIPHER::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMCIPHER::Clean()
{
  config            = NULL;
  cipher            = NULL;

  hashcrc32         = NULL;
  diostream         = NULL;

  mutexread         = NULL;
  mutexwrite        = NULL;

  xthreadconnection = NULL;
}


#pragma endregion

