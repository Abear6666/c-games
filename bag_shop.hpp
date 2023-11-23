#ifndef _bag_shop_hpp
#define _bag_shop_hpp

#include <iostream>
#include <curses.h>
#include <vector>
#include "role.hpp"
#include "userwin.hpp"
#include  <list>
using namespace std;

int display_row = 10;
extern int win_x;
extern int win_y;

//引用C语言库头文件
extern "C"
{
#include <stdio.h>
#include <unistd.h>
}

extern vector<string>  bagMenu;
vector<string>  equipmentMenu;//武器背包菜单
vector<string>  potionMenu;//药水背包菜单
vector<string>  role_disMenu;//人物菜单

//药水类
class potion
{
public: 
virtual void show()=0;
//返回药水名字
string get_name()
{
    return this->name;
}
int get_HP()
{
    return this->HP;
}

void add_sum()
{
    this->sum++;
}

void rm_sum()
{
    this->sum--;
}
int get_sum()
{
    return this->sum;
}

void add_sum(int sum)
{
    this->sum+=sum;
}


protected:
string name;//
int HP;
int sum;

};
//小型药水
class small_potion:public potion
{
public:
    small_potion(int sum =0)
    {
        this->name = "小型药水";
        this->HP = 10;
        this->sum = sum;
        
    }
void show()
{
   char buf[512] ={0};
   sprintf(buf,"%s  补充血量：%d 数量：%d",this->name.c_str(),this->HP,this->sum);  

    potionMenu.push_back(buf);
     
}
private:

};
//中型药水
class mid_potion:public potion
{
public:
    mid_potion(int sum =0)
    {
        this->name = "中型药水";
        this->HP = 30;
        this->sum = sum;
    }
void show()
{
   char buf[512] ={0};
   sprintf(buf,"%s  补充血量：%d 数量：%d",this->name.c_str(),this->HP,this->sum);  
    potionMenu.push_back(buf);
     
}
private:

};

//大型药水
class large_potion:public potion
{
public:
    large_potion(int sum =0)
    {
        this->name = "大型药水";
        this->HP = 60;
        this->sum = sum;
    }

void show()
{
   char buf[512] ={0};
   sprintf(buf,"%s  补充血量：%d 数量：%d",this->name.c_str(),this->HP,this->sum);  
    potionMenu.push_back(buf);
     
}

private:

};

//装备类
class equipment
{
public: 
//显示装备信息
virtual void show()=0;

string get_name()
{
    return this->name;
}
void add_sum()
{
    this->sum++;
}
void add_sum(int sum)
{
    this->sum+=sum;
}

void rm_sum()
{
    this->sum--;
}
int get_sum()
{
    return this->sum;
}

protected: 
string name; //名称
int attk;  //力量
int defense; //防御 
int HP; //血量 
int sum;//数量

};

//大宝剑
class  dbj:public equipment
{
public: 
dbj(int sum = 0)
{
    this->name = "大宝剑"; 
    this->attk = 10;
    this->defense = 5;
    this->HP = 15;
    this->sum = sum;
}
//显示装备 
void show()
{
   char buf[512] ={0};
   sprintf(buf,"%s 攻击力: %d 防御: %d 血量: %d  数量：%d",this->name.c_str(),this->attk,this->defense,this->HP,this->sum);
   // mvprintw(display_row, 0, buf);   
    refresh(); //刷新界面  

    equipmentMenu.push_back(buf);
     

}
};

//天候棒 
class  thb:public equipment
{
public:
thb(int sum = 0)
{
    this->name = "天候棒"; 
    this->attk = 20;
    this->defense = 10;
    this->HP = 30;
    this->sum = sum;
}
//显示装备 
void show()
{
   char buf[512] ={0};
   sprintf(buf,"%s 攻击力: %d 防御: %d 血量: %d  数量：%d",this->name.c_str(),this->attk,this->defense,this->HP,this->sum);
   // mvprintw(display_row, 0, buf);   
    refresh(); //刷新界面 
    equipmentMenu.push_back(buf);  

}
};

//黑夜刀
class  hyd:public equipment
{
public:
hyd(int sum = 0)
{
    this->name = "黑夜刀"; 
    this->attk = 500;
    this->defense = 200;
    this->HP = 450;
    this->sum = sum;
}
//显示装备 
void show()
{
   char buf[512] ={0};
   sprintf(buf,"%s 攻击力: %d 防御: %d 血量: %d  数量：%d",this->name.c_str(),this->attk,this->defense,this->HP,this->sum);
    //mvprintw(display_row, 0, buf);   
    refresh(); //刷新界面   
    equipmentMenu.push_back(buf);

}
};

