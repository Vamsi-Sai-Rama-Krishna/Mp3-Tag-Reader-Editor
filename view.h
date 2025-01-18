#ifndef VIEW_H
#define VIEW_H

typedef enum
{
    success,
    failure
}Status;

typedef struct 
{
    /* file pointer */
    FILE *fptr_mp3_view;

}Tag_List;


//void validate_cla_arguments(int argc, char *argv[]);

int open_file_to_view(char *argv[],Tag_List *tag_list);

// check for ID3 ->read 3 bytes from mp3 file.
int check_ID3_version(Tag_List *tag_list);

void skip_header(Tag_List *tag_list);

int processing_tags(Tag_List *tag_list);

int reading_size(FILE *fptr);

Status mp3view(char *argv[],Tag_List *tag_list);

void tag_viewer(FILE *fptr);

Status Tag_Check(FILE *fptr, char tag_name[]);

#endif
