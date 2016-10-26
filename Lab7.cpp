#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;  // with this, we won't need the std::

FILE *fop, *ofp;
int value, size,i,t;
char *na, *nf, raw[100], c[20], of[]="offset", sc[]="scale", st[]="statistics", ce[]="center", no[]="normalize", nam[100];
double s, o, mean, m;

class Signal{
	private:
		int length;
		int max;
        float *data;
		double average(int *p);
	    double ma(int *p);
        double ave(float *p);
	    double mav(float *p);
	public:
	Signal();  // default constructor.
    Signal(int);  // parametric constructor.
    Signal(const char*);  // parametric constructor.
    ~Signal();  // destructor.
    void number(int value);
    Signal name(const char *na);
    void readfile();
    void offset(int *p);
    void scale(int *p);
    void newoffset(int *p);
    void newscale(int *p);
    void Sig_info();
    void Save_file(char *nf);
};

Signal::Signal(){
    length = 0;
    max = 0;
    data = NULL;
}

Signal::Signal(int value){
    number(value);
}

Signal::Signal(const char* na){
    name(na);
}

Signal::~Signal(){
    delete[] data;
    cout<<"\nDestructor"<<endl;
}
void Signal::number(int value){
	int *p;
    readfile();
    if(fop==NULL)//This is to make sure it will open the file correctly.
    {
        cout << "open file failed!\n" << endl;
        exit(1);
    }
    else
    {
        cout << "open file succeed!\n" << endl;
        cout << "Output the length:" << endl;
        fscanf(fop, "%d", &length);//read the first value in the file which is the size of the file.
        cout << length << endl;
        size=length;
        p = (int*)malloc((size)*sizeof(int));
        while (fscanf(fop, "%d", &t) != EOF) {//read the second value of the file which is the maximum possible value.
		for (i=0;i<size;++i){
		fscanf(fop, "%d", (p+i));//the for loop is to read all the values in the file.
	}
	cout << "Please enter offset or scale or statistics or center or Normalize:" << endl;
	cin >> c;//scan input to meet different tasks.
	if (strcmp(c,of)==0){
       offset(p);//do offset.
	}
    else if (strcmp(c,sc)==0){
        scale(p);//do scale.
            }
    else if (strcmp(c,st)==0){
         ofp = fopen(raw, "w");
            average(p);//calculate mean value.
            ma(p);//find the max value.
          fprintf(ofp, "%.4lf %.4lf\n", mean, m);
    }
    else if (strcmp(c,ce)==0){
                ofp = fopen(raw, "w");
                average(p);
		fprintf(ofp, "%d %.4lf\n", length, -mean);//print out the first value and the offset value in this case which is left offset the mean value.
     	for (i=0;i<size;++i){
          fprintf(ofp, "%.4lf\n", *(p+i)-mean);
        }
            }
    else if (strcmp(c,no)==0){
                ofp = fopen(raw, "w");
                ma(p);
                fprintf(ofp, "%d %.4lf\n", length, 1/m);//print out the first value and the scale factor in this case which is reciprocal of the max value.
                for (i=0;i<size;++i){
          fprintf(ofp, "%.4lf\n", *(p+i)/m);
        }
            }

    else {
            cout << "wrong" << endl;//print out wrong if the input is not one of the correct tasks.
        }
	}
    }
    fclose(fop);
    fclose(ofp);
}

Signal Signal::name(const char *na){
     int *p;
    cout << "Please input the file number." << endl;
    cin >> value;
    cout << value << endl;
    readfile();
    if(fop==NULL)//This is to make sure it will open the file correctly.
    {
        cout << "open file failed!\n" << endl;
        exit(1);
    }
    else
    {
        cout << "open file succeed!\n" << endl;
        cout << "Output the length:" << endl;
        fscanf(fop, "%d", &length);//read the first value in the file which is the size of the file.
        cout << length << endl;
        size=length;
        p=(int*)malloc((size)*sizeof(int));
        while (fscanf(fop, "%d", &t) != EOF) {//read the second value of the file which is the maximum possible value.
		for (i=0;i<size;++i){
		fscanf(fop, "%d", (p+i));//the for loop is to read all the values in the file.
	}
	cout << "Please enter offset or scale or statistics or center or Normalize:" << endl;
	cin >> c;//scan input to meet different tasks.
	if (strcmp(c,of)==0){
       newoffset(p);//do offset.
	}
    else if (strcmp(c,sc)==0){
        newscale(p);//do scale.
            }
    else if (strcmp(c,st)==0){
            char nna[100];
            sprintf(nna, "%s_statistics_%02d.txt", na, value);
            puts(nna);
            ofp = fopen(nna, "w");
            average(p);//calculate mean value.
            ma(p);//find the max value.
          fprintf(ofp, "%.4lf %.4lf\n", mean, m);
    }
    else if (strcmp(c,ce)==0){
                char nna[100];
                sprintf(nna, "%s_center_%02d.txt", na, value);
                puts(nna);
                ofp = fopen(nna, "w");
                average(p);
		fprintf(ofp, "%d %.4lf\n", length, -mean);//print out the first value and the offset value in this case which is left offset the mean value.
     	for (i=0;i<size;++i){
          fprintf(ofp, "%.4lf\n", *(p+i)-mean);
        }
            }
    else if (strcmp(c,no)==0){
                char nna[100];
                sprintf(nna, "%s_normalize_%02d.txt", na, value);
                puts(nna);
                ofp = fopen(nna, "w");
                ma(p);
                fprintf(ofp, "%d %.4lf\n", length, 1/m);//print out the first value and the scale factor in this case which is reciprocal of the max value.
                for (i=0;i<size;++i){
          fprintf(ofp, "%.4lf\n", *(p+i)/m);
        }
            }

    else {
            cout << "wrong" << endl;//print out wrong if the input is not one of the correct tasks.
        }
	}
    }
    fclose(fop);
    fclose(ofp);
}