//**************背包类 管理装备 药水
class bag
{
public: 
    bag()
    {
        equip.push_back(new dbj());
        equip.push_back(new thb());
        equip.push_back(new hyd());
        poti.push_back(new small_potion());
        poti.push_back(new mid_potion());
        poti.push_back(new large_potion());

    }


    //背包管理界面
    void bag_main(role &r)
    {

        while (1)
        {
            //创建一个菜单 显示商品的名字 
            menu  *cw = new menu(win_x/2-10,win_y/2-5,30,20,bagMenu); 
            //开始选择 
            
            int  ctrl =  cw->get_ctrl(); 
             delete cw;
            if(ctrl == 0)
            {
                //武器 遍历武器的容器输出            
                equipmentMenu.clear();
                this->show_equipment();
                equipmentMenu.push_back("返回");    
               menu* cw1 = new menu(win_x/2-10,win_y/2-5,50,30,equipmentMenu); 

                    ctrl =  cw1->get_ctrl(); 
                           
                    if(ctrl == 0)
                    {

                         this->admin_menu(r,10,5,15,"大宝剑",0);//道具管理界面                          
                    
                    }
                    else if(ctrl == 1)//第二把武器
                    {
                         this->admin_menu(r,50,30,25,"天候棒",0);//道具管理界面  
                                                 
                    }
                    else if(ctrl == 2)//第三把武器
                    {//500,200,450 
                         this->admin_menu(r,500,200,450,"黑夜刀",0);//道具管理界面
                          
                    }else if(ctrl == 3)//退出武器界面
                    {
                        delete cw;
                        continue;
                    }  
             
               
            }else if(ctrl == 1)//药水界面
            {
                
                potionMenu.clear();
                this->show_potion();
                potionMenu.push_back("返回");    
                menu* cw1 = new menu(win_x/2-10,win_y/2-5,50,30,potionMenu); 

                    ctrl =  cw1->get_ctrl(); 
                           
                    if(ctrl == 0)//小药水
                    {
                        //开启菜单  
                        this->admin_menu(r,10,1,1,"小型药水",1);//道具管理界面
                    
                    }
                    else if(ctrl == 1)//中药水
                    {
                        this->admin_menu(r,30,1,1,"中型药水",1);//道具管理界面
                    }
                    else if(ctrl == 2)//大药水
                    {
                        this->admin_menu(r,60,1,1,"大型药水",1);//道具管理界面
                    }else if(ctrl == 3)
                    {
                        delete cw1;

                        continue;
                    }                  

            }else if(ctrl == 2)//人物界面
            {
                clear();
                display_row=10;
               this->show_role(); 
               continue;
            }else if(ctrl == 3)
            {

               break; 
            }
            
            
        }
        
         
    }
    //物品管理菜单 ==》丢弃/使用/返回
    void admin_menu(role &r,int hp, int def, int attk, const char *_equipment,int flag)//flag 为0 装备  为1 药水
    {
         vector<string>  adminMenu;
        adminMenu.push_back("使用");
        adminMenu.push_back("丢弃");
        adminMenu.push_back("返回");
            //开启菜单  
        menu*cw = new menu(win_x-20,win_y-11,20,10,adminMenu); 

            //开始选择 
           int ctrl =  cw->get_ctrl(); 
           int judg_sum = 0;


            if(flag == 0)// 装备
            {
                judg_sum = this->return_equitsum(_equipment);
            }else{//药水
                judg_sum = this->return_potisum(_equipment);
            }
 
            if(judg_sum == 0)//数量为0
            {

                    clear();
                    mvprintw(9, 0, "当前物品数量为0！请去商店购买！");     
            }else{                            
            if(ctrl==0)
            {
                    mvprintw(9, 0, "66  ");  
                      mvprintw(9, 0, "77  ctrl:%d  %d",ctrl,judg_sum);  
                    refresh(); //刷新界面 
                //以装备 提升自己的力量 
                if(flag == 0)
                {
                    this->Discard_equipment(_equipment);//减少数量
                    //提升
                    r.promote(hp,def,attk,_equipment);
                    clear();
                    mvprintw(9, 0, "穿戴装备成功！");   
                    refresh(); //刷新界面  
                    r.show();
                }else{
                    this->Discard_potion(_equipment);//减少数量
                    //提升
                    r.potion_treatment(hp);
                    clear();
                    mvprintw(9, 0, "使用药水成功！增加：%d点生命值",hp);   
                    refresh(); //刷新界面  
                }

                sleep(1);                     

            }else if(ctrl==1)
            {
                    if(flag == 0)
                    {
                        clear();
                        mvprintw(9, 0, "装备丢弃成功！");   
                        refresh(); //刷新界面  
                        this->Discard_equipment(_equipment);//数量减少
                    }else{
                         clear();
                        mvprintw(9, 0, "药品丢弃成功！");   
                        refresh(); //刷新界面  
                        this->Discard_potion(_equipment);//数量减少                       
                    }
           

            }else{
  
                delete cw;                                
            } 
            }
                        
    }
        
    
//显示装备
void show_equipment()
{
    display_row = 10;
    list<equipment *>::iterator  it = equip.begin(); 
    for(it;it!=equip.end();it++)
    {       
          (*it)->show(); 

    }
}

//显示药水
void show_potion()
{
    list<potion *>::iterator  it = poti.begin(); 
    for(it;it!=poti.end();it++)
    {
      
          (*it)->show(); 
           // display_row++;  
    }
}
//显示角色
void show_role()
{
    list<role *>::iterator  it = rol.begin(); 
    for(it;it!=rol.end();it++)
    {
        
          (*it)->show(); 
            display_row+=2;
    }

}
//显示单个角色
void show_onerole(string wp,WINDOW *local_win)
{
    list<role *>::iterator  it = rol.begin(); 
    for(it;it!=rol.end();it++)
    {
        if((*it)->get_name() == wp)
        {
           (*it)->output_role_msg(local_win);
        }
    }
}

//添加装备 
void add_equipment(equipment *p)
{
   
    for (list<equipment *>::iterator it = equip.begin(); it != equip.end(); it++)
    {
        if ((*it)->get_name() == p->get_name())
        {
            (*it)->add_sum();
        }
    }

}

//添加指定数量装备 
void add_equipment(equipment *p,int sum)
{
   
    for (list<equipment *>::iterator it = equip.begin(); it != equip.end(); it++)
    {
        if ((*it)->get_name() == p->get_name())
        {
            (*it)->add_sum(sum);
        }
    }

}

//添加药水
void add_potion(potion *p)
{
    
    //this->poti.push_back(p); 

    for (list<potion *>::iterator it = poti.begin(); it != poti.end(); it++)
    {
        if ((*it)->get_name() == p->get_name())
        {
            (*it)->add_sum();
        }
    }
    

}
//添加指定数量药水
void add_potion(potion *p,int sum)
{
    
    //this->poti.push_back(p); 

    for (list<potion *>::iterator it = poti.begin(); it != poti.end(); it++)
    {
        if ((*it)->get_name() == p->get_name())
        {
            (*it)->add_sum(sum);
        }
    }
    

}
//添加角色
void add_role(role *p)
{
    rol.push_back(p);
    role_disMenu.push_back(p->get_name());
    
}
//丢弃装备物品
void Discard_equipment(string wp)
{
    list<equipment *>::iterator  it = equip.begin(); 
    for(it;it!=equip.end();it++)
    {
        if((*it)->get_name() == wp)
        {
           (*it)->rm_sum();
        }
    }
}

//丢弃药水
void Discard_potion(string wp)
{
    list<potion *>::iterator  it = poti.begin(); 
    for(it;it!=poti.end();it++)
    {
        if((*it)->get_name() == wp)
        {
           (*it)->rm_sum();
        }
    }
}

//返回对应装备名字的数量
int return_equitsum(string wp)
{
    list<equipment *>::iterator  it = equip.begin(); 
    for(it;it!=equip.end();it++)
    {
        if((*it)->get_name() == wp)
        {

           return (*it)->get_sum();
        }
    }    
}
//返回对应药水名字的数量
int return_potisum(string wp)
{
    list<potion *>::iterator  it = poti.begin(); 
    for(it;it!=poti.end();it++)
    {
        if((*it)->get_name() == wp)
        {

           return (*it)->get_sum();
        }
    }    
}

//返回对应人物链表size大小
int return_role_size()
{
   
    return rol.size();
}

//返回对应index的药水
role* return_role_in(int index)
{
    if (index > rol.size())
    {
        return *(rol.end());
    }
    list<role *>::iterator it = rol.begin();
    for (int i = 0; i < index; i++)
    {
        it++;
    }
    return *it;
}


//返回对应药水链表size大小
int return_potion_size()
{
   
    return poti.size();
}

//返回对应index的装备
equipment* return_equipment_in(int index)
{
    if (index > equip.size())
    {
        return *(equip.end());
    }
    list<equipment *>::iterator it = equip.begin();
    for (int i = 0; i < index; i++)
    {
        it++;
    }
    return *it;
}


//返回对应装备链表size大小
int return_equipment_size()
{
   
    return equip.size();
}

//返回对应index的人物
potion* return_potion_in(int index)
{
    if (index > poti.size())
    {
        return *(poti.end());
    }
    list<potion *>::iterator it = poti.begin();
    for (int i = 0; i < index; i++)
    {
        it++;
    }
    return *it;
}
//全英雄回血
void recovery_allCurHp()
{
    list<role *>::iterator  it = rol.begin(); 
    for(it;it!=rol.end();it++)
    {       
          (*it)->recovery_CurHp();

    } 
}

private:
list<equipment *>  equip;//装备
list<potion *>  poti;//药水
list<role *>  rol;//角色

};


