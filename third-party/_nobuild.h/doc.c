// nobuild.h

void path_join(char *result, Cstr a, Cstr b, ...);

/*
Description: Joins two or more path components together to create a single file path.
Parameters:
    result: A character buffer that will hold the resulting file path.
    a, b, ...: Path components to be joined together.
Example:
    char result[256];
    path_join(result, "dir1", "dir2", "file.txt", NULL);
    printf("%s\n", result);
    // Output: "dir1/dir2/file.txt"
*/

void path_mkdir(Cstr path);

/*
Description: Creates a directory at the specified path.
Parameters:
    path: The path of the directory to be created.
Example:
    path_mkdir("new_directory");
*/

void path_rm(Cstr path);

/*
Description: Removes a file or directory at the specified path.
Parameters:
    path: The path of the file or directory to be removed.
Example:
    path_rm("file.txt");
*/

int is_path1_modified_after_path2(const char *path1, const char *path2);

/*
Description: Checks if the modification time of path1 is greater than the modification time of path2.
Parameters:
    path1: The path of the first file to be compared.
    path2: The path of the second file to be compared.
Returns:
    1 if path1 is modified after path2, 0 otherwise.
Example:
    int result = is_path1_modified_after_path2("file1.txt", "file2.txt");
    if (result) {
        printf("file1.txt is modified after file2.txt\n");
    } else {
        printf("file1.txt is not modified after file2.txt\n");
}
*/

void VLOG(FILE *stream, Cstr tag, Cstr fmt, va_list args);

/*
Description: Logs a formatted message with a specified tag to a file stream.
Parameters:
    stream: The file stream to which the log message will be written (e.g., stdout, stderr).
    tag: The tag to be used in the log message (e.g., "INFO", "WARN", "ERRO").
    fmt: The format string of the log message.
    args: A va_list of arguments to be used in the format string.
Example:
    VLOG(stderr, "INFO", "This is an informational message: %d", 42);
*/

void INFO(Cstr fmt, ...);
void WARN(Cstr fmt, ...);
void ERRO(Cstr fmt, ...);
void PANIC(Cstr fmt, ...);

/*
Description: Convenience functions for logging messages with predefined tags ("INFO", "WARN", "ERRO", "ERRO" respectively).
*/
