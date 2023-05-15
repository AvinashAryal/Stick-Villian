#pragma once
#include"game.h"

void Game::Create()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    w = SDL_CreateWindow("Stick Villian",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,0);
    r = SDL_CreateRenderer(w,-1,0);
    score_font = TTF_OpenFont("font/font.otf",100);
    grow_sound = Mix_LoadWAV("Sounds/grow.wav");
    run_sound = Mix_LoadWAV("Sounds/run.wav");
    dead_sound = Mix_LoadWAV("Sounds/dead.wav");
    
    background_surf[0] = IMG_Load("Images/background1.jpg");
    background_surf[1] = IMG_Load("Images/background2.jpg");
    background_surf[2] = IMG_Load("Images/background3.jpg");
    background_surf[3] = IMG_Load("Images/background4.jpg");
    player_surf[0] = IMG_Load("Images/player1.png");
    player_surf[1] = IMG_Load("Images/player2.png");
    player_surf[2] = IMG_Load("Images/player3.png");
    player_surf[3] = IMG_Load("Images/player4.png");
    player_surf[4] = IMG_Load("Images/player5.png");
    band_surf[0] = IMG_Load("Images/band1.png");
    band_surf[1] = IMG_Load("Images/band2.png");
    band_surf[2] = IMG_Load("Images/band3.png");
    band_surf[3] = IMG_Load("Images/band4.png");
    startmenu_surf = IMG_Load("Images/startmenu.png");
    retrymenu_surf = IMG_Load("Images/RetryMenu.png");
    
    for(int i = 0;i<4;i++) background_tex[i] = SDL_CreateTextureFromSurface(r,background_surf[i]);
    for(int i = 0;i<5;i++) player_tex[i] = SDL_CreateTextureFromSurface(r,player_surf[i]);
    for(int i = 0;i<4;i++) band_tex[i] = SDL_CreateTextureFromSurface(r,band_surf[i]);
    startmenu_tex = SDL_CreateTextureFromSurface(r,startmenu_surf);
    retrymenu_tex = SDL_CreateTextureFromSurface(r,retrymenu_surf);
    SDL_FreeSurface(score_surf);
    SDL_FreeSurface(retry_surf);
    for(int i = 0;i<4;i++){
        SDL_FreeSurface(background_surf[i]);
        SDL_FreeSurface(band_surf[i]);
    }
    for(int i = 0;i<5;i++) SDL_FreeSurface(player_surf[i]);
    SDL_FreeSurface(startmenu_surf);
    SDL_FreeSurface(retrymenu_surf);
}

void Game::Set()
{
    isRunning = true;
    gameover = false;
    retry = false;
    start = false;
    newgame = false;
    grow = false;
    fall = false;
    gamestate = 1;
    img_index = 1;
    framecount = 0;
    score = 0;
    current.x = 0;
    current.y = 540;
    current.h = 180;
    current.w = 100;
    player.x = current.x + current.w - 40;
    player.y = 480;
    player.w = 35;
    player.h = 60;
    band.x = player.x - 10;
    band.y = player.y + 7;
    band.w = 16;
    band.h = 10;
    stick.w = 5;
    stick.h = 10;
    stick.x = player.x + 35;
    stick.y = 540 - stick.h;
    srand(time(NULL));
    num = rand()%4;
    target.w = 40 + ((rand()%8)*20);
    int temp1 = (current.x + current.w + 20);
    int temp2 = WIDTH - (current.x + current.w + 20) - target.w;
    target.x = temp1 + (rand()%(temp2/10))*10;
    target.h = 180;
    target.y = 540;
}

void Game::Update()
{
    srand(time(NULL));
    if(gamestate == 1)
    {
        if(grow) stick.h+=5;
        if(fall) gamestate = 2;
    }
    if(gamestate == 2)
    {
        int temp = stick.w; 
        stick.w = stick.h;
        stick.h = temp;
        gamestate = 3;
    }
    if(gamestate == 3) move = true;

    else move = false;
    if (move) player.x +=5;
    if((player.x == (stick.x+stick.w-35)) && (gamestate == 3))
    {
        gamestate = 4;
    }
    if((gamestate == 4) && (((stick.x+stick.w)<target.x)||((stick.x+stick.w)>(target.x+target.w))))
    {
        player.y +=5;
        gameover = true;
    }
    if(gamestate == 4 && !gameover)
    {
        gamestate = 5;
    }
    if(gamestate == 5)
    {
        current.w = target.w;
        current.x = 100-current.w;
        srand(time(NULL));
        target.w = 40 + ((rand()%8)*20);
        int temp1 = (current.x + current.w + 20);
        int temp2 = WIDTH - (current.x + current.w + 20) - target.w;
        target.x = temp1 + (rand()%(temp2/10))*10;
        player.x = current.x + current.w - 40;
        stick.h = 10;
        stick.w = 5;
        fall = false;
        grow = false;
        gamestate = 1;
        score += 1;
    }
    
    framecount++;
    if(framecount == 5)
    {
        framecount = 0;
        if(img_index == 4) img_index = 1;
        else img_index++;
    }

    if(player.y >= 720) retry = true;

    band.x = player.x-10;
    band.y = player.y+3;
    band.w = 16;
    band.h = 10;
    stick.x = current.x + current.w - 5;
    stick.y = 540 - stick.h;
    dead.x = player.x;
    dead.y = player.y;
    dead.w = player.h;
    dead.h = player.w;
}

