#ifndef _NPC_hpp
#define _NPC_hpp

#include <iostream>
#include "role.hpp"
#include "userwin.hpp"
#include "bag_shop.hpp"
using namespace std;

//引用C语言库头文件
extern "C"
{
#include <stdio.h>
#include <unistd.h>
}

extern int win_x;
extern int win_y;
extern vector<string>  skillMenu;


class NPC
{
public:
    NPC()
    { 
       this->complete_sum1 = 0; //任务一完成打怪的次数
       this->complete_sum2 = 0;//任务二完成打怪的次数
       this->complete_sum3 = 0;//任务三完成打怪的次数

        this->first_flag = false;//接收任务标志
        this->sec_flag= false;
        this->third_flag= false;

        choices.push_back("任务1====》营救娜美");
        choices.push_back("任务2====》营救索隆");
        choices.push_back("任务3====》营救乔巴");
        choices.push_back("返回主界面");
    }
     
    void NPC_main(bag &bag)//NPC界面
    {
        //获取选项大小
        this->n_choices =  choices.size(); 

        //新建一个窗体     
        local_win = newwin(30,30,6,50); //h w y x 

       //获取当前菜单的宽度和高度 
        x = getmaxx(local_win);
        y = getmaxy(local_win);

        highlight = 0;

        mvprintw(0,0,"任务中心 x=%d ,y=%d",x,y);
        print_menu(local_win,highlight);
        move(5,0);
        for(int i=0;i<COLS;i++)
            addstr("_");
        wrefresh(local_win); //刷新窗体
        refresh();//刷新主窗体

        //营救索隆 娜美 乔巴

        while (1)
        {
            int  ctrl =  this->get_ctrl(); 
            if(ctrl == 0)//营救娜美
            {
                if(!first_flag)
                {
                    chose_task(first_flag,complete_sum1);
                    first_flag = true;
                }else{
                   int flag = chose_task(first_flag,complete_sum1);
                   if(flag == 1)
                   {
                    //将人物链表存入信息
                    //创建人物
                        bag.add_role(new namei);
                        mvprintw(0,0,"成功营救娜美");
                         refresh();//刷新主窗体
                   }
                }
                
            }else if(ctrl == 1)//营救索隆
            {
                if(!sec_flag)
                {
                    chose_task(sec_flag,complete_sum2);
                    sec_flag = true;
                }else{
                   int flag = chose_task(sec_flag,complete_sum2);
                   if(flag == 1)
                   {
                    //将人物链表存入信息
                    //创建人物
                        bag.add_role(new suolong);
                        mvprintw(0,0,"成功营救索隆");
                         refresh();//刷新主窗体
                   }
                }                             
                
            }else if(ctrl == 2)//营救乔巴
            {
                if(!third_flag)
                {
                    chose_task(third_flag,complete_sum3);
                    third_flag = true;
                }else{
                   int flag = chose_task(third_flag,complete_sum3);
                   if(flag == 1)
                   {
                    //将人物链表存入信息
                    //创建人物
                        bag.add_role(new qiaoba);
                        mvprintw(0,0,"成功营救乔巴");
                         refresh();//刷新主窗体
                   }
                }                               
                
            }else 
            {
              break;
            }
            

  

        }
        

    }

    int chose_task(bool flag,int complete_sum)//接任务 提交任务 离开菜单管理
    {
            vector<string> NPCMenu;
            NPCMenu.push_back("接任务");
            NPCMenu.push_back("提交任务");
            NPCMenu.push_back("离开");
            menu *cw =  new menu(win_x-20,win_y-11,20,10,NPCMenu); 
            while (1)
            {
                int ctrl = cw->get_ctrl();
                if(ctrl == 0)
                {
                    if(!flag )
                    {
                        clear();
                        mvprintw(11, 10, "接收任务成功！");   
                        refresh(); //刷新界面 
                        sleep(1); 
                        flag = true; 
                        delete cw; 
                        break;            
                    }else{
                        clear();
                        mvprintw(11, 10, "不允许重复接收任务！按上下键切回模式");   
                        refresh(); //刷新界面 
                        sleep(1);  
                                           
                    }
                                
                }else if(ctrl == 1)
                {
                    if(flag )
                    {
                        clear();
                        if(complete_sum>=2)
                        {
                            mvprintw(11, 10, "任务完成！解救伙伴成功！");   
                            refresh(); //刷新界面 
                            sleep(1); 
                            return 1;
                        }else{
                            mvprintw(11, 10, "当前完成的次数：%d",complete_sum);   
                            refresh(); //刷新界面 
                            sleep(1); 
                        }

                        flag = true; 
                        delete cw;  
                        break;            
                    }else{
                        clear();
                        mvprintw(11, 10, "还没接收任务！按上下键切回模式");   
                        refresh(); //刷新界面 
                        sleep(1);                     
                    }
                }else if(ctrl == 2)
                {
                    //返回
                    delete cw;
                    break;
                }
                
            }
            
        
    }

    bool get_first_flag(){return this->first_flag;}
    bool get_sec_flag(){return this->sec_flag;}
    bool get_third_flag(){return this->third_flag;}

    void add_sum1(){this->complete_sum1++;}
    void add_sum2(){this->complete_sum2++;}
    void add_sum3(){this->complete_sum3++;}
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

        mvprintw(10, 0, "娜美 小时候为了救回家乡被迫加入了阿龙一伙。从橘子镇开始和草帽一伙合作，\n在路飞打倒了阿龙后正式加入了草帽一伙。梦想是绘画出全世界的地图。\n想要营救娜美需要前往东海篇打败小丑巴基2次！");   
        refresh(); //刷新界面     
    }else if(highlight == 1)
    {
        mvprintw(10, 0, "索隆 路飞跟克比一起探索到达海军基地寻找罗罗诺亚索隆，想让罗罗诺亚.索隆一起做海贼。\n但到海军基地的时候，得知罗罗诺亚.索隆被卡蒙上校儿子囚绑起来，限制人身自由，\n为了救出索隆需要打败第二关的怪物2次！");   
        refresh(); //刷新界面     
    }else if(highlight == 2)
    {
        mvprintw(10, 0, "乔巴 路飞在打倒瓦尔波后，多次邀请乔巴加入成为伙伴。\n但乔巴的内心却一直交战着，反复认为自己是驯鹿所以没资格加入，\n为了救出索隆需要打败第三关的怪物2次！");   
        refresh(); //刷新界面     
    }

	wrefresh(menu_win);
}  


    ~NPC()
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
int complete_sum1;
int complete_sum2;
int complete_sum3;

bool first_flag ;
bool sec_flag;
bool third_flag;

};


#endif
