/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       INPLINUXFactory.cpp
* 
* @class      INPLINUXFACTORY
* @brief      INPUT LINUX factory
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "INPLINUXFactory.h"

#include "XFileTXT.h"
#include "XTrace.h"

#include "GRPScreen.h"

#include "INPLINUXDeviceID.h"
#include "INPLINUXDeviceKeyboardDirect.h"
#include "INPLINUXDeviceMouseDirect.h"
#include "INPLINUXDeviceTouchScreenDirect.h"

#ifdef LINUX_X11_ACTIVE
#include "INPLINUXDeviceKeyboardX11.h"
#include "INPLINUXDeviceMouseX11.h"
#endif

#include "INPLINUXSimulate.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE


#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPDEVICE* INPLINUXFACTORY::CreateDevice(XCHAR* devicename, void* param)
* @brief      CreateDevice
* @ingroup    PLATFORM_LINUX
*
* @param[in]  type : device type of the input device
* @param[in]  param : param to create device (in windows need handle to windows)
*
* @return     INPDEVICE* : device input created
*
* --------------------------------------------------------------------------------------------------------------------*/
INPDEVICE* INPLINUXFACTORY::CreateDevice(INPDEVICE_TYPE type, void* param)
{
  INPDEVICE* inpdevice    = NULL;
  GRPSCREEN* grpscreen    = (GRPSCREEN*)param;
  bool       isX11        = false;

  if(grpscreen)
    {
      if(grpscreen->GetType() == GRPSCREENTYPE_LINUX_X11) isX11 = true;
    }


  

  #ifdef LINUX_X11_ACTIVE

  if(isX11)
    {
      switch(type)
        {
          case INPDEVICE_TYPE_KEYBOARD    : { INPLINUXDEVICEKEYBOARDX11* keyboard = new INPLINUXDEVICEKEYBOARDX11();
                                              if(keyboard)
                                                {
                                                  keyboard->SetScreen(param);
                                                  inpdevice = keyboard;
                                                }
                                            }
                                            break;

          case INPDEVICE_TYPE_MOUSE       : { INPLINUXDEVICEMOUSEX11* mouse= new INPLINUXDEVICEMOUSEX11();
                                              if(mouse)
                                                {
                                                  mouse->SetScreen(param);
                                                  inpdevice = mouse;
                                                }
                                            }
                                            break;
        }
    }

  #else

  if(!isX11)
    {
      switch(type)
        {
          case INPDEVICE_TYPE_KEYBOARD    : { INPLINUXDEVICEKEYBOARDDIRECT* keyboard = new INPLINUXDEVICEKEYBOARDDIRECT();
                                              if(keyboard)
                                                {
                                                  keyboard->SetScreen(param);
                                                  inpdevice = keyboard;
                                                }
                                             }
                                            break;

          case INPDEVICE_TYPE_MOUSE       : { INPLINUXDEVICEMOUSEDIRECT* mouse = new INPLINUXDEVICEMOUSEDIRECT();
                                              if(mouse)
                                                {
                                                  mouse->SetScreen(param);
                                                  inpdevice = mouse;
                                                }
                                            }
                                            break;

          case INPDEVICE_TYPE_TOUCHSCREEN : { INPLINUXDEVICETOUCHSCREENDIRECT* touchscreen = new INPLINUXDEVICETOUCHSCREENDIRECT();
                                              if(touchscreen)
                                                {
                                                  touchscreen->SetScreen(param);
                                                  inpdevice = touchscreen;
                                                }
                                            }
                                            break;
        }
    }

  #endif

  return inpdevice;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPLINUXFACTORY::DeleteDevice(INPDEVICE* device)
* @brief      Delete Device
* @ingroup    PLATFORM_LINUX
*
* @param[in]  device : device to delete
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool INPLINUXFACTORY::DeleteDevice(INPDEVICE* device)
{
  if(!device)  return false;

  delete device;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPLINUXFACTORY::GetDeviceHandlers(INPDEVICE_TYPE devicetype, XSTRING& handlers)
* @brief      GetDeviceHandlers
* @ingroup    PLATFORM_LINUX
*
* @param[in]  devicetype : 
* @param[in]  handlers : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool INPLINUXFACTORY::GetDeviceHandlers(INPDEVICE_TYPE devicetype, XVECTOR<INPLINUXDEVICEID*>& devices)
{
  bool status = false;
  
  XFILETXT* xfiletxtdevices =  new XFILETXT();
  if(xfiletxtdevices)
    {
      XPATH xpathdevices;
      
      xpathdevices = INPLINUXDEVICEID_HANDLEFILE;
      
      if(xfiletxtdevices->Open(xpathdevices))
        {
          status = xfiletxtdevices->ReadAllFile();

          for(int c=0; c<xfiletxtdevices->GetNLines(); c++)
            {
              XSTRING* line = xfiletxtdevices->GetLine(c);
              if(line)
                {
                  int index = line->Find(__L("I:"), true);
                  if(index == 0)
                    {
                      INPLINUXDEVICEID* deviceID = new INPLINUXDEVICEID();
                      if(deviceID)
                        {
                          do{ line = xfiletxtdevices->GetLine(c);
                              if(!line) break;
                              if(line->GetSize() < 2) break;  

                              char typeline = (char)line->Get()[0];  
                              switch(typeline)
                                {    
                                  case  'I' : break;                                    

                                  case  'N' : { XSTRING name;

                                                name.AdjustSize(_MAXSTR);
                                                line->UnFormat(__L("N: Name=\"%s\""), name.Get());
                                                name.AdjustSize();      

                                                deviceID->GetName()->Set(name);
                                              }
                                              break;                                    

                                  case  'P' : break;                                    
                                  case  'S' : break;                                    
                                  case  'U' : break;                                    

                                  case  'H' : { XSTRING handlers;
                                                int     event_index = INPLINUXDEVICEID_INVALID;

                                                handlers.AdjustSize(_MAXSTR);
                                                line->UnFormat(__L("H: Handlers=%s"), handlers.Get());
                                                handlers.AdjustSize();      

                                                index = handlers.Find(__L("event"), true);
                                                if(index != XSTRING_NOTFOUND)
                                                  {
                                                    XSTRING eventstr;

                                                    handlers.Copy(index, eventstr);
                                                    eventstr.UnFormat(__L("event%d"), &event_index);

                                                    deviceID->SetEventIndex(event_index);
                                                  }                                                
                                              }
                                              break;        
                           
                                  case  'B' : { XCHAR* prefix[] = { __L("PROP=")  , 
                                                                    __L("EV=")    ,
                                                                    __L("KEY=")   ,
                                                                    __L("ABS=")   ,
                                                                    __L("REL=")   ,
                                                                    __L("MSC=")   
                                                                  };

                                                for(int d=0; d< (sizeof(prefix) / sizeof(XCHAR*)); d++)   
                                                  {
                                                    index = line->Find(prefix[d], true);
                                                    if(index != XSTRING_NOTFOUND)
                                                      {
                                                        switch(d)
                                                          {
                                                            case 0  : break;

                                                            case 1  : { XSTRING ev_str;

                                                                        ev_str.AdjustSize(_MAXSTR);
                                                                        line->Copy(index+3, ev_str);
                                                                        ev_str.AdjustSize();

                                                                        if(!ev_str.Compare(__L("120013"), true)) deviceID->SetType(INPDEVICE_TYPE_KEYBOARD);  
                                                                        if(!ev_str.Compare(__L("17"), true))     deviceID->SetType(INPDEVICE_TYPE_MOUSE);                                                                                                                        
                                                                        if(!ev_str.Compare(__L("b"), true))      deviceID->SetType(INPDEVICE_TYPE_TOUCHSCREEN);                                                                                                                        
                                                                      }
                                                                      break;

                                                            case 2  : break;
                                                            case 3  : break;
                                                            case 4  : break;
                                                            case 5  : break;
                                                          }
                                                      }
                                                  }  
                                              }
                                              break;                                                                      
                                }

                              c++;


                            } while(1);
 
                                
                          if((deviceID->GetEventIndex() != INPLINUXDEVICEID_INVALID) && (devicetype == deviceID->GetType()))
                            {            
                              devices.Add(deviceID);
               
                              #ifdef XTRACE_ACTIVE
                              XSTRING typestr;
   
                              switch(deviceID->GetType())
                                { 
                                                      default       :   
                                  case INPDEVICE_TYPE_NONE          : typestr = __L("Unkwown");       break;
                                  case INPDEVICE_TYPE_KEYBOARD      : typestr = __L("Keyboard");      break;
                                  case INPDEVICE_TYPE_MOUSE         : typestr = __L("Mouse");         break;
                                  case INPDEVICE_TYPE_JOSTICK       : typestr = __L("Jostick");       break;
                                  case INPDEVICE_TYPE_TOUCHSCREEN   : typestr = __L("TouchScreen");   break;
                                  case INPDEVICE_TYPE_WIIMOTE       : typestr = __L("WII Mote");      break;
                                }

                              XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Input Device] Event [%d] Type: %15s Device [%s]"), deviceID->GetEventIndex(), typestr.Get(), deviceID->GetName()->Get());                         
                              #endif                                               
                            } 
                           else delete deviceID;                                 
                        }   
                    }
                }
            }

          xfiletxtdevices->Close();
        }

      delete xfiletxtdevices;
    }

  return status;
}


#ifdef INP_SIMULATE_ACTIVE
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPSIMULATE* INPLINUXFACTORY::CreateSimulator()
* @brief      CreateSimulator
* @ingroup    PLATFORM_LINUX
* 
* @return     INPSIMULATE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPSIMULATE* INPLINUXFACTORY::CreateSimulator()
{
  INPSIMULATE* inpsimulated = (INPSIMULATE*)new INPLINUXSIMULATE();

  return inpsimulated;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPLINUXFACTORY::DeleteSimulator(INPSIMULATE* inputsimulated)
* @brief      DeleteSimulator
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  inputsimulated : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPLINUXFACTORY::DeleteSimulator(INPSIMULATE* inputsimulated)
{
  INPLINUXSIMULATE* inpsimulated = (INPLINUXSIMULATE*)inputsimulated;

  if(!inpsimulated)
    {
      return false;
    }

  delete inpsimulated;

  return true;
}
#endif


#pragma endregion

