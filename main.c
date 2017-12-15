#include "math.h"
#include <stdbool.h>
#include <stdlib.h>
#include "config.h"
#include "SDL.h"
#include "liste.h"
#include "sprite.h"
#include "SDL_ttf.h"
//#include "SDL_mixer.h"


/* MAIN */

int main(int argc, char* argv[])
{
  SDL_Surface *screen, *background, *temp = NULL, *temp1 = NULL;
  SDL_Event event;
  SDL_Rect rcBackground;
  int colorkey, i, j, gameover;
  int level = 1;
  float angle;
  sprite_list_t liste_requin1= NULL, liste_requin2= NULL;
  sprite_t heros = NULL;
  sprite_t requin1, requin2;
  bool test = NULL, test5 = false, test6 = false, test7 = false, test8 = false, test9 = false;
  SDL_Color couleurBlanc = {255, 255, 255, 255};
  float taille_heros_x = 32.25;
  /*  Mix_Music aval;
      Mix_Music boss;
      Mix_Music game;*/
  unsigned int coll_bulle = 0;
  unsigned int coll_petit = 0;
  unsigned int coll_magicarpe = 0;
  unsigned int vie_du_boss = 0;

  /* INITIALISATION SDL */
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  TTF_Font *police = TTF_OpenFont("Images/flic.ttf",300);
  SDL_Surface *texte1 = TTF_RenderText_Solid(police,"GAMEOVER",couleurBlanc);
  SDL_Surface *texte2 = TTF_RenderText_Solid(police,"YOU WON",couleurBlanc);
  SDL_Surface *menu = TTF_RenderText_Solid(police,"Press P to Play",couleurBlanc);

  /* BARRE DE TITRE */
  SDL_WM_SetCaption("SHARKY", "SHARKY");
  
  /* CREATION DE LA FENETRE */
  screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  
  /* set keyboard repeat */
  SDL_EnableKeyRepeat(5, 5);
  
  /* CHARGEMENT ARRIERE PLAN */
  temp  = SDL_LoadBMP(BACKGROUND);
  background = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  
  /* CHARGEMENT DU PERSONNAGE */
  heros = new_sprite(PERSONNAGE1, screen);
  sprite_t  p2 = new_sprite(PERSONNAGE2, screen);
  sprite_t  p3 = new_sprite(PERSONNAGE3, screen);
  sprite_t  p4 = new_sprite(PERSONNAGE4, screen);
  sprite_t  p5 = new_sprite(PERSONNAGE5, screen);

  /* CHARGEMENT DE LA BULLE */
  char fname1[1024];
  sprintf(fname1, BULLE);
  sprite_t bulle = new_sprite(fname1, screen);
  bulle->angle = 0;
  bulle->coordo_perso.x = 50;
  bulle->coordo_perso.y = SCREEN_HEIGHT;
  bulle->x = bulle->coordo_perso.x;
  bulle->y = bulle->coordo_perso.y;
  bulle->pos_perso.x = 0;
  bulle->pos_perso.y = 0;
  bulle->pos_perso.w = 40;
  bulle->pos_perso.h = 43;
  
  
  /* CHARGEMENT PETIT POISSON */
  char fname5[1024];
  sprintf(fname5, PETIT);
  sprite_t petit = new_sprite(fname5, screen);
  
  petit->angle = 0;
 
  petit->coordo_perso.x = (rand()%SCREEN_WIDTH) ;
  petit->coordo_perso.y = (rand()%SCREEN_HEIGHT);
  
  petit->x = petit->coordo_perso.x;
  petit->y = petit->coordo_perso.y;
  
  petit->pos_perso.x = 0;
  petit->pos_perso.y = 0;
  petit->pos_perso.w = 40;
  petit->pos_perso.h = 30;
  
  
  /* CHARGEMENT DE MAGICARPE */
  char fname6[1024];
  sprintf(fname6, MAGICARPE);
  sprite_t magicarpe = new_sprite(fname6, screen);
  
  magicarpe->angle = 0;
  
  magicarpe->coordo_perso.x = (rand()%SCREEN_WIDTH) ;
  magicarpe->coordo_perso.y = (rand()%SCREEN_HEIGHT);
  
  magicarpe->x = magicarpe->coordo_perso.x;
  magicarpe->y = magicarpe->coordo_perso.y;
  
  magicarpe->pos_perso.x = 0;
  magicarpe->pos_perso.y = 0;
  magicarpe->pos_perso.w = 80;
  magicarpe->pos_perso.h = 80;
  
  
  /* CHARGEMENT DES REQUIN1 */
  for (i = 0 ; i < 3 ; i++)
    {
      char fname3[1024];
      sprintf(fname3, REQUIN1);
      sprite_t requin1 = new_sprite(fname3, screen);
      
      requin1->angle = 180;
      
      requin1->coordo_perso.x = rand_a_b(0,1200) ;
      requin1->coordo_perso.y = rand_a_b(0,900);
      
      requin1->x = requin1->coordo_perso.x;
      requin1->y = requin1->coordo_perso.y;
      
      requin1->pos_perso.x = 0;
      requin1->pos_perso.y = 0;
      requin1->pos_perso.w = 168;
      requin1->pos_perso.h = 142;
      
      liste_requin1 = cons_liste(requin1, liste_requin1);
    }
  
  /* CHARGEMENT DES REQUIN2 */
  for (i = 0 ; i < 2 ; i++)
    {
      char fname4[1024];
      sprintf(fname4, REQUIN2);
      sprite_t requin2 = new_sprite(fname4, screen);
      
      requin2->angle = 0;
      
      requin2->coordo_perso.x = rand_a_b(0,1200) ;
      requin2->coordo_perso.y = rand_a_b(200,500);
      
      requin2->x = requin2->coordo_perso.x;
      requin2->y = requin2->coordo_perso.y;
      
      requin2->pos_perso.x = 0;
      requin2->pos_perso.y = 0;
      requin2->pos_perso.w = 150;
      requin2->pos_perso.h = 134;
      
      
      liste_requin2 = cons_liste(requin2, liste_requin2);
    }
  

  /* CHARGEMENT DU BOSS */
  char fname7[1024];
  sprintf(fname7, BOSS);
  sprite_t boss = new_sprite(fname7, screen);
  boss->angle = 0;
  boss->coordo_perso.x = 50;
  boss->coordo_perso.y = SCREEN_HEIGHT;
  boss->x = bulle->coordo_perso.x;
  boss->y = bulle->coordo_perso.y;
  boss->pos_perso.x = 0;
  boss->pos_perso.y = 0;
  boss->pos_perso.w = 450;
  boss->pos_perso.h = 450;
  
  int menu1 = 1;
  gameover = 0;
  int fini = 0;
  int victoire = 0;

  while (!gameover)
    { 
  
      void HandleEvent(SDL_Event event)
      {
      /* QUITTER LE JEU AVEC LE CLAVIER */
	switch (event.key.keysym.sym) 
	  {
	  case SDLK_ESCAPE:
	  case SDLK_q:
	    gameover = 1;
	    break;
	  }
	
	Uint8 *move = SDL_GetKeyState(NULL);
	
	if (move[SDLK_LEFT])
	  {   
	    heros->pos_perso.x = 0;
	    heros->coordo_perso.x = heros->coordo_perso.x - 15;
	  }
	if (move[SDLK_RIGHT])
	  {
	    heros->pos_perso.x = (taille_heros_x);
	    heros->coordo_perso.x = heros->coordo_perso.x + 15;
	  }
	if (move[SDLK_UP]) 
	  {
	    heros->coordo_perso.y = heros->coordo_perso.y  - 15;
	  }
	if (move[SDLK_DOWN])
	  {
	    heros->coordo_perso.y = heros->coordo_perso.y + 15;
	  }
      }
      
      
      /* look for an event */
      if (SDL_PollEvent(&event))
	{
	  HandleEvent(event);
	}
      
      /* DESSINER ARRIERE PLAN */
      SDL_BlitSurface(background, NULL, screen, NULL);
      
      /* DESSINER LE PERSONNAGE */
      SDL_BlitSurface(heros->bmp, &heros->pos_perso, screen, &heros->coordo_perso);
      
      /* CHUTE DU PERSONNAGE */
      heros->coordo_perso.y = heros->coordo_perso.y + 1;
      
      
      /* COLLISION PERSONNAGE AVEC L'ÉCRAN */ 
      if (heros->coordo_perso.x < 0)
	heros->coordo_perso.x = heros->coordo_perso.x;
      
      if (heros->coordo_perso.x >=  SCREEN_WIDTH - TAILLE_HEROS_X)
	heros->coordo_perso.x = SCREEN_WIDTH - TAILLE_HEROS_X;
      
      if (heros->coordo_perso.y < 0)
	heros->coordo_perso.y= heros->coordo_perso.y;
      
      if (heros->coordo_perso.y >= SCREEN_HEIGHT - TAILLE_HEROS_Y)
	heros->coordo_perso.y = SCREEN_HEIGHT - TAILLE_HEROS_Y;
      
      
      /* DESSINER LA BULLE */ 
      if(!coll_bulle)
	{
	  SDL_BlitSurface(bulle->bmp, &bulle->pos_perso, screen, &bulle->coordo_perso);
	  bulle->coordo_perso.y = bulle->coordo_perso.y - 5;
	  if (bulle->coordo_perso.y < 0)
	    bulle->coordo_perso.y= SCREEN_HEIGHT - 43;
	  if (bulle->coordo_perso.y > SCREEN_HEIGHT - 43) 
	    bulle->coordo_perso.y = 0;
	}
      
      /* DESSINER LE PETIT POISSON */
      if(!coll_petit)
	{
	  SDL_BlitSurface(petit->bmp, &petit->pos_perso, screen, &petit->coordo_perso);
	  petit->coordo_perso.x = petit->coordo_perso.x + 8*cos(petit->angle);
	  petit->coordo_perso.y = petit->coordo_perso.y + 8*cos(petit->angle);
	  
	  if (petit->coordo_perso.y < 0)
	    petit->coordo_perso.y= SCREEN_HEIGHT - 30;
	  if (petit->coordo_perso.y > SCREEN_HEIGHT - 30) 
	    petit->coordo_perso.y = 0;
	  if (petit->coordo_perso.x < 0)
	    petit->coordo_perso.x= SCREEN_WIDTH - 40;
	  if (petit->coordo_perso.x > SCREEN_WIDTH - 40) 
	    petit->coordo_perso.x = 0;
	}
      
      /* DESSINER MAGICARPE */
      if(!coll_magicarpe)
	{
	  SDL_BlitSurface(magicarpe->bmp, &magicarpe->pos_perso, screen, &magicarpe->coordo_perso);
	  magicarpe->coordo_perso.x = magicarpe->coordo_perso.x - 2*cos(magicarpe->angle);
	  magicarpe->coordo_perso.y = magicarpe->coordo_perso.y - 2*cos(magicarpe->angle);
	  
	  if (magicarpe->coordo_perso.y < 0)
	    magicarpe->coordo_perso.y= SCREEN_HEIGHT - 80;
	  if (magicarpe->coordo_perso.y > SCREEN_HEIGHT - 80) 
	    magicarpe->coordo_perso.y = 0;
	  if (magicarpe->coordo_perso.x < 0)
	    magicarpe->coordo_perso.x= SCREEN_WIDTH - 80;
	  if (magicarpe->coordo_perso.x > SCREEN_WIDTH - 80) 
	    magicarpe->coordo_perso.x = 0;
	}
      
      /* DESSINER LA LISTE DES REQUINS1 */
      sprite_list_t tmp_liste_requin1 = liste_requin1;
      while (tmp_liste_requin1 != NULL)
	{
	  tmp_liste_requin1->tete->x = tmp_liste_requin1->tete->x  + 9*cos(tmp_liste_requin1->tete->angle);
	  tmp_liste_requin1->tete->y = tmp_liste_requin1->tete->y + 0*cos(tmp_liste_requin1->tete->angle);
	  
	  tmp_liste_requin1->tete->coordo_perso.x = (int)tmp_liste_requin1->tete->x;
	  tmp_liste_requin1->tete->coordo_perso.y = (int)tmp_liste_requin1->tete->y;
	  SDL_BlitSurface(tmp_liste_requin1->tete->bmp, &(tmp_liste_requin1->tete->pos_perso), screen, &(tmp_liste_requin1->tete->coordo_perso));
	  
	  /* COLLISION DES REQUIN1 AVEC LES COTÉS DE L'ÉCRAN */
	  
	  if (tmp_liste_requin1->tete->x > SCREEN_WIDTH - 168)
	    tmp_liste_requin1->tete->x = 0;
	  
	  if (tmp_liste_requin1->tete->x < 0)
	    tmp_liste_requin1->tete->x = SCREEN_WIDTH - 168;
	  
	  if (tmp_liste_requin1->tete->y > SCREEN_HEIGHT - 142)
	    tmp_liste_requin1->tete->y = 0;
	  
	  if (tmp_liste_requin1->tete->y < 0)
	    tmp_liste_requin1->tete->y = SCREEN_HEIGHT - 142;
	  
	  tmp_liste_requin1 = tmp_liste_requin1->reste;
	}
      
      
      /* DESSINER LA LISTE DES REQUIN2 */
      sprite_list_t tmp_liste_requin2 = liste_requin2;
      while (tmp_liste_requin2 != NULL)
	{
	  tmp_liste_requin2->tete->x = tmp_liste_requin2->tete->x  + 7*cos(tmp_liste_requin2->tete->angle);
	  tmp_liste_requin2->tete->y = tmp_liste_requin2->tete->y + 0*cos(tmp_liste_requin2->tete->angle);
	  
	  tmp_liste_requin2->tete->coordo_perso.x = (int)tmp_liste_requin2->tete->x;
	  tmp_liste_requin2->tete->coordo_perso.y = (int)tmp_liste_requin2->tete->y;
	  SDL_BlitSurface(tmp_liste_requin2->tete->bmp, &(tmp_liste_requin2->tete->pos_perso), screen, &(tmp_liste_requin2->tete->coordo_perso));
	  
	  /* COLLISION DES REQUIN2 AVEC LES COTÉS DE L'ÉCRAN */
	  
	  if (tmp_liste_requin2->tete->x > SCREEN_WIDTH - 150)
	    tmp_liste_requin2->tete->x = 0;
	  
	  if (tmp_liste_requin2->tete->x < 0)
	    tmp_liste_requin2->tete->x = SCREEN_WIDTH - 150;
	  
	  if (tmp_liste_requin2->tete->y > SCREEN_HEIGHT - 134)
	    tmp_liste_requin2->tete->y = 0;
	  
	  if (tmp_liste_requin2->tete->y < 0)
	    tmp_liste_requin2->tete->y = SCREEN_HEIGHT - 134;
	  
	  tmp_liste_requin2 = tmp_liste_requin2->reste;
	}
      
      
      /*  COLLISION DE LA BULLE AVEC LE PERSONNAGE */
      if(collision(heros,bulle))
	{
	  free_sprite(bulle);
	  coll_bulle = 1;
	  heros = p2;
	  taille_heros_x = 62.4;
	  level = 2;
	  printf("level: %u \n",level);
	  test5 = true;
	}  
      
      /* COLLISION DU PETIT POISSON AVEC LE PERSONNAGE */

      if(!test6 && test5 && collision(heros,petit))
	{
	  free_sprite(petit);
	  coll_petit = 1;
	  heros = p3;
	  taille_heros_x = 93.75;
	  level = 3;
	  printf("level: %u \n",level);
	  test6 = true;
	}
	
      /* COLLISION DE MAGICARPE AVEC LE PERSONNAGE */

      if(!test7 && test6 && collision(heros,magicarpe))
	{
	  free_sprite(magicarpe);
	  coll_magicarpe = 1;
	  heros = p4;
	  taille_heros_x = 125;
	  level = 4;
	  printf("level: %u \n",level);
	  test7 = true;
	}
      else{
	if (collision(heros, magicarpe))
	  {
	    printf("GAMEOVER\n");
	    fini = 1;
	    free_sprite(heros);
	  }
      }
      
    
      /* COLLISION DES REQUIN1 AVEC LE PERSONNAGE1 */
      sprite_list_t tmp_liste_de_requin1 = liste_requin1;
      while (tmp_liste_de_requin1 != NULL) 
	{
	  if (!test7)
	    {
	      if ( collision(heros,tmp_liste_de_requin1->tete))
		{
		  printf("GAMEOVER\n");
		  fini = 1;
		  free_sprite(heros);
		}
	      tmp_liste_de_requin1 = tmp_liste_de_requin1->reste;
	    }
	
	  else{
	    if (collision(heros,tmp_liste_de_requin1->tete))
	      {
		sprite_list_remove(&liste_requin1, tmp_liste_de_requin1->tete);
		level = level+1;
		printf("level: %d\n",level);
	      }
	    tmp_liste_de_requin1 = tmp_liste_de_requin1->reste; 
	  }

	}
    

      /* COLLISION DES REQUIN2 AVEC LE PERSONNAGE1 */
      sprite_list_t tmp_liste_de_requin2 = liste_requin2;
      while (tmp_liste_de_requin2 != NULL) 
	{
	  if (!test7)
	    {
	      if (collision(heros,tmp_liste_de_requin2->tete)) 
		{
		  printf("GAMEOVER\n");
		  fini = 1;
		  free_sprite(heros);
		}
	      tmp_liste_de_requin2 = tmp_liste_de_requin2->reste;
	    }
	  else{
	    if (collision(heros,tmp_liste_de_requin2->tete))
	      {
		sprite_list_remove(&liste_requin2, tmp_liste_de_requin2->tete);
		level = level + 1;
		printf("level: %d\n",level);
	      }
	    tmp_liste_de_requin2 = tmp_liste_de_requin2->reste; 
	  }

	}
      
      /* BOSS DE FIN */
      if (level == 9)
	{
	  heros = p5;
	  taille_heros_x = 156.25;
	  SDL_BlitSurface(boss->bmp, &boss->pos_perso, screen, &boss->coordo_perso);
	  boss->coordo_perso.x = boss->coordo_perso.x - 2*cos(boss->angle);
	  boss->coordo_perso.y = boss->coordo_perso.y - 2*cos(boss->angle);
	  
	  if (boss->coordo_perso.y < 0)
	    boss->coordo_perso.y= SCREEN_HEIGHT - 80;
	  if (boss->coordo_perso.y > SCREEN_HEIGHT - 80) 
	    boss->coordo_perso.y = 0;
	  if (boss->coordo_perso.x < 0)
	    boss->coordo_perso.x= SCREEN_WIDTH - 80;
	  if (boss->coordo_perso.x > SCREEN_WIDTH - 80) 
	    boss->coordo_perso.x = 0;
	 
	  /* COLLISION ENTRE LE BOSS ET LE HEROS */
	  if (collision(heros,boss))
	    {
	      free_sprite(boss);
	      victoire = 1;
	    }
                       
	}

      if (victoire)
	{
	  SDL_Rect pos_texte2;
	  pos_texte2.x = 100;
	  pos_texte2.y= SCREEN_HEIGHT / 2;
	  SDL_BlitSurface(texte2,NULL,screen,&pos_texte2);
	}
      
      if (fini)
	{
	  SDL_Rect pos_texte1;
	  pos_texte1.x = 100;
	  pos_texte1.y= SCREEN_HEIGHT /2;
	  SDL_BlitSurface(texte1,NULL,screen,&pos_texte1);
	}
      
      /* update the screen */
      SDL_UpdateRect(screen, 0, 0, 0, 0);
      SDL_Delay(25);
	
    }
  /* CLEAN UP */
  SDL_FreeSurface(background);
  TTF_Quit();
  SDL_Quit();
  return 0;
    
}
