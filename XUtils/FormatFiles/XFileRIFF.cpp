/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XFileRIFF.cpp
* 
* @class      XFILERIFF
* @brief      eXtended Utils RIFF file class
* @ingroup    XUTILS
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

#include "XFileRIFF.h"

#include "XFactory.h"
#include "XTrace.h"
#include "XVector.h"

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


#pragma region CLASS_XFILERIFF_LIST


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILERIFF_LIST::XFILERIFF_LIST()
* @brief      Constructor of class
* @ingroup    XUTILS
*
* ---------------------------------------------------------------------------------------------------------------------*/
XFILERIFF_LIST::XFILERIFF_LIST()
{
  Clean();
}
  

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILERIFF_LIST::~XFILERIFF_LIST()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* ---------------------------------------------------------------------------------------------------------------------*/
XFILERIFF_LIST::~XFILERIFF_LIST()
{
  Clean();
}
  

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD XFILERIFF_LIST::GetType()
* @brief      Get type
* @ingroup    XUTILS
*
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD XFILERIFF_LIST::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XFILERIFF_LIST::SetType(XDWORD type)
* @brief      Set type
* @ingroup    XUTILS
*
* @param[in]  type : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void XFILERIFF_LIST::SetType(XDWORD type)
{
  this->type = type; 

  #ifdef GEN_DEBUG    
  
  typestr[0] = (type & 0x000000FF);
  typestr[1] = (type & 0x0000FF00) >> 8;
  typestr[2] = (type & 0x00FF0000) >> 16;
  typestr[3] = (type & 0xFF000000) >> 24;
  typestr[4] = 0;  
  
  #endif

} 


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILERIFF_LIST::IsTypeList()
* @brief      Is type list
* @ingroup    XUTILS
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XFILERIFF_LIST::IsTypeList()
{
  if((GetType() == XFILERIFF_TYPE_LIST) || (GetType() == XFILERIFF_TYPE_RIFF))  return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD XFILERIFF_LIST::GetSize()
* @brief      Get size
* @ingroup    XUTILS
*
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD XFILERIFF_LIST::GetSize()
{
  return size;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XFILERIFF_LIST::SetSize(XDWORD size)
* @brief      Set size
* @ingroup    XUTILS
*
* @param[in]  size : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void XFILERIFF_LIST::SetSize(XDWORD size)
{
  this->size = size;   
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD XFILERIFF_LIST::GetTypeList()
* @brief      Get type list
* @ingroup    XUTILS
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XFILERIFF_LIST::GetTypeList()
{
  return typelist;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XFILERIFF_LIST::SetTypeList(XDWORD typelist)
* @brief      Set type list
* @ingroup    XUTILS
*
* @param[in]  typelist : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void XFILERIFF_LIST::SetTypeList(XDWORD typelist)
{
  this->typelist = typelist;  

  #ifdef GEN_DEBUG    
  
  typeliststr[0] = (typelist & 0x000000FF);
  typeliststr[1] = (typelist & 0x0000FF00) >> 8;
  typeliststr[2] = (typelist & 0x00FF0000) >> 16;
  typeliststr[3] = (typelist & 0xFF000000) >> 24;
  typeliststr[4] = 0;  
  
  #endif
}
     

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XQWORD XFILERIFF_LIST::GetPositionFileData()
* @brief      Get position file data
* @ingroup    XUTILS
*
* @return     XQWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XQWORD XFILERIFF_LIST::GetPositionFileData()
{
  return positionfiledata;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XFILERIFF_LIST::SetPositionFileData(XQWORD positionfiledata)
* @brief      Set position file data
* @ingroup    XUTILS
*
* @param[in]  positionfiledata : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void XFILERIFF_LIST::SetPositionFileData(XQWORD positionfiledata)
{
  this->positionfiledata = positionfiledata;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XFILERIFF_LIST::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* ---------------------------------------------------------------------------------------------------------------------*/
void XFILERIFF_LIST::Clean()
{ 
  type              = 0;
  size              = 0;
  typelist          = 0;  
  positionfiledata  = 0;

  #ifdef GEN_DEBUG    
  
  memset(typestr      , 0, 5);
  memset(typeliststr  , 0, 5);  
  
  #endif
}


#pragma endregion


#pragma region CLASS_XFILERIFF


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILERIFF::XFILERIFF()
* @brief      Constructor of class
* @ingroup    XUTILS
*
* ---------------------------------------------------------------------------------------------------------------------*/
XFILERIFF::XFILERIFF() 
{ 
  Clean();     

  GEN_XFACTORY_CREATE(xfilebase, Create_File())
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILERIFF::~XFILERIFF()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* ---------------------------------------------------------------------------------------------------------------------*/
XFILERIFF::~XFILERIFF()    
{ 
  if(xfilebase) GEN_XFACTORY.Delete_File(xfilebase);

  Clean();                            
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILERIFF::Open(XCHAR* xpath, bool isreadonly)
* @brief      Open
* @ingroup    XUTILS
*
* @param[in]  xpath : 
* @param[in]  isreadonly : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XFILERIFF::Open(XCHAR* xpath, bool isreadonly)
{
  if(!xfilebase) return false;

  iscreatefile  = false;

  return xfilebase->Open(xpath, isreadonly);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILERIFF::Create(XCHAR* xpath)
* @brief      Create
* @ingroup    XUTILS
*
* @param[in]  xpath : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XFILERIFF::Create(XCHAR* xpath)
{
  if(!xfilebase) return false;

  bool status;

  status = xfilebase->Create(xpath);
 
  xtreelist.DeleteContents();
  xtreelist.DeleteAll();  

  if(status) iscreatefile = true;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILERIFF::ReadAllLists()
* @brief      Read all lists
* @ingroup    XUTILS
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XFILERIFF::ReadAllLists()
{
  if(!xfilebase) return false;

  XDWORD               type     = 0;
  XDWORD               size     = 0;
  XDWORD               typelist = 0;  
  XFILERIFF_LIST_NODE* root;   
  XFILERIFF_LIST*      root_data;


  root_data = new XFILERIFF_LIST();
  if(!root_data) 
    {
      return false;
    }
   
  if(!xfilebase->Read((XBYTE*)&type, sizeof(XDWORD)))                   
    { 
      delete root_data;
      return false;
    }    
 
  if((type != XFILERIFF_TYPE_RIFF) && (type != XFILERIFF_TYPE_LIST))    
    {
      delete root_data;
      return false;
    }

  if(!xfilebase->Read((XBYTE*)&size, sizeof(XDWORD)))      
    {
      delete root_data;
      return false;
    }

  if(!size) 
    {
      delete root_data;
      return false;
    }

  if(xfilebase->Read((XBYTE*)&typelist, sizeof(XDWORD)))  
    {          
      XQWORD positionfiledata = 0;
    
      xfilebase->GetPosition(positionfiledata);

      root_data->SetType(type);
      root_data->SetSize(size - sizeof(XDWORD));
      root_data->SetTypeList(typelist);
      root_data->SetPositionFileData(positionfiledata);
  
      XSTRING string;
      ConvertDWORDtoString(typelist, string);

      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[LIST] %s"), string.Get());   
 
      root = new XFILERIFF_LIST_NODE(root_data);
      if(root) 
        {        
          xtreelist.SetRoot(root);

          XQWORD size_calculed = ReadNodeLists(root);
          if((size_calculed + sizeof(XDWORD)) == size) 
            {
              return true;
            }
        }
    }
 
  delete root_data;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XQWORD XFILERIFF::ReadNodeLists(XFILERIFF_LIST_NODE* node)
* @brief      Read node lists
* @ingroup    XUTILS
*
* @param[in]  node : 
* 
* @return     XQWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XQWORD XFILERIFF::ReadNodeLists(XFILERIFF_LIST_NODE* node)
{
  if(!node) return 0;

  XDWORD                data[3]           = { 0, 0, 0 };
  XDWORD                sizenode          = node->GetData()->GetSize();
  XQWORD                currentsizenode   = 0;
  XQWORD                positionfiledata  = 0;
  XFILERIFF_LIST*       list              = NULL;
  XFILERIFF_LIST_NODE*  subnode           = NULL;    
//static XSTRING        tabulated;

//tabulated.Add(__L("  "));
   
  do{ if(!xfilebase->Read((XBYTE*)data, sizeof(XDWORD)*2)) return 0;
      currentsizenode += (sizeof(XDWORD)*2);

      if((data[0] == XFILERIFF_TYPE_LIST) ||  (data[0] == XFILERIFF_TYPE_RIFF))
        { 
          if(!xfilebase->Read((XBYTE*)&data[2], sizeof(XDWORD))) return 0;   
          currentsizenode += sizeof(XDWORD);
          
          xfilebase->GetPosition(positionfiledata);

          list = new XFILERIFF_LIST();
          if(!list) return 0;
      
          list->SetType(data[0]);
          list->SetSize(data[1] - sizeof(XDWORD));
          list->SetTypeList(data[2]);
          list->SetPositionFileData(positionfiledata);

          subnode = new XFILERIFF_LIST_NODE(list);
          if(!subnode)  return 0;

          node->AddChild(subnode);

          XSTRING string;
          ConvertDWORDtoString(data[2], string);
       
          //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("%s[LIST] %s"), tabulated.Get(), string.Get());  
       
          XQWORD inc = ReadNodeLists(subnode);               
          currentsizenode += inc;                           
        }
       else
        {
          xfilebase->GetPosition(positionfiledata);

          list = new XFILERIFF_LIST();
          if(!list) return 0;
     
          list->SetType(data[0]);
          list->SetSize(data[1]);          
          list->SetPositionFileData(positionfiledata);

          subnode = new XFILERIFF_LIST_NODE(list);
          if(!subnode)  return 0;

          node->AddChild(subnode);

          XSTRING string;
          ConvertDWORDtoString(data[0], string);

          //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("%s%s"), tabulated.Get(), string.Get()); 
                 
          XDWORD inc = list->GetSize(); 

          xfilebase->SetPosition(positionfiledata + inc); 
          
          //inc += (inc % 2)?1:0;           
                   
          currentsizenode += inc;            
        }

    } while(currentsizenode < sizenode);   
  
 //tabulated.DeleteCharacters(0, 2);
    
 return currentsizenode;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD XFILERIFF::GetTypeFromString(XCHAR* string)
* @brief      Get type from string
* @ingroup    XUTILS
*
* @param[in]  string : 
* 
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD XFILERIFF::GetTypeFromString(XCHAR* string)
{
  if(!string) return 0;

  XSTRING str;
  XDWORD  result = 0;

  str = string;

  XBUFFER charstr;
  
  str.ConvertToASCII(charstr);  
  memcpy((XBYTE*)&result, (XBYTE*)charstr.Get(), sizeof(XDWORD));  
  
  return result;  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILERIFF_LIST* XFILERIFF::GetList(XDWORD type, XDWORD fathertypelist)
* @brief      Get list
* @ingroup    XUTILS
*
* @param[in]  type : 
* @param[in]  fathertypelist : 
* 
* @return     XFILERIFF_LIST* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XFILERIFF_LIST* XFILERIFF::GetList(XDWORD type, XDWORD fathertypelist)
{
  return GetList(false, xtreelist.GetRoot(), type, fathertypelist);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILERIFF_LIST* XFILERIFF::GetList(XCHAR* typestr, XCHAR* fathertypeliststr)
* @brief      Get list
* @ingroup    XUTILS
*
* @param[in]  typestr : 
* @param[in]  fathertypeliststr : 
* 
* @return     XFILERIFF_LIST* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XFILERIFF_LIST* XFILERIFF::GetList(XCHAR* typestr, XCHAR* fathertypeliststr)
{
  if(!typestr) return NULL;

  XDWORD type           = 0;
  XDWORD fathertypelist = 0;

  type = GetTypeFromString(typestr);  
  if(fathertypeliststr)  fathertypelist = GetTypeFromString(fathertypeliststr);
  
  return GetList(false, xtreelist.GetRoot(), type, fathertypelist);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILERIFF_LIST* XFILERIFF::GetChunk(XDWORD type, XDWORD fathertypelist)
* @brief      Get chunk
* @ingroup    XUTILS
*
* @param[in]  type : 
* @param[in]  fathertypelist : 
* 
* @return     XFILERIFF_LIST* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XFILERIFF_LIST* XFILERIFF::GetChunk(XDWORD type, XDWORD fathertypelist)
{
  return GetList(true, xtreelist.GetRoot(), type, fathertypelist);
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILERIFF_LIST* XFILERIFF::GetChunk(XCHAR* typestr, XCHAR* fathertypeliststr)
* @brief      Get chunk
* @ingroup    XUTILS
* 
* @param[in]  typestr : 
* @param[in]  fathertypeliststr : 
* 
* @return     XFILERIFF_LIST* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILERIFF_LIST* XFILERIFF::GetChunk(XCHAR* typestr, XCHAR* fathertypeliststr)
{
  if(!typestr) return NULL;

  XDWORD type           = 0;
  XDWORD fathertypelist = 0;

  type = GetTypeFromString(typestr);  
  if(fathertypeliststr)  fathertypelist = GetTypeFromString(fathertypeliststr);
  
  return GetList(true, xtreelist.GetRoot(), type, fathertypelist);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILERIFF::GetChunkData(XFILERIFF_LIST* chunkinfo, XBYTE* data, XDWORD& datasize)
* @brief      Get chunk data
* @ingroup    XUTILS
*
* @param[in]  chunkinfo : 
* @param[in]  data : 
* @param[in]  datasize : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XFILERIFF::GetChunkData(XFILERIFF_LIST* chunkinfo, XBYTE* data, XDWORD& datasize)
{
  if(!chunkinfo) return false;

  datasize = 0;

  xfilebase->SetPosition(chunkinfo->GetPositionFileData());
    
  if(!xfilebase->Read(data, chunkinfo->GetSize())) return false;

  datasize = chunkinfo->GetSize();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILERIFF::GetChunkData(XFILERIFF_LIST* chunkinfo, XBUFFER& data)
* @brief      Get chunk data
* @ingroup    XUTILS
*
* @param[in]  chunkinfo : 
* @param[in]  data : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XFILERIFF::GetChunkData(XFILERIFF_LIST* chunkinfo, XBUFFER& data)
{
  if(!chunkinfo) return false;

  XDWORD datasize;

  datasize = chunkinfo->GetSize();

  data.Resize(datasize);

  return GetChunkData(chunkinfo, data.Get(), datasize);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILERIFF_LIST_NODE* XFILERIFF::GetListNode(XDWORD type, XDWORD fathertypelist)
* @brief      Get list node
* @ingroup    XUTILS
*
* @param[in]  type : 
* @param[in]  fathertypelist : 
* 
* @return     XFILERIFF_LIST_NODE* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XFILERIFF_LIST_NODE* XFILERIFF::GetListNode(XDWORD type, XDWORD fathertypelist)
{
  return GetListNode(false, xtreelist.GetRoot(), type, fathertypelist);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILERIFF_LIST_NODE* XFILERIFF::GetListNode(XCHAR* typestr, XCHAR* fathertypeliststr)
* @brief      Get list node
* @ingroup    XUTILS
*
* @param[in]  typestr : 
* @param[in]  fathertypeliststr : 
* 
* @return     XFILERIFF_LIST_NODE* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XFILERIFF_LIST_NODE* XFILERIFF::GetListNode(XCHAR* typestr, XCHAR* fathertypeliststr)
{
  if(!typestr) return NULL;

  XDWORD type           = 0;
  XDWORD fathertypelist = 0;

  type = GetTypeFromString(typestr);  
  if(fathertypeliststr)  fathertypelist = GetTypeFromString(fathertypeliststr);
  
  return GetListNode(false, xtreelist.GetRoot(), type, fathertypelist);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILERIFF_LIST_NODE* XFILERIFF::GetChunkNode(XDWORD type, XDWORD fathertypelist)
* @brief      Get chunk node
* @ingroup    XUTILS
*
* @param[in]  type : 
* @param[in]  fathertypelist : 
* 
* @return     XFILERIFF_LIST_NODE* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
 XFILERIFF_LIST_NODE* XFILERIFF::GetChunkNode(XDWORD type, XDWORD fathertypelist)
{
  return GetListNode(true, xtreelist.GetRoot(), type, fathertypelist);
}

 
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILERIFF_LIST_NODE* XFILERIFF::GetChunkNode(XCHAR* typestr, XCHAR* fathertypeliststr)
* @brief      Get chunk node
* @ingroup    XUTILS
*
* @param[in]  typestr : 
* @param[in]  fathertypeliststr : 
* 
* @return     XFILERIFF_LIST_NODE* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XFILERIFF_LIST_NODE* XFILERIFF::GetChunkNode(XCHAR* typestr, XCHAR* fathertypeliststr)
{
  if(!typestr) return NULL;

  XDWORD type           = 0;
  XDWORD fathertypelist = 0;

  type = GetTypeFromString(typestr);  
  if(fathertypeliststr)  fathertypelist = GetTypeFromString(fathertypeliststr);
  
  return GetListNode(true, xtreelist.GetRoot(), type, fathertypelist);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILERIFF_LIST_NODE* XFILERIFF::CreateListNode(XDWORD type, XDWORD typelist)
* @brief      Create list node
* @ingroup    XUTILS
*
* @param[in]  type : 
* @param[in]  typelist : 
* 
* @return     XFILERIFF_LIST_NODE* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XFILERIFF_LIST_NODE* XFILERIFF::CreateListNode(XDWORD type, XDWORD typelist)
{
  XFILERIFF_LIST* list = new XFILERIFF_LIST();
  if(!list) return NULL;

  XFILERIFF_LIST_NODE* node = new XFILERIFF_LIST_NODE(list);
  if(!node)   
    {
      delete list;
      return NULL;
    }

  list->SetType(type);
  list->SetSize(0);
  list->SetTypeList(typelist);

  return node;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILERIFF_LIST_NODE* XFILERIFF::CreateListNode(XCHAR* typestr, XCHAR* typeliststr)
* @brief      Create list node
* @ingroup    XUTILS
*
* @param[in]  typestr : 
* @param[in]  typeliststr : 
* 
* @return     XFILERIFF_LIST_NODE* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XFILERIFF_LIST_NODE* XFILERIFF::CreateListNode(XCHAR* typestr, XCHAR* typeliststr)
{
  if(!typestr) return NULL;

  XDWORD type     = 0;
  XDWORD typelist = 0;

  type = GetTypeFromString(typestr);  
  if(typeliststr)  typelist = GetTypeFromString(typeliststr);
  
  return CreateListNode(type, typelist);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILERIFF_LIST_NODE* XFILERIFF::CreateChunkNode(XDWORD type, XDWORD datasize)
* @brief      Create chunk node
* @ingroup    XUTILS
* 
* @param[in]  type : 
* @param[in]  datasize : 
* 
* @return     XFILERIFF_LIST_NODE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILERIFF_LIST_NODE* XFILERIFF::CreateChunkNode(XDWORD type, XDWORD datasize)
{
  XFILERIFF_LIST* list = new XFILERIFF_LIST();
  if(!list) return NULL;

  XFILERIFF_LIST_NODE* node = new XFILERIFF_LIST_NODE(list);
  if(!node)   
    {
      delete list;
      return NULL;
    }

  list->SetType(type);
  list->SetSize(datasize);
  list->SetTypeList(0);

  return node;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILERIFF_LIST_NODE* XFILERIFF::CreateChunkNode(XCHAR* typestr, XDWORD datasize)
* @brief      Create chunk node
* @ingroup    XUTILS
* 
* @param[in]  typestr : 
* @param[in]  datasize : 
* 
* @return     XFILERIFF_LIST_NODE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILERIFF_LIST_NODE* XFILERIFF::CreateChunkNode(XCHAR* typestr, XDWORD datasize)
{
  if(!typestr) return NULL;

  XDWORD type = 0;
  
  type = GetTypeFromString(typestr);  
   
  return CreateChunkNode(type, datasize);  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILERIFF::UpdateFilePosition(XFILERIFF_LIST_NODE* node)
* @brief      Update file position
* @ingroup    XUTILS
*
* @param[in]  node : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XFILERIFF::UpdateFilePosition(XFILERIFF_LIST_NODE* node)
{
  XQWORD position;

  if(!GetFileBase()->GetPosition(position)) return false;

  node->GetData()->SetPositionFileData(position);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILERIFF::WriteListToFile(XFILERIFF_LIST* list, XBYTE* data, XDWORD datasize)
* @brief      Write list to file
* @ingroup    XUTILS
*
* @param[in]  list : 
* @param[in]  data : 
* @param[in]  datasize : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XFILERIFF::WriteListToFile(XFILERIFF_LIST* list, XBYTE* data, XDWORD datasize)  
{
  if(!list) return false;

  XDWORD listdata[3]  = { 0, 0, 0 };
//XQWORD position = 0;

  if(!xfilebase->SetPosition(list->GetPositionFileData())) return false;

  listdata[0] = list->GetType();
  listdata[1] = list->GetSize();
  
  if(list->IsTypeList())
    {      
      listdata[2] = list->GetTypeList();
      if(!xfilebase->Write((XBYTE*)listdata, (sizeof(XDWORD)*3))) return false;
    }
   else
    {
      listdata[1] = datasize;
      listdata[2] = 0;

      if(!xfilebase->Write((XBYTE*)listdata, (sizeof(XDWORD)*2))) return false;

      if(data && datasize)
        {
          if(!xfilebase->Write(data, datasize)) return false;
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILERIFF_XTREE* XFILERIFF::GetXTreeList()
* @brief      Get X tree list
* @ingroup    XUTILS
*
* @return     XFILERIFF_XTREE* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XFILERIFF_XTREE* XFILERIFF::GetXTreeList()
{
  return &xtreelist;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILE* XFILERIFF::GetFileBase()
* @brief      Get file base
* @ingroup    XUTILS
*
* @return     XFILE* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XFILE* XFILERIFF::GetFileBase()
{
  return xfilebase;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILERIFF::Close()
* @brief      Close
* @ingroup    XUTILS
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XFILERIFF::Close()
{
  if(!xfilebase) return false;

  return xfilebase->Close();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD XFILERIFF::AdjustSizeOfLists(XFILERIFF_LIST_NODE* node)
* @brief      Adjust size of lists
* @ingroup    XUTILS
*
* @param[in]  node : 
* 
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD XFILERIFF::AdjustSizeOfLists(XFILERIFF_LIST_NODE* node)
{
  XFILERIFF_LIST* list        = NULL;
  XDWORD          currentsize = 0;

  list = node->GetData();  
  if(!list)  return 0;

  if(!list->IsTypeList()) return list->GetSize();

  for(int c=0; c<node->GetNChildren(); c++)
    {
      XFILERIFF_LIST_NODE* subnode = node->GetChild(c);
      if(subnode)
        {
          XFILERIFF_LIST* sublist = subnode->GetData();
          if(sublist)
            {
              if(sublist->IsTypeList())
                {
                  currentsize += (AdjustSizeOfLists(subnode) + (sizeof(XDWORD) * 3));
                }
               else 
                {
                  currentsize += (sublist->GetSize() + (sizeof(XDWORD) * 2)); 
                }        
            }
        }
    }

  list->SetSize(currentsize + sizeof(XDWORD));

  if(!WriteListToFile(list)) return false; 

  return currentsize;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILERIFF::ConvertDWORDtoString(XDWORD data, XSTRING& string);
* @brief      Convert DWOR dto string
* @ingroup    XUTILS
*
* @param[in]  data : 
* @param[in]  string) : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XFILERIFF::ConvertDWORDtoString(XDWORD data, XSTRING& string)
{
  XCHAR characters[4] = { 0, 0 ,0 ,0 };

  characters[0] = (XCHAR)((data >> 24) & 0x000000FF);
  characters[1] = (XCHAR)((data >> 16) & 0x000000FF);
  characters[2] = (XCHAR)((data >> 8)  & 0x000000FF);
  characters[3] = (XCHAR)((data)       & 0x000000FF);

  string.Format(__L("%C%C%C%C"),  characters[3], characters[2], characters[1], characters[0]);

  string.ToUpperCase();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILERIFF_LIST* XFILERIFF::GetList(bool search_chunk, XFILERIFF_LIST_NODE* listnode, XDWORD type, XDWORD fathertypelist)
* @brief      Get list
* @ingroup    XUTILS
*
* @param[in]  search_chunk : 
* @param[in]  listnode : 
* @param[in]  type : 
* @param[in]  fathertypelist : 
* 
* @return     XFILERIFF_LIST* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XFILERIFF_LIST* XFILERIFF::GetList(bool search_chunk, XFILERIFF_LIST_NODE* listnode, XDWORD type, XDWORD fathertypelist)
{
  if(!listnode) return NULL;

  XFILERIFF_LIST* listriff = listnode->GetData();
  if(listriff)
    {
      if(listriff->IsTypeList() != search_chunk)
        {         
          if(fathertypelist  && listnode->GetParent())
            {
              XFILERIFF_LIST_NODE* fatherlistnode = listnode->GetParent();
              if(fatherlistnode)
                {
                  XFILERIFF_LIST* fatherlistriff = fatherlistnode->GetData();
                  if(fatherlistriff)
                    {
                      if(fatherlistriff->GetTypeList() == fathertypelist)
                        {
                          if(search_chunk)
                            {
                              if(listriff->GetType() == type) 
                                {
                                  return listriff;
                                }
                            }
                           else
                            {
                              if(listriff->GetTypeList() == type) 
                                {
                                  return listriff;
                                }
                            }           
                        }                        
                    }
                }
            }
           else
            { 
              if(search_chunk)
                {
                  if(listriff->GetType() == type) 
                    {
                      return listriff;
                    }
                }
               else
                {
                  if(listriff->GetTypeList() == type) 
                    {
                      return listriff;
                    }
                }              
            }                     
        }
    }

  for(XDWORD c=0; c<listnode->GetChildren()->GetSize(); c++)
    {
      XFILERIFF_LIST_NODE* listsubnode = listnode->GetChildren()->Get(c);
      if(listsubnode) 
        {
          XFILERIFF_LIST* sublistriff = GetList(search_chunk, listsubnode, type, fathertypelist);
          if(sublistriff)  return sublistriff;  
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILERIFF_LIST_NODE* XFILERIFF::GetListNode(bool search_chunk, XFILERIFF_LIST_NODE* listnode, XDWORD type, XDWORD fathertypelist)
* @brief      Get list node
* @ingroup    XUTILS
*
* @param[in]  search_chunk : 
* @param[in]  listnode : 
* @param[in]  type : 
* @param[in]  fathertypelist : 
* 
* @return     XFILERIFF_LIST_NODE* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XFILERIFF_LIST_NODE* XFILERIFF::GetListNode(bool search_chunk, XFILERIFF_LIST_NODE* listnode, XDWORD type, XDWORD fathertypelist)
{
  if(!listnode) return NULL;

  XFILERIFF_LIST* listriff = listnode->GetData();
  if(listriff)
    {
      if(listriff->IsTypeList() != search_chunk)
        {         
          if(fathertypelist  && listnode->GetParent())
            {
              XFILERIFF_LIST_NODE* fatherlistnode = listnode->GetParent();
              if(fatherlistnode)
                {
                  XFILERIFF_LIST* fatherlistriff = fatherlistnode->GetData();
                  if(fatherlistriff)
                    {
                      if(fatherlistriff->GetTypeList() == fathertypelist)
                        {
                          if(search_chunk)
                            {
                              if(listriff->GetType() == type) 
                                {
                                  return listnode;
                                }
                            }
                           else
                            {
                              if(listriff->GetTypeList() == type) 
                                {
                                  return listnode;
                                }
                            }           
                        }                        
                    }
                }
            }
           else
            { 
              if(search_chunk)
                {
                  if(listriff->GetType() == type) 
                    {
                      return listnode;
                    }
                }
               else
                {
                  if(listriff->GetTypeList() == type) 
                    {
                      return listnode;
                    }
                }              
            }                     
        }
    }

  for(XDWORD c=0; c<listnode->GetChildren()->GetSize(); c++)
    {
      XFILERIFF_LIST_NODE* sublistnode = listnode->GetChildren()->Get(c);
      if(sublistnode) 
        {
          XFILERIFF_LIST_NODE* sub2listnode = GetListNode(search_chunk, sublistnode, type, fathertypelist);
          if(sub2listnode)  return sub2listnode;  
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XFILERIFF::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* ---------------------------------------------------------------------------------------------------------------------*/
void XFILERIFF::Clean()
{
  xfilebase     = NULL;

  iscreatefile  = false;
}


#pragma endregion


#pragma endregion

