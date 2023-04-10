/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeDeviceDriver_SensorAM2315.cpp
* 
* @class      DIONODEDEVICEDRIVER_SENSOR_AM2315
* @brief      Data Input/Output Node Device Driver Sensor AM2315
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

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIONodeSensor.h"

#include "DIONodeDeviceDriver_Sensor_AM2315.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEDEVICEDRIVER_SENSOR_AM2315::DIONODEDEVICEDRIVER_SENSOR_AM2315(int port, int remotedeviceaddress, int timeout)
* @brief      Constructor
* @ingroup    DATAIO
* 
* @param[in]  int : 
* @param[in]  int remotedeviceaddress : 
* @param[in]  int timeout : 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEDEVICEDRIVER_SENSOR_AM2315::DIONODEDEVICEDRIVER_SENSOR_AM2315(int port, int remotedeviceaddress, int timeout)
{
  Clean();

  am2315 = new DIOI2CTEMHUMSENSORAM2315();

  this->port                = port; 
  this->remotedeviceaddress = remotedeviceaddress; 
  this->timeout             = timeout;    

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEDEVICEDRIVER_SENSOR_AM2315::~DIONODEDEVICEDRIVER_SENSOR_AM2315()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEDEVICEDRIVER_SENSOR_AM2315::~DIONODEDEVICEDRIVER_SENSOR_AM2315()
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
* @fn         bool DIONODEDEVICEDRIVER_SENSOR_AM2315::Open()
* @brief      Open
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEDEVICEDRIVER_SENSOR_AM2315::Open()
{
  if(!am2315)
    {
      return false;
    }
  
  // isopen = am2315->Ini(port, remotedeviceaddress, timeout);
  isopen    = true;
  isworking = true;

  return isopen;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEDEVICEDRIVER_SENSOR_AM2315::Update()
* @brief      Update
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEDEVICEDRIVER_SENSOR_AM2315::Update()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEDEVICEDRIVER_SENSOR_AM2315::Close()
* @brief      Close
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEDEVICEDRIVER_SENSOR_AM2315::Close()
{
  am2315->End();
        
  isopen = false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEDEVICEDRIVER_SENSOR_AM2315::SetNodeItem(DIONODEITEM* nodeitem)
* @brief      SetNodeItem
* @ingroup    DATAIO
* 
* @param[in]  nodeitem : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEDEVICEDRIVER_SENSOR_AM2315::SetNodeItem(DIONODEITEM* nodeitem)
{
  if(!DIONODEDEVICEDRIVER::SetNodeItem(nodeitem)) 
    {
      return false;
    }

  DIONODESENSOR* nodesensor = (DIONODESENSOR*)nodeitem;
  if(!nodesensor)
    {
      return false;
    }

  nodesensor->SetSensorType(DIONODESENSOR_TYPE_TEMPERATURE_HUMIDITY); 

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
* @fn         void DIONODEDEVICEDRIVER_SENSOR_AM2315::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEDEVICEDRIVER_SENSOR_AM2315::Clean()
{
  am2315                = NULL;

  port                  = 0;
  remotedeviceaddress   = 0;
  timeout               = 0;
}
