#include "userwin.hpp"
#include "role.hpp"
#include "battle.hpp"
#include "bag_shop.hpp"
#include "save.hpp"
#include "NPC.hpp"

int win_x=0;
int win_y=0;
//菜单选择栏 
vector<string>  controlMenu; //主界面控制

vector<string>  choiceMenu; //通用菜单

vector<string>  skillMenu; //技能菜单

vector<string>  mapMenu; //地图菜单

vector<string>  roleMenu; //人物菜单

vector<string>  mainMenu; //主功能菜单

//vector<string>  shopMenu; //商店菜单

vector<string> bagMenu;//背包菜单

extern vector<string>  role_disMenu;//人物菜单


void init_interface()
{
    //设置中文环境
    setlocale(LC_ALL,"");
   //WINDOW *my_win;

    //初始化界面 
    initscr();    				 //进入curses 模式
    cbreak();                    //把终端的CBREAK模式打开
    noecho();                    //关闭回显
   //curs_set(0);                //把光标置为不可见
    keypad(stdscr, true);        //使用用户终端的键盘上的小键盘

    start_color();               //开启颜色功能 
    init_pair(1, COLOR_WHITE, COLOR_RED);  //定义白色种
    init_pair(2, COLOR_BLACK, COLOR_GREEN);  //定义黑色红低
    init_pair(3, COLOR_BLACK, COLOR_MAGENTA);  //定义红色紫低
    init_pair(4, COLOR_BLACK, COLOR_CYAN);  //定义红色紫低
    init_pair(5, COLOR_BLACK, COLOR_BLACK);  //定义红色紫低
   //保存当前界面的X Y 
    win_x = COLS; 
    win_y = LINES; 

    move(1,COLS/2-10); //move(y,x); 
    attron(COLOR_PAIR(4));  //添加颜色1  
	printw("欢迎来到海贼王争霸世界!");
    attroff(COLOR_PAIR(4)); //结束颜色1

    move(3,COLS-30);
    printw("win_x=%d win_y=%d\n",win_x,win_y);  //输出当前屏幕的大小 

    move(5,0);
    for(int i=0;i<COLS;i++)
        addstr("_");

	refresh(); //刷新界面  记得要刷新一次，不然不显示  


    controlMenu.push_back("新建角色");
    controlMenu.push_back("继续游戏");
    controlMenu.push_back("退出游戏");

    choiceMenu.push_back("开始战斗");
    choiceMenu.push_back("查看怪物属性");
    choiceMenu.push_back("离开"); 

    skillMenu.push_back("第一技能");
    skillMenu.push_back("第二技能");
    skillMenu.push_back("第三技能");
    skillMenu.push_back("背包");
    skillMenu.push_back("逃跑");

    mapMenu.push_back("东海篇");
    mapMenu.push_back("空岛篇");
    mapMenu.push_back("顶上战争篇");
    mapMenu.push_back("离开");

    roleMenu.push_back("蒙奇·D路飞");
    roleMenu.push_back("哥尔·D艾斯");

    mainMenu.push_back("商店");
    mainMenu.push_back("装备背包");
    mainMenu.push_back("冒险地图");    
    mainMenu.push_back("治疗");   
    mainMenu.push_back("我的任务");   
    mainMenu.push_back("存档退出");   


    bagMenu.push_back("武器");
    bagMenu.push_back("药水");   
    bagMenu.push_back("人物"); 
    bagMenu.push_back("返回主界面");   

}

