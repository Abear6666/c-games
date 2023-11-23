#ifndef _battle_hpp
#define _battle_hpp

#include <iostream>
#include "role.hpp"
#include "userwin.hpp"
#include "NPC.hpp"
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

//战斗界面类 
class battle
{
public:
    battle()
    {
        //创建窗体
        local_win = newwin(win_y-6,win_x,5,0);
        box(local_win, 0 , 0);      /* 0, 0 是字符默认的行列起始位置*/
        
        int y,x; 
        getmaxyx(local_win,y,x);
        x_w = x; 
        y_h = y;
        mvprintw(0,0,"y=%d",y); //y=30 
        mvprintw(0,6,"x=%d",x);//x=135

        /* 绘制探索地图 */
        /* 背景 */
        wattron(local_win,COLOR_PAIR(0));

        for (int d_y = 0; d_y < LINES; d_y++) {
            mvwhline(local_win,d_y, 0,' ',x); //COLS线长
        }

        wattroff(local_win,COLOR_PAIR(1));

        //生成怪物  
       // mvwprintw(local_win,10,10,"D海贼名称"); //y=30 

        /*刷新窗口缓冲，显示box */
        wrefresh(local_win);  

    }

    //选择技能
    void chose_skill_attk(role &r1, role &r2,NPC N,int flag,int skill_flag)
    {
        int attk1 = 0;
        if(skill_flag == 1)//1技能
        {
            attk1 = r1.skill1(r2);
        }else if(skill_flag == 2)
        {
            attk1 = r1.skill2(r2);            
        }else if(skill_flag == 3)
        {
            attk1 = r1.skill3(r2);            
        }

        mvwprintw(local_win,9,0,"%s :发起 %s : %d",r1.get_name().c_str(),r1.get_skill(0).c_str(), attk1); //y=30
        r2.be_hurt(attk1);
        // wrefresh(local_win);  
        if(r2.get_CUR_HP() <= 0)
        {
            
            wrefresh(local_win); 
            if(flag == 1)
            {
            r1.add_Exp(20);
                r1.add_coin(30);
            if(N.get_first_flag())//判断任务是否接收
            {
                N.add_sum1();
            }
                mvwprintw(local_win,13,0,"战斗胜利 获得20点经验值 30金币！"); //y=30   

            }else if(flag ==2)
            {
                r1.add_Exp(40);
                r1.add_coin(300);
            if(N.get_sec_flag())
            {
                    N.add_sum2();
            }
                mvwprintw(local_win,13,0,"战斗胜利 获得40点经验值 300金币！"); //y=30   


            }else if(flag == 3)
            {
                r1.add_Exp(100);
                r1.add_coin(1000);
            if(N.get_third_flag())
            {
                    N.add_sum3();
            }
                mvwprintw(local_win,13,0,"战斗胜利 获得100点经验值 1000金币！"); //y=30   

            }

        } 

        int attk2 = 0;
        if(skill_flag == 1)//1技能
        {
            attk2 = r2.skill1(r1);
        }else if(skill_flag == 2)
        {
            attk2 = r2.skill2(r1);            
        }else if(skill_flag == 3)
        {
            attk2 = r2.skill3(r1);            
        }        
            mvwprintw(local_win,10,0,"%s :发起 %s : %d",r2.get_name().c_str(),r2.get_skill(0).c_str(), attk2);
            wrefresh(local_win); 
        r1.be_hurt(attk2);
        if(r1.get_CUR_HP()<=0)
        {
            mvwprintw(local_win,13,0,"战斗失败 请重新选择人物出战！"); //   
                wrefresh(local_win); 
        }
    }