//readfile function for open the correct file and read the files.
void Signal::readfile(){
    	sprintf(raw, "Raw_data_%02d.txt", value);//sprint is to print a string and for open and creat the correct files.
    	cout << raw << endl;
        fop=fopen(raw,"r");
}

//offset function for offset the value in the files.
void Signal::offset(int *p){
        cout << "please enter the offset value" << endl;
        cin >> o;
        cout << o << endl;
        ofp = fopen(raw, "w");
		fprintf(ofp, "%d %.4lf\n", length, o);//out put the first value and the offset value.
     	for (i=0;i<size;++i){
          fprintf(ofp, "%.4lf\n", *(p+i)+o);//out put the values after offset.
        }
    }
//newoffset function for offset the value and output data in a file named by the customer.
void Signal::newoffset(int *p){
        cout << "please enter the offset value" << endl;
        cin >> o;
        cout << o << endl;
        char nna[100];
        sprintf(nna, "%s_offset_%02d.txt", na, value);
        puts(nna);
        ofp = fopen(nna, "w");
		fprintf(ofp, "%d %.4lf\n", length, o);//out put the first value and the offset value.
     	for (i=0;i<size;++i){
          fprintf(ofp, "%.4lf\n", *(p+i)+o);//out put the values after offset.
        }
    }
//scale function for scale the value in the files.
void Signal::scale(int *p){
        cout << "please enter the scaling factor" << endl;
        cin >> s;
        cout << s << endl;
        ofp = fopen(raw, "w");
		fprintf(ofp, "%d %.4lf\n", length, s);//out put the first value and the scale factor.
     	for (i=0;i<size;++i){
          fprintf(ofp, "%.4lf\n", *(p+i)*s);//out put the values after scaled.
        }
}
//newscale function for offset the value and output data in a file named by the customer.
void Signal::newscale(int *p){
       cout << "please enter the scaling factor" << endl;
        cin >> s;
        cout << s << endl;
        char nna[100];
        sprintf(nna, "%s_scale_%02d.txt", na, value);
        puts(nna);
        ofp = fopen(nna, "w");
		fprintf(ofp, "%d %.4lf\n", length, s);//out put the first value and the scale factor.
     	for (i=0;i<size;++i){
          fprintf(ofp, "%.4lf\n", *(p+i)*s);//out put the values after scaled.
        }
}
//average function for calculate the mean value of all the values in the files.
double Signal::average(int *p){
                mean=0;
     	for (i=0;i<size;++i){
                mean+=*(p+i);
        }
                mean/=size;
                cout << "Output the Average:" << endl;
                cout << mean << endl;
                return mean;
}
//ma function for find the max value in the files.
double Signal::ma(int *p){
                m=0;
            for (i=0;i<size;++i){
            if (*(p+i)>m)
                m=*(p+i);
            }
                cout << "Output the Max:" << endl;
                cout << m << endl;
                return m;
}
//ave function for calculate the mean value of all the values in the files.
double Signal::ave(float *p){
                mean=0;
     	for (i=0;i<size;++i){
                mean+=*(p+i);
        }
                mean/=size;
                cout << "Output the Average:" << endl;
                cout << mean << endl;
                return mean;
}
//mav function for find the max value in the files.
double Signal::mav(float *p){
                m=0;
            for (i=0;i<size;++i){
            if (*(p+i)>m)
                m=*(p+i);
            }
                cout << "Output the Max:" << endl;
                cout << m << endl;
                return m;
}

