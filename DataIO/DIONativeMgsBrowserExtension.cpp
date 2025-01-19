/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONativeMgsBrowserExtension.cpp
* 
* @class      DIONATIVEMSGBROWSEREXTENSION
* @brief      Data Input/Output Native Message Browser Extension class
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
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIONativeMgsBrowserExtension.h"

#include "XFactory.h"
#include "XTrace.h"

#include "DIOOSPipeline.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE


#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIONATIVEMSGBROWSEREXTENSION::DIONATIVEMSGBROWSEREXTENSION()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIONATIVEMSGBROWSEREXTENSION::DIONATIVEMSGBROWSEREXTENSION()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIONATIVEMSGBROWSEREXTENSION::~DIONATIVEMSGBROWSEREXTENSION()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIONATIVEMSGBROWSEREXTENSION::~DIONATIVEMSGBROWSEREXTENSION()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONATIVEMSGBROWSEREXTENSION::IsOpen()
* @brief      Is open
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONATIVEMSGBROWSEREXTENSION::IsOpen()
{
  return GEN_DIOOSPIPELINE.IsOpen();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONATIVEMSGBROWSEREXTENSION::Read(XFILEJSON& json)
* @brief      Read
* @ingroup    DATAIO
* 
* @param[in]  json : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONATIVEMSGBROWSEREXTENSION::Read(XFILEJSON& json)
{
  if(!GEN_DIOOSPIPELINE.IsOpen())
    {      
      return false;
    }

  XBUFFER buffer;
  bool    status;

  buffer.Resize(sizeof(XDWORD));

  status = GEN_DIOOSPIPELINE.Read(buffer);
  if(status)
    {
      XDWORD sizebuffer = 0;

      buffer.Extract(sizebuffer);

      SWAPDWORD(sizebuffer);

      if(sizebuffer)
        {
          buffer.Empty();
          buffer.Resize(sizebuffer);
 
          status = GEN_DIOOSPIPELINE.Read(buffer);
          if(status)
            {
              XSTRING all_string;

              all_string.ConvertFromUTF8(buffer);
      
              buffer.Empty();
              all_string.ConvertToUTF8(buffer);

              json.AddBufferLines(XFILETXTFORMATCHAR_ASCII, buffer);
            }
        }
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONATIVEMSGBROWSEREXTENSION::Write(XFILEJSON& json)
* @brief      Write
* @ingroup    DATAIO
* 
* @param[in]  json : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONATIVEMSGBROWSEREXTENSION::Write(XFILEJSON& json)
{
  if(!GEN_DIOOSPIPELINE.IsOpen())
    {
      return false;
    }

  XBUFFER buffer;
  XSTRING all_lines;
  XDWORD  sizebuffer;

  json.EncodeAllLines();
  json.GetAllInOneLine(all_lines, XFILETXTTYPELF_0D);  

  all_lines.ConvertToUTF8(buffer);

  sizebuffer = (XDWORD)buffer.GetSize() - 1;
  
  SWAPDWORD(sizebuffer);

  buffer.Insert((XDWORD)sizebuffer, 0);
  
  return GEN_DIOOSPIPELINE.Write(buffer);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIONATIVEMSGBROWSEREXTENSION::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIONATIVEMSGBROWSEREXTENSION::Clean()
{

}


#pragma endregion

