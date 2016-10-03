#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>

    FILE *fstream, *ofp;
    int value, size,i,f,t;
    char raw[100], off[100], sca[100], sta[100], cen[100], nor[100], new1[100], new2[100], new3[100], new4[100], new5[100];
    double s, o, mean, max;
//readfile function for open the correct file and read the files.
void readfile(int *p){
       printf("Please input the file number you want to open :");
    	fflush(stdout);
    	sprintf(raw, "Raw_data_%02d.txt", value);//sprint is to print a string and for open and creat the correct files.
    	printf("%s", raw);
    	fflush(stdout);
    	sprintf(off, "offset_data_%02d.txt", value);
    	sprintf(sca, "scaled_data_%02d.txt", value);
        sprintf(sta, "Statistics_data_%02d.txt", value);
        sprintf(cen, "Centered_data_%02d.txt", value);
        sprintf(nor, "Normalized_data_%02d.txt", value);
        fstream=fopen(raw,"r");
}
//offset function for offset the value in the files.
void offset(int *p){
        printf("please enter the offset value");
        fflush(stdout);
        printf("%lf\n", o);
        fflush(stdout);
        ofp = fopen(off, "w");
		fprintf(ofp, "%d %.4lf\n", f, o);//out put the first value and the offset value.
     	for (i=0;i<size;++i){
          fprintf(ofp, "%.4lf\n", *(p+i)+o);//out put the values after offset.
        }
    }
void newoffset(int *p){
        printf("please enter the offset value");
        fflush(stdout);
        printf("%lf\n", o);
        fflush(stdout);
        ofp = fopen(new1, "w");
		fprintf(ofp, "%d %.4lf\n", f, o);//out put the first value and the offset value.
     	for (i=0;i<size;++i){
          fprintf(ofp, "%.4lf\n", *(p+i)+o);//out put the values after offset.
        }
    }
