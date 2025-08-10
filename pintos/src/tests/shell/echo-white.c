/** Tests echo command with whitespace-only arguments. */

#include "tests/lib.h"

int
main (void) 
{
  pid_t pid = exec ("shell echo '   ' '  ' ' '");
  if (pid == -1) {
    fail ("shell exec failed with whitespace-only arguments");
  }
  
  int status = wait (pid);
  msg ("Shell exited with status %d for whitespace-only arguments", status);
  
  if (status != 0) {
    fail ("shell should execute echo with whitespace-only arguments successfully");
  }
  
  msg ("Echo whitespace test completed successfully");
  return 0;
}
