#include "mf_font.h"
#include <stdbool.h>

uint8_t mf_render_character(const struct mf_font_s *font,
                            int16_t x0, int16_t y0,
                            mf_char character,
                            mf_pixel_callback_t callback,
                            void *state)
{
    uint8_t width;
    width = font->render_character(font, x0, y0, character, callback, state);
    
    if (!width)
    {
        width = font->render_character(font, x0, y0, font->fallback_character,
                                       callback, state);
    }
    
    return width;
}

uint8_t mf_character_width(const struct mf_font_s *font,
                           mf_char character)
{
    uint8_t width;
    width = font->character_width(font, character);
    
    if (!width)
    {
        width = font->character_width(font, font->fallback_character);
    }
    
    return width;
}

/* Avoids a dependency on libc */
static bool strequals(const char *a, const char *b)
{
    while (*a)
    {
        if (*a++ != *b++)
            return false;
    }
    return (!*b);
}

const struct mf_font_s *mf_find_font(const char *name,
                                     const struct mf_font_list_s *fonts)
{
    const struct mf_font_list_s *f;
    f = fonts;
    
    while (f)
    {
        if (strequals(f->font->full_name, name) ||
            strequals(f->font->short_name, name))
        {
            return f->font;
        }
        
        f = f->next;
    }
    
    return 0;
}

