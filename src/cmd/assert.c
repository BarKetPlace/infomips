#include <stdio.h>
#include <stdlib.h>



#include "cmd.h"
#include "mem.h"
#include "notify.h"
#include "bits.h"
#include "formats.h"
#include "types.h"
#include "syms.h"
#include "section.h"
#include "reg.h"
#include "is_.h"


int assertcmd(interpreteur inter, mem memory, registre *reg)
{

  char *token=get_next_token(inter);
  char r[128];

  int j, adresse;
  int val_f_r=0, val_f_a =0;
  int val_t_a=0, val_t_r=0;
  byte val_f_m=0;
		
  if (token && !strcmp(token,"reg")) //assert reg
    {
      // La mémoire
      if (memory == NULL) //Probleme avec le chargement de la mémoire
	{
	  WARNING_MSG("Memoire non-chargée");
	  return cmd_unknown;
	}
      token = get_next_token(inter);
      //DEBUG_MSG("ok");
		
      if (token == NULL) //assert reg (null)
	{
	  WARNING_MSG("Missing arguments <registre>");
	  return cmd_unknown;
	}

      else if ((is_registre(token))!=-1) //assert reg <registre>
	{	
	  //DEBUG_MSG("ok");
	  strcpy(r,token);
	  token = get_next_token(inter);
	  //puts(token);

	  if (token == NULL) //assert reg <registre> (null)
	    {
	      WARNING_MSG("Missing arguments <registre>");
	      return cmd_unknown;
	    }

			
	  else if (is_valeur(token) || is_hexa(token)) //assert reg registre valeur
	    {
				
	      //	DEBUG_MSG("ok");		
	      j=transf_reg(reg, r);
	      //	DEBUG_MSG("%d",j);

	      if (is_valeur(token)) // valeur entiere
		{
		  sscanf(token, "%d", &val_t_r); 	//DEBUG_MSG("%d",val_t_r);
		  if (val_t_r==reg[j].val) {return cmd_ok;}
		  else {WARNING_MSG("ERREUR"); return cmd_unknown;}
		}
	      else if (is_hexa(token)) // valeur hexadecimale
		{
		  sscanf(token, "%x", &val_t_r); 	//DEBUG_MSG("%d",val_t_r);
		  if (val_t_r==reg[j].val){return cmd_ok;}
		  else {WARNING_MSG("ERREUR"); return cmd_unknown;}
		}
	      else {WARNING_MSG("la valeur decimale ou hexadecimale");return cmd_unknown;}
	    }

	  else 
	    {	
	      WARNING_MSG("Wrong argument: must be <valeur>");
	      return cmd_unknown;
	    }
	}
      else
	{
	  WARNING_MSG("Wrong argument: must be <registre>");
	  return cmd_unknown;
	}
    }
  else if (token && !strcmp(token, "byte")) //assert byte
    {
      token = get_next_token(inter);
      //DEBUG_MSG("ok");
      if (token && is_hexa(token)) //assert byte <adresse>
	{	
	  //DEBUG_MSG("ok");
	  sscanf(token, "%x", &adresse);
	  token = get_next_token(inter);
		
	  //DEBUG_MSG("ok");

	 
	  
			
	  if (find_byte(memory, adresse, &val_f_a)!=cmd_ok) return cmd_unknown;
	  else 
	    {
	      if (token && is_valeur(token)) // valeur entiere
		sscanf(token, "%d", &val_t_a);
	      else if (token && is_hexa(token)) // valeur hexadecimale	
		sscanf(token, "%x", &val_t_a);
	      else {WARNING_MSG("Wrong argument must be 1 byte value"); return cmd_unknown;}
	      if (val_t_a>255) 
		{
		  WARNING_MSG("La valeur ne tient pas sur 1 octet");
		  return cmd_unknown;
		}
	      DEBUG_MSG("%d %x",val_t_a,val_f_a);
	      //Comparaison entre les deux valeurs
	      if (val_t_a==val_f_a) { return cmd_ok;}
	      else { WARNING_MSG("Erreur"); return cmd_unknown;}
	    }  
	}
      else 
	{	
	  WARNING_MSG("Wrong argument: must be <adresse>");
	  return cmd_unknown;
	}
    }
  else if (token && !strcmp(token, "word")) //assert word)
    {
      token = get_next_token(inter);
      //DEBUG_MSG("ok");
      if (token && is_hexa(token)) //assert byte <adresse>
	{	
	  //DEBUG_MSG("ok");
	  sscanf(token, "%x", &adresse);
	  token = get_next_token(inter);
		
	  //DEBUG_MSG("ok");

	  token = get_next_token(inter);
	  
			
	  if (find_word(memory, adresse, &val_f_a)!=cmd_ok) return cmd_unknown;
	  if (token && is_valeur(token)) // valeur entiere
	     sscanf(token, "%d", &val_t_a);
	  else if (token && is_hexa(token)) // valeur hexadecimale	
	     sscanf(token, "%x", &val_t_a);
	  else {WARNING_MSG("Wrong argument must be 4 byte value"); return cmd_unknown;}
	  if (val_t_a>0xffffffff) 
	    {
	      WARNING_MSG("La valeur ne tient pas sur 4 octets");
	      return cmd_unknown;
	    }
	  //Comparaison entre les deux valeurs
	  if (val_t_a==val_f_a) { return cmd_ok;}
	  else { WARNING_MSG("Erreur"); return cmd_unknown;}
	    
	}
      else 
	{	
	  WARNING_MSG("Wrong argument: must be <adresse>");
	  return cmd_unknown;
	}
    }  
    

 else //assert "autre chose que reg ou word ou byte"  
   {
     WARNING_MSG("Usage: assert \"word\" | assert \"reg\" | assert \"byte\"");
     return cmd_unknown;
   }
//DEBUG_MSG("ok");
return cmd_ok;


}

