#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <string.h>

typedef struct stat stat_t;

//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  if (ans == NULL){
    fprintf(stderr,"Error: malloc in time2str failed\n");
    exit(EXIT_FAILURE);
  }
  char temp1[64];
  char temp2[32];
  const struct tm * t= localtime(when);
  strftime(temp1,512,"%Y-%m-%d %H:%M:%S",t);  
  strftime(temp2,32,"%z",t);
  snprintf(ans,128,"%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

const char * file_type(stat_t call_info){
  switch(call_info.st_mode & S_IFMT){
  case S_IFBLK:
    return "block special file";
  case S_IFCHR:
    return "character special file";
  case S_IFDIR:
    return "directory";
  case S_IFIFO:
    return "fifo";
  case S_IFLNK:
    return "symbolic link";
  case S_IFREG:
    return "regular file";
  case S_IFSOCK:
    return "socket";
  default:
    fprintf(stderr, "Error: stat call has unknown mode field\n");
    exit(EXIT_FAILURE);
  }
}

char is_r_owner(stat_t call_info){
  if (call_info.st_mode & S_IRUSR){
    return 'r';
  }
  else{
    return '-';
  }
}
char is_w_owner(stat_t call_info){
  if (call_info.st_mode & S_IWUSR){
    return 'w';
  }
  else{
    return '-';
  }
}
char is_exe_owner(stat_t call_info){
  if (call_info.st_mode & S_IXUSR){
    return 'x';
  }
  else{
    return '-';
  }
}
char is_r_group(stat_t call_info){
  if (call_info.st_mode & S_IRGRP){
    return 'r';
  }
  else{
    return '-';
  }
}
char  is_w_group(stat_t call_info){
  if (call_info.st_mode & S_IWGRP){
    return 'w';
  }
  else{
    return '-';
  }
}
char is_exe_group(stat_t call_info){
  if (call_info.st_mode & S_IXGRP){
    return 'x';
  }
  else{
    return '-';
  }
}
char is_r_other(stat_t call_info){
  if (call_info.st_mode & S_IROTH){
    return 'r';
  }
  else{
    return '-';
  }
}
char is_w_other(stat_t call_info){
  if (call_info.st_mode & S_IWOTH){
    return 'w';
  }
  else{
    return '-';
  }
}
char is_exe_other(stat_t call_info){
  if (call_info.st_mode & S_IXOTH){
    return 'x';
  }
  else{
    return '-';
  }
}


unsigned int get_major_dev(stat_t call_info){
  return major(call_info.st_rdev);
}

unsigned int get_minor_dev(stat_t call_info){
  return minor(call_info.st_rdev);
}

char * get_access_control(stat_t call_info){
  // check the needed fields of struct first
  
  // the returned string will have 10 characters + null
  char * access = malloc(11 * sizeof(*access));
  if (access != NULL){
    switch(call_info.st_mode & S_IFMT){  // get first char
    case S_IFBLK:
      access[0] = 'b';
      break;
    case S_IFCHR:
      access[0] = 'c';
      break;
    case S_IFDIR:
      access[0] = 'd';
      break;
    case S_IFIFO:
      access[0] = 'p';
      break;
    case S_IFLNK:
      access[0] = 'l';
      break;
    case S_IFREG:
      access[0] = '-';
      break;
    case S_IFSOCK:
      access[0] = 's';
      break;
    default:
      fprintf(stderr,"Error: Invalid stat struct\n");
      free(access);
      exit(EXIT_FAILURE);
    }   
    access[1] = is_r_owner(call_info);
    access[2] = is_w_owner(call_info);
    access[3] = is_exe_owner(call_info);
    access[4] = is_r_group(call_info);
    access[5] = is_w_group(call_info);
    access[6] = is_exe_group(call_info);
    access[7] = is_r_other(call_info);
    access[8] = is_w_other(call_info);
    access[9] = is_exe_other(call_info);
    access[10] = '\0'; // null terminate
    return access;
  }
  else{
    fprintf(stderr, "Could not allocate memory\n");
    exit(EXIT_FAILURE);
  }
}


// need to use struct passwd *getpwuid(uid_t uid)
// use this to look up users name from uid
char * get_user_name(stat_t call_info){
  // you will have to get the name from the struct passwd
  struct passwd * p = getpwuid(call_info.st_uid);
  return p->pw_name;
}

char * get_group_name(stat_t call_info){
  struct group * g = getgrgid(call_info.st_gid);
  return g->gr_name;
}


void mystat(stat_t call_info, const char * call_arg){
  // check to ensure you have a good stat struct
  // Actually nvm, if its here you know it's good (main does the check)
  // !!!!make sure to double check the casting!!!!

  if ((call_info.st_mode & S_IFMT) == S_IFLNK){  // if the file is a sybolic link
    // readlink will tell you how many characters it puts in
    // you will need to null terminate based on how many characters it tells you
    char linktarget[256];
    ssize_t len;
    // first argument parameter is the symbolic link itself (call_arg)
    if ((len = readlink(call_arg, linktarget, 256)) != -1){  // successful call
      linktarget[len] = '\0';
      printf("  File: '%s' -> '%s'\n", call_arg, linktarget); 
    }
    else{
      fprintf(stderr, "Error: readlink call failed\n");
      exit(EXIT_FAILURE);
    }
  }
  else{
    printf("  File: '%s'\n", call_arg);
  }
  
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
	 call_info.st_size, call_info.st_blocks, call_info.st_blksize,
	 file_type(call_info));

  
  if (((call_info.st_mode & S_IFMT) != S_IFCHR) && ((call_info.st_mode & S_IFMT) != S_IFBLK)){
    
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
	   (long unsigned int) call_info.st_dev, (long unsigned int) call_info.st_dev,
	   call_info.st_ino, call_info.st_nlink);
  }
  else{
    
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
	   (long unsigned int) call_info.st_dev, (long unsigned int) call_info.st_dev,
	   call_info.st_ino, call_info.st_nlink, get_major_dev(call_info),
	   get_minor_dev(call_info));
  }
  
  // Fourth line (step 2 & 3)
  char * access = get_access_control(call_info);
  
  printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
  (call_info.st_mode & ~S_IFMT), access, call_info.st_uid, get_user_name(call_info),
  call_info.st_gid, get_group_name(call_info));
  free(access);

  // Last lines (step 4)

  char * atimestr = time2str(&call_info.st_atime, call_info.st_atim.tv_nsec);
  char * mtimestr = time2str(&call_info.st_mtime, call_info.st_mtim.tv_nsec);
  char * ctimestr = time2str(&call_info.st_ctime, call_info.st_ctim.tv_nsec);
  printf("Access: %s\n", atimestr);
  printf("Modify: %s\n", mtimestr);
  printf("Change: %s\n", ctimestr);
  printf(" Birth: -\n");
  free(atimestr);
  free(mtimestr);
  free(ctimestr);
  
}


// NOTE: you do not have to use fancy quotes, you can just use ''

int main(int argc, char ** argv){

  //check for proper usage
  if (argc < 2){
    fprintf(stderr,"stat: missing operand\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc; i++){
  
    stat_t sb_t;   // struct stat to be filled
    const char * stat_arg_name = argv[i];
    
    if (lstat(argv[i], &sb_t) == -1){
      fprintf(stderr, "Error: lstat call failed\n");
      exit(EXIT_FAILURE);
    }
    mystat(sb_t, stat_arg_name);
  }
  return EXIT_SUCCESS;
}