//地图   
class game_map
{
private: 
WINDOW *local_win;
int x_w; 
int y_h;
//移动的位置
int m_x = 0; 
int m_y = 0;
char Mon[10];
int n;

public:
//构造函数
game_map(const char *Mon,int n)
{
    strcpy(this->Mon,Mon);
    this->n = n;
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
    wattron(local_win,COLOR_PAIR(this->n));

    for (int d_y = 0; d_y < LINES; d_y++) {
        mvwhline(local_win,d_y, 0,' ',x); //COLS线长
    }

    wattroff(local_win,COLOR_PAIR(this->n));

    //生成怪物  
    mvwprintw(local_win,10,10,this->Mon); //

    //生成离开的点

    mvwprintw(local_win,10,30,"B"); //y=30 	

	/*刷新窗口缓冲，显示box */
	wrefresh(local_win);   

}

void refresh_map()
{ 
	int y,x; 
	getmaxyx(local_win,y,x);
    x_w = x; 
    y_h = y;
	mvprintw(0,0,"y=%d",y); //y=30 
	mvprintw(0,6,"x=%d",x);//x=135

    /* 绘制探索地图 */
    /* 背景 */
    wattron(local_win,COLOR_PAIR(this->n));

    for (int d_y = 0; d_y < LINES; d_y++) {
        mvwhline(local_win,d_y, 0,' ',x); //COLS线长
    }

    wattroff(local_win,COLOR_PAIR(this->n));

    //生成怪物  
    mvwprintw(local_win,10,10,this->Mon); //y=30 

    mvwprintw(local_win,10,30,"B"); //y=30 
	

	/*刷新窗口缓冲，显示box */
	wrefresh(local_win);      
} 

int is_move_okay(int y, int x,int *mark)
{
    this->m_x = x;
    this->m_y = y;

    int testch;
    /* 当空白处可以进入的时候返回true */
    testch = mvwinch(local_win,y, x);  //获取当前的文字 
    *mark = testch; //得到字符
    return (((testch & A_CHARTEXT) == GRASS)    //判断是否为 点或空白处
            || ((testch & A_CHARTEXT) == EMPTY));
}

void move_map(role &r2,NPC &N,char M,bag &bag,int flag)//flag用来判断任务一二三
{

    int y, x;
    int ch;
 /* 在左下角创建新角色 */
     y = y_h - 1;
     x = 0;

    int mark=0;

    do {
        /* 默认情况下，你获得了一个闪烁的光标--用来指明玩家 * */
        wattron(local_win,COLOR_PAIR(1));
        mvwaddch(local_win,y, x, PLAYER);
        wattroff(local_win,COLOR_PAIR(1));
        wmove(local_win,y, x);
        wrefresh(local_win);
        ch = getch();
        /* 测试输入键值并获取方向 */
        switch (ch) {
        case KEY_UP:
        case 'w':
        case 'W':
            if ((y > 0) && is_move_okay(y - 1, x,&mark)) {
                wattron(local_win,COLOR_PAIR(2));
                mvwaddch(local_win,y, x, EMPTY);  //走过的位置
                wattroff(local_win,COLOR_PAIR(2));
                y = y - 1;
            }
            break;
        case KEY_DOWN:
        case 's':
        case 'S':
            if ((y < y_h - 1) && is_move_okay(y + 1, x,&mark)) {
                wattron(local_win,COLOR_PAIR(2));
                mvwaddch(local_win,y, x, EMPTY);
                wattroff(local_win,COLOR_PAIR(2));
                y = y + 1;
            }
            break;
        case KEY_LEFT:
        case 'a':
        case 'A':
            if ((x > 0) && is_move_okay(y, x - 1,&mark)) {
                wattron(local_win,COLOR_PAIR(2));
                mvwaddch(local_win,y, x, EMPTY);
                wattroff(local_win,COLOR_PAIR(2));
                x = x - 1;
            }
            break;
        case KEY_RIGHT:
        case 'd':
        case 'D':
            if ((x < x_w - 1) && is_move_okay(y, x + 1,&mark)) {
                wattron(local_win,COLOR_PAIR(2));
                mvwaddch(local_win,y, x, EMPTY);
                wattroff(local_win,COLOR_PAIR(2));
                x = x + 1;
            }
            break;
        }


        mvprintw(1,0,"mark=%c",mark);
        wrefresh(local_win);


        if(mark == M)  //遇到怪物
        {
            
            //开启菜单  
            menu  *cw = new menu(win_x-20,win_y-11,20,10,choiceMenu); 
            //开始选择 
            int  ctrl =  cw->get_ctrl(); 
            delete  cw; //销毁窗体
            if(ctrl == 0)
            {
            //选择角色
              role_disMenu.resize(bag.return_role_size());//删除重复添加的角色信息
            menu  *cw = new menu(win_x-20,win_y-11,20,10,role_disMenu); //选择角色出战
        

            //开始选择 
            int  ctrl =  cw->get_ctrl();    
            role *r1 = bag.return_role_in(ctrl);  //返回对应角色的对象指针
        
                while (1)
                {
                    //判断角色血量是否为0 则返回
                    if(r1->get_CUR_HP()<=0)
                    {
                        clear();
                        mvprintw(10, 0, "当前血量不足 无法出战！");   
                        refresh(); //刷新界面 
                        sleep(1);
                        break;       
                    }
                    battle *b;
                    b = new battle;
                    r2.recovery_CurHp();//怪物补血
                    b->battle_win(*r1,r2,N,bag,flag);//开始战斗
                    //弹出一个离开界面菜单   再次战斗 退出冒险
                    vector <string> backMenu;
                    backMenu.push_back("再次战斗");
                    backMenu.push_back("退出战斗");
                    
                    menu  *bac =new menu(win_x/2-10,win_y/2-5,20,10,backMenu); 
                    //开始选择 
                    ctrl =  bac->get_ctrl(); 
                    delete bac;
                    if(ctrl == 0)
                    {                  
                        //继续战斗
                        continue;
                    }
                    if(ctrl == 1)
                    {
                        //退出战斗
                         
                        break;
                    }
                       //清空窗体,指定窗体

                }
                wclear(local_win); 

                //刷新窗体
                wrefresh(local_win);
                refresh_map();//重画界面

                continue;    

            }else if(ctrl == 1)   //输出怪物属性
            {
             
                wclear(local_win); 

                //刷新窗体
                wrefresh(local_win);
                refresh_map();//重画界面                
                r2.output_role_msg(local_win);
                continue;
            }else if(ctrl == 2)//退出
            {
                //清空窗体,指定窗体
                wclear(local_win); 

                //刷新窗体
                wrefresh(local_win);
                refresh_map();//重画界面
 
                continue;
            }


             //清空窗体,指定窗体
            wclear(local_win); 



            //刷新窗体
            wrefresh(local_win);

            //销毁窗体
            delwin(local_win);    
        }

        if(mark == 'B')//离开的点
        {
             wclear(local_win); 



            //刷新窗体
            wrefresh(local_win);

            //销毁窗体
            delwin(local_win);
             mvprintw(2,0,"离开了\n");
             break;

        } 

    }
    while ((ch != 'q') && (ch != 'Q'));
}

//析构函数
~game_map()
{
    //清空窗体,指定窗体
    wclear(local_win); 



    //刷新窗体
    wrefresh(local_win);

    //销毁窗体
    delwin(local_win);
}
};

