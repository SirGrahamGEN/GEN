/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeElement.h
* 
* @class      DIONODEELEMENT
* @brief      Data Input/Output Node element (Base for DIONODESENSOR, DIONODEACTUATOR, ...)
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

#ifndef _DIONODEELEMENT_H_
#define _DIONODEELEMENT_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XUUID.h"
#include "XSerializable.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum DIONODEELEMENT_TYPE
{
  DIONODEELEMENT_TYPE_UNKNOWN           = 0 ,
  DIONODEELEMENT_TYPE_SENSOR                ,
  DIONODEELEMENT_TYPE_ACTUATOR              ,  
};


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIONODEDEVICEDRIVER;

class DIONODEELEMENT : public XSERIALIZABLE
{
  public:
                              DIONODEELEMENT                ();
    virtual                  ~DIONODEELEMENT                ();

    DIONODEELEMENT_TYPE       GetElementType                (); 
    void                      SetElementType                (DIONODEELEMENT_TYPE type);     

    bool                      GetElementTypeDescription     (XSTRING& typedescription);

    XUUID&                    GetID                         ();
    void                      SetID                         (XUUID& UUID);

    DIONODEDEVICEDRIVER*      DeviceDriver_Get              ();
    bool                      DeviceDriver_Set              (DIONODEDEVICEDRIVER* devicedriver);
    bool                      DeviceDriver_Open             ();
    bool                      DeviceDriver_Close            ();

    virtual bool              Serialize                     ();                                          
    virtual bool              Deserialize                   ();

  protected:

    DIONODEELEMENT_TYPE       elementtype;
    XUUID                     UUID;
    DIONODEDEVICEDRIVER*      devicedriver;

  private:

    void                      Clean                  ();   
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif

