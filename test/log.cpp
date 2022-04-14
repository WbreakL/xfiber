#include<iostream>

#include"../log.h"
using namespace std;

ostringstream a;
ostream& fun(){
    return cout;
}

int main(int argc,char* argv[]){
    LOG("error")<<"world";
    
}