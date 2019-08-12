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
static const int MAX_MAP_LENGTH=10000;
static const int WARRIOR_TYPE_NUM=5;
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
public:
    unsigned int life;
    string type;
    warrior(string type,unsigned int life)
    {
      this->type=type;
      this->life=life;
    }
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
//count
class warriorInfo
{
public:
    warrior *w;
    string name;
    unsigned int count;
    warriorInfo(warrior *w)
    {
        this->w=w;
        this->name=w->type;
        this->count=0;
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
    //end
    warrior *lastWarriorList[WARRIOR_TYPE_NUM-1];  //最后一组
    warrior *warriorTypeList[WARRIOR_TYPE_NUM];    //武士列表
    warriorInfo *warriorInfoList[WARRIOR_TYPE_NUM];//武士信息表，多了一个计数
    string printMap[MAX_MAP_LENGTH];
    string type; //red or blue
    unsigned int times;
    unsigned int printMapLength;
    unsigned int lastWarriorListLength;
    //dragon 、ninja、iceman、lion、wolf
    commandArea(string type,unsigned int initLive,unsigned int *lineArray)
    {
        this->type=type;
        this->initLive=initLive;
        this->remainLive=initLive;
        warrior *temp;
        warriorInfo *temp_warriorInfo;
        if(type=="red"){
            //
            temp=new warrior("iceman",lineArray[2]);
            temp_warriorInfo=new warriorInfo(temp);
            warriorTypeList[0]=temp;
            warriorInfoList[0]=temp_warriorInfo;
            //
            temp=new warrior("lion",lineArray[3]);
            temp_warriorInfo=new warriorInfo(temp);
            warriorTypeList[1]=temp;
            warriorInfoList[1]=temp_warriorInfo;
            //
            temp=new warrior("wolf",lineArray[4]);
            temp_warriorInfo=new warriorInfo(temp);
            warriorTypeList[2]=temp;
            warriorInfoList[2]=temp_warriorInfo;
            //
            temp=new warrior("ninja",lineArray[1]);
            temp_warriorInfo=new warriorInfo(temp);
            warriorTypeList[3]=temp;
            warriorInfoList[3]=temp_warriorInfo;
            //
            temp=new warrior("dragon",lineArray[0]);
            temp_warriorInfo=new warriorInfo(temp);
            warriorTypeList[4]=temp;
            warriorInfoList[4]=temp_warriorInfo;
            
        }
        if(type=="blue"){
            temp=new warrior("lion",lineArray[3]);
            temp_warriorInfo=new warriorInfo(temp);
            warriorTypeList[0]=temp;
            warriorInfoList[0]=temp_warriorInfo;
            //
            temp=new warrior("dragon",lineArray[0]);
            temp_warriorInfo=new warriorInfo(temp);
            warriorTypeList[1]=temp;
            warriorInfoList[1]=temp_warriorInfo;
            //
            temp=new warrior("ninja",lineArray[1]);
            temp_warriorInfo=new warriorInfo(temp);
            warriorTypeList[2]=temp;
            warriorInfoList[2]=temp_warriorInfo;
            //
            temp=new warrior("iceman",lineArray[2]);
            temp_warriorInfo=new warriorInfo(temp);
            warriorTypeList[3]=temp;
            warriorInfoList[3]=temp_warriorInfo;
            //
            temp=new warrior("wolf",lineArray[4]);
            temp_warriorInfo=new warriorInfo(temp);
            warriorTypeList[4]=temp;
            warriorInfoList[4]=temp_warriorInfo;
        }
        
        this->warriorLifeSum=this->getwarriorLifeSum(lineArray);//总数
        this->period=this->getPeriod();       //周期
        this->times=this->getTimes(lineArray);//一共输出的次数
        this->printMapLength=this->times+1;   //增加停止输出
        this->lastWarriorListLength=0;
    }
    unsigned int getInitLive()
    {
        return this->initLive;
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
            string warriorType=this->lastWarriorList[i]->type;
            string id=to_string(i+1);
            string temp="born with strength";
            string target=time+" "+commandAreaType+" "+warriorType+" "+id+" "+temp+" "+to_string(lastWarriorList[i]->life);
            //tail
            string tail=to_string(this->warriorInfoList[i]->count)+" "+warriorType+" in " +this->type+ " headquarter";
            printMap[i]=target+","+tail;
            line=i;
        }
        printMap[++line]=this->stopProduceWarrior(line);
    }
    unsigned int getTimesForNotEnough(unsigned int *lineArray)
    {
        this->lastWarriorListLength=0;
        unsigned int sum=this->initLive;
        int remain=0;
        warrior *temp;
        for(int i=0;i<WARRIOR_TYPE_NUM;i++)
        {
            remain=sum-this->warriorTypeList[i]->life;
            if(remain>0){
                temp=new warrior(this->warriorTypeList[i]->type,this->warriorTypeList[i]->life);
                this->lastWarriorList[i]=temp;
                this->warriorInfoList[i]->count++;
                this->lastWarriorListLength++;
                sum=remain;
            }else{
                for(int j=i+1;j<WARRIOR_TYPE_NUM;j++){
                    remain=sum-this->warriorTypeList[j]->life;
                    if(remain>0){
                      temp=new warrior(this->warriorTypeList[j]->type,this->warriorTypeList[j]->life);
                        this->lastWarriorList[this->lastWarriorListLength]=temp;
                        sum=remain;
                        this->warriorInfoList[j]->count++;
                        this->lastWarriorListLength++;
                    }
                    
                }
            }
            
        }
        return this->lastWarriorListLength;
    }
    //stop
    string stopProduceWarrior(int line)
    {
        string tail="headquarter stops making warriors";
        string str=to_string(line)+" "+this->type+" "+tail;
        return str;
    }
};
void dealWarrior(unsigned int m,unsigned int *a)
{
    unsigned int a1=m;
    unsigned int *b=a;
    commandArea red=commandArea("red",a1,b);
    commandArea blue=commandArea("blue",a1,b);
    red.produceWarrior();
    blue.produceWarrior();
    for(int i=0;i<blue.printMapLength;i++){
        if(red.printMap[i]!=""){
         cout<<red.printMap[i]<<endl;
        }
        if(blue.printMap[i]!=""){
        cout<<blue.printMap[i]<<endl;
        }
        
    }
    
    
    


    
    
}
int main() {
 
    int N;
    cin>>N;
    int i=1;
    while(N--){
        unsigned int  m;unsigned int a[WARRIOR_TYPE_NUM];
        cin>>m;
        for(int i=0;i<WARRIOR_TYPE_NUM;i++){
            cin>>a[i];
        }
        cout<<"Case:"<<i++<<endl;
        dealWarrior(m,a);
    }
    

    return 0;
}