//主界面运行
void start_win()
{
    role *people;
    bag bag;
    save save;
    NPC NPC;
    init_interface();//初始化界面接口
    //主控界面
     menu  *cw = new menu(win_x/2-10,win_y/2-5,20,10,controlMenu); 
    // //开始选择 
    int  ctrl =  cw->get_ctrl(); 
    delete  cw; //销毁窗体 
    //********************新建角色
    if(ctrl == 0)
    {
        //人物选择
        menu  *rw = new menu(win_x/2-10,win_y/2-5,20,10,roleMenu); 
        // 开始选择 
        ctrl =  cw->get_ctrl(); 
        delete  cw; //销毁窗体     
        
        if(ctrl == 0)
        {
            people = new lufei ;
        }else if(ctrl == 1)
        {
            people = new aisi ;
        }
            bag.add_role(people);
     //********************读取文档
    }else if(ctrl == 1)
    {
        save.read_all_role(bag);
        save.read_potion(bag);
        save.read_equipment(bag);
            //主角色 读取文件的第一个英雄 
        people = bag.return_role_in(0);
            attron(COLOR_PAIR(4));  //添加颜色1 
        mvprintw(10, 10, "读取游戏存档中。。。。请稍后>>>>>>>>>>>>>>>>>>>>>>>>");   
         attron(COLOR_PAIR(4));  //添加颜色1 
        refresh(); //刷新界面   
        sleep(1);
        mvprintw(10, 10, "游戏存档读取成功！欢迎回到海贼王 *-*                 ");   
        refresh(); //刷新界面    
        sleep(1);  
        attron(COLOR_PAIR(5));  //添加颜色1   
        mvprintw(10, 10, "                                                     ");   
        refresh(); //刷新界面           
    }else if(ctrl == 2)
    {
        mvprintw(10, 10, "年轻人 欢迎下次再来战斗吧！>>>>>>>>>>>>>>>>>>>>>>>>");   
        refresh(); //刷新界面   
        sleep(1);
        system("killall -9 a.out");
        exit(0);
        
    }     
    //**************刷新界面功能显示 商店 装备背包 冒险地图 治疗 存档退出
    while (1)
    {
        menu  *win = new menu(win_x/2-10,win_y/2-5,20,10,mainMenu); 
        // 开始选择 
        ctrl =  win->get_ctrl(); 
        delete  win; //销毁窗体     
        if(ctrl == 0)//商店
        {
               clear();
            move(1,COLS/2); //move(y,x); 
            attron(COLOR_PAIR(1));  //添加颜色1  
            printw("  《道具商店》  ");
            attroff(COLOR_PAIR(1)); //结束颜色1
           
           shop shop;
           shop.shop_main(&bag,people);
             clear();

        }else if(ctrl == 1)//装备背包
        {
            move(12,COLS/2); //move(y,x); 
            attron(COLOR_PAIR(1));  //添加颜色1  
            printw("《装备背包》");
            attroff(COLOR_PAIR(1)); //结束颜色1
            bag.bag_main(*people);
          
            move(12,COLS/2); //move(y,x); 
            printw("           ");           
        }else if(ctrl == 2)//地图
        {
            //地图选择：
            menu  *dt = new menu(win_x/2-10,win_y/2-5,20,10,mapMenu); 
            // //开始选择 
            ctrl =  dt->get_ctrl(); 
            delete  dt; //销毁窗体    
            if(ctrl == 0)//东岛篇  
            {
                game_map  *m;
  
                m =  new game_map("M",1); //新建地图
                baji b;
                //开始移动
                m->move_map(b,NPC,'M',bag,1);
     
            }else if(ctrl == 1)
            {
                 game_map  *m;

                m =  new game_map("K",2); //新建地图空岛篇
                //开始移动
                ainilu b;
                m->move_map(b,NPC,'K',bag,2);              
            }else if(ctrl == 2)
            {
                 game_map  *m;

                m =  new game_map("C",3); //新建地图顶上战争
                //开始移动
                chiquan b;
                m->move_map(b,NPC,'C',bag,3);              
            }         
        }else if(ctrl == 3)//治疗
        {
            //治疗
            bag.recovery_allCurHp();
            move(11,COLS/2-10); //move(y,x); 
            attron(COLOR_PAIR(1));  //添加颜色1  
            printw("全部角色治疗成功！");
            attroff(COLOR_PAIR(1)); //结束颜色1
            refresh();
            sleep(1);
            move(11,COLS/2-10); //move(y,x); 
            printw("                  ");

        }else if(ctrl == 4)//我的任务
        {
           
            NPC.NPC_main(bag);
             clear();

        }else if(ctrl == 5)//存档退出
        {
            save.save_all_role(bag);
            save.save_potion(bag);
            save.save_equipment(bag);
                attron(COLOR_PAIR(4));  //添加颜色1 
        mvprintw(10, 10, "游戏存档中。。。。请稍后>>>>>>>>>>>>>>>>>>>>>>>>");   
         attron(COLOR_PAIR(4));  //添加颜色1 
        refresh(); //刷新界面   
        sleep(1);
        mvprintw(10, 10, "游戏存档成功！欢迎下次回来！ *-*                 ");   
        refresh(); //刷新界面    
        sleep(1); 
        system("killall -9 a.out");
        exit(0);
        }
    }

    
}

