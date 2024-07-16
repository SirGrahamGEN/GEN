
#pragma region INCLUDES

#include "XFactory.h"
#include "XTimer.h"
#include "XTrace.h"
#include "XFileTXT.h"
#include "XVariant.h"

#include "GRPVECTORFILE_XEVENT.h"
#include "GRPVECTORFILEDXFTextBlock.h"
#include "GRPVECTORFILEDXFTextSectionBlocks.h"
#include "GRPVECTORFILEDXFTextSectionEntities.h"
#include "GRPVECTORFILEDXFTextSectionHeader.h"

#include "GRPVectorFileDXF.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS


GRPVECTORFILEDXF::GRPVECTORFILEDXF ( )
{
   Clean ();
}


GRPVECTORFILEDXF::~GRPVECTORFILEDXF ( )
{
   sections.DeleteContents();
   sections.DeleteAll();

   Clean ();
}


GRPVECTORFILERESULT GRPVECTORFILEDXF::DetectType ( )
{  
   GRPVECTORFILERESULT result;

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
      return GRPVECTORFILERESULT_ERRORNOTFILE;  
   }

   if(!extension.Compare(GRPVECTORFILEDXF_Extension, true))
   {
      type = VECTORFILETYPE_DXF;  
   }
  
   if(DetectFileFormatText(pathFile))
   {
      XFILETXT* file = new XFILETXT();
      if(file)  
      {
         if(file->Open(pathFile))
         {
            int nlines = 100;

            file->ReadNLines(nlines);

            nlines = file->GetNLines();

            if(ParserHaveAnySection(file, nlines))
            {
               result = GRPVECTORFILERESULT_OK; 
            }
            else
            {
               result = GRPVECTORFILERESULT_ErrorInvalidFormat;   
            }        
 
            file->Close();             

         } else result = GRPVECTORFILERESULT_ERRORNOTFILE;

         delete file;

      } else result = GRPVECTORFILERESULT_ERRORNOTMEMORY;

   } else result = GRPVECTORFILERESULT_ErrorInvalidFormat; 

   return result;
}


GRPVECTORFILERESULT GRPVECTORFILEDXF::Load ( )
{
   GRPVECTORFILEDXFResult result = GRPVECTORFILERESULT_ERRORNOTMEMORY;

   XFILETXT* file = new XFILETXT();
   if(!file)  return GRPVECTORFILERESULT_ERRORNOTMEMORY;

   if(file->Open(pathFile))
   {
      XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
      if(xtimer)
      {
         //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Reading TXT file ..."));

         xtimer->Reset();
      
         file->ReadAllFile();      

         //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Read TXT file: %ld Milliseconds."), xtimer->GetMeasureMilliSeconds());   

         GEN_XFACTORY.DeleteTimer(xtimer);
      }
   
      result = ParserTextFile (file);
    
      file->Close();    
   } 
   else 
   {
      result = GRPVECTORFILERESULT_ERRORNOTFILE;
   }

   delete file;

   return result.TakeAsBase();
}


GRPVECTORFILECONFIG* GRPVECTORFILEDXF::GetConfig ( )
{
   return (GRPVECTORFILECONFIG*)&config;
}


XVECTOR<GRPVECTORFILEDXFTextSection*>* GRPVECTORFILEDXF::GetSections()
{
   return &sections;
}

GRPVECTORFILEDXFTextSection* GRPVECTORFILEDXF::GetSection (GRPVECTORFILEDXFTextSection_TypeSection type)
{
   for(XDWORD c=0; c<sections.GetSize(); c++)
   {
      GRPVECTORFILEDXFTextSection* section = sections.Get(c);
      if(section)
      {
        if(section->type == type) return section;
      }
   }

   return NULL;
}


bool GRPVECTORFILEDXF::ParserTextFilePrepareLine(XSTRING* line)
{
   if(!line) return false;
   if(line->IsEmpty()) return false;

   line->DeleteCharacter(__C(' '), XSTRINGCONTEXT_FROM_FIRST);
   line->DeleteCharacter(__C(' '), XSTRINGCONTEXT_TO_END);

   return true;
}


