#include <SFML/Audio.h>
#include <SFML/Graphics.h>

sfRenderWindow* janela;
sfRectangleShape *rect;
sfText* text;
sfFont* font;
sfMusic *som;
int cell = 20;

int iniciar(int _cell, int sizeX, int sizeY);
void finalizar();

void drawRect(sfColor cor, float x, float y);
void drawText(const char * meutexto, float x, float y);
void playSound(const char * path);


int main()
{
    /* Create the main window */
    iniciar(50, 24, 16);

    int posx = 0;
    int posy = 0;

    /* Start the game loop */
    sfEvent event;
    while (sfRenderWindow_isOpen(janela))
    {
        /* Process events */
        while (sfRenderWindow_pollEvent(janela, &event))
        {
            /* Close window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(janela);

            if(event.type == sfEvtKeyPressed)
            {
                if(event.key.code == sfKeyUp){
                    posy -= 1;
                    playSound("../resources/saber.ogg");
                }
                if(event.key.code == sfKeyDown){
                    posy += 1;
                    playSound("../resources/dog.ogg");
                }
            }
        }

        /* Clear the screen */
        sfRenderWindow_clear(janela, sfBlack);

        /* Draw the text */
        drawRect(sfWhite, posx, posy);
        drawText("dog", posx, posy + 1);

        /* Update the window */
        sfRenderWindow_display(janela);
    }

    /* Cleanup resources */
    finalizar();
    return 0;
}










/*  FUNCOES GRAFICAS */

int iniciar(int _cell, int sizeX, int sizeY){
    cell = _cell;
    sfVideoMode mode = {cell * sizeX, cell * sizeY, 32};
    janela = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    if (!janela)
        return 0;

    font = sfFont_createFromFile("../resources/inconsolata.otf");
    if (!font)
        return 0;
    text = sfText_create();
    sfText_setFont(text, font);
    sfText_setColor(text, sfWhite);

    rect = sfRectangleShape_create();
    sfRectangleShape_setSize(rect, (sfVector2f){cell, cell});
    return 1;
}


void drawRect(sfColor cor, float x, float y){
    sfRectangleShape_setPosition(rect, (sfVector2f){x * cell, y * cell});
    sfRectangleShape_setFillColor(rect, cor);
    sfRenderWindow_drawRectangleShape(janela, rect, NULL);
}


void drawText(const char * meutexto, float x, float y){
    sfText_setString(text, meutexto);
    sfText_setCharacterSize(text, cell);
    sfText_setPosition(text, (sfVector2f){x * cell, y * cell});
    sfRenderWindow_drawText(janela, text, NULL);
}

void finalizar(){
    sfMusic_destroy(som);
    sfText_destroy(text);
    sfFont_destroy(font);
    sfRectangleShape_destroy(rect);
    sfRenderWindow_destroy(janela);
}

void playSound(const char * path){
    if(som != NULL)
        sfMusic_destroy(som);
    som = sfMusic_createFromFile(path);
    sfMusic_play(som);
}
