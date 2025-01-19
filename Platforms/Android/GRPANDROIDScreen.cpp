/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPANDROIDScreen.cpp
* 
* @class      GRPANDROIDSCREEN
* @brief      ANDROID Graphics Screen class
* @ingroup    PLATFORM_ANDROID
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

#include "GRPANDROIDScreen.h"

#include "GRPCanvas.h"

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
* @fn         GRPANDROIDSCREEN::GRPANDROIDSCREEN()
* @brief      Constructor of class
* @ingroup    PLATFORM_ANDROID
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPANDROIDSCREEN::GRPANDROIDSCREEN(): GRPSCREEN()
{
  Clean();

  type = GRPSCREENTYPE_ANDROID;

  SetMode(GRPPROPERTYMODE_32_RGBA_8888);

  SetIsBufferInverse(true);

  SetStyle(GRPSCREENSTYLE_FULLSCREEN);

  isvalid = true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPANDROIDSCREEN::~GRPANDROIDSCREEN()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_ANDROID
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPANDROIDSCREEN::~GRPANDROIDSCREEN()
{
  Delete();
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPANDROIDSCREEN::Create(bool show)
* @brief      Create
* @ingroup    PLATFORM_ANDROID
*
* @param[in]  show :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPANDROIDSCREEN::Create(bool show)
{
  CreateBuffers();

  return GRPSCREEN::Create(show);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPANDROIDSCREEN::Update()
* @brief      Update
* @ingroup    PLATFORM_ANDROID
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPANDROIDSCREEN::Update()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPANDROIDSCREEN::Update(GRPCANVAS* canvas)
* @brief      Update
* @ingroup    PLATFORM_ANDROID
*
* @param[in]  canvas :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPANDROIDSCREEN::Update(GRPCANVAS* canvas)
{
  if(!canvas)        return false;
  if(!anativehandle) return false;

  ANativeWindow_Buffer abuffer;

  if(IsEqualSizeTo(canvas) == ISEQUAL)
    {
      if(ANativeWindow_lock(anativehandle, &abuffer, NULL) >= 0)
        {
          memcpy(abuffer.bits, canvas->GetBuffer(), height * width * GetBytesperPixel());
          ANativeWindow_unlockAndPost(anativehandle);
        }
    }
   else
    {
      canvas->CopyBufferRenderToScreen(this);

      if(ANativeWindow_lock(anativehandle, &abuffer, NULL) >= 0)
        {
          memcpy((XBYTE*)abuffer.bits, buffer, height * width * GetBytesperPixel());

          ANativeWindow_unlockAndPost(anativehandle);
        }

      /*
      if(ANativeWindow_lock(anativehandle, &abuffer, NULL) >= 0)
        {
          canvas->CopyBufferRenderToBufferScreen((XBYTE*)abuffer.bits, width, height, isbufferinverse);

          ANativeWindow_unlockAndPost(anativehandle);
        }
      */
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPANDROIDSCREEN::Delete()
* @brief      Delete
* @ingroup    PLATFORM_ANDROID
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPANDROIDSCREEN::Delete()
{
  DeleteBuffers();

  isactive = false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPANDROIDSCREEN::Resize(int width, int height)
* @brief      Resize
* @ingroup    PLATFORM_ANDROID
*
* @param[in]  width :
* @param[in]  height :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPANDROIDSCREEN::Resize(int width, int height)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* GRPANDROIDSCREEN::GetHandle()
* @brief      Get handle
* @ingroup    PLATFORM_ANDROID
*
* @return     void* :
*
* --------------------------------------------------------------------------------------------------------------------*/
void* GRPANDROIDSCREEN::GetHandle()
{
  return (void*)anativehandle;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         ANativeWindow* GRPANDROIDSCREEN::GetAndroidHandle()
* @brief      Get android handle
* @ingroup    PLATFORM_ANDROID
*
* @return     ANativeWindow* :
*
* --------------------------------------------------------------------------------------------------------------------*/
ANativeWindow* GRPANDROIDSCREEN::GetAndroidHandle()
{
  return anativehandle;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPANDROIDSCREEN::SetAndroidHandle(ANativeWindow* anativehandle)
* @brief      Set android handle
* @ingroup    PLATFORM_ANDROID
*
* @param[in]  anativehandle :
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPANDROIDSCREEN::SetAndroidHandle(ANativeWindow* anativehandle)
{
  this->anativehandle = anativehandle;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPANDROIDSCREEN::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_ANDROID
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPANDROIDSCREEN::Clean()
{
  anativehandle  = NULL;
}


#pragma endregion

