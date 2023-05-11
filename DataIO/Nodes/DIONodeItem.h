/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeItem.h
* 
* @class      DIONODEITEM
* @brief      Data Input/Output Node item (Base for DIONODESENSOR, DIONODEACTUATOR, ...)
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

#ifndef _DIONODEITEM_H_
#define _DIONODEITEM_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XUUID.h"
#include "XSerializable.h"

#include "DIONodeItemValue.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum DIONODEITEM_TYPE
{
  DIONODEITEM_TYPE_UNKNOWN                            = 0 ,  
  DIONODEITEM_TYPE_SENSORHUMIDITYTEMPERATURE              ,
  DIONODEITEM_TYPE_GPIO                                   ,  

  DIONODEITEM_TYPE_OWER
};


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIONODEITEMHANDLER;

class DIONODEITEM : public XSERIALIZABLE
{
  public:
                                  DIONODEITEM                   ();
                                  DIONODEITEM                   (DIONODEITEMHANDLER* itemhandler);
    virtual                      ~DIONODEITEM                   ();

    XDWORD                        GetType                       ();     
    void                          SetType                       (XDWORD type);     

    XSTRING*                      GetDescription                (); 
    
    XUUID&                        GetID                         ();
    void                          SetID                         (XUUID& UUID);

    DIONODEITEMHANDLER*           ItemHandler_Get               ();
    bool                          ItemHandler_Set               (DIONODEITEMHANDLER* itemhandler);
    bool                          ItemHandler_Open              ();
    bool                          ItemHandler_Close             ();

    bool                          IsSimulated                   ();
    void                          SetIsSimulated                (bool issimulated);

    XQWORD                        GetTimeToUpdate               ();
    void                          SetTimeToUpdate               (XQWORD timetoupdate);
    
    XTIMER*                       GetUpdateTimer                ();

    XVECTOR<DIONODEITEMVALUE*>*   GetValues                     ();

    virtual bool                  Update                        ();

    virtual bool                  Serialize                     ();                                          
    virtual bool                  Deserialize                   ();

  protected:

    XDWORD                        type;
    XSTRING                       description;
    XUUID                         UUID;
    DIONODEITEMHANDLER*           itemhandler;    
    bool                          issimulated;
    XQWORD                        timetoupdate;
    XVECTOR<DIONODEITEMVALUE*>    values;
    XTIMER*                       updatetimer;

  private:
   
    void                          Clean                         ();   
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif

