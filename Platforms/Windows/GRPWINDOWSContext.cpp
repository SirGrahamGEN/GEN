
/*------------------------------------------------------------------------------------------
//  GRPWINDOWSCONTEXT.CPP
//
//  Windows Graphics Context
//
//  Author            : Imanol Celaya Ruiz de Alegria
//  Date Of Creation  : 04/04/2016 17:13:57
//  Last Modification :
//
//  GEN  Copyright (C).  All right reserved.
//----------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES --------------------------------------------------------------------------*/

#include "GRPWINDOWSContext.h"
#include "GRPWINDOWSScreen.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ------------------------------------------------------------------*/


/*---- CLASS MEMBERS ---------------------------------------------------------------------*/


/*-------------------------------------------------------------------
//  GRPWINDOWSCONTEXT::GRPWINDOWSCONTEXT
*/
/**
//
//  Class Constructor GRPWINDOWSCONTEXT
//
//  ""
//  @version      02/05/2016 6:52:43
//
*/
/*-----------------------------------------------------------------*/
GRPWINDOWSCONTEXT::GRPWINDOWSCONTEXT() : GRPCONTEXT()
{
  Clean();
}



/*-------------------------------------------------------------------
//  GRPWINDOWSCONTEXT::~GRPWINDOWSCONTEXT
*/
/**
//
//   Class Destructor GRPWINDOWSCONTEXT
//
//  ""
//  @version      02/05/2016 6:53:09
//
*/
/*-----------------------------------------------------------------*/
GRPWINDOWSCONTEXT::~GRPWINDOWSCONTEXT()
{
  Clean();
}



/*-------------------------------------------------------------------
//  GRPWINDOWSCONTEXT::Create
*/
/**
//
//
//
//  ""
//  @version      02/05/2016 6:53:14
//
//  @return       bool :
//
//  @param        handle :
*/
/*-----------------------------------------------------------------*/
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



/*-------------------------------------------------------------------
//  GRPWINDOWSCONTEXT::IsLost
*/
/**
//
//
//
//  ""
//  @version      02/05/2016 6:53:27
//
//  @return       bool :
//
*/
/*-----------------------------------------------------------------*/
bool GRPWINDOWSCONTEXT::IsLost()
{
  #ifdef GRP_OPENGL_ACTIVE

  return wglGetCurrentContext() == NULL;

  #else

  return false;

  #endif
}



/*-------------------------------------------------------------------
//  GRPWINDOWSCONTEXT::Destroy
*/
/**
//
//
//
//  ""
//  @version      02/05/2016 6:53:21
//
//  @return       bool :
//
*/
/*-----------------------------------------------------------------*/
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
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPWINDOWSCONTEXT::Clean()
{
  #ifdef GRP_OPENGL_ACTIVE

  #endif
}