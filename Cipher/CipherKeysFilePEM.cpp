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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "CipherKeysFilePEM.h"

#include "XBuffer.h"
#include "XBER_XEvent.h"
#include "XBER.h"
#include "XFileTXT.h"
#include "XTrace.h"

#include "CipherKey.h"
#include "CipherKeyCertificate.h"

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
* @fn         CIPHERKEYSFILEPEM::CIPHERKEYSFILEPEM()
* @brief      Constructor
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEYSFILEPEM::CIPHERKEYSFILEPEM()
{
  Clean();
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
  Key_DelAll();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSFILEPEM::Key_Add(CIPHERKEY* key)
* @brief      Key_Add
* @ingroup    CIPHER
* 
* @param[in]  key : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSFILEPEM::Key_Add(CIPHERKEY* key)
{
  if(!key)
    {
      return false;
    }

  return keys.Add(key);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSFILEPEM::Key_Del(CIPHERKEY* key)
* @brief      Key_Del
* @ingroup    CIPHER
* 
* @param[in]  key : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSFILEPEM::Key_Del(CIPHERKEY* key)
{
  if(!key)
    {
      return false;
    }

  keys.Delete(key);
  delete key;
 
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSFILEPEM::Key_DelAll()
* @brief      Key_DelAll
* @ingroup    CIPHER
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSFILEPEM::Key_DelAll()
{
  if(keys.IsEmpty()) 
    {
      return false;
    }

  keys.DeleteContents();
  keys.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSFILEPEM::ReadDecodeAllFile(XPATH& xpath)
* @brief      ReadDecodeAllFile
* @ingroup    CIPHER
* 
* @param[in]  xpath : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSFILEPEM::ReadDecodeAllFile(XPATH& xpath)
{
  XFILETXT*                               xfiletxt;
  XVECTOR<CIPHERKEYSFILEPEM_ENTRYBUFFER*> entrysbuffer;
  CIPHERKEYSFILEPEM_ENTRYBUFFER*          entrybuffer = NULL;
    
  xfiletxt = new XFILETXT();
  if(!xfiletxt) 
    {
      return false;
    }

  if(!xfiletxt->Open(xpath))  
    {
      return false;
    }

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
          decodekey = NULL;
         
          if(!entrybuffer->type.Compare(__L("CERTIFICATE")))
            {
              decodekey = (CIPHERKEY*) new CIPHERKEYCERTIFICATE();  
            }

          if(decodekey)
            {
              if(asn1.Decode(entrybuffer->data, this))
                {
                  Key_Add(decodekey);
                } 
               else
                {
                  delete decodekey;
                }   
            }
        }  
    }


  entrysbuffer.DeleteContents();
  entrysbuffer.DeleteAll();

  xfiletxt->Close();

  delete xfiletxt;

  xfiletxt = NULL;

  return true;
}

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSFILEPEM::DecodeCertificates(CIPHERROOTCERTIFICATES certificates, int nlinescertificates)
* @brief      DecodeCertificates
* @ingroup    CIPHER
* 
* @param[in]  certificates : 
* @param[in]  nlinescertificates : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSFILEPEM::DecodeCertificates(CIPHERROOTCERTIFICATES certificates, int nlinescertificates)
{
  XVECTOR<CIPHERKEYSFILEPEM_ENTRYBUFFER*> entrysbuffer;
  CIPHERKEYSFILEPEM_ENTRYBUFFER*          entrybuffer = NULL;
  XSTRING                                 line;
  
  for(XDWORD c=0; c<nlinescertificates; c++)
    {
      XCHAR*  _line = certificates[c];     
      int     ini;
      int     end;    

      line = _line;

      ini = line.Find(CIPHERKEYSFILEPEM_BEGINKEY, true);
      if(ini != XSTRING_NOTFOUND)
        {
          ini += XSTRING::GetSize(CIPHERKEYSFILEPEM_BEGINKEY);

          if(!entrybuffer)
            {
              entrybuffer = new CIPHERKEYSFILEPEM_ENTRYBUFFER(); 
              if(entrybuffer)
                {
                  entrybuffer->ini_line = c+1;  
                  end = line.Find(CIPHERKEYSFILEPEM_FINISH, true, ini);
                  if(end != XSTRING_NOTFOUND)
                    {
                      entrybuffer->type.AdjustSize(_MAXSTR);                                                                  
                      line.Copy(ini, end, entrybuffer->type);
                      entrybuffer->type.AdjustSize();                
                    }
                }
            }
        }

      ini = line.Find(CIPHERKEYSFILEPEM_ENDKEY, true);
      if(ini != XSTRING_NOTFOUND)
        {
          ini += XSTRING::GetSize(CIPHERKEYSFILEPEM_ENDKEY);

          if(entrybuffer)
            {
              entrybuffer->end_line = c;                          
              end = line.Find(CIPHERKEYSFILEPEM_FINISH, true, ini);
              if(end != XSTRING_NOTFOUND)
                {
                  XSTRING type;  

                  type.AdjustSize(_MAXSTR);                                                                  
                  line.Copy(ini, end, type);
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

  for(XDWORD c=0; c<entrysbuffer.GetSize(); c++)
    {
      CIPHERKEYSFILEPEM_ENTRYBUFFER* entrybuffer = entrysbuffer.Get(c);
      if(entrybuffer)
        {
          XSTRING datastr;

          XSTRING datastr1;

          for(int d=entrybuffer->ini_line; d<entrybuffer->end_line; d++)
            {
              datastr += certificates[d];                                 
            }

          entrybuffer->data.ConvertFromBase64(datastr); 
        }
    }

  XASN1 asn1;
    
  for(XDWORD c=0; c< 1 /*entrysbuffer.GetSize()*/; c++)
    {
      CIPHERKEYSFILEPEM_ENTRYBUFFER* entrybuffer = entrysbuffer.Get(c);

      if(entrybuffer)
        {
          decodekey = NULL;
         
          if(!entrybuffer->type.Compare(__L("CERTIFICATE")))
            {
              decodekey = (CIPHERKEY*) new CIPHERKEYCERTIFICATE();  
            }

          if(decodekey)
            {
              if(asn1.Decode(entrybuffer->data, this))
                {
                  Key_Add(decodekey);
                } 
               else
                {
                  delete decodekey;
                }   
            }
        }  
    }

  entrysbuffer.DeleteContents();
  entrysbuffer.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CIPHERKEYSFILEPEM::HandleEvent_XBER(XBER_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    CIPHER
* 
* @param[in]  event : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CIPHERKEYSFILEPEM::HandleEvent_XBER(XBER_XEVENT* event)
{  
  if(!decodekey)
    {
      return;
    }
    
  switch(event->GetEventType())
    {
      case XBERXEVENT_TYPE_DECODE_START   : XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Cipher Keys File PEM] Start [%d]"), decodekey->GetType());
                                            break;

      case XBERXEVENT_TYPE_DECODE_DATA    : { XSTRING levelsstr;

                                              levelsstr = event->GetLevelsString()->Get();

                                              if(decodekey->GetType() == CIPHERKEYTYPE_CERTIFICATE)
                                                {
                                                  CIPHERKEYCERTIFICATE* certificate = (CIPHERKEYCERTIFICATE*)decodekey;

                                                  // Version 
                                                  if(!levelsstr.Compare(__L("1.1.1.1")))
                                                    {
                                                      certificate->SetVersion((XWORD)event->GetData()->Get()[0]);
                                                    }

                                                  // Serial
                                                  if(!levelsstr.Compare(__L("1.1.2")))
                                                    {
                                                      certificate->GetSerial()->CopyFrom((*event->GetData()));
                                                    }

                                                  // Algorithm type
                                                  if(!levelsstr.Compare(__L("1.1.3.1")))
                                                    {
                                                      certificate->SetAlgorithmType(event->GetProperty()->OID);
                                                    }

                                                  // Date Not Before
                                                  if(!levelsstr.Compare(__L("1.1.5.1")))
                                                    {
                                                      XVARIANT* value;
                                                      XSTRING   valuestr;  

                                                      value     = (XVARIANT*)event->GetValue();
                                                      valuestr  = (XSTRING)(*value);

                                                      certificate->ConvertDateTime(valuestr.Get(), certificate->GetDateNotBefore());   
                                                    }

                                                  // Date Not After
                                                  if(!levelsstr.Compare(__L("1.1.5.2")))
                                                    {
                                                      XVARIANT* value;
                                                      XSTRING   valuestr;  

                                                      value     = (XVARIANT*)event->GetValue();
                                                      valuestr  = (XSTRING)(*value);

                                                      certificate->ConvertDateTime(valuestr.Get(), certificate->GetDateNotAfter());       
                                                    }

                                                  if(event->GetBeforeEvent()->GetTagType() == XBER_TAGTYPE_OBJECT_IDENTIFIER)
                                                    {
                                                      XSTRING   _OID;
                                                      XVARIANT* value;

                                                      _OID = event->GetBeforeEvent()->GetProperty()->OID;
                                                      
                                                      value = (XVARIANT*)event->GetValue();
  
                                                      if(!_OID.Compare(__L("2.5.4.6"), false))
                                                        {
                                                          certificate->GetCountryName()->Set((XSTRING)(*value));  
                                                        }

                                                      if(!_OID.Compare(__L("2.5.4.10"), false))
                                                        {
                                                          certificate->GetOrganizationName()->Set((XSTRING)(*value));  
                                                        }

                                                      if(!_OID.Compare(__L("2.5.4.11"), false))
                                                        {
                                                          certificate->GetOrganizationalUnitName()->Set((XSTRING)(*value));  
                                                        }

                                                      if(!_OID.Compare(__L("2.5.4.3"), false))
                                                        {
                                                          certificate->GetCommonName()->Set((XSTRING)(*value));  
                                                        }
                                                    }
                                                }

                                              levelsstr.AddFormat(__L(" %s"), event->GetLine()->Get());                                          

                                              XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, levelsstr.Get(), NULL);                                                         
                                            }
                                            break;

      case XBERXEVENT_TYPE_DECODE_END     : XTRACE_PRINTCOLOR((event->GetStatus()?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[Cipher Keys File PEM] End"));                                              
                                            break;

    } 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CIPHERKEYSFILEPEM::HandleEvent(XEVENT* xevent)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    CIPHER
* 
* @param[in]  xevent : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CIPHERKEYSFILEPEM::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_XBER             : { XBER_XEVENT* event = (XBER_XEVENT*)xevent;
                                            if(!event) return;

                                            HandleEvent_XBER(event);
                                          }
                                          break;
    }
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
  decodekey = NULL;
}


#pragma endregion


#pragma endregion

