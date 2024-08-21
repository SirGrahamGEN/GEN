#pragma region INCLUDES

#include "XMap.h"
#include "XVariant.h"

#include "GRPVectorFile_XEvent.h"
#include "GRPVectorFileDXF.h"
#include "GRPVectorFileDXFValue.h"
#include "GRPVectorFileDXFXDataCtrl.h"
#include "GRPVectorFileDXFTextBlock.h"
#include "GRPVectorFileDXFTextSectionEntities.h"

#include "GRPVectorFileDXFTextSectionBlocks.h"

#pragma endregion


#pragma region GENERAL_VARIABLES

GRPVECTORFILEDXFTEXTSECTIONBlockDef GRPVECTORFILEDXFTEXTSECTIONBLOCKS::defBlock[GRPVECTORFILEDXFBlocks_MaxNDefBlocks] = 
{    
   { __L("BLOCK")    , 15 , false,  { {   5 , __L("HANDLE")                     , __L("Handle") },
                                      { 102 , __L("XDATAGROUP1")                , __L("Start of application-defined group '{application_name'. For example, '{ACAD_REACTORS' indicates the start of the AutoCAD persistent reactors group (optional) application-defined codes Codes and values within the 102 groups are application defined (optional)") },
                                      { 102 , __L("XDATAGROUP2")                , __L("End of group, '}' (optional)") },
                                      { 330 , __L("ID-HDL_OWNER_OBJECT")        , __L("Soft-pointer ID/handle to owner object") },
                                      { 100 , __L("SUBCLASS_ACDBENTITY")        , __L("Subclass marker (AcDbBlock)") },
                                      {   8 , __L("LAYER_NAME")                 , __L("Layer name") },
                                      { 100 , __L("SUBCLASS_ACDBBLOCKBEGIN")    , __L("Subclass marker (AcDbBlockBegin)") },
                                      {   2 , __L("BLOCK_NAME")                 , __L("Block name") },
                                      {  70 , __L("BLOCK-TYPE_FLAGS")           , __L("Block-type flags (bit-coded values, may be combined): 0 = Indicates none of the following flags apply, 1 = This is an anonymous block generated by hatching, associative dimensioning, other internal operations, or an application, 2 = This block has non-constant attribute definitions (this bit is not set if the block has any attribute definitions that are constant, or has no attribute definitions at all), 4 = This block is an external reference (xref), 8 = This block is an xref overlay, 16 = This block is externally dependent, 32 = This is a resolved external reference, or dependent of an external reference (ignored on input), 64 = This definition is a referenced external reference (ignored on input).") },
                                      {  10 , __L("BASE_POINT_X")               , __L("Base point DXF: X value; APP: 3D point") },
                                      {  20 , __L("BASE_POINT_Y")               , __L("DXF: Y value of base point") },
                                      {  30 , __L("BASE_POINT_Z")               , __L("DXF: Z value of base point") },
                                      {   3 , __L("BLOCK_NAME")                 , __L("Block name") },
                                      {   1 , __L("XREF_PATH_NAME")             , __L("Xref path name") },
                                      {   4 , __L("BLOCK_DESCRIPTION")          , __L("Block description (optional)") } } },

   { __L("ENDBLK")   ,  1 ,  true,  { {   5 , __L("HANDLE")                     , __L("Handle") },
                                      { 102 , __L("XDATAGROUP")                 , __L("Start of application-defined group '{application_name'. For example, '{ACAD_REACTORS' indicates the start of the AutoCAD persistent reactors group (optional) application-defined codes Codes and values within the 102 groups are application defined (optional)") },
                                      { 102 , __L("END_GROUP")                  , __L("End of group, '}' (optional)") },
                                      { 330 , __L("ID-HDL_OWNER_OBJECT")        , __L("Soft-pointer ID/handle to owner object") },
                                      { 100 , __L("SUBCLASS_ACDBENTITY")        , __L("Subclass marker (AcDbBlock)") },
                                      {   8 , __L("LAYER_NAME")                 , __L("Layer name") },
                                      { 100 , __L("SUBCLASS_ACDBBLOCKEND")      , __L("Subclass marker (AcDbBlockEnd)") } } },   
   };

#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFTEXTSECTIONBLOCKS::GRPVECTORFILEDXFTEXTSECTIONBLOCKS()
{
   Clean();

   type = GRPVECTORFILEDXFTEXTSECTION_TYPESECTION_BLOCKS;
}


