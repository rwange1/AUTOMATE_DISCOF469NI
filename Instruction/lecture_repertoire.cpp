#include "all_includes.h"
#include "FATFileSystem.h"

struct dirent* files_name[10];
char *rest;
char sd_present=0;
char buf[30];
//Défini dans automate_visuel

//comprendra qui pourra

void lecture_fichier(char * strat){
    short i,j;

    struct dirent de;
    Dir* rep = NULL;
    f_mkdir("/sd");
    sprintf(buf,"/sd/%s",strat);
    
        // strcpy(strat,"/sd");
        rep->open(&m_fs,"/sd");
        /*     J'ai pas compris à quoi sert ce qu'il y a apres
        for(i=0;i<20;i++)
        {
            files_name[i]= ;  
                    
            if(files_name[i]->d_name=="")
            {
                i=20;
            }
            else
            {
                sd_present=1;
                strcpy(strat_sd[i-j],files_name[i]->d_name);
                rest=strstr(strat_sd[i-j],".txt");
                
                if(rest==NULL)
                {
                    strcpy(strat_sd[i-j],"");
                    j++;
                }
                else
                {
                    strcpy(strat_sd[i-j],strtok(strat_sd[i-j],"."));
                }
                
            }
        }*/
}
        
