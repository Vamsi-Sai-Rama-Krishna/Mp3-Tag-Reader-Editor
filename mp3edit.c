#include<stdio.h>
#include<string.h>
#include"edit.h"
#include "view.h"

int mp3edit(char *argv[])
{
    if( strcmp(argv[2],"-t") == 0)
    {
        printf("Editing Song Tiltle..\n");
        Tag_Edit(argv,"TIT2");     
        printf("\n-------------------------------");
        printf("\nSong Title Updated Successfully\n");
        printf("-------------------------------\n");
    }
    if(strcmp(argv[2],"-a") == 0)
    {
        printf("Editing Artist Name..\n");
        Tag_Edit(argv,"TPE1");
        printf("\n--------------------------------");
        printf("\nArtist Name Updated Successfully\n");
        printf("---------------------------------\n");
    }
    if(strcmp(argv[2],"-A") == 0 )
    {
        printf("Editing Album Name..\n");
        Tag_Edit(argv,"TALB");
        printf("\n-------------------------------");
        printf("\nAlbum Name Updated Successfully\n");
        printf("-------------------------------\n");

    }
    if(strcmp(argv[2],"-g") == 0 )
    {
        printf("Editing Genre..\n");
        Tag_Edit(argv,"TCON");
        printf("\n----------------------------");
        printf("\nGenre Updated Successfully\n");
        printf("----------------------------\n");
    }
    if(strcmp(argv[2],"-y") == 0)
    {
        printf("Editing Year..\n");
        Tag_Edit(argv,"TYER");
        printf("\n-------------------------");
        printf("\nYear Updated Successfully\n");
        printf("-------------------------\n");

    }
    if(strcmp(argv[2],"-c") == 0)
    { 
        printf("Editing Comment..\n");
        Tag_Edit(argv,"COMM");
        printf("\n----------------------------");
        printf("\nComment Updated Successfully\n");
        printf("----------------------------\n");
    }
    return success;
}

int Tag_Edit(char *argv[],char tag_name[])
{
    //open the file
    FILE *fptr_src_mp3file = fopen(argv[4],"r");
    //error handling for opeining file.
    if(fptr_src_mp3file == NULL )
    {
        perror("fopen");
        printf("Error: Unable to open \"%s\" file\n",argv[4]);
        return failure;
    }

    char start[3];
    fread(start,3,1,fptr_src_mp3file);
    start[3] = '\0';
    
    if(strcmp(start,"ID3") != 0)
    {
        printf("ID3 Tag Not Matching\n");
        return failure;
    }

    //check for verssion i.e 2 bytes.
    char version;
    fread(&version,1,1,fptr_src_mp3file);
    
    //if(version[0] == 0x03 && version[1] == 0x00)
    if(version != 0x03)
    {
        printf("Main Version Not Matching\n");
        return failure;
    }
    
    //after opening file check for signature whether ID3 or not.
    FILE *fptr_temp_file = fopen("temp.mp3","w");
    if(fptr_temp_file == NULL)
    {
        perror("fopen");
        printf("Error: Unable to open temperory file\n");
        return failure;
    }

    //write to temperory file first 10 bytes
    rewind(fptr_src_mp3file);
    char header[10];
    fread(header,10,1,fptr_src_mp3file);
    fwrite(header,10,1,fptr_temp_file);
    
    int no_of_tags = 6;
    while(no_of_tags)
    {
        //now check the tag.
        char tag[5];
        fread(tag,4,1,fptr_src_mp3file);
        tag[4] = '\0';

        if(strcmp(tag,tag_name) == 0)
        {
            //if match
            fwrite(tag,4,1,fptr_temp_file);

            //go for editing
            //read size -> convert it to little endian
            char old_size[4];
            fread(old_size,4,1,fptr_src_mp3file);
            int extracted_old_size=0;

            //read size covert to litte endian and store in variable based on that length.
            //convert size to little endian.
            for(int i = 0; i < 4; i++)
            {
                extracted_old_size = extracted_old_size << i*8 | old_size[i];
            }
            extracted_old_size = extracted_old_size - 1;
            
            //take new length from the cla and convert to big endian.
            //now paste to 4 bytes to size
            //paste new size after converting it into big endian format.
            int new_size = strlen(argv[3])+1;
            char *cptr = (char*)&new_size;
            for(int i = 0; i < 2; i++)
            {
                // converted_new_size = converted_new_size >> i * 8 | new_size[i];
                char temp = cptr[i];
                cptr[i] = cptr[4-i-1];
                cptr[4-i-1] = temp;
            }
            fwrite(cptr,4,1,fptr_temp_file);

            
            //skip flags &read content based on retrived size-1
            char matched_flags[3];
            fread(matched_flags,3,1,fptr_src_mp3file);
            fwrite(matched_flags,3,1,fptr_temp_file);


        for(int i=0; i<strlen(argv[3]); i++)
        {
            //write to file charcater by charcter/byte by byte.
            fwrite(&argv[3][i],sizeof(char),1,fptr_temp_file);
        }
            fseek(fptr_src_mp3file,extracted_old_size,SEEK_CUR);
            
            char ch;
            int count;
            while( count = fread(&ch,sizeof(char),1,fptr_src_mp3file) > 0)
            {
                fwrite(&ch,sizeof(char),1,fptr_temp_file);
            }

            
            //remove the previous file using file name.
            remove(argv[4]);
            //after modifying or editing change name of the temperory file to user give original file name.
            rename("temp.mp3",argv[4]);

            //directly return "success" to exit the function.
            return success;
        }
        else
        {
            //if not match
            //paste the unmatched tag as it is to temp file.
            fwrite(tag,4,1,fptr_temp_file);

            int modified_size = 0;
            char un_modified_size[4];
            fread(un_modified_size,4,1,fptr_src_mp3file);
            
            //read size covert to litte endian and store in variable based on that length.
            //convert size
            for(int i = 0; i < 4; i++)
            {
                modified_size = modified_size << i * 8 | un_modified_size[i];
            }
            modified_size = modified_size - 1;
            
            //paste unmodified size.
            fwrite(un_modified_size,4,1,fptr_temp_file);
            
            char unmatched_flags[3];
            //read flags and paste as it is
            fread(unmatched_flags,3,1,fptr_src_mp3file);
            fwrite(unmatched_flags,3,1,fptr_temp_file); 

            //read content based on converted size, paste as it is.
            char unmatched_tag_content[modified_size];
            fread(unmatched_tag_content,modified_size,1,fptr_src_mp3file);
            fwrite(unmatched_tag_content,modified_size,1,fptr_temp_file);
            
            //decrement tags for every iteration.
            no_of_tags--;
        }
    }
    return success;
}