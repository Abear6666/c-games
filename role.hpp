#ifndef _role_hpp
#define _role_hpp

#include <iostream>
#include <vector>

using namespace std;

//引用C语言库头文件
extern "C"
{
#include <stdio.h>
}
extern vector<string>  role_disMenu;
extern int display_row;

class role
{
public:
    role(){}
    void show()
    {
        char buf[512] ={0};
        sprintf(buf,"海贼名称：%s 攻击力: %d 防御: %d \n血量: %d 装备：%s 悬赏金额:%d",this->name.c_str(),this->attk,this->defense,this->HP,this->get_equimnet().c_str(),this->get_reward());
        mvprintw(display_row, 0, buf);   
        refresh(); //刷新界面   
        role_disMenu.push_back(this->name.c_str());        
    }
    void potion_treatment(int h)//药水治疗
    {
        if (this->CUR_HP + h > this->HP)
        {
            this->recovery_CurHp();
            return;
        }
        this->CUR_HP += h;

    }
    
    void recovery_CurHp()//治疗恢复
    {
        this->CUR_HP = this->HP;
    }
    //输出人物信息
    void output_role_msg(WINDOW *local_win)
    {
        mvwprintw(local_win,3,0,"            "); //y=30 
        mvwprintw(local_win,3,50,"          "); //y=30 
        //输出各自信息：
        mvwprintw(local_win,1,0,"海贼名称:%s",this->get_name().c_str()); //y=30 
        mvwprintw(local_win,2,0,"等级:%d",this->get_grade()); //y=30 
        mvwprintw(local_win,3,0,"生命值:%d ",this->get_CUR_HP()); //y=30 
        mvwprintw(local_win,4,0,"攻击力:%d",this->get_attk()); //y=30 
        mvwprintw(local_win,5,0,"装备:%s",this->get_equimnet().c_str()); //y=30 
        mvwprintw(local_win,6,0,"经验值:%d/100",this->get_experience()); //y=30 
        mvwprintw(local_win,7,0,"悬赏金额:%d",this->get_reward()); //y=30 

        wrefresh(local_win);          
    }    

    void add_Exp(int Exp)//增加经验
    {
        this->experience += Exp;
        if (this->experience >= 100 && this->grade < 5)
        {
            //cout << "升级成功" << endl;升一级所有属性涨70% 
            this->HP *= 1.7;
            this->CUR_HP = this->HP;
            this->attk *= 1.7 ;
            this->defense *= 1.7;
            this->grade += 1;
            this->experience -= 100;
            this->reward *=3;
        }        
    } 

    void promote(int hp, int def,int attk,const char *_equipment)//穿戴装备提升能力
    {
        this->HP+=hp;
        this->CUR_HP+=hp;
        this->defense+=def;
        this->attk+=attk;
        this->equipment = _equipment;
    }
    void add_coin(int coin )//增加金币 
    {
        this->gold_coins += coin;
    } 
    bool reduce_coin(int sum)//减少金币 用于商店购买
    {
         this->gold_coins -= sum;
        if(this->gold_coins <0)
        {
            //购买失败
            this->gold_coins += sum;
            return false;
        }else{
            return true;
        }
    }


    int get_attk()
    {
        return this->attk;
    }
    string get_name()
    {
        return this->name;
    }
    int get_grade(){return this->grade;}
    int get_defense(){return this->defense;}
    int get_coins(){return this->gold_coins;}
    int get_CUR_HP(){return this->CUR_HP;} 
    int get_HP(){return this->HP;}     
    int get_reward(){return this->reward;}
    string get_equimnet(){return this->equipment;}
    int get_experience(){return this->experience;}

