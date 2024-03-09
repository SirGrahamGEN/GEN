/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       CipherKeysFilePEM.cpp
* 
* @class      CIPHERKEYSFILEPEM
* @brief      Cipher File Keys PEM (GEN Key File) class
* @ingroup    CIPHER
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

#include "CipherKeysFilePEM.h"

#include "XBuffer.h"
#include "XBER.h"
#include "XFileTXT.h"
#include "XTrace.h"

#include "CipherKey.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#pragma region CIPHERKEYSFILEPEM_TYPECERTIFICATE


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEYSFILEPEM_TYPECERTIFICATE::CIPHERKEYSFILEPEM_TYPECERTIFICATE()
* @brief      Constructor
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEYSFILEPEM_TYPECERTIFICATE::CIPHERKEYSFILEPEM_TYPECERTIFICATE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEYSFILEPEM_TYPECERTIFICATE::~CIPHERKEYSFILEPEM_TYPECERTIFICATE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEYSFILEPEM_TYPECERTIFICATE::~CIPHERKEYSFILEPEM_TYPECERTIFICATE()
{
  Clean();
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CIPHERKEYSFILEPEM_TYPECERTIFICATE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CIPHERKEYSFILEPEM_TYPECERTIFICATE::Clean()
{

}


#pragma endregion


#pragma region CIPHERKEYSFILEPEM


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEYSFILEPEM::CIPHERKEYSFILEPEM(XPATH& xpath)
* @brief      Constructor
* @ingroup    CIPHER
* 
* @param[in]  XPATH& : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEYSFILEPEM::CIPHERKEYSFILEPEM(XPATH& xpath)
{
  Clean();

  this->xpath  = xpath;

  xfiletxt = new XFILETXT();
  if(!xfiletxt) return;

  ReadAllFile();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEYSFILEPEM::~CIPHERKEYSFILEPEM()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEYSFILEPEM::~CIPHERKEYSFILEPEM()
{
  DeleteAllKeys();

  if(xfiletxt) 
    {
      delete xfiletxt;
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSFILEPEM::HaveKey(CIPHERKEYTYPE type)
* @brief      HaveKey
* @ingroup    CIPHER
* 
* @param[in]  type : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSFILEPEM::HaveKey(CIPHERKEYTYPE type)
{
  for(int c=0; c<(int)keys.GetSize(); c++)
    {
      CIPHERKEY* key = keys.Get(c);
      if(key)
        {
          if(key->GetType() == type)  return true;
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEY* CIPHERKEYSFILEPEM::GetKey(CIPHERKEYTYPE type)
* @brief      GetKey
* @ingroup    CIPHER
* 
* @param[in]  type : 
* 
* @return     CIPHERKEY* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEY* CIPHERKEYSFILEPEM::GetKey(CIPHERKEYTYPE type)
{
  for(int c=0; c<(int)keys.GetSize(); c++)
    {
      CIPHERKEY* key = keys.Get(c);
      if(key)
        {
          if(key->GetType() == type)  return key;
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSFILEPEM::AddKey(CIPHERKEY& key)
* @brief      AddKey
* @ingroup    CIPHER
* 
* @param[in]  key : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSFILEPEM::AddKey(CIPHERKEY& key)
{
  if(HaveKey(key.GetType())) return false;

  switch(key.GetType())
    {
      case CIPHERKEYTYPE_UNKNOWN        : break;

      case CIPHERKEYTYPE_SYMMETRICAL    : break;

      case CIPHERKEYTYPE_PUBLIC         : break;

      case CIPHERKEYTYPE_PRIVATE        : break;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSFILEPEM::DeleteKey(CIPHERKEYTYPE type)
* @brief      DeleteKey
* @ingroup    CIPHER
* 
* @param[in]  type : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSFILEPEM::DeleteKey(CIPHERKEYTYPE type)
{
  for(int c=0; c<(int)keys.GetSize(); c++)
    {
      CIPHERKEY* key = keys.Get(c);
      if(key)
        {
          if(key->GetType() == type)
            {
              keys.Delete(key);
              delete key;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSFILEPEM::DeleteAllKeys()
* @brief      DeleteAllKeys
* @ingroup    CIPHER
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSFILEPEM::DeleteAllKeys()
{
  if(keys.IsEmpty()) return false;

  keys.DeleteContents();

  keys.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XPATH& CIPHERKEYSFILEPEM::GetXPath()
* @brief      GetXPath
* @ingroup    CIPHER
* 
* @return     XPATH& : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XPATH& CIPHERKEYSFILEPEM::GetXPath()
{ 
  return xpath;                           
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILETXT* CIPHERKEYSFILEPEM::GetXFileTXT()
* @brief      GetXFileTXT
* @ingroup    CIPHER
* 
* @return     XFILETXT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILETXT* CIPHERKEYSFILEPEM::GetXFileTXT()
{ 
  return xfiletxt;                        
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSFILEPEM::ReadAllFile()
* @brief      ReadAllFile
* @ingroup    CIPHER
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSFILEPEM::ReadAllFile()
{
  typedef struct
  {
    XSTRING   type;
    XDWORD    ini_line;
    XDWORD    end_line;
    XBUFFER   data;  

  } CIPHERKEYSFILEPEM_ENTRYBUFFER ;

  XVECTOR<CIPHERKEYSFILEPEM_ENTRYBUFFER*> entrysbuffer;
  CIPHERKEYSFILEPEM_ENTRYBUFFER*          entrybuffer = NULL;
  
  if(!xfiletxt) return false;

  if(!xfiletxt->Open(xpath))  return false;

  xfiletxt->ReadAllFile();

  for(XDWORD c=0; c<xfiletxt->GetNLines(); c++)
    {
      XSTRING* line = xfiletxt->GetLine(c); 
      if(line)
        {          
          int ini;
          int end;

          ini = line->Find(CIPHERKEYSFILEPEM_BEGINKEY, true);
          if(ini != XSTRING_NOTFOUND)
            {
              ini += XSTRING::GetSize(CIPHERKEYSFILEPEM_BEGINKEY);

              if(!entrybuffer)
                {
                  entrybuffer = new CIPHERKEYSFILEPEM_ENTRYBUFFER(); 
                  if(entrybuffer)
                    {
                      entrybuffer->ini_line = c+1;  
                      end = line->Find(CIPHERKEYSFILEPEM_FINISH, true, ini);
                      if(end != XSTRING_NOTFOUND)
                        {
                          entrybuffer->type.AdjustSize(_MAXSTR);                                                                  
                          line->Copy(ini, end, entrybuffer->type);
                          entrybuffer->type.AdjustSize();                
                        }
                    }
                }
            }

          ini = line->Find(CIPHERKEYSFILEPEM_ENDKEY, true);
          if(ini != XSTRING_NOTFOUND)
            {
              ini += XSTRING::GetSize(CIPHERKEYSFILEPEM_ENDKEY);

              if(entrybuffer)
                {
                  entrybuffer->end_line = c;                          
                  end = line->Find(CIPHERKEYSFILEPEM_FINISH, true, ini);
                  if(end != XSTRING_NOTFOUND)
                    {
                      XSTRING type;  

                      type.AdjustSize(_MAXSTR);                                                                  
                      line->Copy(ini, end, type);
                      type.AdjustSize();  

                      if(!type.Compare(entrybuffer->type))
                        {
                          entrysbuffer.Add(entrybuffer);  
                          entrybuffer = NULL;
                        }                                   
                    }      
                }  
            }
        }   
   }

  for(XDWORD c=0; c<entrysbuffer.GetSize(); c++)
    {
      CIPHERKEYSFILEPEM_ENTRYBUFFER* entrybuffer = entrysbuffer.Get(c);
      if(entrybuffer)
        {
          XSTRING datastr;

          XSTRING datastr1;

          for(int d=entrybuffer->ini_line; d<entrybuffer->end_line; d++)
            {
              datastr += xfiletxt->GetLine(d)->Get();                                 
            }

          entrybuffer->data.ConvertFromBase64(datastr); 
        }
    }


  XASN1 asn1;
    
  for(XDWORD c=0; c<entrysbuffer.GetSize(); c++)
    {
      CIPHERKEYSFILEPEM_ENTRYBUFFER* entrybuffer = entrysbuffer.Get(c);

      if(entrybuffer)
        {
          CIPHERKEYSFILEPEM_TYPECERTIFICATE certificate;

          XTRACE_PRINTHEADER(__L("Certificate"));  

          asn1.Decode(entrybuffer->data);
          
          XTRACE_PRINTHEADER(NULL);  
        }  
    }


  entrysbuffer.DeleteContents();
  entrysbuffer.DeleteAll();

  xfiletxt->Close();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CIPHERKEYSFILEPEM::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CIPHERKEYSFILEPEM::Clean()
{
  xfiletxt  = NULL;
}


#pragma endregion


#pragma endregion

