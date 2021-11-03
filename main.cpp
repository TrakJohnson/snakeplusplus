#include <array>
#include <iostream>
#include <vector>
#include "sys/ioctl.h"

#include "stdlib.h"

#include "config.h"
#include "internals.h"
#include "display.h"
#include "food.h"


void backgroundSetup( const int nx, const int ny, std::vector<int>& bg){
    decltype(bg.size()) i;
    for( i=0; i<nx; i++){
        bg[i] = 1;
    }
    for( i=0; i<nx; i++){
        bg[(ny-1)*nx + i] = 1;
    }
    for( i=0; i<ny; i++){
        bg[i*nx] = 1;
    }
    for( i=0; i<ny; i++){
        bg[i*nx+nx-1] = 1;
    }
}



void add_snake(const std::vector<std::pair<int,int>>& snake, std::vector<int>& bg, const int& nx, const int& ny){
    
}

void remove_snake(const std::vector<std::pair<int,int>>& snake, std::vector<int>& bg, const int& nx, const int& ny){
    
}



std::array<int,2> snake_movement(const char& k ){
    std::array<int,2> dxdy;
    if(k=='d'||k=='6'){
        // Right                                                                      
        dxdy[0] = 1;
        dxdy[1] = 0;
    }else if(k=='q'||k=='4'){
        // Left                                                                       
        dxdy[0] = -1;
        dxdy[1] = 0;
    }else if(k=='s'||k=='2'){
        // Down                                                                        
        dxdy[0] = 0;
        dxdy[1] = 1;
    }else if(k=='z'||k=='8'){
        // Up                                                                      
        dxdy[0] = 0;
        dxdy[1] = -1;
    }
    return dxdy;
}



bool verifyBorder(const std::vector<std::pair<int,int> >& snake, int nx, int ny){
    
    
}


void setupSnake(std::vector<std::pair<int, int>>& snake, const int& init_size){
    for( int i=0; i<init_size; i++){
        snake.push_back( {10+i, 3} );
    }
}


void update_snake_coordinates(std::vector<std::pair<int, int>>& snake, const std::array<int,2> dxdy){
    
}

void startGame(const int& lap, const int& nx, const int& ny, std::vector<std::pair<int,int>>& snake, std::vector<int>& bg){
    char key;

    std::array<int, 2> dxdy {1, 0};
    std::array<int, 2> food {0, 0};

    createFood( bg, food, nx, ny );

    while( true ){
        internal::frameSleep(lap);
        if( internal::keyEvent() ){
            std::cin >> key; 
            dxdy = snake_movement(key);
        }
        backgroundClear();
        add_snake( snake, bg, nx, ny );
        printFrame(nx, ny, bg);
        remove_snake(snake, bg, nx, ny);
        bool out =  verifyBorder(snake, nx, ny);
        if( out == false){
            std::cerr << "" << std::endl;
            exit(1);
        }
        bool eat = eatFood(food, snake);
        if(eat){
            createFood(bg, food, nx, ny);
            snake.push_back({-1,-1});
        }
        update_snake_coordinates(snake, dxdy);
    }
}



int main(){
    const int snake_init_sz = 3;
    const int nx = 50;
    const int ny = 25;
    const int lap= 200;

    std::vector<int> background(nx*ny, -1);

    std::vector<std::pair<int, int> > snake;
    backgroundSetup(nx, ny, background);
    setupSnake(snake, snake_init_sz);
    
    startGame(lap, nx, ny,snake, background);
    return EXIT_SUCCESS;
}



