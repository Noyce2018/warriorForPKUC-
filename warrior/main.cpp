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
    
    unsigned int period;//周期
    unsigned int initLive;
    unsigned int remainLive;
    unsigned int warriorLifeSum;
    
public:
    string printMap[10000];
    string line[5];
    int lineNumber[5];
    string type; //red or blue
    unsigned int times;
    unsigned int printMapLength;
    //dragon 、ninja、iceman、lion、wolf
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
            //
            lineNumber[0]=lineArray[2];
            lineNumber[1]=lineArray[3];
            lineNumber[2]=lineArray[4];
            lineNumber[3]=lineArray[1];
            lineNumber[4]=lineArray[0];
        }
        if(type=="blue"){
            line[0]="lion";
            line[1]="dragon";
            line[2]="ninja";
            line[3]="iceman";
            line[4]="wolf";
            //
            lineNumber[0]=lineArray[3];
            lineNumber[1]=lineArray[0];
            lineNumber[2]=lineArray[1];
            lineNumber[3]=lineArray[2];
            lineNumber[4]=lineArray[4];
        }
        
        this->warriorLifeSum=this->getwarriorLifeSum(lineArray);//总数
        this->period=this->getPeriod();       //周期
        this->times=this->getTimes(lineArray);//一共输出的次数
        this->printMapLength=this->times+1;   //增加停止输出
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
    void produceWarrior()
    {
        //
        if(this->times<5)
        {
            this->storeProduceInfoNotEnough();
        }
    }
    void storeProduceInfoNotEnough()
    {
        int line;
        for(int i=0;i<this->times;i++){
            //head
            string time=to_string(i);  //id
            string commandAreaType=this->type;
            string warriorType=this->line[i];
            string id=to_string(i+1);
            string temp="born with strength";
            string target=time+" "+commandAreaType+" "+warriorType+" "+id+" "+temp+" "+to_string(lineNumber[i]);
            //tail
            string tail="1 "+warriorType+" in " +this->type+ " headquarter";
            printMap[i]=target+","+tail;
            line=i;
        }
        printMap[line++]=this->stopProduceWarrior();
    }
    unsigned int getTimesForNotEnough(unsigned int *lineArray)
    {
        unsigned int sum=0;
        unsigned int times;
        for(int i=0;i<5;i++)
        {
            sum=sum+lineArray[i];
            if(sum>this->initLive){
                times=i;
                break;
            }
        }
        return times;
    }
    //stop
    string stopProduceWarrior()
    {
        string tail="headquarter stops making warriors";
        string str=this->type+" "+tail;
        return str;
    }
};
void dealWarrior()
{
    unsigned int a=20;
    unsigned int b[5]={3,4,5,6,7};
    commandArea red=commandArea("red",a,b);
    commandArea blue=commandArea("blue",a,b);
    red.produceWarrior();
    blue.produceWarrior();
    for(int i=0;i<red.printMapLength;i++){
        cout<<red.printMap[i]<<endl;
        cout<<blue.printMap[i]<<endl;
    }
    
    
    
//    unsigned int redtime=red.times;
//    commandArea blue=commandArea("blue",a,b);
//    unsigned int bluetime=blue.times;
//    unsigned maintime=max(redtime,bluetime);

    
    
}
int main() {

    
    dealWarrior();

    return 0;
}
