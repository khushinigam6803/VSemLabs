/*Write a program that allows the user to remove any or all of the files in a current
working directory. The name of the file should appear followed by a prompt as to
whether it should be removed.*/
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

int main() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
        return 1;
    }
    
    DIR *directory;
    struct dirent *entry;
    
    directory = opendir(cwd);
    if (directory != NULL) {
        while ((entry = readdir(directory)) != NULL) {
            printf("Do you want to remove file '%s'? (y/n): ", entry->d_name);
            
            char response;
            scanf(" %c", &response);
            
            if (response == 'y' || response == 'Y') {
                char file_path[1024];
                snprintf(file_path, sizeof(file_path), "%s/%s", cwd, entry->d_name);
                
                if (remove(file_path) == 0) {
                    printf("File '%s' removed successfully.\n", entry->d_name);
                } else {
                    perror("Error removing file");
                }
            }
        }
        closedir(directory);
    } else {
        perror("Error opening directory");
        return 1;
    }
    
    return 0;
}