//**************商店类 提供装备 药水的购买
class shop
{
public:
    //商店主界面
    shop()
    {
        choices.push_back("1.小型药水.........10RMB");
        choices.push_back("2.中型药水.........30RMB");
        choices.push_back("3.大型药水.........60RMB");
        choices.push_back("4.大宝剑.........20RMB");
        choices.push_back("5.天候棒.........200RMB");
        choices.push_back("6.黑刀夜.........1000RMB");
        choices.push_back("返回");
        //获取选项大小
        this->n_choices =  choices.size(); 

        //新建一个窗体     
        local_win = newwin(30,30,6,50); //h w y x 

       //获取当前菜单的宽度和高度 
        x = getmaxx(local_win);
        y = getmaxy(local_win);

        highlight = 0;

        mvprintw(0,0,"商店 x=%d ,y=%d",x,y);
        print_menu(local_win,highlight);
        move(5,0);
        for(int i=0;i<COLS;i++)
            addstr("_");
        wrefresh(local_win); //刷新窗体
        refresh();//刷新主窗体 

    }
    //选择  
    int get_ctrl()
    {
         print_menu(local_win,highlight);
        int c;
         while(1)
	    {	
            //获取窗体的输入值
            c = wgetch(local_win);
            switch(c)
            {	case 'A':
                    if(highlight == -1)
                        highlight = n_choices;
                    else
                        --highlight;
                    break;
                case 'B':
                    if(highlight == n_choices+1)
                        highlight = 0;
                    else 
                        ++highlight;
                    break;
                default:
                    mvprintw(2, 0, "printed as %c",c); //输出到主窗体 
                    refresh();
            }

            //输出菜单 
            print_menu(local_win, highlight);
            if(c == 10)	/* User did a choice come out of the infinite loop */
            { 
                if(choices.size()!=0)
                {
                    mvprintw(0, 0, "printed as %s",this->choices.at(highlight).c_str());
    
                    refresh(); //刷新界面
                }


                return highlight;
	        }	
        }

    }

