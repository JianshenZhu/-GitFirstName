#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cctype>

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
    cout << "Please input the message." << endl;
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

int main(){
    cout << "Please input the message." << endl;
    string n;
    getline (cin, n);//get user's input
    message M1(n);
    M1.printinfo();//output the message
    morseCodeMessage cM1(n);
    cM1.printinfo();//output the message in morseCode
    messageStack S1;
    S1.push();//do push
    S1.pop();//do pop
    S1.printStack();//output the stuff in the Stack
}