#include <sys/types.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *
check_zope() 
{
  struct group *zope_group;
  struct passwd *zope_pw, *pw;
  char **mem;

  if ((zope_pw = getpwnam("zope")) == NULL)
    return "FAILED to look up zope group!\n";

  if (geteuid() != zope_pw->pw_uid)
    return "FAILED: the effective user isn't zope";
  
  if ((pw = getpwuid(getuid())) == NULL)
    return "FAILED to get password entry";
  
  if ((zope_group = getgrnam("zope")) == NULL)
    return "FAILED to look up zope group!\n";
  
  for (mem=zope_group->gr_mem; *mem; mem++)
    if (strcmp(*mem, pw->pw_name) == 0)
      return NULL;              /* We're good! */
    
  return "You aren't in the zope group";
}

void
usage() {
  printf("Usage: zu command arg1 arg2 ...\n"
         "\n"
         "Run a command as zope.\n"
         );
}

int
main(int argc, char **argv)
{
  struct passwd *zope_pw;
  char *err;

  if (argc < 2) {
    usage();
    return 2;
  }

  if ((err = check_zope()) != NULL)
    {
      printf(err);
      return 1;
    }

  if (execvp(argv[1], argv+1)) 
    {
      printf("FAILED exec failed\n\n");
      usage();
      return 3;
    }

  return 0;
}
