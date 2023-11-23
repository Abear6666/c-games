#ifndef _save_hpp
#define _save_hpp
#include <iostream>
#include "role.hpp"

using namespace std;

//引用C语言库头文件
extern "C"
{
#include <stdio.h>
#include <string.h>

}

class save
{
public:
    //存武器
    bool save_equipment(bag &bag)
    {
        fp = fopen("./equipment.txt","w+");
 
        refresh(); //刷新界面   
        for(int i=0; i<bag.return_equipment_size();i++)
        {
            equipment * r = bag.return_equipment_in(i);
            char buf[1024];

            sprintf(buf,"%s %d ",r->get_name().c_str(),r->get_sum());//
            fwrite(buf, strlen(buf), 1, fp);

        }
        fclose(fp);
    }
    //存药水
    bool save_potion(bag &bag)
    {
        fp = fopen("./potion.txt","w+");
 
        refresh(); //刷新界面   
        for(int i=0; i<bag.return_potion_size();i++)
        {
            potion * r = bag.return_potion_in(i);
            char buf[1024];

            sprintf(buf,"%s %d ",r->get_name().c_str(),r->get_sum());//
            fwrite(buf, strlen(buf), 1, fp);

        }
        fclose(fp);
    }
    //存所有角色
    bool save_all_role(bag &bag)
    {
        fp = fopen("./role.txt","w+");
 
        refresh(); //刷新界面   
        for(int i=0; i<bag.return_role_size();i++)
        {
            role * r = bag.return_role_in(i);


           this->save_role(r);

        }
        fclose(fp);
    }
   //存一个角色
    bool save_role(role *r)
    {

        if(fp == NULL)
        {
            perror("game_archive.txt open faile");
            return false;    
        }
        char buf[1024];

        sprintf(buf,"%s %d %d %d %d %d %s %d %d %d ",r->get_name().c_str(),r->get_grade(),r->get_HP(),r->get_CUR_HP(),r->get_attk(),r->get_defense(),r->get_equimnet().c_str(),r->get_experience(),r->get_reward(),r->get_coins());//
        fwrite(buf, strlen(buf), 1, fp);
        //fclose(fp);
        return true;        
    }



    //读所有角色
    bool read_all_role(bag &bag)
    {
        FILE *fp = fopen("./role.txt","r");
        if (fp == NULL)
        {
            perror("game_archive.txt open faile");
            return NULL;
        }        
        //读取存档角色信息
        char name[64] = {0};
        int grade ;
        int Hp ;
        int CUR_HP ;        
        int attk;
        int defense;
        char equipment[64]  = {0};
        int experience ;
        int reward ;
        int gold_coins ; 

        int flag = 0;
        while (-1 != fscanf(fp, "%s %d %d %d %d %d %s %d %d %d ", name, &grade, &Hp, &CUR_HP, &attk,
                            &defense, equipment, &experience, &reward, &gold_coins))
        {
            flag = 1;
            role *p = NULL;
            if (string(name) == string("蒙奇*D路飞"))
            {

                p = new lufei;

            }
            else if (string(name) == string("哥尔*D艾斯"))
            {

                p = new aisi;

            }
            else if (string(name) == string("娜美"))
            {

                p = new namei;

            }
            else if (string(name) == string("索隆"))
            {

                p = new suolong;
            }else if (string(name) == string("乔巴"))
            {

                p = new qiaoba;
            } 


           
           p->read_file_setmsg(name,grade,Hp,CUR_HP,attk,defense,equipment,experience,reward,gold_coins);


            bag.add_role(p);
           // cout << "读取的宠物已经放入背包" << endl;
            bzero(name, sizeof(name));
            bzero(equipment, sizeof(equipment));
        }
        fclose(fp);
    } 


    //读药水
    bool read_potion(bag &bag)
    {
        FILE *fp = fopen("./potion.txt","r");
        if (fp == NULL)
        {
            perror("game_archive.txt open faile");
            return NULL;
        }        
        //读取存档角色信息
        char name[64] = {0};
        int sum ;

            while (-1 != fscanf(fp, "%s %d ",name,&sum))
            {
                if(strcmp(name,"小型药水")==0)
                {
                    bag.add_potion(new small_potion(),sum);

                }else if(strcmp(name,"中型药水")==0)
                {
                    bag.add_potion(new mid_potion(),sum);

                }else if(strcmp(name,"大型药水")==0)
                {
                    bag.add_potion(new large_potion(),sum);

                }
            }

        bzero(name, sizeof(name));       
        fclose(fp);
    }     
  //读装备
    bool read_equipment(bag &bag)
    {
        FILE *fp = fopen("./equipment.txt","r");
        if (fp == NULL)
        {
            perror("game_archive.txt open faile");
            return NULL;
        }        
        //读取存档角色信息
        char name[64] = {0};
        int sum ;

            while (-1 != fscanf(fp, "%s %d ",name,&sum))
            {
                if(strcmp(name,"大宝剑")==0)
                {
                    bag.add_equipment(new dbj(),sum);
 
                }else if(strcmp(name,"天候棒")==0)
                {
                    bag.add_equipment(new thb(),sum);
 
                }else if(strcmp(name,"黑夜刀")==0)
                {
                    bag.add_equipment(new hyd(),sum);

                }
            }

        bzero(name, sizeof(name));       
        fclose(fp);
    } 
private:
FILE *fp;

};



#endif
