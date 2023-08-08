/*Write a program that will only list subdirectories 
in alphabetical order.*/
#include <stdio.h>
#include <dirent.h>
#include <string.h>

int is_directory(const char *path) {
    DIR *directory = opendir(path);
    if (directory != NULL) {
        closedir(directory);
        return 1;
    }
    return 0;
}

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    const char *path = "."; // current directory
    DIR *directory;
    struct dirent *entry;
    char *subdirectories[100]; // assuming a maximum of 100 subdirectories
    
    int i = 0;
    directory = opendir(path);
    if (directory != NULL) {
        while ((entry = readdir(directory)) != NULL) {
            if (is_directory(entry->d_name)) {
                subdirectories[i] = strdup(entry->d_name);
                i++;
            }
        }
        closedir(directory);
    }
    
    qsort(subdirectories, i, sizeof(char *), compare);
    
    for (int j = 0; j < i; j++) {
        printf("%s\n", subdirectories[j]);
        free(subdirectories[j]);
    }
    
    return 0;
}