    void be_hurt(int hurt){this->CUR_HP -= hurt; }
    string get_skill(int i){return skill[i];}
    //读取文件设置人物属性
    void read_file_setmsg(const char *name,int grade,int Hp,
        int CUR_HP ,int attk,int defense,const char *equipment ,int experience , int reward ,int gold_coins )
    {
        this->name = string(name);
        this->grade = grade;
        this->HP = Hp;
        this->CUR_HP =CUR_HP;
        this->attk = attk;
        this->defense = defense;
        this->equipment = string(equipment);
        this->experience = experience;
        this->reward = reward;
        this->gold_coins = gold_coins;

    }
    //每个人物都有三个技能 设置纯虚函数 预留接口 实现传入不同的对象就会使用不同的对应的技能 多态
    virtual int skill1(role &r) = 0;
    virtual int skill2(role &r) = 0;
    virtual int skill3(role &r) = 0;

protected:
    string name;//名字
    int HP;//血量
    int CUR_HP;//当前血量
    int attk;//攻击
    int defense;//防御
    string equipment;//装备
    int grade;//等级
    int experience;//经验
    int reward;//悬赏金额
    int gold_coins;//金币
    vector <string> skill;//技能


};

//路飞
class lufei:public role
{
public:
    lufei()
    {
        this->name = "蒙奇*D路飞";
        this->grade= 1;
        this->HP = 100;
        this->CUR_HP = 100;        
        this->attk= 10;
        this->defense=3;
        this->equipment = "无";
        this->experience = 0;
        this->reward = 1000;
        this->gold_coins = 100;
        skill.push_back("普通攻击");
        skill.push_back("霸王枪");
        skill.push_back("橡胶火箭炮");
    }

    int skill1(role &r)
    {
        return this->attk * this->attk / (this->attk + r.get_defense());
    }
    int skill2(role &r)
    {
       // cout<<"路飞发动了橡胶火箭炮"<<endl;
        return this->attk*2 * this->attk / (this->attk + r.get_defense()) ;
    }
    int skill3(role &r)
    {
       // cout<<"路飞发动了霸王枪"<<endl;
        return this->attk*10 * this->attk / (this->attk + r.get_defense()) ;
    } 
     
private:

};

//艾斯 
class aisi:public role
{
public:
    aisi()
    {
        this->name = "哥尔*D艾斯";
        this->grade= 1;
        this->HP = 300;
        this->CUR_HP = 300;        
        this->attk= 50;
        this->defense=30;
        this->equipment = "烧烧果实";
        this->experience = 0;
        this->reward = 1000;
        this->gold_coins = 100;
        skill.push_back("普通攻击");
        skill.push_back("火拳");
        skill.push_back("焰火");
    }

    int skill1(role &r)
    {
        return this->attk * this->attk / (this->attk + r.get_defense());
    }
    int skill2(role &r)
    {
        return this->attk*5 * this->attk / (this->attk + r.get_defense()) ;
    }
    int skill3(role &r)
    {
        return this->attk*20 * this->attk / (this->attk + r.get_defense()) ;
    }   
private:
};

//娜美
class namei:public role
{
public:
    namei()
    {
        this->name = "娜美";
        this->grade= 1;
        this->HP = 100;
        this->CUR_HP = 100;        
        this->attk= 5;
        this->defense=3;
        this->equipment = "天候棒";
        this->experience = 0;
        this->reward = 3000;
        this->gold_coins = 100;
        skill.push_back("普通攻击");
        skill.push_back("雷雷枪");
        skill.push_back("雷电闪击");
    }
    int skill1(role &r)
    {
        return this->attk * this->attk / (this->attk + r.get_defense());
    }
    int skill2(role &r)
    {

        return this->attk*2 * this->attk / (this->attk + r.get_defense()) ;
    }
    int skill3(role &r)
    {
        return this->attk*10 * this->attk / (this->attk + r.get_defense()) ;
    } 
private:
};
//乔巴
class qiaoba:public role
{
public:
    qiaoba()
    {
        this->name = "乔巴";
        this->grade= 1;
        this->HP = 150;
        this->CUR_HP = 150;        
        this->attk= 15;
        this->defense=10;
        this->equipment = "人人果实";
        this->experience = 0;
        this->reward = 100;
        this->gold_coins = 100;
        skill.push_back("腕力强化");
        skill.push_back("刻蹄樱吹雪");
        skill.push_back("重量强化·摔击");
    }
    int skill1(role &r)
    {
        return this->attk * this->attk / (this->attk + r.get_defense());
    }
    int skill2(role &r)
    {

        return this->attk*2 * this->attk / (this->attk + r.get_defense()) ;
    }
    int skill3(role &r)
    {
        return this->attk*9 * this->attk / (this->attk + r.get_defense()) ;
    } 
private:
};

