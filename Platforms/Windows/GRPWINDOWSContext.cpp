/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPWINDOWSContext.cpp
* 
* @class      GRPWINDOWSCONTEXT
* @brief      WINDOWS Graphics context class
* @ingroup    PLATFORM_WINDOWS
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

#include "GRPWINDOWSContext.h"

#include "GRPWINDOWSScreen.h"

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
* @fn         GRPWINDOWSCONTEXT::GRPWINDOWSCONTEXT()
* @brief      Constructor of class
* @ingroup    PLATFORM_WINDOWS
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPWINDOWSCONTEXT::GRPWINDOWSCONTEXT() : GRPCONTEXT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPWINDOWSCONTEXT::~GRPWINDOWSCONTEXT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPWINDOWSCONTEXT::~GRPWINDOWSCONTEXT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPWINDOWSCONTEXT::Create(void* handle)
* @brief      Create
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  handle : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSCONTEXT::Create(void* handle)
{
  // deal with weird windows context creation


  #ifdef GRP_OPENGL_ACTIVE

  GRPWINDOWSSCREEN* windowsscreen = (GRPWINDOWSSCREEN*)this->screen;
  if(!windowsscreen) return false;

  // Choose the corect pixel format
  windowsscreen->ChooseValidPixelFormat();
  // make dummy opengl context

  hdlopenglrc = wglCreateContext(windowsscreen->GetHDC());
  wglMakeCurrent(windowscreen->GetHDC(), hdlopenglrc);

  glewExperimental = true;
  if(glewInit() != GLEW_OK) return false;

  // Set the pixel format usiong wgl extensions
  int   nPixelFormat;
  BOOL  bValidPixFormat;
  UINT  nMaxFormats     = 1;
  UINT  nNumFormats;
  float pfAttribFList[] = { 0, 0 };
  int   piAttribIList[] = { WGL_DRAW_TO_WINDOW_ARB,   GL_TRUE,
                            WGL_SUPPORT_OPENGL_ARB,   GL_TRUE,
                            WGL_ACCELERATION_ARB,     WGL_FULL_ACCELERATION_ARB,
                            WGL_COLOR_BITS_ARB,       32,
                            WGL_ALPHA_BITS_ARB,       8,
                            WGL_DEPTH_BITS_ARB,       16,
                            WGL_STENCIL_BITS_ARB,     8,
                            WGL_DOUBLE_BUFFER_ARB,    GL_TRUE,
                            WGL_PIXEL_TYPE_ARB,       WGL_TYPE_RGBA_ARB,
                            WGL_SAMPLE_BUFFERS_ARB,   (multisampling != 0) ? 1 : 0, //Number of mutisample buffers (must be 1 at time of writing)
                            WGL_SAMPLES_ARB,          (int)multisampling,               //Number of samples
                            0, 0 };

  bValidPixFormat = wglChoosePixelFormatARB(windowsscreen->GetHDC(), piAttribIList, pfAttribFList, nMaxFormats, &nPixelFormat, &nNumFormats );
  if(!bValidPixFormat)
    {
      XTRACE_PRINTCOLOR(4,__L("Invalid Pixel Format! Try back..."));

      const int attribList[] ={ WGL_DRAW_TO_WINDOW_ARB  , GL_TRUE           ,
                                WGL_SUPPORT_OPENGL_ARB  , GL_TRUE           ,
                                WGL_DOUBLE_BUFFER_ARB   , GL_TRUE           ,
                                WGL_PIXEL_TYPE_ARB      , WGL_TYPE_RGBA_ARB ,
                                WGL_COLOR_BITS_ARB      , 32                ,
                                WGL_DEPTH_BITS_ARB      , 24                ,
                                WGL_STENCIL_BITS_ARB    ,  8                ,
                                0,        //End
                              };

      bValidPixFormat = wglChoosePixelFormatARB(windowsscreen->GetHDC(), attribList, pfAttribFList, nMaxFormats, &nPixelFormat, &nNumFormats );
      if(!bValidPixFormat)
        {
          XTRACE_PRINTCOLOR(4,__L("\n\n\n\nInvalid Pixel Format!"));
          return false;
        }
    }

  windowsscreen->SetPixelFormat(nPixelFormat);

  // delete old window
  windowsscreen->Delete();

  // make real window
  windowsscreen->Create(handle);

  // delete old context
  Destroy();

  // make real context
  hdlopenglrc = wglCreateContext(windowsscreen->GetHDC());
  wglMakeCurrent(windowsscreen->GetHDC(), hdlopenglrc);

  openglctrl.Ini();

  return true;

  #else

  return false;

  #endif
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPWINDOWSCONTEXT::IsLost()
* @brief      Is lost
* @ingroup    PLATFORM_WINDOWS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSCONTEXT::IsLost()
{
  #ifdef GRP_OPENGL_ACTIVE

  return wglGetCurrentContext() == NULL;

  #else

  return false;

  #endif
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPWINDOWSCONTEXT::Destroy()
* @brief      Destroy
* @ingroup    PLATFORM_WINDOWS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSCONTEXT::Destroy()
{
  #ifdef GRP_OPENGL_ACTIVE

  wglDeleteContext(hdlopenglrc);

  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPWINDOWSCONTEXT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPWINDOWSCONTEXT::Clean()
{
  #ifdef GRP_OPENGL_ACTIVE

  #endif
}


#pragma endregion

