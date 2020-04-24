#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<getopt.h>
#include<string.h>
#include<unistd.h>

int p=0,randp;
unsigned int randx;

void getfilename(char* filename)
{
    sprintf(filename,"%08x%08x%08x%08x",randp,(int)getpid(),(unsigned int)time(0),p);
    p++;
}

inline unsigned int xorshift32()
{
	/* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
	unsigned int x = randx;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	randx = x;
	return x;
}

void getbuf(unsigned int* buf)
{
    for(int i=0;i<1024;i++)
        buf[i]=xorshift32();
}

int main(int argc, char *argv[])
{
    char opt=0;
    char const* optstring ="o:n:s:dh";
    char path[1024]="\0",fullpath[1024];
    int num=4,size=1<<18,dit=0,rs;
    while((opt=getopt(argc, argv, optstring))!=-1)
    {
        switch(opt)
        {
            case 'o': sscanf(optarg,"%s",path);
            break;
            case 'n': sscanf(optarg,"%d",&num);
            break;
            case 's': sscanf(optarg,"%d",&size);
            break;
            case 'd': dit=1;
            break;
            case 'h': printf("Usage: -o [path] -n [num] -s [size] -d\n");
            printf("-o Assign a file path, can be left out.\n");
            printf("-n Dicide numbers of rubbish files. Default value is 4\n");
            printf("-s Decide the size of rubbish files. One unit equals to 4KiB. Default value is 2^18 (1GiB). It should no less than 2048\n");
            printf("-d Enable the dithering of file sizes.\n");
            printf("-h Show this page.\n");
            default: break;
        }
    }
    
    char filename[32];
    unsigned int buf[1024];
    srand((int)getpid()+time(0));
    randp=rand();
    randx=rand();
    FILE *outfile;
    rs=size;
    for(int i=0;i<num;i++)
    {
        getfilename(filename);
        strcpy(fullpath,path);
        strcat(fullpath,filename);
        outfile=fopen(fullpath,"wb");
        if(dit) rs=size+rand()%2048-1024;
        for(int j=0;j<rs;j++)
        {
            getbuf(buf);
            fwrite(buf,1,4096,outfile);
        }
        fclose(outfile);
    }
    return 0;
}