GRPVECTORFILEDXFTEXTSECTIONBLOCKS::~GRPVECTORFILEDXFTEXTSECTIONBLOCKS()
{
   DeleteAllBlocks();

   Clean();
}


GRPVECTORFILEDXFTEXTSECTIONBlockDef* GRPVECTORFILEDXFTEXTSECTIONBLOCKS::IsKnownBlock(XSTRING& name)
{  
   for(XDWORD c=0; c<GRPVECTORFILEDXFBlocks_MaxNDefBlocks; c++)
   {
      GRPVECTORFILEDXFTEXTSECTIONBlockDef* blockDef = &GRPVECTORFILEDXFTEXTSECTIONBLOCKS::defBlock[c];
      if(blockDef)
      {
         if(!name.Compare(blockDef->name, true)) 
         {
            return blockDef;
         }    
      }
   }
  
   return NULL;
}


GRPVECTORFILEDXFTEXTSECTIONBlockDefType* GRPVECTORFILEDXFTEXTSECTIONBLOCKS::IsKnownTypeValue(XSTRING& namevar, int type)
{  
   for(int c=0; c<GRPVECTORFILEDXFBlocks_MaxNDefBlocks; c++)
   {
      GRPVECTORFILEDXFTEXTSECTIONBlockDef* block  = &GRPVECTORFILEDXFTEXTSECTIONBLOCKS::defBlock[c];
      if(block)
      {
         if(!namevar.Compare(block->name, true)) 
         {
            for(int d=0; d<block->ntypes; d++)
            {
               GRPVECTORFILEDXFTEXTSECTIONBlockDefType* typeDef = &block->type[d]; 
               if(typeDef)
               {
                  if(typeDef->type == type) 
                  {
                     return typeDef;                  
                  }
               }            
            }
         }    
      }
   }
  
   return NULL;
}


bool GRPVECTORFILEDXFTEXTSECTIONBLOCKS::AddBlock (GRPVECTORFILEDXFTextBlock* block)
{
   if(!block) return false;

   if(block->GetName()->IsEmpty()) return false;
  
   return blocks.Add(block);
   
   return true;

}


XVECTOR<GRPVECTORFILEDXFTextBlock*>* GRPVECTORFILEDXFTEXTSECTIONBLOCKS::GetBlocks ()
{
  return &blocks;
}
    
    
GRPVECTORFILEDXFTextBlock* GRPVECTORFILEDXFTEXTSECTIONBLOCKS::GetBlock (XCHAR* nameBlock, XDWORD index)
{
   if(blocks.IsEmpty()) return NULL;

   int iindex = 0;

   for(XDWORD c=0; c<blocks.GetSize(); c++)
   {
      GRPVECTORFILEDXFTextBlock* block = blocks.Get(c);
      if(block)
      {
         if(block->GetName()->Find(nameBlock, false) != XSTRING_NOTFOUND)
         {
            if(iindex == index)
              {              
                return block;
              }

            iindex ++;
         }
      }    
   }
  
   return NULL;
}
    
    
bool GRPVECTORFILEDXFTEXTSECTIONBLOCKS::DeleteBlock(XCHAR* nameBlock, XDWORD index)
{
   if(blocks.IsEmpty()) return false;

   GRPVECTORFILEDXFTextBlock* block = GetBlock (nameBlock, index);
   if(block)
   { 
      blocks.Delete(block);
      delete block;

      return true;
   }

   return false;    
}
    
    
bool GRPVECTORFILEDXFTEXTSECTIONBLOCKS::DeleteAllBlocks(XCHAR* nameBlock)
{
   if(blocks.IsEmpty()) return false;

   GRPVECTORFILEDXFTextBlock* block;
   int index = 0;

   do {  block = GetBlock (nameBlock, index);
         if(block)
         {
            DeleteBlock(nameBlock, index);
         }
         else 
         {
            index++;
         }
   
     } while(block);

   return true;
}
    
    
bool GRPVECTORFILEDXFTEXTSECTIONBLOCKS::DeleteAllBlocks()
{
   if(blocks.IsEmpty()) return false;

   blocks.DeleteContents();
   blocks.DeleteAll();

   return true;
}