    //设置战斗场景  flag用来判断任务一二三
    void battle_win(role &r1,role &r2,NPC &N,bag &bag,int flag)
    {
            //r1 是角色   r2是怪物
            int attk1 = 0,attk2 = 0;
            //输出各自信息：
            output_role_msg(r1,r2);
            //选择技能 //开启菜单  
            menu  *cw = new menu(win_x-21,win_y-11,20,10,skillMenu); 
            //开始选择 
            int  ctrl =  cw->get_ctrl(); 
            

            while (1)
            {
                int  ctrl =  cw->get_ctrl(); 
                if(ctrl == 0)//技能1 普通攻击
                {

                    attk1 = r1.skill1(r2);
                    mvwprintw(local_win,9,0,"%s :发起 %s : %d",r1.get_name().c_str(),r1.get_skill(0).c_str(), attk1); //y=30
                    r2.be_hurt(attk1);
                   // wrefresh(local_win);  
                    if(r2.get_CUR_HP() <= 0)
                    {
                     
                         if(flag == 1)
                         {
                            r1.add_Exp(20);
                             r1.add_coin(30);
                            if(N.get_first_flag())//判断任务是否接收
                            {
                                N.add_sum1();
                            }
                               mvwprintw(local_win,13,0,"战斗胜利 获得20点经验值 30金币！"); //y=30   
                                     wrefresh(local_win); 

                         }else if(flag ==2)
                         {
                            r1.add_Exp(40);
                             r1.add_coin(300);
                            if(N.get_sec_flag())
                            {
                                 N.add_sum2();
                            }
                             mvwprintw(local_win,13,0,"战斗胜利 获得40点经验值 300金币！"); //y=30   
                                    wrefresh(local_win); 

                         }else if(flag == 3)
                         {
                             r1.add_Exp(100);
                             r1.add_coin(1000);
                            if(N.get_third_flag())
                            {
                                 N.add_sum3();
                            }
                             mvwprintw(local_win,13,0,"战斗胜利 获得100点经验值 1000金币！"); //y=30   
                                wrefresh(local_win); 
                         }
 
                         break;
                    } 
                    attk2 = r2.skill1(r1);
                     mvwprintw(local_win,10,0,"%s :发起 %s : %d",r2.get_name().c_str(),r2.get_skill(0).c_str(), attk2);
                     wrefresh(local_win); 
                    r1.be_hurt(attk2);
                    if(r1.get_CUR_HP()<=0)
                    {
                        mvwprintw(local_win,13,0,"战斗失败 请重新选择人物出战！"); //   
                         wrefresh(local_win); 
                          break;
                    }
                }

                if(ctrl == 1)//技能2 
                {
                    attk1 = r1.skill2(r2);
                    mvwprintw(local_win,9,0,"%s :发起 %s : %d",r1.get_name().c_str(),r1.get_skill(0).c_str(), attk1); //y=30
                    r2.be_hurt(attk1);
                   // wrefresh(local_win);  
                    if(r2.get_CUR_HP() <= 0)
                    {
                     
                         if(flag == 1)
                         {
                            r1.add_Exp(20);
                             r1.add_coin(30);
                            if(N.get_first_flag())//判断任务是否接收
                            {
                                N.add_sum1();
                            }
                               mvwprintw(local_win,13,0,"战斗胜利 获得20点经验值 30金币！"); //y=30   
                                     wrefresh(local_win); 

                         }else if(flag ==2)
                         {
                            r1.add_Exp(40);
                             r1.add_coin(300);
                            if(N.get_sec_flag())
                            {
                                 N.add_sum2();
                            }
                             mvwprintw(local_win,13,0,"战斗胜利 获得40点经验值 300金币！"); //y=30   
                                    wrefresh(local_win); 

                         }else if(flag == 3)
                         {
                             r1.add_Exp(100);
                             r1.add_coin(1000);
                            if(N.get_third_flag())
                            {
                                 N.add_sum3();
                            }
                             mvwprintw(local_win,13,0,"战斗胜利 获得100点经验值 1000金币！"); //y=30   
                                wrefresh(local_win); 
                         }
 
                         break;
                    } 
                    attk2 = r2.skill2(r1);
                     mvwprintw(local_win,10,0,"%s :发起 %s : %d",r2.get_name().c_str(),r2.get_skill(0).c_str(), attk2);
                     wrefresh(local_win); 
                    r1.be_hurt(attk2);
                    if(r1.get_CUR_HP()<=0)
                    {
                        mvwprintw(local_win,13,0,"战斗失败 请重新选择人物出战！"); //   
                         wrefresh(local_win); 
                          break;
                    }                   
                }

                if(ctrl == 2)//技能3 
                {
                    attk1 = r1.skill3(r2);
                    mvwprintw(local_win,9,0,"%s :发起 %s : %d",r1.get_name().c_str(),r1.get_skill(0).c_str(), attk1); //y=30
                    r2.be_hurt(attk1);
                   // wrefresh(local_win);  
                    if(r2.get_CUR_HP() <= 0)
                    {
                     
                         if(flag == 1)
                         {
                            r1.add_Exp(20);
                             r1.add_coin(30);
                            if(N.get_first_flag())//判断任务是否接收
                            {
                                N.add_sum1();
                            }
                               mvwprintw(local_win,13,0,"战斗胜利 获得20点经验值 30金币！"); //y=30   
                                     wrefresh(local_win); 

                         }else if(flag ==2)
                         {
                            r1.add_Exp(40);
                             r1.add_coin(300);
                            if(N.get_sec_flag())
                            {
                                 N.add_sum2();
                            }
                             mvwprintw(local_win,13,0,"战斗胜利 获得40点经验值 300金币！"); //y=30   
                                    wrefresh(local_win); 

                         }else if(flag == 3)
                         {
                             r1.add_Exp(100);
                             r1.add_coin(1000);
                            if(N.get_third_flag())
                            {
                                 N.add_sum3();
                            }
                             mvwprintw(local_win,13,0,"战斗胜利 获得100点经验值 1000金币！"); //y=30   
                                wrefresh(local_win); 
                         }
 
                         break;
                    } 
                    attk2 = r2.skill3(r1);
                     mvwprintw(local_win,10,0,"%s :发起 %s : %d",r2.get_name().c_str(),r2.get_skill(0).c_str(), attk2);
                     wrefresh(local_win); 
                    r1.be_hurt(attk2);
                    if(r1.get_CUR_HP()<=0)
                    {
                        mvwprintw(local_win,13,0,"战斗失败 请重新选择人物出战！"); //   
                         wrefresh(local_win); 
                          break;
                    }
                }
                if(ctrl == 3)//其他操作
                {
                potionMenu.clear();
                bag.show_potion();
                potionMenu.push_back("返回");
                    //其他操作 补血
                    menu  *cw = new menu(win_x-61,win_y-11,61,10,potionMenu); 
                    //开始选择 
                    int  ctrl =  cw->get_ctrl(); 
                    if(ctrl == 0)
                    {
                        bag.admin_menu(r1,10,1,1,"小型药水",1);
                    }else if(ctrl == 1)
                    {
                        bag.admin_menu(r1,30,1,1,"中型药水",1);
                    }else if(ctrl == 2)
                    {
                        bag.admin_menu(r1,60,1,1,"大型药水",1);
                    }else{
                        delete cw;
                        continue;
                    }
                   


                }
                if(ctrl == 4)
                {
                    break;
                }
                  
                  mvwprintw(local_win,9,0,"                                                     ");
                  mvwprintw(local_win,10,0,"                                                    ");
                sleep(1);
                 output_role_msg(r1,r2);
                                   
            }
            
            delete  cw; //销毁窗体


    }