    //输出菜单 
    void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;	

	x = 2;
	y = 2;

    wattron(local_win,COLOR_PAIR(2));
	//box(menu_win, 0, 0);
    wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' '); //绘制边框
    wattroff(local_win,COLOR_PAIR(2));


	for(i = 0; i < n_choices; ++i)
	{	if(highlight == i ) /* High light the present choice */
		{	wattron(menu_win, COLOR_PAIR(1));  //设置当前窗体的颜色
			mvwprintw(menu_win, y, x, "%s", this->choices.at(highlight).c_str());
			wattroff(menu_win, COLOR_PAIR(1));
		}
		else
			mvwprintw(menu_win, y, x, "%s", this->choices.at(i).c_str());
		++y;
	}
    if(highlight == 0)
    {

        mvprintw(10, 0, "小型回复药剂 : 能帮助角色恢复10点生命值\n需花费的金币：10");   
        refresh(); //刷新界面     
    }else if(highlight == 1)
    {
        mvprintw(10, 0, "中型回复药剂 : 能帮助角色恢复30点生命值\n需花费的金币：30");   
        refresh(); //刷新界面     
    }else if(highlight == 2)
    {
        mvprintw(10, 0, "大型回复药剂 : 能帮助角色恢复90点生命值\n需花费的金币：60");   
        refresh(); //刷新界面     
    }else if(highlight == 3)
    {
        mvprintw(10, 0, "武器：《大宝剑》 : 能帮助角色增加10攻击力，5防御，15点生命值。\n需花费的金币：20");   
        refresh(); //刷新界面     
    }else if(highlight == 4)
    {
        mvprintw(10, 0, "武器：《天候棒》 : 能帮助角色增加50攻击力，30防御，25点生命值。\n需花费的金币：200");  
        refresh(); //刷新界面     
    }else if(highlight == 5)
    {
        mvprintw(10, 0, "武器：《黑刀夜》 : 能帮助角色增加500攻击力，200防御，450点生命值。\n需花费的金币：1000");   
        refresh(); //刷新界面     
    }

	wrefresh(menu_win);
}    
    void shop_main(bag*bag,role *role)//放入背包的对象 和人物的对象
    {

        //开始选择 
        int  ctrl =  this->get_ctrl(); 
        if(ctrl == 0)
        {
           //1.判断钱够不够用

              if(role->reduce_coin(10))
              {
                //购买成功 把商品加入背包里边
                mvprintw(10, 0, "恭喜您 购买成功 消费10金币！                      \n       剩余金币：%d           ",role->get_coins());   
                refresh(); //刷新界面  
                bag->add_potion(new small_potion());    
               
              }else{
                //余额不足
                mvprintw(10, 0, "剩余的金币 %d不足购买！请去做任务获得金币                 \n                ",role->get_coins());   
                refresh(); //刷新界面      
              }
              sleep(1);
 
           
        }else if(ctrl == 1)
        {
              if(role->reduce_coin(30))
              {
                //购买成功 把商品加入背包里边
                mvprintw(10, 0, "恭喜您 购买成功 消费30金币！                      \n       剩余金币：%d           ",role->get_coins());   
                refresh(); //刷新界面  
                bag->add_potion(new mid_potion());    
               
              }else{
                //余额不足
                mvprintw(10, 0, "剩余的金币 %d不足购买！请去做任务获得金币                 \n                ",role->get_coins());   
                refresh(); //刷新界面      
              }
              sleep(1);
        }else if(ctrl == 2)
        {
              if(role->reduce_coin(60))
              {
                //购买成功 把商品加入背包里边
                mvprintw(10, 0, "恭喜您 购买成功 消费60金币！                      \n       剩余金币：%d           ",role->get_coins());   
                refresh(); //刷新界面  
                bag->add_potion(new large_potion());    
               
              }else{
                //余额不足
                mvprintw(10, 0, "剩余的金币 %d不足购买！请去做任务获得金币                 \n                ",role->get_coins());   
                refresh(); //刷新界面      
              }
              sleep(1);            
        }else if(ctrl == 3)
        {
              if(role->reduce_coin(20))
              {
                //购买成功 把商品加入背包里边
                mvprintw(10, 0, "恭喜您 购买成功 消费20金币！                      \n       剩余金币：%d           ",role->get_coins());   
                refresh(); //刷新界面  
                bag->add_equipment(new dbj());   
               
              }else{
                //余额不足
                mvprintw(10, 0, "剩余的金币 %d不足购买！请去做任务获得金币                 \n                ",role->get_coins());   
                refresh(); //刷新界面      
              }
              sleep(1);              
        }else if(ctrl == 4)
        {

              if(role->reduce_coin(200))
              {
                //购买成功 把商品加入背包里边
                mvprintw(10, 0, "恭喜您 购买成功 消费200金币！                      \n       剩余金币：%d           ",role->get_coins());   
                refresh(); //刷新界面  
                bag->add_equipment(new thb());   
               
              }else{
                //余额不足
                mvprintw(10, 0, "剩余的金币 %d不足购买！请去做任务获得金币                 \n                ",role->get_coins());   
                refresh(); //刷新界面      
              }
              sleep(1);  
        }else if(ctrl == 5)
        {
              if(role->reduce_coin(1000))
              {
                //购买成功 把商品加入背包里边
                mvprintw(10, 0, "恭喜您 购买成功 消费1000金币！                      \n       剩余金币：%d           ",role->get_coins());   
                refresh(); //刷新界面  
                bag->add_equipment(new hyd());   
               
              }else{
                //余额不足
                mvprintw(10, 0, "剩余的金币 %d不足购买！请去做任务获得金币                 \n                ",role->get_coins());   
                refresh(); //刷新界面      
              }
              sleep(1);            
        }else if(ctrl == 6)
        {
          
        }
 
    }

    ~shop()
    {
        //清空窗体,指定窗体
        wclear(local_win); 

        //刷新窗体
        wrefresh(local_win);

        //销毁窗体
        delwin(local_win);
    }


private:
//窗口对象
WINDOW *local_win;
//地址
int x;
int y;
int highlight; //高亮区 
int    n_choices;//选项
vector<string> choices;

};

#endif