void Game::DrawStartMenu()
{
    SDL_RenderClear(r);
    SDL_RenderCopy(r,startmenu_tex,NULL,&background);
    SDL_RenderPresent(r);
}


void Game::Run()
{
    SDL_RenderClear(r);

    score_str = std::to_string(score);
    retry_str = "YOUR SCORE:"+std::to_string(score);

    score_surf = TTF_RenderText_Solid(score_font,score_str.c_str(),text_color);
    retry_surf = TTF_RenderText_Solid(score_font,retry_str.c_str(),text_color);

    score_tex = SDL_CreateTextureFromSurface(r,score_surf);
    retry_tex = SDL_CreateTextureFromSurface(r,retry_surf);

    SDL_RenderCopy(r,background_tex[num],NULL,&background);
    if(!retry) SDL_RenderCopy(r,score_tex,NULL,&score_rect);
    if(newgame) SDL_RenderCopy(r,retry_tex,NULL,&retry_rect);
    if (gameover) SDL_RenderCopy(r,player_tex[4],NULL,&dead);
    else if(gamestate == 3) SDL_RenderCopy(r,player_tex[img_index-1],NULL,&player);
    else SDL_RenderCopy(r,player_tex[0],NULL,&player);
    SDL_RenderCopy(r,band_tex[img_index-1],NULL,&band);

    SDL_SetRenderDrawColor(r,0,0,0,255);
    SDL_RenderFillRect(r,&current);
    SDL_RenderFillRect(r,&target);
    SDL_RenderFillRect(r,&stick);
    SDL_SetRenderDrawColor(r,100,100,255,255);
	SDL_RenderPresent(r);
}

void Game::PlaySound()
{
    if(grow) Mix_PlayChannel(1,grow_sound,0);
    if(gamestate == 3) Mix_PlayChannel(2,run_sound,0);
    if(gameover){
	    Mix_PlayChannel(2,dead_sound,0);
	    gameover = false;
     }
}

bool Game::Stop()
{
	SDL_PollEvent(&e);
	switch(e.type)
	{
        case(SDL_KEYDOWN):
            {
            switch(e.key.keysym.scancode)
            {
            case(SDL_SCANCODE_UP):
            {
                if(gamestate == 1) 
                {
                    grow = true;
                }
                break;
            }
            break;
            }
            break;
            }   
        case(SDL_KEYUP):
            {
            switch(e.key.keysym.scancode)
            {
            case(SDL_SCANCODE_UP):
            {
                if(gamestate == 1)
                {
                    if(grow)
                    {
                        fall = true;
                        grow = false;
                    }
                }
                else break;
            }
            break;
            }   
            break;
            }
        case SDL_MOUSEBUTTONDOWN:
            {
                if(retry)
                {
                if(e.button.button == SDL_BUTTON_LEFT)
                {
                    if((e.button.x > 180 ) && (e.button.x < 440))
                    {
                        if((e.button.y > 350 ) && e.button.y < 460)
                        {
                            newgame = true;
                        }
                    }
                }
                }
                else
                {
                if(e.button.button == SDL_BUTTON_LEFT)
                {
                    if((e.button.x > 180 ) && (e.button.x < 440))
                    {
                        if((e.button.y > 350 ) && e.button.y < 460)
                        {
                            start = true;
                        }
                    }
                }
                }
                break;
            }
        case(SDL_QUIT):
            {
                isRunning = false;
                break;
            }
        break;
    }
    return !isRunning;
}

void Game::DrawRestartMenu()
{
    SDL_RenderClear(r);
    SDL_RenderCopy(r,retrymenu_tex,NULL,&background);
    SDL_RenderCopy(r,retry_tex,NULL,&retry_rect);
    SDL_RenderPresent(r);
}

void Game::Clear()
{
    SDL_DestroyWindow(w);
    SDL_DestroyRenderer(r);
    SDL_DestroyTexture(score_tex);
    SDL_DestroyTexture(retry_tex);
    for(int i = 0;i<4;i++) SDL_DestroyTexture(background_tex[i]);
    for(int i = 0;i<5;i++)SDL_DestroyTexture(player_tex[i]);
    for(int i = 0;i<4;i++)SDL_DestroyTexture(band_tex[i]);
    SDL_DestroyTexture(startmenu_tex);
    SDL_DestroyTexture(retrymenu_tex);
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}
