#include<stdio.h>
#include<string.h>
#include "view.h"
#include "edit.h"


int main(int argc,char *argv[])
{   
    Tag_List tag_list;

    //less then 2 arguments.
    if(argc < 2)
    {
        printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
        printf("UASAGE :\n");
        printf("To veiw please pass like: ./a.out -v mp3filename\n");
        printf("To edit please pass like : ./a.out -e -t/-a/-A/-g/-y/-c changing_text mp3filename\n");
        printf("To get help pass like : ./a.out --help\n");
        return success;
    }
    //for help only 2 arguments.
    if(strcmp(argv[1],"--help") == 0 && argc == 2)
    {
        printf("\n-------------- HELP MENU ---------------\n\n");
        printf("1. -v -> to view mp3 file contents\n");
        printf("2. -e -> to edit mp3 file contents\n");
        printf("         2.1. -t -> to edit song title\n");
        printf("         2.2. -a -> to edit artist name\n");
        printf("         2.3. -A -> to edit album name\n");
        printf("         2.4. -g -> to edit genre\n");
        printf("         2.5. -y -> to edit year\n");
        printf("         2.6. -c -> to edit comment\n");
        return success;
    }
    //for view  only 3 arguments.
    if(strcmp(argv[1], "-v") == 0 && argc == 3)
    {
        if( strstr(argv[2],".mp3") != NULL && (strcmp(strstr(argv[2],".mp3"),".mp3") == 0)  )
        {
            if(mp3view(argv,&tag_list) == success)
            {
                return success;
            }
                return failure;
        }
        else
        {
            printf("ERROR: Invalid File\n");
            return failure;
        }
    }
    
    //for 5 arguments, validate arguments.
    if(strcmp(argv[1], "-e") == 0 && argc == 5)
    {
        if( (strcmp(argv[2],"-t") == 0 ||
            strcmp(argv[2],"-a") == 0 ||
            strcmp(argv[2],"-A") == 0 ||
            strcmp(argv[2],"-g") == 0 ||
            strcmp(argv[2],"-y") == 0 ||
            strcmp(argv[2],"-c") == 0)  && strlen(argv[3]) <=30 )
        { 
            if(mp3edit(argv) == success)
            {
                return success;
            }
                return failure;
        }
        else
        {
            printf("ERROR: Invalid Tag Argument\n");
            return failure;
        }
    }
    else
    {
        printf("ERROR: Invalid Arguments\n");
        return failure;
    }

    //for arguments more then 5.
    if(argc>5 || argc <5)
    {
        printf("ERROR: Invalid Arguments\n");
        return failure;
    } 
}