#pragma once

#define WIDTH 640
#define HEIGHT 720

#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>
#include<cstdlib>
#include<ctime>
#include<string>

class Game
{
	bool isRunning,start,retry,newgame,grow,gameover,fall,move;
	int gamestate;//1 = rest, 2 = growing stick, 3 = falling stick, 4 = running player, 5 = moving platforms
	int img_index;
	int framecount;
	int score,num; 
	std::string score_str;
	std::string retry_str;
	SDL_Window *w;
	SDL_Renderer *r;
	SDL_Event e;
	SDL_Rect player,dead,current,target,cherry,stick,band;
	SDL_Rect score_rect = {300,0,40,40};
	SDL_Rect retry_rect = {220,0,200,60};
	SDL_Rect background = {0,0,640,720};
	SDL_Color text_color = {255,0,0,255};
	SDL_Surface *score_surf,*retry_surf,*background_surf[4],*player_surf[5],*band_surf[4],*startmenu_surf,*retrymenu_surf;
	SDL_Texture *score_tex,*retry_tex,*background_tex[4],*player_tex[5],*band_tex[4],*startmenu_tex,*retrymenu_tex;
	TTF_Font *score_font;
	Mix_Chunk *grow_sound,*run_sound,*dead_sound;


	public:
	void DrawStartMenu();
	bool StartGame()
	{
		return start;
	}
	void Create();
	void Set();
	void Update();
	void PlaySound();
	void Run();
	bool Stop();
	bool RestartGame()
	{
		return retry;
	}
	void DrawRestartMenu();
	bool NewGame()
	{
		return newgame;
	}
	//void Reset();
	void Clear();
};

