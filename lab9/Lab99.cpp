#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>

using namespace std;  // with this, we won't need the std::

FILE *fop, *ofp;
int value, size,i,t, *p, val, x, y;
char *na, *nf, raw[100],raw2[100], c[20], of[]="offset", sc[]="scale", st[]="statistics", ce[]="center", no[]="normalize", nam[100];
double s, o, mean, m, *pp;

class Signal{
	private:
		
        
        double ave(float *p);
	    double mav(float *p);
	public:
	int *data;
	int length;
	float avera;
	float max;
	Signal();  // default constructor.
    Signal(int x);  // parametric constructor.
    Signal(const char*);  // parametric constructor.
    ~Signal();  // destructor.
    Signal number(int *p);
    Signal name(int *p);
    void readfile();
    void offset(int *p);
    void scale(int *p);
    void newoffset(int *p);
    void newscale(int *p);
    void Sig_info();
    void info();
    void Save_file(char *nf);
    double average(int *p);
    double ma(int *p);
    void operator+(double &x);
    void operator*(double &fa);
};

Signal::Signal(){
    max = 0;
    avera = 0;
    data = (int*)malloc((size)*sizeof(int));
}

Signal::Signal(int x){
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
	data = (int*)malloc((size)*sizeof(int));
        while (fscanf(fop, "%d", &t) != EOF) {//read the second value of the file which is the maximum possible value.
		for (i=0;i<size;++i){
		fscanf(fop, "%d", (p+i));//the for loop is to read all the values in the file.
		*(data+i) = *(p+i);
	}
 //   number(p);
}
}
}

Signal::Signal(const char* na){
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
 //   name(p);
}
}
}

Signal::~Signal(){
    cout<<"\nDestructor"<<endl;
}

//readfile function for open the correct file and read the files.
void Signal::readfile(){
    	sprintf(raw, "Raw_data_%02d.txt", value);//sprint is to print a string and for open and creat the correct files.
    	cout << raw << endl;
        fop=fopen(raw,"r");
}

//average function for calculate the mean value of all the values in the files.
double Signal::average(int *p){
                mean=0;
     	for (i=0;i<size;++i){
                mean+=*(data+i);
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
            if (*(data+i)>m)
                m=*(data+i);
            }
                cout << "Output the Max:" << endl;
                cout << m << endl;
                return m;
}

void Signal::info(){
	cout << "max = " << max << endl;
	cout << "average = " << avera << endl;
	for (int i = 0; i < size; i++){
	cout << "data = " << *(data+i) << endl;
}
}


Signal operator+(Signal &lhs, Signal &rhs)
{
	Signal maxx;
	if (lhs.ma(lhs.data) > rhs.ma(rhs.data))
	maxx.max = lhs.ma(lhs.data);
else
maxx.max = rhs.ma(rhs.data);
cout << lhs.average(lhs.data) << rhs.average(rhs.data) << endl;
	maxx.avera = (lhs.average(lhs.data) + rhs.average(rhs.data))/2;
	for (int i = 0; i < lhs.length; i ++){
	*(maxx.data+i) = *(lhs.data+i) + *(rhs.data+i);
}
	
	return maxx;
}

int main(int argc, char *argv[])
{
	cout << "Please input the file number 1." << endl;
                cin >> value;
                
	Signal Sig1(value);
	cout << "Please input the file number 2." << endl;
                cin >> value;
Signal Sig2(value), Sig3;
	if (Sig1.length == Sig2.length){
	Sig3 = operator+(Sig1, Sig2);
	Sig3.info();
}
    }
