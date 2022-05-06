/**-------------------------------------------------------------------------------------------------------------------
*
* @file       GRPLINUXScreenFrameBuffer.cpp
*
* @class      GRPLINUXSCREENFRAMEBUFFER
* @brief      LINUX Frame Buffer Screen class
* @ingroup    PLATFORM_LINUX
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
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <linux/kd.h>
#include <errno.h>

#include "XTrace.h"

#include "GRPCanvas.h"
#include "GRPLINUXScreenFrameBuffer.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPLINUXSCREENFRAMEBUFFER::GRPLINUXSCREENFRAMEBUFFER()
* @brief      Constructor
* @ingroup    PLATFORM_LINUX
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPLINUXSCREENFRAMEBUFFER::GRPLINUXSCREENFRAMEBUFFER(): GRPSCREEN()
{
  Clean();

  type = GRPSCREENTYPE_LINUX_FRAMEBUFFER;

  struct fb_var_screeninfo varinfo;
  struct fb_fix_screeninfo fixinfo;

  handlefb = open(GRPLINUXSCREENFRAMEBUFFER_DEVICE, O_RDWR);
  if(handlefb !=-1)
    {
      if(ioctl(handlefb, FBIOGET_VSCREENINFO, &varinfo) != -1)
        {
          SetWidth(varinfo.xres);
          SetHeight(varinfo.yres);

          SetSize(varinfo.xres, varinfo.yres);
          SetMaxSize(varinfo.xres, varinfo.yres);

          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Frame Buffer] Screen [%d x %d]  %d bits"), varinfo.xres, varinfo.yres, varinfo.bits_per_pixel);

          switch(varinfo.bits_per_pixel)
            {
              case   8 : SetMode(GRPPROPERTYMODE_08_INDEX);     break;
              case  16 : SetMode(GRPPROPERTYMODE_16_RGB_565);   break;
              case  24 : SetMode(GRPPROPERTYMODE_24_BGR_888);   break;
              case  32 : SetMode(GRPPROPERTYMODE_32_BGRA_8888); break;
            }

          SetIsBufferInverse(true);

        }
    }

  if(handlefb!=-1)  close(handlefb);

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPLINUXSCREENFRAMEBUFFER::~GRPLINUXSCREENFRAMEBUFFER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPLINUXSCREENFRAMEBUFFER::~GRPLINUXSCREENFRAMEBUFFER()
{
  Delete();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPLINUXSCREENFRAMEBUFFER::Create(bool show)
* @brief      Create
* @ingroup    PLATFORM_LINUX
*
* @param[in]  show :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENFRAMEBUFFER::Create(bool show)
{
  Clean();

  handlefb = open(GRPLINUXSCREENFRAMEBUFFER_DEVICE, O_RDWR);
  if(handlefb!=-1)
    {
      int consoletty = open("/dev/tty1", O_RDWR);
      if(ioctl(consoletty, KDSETMODE, KD_GRAPHICS) != -1)
        {
          if(!ScreenResolution(width, height))
            {
              XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("ERROR! Change screen mode: error[%d]"), errno);
            }

          CreateBuffers();

          //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("X: %d, Y: %d  mode: %d"), width, height, GetMode());

          int zero = 0;
          if(ioctl(handlefb, FBIO_WAITFORVSYNC, &zero) == -1) 
            {
              XSTRING errorstr;
              
              errorstr = strerror(errno);
              XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("Frame Buffer VSYNC: %s"), errorstr.Get());
            }

          return GRPSCREEN::Create(show);
        }
    }

  XTRACE_PRINTCOLOR(4, __L("ERROR! open device screen: %d"), errno);

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPLINUXSCREENFRAMEBUFFER::Update()
* @brief      Update
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENFRAMEBUFFER::Update()
{

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPLINUXSCREENFRAMEBUFFER::Update(GRPCANVAS* canvas)
* @brief      Update
* @ingroup    PLATFORM_LINUX
*
* @param[in]  canvas :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENFRAMEBUFFER::Update(GRPCANVAS* canvas)
{
  if(handlefb == -1) return false;
  if(!buffersize)    return false;


  if(ioctl(handlefb, FBIO_WAITFORVSYNC, 0)) 
    {
      //printf("VSync failed.\n");
    }

  XBYTE* fbp = (XBYTE*)mmap(0, buffersize, PROT_READ | PROT_WRITE, MAP_SHARED, handlefb, 0);
  if(fbp == (XBYTE*)-1)  return false;

  if(IsEqualSizeTo(canvas) == ISEQUAL)
    {
      memcpy(fbp, (XBYTE*)canvas->GetBuffer(), buffersize);
    }
   else
    {
      //canvas->CopyBufferRenderToScreen(this);
      //memcpy(fbp,(XBYTE*)buffer, buffersize);

      canvas->CopyBufferRenderToBufferScreen((XBYTE*)(fbp), width, height, isbufferinverse);
    }

  munmap((XBYTE*)fbp, buffersize);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPLINUXSCREENFRAMEBUFFER::Delete()
* @brief      Delete
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENFRAMEBUFFER::Delete()
{
  ClearScreen();

  DeleteBuffers();

  int consoletty = open("/dev/tty1", O_RDWR);
  ioctl(consoletty, KDSETMODE, KD_TEXT);

  if(handlefb!=-1)  close(handlefb);

  isactive = false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPLINUXSCREENFRAMEBUFFER::Resize(int width, int height)
* @brief      Resize
* @ingroup    PLATFORM_LINUX
*
* @param[in]  width : new width
* @param[in]  height : new height
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENFRAMEBUFFER::Resize(int width, int height)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPLINUXSCREENFRAMEBUFFER::Show(bool active)
* @brief      Show
* @ingroup    PLATFORM_LINUX
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENFRAMEBUFFER::Show(bool active)
{
  isshow  = active;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPLINUXSCREENFRAMEBUFFER::ShowCursor(bool active)
* @brief      ShowCursor
* @ingroup    PLATFORM_LINUX
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENFRAMEBUFFER::ShowCursor(bool active)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* GRPLINUXSCREENFRAMEBUFFER::GetHandle()
* @brief      GetHandle
* @ingroup    PLATFORM_LINUX
*
* @return     void* :
*
* --------------------------------------------------------------------------------------------------------------------*/
void* GRPLINUXSCREENFRAMEBUFFER::GetHandle()
{
  void* ptr = 0;

  memcpy((XBYTE*)&ptr, (XBYTE*)&handlefb, sizeof(int));

  return ptr;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int GRPLINUXSCREENFRAMEBUFFER::GetHandleFB()
* @brief      GetHandleFB
* @ingroup    PLATFORM_LINUX
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int GRPLINUXSCREENFRAMEBUFFER::GetHandleFB()
{
  return handlefb;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPLINUXSCREENFRAMEBUFFER::ScreenResolution(int width, int height)
* @brief      ScreenResolution
* @ingroup    PLATFORM_LINUX
*
* @param[in]  width :
* @param[in]  height :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENFRAMEBUFFER::ScreenResolution(int width, int height)
{
  if(handlefb == -1) return false;

  struct fb_fix_screeninfo fixed_info;
  struct fb_var_screeninfo variable_info;
  int                      screen_width;
  int                      screen_height;

  if(ioctl(handlefb, FBIOGET_VSCREENINFO, &variable_info) == -1)
    {
      return false;
    }

  screen_width               = variable_info.xres;
  screen_height              = variable_info.yres;

  variable_info.xres         = width;
  variable_info.yres         = height;

  variable_info.xres_virtual = variable_info.xres;
  variable_info.yres_virtual = variable_info.yres;

  if(ioctl(handlefb, FBIOPUT_VSCREENINFO, &variable_info) == -1)
    {
      ioctl(handlefb, FBIOGET_VSCREENINFO, &variable_info);

      SetWidth(screen_width);
      SetHeight(screen_height);

      return false;
    }

  if(ioctl(handlefb, FBIOGET_FSCREENINFO, &fixed_info) == -1)
    {
      return false;
    }


  /*
  variable_info.xres = width;
  variable_info.yres = height;

  if(ioctl(handlefb, FBIOPAN_DISPLAY    , &variable_info) == -1)
    {
      XTRACE_PRINTCOLOR(4, __L("ERROR! 4"));
      return false;
    }
  */

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPLINUXSCREENFRAMEBUFFER::ClearScreen()
* @brief      Clear Screen to black
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENFRAMEBUFFER::ClearScreen()
{
  if(handlefb == -1) return false;
  if(!buffersize)    return false;

  XBYTE* fbp = (XBYTE *)mmap(0, buffersize, PROT_READ | PROT_WRITE, MAP_SHARED, handlefb, 0);
  if(fbp == (XBYTE*)-1)  return false;


  memset(fbp, 0, buffersize);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPLINUXSCREENFRAMEBUFFER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPLINUXSCREENFRAMEBUFFER::Clean()
{
  handlefb  = -1;
}


