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
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "GRPVectorFile.h"

#include "XFactory.h"
#include "XFileTXT.h"

#ifdef VECTORFILEDXF_ACTIVE
#include "GRPVectorFileDXF.h"
#endif

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILE::GRPVECTORFILE()
* @brief      Constructor
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILE::GRPVECTORFILE()
{
  Clean();

  RegisterEvent(GRPVECTORFILE_XEVENTTYPE_PartUnknown);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILE::~GRPVECTORFILE()
* @brief      Destructor
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
  
   DeRegisterEvent(GRPVECTORFILE_XEVENTTYPE_PartUnknown);
  
   Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XPATH* GRPVECTORFILE::GetPathFile()
* @brief      GetPathFile
* @ingroup    GRAPHIC
* 
* @return     XPATH* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XPATH* GRPVECTORFILE::GetPathFile()
{
  return &pathFile;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         VECTORFILETYPE GRPVECTORFILE::GetType()
* @brief      GetType
* @ingroup    GRAPHIC
* 
* @return     VECTORFILETYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
VECTORFILETYPE GRPVECTORFILE::GetType()
{
  return type;
}
  

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILE::SetType(VECTORFILETYPE type)
* @brief      SetType
* @ingroup    GRAPHIC
* 
* @param[in]  type : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILE::SetType(VECTORFILETYPE type)
{
  this->type = type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILE* GRPVECTORFILE::CreateInstance(XPATH& pathFile)
* @brief      CreateInstance
* @ingroup    GRAPHIC
* 
* @param[in]  pathFile : 
* 
* @return     GRPVECTORFILE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILE* GRPVECTORFILE::CreateInstance(XPATH& pathFile)
{
  if(!GRPVECTORFILE::DetectFile(pathFile)) 
    {
      return NULL;
    }

  GRPVECTORFILE* vectorFile = NULL;
  VECTORFILETYPE list[]     = { VECTORFILETYPE_DXF                                 
                              };

  for(int c=0; c < (sizeof(list)/sizeof(VECTORFILETYPE)); c++)
    {    
      vectorFile = GRPVECTORFILE::CreateInstance(list[c]);
      if(vectorFile) 
        {
          vectorFile->GetPathFile()->Set(pathFile);

          if(vectorFile->DetectType() == GRPVECTORFILERESULT_OK) 
            {              
              return vectorFile;

            } else delete vectorFile;
        }   
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILE* GRPVECTORFILE::CreateInstance(VECTORFILETYPE type)
* @brief      CreateInstance
* @ingroup    GRAPHIC
* 
* @param[in]  type : 
* 
* @return     GRPVECTORFILE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILE* GRPVECTORFILE::CreateInstance(VECTORFILETYPE type)
{
  GRPVECTORFILE* vectorFile = NULL;

  switch(type)
    {
      case VECTORFILETYPE_UNKNOWN : 
                        default   : break;

      #ifdef VECTORFILEDXF_ACTIVE
      case VECTORFILETYPE_DXF     : vectorFile = new GRPVECTORFILEDXF();
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
* @fn         XCHAR* GRPVECTORFILE::GetTypeText(VECTORFILETYPE type)
* @brief      GetTypeText
* @ingroup    GRAPHIC
* 
* @param[in]  type : 
* 
* @return     XCHAR* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* GRPVECTORFILE::GetTypeText(VECTORFILETYPE type)
{
  XCHAR* typeTXT = NULL;

  switch(type)
    {
      case VECTORFILETYPE_UNKNOWN : 
                        default   : typeTXT = __L("Unknown");
                                    break;

      #ifdef VECTORFILEDXF_ACTIVE
      case VECTORFILETYPE_DXF     : typeTXT = __L("DXF");
                                    break; 
      #endif     
    }

  return typeTXT;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILERESULT GRPVECTORFILE::DetectType()
* @brief      DetectType
* @ingroup    GRAPHIC
* 
* @return     GRPVECTORFILERESULT : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILERESULT GRPVECTORFILE::DetectType()
{  
  if(pathFile.IsEmpty()) 
    {
      type = VECTORFILETYPE_UNKNOWN;
      return GRPVECTORFILERESULT_ERRORNOTFILE;
    }

   XSTRING extension;
   pathFile.GetExt(extension);

   if(extension.IsEmpty())
   {
      type = VECTORFILETYPE_UNKNOWN;
      return  GRPVECTORFILERESULT_ERRORNOTFILE;  
   }

   return (type != VECTORFILETYPE_UNKNOWN)?GRPVECTORFILERESULT_OK:GRPVECTORFILERESULT_ERRORNOTFILE;
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
* @brief      GetConfig
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
* @fn         bool GRPVECTORFILE::DetectFileFormatText(XPATH& pathFile)
* @brief      DetectFileFormatText
* @ingroup    GRAPHIC
* 
* @param[in]  pathFile : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILE::DetectFileFormatText(XPATH& pathFile)
{  
  XFILETXTFORMATCHAR formatchar =  XFILETXTFORMATCHAR_UNKNOWN;
  bool isText = false;
  
  XFILETXT* fileTXT = new XFILETXT();
  if(fileTXT)  
    {
      if(fileTXT->Open(pathFile))
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
      if(file->Open(pathFile))
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
* @brief      IsConversionFile
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
* @brief      SetIsConversionFile
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
* @fn         bool GRPVECTORFILE::DetectFile(XPATH& pathFile)
* @brief      DetectFile
* @ingroup    GRAPHIC
* 
* @param[in]  pathFile : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILE::DetectFile(XPATH& pathFile)
{   
  XFILE* file = GEN_XFACTORY.Create_File();
  if(!file) 
    {
      return GRPVECTORFILERESULT_ERRORNOTMEMORY;
    }
  
  bool result = file->Exist(pathFile);  
  
  delete file;
  
  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILE::Clean()
{
  pathFile.Empty();
  type = VECTORFILETYPE_UNKNOWN;
  isconversionfile = false;
}


#pragma endregion


