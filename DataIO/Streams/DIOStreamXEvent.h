/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOStreamXEvent.h
* 
* @class      DIOSTREAMXEVENT
* @brief      Data Input/Output eXtended Event class
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

#ifndef _DIOSTREAMXEVENT_H_
#define _DIOSTREAMXEVENT_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES


#include "XEvent.h"

#include "DIOStreamDevice.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

enum DIOSTREAMXEVENT_TYPE
{
  DIOSTREAMXEVENT_TYPE_UNKNOWN             = XEVENT_TYPE_DIOSTREAM  ,
  DIOSTREAMXEVENT_TYPE_GETTINGCONNECTION                            ,
  DIOSTREAMXEVENT_TYPE_CONNECTED                                   ,
  DIOSTREAMXEVENT_TYPE_DISCONNECTED                                ,
  DIOSTREAMXEVENT_TYPE_EXCEPTIONDEVICE                             ,
  DIOSTREAMXEVENT_TYPE_COOPERATIONDEVICE                           ,
};

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class DIOSTREAM;


class DIOSTREAMXEVENT : public XEVENT
{
  public:
                                DIOSTREAMXEVENT                 (XSUBJECT* subject, XDWORD type = DIOSTREAMXEVENT_TYPE_UNKNOWN, XDWORD family = XEVENT_TYPE_DIOSTREAM) : XEVENT(subject, type, family)
                                {
                                  Clean();
                                }

    virtual                    ~DIOSTREAMXEVENT                 ()                                                                                          { Clean();                          }

    DIOSTREAM*                  GetDIOStream                    ()                                                                                          { return diostream;                 }
    void                        SetDIOStream                    (DIOSTREAM* diostream)                                                                      { this->diostream = diostream;      }

    DIOSTREAMDEVICE*            GetDevice                       ()                                                                                          { return &device;                   }
    void                        SetDevice                       (DIOSTREAMDEVICE& device)                                                                   {                                   }

  private:

    void                        Clean                           ()
                                {
                                  diostream = NULL;
                                }

    DIOSTREAM*                  diostream;
    DIOSTREAMDEVICE             device;
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

