#include"start.hpp"
#include"menu.hpp"
#include"rank.hpp"
#include<chrono>
#include<thread>
#include<fstream>
#include<cassert>
void Start()
{
	menu sub_menu(std::make_tuple(100,150,"腕立てスタート"),
						std::make_tuple(100,250,"設定"));
	bool return_flag=false;
	while(!ScreenFlip()&&!ProcessMessage()&&!ClearDrawScreen()){
		sub_menu.effectiving();
		
		switch(sub_menu.Drow_menus()){
		case 0:
			begin(sub_menu);
			return;
		case 1:
			Setting(sub_menu);
			return;
		case -1:
			;
		}
	}
}

void Setting(menu& m)
{
	unsigned int Green=GetColor(255,255,255);
	int max_f=-1;
	
	m.effectiving();

	DrawStringToHandle(0,145,"測定回数設定:",Green,m.font_Handle[2]);
	max_f=KeyInputNumber(0,200,640,0,false);

	std::ofstream ofs("data/max_v.dat");
	if(!ofs.is_open())assert(0);
	ofs<<max_f;
	ofs.close();
}


void begin(menu& m)
{
	ClearDrawScreen();
	const unsigned int x=0;
	const unsigned int y=195;
	const unsigned int Green=GetColor(0,255,0);
	unsigned int counter=0;

	m.load_max_v();
	
	DrawFormatString(520,450,GetColor(255,255,255),"Loading ...");
	for(unsigned int count_down=3;
			!ScreenFlip()&&!ProcessMessage()&&!ClearDrawScreen()&&count_down>0;
			--count_down){
				m.effectiving();
				DrawStringToHandle(x+260,y,boost::lexical_cast<std::string>(count_down).c_str(),
					Green,m.font_Handle[1]);
				
				std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::this_thread::sleep_for(std::chrono::seconds(1));

	std::chrono::system_clock::time_point start=std::chrono::system_clock::now();
	while(!ScreenFlip()&&!ProcessMessage()&&!ClearDrawScreen()){
		m.effectiving();

		DrawStringToHandle(x+100,y,"残り",Green,m.font_Handle[0]);
		DrawStringToHandle(x+235,y,boost::lexical_cast<std::string>(m.max_v-counter).c_str(),
							Green,m.font_Handle[1]);
		DrawStringToHandle(x,0,
			(std::string("回数: ")+=boost::lexical_cast<std::string>(m.max_v)).c_str(),
			Green,m.font_Handle[2]);
		DrawStringToHandle(x,45,
			(std::string("現在: ")+=boost::lexical_cast<std::string>(counter)).c_str(),
			Green,m.font_Handle[2]);
		DrawStringToHandle(x,90,
			(std::string("時間: ")+=boost::lexical_cast<std::string>(
				std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-start).count()
			)).c_str(),
			Green,m.font_Handle[2]);
		DrawStringToHandle(x,135,"Q: 中止",Green,m.font_Handle[2]);
		
		count(counter);
		if(counter==m.max_v)break;
		if(CheckHitKey(KEY_INPUT_Q))break;
	}

	Rank(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now()-start),m);
}