//索隆
class suolong:public role
{
public:
    suolong()
    {
        this->name = "索隆";
        this->grade= 1;
        this->HP = 500;
        this->CUR_HP = 500;        
        this->attk= 200;
        this->defense=10;
        this->equipment = "秋水-三代鬼彻";
        this->experience = 0;
        this->reward = 5000;
        this->gold_coins = 100;
        skill.push_back("无刀流-龙卷风");
        skill.push_back("一刀流居合-狮子歌歌");
        skill.push_back("三刀流奥义-三千世界");
    }
    int skill1(role &r)
    {
        return this->attk * this->attk / (this->attk + r.get_defense());
    }
    int skill2(role &r)
    {

        return this->attk*3 * this->attk / (this->attk + r.get_defense()) ;
    }
    int skill3(role &r)
    {
        return this->attk*12 * this->attk / (this->attk + r.get_defense()) ;
    } 
private:
};
//****************怪物*****************
//小丑·巴基
class baji:public role
{
public:
    baji()
    {
        this->name = "小丑·巴基";
        this->grade= 1;
        this->HP = 50;
        this->CUR_HP = 50;
        this->attk= 5;
        this->defense=3;
        this->equipment = "无";
        this->experience = 0;
        this->reward = 900 ;
        skill.push_back("普通攻击");
        skill.push_back("巴巴冲刺");
        skill.push_back("巴拉巴拉");
    }

    int skill1(role &r)
    {
       // cout<<"巴基发动了普通攻击"<<endl;
        return this->attk * this->attk / (this->attk + r.get_defense());
    }
    int skill2(role &r)
    {
       // cout<<"巴基发动了巴巴冲刺"<<endl;
        return this->attk*2 * this->attk / (this->attk + r.get_defense()) ;
    }
    int skill3(role &r)
    {
       // cout<<"巴基发动了巴拉巴拉"<<endl;
        return this->attk*2 * this->attk / (this->attk + r.get_defense()) ;
    }    
private:
};

//神—艾尼路
class ainilu:public role
{
public:
    ainilu()
    {
        this->name = "神—艾尼路";
        this->grade= 3;
        this->HP = 200;
        this->CUR_HP = 200;
        this->attk= 50;
        this->defense= 30;
        this->equipment = "响雷果实";
        this->experience = 0;
        this->reward = 5000  ;
        skill.push_back("雷指-雷闪");
        skill.push_back("雷鸟-神之制裁");
        skill.push_back("小奥义-万雷");
    }

    int skill1(role &r)
    {
        return this->attk * this->attk / (this->attk + r.get_defense());
    }
    int skill2(role &r)
    {
        return this->attk*2 * this->attk / (this->attk + r.get_defense()) ;
    }
    int skill3(role &r)
    {
        return this->attk*5 * this->attk / (this->attk + r.get_defense()) ;
    }    
private:
};

//萨卡斯基-赤犬
class chiquan:public role
{
public:
    chiquan()
    {
        this->name = "萨卡斯基-赤犬";
        this->grade= 5;
        this->HP = 1000;
        this->CUR_HP = 1000;
        this->attk= 200;
        this->defense= 99;
        this->equipment = "岩浆果实";
        this->experience = 0;
        this->reward = 20000  ;
        skill.push_back("大喷火");
        skill.push_back("火山喷发");
        skill.push_back("犬啮红莲");
    }

    int skill1(role &r)
    {
        return this->attk * this->attk / (this->attk + r.get_defense());
    }
    int skill2(role &r)
    {
        return this->attk*2 * this->attk / (this->attk + r.get_defense()) ;
    }
    int skill3(role &r)
    {
        return this->attk*10 * this->attk / (this->attk + r.get_defense()) ;
    }    
private:
};
#endif