GRPVECTORFILEDXFResult GRPVECTORFILEDXF::ParserTextSections (XFILETXT* fileTXT, XVECTOR<GRPVECTORFILEDXFTextSection*>& sections)
{
   GRPVECTORFILEDXFTextSection* section = NULL;
   GRPVECTORFILEDXFResult result = GRPVECTORFILERESULT_ERRORUNKNOWN;
   int c = 0;
 
   do{  if(!section)
        {
          section = new GRPVECTORFILEDXFTextSection ();
        }
    
        XSTRING* line = fileTXT->GetLine(c);
        ParserTextFilePrepareLine(line);

        if(line && !line->Compare(__L("0"),true))
        {           
           line = fileTXT->GetLine(c+1);
           ParserTextFilePrepareLine(line);
           if(line && !line->Compare(__L("SECTION"), false))
           {
             
              line = fileTXT->GetLine(c+2);
              ParserTextFilePrepareLine(line);
              if(line && !line->Compare(__L("2"),true))
              {
                c += 3;

                line = fileTXT->GetLine(c);
                ParserTextFilePrepareLine(line);
                section->iniline = c+1;
                section->name = line->Get(); 

                c++;
              }
           }

           if(line && !line->Compare(__L("ENDSEC"), false))
           {
              section->endline = c-1;                                       
              section->type = GRPVECTORFILEDXFTextSection::GetTypeSection(section->name);  
              
              #ifdef XTRACE_ACTIVE
              if(section->type == GRPVECTORFILEDXFTextSection_TypeSection_Unknown)
              {                 
                 XSTRING message;

                 message.Format(__L("section %s Unknown"), section->name.Get());   
                                                
                 GRPVECTORFILE_XEVENT vfEvent(this, GRPVECTORFILE_XEVENTTYPE_PartUnknown);

                 vfEvent.SetType(VECTORFILETYPE_DXF);
                 vfEvent.GetPath()->Set(fileTXT->GetPrimaryFile()->GetPathNameFile());
                 vfEvent.GetMsg()->Set(message);

                 PostEvent(&vfEvent);       
              }
              #endif

              GRPVECTORFILEDXFTextSection* sectionType = GRPVECTORFILEDXFTextSection::CreateInstance(section->type);
              if(sectionType) 
               { 
                  section->CopyTo(sectionType);
                  sectionType->SetGRPVECTORFILE(this);
                  sections.Add(sectionType);
                  
                  delete section;                                         
               }
              else 
               {
                  sections.Add(section);
               }

              section = NULL;
           }

           if(line && !line->Compare(__L("EOF"), false))
           {
              c++;
              break;
           }
        }
        c++;

     } while(c < fileTXT->GetNLines());
     
   if(section &&  (section->type == GRPVECTORFILEDXFTextSection_TypeSection_Unknown))
   {
      delete section;
   }

   if(!sections.IsEmpty()) 
   {    
      result = GRPVECTORFILERESULT_OK;
   } 
   else
   {
      result = GRPVECTORFILEDXFResult_NotSections;
   }
  
  
   return result;
}


bool GRPVECTORFILEDXF::ParserHaveAnySection(XFILETXT* file, int nlinesmax)
{
   bool foundSection = false;
   int c = 0;
 
   do{   XSTRING* line = file->GetLine(c);
         ParserTextFilePrepareLine(line);

         if(line && !line->Compare(__L("0"),true))
         {
            c++;
            line = file->GetLine(c);
            ParserTextFilePrepareLine(line);
            if(line && !line->Compare(__L("SECTION"), false))
            {
               c++;
               line = file->GetLine(c);
               ParserTextFilePrepareLine(line);
               if(line && !line->Compare(__L("2"),true))
               {
                  c++;
                  line = file->GetLine(c);
                  ParserTextFilePrepareLine(line);

                  foundSection = true;
                
                  break;
               }
            }
         }
         c++;

    } while(c < nlinesmax);

  return foundSection;
}


GRPVECTORFILEDXFResult GRPVECTORFILEDXF::ParserTextFile (XFILETXT* fileTXT)
{
   GRPVECTORFILEDXFResult result = GRPVECTORFILERESULT_ERRORUNKNOWN;

   sections.DeleteContents();
   sections.DeleteAll();

   result = ParserTextSections (fileTXT, sections);
   if(result == (GRPVECTORFILEDXFResult)GRPVECTORFILERESULT_OK)
   {         
      for(XDWORD c=0; c<sections.GetSize(); c++)
      {
         GRPVECTORFILEDXFTextSection* section = sections.Get(c);
         if(section)
         {
            result = section->ParserTextSection(fileTXT);
            if(result != (GRPVECTORFILEDXFResult)GRPVECTORFILERESULT_OK) break;
         }
      }

      if(!sections.GetSize()) 
        {
          result = GRPVECTORFILEDXFResult_NotSections;
        }      
   }

   GRPVECTORFILEDXFTextSectionHeader* sectionheader = (GRPVECTORFILEDXFTextSectionHeader*)GetSection(GRPVECTORFILEDXFTextSection_TypeSection_Header);
   if(sectionheader)
   {
      config.SetHeader(sectionheader);
   }

   #ifdef XTRACE_ACTIVE    
   ShowTraceAllSections();
   #endif
  
   return result;
}


