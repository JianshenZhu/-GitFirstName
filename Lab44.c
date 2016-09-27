#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>

    FILE *fstream, *ofp;
    int x, size,i,f,t;
    char raw[100], off[100], sca[100], sta[100], cen[100], nor[100], c[20], of[]="offset", sc[]="scale", st[]="statistics", ce[]="center", no[]="normalize";
    double s, o, mean, max;
//readfile function for open the correct file and read the files.
void readfile(int *p){
       printf("Please input the file number you want to open :");
    	fflush(stdout);
    	scanf("%d", &x);
    	sprintf(raw, "Raw_data_%02d.txt", x);//sprint is to print a string and for open and creat the correct files.
    	printf("%s", raw);
    	fflush(stdout);
    	sprintf(off, "offset_data_%02d.txt", x);
    	sprintf(sca, "scaled_data_%02d.txt", x);
        sprintf(sta, "Statistics_data_%02d.txt", x);
        sprintf(cen, "Centered_data_%02d.txt", x);
        sprintf(nor, "Normalized_data_%02d.txt", x);
        fstream=fopen(raw,"r");
}
//offset function for offset the value in the files.
void offset(int *p){
        printf("please enter the offset value");
        fflush(stdout);
        scanf("%lf", &o);
        printf("%lf\n", o);
        fflush(stdout);
        ofp = fopen(off, "w");
		fprintf(ofp, "%d %.4lf\n", f, o);//out put the first value and the offset value.
     	for (i=0;i<size;++i){
          fprintf(ofp, "%.4lf\n", *(p+i)+o);//out put the values after offset.
        }
    }
//scale function for scale the value in the files.
void scale(int *p){
        printf("please enter the scaling factor");
        fflush(stdout);
        scanf("%lf", &s);
        printf("%lf\n", s);
        fflush(stdout);
        ofp = fopen(sca, "w");
		fprintf(ofp, "%d %.4lf\n", f, s);//out put the first value and the scale factor.
     	for (i=0;i<size;++i){
          fprintf(ofp, "%.4lf\n", *(p+i)*s);//out put the values after scaled.
        }
}
//me function for calculate the mean value of all the values in the files.
void me(int *p){
     mean=0;
     	for (i=0;i<size;++i){
                mean+=*(p+i);
        }
                mean/=size;
                printf("%lf", mean);
                fflush(stdout);
}
//ma function for find the max value in the files.
void ma(int *p){
     max=0;
            for (i=0;i<size;++i){
            if (*(p+i)>max)
                max=*(p+i);
            }
                printf("%lf", max);
                fflush(stdout);
}
int main()
{
    int *p=malloc((size)*sizeof(int));
    readfile(p);
    if(fstream==NULL)//This is to make sure it will open the file correctly.
    {
        printf("open file failed!\n");
    	fflush(stdout);
        exit(1);
    }
    else
    {
        printf("open file succeed!\n");
    	fflush(stdout);
            printf("Please input size:");
        	fflush(stdout);
        	fscanf(fstream, "%d", &f);//read the first value in the file which is the size of the file.
        	printf("%d\n", f);
         	fflush(stdout);
         	size=f;
        while (fscanf(fstream, "%d", &t) != EOF) {//read the second value of the file which is the maximum possible value.
		for (i=0;i<size;++i){
		fscanf(fstream, "%d", (p+i));//the for loop is to read all the values in the file.
	}
	printf("Please enter offset or scale or statistics or center or Normalize:");
	fflush(stdout);
	scanf("%s", c);//scan input to meet different tasks.
	if (strcmp(c,of)==0){
       offset(p);//do offset.
	}
    else if (strcmp(c,sc)==0){
        scale(p);//do scale.
            }
    else if (strcmp(c,st)==0){
         ofp = fopen(sta, "w");
            me(p);//calculate mean value.
            ma(p);//find the max value.
          fprintf(ofp, "%.4lf %.4lf\n", mean, max);
    }
    else if (strcmp(c,ce)==0){
                ofp = fopen(cen, "w");
              me(p);
		fprintf(ofp, "%d %.4lf\n", f, -mean);//print out the first value and the offset value in this case which is left offset the mean value.
     	for (i=0;i<size;++i){
          fprintf(ofp, "%.4lf\n", *(p+i)-mean);
        }
            }
    else if (strcmp(c,no)==0){
                ofp = fopen(nor, "w");
               ma(p);
                fprintf(ofp, "%d %.4lf\n", f, 1/max);//print out the first value and the scale factor in this case which is reciprocal of the max value.
                for (i=0;i<size;++i){
          fprintf(ofp, "%.4lf\n", *(p+i)/max);
        }
            }
                
    else {
            printf("wrong");//print out wrong if the input is not one of the correct tasks.
            fflush(stdout);
        }    
	}
    } 
    fclose(fstream);
    return 0;
}
