
//#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>

#include <gdbm.h>

static char bigbuf[1048576];

int main(int argc, char **argv)
{
  
  int i;
  datum key, val;


  if (strcmp(basename(argv[0]),"gdbm2dump")==0) {

    if (argc <= 2) { printf("usage:%s <gdbmfile> <dumpfile>\n",basename(argv[0])); return(1); }

    fprintf(stderr,"Dumping GDBM file %s to flat file %s\n",argv[1],argv[2]);

    GDBM_FILE dbf = gdbm_open(argv[1],0,GDBM_READER,0400,0);
    if (dbf == NULL) { perror("Open"); return(1); }

    FILE* out = fopen(argv[2],"w");
    if (out == NULL) { perror("Open"); return(1); }

    i = 0;

    key = gdbm_firstkey(dbf);
    while (key.dptr != NULL) {

      i++;
      val = gdbm_fetch(dbf,key);
      fprintf(out,"|%d|%s|%d|%s|\n",strlen(key.dptr),key.dptr,strlen(val.dptr),val.dptr);

      key = gdbm_nextkey(dbf,key);

    }

    fclose(out);

    gdbm_close(dbf);

    fprintf(stderr,"Dumped %d rows from GDBM file\n",i);

  } else if (strcmp(basename(argv[0]),"dump2gdbm")==0) {

    if (argc <= 2) { printf("usage:%s <dumpfile> <gdbmfile>\n",basename(argv[0])); return(1); }

    fprintf(stderr,"Converting flat file %s to GDBM file %s\n",argv[1],argv[2]);

    FILE* dump = fopen(argv[1],"r");
    if (dump == NULL) { perror("Open"); return(1); }

    i = 0;

    char* ptr;
    while ((ptr=fgets(bigbuf,1048576,dump))!=NULL) {

      i++;
      fprintf(stderr,"[%d][%s]\n",i,ptr);

      char* p = strchr(ptr,'|');
	
      
    }

    fclose(dump);

    fprintf(stderr,"Converted %d rows from flat file\n",i);

  }

}

