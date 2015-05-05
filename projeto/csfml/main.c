#include <SFML/Audio.h>
#include <SFML/Graphics.h>

int main()
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow* window;
    sfTexture* texture;
    sfSprite* sprite;
    sfFont* font;
    sfText* text;
    sfMusic* music;
    sfEvent event;
    sfRectangleShape *rect;
    rect = sfRectangleShape_create();
    sfRectangleShape_setFillColor(rect, sfWhite);
    sfRectangleShape_setSize(rect, (sfVector2f){100, 50});

    /* Create the main window */
    window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    /* Load a sprite to display */
    texture = sfTexture_createFromFile("../resources/image.jpg", NULL);
    if (!texture)
        return 1;
    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);

    /* Create a graphical text to display */
    font = sfFont_createFromFile("../resources/inconsolata.otf");
    if (!font)
        return 1;
    text = sfText_create();
    sfText_setString(text, "Hello SFML");
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 50);


    /* Load a music to play */
    music = sfMusic_createFromFile("../resources/locked.ogg");
    if (!music)
        return 1;

    /* Play the music */
    sfMusic_play(music);

    int posx = 0;
    int posy = 0;
    /* Start the game loop */
    while (sfRenderWindow_isOpen(window))
    {

        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event))
        {
            /* Close window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            else{
                if(event.type == sfEvtKeyPressed){
                    switch(event.key.code){
                        case sfKeyUp:
                            posy -= 5; break;
                        case sfKeyDown:
                            posy += 5; break;
                    }
                }
            }

        }

        if(sfKeyboard_isKeyPressed(sfKeyLeft)){
            posx -= 5;
        }
        if(sfKeyboard_isKeyPressed(sfKeyRight)){
            posx += 5;
        }

        /* Clear the screen */
        sfRenderWindow_clear(window, sfWhite);

        /* Draw the sprite */
        sfRenderWindow_drawSprite(window, sprite, NULL);

        /* Draw the text */
        sfText_setPosition(text,(sfVector2f){posx, posy});
        sfRenderWindow_drawText(window, text, NULL);

        //Draw the rect
        sfRectangleShape_setPosition(rect,(sfVector2f){posx, posy + 200});
        sfRenderWindow_drawRectangleShape(window, rect, NULL);
        /* Update the window */
        sfRenderWindow_display(window);
    }

    /* Cleanup resources */
    sfMusic_destroy(music);
    sfText_destroy(text);
    sfFont_destroy(font);
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
    sfRectangleShape_destroy(rect);
    sfRenderWindow_destroy(window);

    return 0;
}