//scale function for scale the value in the files.
void scale(int *p){
        printf("please enter the scaling factor");
        fflush(stdout);
        printf("%lf\n", s);
        fflush(stdout);
        ofp = fopen(sca, "w");
		fprintf(ofp, "%d %.4lf\n", f, s);//out put the first value and the scale factor.
     	for (i=0;i<size;++i){
          fprintf(ofp, "%.4lf\n", *(p+i)*s);//out put the values after scaled.
        }
}
void newscale(int *p){
        printf("please enter the scaling factor");
        fflush(stdout);
        printf("%lf\n", s);
        fflush(stdout);
        ofp = fopen(new2, "w");
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
int main(int argc, char *argv[])
{
    int ia, ib, ic, id, ie, ig, ih, ii;
     int *p;
        for (ii=1;ii<argc;ii++){
    if ((argv[ii][0] == '-') && (argv[ii][1] == 'h')){
        printf("-n: File number (value needed)\n-o: offset value (value needed)\n-s: scale factor (value needed)\n-S: Get statistics\n-C: Center the signal\n-N: Normalize signal\n-r: Rename files (name needed) \nFor example:./My_Lab5_program –s 1.7 –S –N –n 10 will read the file “Raw_data_10.txt”; it should scale the signal by 1.7 (and save the corresponding file “Scaled_data_10.txt”); it should calculate the statistics of the original signal (and save them to the corresponding file); and it should normalize the original signal (again, saving the corresponding file).  \n");
        fflush(stdout);
        exit(0);
    }
    }
    for (ia=1;ia<=argc;ia++){
    if(argc >= 3 && ia>=1){
        if((argv[ia][0] == '-') && (argv[ia][1] == 'n')) {
            value = atoi(argv[ia+1]);
            if (value!=0){
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
            p=malloc((size)*sizeof(int));
        while (fscanf(fstream, "%d", &t) != EOF) {//read the second value of the file which is the maximum possible value.
		for (i=0;i<size;++i){
		fscanf(fstream, "%d", (p+i));//the for loop is to read all the values in the file.
	}
    for (ih=1;ih < argc;ih++){  
    if ((argv[ih][0] == '-') && (argv[ih][1] == 'r')){
    for (ib=1;ib<argc;ib++){
    if((argv[ib][0] == '-') && (argv[ib][1] == 'o')){
        char *q;
        o=strtod(argv[ib+1], &q);
        strcat(new1, argv[ih+1]);
        strcat(new1, "_Offset.txt");
        puts(new1);
        if (o!=0)
       newoffset(p);//do offset.
        else{
            printf("wrong offset option.\nHint:-n: File number (value needed)\n-o: offset value (value needed)\n-s: scale factor (value needed)\n-S: Get statistics\n-C: Center the signal\n-N: Normalize signal\n-r: Rename files (name needed) \nFor example:./My_Lab5_program –s 1.7 –S –N –n 10 will read the file “Raw_data_10.txt”; it should scale the signal by 1.7 (and save the corresponding file “Scaled_data_10.txt”); it should calculate the statistics of the original signal (and save them to the corresponding file); and it should normalize the original signal (again, saving the corresponding file). \n");
            fflush(stdout);
        }
	       }
    }
    for (ic=1;ic<argc;ic++){
    if ((argv[ic][0] == '-') && (argv[ic][1] == 's')){
        char *q;
        s=strtod(argv[ic+1], &q);
        strcat(new2, argv[ih+1]);
        strcat(new2, "_Scaled.txt");
        puts(new2);
        if (s!=0)
        newscale(p);//do scale.
        else{
            printf("wrong scale option.\nHint:-n: File number (value needed)\n-o: offset value (value needed)\n-s: scale factor (value needed)\n-S: Get statistics\n-C: Center the signal\n-N: Normalize signal\n-r: Rename files (name needed) \nFor example:./My_Lab5_program –s 1.7 –S –N –n 10 will read the file “Raw_data_10.txt”; it should scale the signal by 1.7 (and save the corresponding file “Scaled_data_10.txt”); it should calculate the statistics of the original signal (and save them to the corresponding file); and it should normalize the original signal (again, saving the corresponding file). \n");
            fflush(stdout);
        }
            }
    }
    for (id=1;id<argc;id++){
     if ((argv[id][0] == '-') && (argv[id][1] == 'S')){
            strcat(new3, argv[ih+1]);
            strcat(new3, "_Statistics.txt");
            puts(new3);
            ofp = fopen(new3, "w");
            me(p);//calculate mean value.
            ma(p);//find the max value.
          fprintf(ofp, "%.4lf %.4lf\n", mean, max);
            }
    }
    for (ie=1;ie<argc;ie++){
    if ((argv[ie][0] == '-') && (argv[ie][1] == 'C')){
            strcat(new4, argv[ih+1]);
            strcat(new4, "_Centerd.txt");
            puts(new4);
            ofp = fopen(new4, "w");
            me(p);
		fprintf(ofp, "%d %.4lf\n", f, -mean);//print out the first value and the offset value in this case which is left offset the mean value.
     	for (i=0;i<size;++i){
          fprintf(ofp, "%.4lf\n", *(p+i)-mean);
                }
            }
    }
    for (ig=1;ig<argc;ig++){
    if ((argv[ig][0] == '-') && (argv[ig][1] == 'N')){
            strcat(new5, argv[ih+1]);
            strcat(new5, "_Normalized.txt");
            puts(new4);
            ofp = fopen(new5, "w");
            ma(p);
            fprintf(ofp, "%d %.4lf\n", f, 1/max);//print out the first value and the scale factor in this case which is reciprocal of the max value.
                for (i=0;i<size;++i){
          fprintf(ofp, "%.4lf\n", *(p+i)/max);
                    }
                }
            }
        exit(0);
    }        
    }
    for (ib=1;ib<argc;ib++){
    if((argv[ib][0] == '-') && (argv[ib][1] == 'o')){
        char *q;
        o=strtod(argv[ib+1], &q);
        if (o!=0)
       offset(p);//do offset.
        else{
            printf("wrong offset option.\nHint:-n: File number (value needed)\n-o: offset value (value needed)\n-s: scale factor (value needed)\n-S: Get statistics\n-C: Center the signal\n-N: Normalize signal\n-r: Rename files (name needed) \nFor example:./My_Lab5_program –s 1.7 –S –N –n 10 will read the file “Raw_data_10.txt”; it should scale the signal by 1.7 (and save the corresponding file “Scaled_data_10.txt”); it should calculate the statistics of the original signal (and save them to the corresponding file); and it should normalize the original signal (again, saving the corresponding file). \n");
            fflush(stdout);
        }
	       }
    }
    for (ic=1;ic<argc;ic++){
    if ((argv[ic][0] == '-') && (argv[ic][1] == 's')){
        char *q;
        s=strtod(argv[ic+1], &q);
        if (s!=0)
        scale(p);//do scale.
        else{
            printf("wrong scale option.\nHint:-n: File number (value needed)\n-o: offset value (value needed)\n-s: scale factor (value needed)\n-S: Get statistics\n-C: Center the signal\n-N: Normalize signal\n-r: Rename files (name needed) \nFor example:./My_Lab5_program –s 1.7 –S –N –n 10 will read the file “Raw_data_10.txt”; it should scale the signal by 1.7 (and save the corresponding file “Scaled_data_10.txt”); it should calculate the statistics of the original signal (and save them to the corresponding file); and it should normalize the original signal (again, saving the corresponding file). \n");
            fflush(stdout);
        }
            }
    }
    for (id=1;id<argc;id++){
     if ((argv[id][0] == '-') && (argv[id][1] == 'S')){
         ofp = fopen(sta, "w");
            me(p);//calculate mean value.
            ma(p);//find the max value.
          fprintf(ofp, "%.4lf %.4lf\n", mean, max);
            }
    }
    for (ie=1;ie<argc;ie++){
    if ((argv[ie][0] == '-') && (argv[ie][1] == 'C')){
            ofp = fopen(cen, "w");
              me(p);
		fprintf(ofp, "%d %.4lf\n", f, -mean);//print out the first value and the offset value in this case which is left offset the mean value.
     	for (i=0;i<size;++i){
          fprintf(ofp, "%.4lf\n", *(p+i)-mean);
                }
            }
    }
    for (ig=1;ig<argc;ig++){
    if ((argv[ig][0] == '-') && (argv[ig][1] == 'N')){
                ofp = fopen(nor, "w");
               ma(p);
            fprintf(ofp, "%d %.4lf\n", f, 1/max);//print out the first value and the scale factor in this case which is reciprocal of the max value.
                for (i=0;i<size;++i){
          fprintf(ofp, "%.4lf\n", *(p+i)/max);
                    }
                }
            }
            exit(0);
    }
    }
            }
            else{
                printf("wrong readfile.\nHint:-n: File number (value needed)\n-o: offset value (value needed)\n-s: scale factor (value needed)\n-S: Get statistics\n-C: Center the signal\n-N: Normalize signal\n-r: Rename files (name needed) \nFor example:./My_Lab5_program –s 1.7 –S –N –n 10 will read the file “Raw_data_10.txt”; it should scale the signal by 1.7 (and save the corresponding file “Scaled_data_10.txt”); it should calculate the statistics of the original signal (and save them to the corresponding file); and it should normalize the original signal (again, saving the corresponding file). \n");
                fflush(stdout);
                exit(0);
            }
}
        else if (ia==argc-1){
            printf("%d,Wrong message.\nHint:-n: File number (value needed)\n-o: offset value (value needed)\n-s: scale factor (value needed)\n-S: Get statistics\n-C: Center the signal\n-N: Normalize signal\n-r: Rename files (name needed) \nFor example:./My_Lab5_program –s 1.7 –S –N –n 10 will read the file “Raw_data_10.txt”; it should scale the signal by 1.7 (and save the corresponding file “Scaled_data_10.txt”); it should calculate the statistics of the original signal (and save them to the corresponding file); and it should normalize the original signal (again, saving the corresponding file).  ", &ia);
            exit(0);
        }
    }
        else{
            printf("Wrong input!\nHint:-n: File number (value needed)\n-o: offset value (value needed)\n-s: scale factor (value needed)\n-S: Get statistics\n-C: Center the signal\n-N: Normalize signal\n-r: Rename files (name needed) \nFor example:./My_Lab5_program –s 1.7 –S –N –n 10 will read the file “Raw_data_10.txt”; it should scale the signal by 1.7 (and save the corresponding file “Scaled_data_10.txt”); it should calculate the statistics of the original signal (and save them to the corresponding file); and it should normalize the original signal (again, saving the corresponding file). \n ");
        exit(0);
        }
}
    
    fclose(fstream);
    return 0;
}
