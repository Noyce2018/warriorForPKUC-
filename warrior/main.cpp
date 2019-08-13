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
//warrior
class warrior
{
    unsigned int warriorId;
    unsigned int attack;
    unsigned int life;
    string type;
public:
    friend class warriorInfo;
    friend class commandArea;
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
    
    unsigned int remainder;//余数
    unsigned int initLive;
    unsigned int remainLive;
    unsigned int warriorLifeSum;//五个武士生命值之和
    unsigned int liveArray[WARRIOR_TYPE_NUM];//输入的数组
public:
    //end
    warrior *lastWarriorList[WARRIOR_TYPE_NUM-1];  //最后一组
    warrior *warriorTypeList[WARRIOR_TYPE_NUM];    //武士列表
    warriorInfo *warriorInfoList[WARRIOR_TYPE_NUM];//武士信息表，多了一个计数
    string printMap[MAX_MAP_LENGTH];               //行为日志表
    string type; //red or blue
    unsigned int times;
    unsigned int printMapLength;                   //日志条数
    unsigned int lastWarriorListLength;
    //dragon 、ninja、iceman、lion、wolf
    commandArea(string type,unsigned int initLive,unsigned int *lineArray)
    {
        this->type=type;
        this->initLive=initLive;
        this->remainLive=initLive;
        for(int i=0;i<WARRIOR_TYPE_NUM;i++){
            liveArray[i]=lineArray[i];
        }
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
        
        this->warriorLifeSum=this->getwarriorLifeSum(lineArray);//获取五个武士生命值之和
        this->remainder=this->getremainder();       //余数
        this->lastWarriorListLength=0;              //日志条数，初始化为0
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
    unsigned int getremainder()
    {
        return (this->initLive)%(this->warriorLifeSum);
        
    }
    unsigned int getTimes(unsigned int *lineArray)
    {
        //not enough
        if(this->remainder==this->initLive){
            return getTimesForNotEnough(lineArray);
            
        }
        //can get int remainder
        if(this->remainder==0){
            int target=(this->initLive)/(this->warriorLifeSum)*5;
            this->dealCanDevideInt(target);
            return target;
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
        /*
        三种情况
        1.不够
        2.正好整除
        3.整除一段+余数一段
        */
    
        //不够：初始化生命值小于五个武士生命之和
        if(this->initLive<this->warriorLifeSum)
        {
            this->produceWarriorForNotEnoughLife();
            return;
        }
        //正好整除
        if(this->initLive>=this->warriorLifeSum&&this->remainder==0){
            this->produceInfoEnoughDevide();
            return;
        }
        //整除一部分但是剩余一部分
        if(this->initLive>this->warriorLifeSum&&this->remainder!=0){
            //处理整除部分
            this->produceInfoEnoughDevide();
            //处理剩余部分
            this->dealRemain(this->remainder,this->printMapLength);
            return;
        }
        
    }
    //处理剩余部分
    void dealRemain(unsigned int reminder,unsigned int length)
    {
        unsigned int sum=reminder;
        int remain=0;
        warrior *temp;
        for(int i=0;i<WARRIOR_TYPE_NUM-1;i++){
            remain=sum-this->warriorTypeList[i]->life;
            if(remain>=0){
                temp=new warrior(this->warriorTypeList[i]->type,this->warriorTypeList[i]->life);
                this->lastWarriorList[i]=temp;
                this->warriorInfoList[i]->count++;
                this->lastWarriorListLength++;
                //记日志
                writeProduceInfo(i+length,warriorInfoList[i]);
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
                        //记日志
                        writeProduceInfo(j+length,warriorInfoList[j]);
                    }
                    
                }
            }
        }
        this->stopProduceWarrior(++this->lastWarriorListLength);
    }
    //不够情况下的生产武士(生产的同时记日志)
    void produceWarriorForNotEnoughLife()
    {
        unsigned int sum=this->initLive;
        int remain=0;
        warrior *temp;
        for(int i=0;i<WARRIOR_TYPE_NUM-1;i++)
        {
            remain=sum-this->warriorTypeList[i]->life;
            if(remain>=0){
                temp=new warrior(this->warriorTypeList[i]->type,this->warriorTypeList[i]->life);
                this->lastWarriorList[i]=temp;
                this->warriorInfoList[i]->count++;
                this->lastWarriorListLength++;
                //记日志
                writeProduceInfo(i,warriorInfoList[i]);
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
                        //记日志
                        writeProduceInfo(j,warriorInfoList[j]);
                    }
                    
                }
            }
            
        }
        this->stopProduceWarrior(this->lastWarriorListLength);
        
    }
    //
    void produceInfoEnoughDevide()
    {
        int period=this->initLive/this->warriorLifeSum;//计算周期
        //每生产五个武士是一个完整的周期
        for(int i=0;i<period;i++){
            produceOnePeriodWarrior(i);
        }
        this->stopProduceWarrior(period*WARRIOR_TYPE_NUM);
    }
    //生产一个周期的武士
    void produceOnePeriodWarrior(int m)
    {
        warrior *temp;
        for(int i=0;i<WARRIOR_TYPE_NUM;i++){
            temp=new warrior(this->warriorTypeList[i]->type,this->warriorTypeList[i]->life);
            this->lastWarriorList[i]=temp;
            this->warriorInfoList[i]->count++;
            this->lastWarriorListLength++;
            //记日志
            writeProduceInfo(i+WARRIOR_TYPE_NUM*m,warriorInfoList[i]);
        }
    }
    //记日志
    void writeProduceInfo(int id,warriorInfo *warriorIn)
    {
        string time=to_string(id);
        string commandAreaType=this->type;//红蓝司令部
        string warriorType=warriorIn->name;
        string birthId=to_string(id+1);
        string temp="born with strength";
        //head
        string target=time+" "+commandAreaType+" "+warriorType+" "+birthId+" "+temp+" "+to_string(warriorIn->w->getLife());
        //tail
        //string one="1";
        string tail=to_string(warriorIn->count)+" "+warriorType+" in " +this->type+ " headquarter";
        printMap[id]=target+","+tail;
        
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
        //printMap[++line]=this->stopProduceWarrior(line);
    }
    void storeProduceInfoEnoughDevide()
    {
        int line;
        for(int i=0;i<this->times;i++){
            //head
            string time=to_string(i);  //id
            string commandAreaType=this->type;
            string warriorType=this->lastWarriorList[i%WARRIOR_TYPE_NUM]->type;
            string id=to_string(i+1);
            string temp="born with strength";
            string target=time+" "+commandAreaType+" "+warriorType+" "+id+" "+temp+" "+to_string(lastWarriorList[i%WARRIOR_TYPE_NUM]->life);
            //tail
            string tail=to_string(this->warriorInfoList[i%WARRIOR_TYPE_NUM]->count)+" "+warriorType+" in " +this->type+ " headquarter";
            printMap[i]=target+","+tail;
            line=i;
        }
        //printMap[++line]=this->stopProduceWarrior(line);
    }
    //实际生产的过程
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
    //deal int devide
    //实际生产的过程
    void dealCanDevideInt(int times)
    {
        int line=0;
        for(int i=0;i<times;i++){
            warrior *temp;
            temp=new warrior(this->warriorTypeList[i%WARRIOR_TYPE_NUM]->type,this->warriorTypeList[i%WARRIOR_TYPE_NUM]->life);
            this->lastWarriorList[i%WARRIOR_TYPE_NUM]=temp;
            this->warriorInfoList[i%WARRIOR_TYPE_NUM]->count++;
            this->lastWarriorListLength++;
            string time=to_string(i);  //id
            string commandAreaType=this->type;
            string warriorType=this->lastWarriorList[i%WARRIOR_TYPE_NUM]->type;
            string id=to_string(i+1);
            string temp0="born with strength";
            string target=time+" "+commandAreaType+" "+warriorType+" "+id+" "+temp0+" "+to_string(lastWarriorList[i%WARRIOR_TYPE_NUM]->life);
            //tail
            string tail=to_string(this->warriorInfoList[i%WARRIOR_TYPE_NUM]->count)+" "+warriorType+" in " +this->type+ " headquarter";
            printMap[i]=target+","+tail;
            line=i;
        }
        //printMap[++line]=this->stopProduceWarrior(line);
    }
    //stop
    void stopProduceWarrior(int line)
    {
        string tail="headquarter stops making warriors";
        string str=to_string(line)+" "+this->type+" "+tail;
        //return str;
        printMap[line]=str;
        this->printMapLength=++line;
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
    for(int i=0;i<MAX_MAP_LENGTH;i++){
        if(red.printMap[i]!=""){
         cout<<red.printMap[i]<<endl;
        }
        if(blue.printMap[i]!=""){
        cout<<blue.printMap[i]<<endl;
        }
        
    }
    
    
    


    
    
}
int main() {
 
    int N=1;
    //cin>>N;
    int i=1;
    while(N--){
        unsigned int  m;unsigned int a[WARRIOR_TYPE_NUM]={4,4,4,4,4};;
//        cin>>m;
//        for(int i=0;i<WARRIOR_TYPE_NUM;i++){
//            cin>>a[i];
//        }

        cout<<"Case:"<<i++<<endl;
        dealWarrior(24,a);
    }
    

    return 0;
}

