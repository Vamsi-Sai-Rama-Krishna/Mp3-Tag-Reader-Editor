#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "view.h"

int open_file_to_view(char *argv[],Tag_List *tag_list)
{
    //open the file
    tag_list->fptr_mp3_view  = fopen(argv[2],"r");
    
    //error handling for opeining file.
    if(tag_list->fptr_mp3_view  == NULL)
    {
        perror("fopen");
        printf("Error: Unable to open \"%s\" file\n",argv[3]);
        return failure;
    }

    return success;
}

int check_ID3_version(Tag_List *tag_list)
{
    char start[3];
    fread(start,3,1,tag_list->fptr_mp3_view);
    start[3] = '\0';
    
    printf("Tag ID : %s\n",start);
    if(strcmp(start,"ID3") == 0)
    {
        //check for verssion i.e 2 bytes.

        char version;
        fread(&version,1,1,tag_list->fptr_mp3_view);
        
        printf("Version: %d \n",version);
        //if(version[0] == 0x03 && version[1] == 0x00)
        if(version == 0x03)
        {
            printf("\n------------------------------\n");
            return success;
        }
        else
        {
            printf("Main Version not Matching\n");
            return failure;
        }
    }
    else
    {
        printf("Not an ID3 Version\n");
        return failure;
    }

    // //check for verssion i.e 2 bytes.

    // char version;
    // fread(&version,1,1,tag_list->fptr_mp3_view);
    // printf("%c\n",version);
    // printf("version: %d \n",version);
    // //if(version[0] == 0x03 && version[1] == 0x00)
    // if(version == 0x03)
    // {
    //     printf("Main version matching\n");
    // }
    // else
    // {
    //     printf("Main version not matching\n");
    //     return failure;
    // }
}

void skip_header(Tag_List *tag_list)
{
    //skip header (10 bytes)
    fseek(tag_list->fptr_mp3_view,10,SEEK_SET);
}

int reading_size(FILE *fptr)
{
    // int size=0;
    // fread(&size,4,1,fptr);
    // // char *cptr = (char *)&(Tag ->size);
	// for(int i=0;i<2;i++)
	// {
	//     char temp = cptr[i];
	//     cptr[i] = cptr[4-i-1];
	//     cptr[4-i-1] = temp;
	// }
    int size=0;
    char ch;
    for(int i = 0; i < 4; i++)
    {
        fread(&ch, 1, 1, fptr);
        size = size << i * 8 | ch;
    }
    size = size - 1;
    //printf("size is %d",size);
    return size;
}

Status Tag_Check(FILE *fptr,char tag_name[])
{
    char tag_read[5];
    fread(tag_read,sizeof(char),4,fptr);
    tag_read[4] = '\0';

    //then compare with given tag.
    if(strcmp(tag_read,tag_name) == success)
    {
        //then read size, next 4 bytes.
        int size  = reading_size(fptr);

        //skip 3 bytes of flags
        fseek(fptr,3,SEEK_CUR);
    
        //based on size read next content and store it in temperory string.
        char *temp = malloc(size+1);

        //read content
        fread(temp,sizeof(char),size,fptr);
        temp[size] = '\0';

        printf(" %s\n",temp);
        free(temp);

        return success;
    }
    return failure;
}

int processing_tags(Tag_List *tag_list)
{      
    // TIT2 for Tilte.
    printf("Title/Song Name : ");
    if(Tag_Check(tag_list->fptr_mp3_view,"TIT2") == success)
    {
        // TPE1 for artist.
        printf("Artist Name : ");
        if(Tag_Check(tag_list->fptr_mp3_view,"TPE1") == success)
        {
        // TALB for album name.
            printf("Album Name : ");
            if(Tag_Check(tag_list->fptr_mp3_view,"TALB") == success)
            {
                //TYER for year
                printf("Year : ");
                if(Tag_Check(tag_list->fptr_mp3_view,"TYER") == success)
                {
                    //TCON for genre.
                    printf("Genre : ");
                    if(Tag_Check(tag_list->fptr_mp3_view,"TCON") == success)
                    {
                        //COMM for comment.
                        printf("Comment : ");
                        if(Tag_Check(tag_list->fptr_mp3_view,"COMM") == success)
                        {
                            return success;
                        }
                        else
                        {
                            return failure;
                        }
                    }
                }
            }
        }
    }
    else
    {
        return failure;
    }
}

// fetching only 6 tags.
Status mp3view(char *argv[],Tag_List *tag_list)
{   
    if(open_file_to_view(argv,tag_list) == success)
    {
        if(check_ID3_version(tag_list) == success)
        {
            skip_header(tag_list);
            if(processing_tags(tag_list) == success)
            {
                printf("\n----------------------");
                printf("\nView Process Completed\n");
                printf("----------------------\n");
                return success;
            }
            else
            {
                printf("\n-------------------");
                printf("\nView Process Failed\n");
                printf("-------------------\n");
                return failure;
            }
        }
        else
        {
            printf("Not ID3 File\n");
        }
    }
    else
    {
        printf("INFO: Opening Mp3 File Failed\n");
    }
}
