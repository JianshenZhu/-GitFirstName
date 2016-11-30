#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cctype>

int fd;		// for the file descriptor of the special file we need to open.
unsigned long *BasePtr;		// base pointer, for the beginning of the memory page (mmap)
unsigned long *PBDR, *PBDDR;	// pointers for port B DR/DDR
using namespace std;
static string letters = "abcdefghijklmnopqrstuvwxyz";
static string morseCode[] = {
    ".-",   //A
    "-...", //B
    "-.-.", //C
    "-..",  //D
    ".",    //E
    "..-.", //F
    "--.",  //G
    "....", //H
    "..",   //I
    ".---", //J
    "-.-",  //K
    ".-..", //L
    "--",   //M
    "-.",   //N
    "---",  //O
    ".--.", //P
    "--.-", //Q
    ".-.",  //R
    "...",  //S
    "-",    //T
    "..-",  //U
    "...-", //V
    ".--",  //W
    "-..-", //X
    "-.--", //Y
    "--..", //Z
};

class message{//message class
    private:

    protected:
        string msg;
    public:
        message();
        message(string m);
        ~message();
        string str();
        virtual void printinfo();
};

message::message(){//default
    cout << "Please input the message." << endl;
    msg = "";
}

message::message(const string m){//Parametric constructor take in the message
    msg = m;
}

message::~message(){//destructor
    msg.clear();
}

void message::printinfo(){//print the message
    cout << "Message is :" << msg << endl;
}

string message::str(){//to return the message input
    return (msg);
}

class morseCodeMessage : public message{//derived class from message
    private:

    public:
        int index, length, x;
        char *letter;
        string *Code;
        morseCodeMessage(string m);
        ~morseCodeMessage();
        void translate();
	void morseCodetoLight();
        void printinfo();
};

morseCodeMessage::morseCodeMessage(string m) : message(m){
    length = msg.length();
    letter = new char[length+1];
    strcpy (letter, msg.c_str());
    x = 0;
     while (letter[x])
  {
    letter[x] = tolower(letter[x]);//make all the letters in uppercase to lowercase
    x++;
  }
    Code = new string[length];
    translate();//translate the message to morse code
}

morseCodeMessage::~morseCodeMessage(){
    msg.clear();
    delete letter, Code;
}

void morseCodeMessage::translate(){
    for (x = 0; x < length; x++){
    size_t index = letters.find(letter[x]);//to find the letter in the string letters
    if (index!=string::npos){
//    cout << "letters found at: " << index << '\n' << endl;
//    cout << "Which Morse Code is: " << morseCode[index] << '\n' << endl;
        Code[x] = morseCode[index];//take the corresponding morse code
//        cout << Code[x] << endl;
    }
    }
}

void morseCodeMessage::morseCodetoLight(){
	//to turn off all the LED lights
	*PBDR &= ~0x80;
	*PBDR &= ~0x40;
	*PBDR &= ~0x20;
	for (int i =0;i < length; i++){
	x = Code[i].length();// get the length of each Morse code letter
	//cout << x << endl;
	// For one single letter, check the Morse code and if it is '.' make the red light on, if it is '-' let the yello light on
	for (int y = 0;y < x; y++){
		if (Code[i][y] == '.'){
				*PBDDR |= 0x20;
			    *PBDR |= 0x20;
				usleep(500000);
			    *PBDR &= ~0x20;
			    usleep(500000);
		}
		if (Code[i][y] == '-'){
			 	 *PBDDR |= 0x40;
			     *PBDR |= 0x40;
			     usleep(500000);
			     *PBDR &= ~0x40;
			     usleep(500000);
		}
	}
	sleep(1);// sleep one second to indicate the end of this letter
	}
			// let the green light on to indicate the end of the word
				*PBDDR |= 0x80;
				*PBDR |= 0x80;
				 sleep(1);
				 *PBDR &= ~0x80;
				 sleep(1);
}

void morseCodeMessage::printinfo(){//output the message, lowercase message, morse code of the message
    cout << "Message is: " << msg << "\n" << endl
         << "Message in lowercase is: " << letter << "\n" << endl
         << "Morse Code is: ";
    for (int i = 0; i < length; i ++){
    cout << Code[i] << " ";
    }
    cout << "\n" << endl;
}

class messageStack{//Stack class
    private:

