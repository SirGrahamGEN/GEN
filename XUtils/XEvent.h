/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XEvent.h
* 
* @class      XEVENT
* @brief      eXtended Utils Event base class
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

#ifndef _XEVENT_H_
#define _XEVENT_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XBase.h"
#include "XVector.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#ifdef BUILDER
enum XEVENT_TYPE
#else
enum XEVENT_TYPE : XDWORD
#endif
{
  XEVENT_TYPE_NONE                              = 0x00000000 ,
  XEVENT_TYPE_USERINTERFACE                     = 0x00010000 ,
  XEVENT_TYPE_GRAPHICS                          = 0x00020000 ,
  XEVENT_TYPE_DIOSTREAM                         = 0x00030000 ,
  XEVENT_TYPE_DIOIEC60870_5                     = 0x00040000 ,
  XEVENT_TYPE_DIOMODBUSELECTRICMETER            = 0x00050000 ,
  XEVENT_TYPE_DIONODE                           = 0x00060000 ,
  XEVENT_TYPE_DIODNS                            = 0x00070000 ,
  XEVENT_TYPE_PING                              = 0x00080000 ,
  XEVENT_TYPE_WEBCLIENT                         = 0x00090000 ,
  XEVENT_TYPE_WEBSERVER                         = 0x000A0000 ,
  XEVENT_TYPE_WEBPAGEHTMLCREATOR                = 0x000B0000 ,
  XEVENT_TYPE_INTERNET                          = 0x000C0000 ,
  XEVENT_TYPE_PROTOCOL                          = 0x000D0000 ,
  XEVENT_TYPE_PROTOCOLCONNECTIONS               = 0x000E0000 ,
  XEVENT_TYPE_INPUT                             = 0x000F0000 ,
  XEVENT_TYPE_SCRIPT                            = 0x00100000 ,
  XEVENT_TYPE_SOUND                             = 0x00110000 ,
  XEVENT_TYPE_SCHEDULER                         = 0x00120000 ,
  XEVENT_TYPE_LICENSE                           = 0x00130000 ,
  XEVENT_TYPE_APPLICATIONCHECKRESOURCESHW       = 0x00140000 ,
  XEVENT_TYPE_APPLICATIONINTERNETSERVICES       = 0x00150000 ,
  XEVENT_TYPE_APPLICATIONUPDATE                 = 0x00160000 ,
  XEVENT_TYPE_APPLICATION                       = 0x00170000 ,
  XEVENT_TYPE_LOADER                            = 0x00180000 ,
  XEVENT_TYPE_DRIVEIMAGEMANAGER                 = 0x00190000 ,
  XEVENT_TYPE_FILEZIP                           = 0x001A0000 ,
  XEVENT_TYPE_FILECFG                           = 0x001B0000 ,  
  XEVENT_TYPE_BLUETOOTH                         = 0x001C0000 ,
  XEVENT_TYPE_INPUT_CAPTURE                     = 0x001D0000 , 
  XEVENT_TYPE_CAMERA                            = 0x001E0000 ,  
  XEVENT_TYPE_LINUX_DBUS                        = 0x001F0000 ,
  XEVENT_TYPE_XBER                              = 0x00200000 ,

  XEVENT_TYPE_OWNAPPLICATION                    = 0x80000000 
};

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class  XSUBJECT;

class XEVENT
{
  public:
                      XEVENT            (XSUBJECT* subject, XDWORD type, XDWORD family);
                      XEVENT            (XSUBJECT* subject, XDWORD type);

    virtual          ~XEVENT            ();

    XSUBJECT*         GetSubject        ();
    void              SetSubject        (XSUBJECT* subject);

    XDWORD            GetEventFamily    ();
    void              SetEventFamily    (XDWORD family);

    XDWORD            GetEventType      ();
    void              SetEventType      (XDWORD type);        

  protected:

    void              Clean             ();

    XDWORD            family;
    XDWORD            type;
    XSUBJECT*         subject;
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

