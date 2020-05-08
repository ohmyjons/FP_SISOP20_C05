#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
// #include "string.h"

void movebiasa(char *a , char *b){
  
  if ((link(a, b) < 0)  || (unlink(a)<0))
    printf(2, "mv %s to %s failed\n", a, b);
  return;
  unlink(a);
  exit();
  // close();
}
void strcat(char *destination, char *source) {
    int j = strlen(destination);
    for(int i = 0; i < strlen(source); ++i, j++){
        destination[j] = source[i];
    }
    destination[j] = '\0';
    return;
}

void movebintang(char *a ,char *b){

  char tujuan[256];
  memset(tujuan,'\0',sizeof(char));

  // strcat(b,a);
  strcat(tujuan,b);
  strcat (tujuan ,a);

    // printf(2, "mv %s to %s failed\n", a, tujuan);
    
  if ((link(a, tujuan) < 0)  || (unlink(a)<0))
    printf(2, "mv %s to %s failed\n", a, tujuan);
  return;
  unlink(a);
  exit();
  // close();
}



void mvbintang(char *path, char *tuju){
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    printf(2, "failed to remove %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  // char dirtuju[100];
  // asprintf(dirtuju,tuju);

  switch(st.type){
  // fgets(dirtuju,&buf[2]);
  // case T_FILE:
	// movebiasa(&buf[2],tuju);
  //   break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
    //  strcat(tuju,&buf[2]); 
    //  printf(1,"%s\n",tuju);
	  if (st.type == T_FILE) movebintang(&buf[2],tuju);
    }
    break;
  }
  close(fd);
}


int main (int argc, char *argv[]){
  if (argc != 3){
    printf(2, "Usage: mv oldname newname\n");
    exit();
  }

  if (!strcmp(argv[1],"*")){
    mvbintang(".",argv[2]);
  }

  else {
    movebiasa(argv[1],argv[2]);
  }
  
  exit();
}
