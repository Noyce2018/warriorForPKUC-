//
//  main.cpp
//  warrior
//
//  Created by Mac on 2019/8/11.
//  Copyright © 2019年 Mac. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
using namespace std;
//warrior
class warrior
{
    unsigned int warriorId;
    unsigned int attack;
    unsigned int life;
    string type;
public:
    warrior(unsigned int warriorId,unsigned int life,string type)
    {
        this->warriorId=warriorId;
        this->life=life;
        this->type=type;
        
    }
    unsigned int getWarriorId()
    {
        return this->warriorId;
    }
    unsigned int getAttack()
    {
        return this->attack;
    }
    unsigned int getLife()
    {
        return this->life;
    }
    string getType()
    {
        return this->type;
    }
};
//commandArea
class commandArea
{
    string type; //red or blue
    string line[5];
    unsigned int period;//周期
    unsigned int initLive;
    unsigned int remainLive;
public:
    commandArea(string type,unsigned int initLive)
    {
        this->type=type;
        this->initLive=initLive;
        this->remainLive=initLive;
        if(type=="red"){
            line[0]="iceman";
            line[1]="lion";
            line[2]="wolf";
            line[3]="ninja";
            line[4]="dragon";
        }
        if(type=="blue"){
            line[0]="lion";
            line[1]="dragon";
            line[2]="ninja";
            line[3]="iceman";
            line[4]="wolf";
        }
    }
    bool judgeCanContinueProduce(warrior w)
    {
        if(w.getLife()>this->remainLive){
            return false;
        }
        return true;
    }
    
};
int main() {
    return 0;
}
