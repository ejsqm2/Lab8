//Lab8.cpp
#include <iostream>
#include <cstring>
#include <string>
#include <locale>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

class Message{
	protected: 
		string msg;
	public:
		Message();
		Message(string messagestr);
		~Message();
		virtual void printInfo();
};
Message::Message(){
	cout << "No string. Enter message: ";
	cin >> msg;
}
Message::Message(string messagestr){
	cout << "Message String Constructor" << endl;
	msg = messagestr;
	printInfo();
}
Message::~Message(){
	cout << "Message Destructor" << endl;
}
void Message::printInfo(){
	cout << "Message: " << msg << endl;
}
class mcMessage : public Message{
	public: 
		string *tran_msg;
		int index;
		mcMessage(string);//new constructor for derived class
		mcMessage();//new constructor for derived class
		~mcMessage();
		void translate();
		void printInfo();//redefine printInfo function
};
mcMessage::mcMessage() : Message(){
	cout << "mcMessage empty constructor" << endl;
	int strlength = msg.length();//get string length
	tran_msg = new string[strlength];//array of proper length
	translate();
	printInfo();

}
mcMessage::mcMessage(string messagestr) : Message(messagestr){
	cout << "mcMessage constructor" << endl;
	int strlength = msg.length();
	tran_msg = new string[strlength];
	translate();
	printInfo();

}
mcMessage::~mcMessage(){
	delete[] tran_msg;
	cout << "mcMessage Desctructor" << endl;
	
}
void mcMessage::translate(){
	locale loc; //needed for to lower function
	string letters = "abcdefghijklmnopqrstuvwxyz";
	string MorseCode[26] = {".-", "-...", "-.-.", "-..", ".", "..-.",
							"--.", "....", "..", ".---", "-.-", ".-..", 
							"--", "-.", "---", ".--.", "--.-", ".-." , 
							"...", "-", ".._", "...-", ".--", "-..-",
							"-.--", "--.."};//array of morse code letters
	for(int i=0; i<msg.length(); i++){
		index = 0;
		//cout << "msg[i]: " << msg[i] << endl;
		for(int j=0; j<26; j++){//this loop finds out what letter message is
			if(tolower(msg[i]) == letters[j])//if match found
				index = j;//save index
		}
		tran_msg[i] = MorseCode[index];//save correct Morse Code index
		//cout << "Morse code: " << tran_msg[i] << endl;
	}
	
}
void mcMessage::printInfo(){
	cout << endl << "Message: " << msg << endl;
	cout << "Translated Message: ";
	for(int i=0; i<msg.length(); i++){
		cout << tran_msg[i] << " ";
	}
	cout << endl << endl;
}
class msgStack{
	public:
		Message **ptSt;
		int num_obj;
		msgStack();
		~msgStack();
		void printStack();//print after each push/pop
		void push(Message *obj);
		void pop();
};
msgStack::msgStack(){
	cout << "Stack Constructor" << endl;
	ptSt = new Message*;
	for(int i=0; i<10; i++){
		ptSt[i] = NULL;
	}
}
msgStack::~msgStack(){
	cout << "Msg Stack Destructor" << endl;
	delete *ptSt;
}
void msgStack::push(Message *obj){
	
	cout << "PUSHING" << endl;
	for(int i=9; i>=0; i--){//push message to end of stack
		if(ptSt[i] == NULL){
			ptSt[i] = obj;
			return;
		}
	}
}
void msgStack::pop(){
	
	for(int i=0; i<10; i++){
		if(ptSt[i]!=NULL){//first element that has info
			cout << "POPPING" << endl;
			ptSt[i] = NULL;//remove message from stack
			return;
		}
	}
}
void msgStack::printStack(){
	cout << endl << "*****Printing Stack*****" << endl;
	for(int i=0; i<10; i++){
		if(ptSt[i]!=NULL){//if message is stored, print info
			ptSt[i]->printInfo();
		}
	}
}
int main(){
	cout << "Starting program........" << endl << endl;
	
	mcMessage obj1("ObjOne");//preset string
	mcMessage obj2; // empty constructor
	mcMessage obj3("objthree");
	mcMessage obj4("objfour");
	
	msgStack msgst;
	msgst.push(&obj1);
	msgst.push(&obj2);
	msgst.push(&obj3);
	msgst.printStack();
	msgst.pop();
	msgst.push(&obj4);
	
	msgst.printStack();	
	
	return 0;
}