/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCoreProtocol_Message.cpp
* 
* @class      DIOCOREPROTOCOL_MESSAGE
* @brief      Data Input/Output Core Protocol CFG class
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XBase.h"
#include "XFactory.h"

#include "DIOCoreProtocol_Messages.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE


#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_DIOCOREPROTOCOL_MESSAGE


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_MESSAGE::DIOCOREPROTOCOL_MESSAGE()
* @brief      Constructor
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_MESSAGE::DIOCOREPROTOCOL_MESSAGE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_MESSAGE::~DIOCOREPROTOCOL_MESSAGE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_MESSAGE::~DIOCOREPROTOCOL_MESSAGE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_MESSAGE_TYPE_ACQUISITION DIOCOREPROTOCOL_MESSAGE::GetAcquisitionType()
* @brief      GetAcquisitionType
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOL_MESSAGE_TYPE_ACQUISITION : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_MESSAGE_TYPE_ACQUISITION DIOCOREPROTOCOL_MESSAGE::GetAcquisitionType()
{
  return acquisitiontype;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_MESSAGE::SetAcquisitionType(DIOCOREPROTOCOL_MESSAGE_TYPE_ACQUISITION acquisitiontype)
* @brief      SetAcquisitionType
* @ingroup    DATAIO
* 
* @param[in]  acquisitiontype : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_MESSAGE::SetAcquisitionType(DIOCOREPROTOCOL_MESSAGE_TYPE_ACQUISITION acquisitiontype)
{
  this->acquisitiontype = acquisitiontype;
}  
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_HEADER* DIOCOREPROTOCOL_MESSAGE::GetHeader()
* @brief      GetHeader
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOL_HEADER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_HEADER* DIOCOREPROTOCOL_MESSAGE::GetHeader()
{
  return &header;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* DIOCOREPROTOCOL_MESSAGE::GetContent()
* @brief      GetContent
* @ingroup    DATAIO
* 
* @return     XBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* DIOCOREPROTOCOL_MESSAGE::GetContent()
{
  return &content;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_MESSAGE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_MESSAGE::Clean()
{                                                            
  acquisitiontype = DIOCOREPROTOCOL_MESSAGE_TYPE_ACQUISITION_UNKNOWN;
}


#pragma endregion


#pragma region CLASS_DIOCOREPROTOCOL_MESSAGES


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_MESSAGES::DIOCOREPROTOCOL_MESSAGES()
* @brief      Constructor
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_MESSAGES::DIOCOREPROTOCOL_MESSAGES()
{
  Clean();

  xmutexmessages = GEN_XFACTORY.Create_Mutex();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_MESSAGES::~DIOCOREPROTOCOL_MESSAGES()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_MESSAGES::~DIOCOREPROTOCOL_MESSAGES()
{
  if(xmutexmessages)
    {
      GEN_XFACTORY.Delete_Mutex(xmutexmessages);
    }

  DeleteAll();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XMAP<DIOCOREPROTOCOL_MESSAGE*, DIOCOREPROTOCOL_MESSAGE*>* DIOCOREPROTOCOL_MESSAGES::GetMessages()
* @brief      GetMessages
* @ingroup    DATAIO
* 
* @return     XMAP<DIOCOREPROTOCOL_MESSAGE*, : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XMAP<DIOCOREPROTOCOL_MESSAGE*, DIOCOREPROTOCOL_MESSAGE*>*  DIOCOREPROTOCOL_MESSAGES::GetAll()
{
  return &allmessages;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_MESSAGES::DeleteAll()
* @brief      DeleteAll
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_MESSAGES::DeleteAll()
{
  if(allmessages.IsEmpty())
    {
      return false;
    }

  allmessages.DeleteKeyContents();
  allmessages.DeleteElementContents();
 
  return allmessages.DeleteAll();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DIOCOREPROTOCOL_MESSAGES::FindRequest(XUUID* IDmessage)
* @brief      FindRequest
* @ingroup    DATAIO
* 
* @param[in]  IDmessage : 
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int DIOCOREPROTOCOL_MESSAGES::FindRequest(XUUID* IDmessage)
{
  for(XDWORD c=0; c<allmessages.GetSize(); c++)
    {
      DIOCOREPROTOCOL_MESSAGE* message_request = allmessages.GetKey(c);
      if(message_request)
        {
          if(message_request->GetHeader()->GetIDMessage()->Compare((*IDmessage)))
            {
              return (int)c;
            }
        }    
    }

  return NOTFOUND;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DIOCOREPROTOCOL_MESSAGES::FindResponse(XUUID* IDmessage)
* @brief      FindResponse
* @ingroup    DATAIO
* 
* @param[in]  IDmessage : 
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int DIOCOREPROTOCOL_MESSAGES::FindResponse(XUUID* IDmessage)
{
  for(XDWORD c=0; c<allmessages.GetSize(); c++)
    {
      DIOCOREPROTOCOL_MESSAGE* message_response = allmessages.GetElement(c);
      if(message_response)
        {
          if(message_response->GetHeader()->GetIDMessage()->Compare((*IDmessage)))
            {
              return (int)c;
            }
        }    
    }

  return NOTFOUND;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DIOCOREPROTOCOL_MESSAGES::FindRequest(DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param)
* @brief      FindRequest
* @ingroup    DATAIO
* 
* @param[in]  operation : 
* @param[in]  operation_param : 
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int DIOCOREPROTOCOL_MESSAGES::FindRequest(DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param)
{
  for(XDWORD c=0; c<allmessages.GetSize(); c++)
    {
      DIOCOREPROTOCOL_MESSAGE* message_request = allmessages.GetKey(c);
      if(message_request)
        {
          if((message_request->GetHeader()->GetOperation() == operation) && !message_request->GetHeader()->GetOperationParam()->Compare(operation_param))
            {
              return (int)c;
            }
        }    
    }

  return NOTFOUND;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DIOCOREPROTOCOL_MESSAGES::FindResponse(DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param)
* @brief      FindResponse
* @ingroup    DATAIO
* 
* @param[in]  operation : 
* @param[in]  operation_param : 
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int DIOCOREPROTOCOL_MESSAGES::FindResponse(DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param)
{
  for(XDWORD c=0; c<allmessages.GetSize(); c++)
    {
      DIOCOREPROTOCOL_MESSAGE* message_response = allmessages.GetElement(c);
      if(message_response)
        {
          if((message_response->GetHeader()->GetOperation() == operation) && !message_response->GetHeader()->GetOperationParam()->Compare(operation_param))
            {
              return (int)c;
            }
        }    
    }

  return NOTFOUND;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_MESSAGES::AddRequest(DIOCOREPROTOCOL_MESSAGE* message_request)
* @brief      AddRequest
* @ingroup    DATAIO
* 
* @param[in]  message_request : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_MESSAGES::AddRequest(DIOCOREPROTOCOL_MESSAGE* message_request)
{
  if(!message_request)
    {
      return false;
    }

  if(xmutexmessages)
    {
      xmutexmessages->Lock();
    }

  allmessages.Add(message_request, NULL); 

  if(xmutexmessages)
    {
      xmutexmessages->UnLock();
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_MESSAGES::AddResponse(DIOCOREPROTOCOL_MESSAGE* message_response)
* @brief      AddResponse
* @ingroup    DATAIO
* 
* @param[in]  message_response : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_MESSAGES::AddResponse(DIOCOREPROTOCOL_MESSAGE* message_response)
{
  bool status = false;

  if(!message_response)
    {
      return false;
    }

  if(xmutexmessages)
    {
      xmutexmessages->Lock();
    }

  int index = FindRequest(message_response->GetHeader()->GetIDMessage());

  for(XDWORD c=0; c<allmessages.GetSize(); c++)
    {
      DIOCOREPROTOCOL_MESSAGE* message_request = allmessages.GetKey(c);
      if(message_request)
        {
          if(message_request->GetHeader()->GetIDMessage()->Compare((*message_response->GetHeader()->GetIDMessage())))
            {
              allmessages.Set(message_request, message_response);

              status = true;  
            }
        }    
    }

  if(xmutexmessages)
    {
      xmutexmessages->UnLock();
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_MESSAGES::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_MESSAGES::Clean()
{
  xmutexmessages = NULL;
}


#pragma endregion

