#include "tests/lib.h"

int main(void) 
{
    // Create two new files
    pid_t pid = exec("shell touch testfile1.txt testfile2.txt");
    if (pid == -1) fail("shell exec failed for multiple files");
    int status = wait(pid);
    if (status != 0) fail("touch failed to create multiple files");

    // Check if files exist
    if (!filesys_file_exists("testfile1.txt") || !filesys_file_exists("testfile2.txt"))
        fail("touch did not create files correctly");

    msg("Multiple file creation test passed");

    // Update timestamp of an existing file
    pid = exec("shell touch testfile1.txt");
    if (pid == -1) fail("shell exec failed for updating timestamp");
    status = wait(pid);
    if (status != 0) fail("touch failed to update timestamp");

    msg("Existing file timestamp update test passed");
    return 0;
}
