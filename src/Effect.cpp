#include"Effect.hpp"

effect::effect()
	:back(LoadGraph("img/tikara.jpg")),
	overlay(LoadGraph("img/over.png")),
	count(0)
{}
effect::~effect()
{
	DeleteGraph(back);
	DeleteGraph(overlay);
}

void effect::graph()
{
	++count;
	DrawGraph(0,0,back,false);
	SetDrawBlendMode(DX_BLENDMODE_ADD,255);
	DrawRotaGraph2(320,240,370,370,1.0,PI2/240*count,overlay,true);
	DrawRotaGraph2(320,240,370,370,1.0,PI2/240*(count-120),overlay,true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	DeleteMaskScreen();
}