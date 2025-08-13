#include "tests/lib.h"
#include <string.h>

int main(void) 
{
    char buf[64];
    int len;

    // Redirect 'hello' to file1.txt
    pid_t pid = exec("shell echo hello > file1.txt");
    if (pid == -1) fail("shell exec failed for first redirection");
    int status = wait(pid);
    if (status != 0) fail("first redirection failed");

    len = read_file("file1.txt", buf, sizeof(buf));
    if (len < 0) fail("failed to read file1.txt");
    buf[len] = '\0';
    if (strcmp(buf, "hello\n") != 0) fail("file1.txt does not contain 'hello'");

    // Redirect 'world' to file2.txt
    pid = exec("shell echo world > file2.txt");
    if (pid == -1) fail("shell exec failed for second redirection");
    status = wait(pid);
    if (status != 0) fail("second redirection failed");

    len = read_file("file2.txt", buf, sizeof(buf));
    if (len < 0) fail("failed to read file2.txt");
    buf[len] = '\0';
    if (strcmp(buf, "world\n") != 0) fail("file2.txt does not contain 'world'");

    msg("Multiple echo redirections test passed");
    return 0;
}
