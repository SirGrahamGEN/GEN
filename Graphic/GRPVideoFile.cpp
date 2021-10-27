/**-------------------------------------------------------------------------------------------------------------------
*
* @file       GRPVideoFile.cpp
*
* @class      GRPVIDEOFILE
* @brief      Graphic Video File Class
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"

#include "GRPProperties.h"
#include "GRPBitmap.h"
#include "GRPBitmapSequence.h"

#include "GRPVideoFile.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* GRPVIDEOFILE_PROPERTYS
*
*---------------------------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVIDEOFILE_PROPERTYS::GRPVIDEOFILE_PROPERTYS()
* @brief      Constructor
* @ingroup    GRAPHIC
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
GRPVIDEOFILE_PROPERTYS::GRPVIDEOFILE_PROPERTYS()
{
  Clean();
}
 

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVIDEOFILE_PROPERTYS::~GRPVIDEOFILE_PROPERTYS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    GRAPHIC
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
GRPVIDEOFILE_PROPERTYS::~GRPVIDEOFILE_PROPERTYS()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVIDEOFILE_PROPERTYS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void GRPVIDEOFILE_PROPERTYS::Clean()
{
  width     = 0;
  height    = 0;
  nframes   = 0;
  framerate = 0;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* GRPVIDEOFILE
*
*---------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPVIDEOFILE::GRPVIDEOFILE()
* @brief      Constructor
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPVIDEOFILE::GRPVIDEOFILE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPVIDEOFILE::~GRPVIDEOFILE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPVIDEOFILE::~GRPVIDEOFILE()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVIDEOFILE::Open(XCHAR* xpath)
* @brief      Open
* @ingroup    GRAPHIC
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  xpath : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool GRPVIDEOFILE::Open(XCHAR* xpath)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVIDEOFILE::Create(XCHAR* xpath)
* @brief      Create
* @ingroup    GRAPHIC
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  xpath : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool GRPVIDEOFILE::Create(XCHAR* xpath)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVIDEOFILE_PROPERTYS* GRPVIDEOFILE::GetPropertys()
* @brief      GetPropertys
* @ingroup    GRAPHIC
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     GRPVIDEOFILE_PROPERTYS* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
GRPVIDEOFILE_PROPERTYS*  GRPVIDEOFILE::GetPropertys()
{
  return &propertys;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE* GRPVIDEOFILE::GetDataFrame(XDWORD index_frame, XDWORD& sizeframe)
* @brief      GetDataFrame
* @ingroup    GRAPHIC
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  index_frame : 
* @param[in]  sizeframe : 
* 
* @return     XBYTE* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XBYTE* GRPVIDEOFILE::GetDataFrame(XDWORD index_frame, XDWORD& sizeframe)
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVIDEOFILE::AddFrame(XBYTE* dataframe, XDWORD dataframesize)
* @brief      AddFrame
* @ingroup    GRAPHIC
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  dataframe : 
* @param[in]  dataframesize : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool GRPVIDEOFILE::AddFrame(XBYTE* dataframe, XDWORD dataframesize)
{

  return false;
}


    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVIDEOFILE::Close()
* @brief      Close
* @ingroup    GRAPHIC
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool GRPVIDEOFILE::Close()
{
 return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPVIDEOFILE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPVIDEOFILE::Clean()
{

}