GRPVECTORFILERESULT GRPVECTORFILEDXFTEXTSECTIONBLOCKS::ParserTextSection (XFILETXT* fileTXT)
{    
   XVECTOR<GRPVECTORFILEDXFTextPart*> parts;
   GRPVECTORFILEDXFTextPart* part = NULL;  
   GRPVECTORFILEDXFXDATACTRL* xDataCtrl = NULL;
   int indexline = iniline;
   XSTRING* line;
  
   part = new GRPVECTORFILEDXFTextPart ();

   do{   line = fileTXT->GetLine(indexline);
         if(line) 
         {                       
            GRPVECTORFILEDXF::ParserTextFilePrepareLine(line);

            if(line && !line->Compare(__L("0"),true))
            {               
               line = fileTXT->GetLine(indexline + 1);
               GRPVECTORFILEDXF::ParserTextFilePrepareLine(line);

               if(IsKnownBlock(*line))
               {
                  indexline++; 
               
                  if(part)
                  {
                     if(part->iniline != -1)
                     {               
                        part->endline = indexline - 2; 
                                
                        parts.Add(part); 
                        part = NULL;
                  
                        part = new GRPVECTORFILEDXFTextPart ();
                     }
                     else
                     {
                        if(part->iniline == -1)
                        {                     
                           part->name    = line->Get();
                           part->iniline = indexline + 1;              
                        }                             
                     }
                  }
               }          
            } 
         }
                           
         indexline++;

     } while(indexline < endline);

   if(part && (part->iniline != -1))
   {               
      part->endline = indexline-1; 
      
      parts.Add(part); 
      part = NULL;           
   }

   if(part && part->iniline == -1)
   {
      delete part;
      part = NULL;    
   }
  
   for(XDWORD c=0; c<parts.GetSize(); c++)
   {
      part = parts.Get(c);
      if(part)
      {         
         GRPVECTORFILEDXFTextBlock* block = new GRPVECTORFILEDXFTextBlock();
         if(block)
         {               
            GRPVECTORFILEDXFTEXTSECTIONBlockDef* blockDef = IsKnownBlock(part->name);
            if(blockDef)
            {
               block->SetIsEndBlock(blockDef->isendblock);

               if(blockDef->isendblock)
               {
                  GRPVECTORFILEDXFTextBlock* lastblock = blocks.Get(blocks.GetSize()-1);
                  if(lastblock)
                  {
                     block->GetName()->Set(lastblock->GetName()->Get());
                  }                             
               }
            }

            indexline = part->iniline;

            bool nomorevalues = false;
                  
            while(part->endline > indexline)
            {  
               line = fileTXT->GetLine(indexline);      
               if(line) 
               {  
                  indexline++;                    
                  GRPVECTORFILEDXF::ParserTextFilePrepareLine(line);                  
                  int type = line->ConvertToInt();
                        
                  if(!type)
                     {                    
                        line = fileTXT->GetLine(indexline);
                        if(line)
                        {  
                           GRPVECTORFILEDXF::ParserTextFilePrepareLine(line); 
                                                     
                           GRPVECTORFILEDXFTEXTSECTIONENTITIES* sectionEntities = new GRPVECTORFILEDXFTEXTSECTIONENTITIES();
                           if(sectionEntities)
                           { 
                              sectionEntities->iniline = indexline - 1;
                              sectionEntities->endline = part->endline;

                              if(sectionEntities->IsKnownEntity((*line)))
                              {     
                                 sectionEntities->SetGRPVECTORFILE(GetGRPVECTORFILE());
                                 sectionEntities->ParserTextSection(fileTXT);  
                                 indexline = part->endline - 1;
                                 
                                 block->SetSectionEntities(sectionEntities);

                                 nomorevalues = true;
                              }
                           }                                                                                                   
                        }                        
                     }

                  if(!nomorevalues)    
                  {
                     GRPVECTORFILEDXFVALUE* value = new GRPVECTORFILEDXFVALUE();
                     if(value)
                     {      
                        GRPVECTORFILEDXFTEXTSECTIONBlockDefType* defType = IsKnownTypeValue(part->name, type);
                        if(!defType)
                        {                              
                           #ifdef TEST_ONLY_DEFINE_IN_BLOCKS

                           XSTRING message;

                           message.Format(__L("type data of block %d Not register [%d]"), type);
                               
                           GRPVECTORFILE_XEVENT vfEvent(GetGRPVECTORFILE(), GRPVECTORFILE_XEVENTTYPE_PartUnknown);

                           vfEvent.SetType(VECTORFILETYPE_DXF);
                           vfEvent.GetPath()->Set(fileTXT->GetPrimaryFile()->GetPathNameFile());
                           vfEvent.GetMessage()->Set(message);

                           PostEvent(&vfEvent, GetGRPVECTORFILE());                           

                           indexline++;                          
                           delete value;
                           
                           continue;

                           #else

                           GRPVECTORFILEDXFTEXTSECTIONGenericDefType* genDefType = GetGenericDefType(type);
                           if(genDefType)
                           {
                              value->SetType(genDefType->type);
                              value->GetName()->Set(genDefType->name);
                              value->GetRemark()->Set(genDefType->remark);                      
                           }
                           else 
                           {                              
                              XSTRING message;

                              message.Format(__L("type data of block %d Not register [%d]"), type);
                               
                              GRPVECTORFILE_XEVENT vfEvent(GetGRPVECTORFILE(), GRPVECTORFILE_XEVENTTYPE_PARTUNKNOWN);

                              vfEvent.SetType(VECTORFILETYPE_DXF);
                              vfEvent.GetPath()->Set(fileTXT->GetPrimaryFile()->GetPathNameFile());
                              vfEvent.GetMsg()->Set(message);

                              PostEvent(&vfEvent, GetGRPVECTORFILE());                          

                              indexline++;
                              continue;
                           }

                           #endif
                        }
                        else
                        {
                           value->SetType(defType->type);
                           value->GetName()->Set(defType->name);
                           value->GetRemark()->Set(defType->remark); 
                        }

                        line = fileTXT->GetLine(indexline);
                        if(line)
                        {
                           GRPVECTORFILEDXF::ParserTextFilePrepareLine(line); 
                           
                           GetVariableFromLine(value->GetName()->Get(), type, line, (*value->GetData()));                        

                           switch(IsXDataControl(type, (*line)))
                           {
                              case GRPVECTORFILEDXFTEXTSECTION_XDataCtrl_Status_Not    :  if(xDataCtrl) 
                                                                                       {
                                                                                          if(value) 
                                                                                          {                                                                                                            
                                                                                             xDataCtrl->GetValues()->Add(value);   
                                                                                          }
                                                                                       }
                                                                                       break;

                              case GRPVECTORFILEDXFTEXTSECTION_XDataCtrl_Status_Ini    :  if(!xDataCtrl)                
                                                                                       {
                                                                                          xDataCtrl = new GRPVECTORFILEDXFXDATACTRL();
                                                                                          if(xDataCtrl)                
                                                                                          {
                                                                                             XSTRING name;
                                                                                             line->Copy(1, name);
                                                                                       
                                                                                             xDataCtrl->GetName()->Set(name);
                                                                                          }
                                                                                       }
                                                                                       break;

                              case GRPVECTORFILEDXFTEXTSECTION_XDataCtrl_Status_End   :   if(xDataCtrl)                
                                                                                       { 
                                                                                          block->GetXDataCtrlList()->Add(xDataCtrl);
                                                                                          xDataCtrl = NULL;
                                                                                       }                              
                                                                                       break;
                           }
 
                           
                           if(value) 
                           {  
                              if((value->GetType() == 2) || (value->GetType() == 3))
                              {
                                 XSTRING* data = (XSTRING*)(value->GetData()->GetData());                                 
                                 if(data) block->GetName()->Set(data->Get()); 
                              }

                              block->AddValue(value);
                           }
                        }                                            
                     }
                  }
               }
         
               indexline++;

              }         

            AddBlock(block);
         }
      }
   } 

   parts.DeleteContents();
   parts.DeleteAll();

   #ifdef XTRACE_ACTIVE
   //ShowTraceAllBlocks();
   #endif
   
   return GRPVECTORFILERESULT_OK;
}


#ifdef XTRACE_ACTIVE
bool GRPVECTORFILEDXFTEXTSECTIONBLOCKS::ShowTraceAllBlocks()
{ 
   for(XDWORD c=0; c<blocks.GetSize(); c++)
   {
      GRPVECTORFILEDXFTextBlock* block = blocks.Get(c);
      if(block)
      {
         XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[GRPVECTORFILEDXFTEXTSECTIONBLOCKS] (%3d) Block %c [%s] (%d) values."), c, (block->IsEndBlock()?__C('<'):__C('>')), block->GetName()->Get(), block->GetValues()->GetSize());
      }
   }

   return true;
}
#endif


void GRPVECTORFILEDXFTEXTSECTIONBLOCKS::Clean()
{
  
}

#pragma endregion
