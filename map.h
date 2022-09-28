// Map Class
#include "splashkit.h"
#include "tile.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
using namespace std;

#pragma once

class LevelOjectsMap
{
    protected:
        vector<vector<int> > map_array;
        int tile_size = 64;
        int map_width;
        int map_height;
        string type;

    public:
        LevelOjectsMap(){};

        ~LevelOjectsMap()
        {
            map_array.clear();
        };

        LevelOjectsMap(string level, int tile_size)
        {
            this->tile_size = tile_size;
            check_map_dimensions(level);
            this->map_array = new_level(level);
        };
            
        void check_map_dimensions(string file)
        {
            ifstream map_level;
            std::string line;
            int y_count = 0;
            int x_count = 0;

            map_level.open(file);

            if(map_level.fail())
            {
                write_line("Error");
                cerr << "Error Opening File" << endl;
                exit(1);
            }

            while(std::getline(map_level, line))
            {
                std::istringstream iss(line);

                int i;
                x_count = 0;
                
                while(iss >> i)
                {
                    x_count += 1;
                }
                y_count += 1;
            }

            map_level.close();

            this->map_height = y_count;
            this->map_width = x_count;
        };

        int get_map_width()
        {
            return this->map_width;
        };

        int get_map_height()
        {
            return this->map_height;
        };

        vector<vector<int> > new_level(string file)
        {
            // Initialise a 2D matrix of int to store level design  
            vector<vector<int> > map;

            // load in the level layout from file
            ifstream map_level;
            map_level.open(file);

            // Check for errors
            if(map_level.fail())
            {
                write_line("Error");
                cerr << "Error Opening File" << endl;
                exit(1);
            }

            // initialise a vector of strings to store each line of text
            vector<int> map_line;
            int temp;

            for (int i = 0; i < this->map_height; i++)
            {
                for (int j = 0; j < this->map_width; j++)
                {
                    map_level >> temp;
                    map_line.push_back(temp);
                }
                // pushback line
                map.push_back(map_line);
                map_level.ignore();
                map_line.clear();
            }
            map_level.close();
            return map;
        };

        vector<vector<Tile>> load_layer(vector<vector<Tile>> tiles, string type, bitmap cell_sheet, int offset)
        {
             for (int i = 0; i < this->map_height; i++)
                for (int j = 0; j < this->map_width; j++)
                {
                    if(this->map_array[i][j] > offset)
                    {
                        int cell = (this->map_array[i][j] - 1) - offset;
                        tiles[i][j].load_tile(this->map_array[i][j], cell, type, cell_sheet);
                    }
                }

            return tiles;
        };
};

