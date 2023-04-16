/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeItemDriver_SensorAM2315.cpp
* 
* @class      DIONODEITEMDRIVER_SENSOR_AM2315
* @brief      Data Input/Output Node Item Driver Sensor AM2315
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "math.h"

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIONodeItemSensor.h"

#include "DIONodeItemDriver_Sensor_AM2315.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMDRIVER_SENSOR_AM2315::DIONODEITEMDRIVER_SENSOR_AM2315(int port, int remoteitemaddress, int timeout)
* @brief      Constructor
* @ingroup    DATAIO
* 
* @param[in]  int : 
* @param[in]  int remoteitemaddress : 
* @param[in]  int timeout : 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMDRIVER_SENSOR_AM2315::DIONODEITEMDRIVER_SENSOR_AM2315(int port, int remoteitemaddress, int timeout)
{
  Clean();

  am2315 = new DIOI2CTEMHUMSENSORAM2315();

  this->port                = port; 
  this->remoteitemaddress = remoteitemaddress; 
  this->timeout             = timeout;   

  type        = DIONODEITEMDRIVER_TYPE_SENSOR_AM2315;  
  description = __L("AOSONG AM2315");
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMDRIVER_SENSOR_AM2315::~DIONODEITEMDRIVER_SENSOR_AM2315()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMDRIVER_SENSOR_AM2315::~DIONODEITEMDRIVER_SENSOR_AM2315()
{
  Close();

  if(am2315)
    {
      delete am2315;  
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMDRIVER_SENSOR_AM2315::Open()
* @brief      Open
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMDRIVER_SENSOR_AM2315::Open()
{
  if(!am2315)
    {
      return false;
    }

  DIONODEITEMSENSOR* nodeitemsensor = (DIONODEITEMSENSOR*)GetNodeItem();
  if(nodeitemsensor)
    {  
      nodeitemsensor->SetSensorType(DIONODEITEMSENSOR_TYPE_TEMPERATURE_HUMIDITY); 
    }

  
  #ifndef WINDOWS
  isopen = am2315->Ini(port, remoteitemaddress, timeout);  
  #else
  isopen = true;
  #endif
  if(isopen)
    {
      isworking = true;
    }

  return isopen;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMDRIVER_SENSOR_AM2315::Update()
* @brief      Update
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMDRIVER_SENSOR_AM2315::Update()
{
  float value[2] = { 0.0f, 0.0f };
  
  isworking = am2315->Read(value[0], value[1]);

  DIONODEITEM* nodeitem = GetNodeItem();
  if(!nodeitem)
    {
      return false;
    }

  if(nodeitem->GetValues()->GetSize() != 2) 
    {
      return false;
    }

  DIONODEITEMVALUE* nodeitemvalue;

  for(int c=0; c<2; c++)
    {
      nodeitemvalue = nodeitem->GetValues()->Get(c);
      if(nodeitemvalue)
        {
          float      differencevalue = 0.0f;
          XVARIANT*  nodeitemdifferencevalue = nodeitemvalue->GetDifferenceForChange();
 
          if(nodeitemdifferencevalue)
            {
              if(!nodeitemdifferencevalue->IsNull())
                {                  
                   differencevalue = (float)(*nodeitemdifferencevalue);    
                   differencevalue = (float)fabs(differencevalue);
                }
            }

          float difference = (value[c] - (float)(*nodeitemvalue->GetValue()));

          if(fabs(difference) > differencevalue)
            {
              (*nodeitemvalue->GetValue()) = value[c];
              nodeitemvalue->SetValueHasChanged(true); 

              XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[DIONODE item driver %s] %s %s value %f"), GetDescription()->Get(), nodeitem->GetDescription()->Get(), (!c)?__L("temperature"):__L("humidity"), value[c]);  
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMDRIVER_SENSOR_AM2315::Close()
* @brief      Close
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMDRIVER_SENSOR_AM2315::Close()
{
  am2315->End();
        
  isopen = false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMDRIVER_SENSOR_AM2315::SetNodeItem(DIONODEITEM* nodeitem)
* @brief      SetNodeItem
* @ingroup    DATAIO
* 
* @param[in]  nodeitem : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMDRIVER_SENSOR_AM2315::SetNodeItem(DIONODEITEM* nodeitem)
{
  if(!DIONODEITEMDRIVER::SetNodeItem(nodeitem)) 
    {
      return false;
    }

  DIONODEITEMSENSOR* nodeitemsensor = (DIONODEITEMSENSOR*)nodeitem;
  if(!nodeitemsensor)
    {
      return false;
    }

  nodeitemsensor->SetSensorType(DIONODEITEMSENSOR_TYPE_TEMPERATURE_HUMIDITY); 

  DIONODEITEMVALUE* value[2];

  for(XDWORD c=0; c<2; c++)
    {
      value[c] = new DIONODEITEMVALUE();
      if(value[c])
    
      switch(c)
        {
          case  0 : value[c]->SetType(DIONODEITEMVALUE_TYPE_TEMPERATURE); 
    
                    (*value[c]->GetValue())    =    0.00f;
                    (*value[c]->GetMinValue()) =  -50.00f;
                    (*value[c]->GetMaxValue()) =   50.00f;

                    value[c]->GetUnitFormat()->SetType(DIONODEITEMVALUE_UNITSFORMAT_TYPE_CELSIUSDEGREE);
                    break;

          case  1 : value[c]->SetType(DIONODEITEMVALUE_TYPE_HUMIDITY); 

                    (*value[c]->GetValue())    =   0.00f; 
                    (*value[c]->GetMinValue()) =   0.00f; 
                    (*value[c]->GetMaxValue()) = 100.00f;   

                    value[c]->GetUnitFormat()->SetType(DIONODEITEMVALUE_UNITSFORMAT_TYPE_RELATIVEHUMIDITY);
                    break;
        }

      nodeitem->GetValues()->Add(value[c]);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMDRIVER_SENSOR_AM2315::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMDRIVER_SENSOR_AM2315::Clean()
{
  am2315                = NULL;

  port                  = 0;
  remoteitemaddress   = 0;
  timeout               = 0;
}
