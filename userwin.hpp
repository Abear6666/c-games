#ifndef _USERWIN_HPP
#define _USERWIN_HPP

#include <iostream>
//添加curses 库
#include <curses.h>
#include <vector>

//引用C语言库头文件
extern "C"
{
#include <stdio.h>

}

using namespace std;
//一些宏定义
#define GRASS     ' '
#define EMPTY     '.'
#define WATER     '~'
#define MOUNTAIN  '^'
#define PLAYER    '*'
#define GRASS_PAIR     1
#define EMPTY_PAIR     1
#define WATER_PAIR     2
#define MOUNTAIN_PAIR  3
#define PLAYER_PAIR    4

//声明函数接口
void start_win();

//菜单类
class  menu
{
private:
//窗口对象
WINDOW *local_win;
//地址
int x;
int y;
int highlight; //高亮区 
int    n_choices;//选项
vector<string> choices;

public:
     menu(int sx,int sy,int width,int high,vector<string> c):choices(c)
     {
        //获取选项大小
        this->n_choices =  choices.size(); 

        //新建一个窗体     
        local_win = newwin(high,width,sy,sx); //h w y x 

       //获取当前菜单的宽度和高度 
        x = getmaxx(local_win);
        y = getmaxy(local_win);

        highlight = 0;

        mvprintw(0,0,"新建窗体 x=%d ,y=%d",x,y);
        print_menu(local_win,highlight);

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

    int get_ctrl_info(const char *str1,const char *str2,const char *str3)
    {
        print_menu_info(local_win,highlight,str1,str2,str3);
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
           print_menu_info(local_win,highlight,str1,str2,str3);
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
    void print_menu_info(WINDOW *menu_win, int highlight,const char *str1,const char *str2,const char *str3)
    {
        int x, y, i;	

        x = 2;
        y = 2;

        wattron(local_win,COLOR_PAIR(3));
        //box(menu_win, 0, 0);
        wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' '); //绘制边框
        wattroff(local_win,COLOR_PAIR(3));


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
            mvprintw(10, 0, str1);   
                refresh(); //刷新界面          
        }else if(highlight ==1)
        {
            mvprintw(10, 0, str2);   
                refresh(); //刷新界面 
        }else if(highlight ==2)
        {
            mvprintw(10, 0, str3);   
                refresh(); //刷新界面 
        }

        wrefresh(menu_win);
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
	wrefresh(menu_win);
}

    void clear_screen()
    {
        wclear(local_win);
        wrefresh(local_win);

    }
    ~menu()  //析构函数
    {
        //清空窗体,指定窗体
        wclear(local_win); 


        //刷新窗体
        wrefresh(local_win);

        //销毁窗体
        delwin(local_win);

    }
};


#endif
