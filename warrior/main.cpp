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
//static int LINE=10000;
using namespace std;
//get max
unsigned int getMax(unsigned int a,unsigned int b)
{
    if(a>b){
        return a;
    }
    return b;
}
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
    string printMap[10000];
    unsigned int period;//周期
    unsigned int initLive;
    unsigned int remainLive;
    unsigned int warriorLifeSum;
public:
    unsigned int times;//
    commandArea(string type,unsigned int initLive,unsigned int *lineArray)
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
        this->warriorLifeSum=this->getwarriorLifeSum(lineArray);
        this->period=this->getPeriod();
        this->times=this->getTimes(lineArray);
    }
    unsigned int getwarriorLifeSum(unsigned int *lineArray)
    {
        unsigned int sum=0;
        for(int i=0;i<5;i++)
        {
            sum=sum+lineArray[i];
        }
        return sum;
    }
    unsigned int getPeriod()
    {
        return (this->initLive)%(this->warriorLifeSum);
        
    }
    unsigned int getTimes(unsigned int *lineArray)
    {
        //not enough
        if(this->period==this->initLive){
            return getTimesForNotEnough(lineArray);
            
        }
        //can get int period
        if(this->period==0){
            return (this->initLive)/(this->warriorLifeSum)*5;
        }
        //remain last
        return 0;
    }
    bool judgeCanContinueProduce(warrior w)
    {
        if(w.getLife()>this->remainLive){
            return false;
        }
        return true;
    }
    void produceWarrior(int time)
    {
        
    }
    unsigned int getTimesForNotEnough(unsigned int *lineArray)
    {
        unsigned int sum=0;
        unsigned int times;
        for(int i=0;i<5;i++)
        {
            sum=sum+lineArray[i];
            if(sum>this->initLive){
                times=--i;
                break;
            }
        }
        return times;
    }
    void stopProduceWarrior()
    {
        
    }
    
};
void dealWarrior()
{
    unsigned int a=20;
    unsigned int b[5]={3,4,5,6,7};
    commandArea red=commandArea("red",a,b);
    unsigned int redtime=red.times;
    commandArea blue=commandArea("blue",a,b);
    unsigned int bluetime=blue.times;
    unsigned maintime=max(redtime,bluetime);
    for(int i=0;i<maintime;i++)
    {
        red.produceWarrior(i);
        blue.produceWarrior(i);
    }
    
    
}
int main() {

    


    return 0;
}
