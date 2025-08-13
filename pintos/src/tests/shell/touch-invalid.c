#include "tests/lib.h"

int main(void) 
{
    // Attempt to create a valid file and an invalid path
    pid_t pid = exec("shell touch validfile.txt /invalid/path/file.txt");
    if (pid == -1) fail("shell exec failed for mixed valid/invalid paths");
    int status = wait(pid);
    
    // Should still succeed for valid file
    if (!filesys_file_exists("validfile.txt"))
        fail("touch failed to create valid file when invalid path given");

    msg("Mixed valid/invalid path test passed with shell exit status %d", status);
    return 0;
}
