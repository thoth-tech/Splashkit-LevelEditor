#include "splashkit.h"

#pragma once
class Tile
{
    private:
        bitmap current_bitmap;
        string type;
        point_2d position;
        int value  = 0;
        drawing_options current_opts;
        rectangle border;
        int tile_size;

    public:
        Tile (bitmap initial_bitmap, point_2d position, int tile_size)
        {
            this->position = position;
            this->tile_size = tile_size;
            this->border = rectangle_from(this->position, this->tile_size, this->tile_size);
            this->current_bitmap = initial_bitmap;
            this->current_opts = option_defaults();
        };

        void draw_tile()
        {
            if(this->value > 0)
                draw_bitmap(current_bitmap, position.x, position.y, current_opts);
            
            draw_rectangle(COLOR_GREEN, border);
        };

        void check_input(int tile_selected, bitmap current_bitmap, int offset)
        {
            point_2d pt = mouse_position();
            point_2d camera = camera_position();

            pt.x = pt.x + camera.x;
            pt.y = pt.y + camera.y;

            update_tile(pt, tile_selected, offset, type, current_bitmap);
        };

        void update_tile(point_2d mouse_position, int tile_selected, int offset, string type, bitmap current_bitmap)
        {
            if(mouse_down(LEFT_BUTTON))
            {
                if(point_in_rectangle(mouse_position, this->border))
                {
                    this->current_bitmap = current_bitmap;
                    this->type = type;
                    this->value = tile_selected + offset;
                    this->current_opts.draw_cell = tile_selected - 1;
                }
            }
            
            if(mouse_down(RIGHT_BUTTON))
            {
                if(point_in_rectangle(mouse_position, this->border))
                {
                    this->current_opts.draw_cell = 0;
                    value = 0; 
                }
            }
        };

        void load_tile(int value, int tile_selected, string type, bitmap current_bitmap)
        {
            this->current_bitmap = current_bitmap;
            this->type = type;
            this->value = value;
            this->current_opts.draw_cell = tile_selected;
        }

        int get_value()
        {
            return this->value;
        };

        void set_type(string type)
        {
            this->type = type;
        }
};