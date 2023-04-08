/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeActuator.h
* 
* @class      DIONODEACTUATOR
* @brief      Data Input/Output Node Actuator
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

#ifndef _DIONODEACTUATOR_H_
#define _DIONODEACTUATOR_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIONodeItem.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum DIONODEACTUATOR_TYPE
{
  DIONODEITEM_TYPE_ACTUATOR_UNKNOWN           = 0 ,
  DIONODEITEM_TYPE_ACTUATOR_GPIO                  ,
  DIONODEITEM_TYPE_ACTUATOR_LIGHT                 ,
  DIONODEITEM_TYPE_ACTUATOR_ENGINE                ,
};


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIONODEACTUATOR :  public DIONODEITEM
{
  public:
                              DIONODEACTUATOR               ();
    virtual                  ~DIONODEACTUATOR               ();

    DIONODEACTUATOR_TYPE      GetActuatorType               ();
    void                      SetActuatorType               (DIONODEACTUATOR_TYPE type); 

    bool                      GetActuatorTypeDescription    (XSTRING& typedescription);

    virtual bool              Serialize                     ();                                          
    virtual bool              Deserialize                   ();  

  protected:

    DIONODEACTUATOR_TYPE      actuatortype;
 
  private:

    void                      Clean                         ();   
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif

