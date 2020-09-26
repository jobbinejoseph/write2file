#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFERSIZE 1024
#define SETZERO 0 

char *map;
void write2file(char *text, const char *filepath , int fd,
		unsigned long *filesizenew, int textsize) {
	unsigned long filesizeold;
	struct stat fileinfo;
	int i;
	if(stat(filepath,&fileinfo)== -1){
		perror("stat");
		exit(1);
	}
	filesizeold = fileinfo.st_size;
	*filesizenew = filesizeold + textsize;
	if(ftruncate(fd, *filesizenew) == -1){
		close(fd);
		perror("Error , Resizing file");
		exit(1);
	}
	map = mmap(SETZERO,*filesizenew, PROT_READ | PROT_WRITE , MAP_SHARED ,fd, SETZERO);
	if(map == MAP_FAILED){
		close(fd);
		perror("mmap");
		exit(1);
	}
	for(i = 0; i < textsize;i++) {
		map[i+filesizeold] = text[i];
	}
	if(msync(map, *filesizenew,MS_SYNC)== -1){
		perror("msync");
	}
}

int main(int argc, char *argv[]){
	int fd,offset = 0;
	const char *filepath;
	char c;
	int i = -1;
	char ch[1024];
	FILE *input;
	unsigned long filesizenew;

	input = stdin;

	if(argc != 2 ){
		fprintf(stderr, "Usage : Executable filename\n");
		fprintf(stderr, " 	Example : ./binary file.txt\n");
		exit(1);
	}

	filepath = argv[1];
	if( (fd = open(filepath, O_RDWR | O_CREAT, (mode_t)0664)) == -1) {
		perror("open");
		exit(1);
	}

	fprintf(stderr,"Please enter + ctrlD once done / ctrl+c for cancel \n");
	memset(ch,SETZERO,BUFFERSIZE);

	while(EOF != (c = fgetc(input)) ){
		i = i+1;
		ch[i] = c;
		if(i == BUFFERSIZE){
			ch[i] = c;
			write2file(ch,filepath, fd, &filesizenew , i+1);
			i = -1;
			memset(ch,SETZERO,BUFFERSIZE);
		}
	}

	if(i!= -1 ){
		write2file(ch,filepath, fd, &filesizenew , i+1);
	}
	fprintf(stderr, "\nExit Reading\n");

	if(map && munmap(map,filesizenew) == -1){
		close(fd);
		perror("munmap");
		exit(1);
	}
	close(fd);

	return(0);
}
