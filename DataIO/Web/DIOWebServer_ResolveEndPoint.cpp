/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOWebServer_ResolveEndPoint.cpp
* 
* @class      DIOWEBSERVER_RESOLVEENDPOINT
* @brief      Data Input/Output Web Server Resolve EndPoint class
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

#include "XFileJSON.h"

#include "DIOWebServer_ResolveEndPoint.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOWEBSERVER_RESOLVEENDPOINT::DIOWEBSERVER_RESOLVEENDPOINT()
* @brief      Constructor
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_RESOLVEENDPOINT::DIOWEBSERVER_RESOLVEENDPOINT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOWEBSERVER_RESOLVEENDPOINT::~DIOWEBSERVER_RESOLVEENDPOINT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_RESOLVEENDPOINT::~DIOWEBSERVER_RESOLVEENDPOINT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWEBSERVER_RESOLVEENDPOINT::Update()
* @brief      Update
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_RESOLVEENDPOINT::Update()
{  
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWEBSERVER_RESOLVEENDPOINT::CreateResponse(XSTRING* response)
* @brief      CreateResponse
* @ingroup    
* 
* @param[in]  response : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_RESOLVEENDPOINT::CreateResponse(XSTRING* response)
{ 
  bool status = false;

  /*
  XSERIALIZATIONMETHOD* serializationmethod;
  XFILEJSON             xfileJSON;      
  XSTRING               alllines;
  
  
  serializationmethod = XSERIALIZABLE::CreateInstance(xfileJSON);

  InitSerialize(serializationmethod);
  xfileJSON.EncodeAllLines(true);  
  
  if(response) 
    {
      xfileJSON.GetAllInOneLine((*response));
      status = true;
    }

  delete serializationmethod;
  */
  
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWEBSERVER_RESOLVEENDPOINT::Serialize()
* @brief      Serialize
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_RESOLVEENDPOINT::Serialize()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWEBSERVER_RESOLVEENDPOINT::Deserialize()
* @brief      Deserialize
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_RESOLVEENDPOINT::Deserialize()
{     
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOWEBSERVER_RESOLVEENDPOINT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_RESOLVEENDPOINT::Clean()
{
 
}