void Signal::Sig_info(){//used to cout info
                float *p;
                float w;
                cout << "Please input the file number." << endl;
                cin >> value;
                cout << value << endl;
                readfile();
                if(fop==NULL)//This is to make sure it will open the file correctly.
                {
                    cout << "open file failed!\n" << endl;
                    exit(1);
                }
                        else
                {
                    cout << "open file succeed!\n" << endl;
                    cout << "Output the length:" << endl;
                    fscanf(fop, "%d", &length);//read the first value in the file which is the size of the file.
                    cout << length << endl;
                    size=length;
                    p=(float*)malloc((size)*sizeof(int));
                    while (fscanf(fop, "%f", &w) != EOF) {//read the second value of the file which is the maximum possible value.
		            for (i=0;i<size;++i){
		            fscanf(fop, "%f", (p+i));//the for loop is to read all the values in the file.
	                   }
                    ave(p);//calculate mean value.
                    mav(p);//find the max value.
            }
        }
}

void Signal::Save_file(char *nf){//used to save the data in new file
    readfile();
    if(fop==NULL)//This is to make sure it will open the file correctly.
    {
        cout << "open file failed!\n" << endl;
        exit(1);
    }
    else
    {   
        float w;
        cout << "open file succeed!\n" << endl;
        fscanf(fop, "%d", &length);//read the first value in the file which is the size of the file.
        size=length;
        data =(float*)malloc((size)*sizeof(int));
        while (fscanf(fop, "%f", &w) != EOF) {//read the second value of the file which is the maximum possible value.
		for (i=0;i<size;++i){
		fscanf(fop, "%f", (data+i));//the for loop is to read all the values in the file.
	}
    char nnb[100];
    sprintf(nnb, "%s_data_%02d.txt", nf, value);
    puts(nnb);
    ofp = fopen(nnb, "w");
    fprintf(ofp, "%d %f\n", length, w);
    for (i=0;i<size;++i){
        fprintf(ofp, "%f\n", *(data+i));
    }
}
}
}

int main(int argc, char *argv[])
{
    while (1){
        if (argc >= 2){//check the command have 2 or more arguments or not
        if ((argv[1][0] == '-') && (argv[1][1] == 'n')){//if input -n then do this
        	char *q;
            value = strtod(argv[2], &q);
            cout << value << endl;
            Signal Signal1(value);
            exit(1);
        }
        else if ((argv[1][0] == '-') && (argv[1][1] == 'f')){//if input -f then do this
            na = nam;
            strcat(nam, argv[2]);
            Signal Signal2(na);
            exit(1);
        }
        }
        else {//if no correct command, then do it manually
            char c;
            cout << "Please input a (To open the file by file number) or b (To creat a new file) or e (exit), otherwise, call the default constructor." << endl;
            c=getchar();
            switch(c){//check the input value
            case 'a':{
                cout << "Please input the file number." << endl;
                cin >> value;
                cout << value << endl;
                Signal Signal1(value);
                cout << "Do you want to display info (y/n)" << endl;
                char info;
                cin >> info;
                if (info == 'y'){
                Signal1.Sig_info();//cout info
                cout << "Do you want to save info (y/n)" << endl;
                    char save;
                    cin >> save;
                    if ( save == 'y'){
                        cin >> nam;
                        nf = nam;
                        Signal1.Save_file(nf);// save data in new file
                        break;
                    }
                    else 
                        break;
                }
                else {
                    cout << "Do you want to save info (y/n)" << endl;
                    char save;
                    cin >> save;
                    if ( save == 'y'){
                        cin >> nam;
                        nf = nam;
                        Signal1.Save_file(nf);//save data in new file
                        break;
                    }
                    else 
                        break;
                }
            }
            case 'b':{
                cout << "Please input the name of your new file." << endl;
                cin >> nam;
                cout << nam << endl;
                na = nam;
                Signal Signal2(na);
                cout << "Do you want to display info (y/n)" << endl;
                char info;
                cin >> info;
                if (info == 'y'){
                Signal2.Sig_info();//cout info
//                cout << "Do you want to save info (y/n)" << endl;
//                    char save;
//                    cin >> save;
//                    if ( save == 'y'){
//                        cin >> nam;
//                        nf = nam;
//                        Signal2.Save_file(nf);
//                        break;
//                    }
//                    else 
                        break;
                }
                else {
//                    cout << "Do you want to save info (y/n)" << endl;
//                    char save;
//                    cin >> save;
//                    if ( save == 'y'){
//                        cin >> nam;
//                        nf = nam;
//                        Signal2.Save_file(nf);
//                        break;
//                    }
//                    else
                        break;
                }
            }     
            case 'e':{
                exit(1);
            }
            default:{
                Signal Signal3();
                break;
            }    
            }
        }
    }
    }