    //输出人物信息
    void output_role_msg(role &r1,role &r2)
    {
        mvwprintw(local_win,3,0,"            "); //y=30 
        mvwprintw(local_win,3,50,"          "); //y=30 
        //输出各自信息：
        mvwprintw(local_win,1,0,"海贼名称:%s",r1.get_name().c_str()); //y=30 
        mvwprintw(local_win,2,0,"等级:%d",r1.get_grade()); //y=30 
        mvwprintw(local_win,3,0,"生命值:%d ",r1.get_CUR_HP()); //y=30 
        mvwprintw(local_win,4,0,"攻击力:%d",r1.get_attk()); //y=30 
        mvwprintw(local_win,5,0,"装备:%s",r1.get_equimnet().c_str()); //y=30 
        mvwprintw(local_win,6,0,"经验值:%d/100",r1.get_experience()); //y=30 
        mvwprintw(local_win,7,0,"悬赏金额:%d",r1.get_reward()); //y=30 

        mvwprintw(local_win,1,50,"海贼名称:%s",r2.get_name().c_str()); //y=30 
        mvwprintw(local_win,2,50,"等级:%d",r2.get_grade()); //y=30 
        mvwprintw(local_win,3,50,"生命值:%d",r2.get_CUR_HP()); //y=30 
        mvwprintw(local_win,4,50,"攻击力:%d",r2.get_attk()); //y=30 
        mvwprintw(local_win,5,50,"装备:%s",r2.get_equimnet().c_str()); //y=30  
        mvwprintw(local_win,6,50,"经验值:%d/100",r2.get_experience()); //y=30               
        mvwprintw(local_win,7,50,"悬赏金额:%d",r2.get_reward()); //y=30 
        wrefresh(local_win);          
    }



//析构函数
~battle()
{
    //清空窗体,指定窗体
    wclear(local_win); 


    //刷新窗体
    wrefresh(local_win);

    //销毁窗体
    delwin(local_win);
}

private:
WINDOW *local_win;
int x_w; 
int y_h;
//移动的位置
int m_x = 0; 
int m_y = 0;
};


#endif
