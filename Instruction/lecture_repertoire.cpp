#include "all_includes.h"


struct dirent* files_name[10];
char *rest;
char sd_present=0;


void lecture_fichier(void){
    short i,j;

    DIR* rep = NULL;

    mkdir("/sd", 0777);
        strcpy(cheminFileStart,"/sd");
        rep=opendir("/sd");
        
        for(i=0;i<20;i++)
        {
            files_name[i]= readdir(rep);  
                    
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
        }
}
        