#ifdef XTRACE_ACTIVE         

bool GRPVECTORFILEDXF::GenerateSectionsEntities(GRPVECTORFILEDXFTextSectionEntities* sectionentities, XSTRING& line)
{
   //line.Empty();

   XMAP<XSTRING*, int>* entities = sectionentities->GetEnumEntitys();
   if(entities)
   {                                          
      for(XDWORD d=0; d<entities->GetSize(); d++)
      {
         XSTRING* name = entities->GetKey(d);
         int nentities = entities->GetElement(d);

         if(name) 
         { 
            line.AddFormat(__L(" %s (%d)"), name->Get(), nentities);
            if(d < (entities->GetSize()-1)) line.Add(__L(","));
         }
      }
   }

   return true;
}


bool GRPVECTORFILEDXF::ShowTraceAllSections()
{
   for(XDWORD c=0; c<sections.GetSize(); c++)
   {
      GRPVECTORFILEDXFTextSection* section = sections.Get(c);
      if(section)
      {
         XSTRING line;

         line.Format(__L("[Vector file DXF load] Section [%d, %d]: %s"), section->iniline, section->endline, section->name.Get());

         switch(section->type)
         {
            case GRPVECTORFILEDXFTextSection_TypeSection_Unknown        :
                                                   default           :  break;

            case GRPVECTORFILEDXFTextSection_TypeSection_Header         :  {  GRPVECTORFILEDXFTextSectionHeader* sectionheader = (GRPVECTORFILEDXFTextSectionHeader*)GetSection (section->type);
                                                                           if(sectionheader) 
                                                                              {
                                                                                 line.AddFormat(__L(" -> NVariables (%d)"), sectionheader->GetVariables()->GetSize());                                                                                                                                                       
                                                                                 XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, line.Get());
                                                                              }
                                                                        }
                                                                        break;         

            case GRPVECTORFILEDXFTextSection_TypeSection_Classes        : 
            case GRPVECTORFILEDXFTextSection_TypeSection_Tables         :  break;

            case GRPVECTORFILEDXFTextSection_TypeSection_Blocks         :  {  GRPVECTORFILEDXFTextSectionBlocks* sectionblocks = (GRPVECTORFILEDXFTextSectionBlocks*)GetSection(section->type);
                                                                           if(sectionblocks)
                                                                           {
                                                                              line.AddFormat(__L(" -> (%d)"), sectionblocks->GetBlocks()->GetSize());
                                                                              XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, line.Get());

                                                                              for(XDWORD d=0; d<sectionblocks->GetBlocks()->GetSize(); d++)
                                                                              {
                                                                                 GRPVECTORFILEDXFTextBlock* block = sectionblocks->GetBlocks()->Get(d);
                                                                                 if(block)
                                                                                 {
                                                                                    if(!block->IsEndBlock())
                                                                                    {
                                                                                       GRPVECTORFILEDXFTextSectionEntities* sectionentities = block->GetSectionEntities();  
                                                                                       if(sectionentities)
                                                                                       {                   
                                                                                          line.Format(__L("[Vector file DXF load] Block (%2d) [%s] ENTITIES "), d+1, block->GetName()->Get());                                                                                          
                                                                                          GenerateSectionsEntities(sectionentities,line);
                                                                                          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, line.Get());

                                                                                       }                                                                               
                                                                                    }
                                                                                 }                                                                             
                                                                              }                                                                            
                                                                           }                                                                              
                                                                        }
                                                                        break; 

            case GRPVECTORFILEDXFTextSection_TypeSection_Entities       :  {  GRPVECTORFILEDXFTextSectionEntities* sectionentities = (GRPVECTORFILEDXFTextSectionEntities*)GetSection (section->type);
                                                                           if(sectionentities) 
                                                                           {                                                                              
                                                                             GenerateSectionsEntities(sectionentities,line);
                                                                             XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, line.Get());
                                                                           }
                                                                        }
                                                                        break; 
            case GRPVECTORFILEDXFTextSection_TypeSection_Objects        : 
            case GRPVECTORFILEDXFTextSection_TypeSection_ACDSData       : 
            case GRPVECTORFILEDXFTextSection_TypeSection_ThumbNailImage :  break;
          }           
      }
   }            

   return true;
}

#endif


void GRPVECTORFILEDXF::Clean ()
{
  
}

#pragma endregion
