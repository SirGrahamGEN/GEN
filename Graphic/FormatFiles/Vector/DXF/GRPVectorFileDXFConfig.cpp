#pragma region INCLUDES

#include "XPath.h"
#include "XFileINI.h"
#include "XFileCFG.h"

#include "GRPVectorFileDXF.h"

#include "GRPVECTORFILEDXFConfig.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFConfig::GRPVECTORFILEDXFConfig ( )
{
   Clean();

   fileCFG = new XFILECFG();
}


GRPVECTORFILEDXFConfig::~GRPVECTORFILEDXFConfig ( )
{
   if(fileCFG)
   {
      delete fileCFG;
   }

   Clean();
}


GRPVECTORFILEDXFTextSectionHeader* GRPVECTORFILEDXFConfig::GetHeader ( )
{
   return header;
}


bool GRPVECTORFILEDXFConfig::SetHeader ( GRPVECTORFILEDXFTextSectionHeader* header)
{
   this->header = header;

   fileCFG->DeleteAllValues();

   for(XDWORD c=0; c<header->GetVariables()->GetSize(); c++)
   {   
      XSTRING* namekey = header->GetVariables()->GetKey(c);
      XVARIANT* variant = header->GetVariables()->GetElement(c);
      
      if(namekey && variant)
      {
         switch(variant->GetType())
         {         
            case XVARIANT_TYPE_BOOLEAN        : fileCFG->AddValue(XFILECFG_VALUETYPE_BOOLEAN, VECTORFILEDXFCONFIG_SECTION_DFX_CFG, namekey->Get(), (bool*)(variant->GetData()));         
                                                break;

            case XVARIANT_TYPE_INTEGER        : fileCFG->AddValue(XFILECFG_VALUETYPE_INT, VECTORFILEDXFCONFIG_SECTION_DFX_CFG, namekey->Get(), (int*)(variant->GetData()));         
                                                break;

            case XVARIANT_TYPE_FLOAT          : fileCFG->AddValue(XFILECFG_VALUETYPE_FLOAT, VECTORFILEDXFCONFIG_SECTION_DFX_CFG, namekey->Get(), (float*)(variant->GetData()));     
                                                break;

            case XVARIANT_TYPE_STRING         : fileCFG->AddValue(XFILECFG_VALUETYPE_STRING, VECTORFILEDXFCONFIG_SECTION_DFX_CFG, namekey->Get(), (XSTRING*)(variant->GetData()));  
                                                break;

            case XVARIANT_TYPE_NULL           :
            case XVARIANT_TYPE_DOUBLEINTEGER  :            
            case XVARIANT_TYPE_DOUBLE         :
            case XVARIANT_TYPE_CHAR           :
            case XVARIANT_TYPE_XCHAR          :            
            case XVARIANT_TYPE_DATE           :
            case XVARIANT_TYPE_TIME           :
            case XVARIANT_TYPE_DATETIME       : 
                                  default     : return false;
                                                break;
         }         

         {  XCHAR* remark = NULL;
            remark = header->GetVariableRemark((*namekey));

            if(remark) 
            {
               fileCFG->AddRemark(VECTORFILEDXFCONFIG_SECTION_DFX_CFG, namekey->Get(), remark, 64, 0);
            }
         }
      }   
   }

   return true;
}


bool GRPVECTORFILEDXFConfig::Create_File (XCHAR* pathFile)
{
   if(!fileCFG) return false;

   XPATH path;
   
   path = pathFile;

   return fileCFG->Save(path);
}


bool GRPVECTORFILEDXFConfig::Load_File (XCHAR* pathFile)
{
   if(!fileCFG) return false;
   if(!header)  return false;

   XPATH path;
   bool status = false;
   
   path = pathFile;

   header->DeleteAllVariables();

   fileCFG->DeleteAllValues();

   if(fileCFG->IniFile(path)) 
   {
      fileCFG->AjustRemarks();

      XFILEINISECTION* sectionINI = fileCFG->GetFileINI()->GetSection(VECTORFILEDXFCONFIG_SECTION_DFX_CFG);
      if(sectionINI)
        {
          XSTRING key;
          
          XSTRING value;

          while(sectionINI->GetNextKey(key, value))
            {
               XVARIANT variant;
               XSTRING  trash;                              
               int      type = 0;

               trash.AdjustSize(_MAXSTR);

               key.UnFormat(__L("$%s_%d"), trash.Get(), &type, NULL);

               GRPVECTORFILEDXFTextSection::GetVariableFromLine(trash.Get(), type, &value, variant);
                           
               if(variant.GetType() != XVARIANT_TYPE_NULL)   
               {
                  header->AddVariable(key.Get(), &variant);
               }
            }
        }
       
     //status = fileCFG->EndFile();

     fileCFG->GetFileINI()->XFILETXT::Close();
     fileCFG->DeleteAllRemarks();
   }

   #ifdef XTRACE_ACTIVE
   header->ShowTraceAllVariables();
   #endif

   return status;
}


void GRPVECTORFILEDXFConfig::Clean ( )
{
  header    = NULL;

  pathFile.Empty();

  fileCFG   = NULL;
}

#pragma endregion
