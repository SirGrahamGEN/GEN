/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPVectorFile.cpp
* 
* @class      GRPVECTORFILE
* @brief      Graphic Vector File class
* @ingroup    GRAPHIC
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

#include "GRPVectorFile.h"

#include "GRPVectorFile_XEvent.h"

#include "XFactory.h"
#include "XFileTXT.h"

#ifdef GRP_VECTOR_FILE_DXF_ACTIVE
#include "GRPVectorFileDXF.h"
#endif

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
* @fn         GRPVECTORFILE::GRPVECTORFILE()
* @brief      Constructor of class
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILE::GRPVECTORFILE()
{
  Clean();

  RegisterEvent(GRPVECTORFILE_XEVENTTYPE_PARTUNKNOWN);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILE::~GRPVECTORFILE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILE::~GRPVECTORFILE()
{
  if(IsConversionFile())
    {
      XFILE* xfile = GEN_XFACTORY.Create_File();
      if(xfile)
        {
          xfile->Erase((*GetPathFile()));
          GEN_XFACTORY.Delete_File(xfile);
        }
  
    }
  
  DeRegisterEvent(GRPVECTORFILE_XEVENTTYPE_PARTUNKNOWN);
  
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XPATH* GRPVECTORFILE::GetPathFile()
* @brief      Get path file
* @ingroup    GRAPHIC
* 
* @return     XPATH* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XPATH* GRPVECTORFILE::GetPathFile()
{
  return &pathfile;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILETYPE GRPVECTORFILE::GetType()
* @brief      Get type
* @ingroup    GRAPHIC
* 
* @return     GRPVECTORFILETYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILETYPE GRPVECTORFILE::GetType()
{
  return type;
}
  

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILE::SetType(GRPVECTORFILETYPE type)
* @brief      Set type
* @ingroup    GRAPHIC
* 
* @param[in]  type : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILE::SetType(GRPVECTORFILETYPE type)
{
  this->type = type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILE* GRPVECTORFILE::CreateInstance(XPATH& pathfile)
* @brief      Create instance
* @ingroup    GRAPHIC
* 
* @param[in]  pathfile : 
* 
* @return     GRPVECTORFILE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILE* GRPVECTORFILE::CreateInstance(XPATH& pathfile)
{
  if(!GRPVECTORFILE::DetectFile(pathfile)) 
    {
      return NULL;
    }

  GRPVECTORFILE*    vectorFile = NULL;
  GRPVECTORFILETYPE list[]     = { GRPVECTORFILETYPE_DXF                                 
                                 };

  for(int c=0; c < (sizeof(list)/sizeof(GRPVECTORFILETYPE)); c++)
    {    
      vectorFile = GRPVECTORFILE::CreateInstance(list[c]);
      if(vectorFile) 
        {
          vectorFile->GetPathFile()->Set(pathfile);

          if(vectorFile->DetectType() == GRPVECTORFILERESULT_OK) 
            {              
              return vectorFile;

            } 
           else 
            {
              delete vectorFile;
            }
        }   
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILE* GRPVECTORFILE::CreateInstance(GRPVECTORFILETYPE type)
* @brief      Create instance
* @ingroup    GRAPHIC
* 
* @param[in]  type : 
* 
* @return     GRPVECTORFILE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILE* GRPVECTORFILE::CreateInstance(GRPVECTORFILETYPE type)
{
  GRPVECTORFILE* vectorFile = NULL;

  switch(type)
    {
      case GRPVECTORFILETYPE_UNKNOWN  : 
                            default   : break;

      #ifdef GRP_VECTOR_FILE_DXF_ACTIVE
      case GRPVECTORFILETYPE_DXF      : vectorFile = new GRPVECTORFILEDXF();
                                        break; 
      #endif      
   }

  if(vectorFile) 
    {
      vectorFile->SetType(type);
    }

  return vectorFile;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XCHAR* GRPVECTORFILE::GetTypeText(GRPVECTORFILETYPE type)
* @brief      Get type text
* @ingroup    GRAPHIC
* 
* @param[in]  type : 
* 
* @return     XCHAR* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* GRPVECTORFILE::GetTypeText(GRPVECTORFILETYPE type)
{
  XCHAR* typeTXT = NULL;

  switch(type)
    {
      case GRPVECTORFILETYPE_UNKNOWN : 
                           default   :  typeTXT = __L("Unknown");
                                        break;

      #ifdef GRP_VECTOR_FILE_DXF_ACTIVE
      case GRPVECTORFILETYPE_DXF     :  typeTXT = __L("DXF");
                                        break; 
      #endif     
    }

  return typeTXT;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILERESULT GRPVECTORFILE::DetectType()
* @brief      Detect type
* @ingroup    GRAPHIC
* 
* @return     GRPVECTORFILERESULT : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILERESULT GRPVECTORFILE::DetectType()
{  
  if(pathfile.IsEmpty()) 
    {
      type = GRPVECTORFILETYPE_UNKNOWN;
      return GRPVECTORFILERESULT_ERRORNOTFILE;
    }

  XSTRING extension;
  pathfile.GetExt(extension);

  if(extension.IsEmpty())
    {
      type = GRPVECTORFILETYPE_UNKNOWN;
      return  GRPVECTORFILERESULT_ERRORNOTFILE;  
    }

  return (type != GRPVECTORFILETYPE_UNKNOWN)?GRPVECTORFILERESULT_OK:GRPVECTORFILERESULT_ERRORNOTFILE;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILERESULT GRPVECTORFILE::Load()
* @brief      Load
* @ingroup    GRAPHIC
* 
* @return     GRPVECTORFILERESULT : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILERESULT GRPVECTORFILE::Load()
{
  return GRPVECTORFILERESULT_ERRORUNKNOWN;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILECONFIG* GRPVECTORFILE::GetConfig()
* @brief      Get config
* @ingroup    GRAPHIC
* 
* @return     GRPVECTORFILECONFIG* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILECONFIG* GRPVECTORFILE::GetConfig()
{
  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILE::DetectFileFormatText(XPATH& pathfile)
* @brief      Detect file format text
* @ingroup    GRAPHIC
* 
* @param[in]  pathfile : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILE::DetectFileFormatText(XPATH& pathfile)
{  
  XFILETXTFORMATCHAR  formatchar  =  XFILETXTFORMATCHAR_UNKNOWN;
  bool                isText      = false;
  
  XFILETXT* fileTXT = new XFILETXT();
  if(fileTXT)  
    {
      if(fileTXT->Open(pathfile))
        {
          formatchar = fileTXT->GetFormatCharFromFile();
  
          fileTXT->Close();
        }
  
      delete fileTXT;
    }
  
  if(formatchar != XFILETXTFORMATCHAR_ASCII) return true;

  XFILE* file = GEN_XFACTORY.Create_File();
  if(file)  
    {
      if(file->Open(pathfile))
        {
          #define MAX_BUFFER_TEST 1024*5 
  
          XBUFFER buffer;
          XDWORD  size = MAX_BUFFER_TEST;
          XDWORD  controlchars = 0;
  
          buffer.Resize(MAX_BUFFER_TEST);
          file->Read(buffer.Get(), &size);
  
          if(size)
            {
              for(XDWORD c=0; c<size; c++)
                {
                  if(((buffer.Get()[c] >= 0x00) && (buffer.Get()[c] < 0x0A)) ||         
                     ((buffer.Get()[c] >  0x0D) && (buffer.Get()[c] < 0x20)))
                    {
                      controlchars++;
                    }
                }
  
              int percent = (controlchars*100/size);
              if(percent < 10) isText = true;
            }
     
          file->Close();
        }
  
      delete file;
    }

   return isText;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILE::IsConversionFile()
* @brief      Is conversion file
* @ingroup    GRAPHIC
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILE::IsConversionFile()
{
  return isconversionfile;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILE::SetIsConversionFile(bool isconversionfile)
* @brief      Set is conversion file
* @ingroup    GRAPHIC
* 
* @param[in]  isconversionfile : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILE::SetIsConversionFile(bool isconversionfile)
{
  this->isconversionfile = isconversionfile;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILE::DetectFile(XPATH& pathfile)
* @brief      Detect file
* @ingroup    GRAPHIC
* 
* @param[in]  pathfile : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILE::DetectFile(XPATH& pathfile)
{   
  XFILE* file = GEN_XFACTORY.Create_File();
  if(!file) 
    {
      return false;
    }
  
  bool result = file->Exist(pathfile);  
  
  delete file;
  
  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILE::Clean()
{
  pathfile.Empty();

  type             = GRPVECTORFILETYPE_UNKNOWN;
  isconversionfile = false;
}


#pragma endregion


