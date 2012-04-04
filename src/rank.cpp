#include"rank.hpp"
#include<fstream>
#include<cassert>
#include<iterator>
#include<algorithm>
#include<vector>
#include<string>
#include<boost/lexical_cast.hpp>
#include<thread>
#include<chrono>

void Rank(menu& m)
{
	std::ifstream ifs("data/rank.dat");
	if(!ifs.is_open())assert(0);
	
	std::vector<std::string> ranking;
	std::string tmp;
	unsigned int i=0;
	
	while(std::getline(ifs,tmp)){
		ranking.push_back(boost::lexical_cast<std::string>(1+i)+="ˆÊ: ");
		ranking[i++]+=tmp;
	}
	ifs.close();
	
	int x=0,y=0;
	i=1;
	unsigned int Green=GetColor(255,255,0);

	while(!ScreenFlip()&&!ProcessMessage()&&!ClearDrawScreen()){
		m.effectiving();

		for(unsigned int i=1; i<ranking.size()*80; i+=80)
			DrawStringToHandle(x,y+i,ranking[i/80].c_str(),Green,m.font_Handle[2]);

		DrawStringToHandle(400,400,"Q: –ß‚é",Green,m.font_Handle[0]);
		if(CheckHitKey(KEY_INPUT_Q))break;
	}
}

void Rank(std::chrono::seconds s,menu& m)
{
	std::ifstream ifs("data/rank.dat");
	if(!ifs.is_open())assert(0);
	
	unsigned int second=static_cast<unsigned int>(s.count());
	bool new_lecord_flag=false;
	std::vector<std::string> ranking;
	unsigned int rank_new=0;

	std::copy(std::istream_iterator<std::string>(ifs),
				std::istream_iterator<std::string>(),
				std::back_inserter(ranking));
	ifs.close();

	if(ranking.end()!=std::upper_bound(ranking.begin(),ranking.end(),boost::lexical_cast<std::string>(second))&&
		!std::binary_search(ranking.begin(),ranking.end(),boost::lexical_cast<std::string>(second)))
		new_lecord_flag=true;


	if(new_lecord_flag){
		ranking.push_back(boost::lexical_cast<std::string>(second));
		std::sort(ranking.begin(),ranking.end());

		std::ofstream ofs("data/rank.dat");
		if(!ofs.is_open())assert(0);
		for(unsigned int i=0; i<ranking.size()-1; ++i)
			ofs<<ranking[i]<<std::endl;
		ofs.close();
		rank_new=std::lower_bound(ranking.begin(),ranking.end(),boost::lexical_cast<std::string>(second))-ranking.begin()+1;
	}

	int x=0,y=0;
	unsigned int Green=GetColor(255,255,0);
	unsigned int Red=GetColor(204,51,0);

	while(!ScreenFlip()&&!ProcessMessage()&&!ClearDrawScreen()){
		m.effectiving();
		DrawStringToHandle(400,400,"Q: –ß‚é",Green,m.font_Handle[0]);
		if(CheckHitKey(KEY_INPUT_Q))break;

		if(new_lecord_flag){
			unsigned int c=1;
			for(unsigned int i=0; i<ranking.size()*80-10; i+=80,++c){
				if(rank_new&&c==rank_new)
					DrawStringToHandle(x,y+i,
						(boost::lexical_cast<std::string>(c)+
						std::string("ˆÊ ")+
						ranking[i/80]).c_str(),
					Red,m.font_Handle[0]);
				else
					DrawStringToHandle(x,y+i,
						(boost::lexical_cast<std::string>(c)+
						std::string("ˆÊ ")+
						ranking[i/80]).c_str(),
					Green,m.font_Handle[0]);
			}
		}else{
			unsigned int c=1;
			for(unsigned int i=0; i<ranking.size()*80-10; i+=80,++c)
				DrawStringToHandle(x,y+i,
						(boost::lexical_cast<std::string>(c)+
						std::string("ˆÊ ")+
						ranking[i/80]).c_str(),
					Green,m.font_Handle[0]);
		}
	}
}