    public:
        message *ptrStack[10];
        messageStack();
        ~messageStack();
        void push();
        message pop();
        void printStack();
        int stack_pop;
        int num_of_objects;//to count the messages in the stack
};

messageStack::messageStack(){// a parametric constructor take one message object.
    num_of_objects = 0;
    cout << "Please input the first message in Stack." << endl;
    string n;
    getline (cin, n);
    if (num_of_objects < n.length()){
    ptrStack[num_of_objects] = new message(n);//allocate the memory to the pointer
    num_of_objects++;
    }
    cout << ptrStack[0]->str() << endl;
}

messageStack::~messageStack(){//destructor
    for (int i = 0; i < num_of_objects; i++){
    delete ptrStack[i];
    }
}

void messageStack::push(){//push new message to the stack
    while (num_of_objects < 10){
    cout << "Do you want to push message? (y/n)" << endl;
    char c;
    cin >> c;
    if (c == 'y'){
    cout << "Please input the message." << endl;
    string n;
    cin >> n;
    ptrStack[num_of_objects] = new message(n);
    num_of_objects++;
    cout << ptrStack[num_of_objects-1]->str() << endl;
    }
    else{
        cout << "No message pushed." << endl;
        break;
    }
    }
}

message messageStack::pop(){//pop out the last message pushed into the Stack
    message temp;
    temp = message("ok");
    while (num_of_objects > 1){
    cout << "Do you want to pop message? (y/n)" << endl;
    char c;
    cin >> c;
    if (c == 'y'){
        cout << ptrStack[num_of_objects-1]->str() << endl;
        delete ptrStack[num_of_objects-1];
        num_of_objects--;
//        cout << num_of_objects << endl;
        }
    else{
        cout << "No message poped." << endl;
        break;
    }
    }
    return (temp);
}

void messageStack::printStack(){//print all the messages in the Stack
    for (int i = num_of_objects-1; i >= 0; i--){
    cout << ptrStack[i]->str() << endl;
    }
}

int main(int argc, char **argv){

    fd = open("/dev/mem", O_RDWR|O_SYNC);	// open the special file /dem/mem
	if(fd == -1){
		printf("\n error\n");
	    return(-1);  // failed open
	}

	// We need to map Address 0x80840000 (beginning of the page)
	BasePtr = (unsigned long*)mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0x80840000);
    if(BasePtr == MAP_FAILED){
    	printf("\n Unable to map memory space \n");
    	return(-2);
    }  // failed mmap

	// To access other registers in the page, we need to offset the base pointer to reach the
	// corresponding addresses. Those can be found in the board's manual.
	PBDR = BasePtr + 1;		// Address of port B DR is 0x80840004
    PBDDR = BasePtr + 5;	// Address of port B DDR is 0x80840014

    *PBDDR |= 0x80;			// configures port B7 as output (Green LED)
	*PBDDR &= 0xFFFFFFFE;	// configures port B0 as input (first push button). 

	//turn off all the lights first
	*PBDR &= ~0x80;
	*PBDR &= ~0x40;
	*PBDR &= ~0x20;
	*PBDR |= 0x80;	// ON: write a 1 to port B0. Mask all other bits.
	usleep (250000);	// sleep 0.25 second.
    *PBDR &= ~0x80;	// OFF: write a 0 to port B0. Mask all other bits.
    sleep(1);
    *PBDDR |= 0x40;// yello light ON
     *PBDR |= 0x40;
 	sleep(1);
     *PBDR &= ~0x40;// OFF
     sleep(1);
    *PBDDR |= 0x20;// red light ON
    *PBDR |= 0x20;
	sleep(1);
    *PBDR &= ~0x20;//OFF
    sleep(1);
    //Turn on all the lights
    *PBDR |= 0x80;
    *PBDR |= 0x40;
    *PBDR |= 0x20;

	// If you wanted to read the status of Port B0, how could you do it?
    cout << "Please input the message." << endl;
        string n;
        getline (cin, n);//get user's input
        message M1(n);
        M1.printinfo();//output the message
        morseCodeMessage cM1(n);
        cM1.morseCodetoLight();//turn the LEDs on the auxiliary board according to the Morse code.
        cM1.printinfo();//output the message in morseCode
        messageStack S1;
        S1.push();//do push
        S1.pop();//do pop
        S1.printStack();//output the stuff in the Stack



    close(fd);	// close the special file
    return 0;
}

