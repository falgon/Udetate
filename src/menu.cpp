#include"menu.hpp"
#include<fstream>
#include<cassert>
#include<boost/lexical_cast.hpp>
#include<iostream>

menu::menu():max_v(0)
{
	// I wanted to using Uniform initialization... But VC++11 is(ry
	menu_string_color=GetColor(51,204,255);
	select_m=0;
	Picture_Handle.push_back(LoadGraph("img/bar.png"));
	menus.push_back(std::make_tuple(100,100,"開始"));
	menus.push_back(std::make_tuple(100,200,"ランキング"));
	menus.push_back(std::make_tuple(100,300,"終了"));

	font_Handle.push_back(CreateFontToHandle("メイリオ",66,3,DX_FONTTYPE_ANTIALIASING_EDGE));
	font_Handle.push_back(CreateFontToHandle("メイリオ",150,3,DX_FONTTYPE_ANTIALIASING_EDGE));
	font_Handle.push_back(CreateFontToHandle("メイリオ",70,3,DX_FONTTYPE_ANTIALIASING_EDGE));
}

menu::menu(const std::tuple<int,int,const char*>& lhs,
		   const std::tuple<int,int,const char*>& rhs)
{
	menu_string_color=GetColor(51,204,255);
	select_m=0;

	menus.push_back(lhs);
	menus.push_back(rhs);

	font_Handle.push_back(CreateFontToHandle("メイリオ",66,3,DX_FONTTYPE_ANTIALIASING_EDGE));
	font_Handle.push_back(CreateFontToHandle("メイリオ",150,3,DX_FONTTYPE_ANTIALIASING_EDGE));
	font_Handle.push_back(CreateFontToHandle("メイリオ",40,3,DX_FONTTYPE_ANTIALIASING_EDGE));
}

menu::~menu()
{
	if(!Picture_Handle.empty())DeleteGraph(Picture_Handle[0]);
}

int menu::Drow_menus()
{
	count();

	for(unsigned int i=0; i<menus.size(); ++i){
		if(i==select_m)
			DrawStringToHandle(std::get<0>(menus[i])-35,std::get<1>(menus[i]),
								std::get<2>(menus[i]).c_str(),menu_string_color,font_Handle[0]);
		else
			DrawStringToHandle(std::get<0>(menus[i]),std::get<1>(menus[i]),
								std::get<2>(menus[i]).c_str(),menu_string_color,font_Handle[0]);
	}

	if(CheckHitKey(KEY_INPUT_RETURN))
		return select_m;
	return -1;
}

void menu::Draw_bars()
{
	for(unsigned int i=0; i<menus.size(); ++i)
		DrawGraph(0,std::get<1>(menus[i])-12,Picture_Handle[0],true);
}

void menu::effectiving()
{
	ef.graph();
}

void menu::load_max_v()
{
	std::string tmp;
	std::ifstream ifs("data/max_v.dat");
	if(!ifs.is_open())assert(0);
	ifs>>tmp;
	ifs.close();
	max_v=boost::lexical_cast<unsigned int>(tmp);
}