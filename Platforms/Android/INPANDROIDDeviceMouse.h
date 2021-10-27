/**-------------------------------------------------------------------------------------------------------------------
*
* @file       INPANDROIDDeviceMouse.h
*
* @class      INPANDROIDDEVICEMOUSE
* @brief      ANDROID input device mouse class
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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

#ifndef _INPANDROIDDEVICEMOUSE_H_
#define _INPANDROIDDEVICEMOUSE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "INPCursor.h"
#include "INPDevice.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class GRPANDROIDSCREEN;

class INPANDROIDDEVICEMOUSE : public INPDEVICE
{
  public:
                                INPANDROIDDEVICEMOUSE         (GRPANDROIDSCREEN* grpscreen = NULL);
    virtual                    ~INPANDROIDDEVICEMOUSE         ();

    virtual bool                SetScreen                     (void* screenpointer);

    bool                        Update                        ();

    bool                        AddPosition                   (int index, float x, float y, bool ispressed);

  private:

    void                        Clean                         ();

    bool                        CreateAllButtons              ();
    bool                        CreateAllCursors              ();

    GRPANDROIDSCREEN*           grpscreen;
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif



