/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONode.cpp
* 
* @class      DIONODE
* @brief      Data Input/Output NODE (Base class for a control of nodes) class
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIONode.h"

#include "DIONodeItem.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODE::DIONODE()
* @brief      Constructor
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODE::DIONODE()
{
  Clean();
  
  UUID.GenerateRandom();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODE::~DIONODE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODE::~DIONODE()
{
  items.DeleteContents();
  items.DeleteAll();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XUUID& DIONODE::GetID()
* @brief      GetID
* @ingroup    DATAIO
* 
* @return     XUUID& : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XUUID& DIONODE::GetID()
{
  return UUID;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODE::SetID(XUUID& UUID)
* @brief      SetID
* @ingroup    DATAIO
* 
* @param[in]  UUID : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODE::SetID(XUUID& UUID)
{
  this->UUID.CopyFrom(UUID);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<DIONODEITEM*>* DIONODE::GetItems()
* @brief      GetItems
* @ingroup    DATAIO
* 
* @return     XVECTOR<DIONODEITEM*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<DIONODEITEM*>* DIONODE::GetItems()
{
  return &items;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODE::IsLocal()
* @brief      IsLocal
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODE::IsLocal()
{
  return islocal;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODE::SetIsLocal(bool islocal)
* @brief      SetIsLocal
* @ingroup    DATAIO
* 
* @param[in]  islocal : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODE::SetIsLocal(bool islocal)
{
  this->islocal = islocal;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIONODE::GetGroup()
* @brief      GetGroup
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIONODE::GetGroup()
{
  return &group;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODE::GetSubGroups(XVECTOR<XSTRING*>& listsubgroups)
* @brief      GetSubGroups
* @ingroup    DATAIO
* 
* @param[in]  listsubgroups : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODE::GetSubGroups(XVECTOR<XSTRING*>& listsubgroups)
{  
  XPATH pathgroup;  

  pathgroup = group.Get();  
  
  pathgroup.Slash_Delete();

  do{ XSTRING* _subgroup = new XSTRING();
      if(_subgroup)
        {
          pathgroup.GetNamefileExt(*_subgroup);        
          pathgroup.GetPath(pathgroup);

          if(!_subgroup->Compare(pathgroup, true))
            {
              listsubgroups.Insert(0, _subgroup); 
              break;
            }

          pathgroup.Slash_Delete();

          if(_subgroup->IsEmpty())
            {
              delete _subgroup;
              break;
            }
           else 
            {
              listsubgroups.Insert(0, _subgroup);
            }       
        } 
       else 
        {
          break;
        }

   } while(1);

  
  return listsubgroups.IsEmpty()?false:true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODE::GetSubGroup(XDWORD level, XSTRING& subgroup)
* @brief      GetSubGroup
* @ingroup    DATAIO
* 
* @param[in]  level : 
* @param[in]  subgroup : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODE::GetSubGroup(XDWORD level, XSTRING& subgroup)
{
  subgroup.Empty();

  XVECTOR<XSTRING*> listsubgroups;
  bool              status;  

  if(!GetSubGroups(listsubgroups))
    {
      return false;
    }

  if(level < listsubgroups.GetSize())
    {
      subgroup = listsubgroups.Get(level)->Get();
      status = true;
    }

  listsubgroups.DeleteContents();
  listsubgroups.DeleteAll();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODE::Update()
* @brief      Update
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODE::Update()
{
  for(XDWORD c=0; c<items.GetSize(); c++)
    {
      DIONODEITEM* item = items.Get(c);
      if(item)
        {
          item->Update();
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODE::CreateJSONSerialization()
* @brief      CreateJSONSerialization
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODE::CreateJSONSerialization()
{
  XFILEJSON             xfileJSON;
  XSERIALIZATIONMETHOD* serializationmethod;
  XSTRING               string;

  serializationmethod = XSERIALIZABLE::CreateInstance(xfileJSON);
  if(!serializationmethod) return false;
  
  InitSerialize(serializationmethod);

  XPATH path;
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, path);
  path += __L("test.json");

  if(xfileJSON.Create(path))
    {
      xfileJSON.WriteAndEncodeAllLines(true);
      xfileJSON.Close();
    }

  xfileJSON.EncodeAllLines();
  xfileJSON.GetAllInOneLine(string, XFILETXTTYPELF_DEFAULT);
  xfileJSON.ShowTraceJSON(XTRACE_COLOR_PURPLE);

  delete serializationmethod;
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODE::Serialize()
* @brief      Serialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODE::Serialize()
{  
  XSTRING ID;
 
  UUID.GetToString(ID); 

  Primitive_Add<XSTRING*>(&ID, __L("ID"));
  Primitive_Add<XSTRING*>(&group, __L("group"));
  XVectorClass_Add<DIONODEITEM>(&items, __L("items"), __L("item"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODE::Deserialize()
* @brief      Deserialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODE::Deserialize()
{
  XSTRING ID;

  Primitive_Extract<XSTRING*>(&ID, __L("ID"));
  Primitive_Extract<XSTRING*>(&group, __L("group"));
  XVectorClass_Extract<DIONODEITEM>(&items, __L("items"), __L("item"));

  UUID.SetFromString(ID);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODE::Clean()
{
  islocal = false;
  
}


#pragma endregion

