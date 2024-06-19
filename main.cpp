#include <SDL.h>
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <vector>

#define TILE_SIZE 64



struct game_map_t {
    int width, height;
    std::vector<int> map;

    int get(int x, int y) const {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            return 1;
        }
        if (map[y * width + x] == 1 ||                       // Top-left corner
            map[y * width + (x + TILE_SIZE - 1) / TILE_SIZE] == 1 || // Top-right corner
            map[(y + TILE_SIZE - 1) / TILE_SIZE * width + x] == 1 || // Bottom-left corner
            map[(y + TILE_SIZE - 1) / TILE_SIZE * width + (x + TILE_SIZE - 1) / TILE_SIZE] == 1) { // Bottom-right corner
            return 1; // Collision detected
        }
        return 0; // No collision
    }
};

// New game map with multiple labyrinths going upwards
game_map_t game_map1 = {
        140, 15, { // Map width 30, height 15
                // Ground layer
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,0,0,0,0,0,1, 1, 1, 1, 1,1,1,1,1,1,1, 1, 1, 1, 1,1,1,1,1,1,1, 1, 1, 1, 1,1,1,1,1,1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,0,0,0,0,0,1, 1, 1, 1, 1,1,1,1,1,1,1, 1, 1, 1, 1,1,1,1,1,1,1, 1, 1, 1, 1,1,1,0,0,1,1
        }
};

game_map_t game_map2 = {
        30, 15, { // Map width 30, height 15
                // Ground layer
                0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        }
};


game_map_t current_map = game_map1;




std::shared_ptr<SDL_Texture> load_image(SDL_Renderer *renderer, const std::string &file_name) {
    SDL_Surface *surface;
    SDL_Texture *texture;
    surface = SDL_LoadBMP(file_name.c_str());
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
        throw std::invalid_argument(SDL_GetError());
    }
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 255));
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        throw std::invalid_argument(SDL_GetError());
    }
    SDL_FreeSurface(surface);
    return { texture, [](SDL_Texture *t) {
        SDL_DestroyTexture(t);
    } };
}

union vect_t {
    struct { double x; double y; } v;
    double p[2];
};

vect_t operator+(const vect_t a, const vect_t b) {
    vect_t ret = a;
    ret.v.x += b.v.x;
    ret.v.y += b.v.y;
    return ret;
}

vect_t operator*(const vect_t a, const double b) {
    vect_t ret = a;
    ret.v.x *= b;
    ret.v.y *= b;
    return ret;
}
struct camera_t {
    int x, y, width, height;
};

struct player_t {
    vect_t p; ///< position
    vect_t v; ///< velocity
    vect_t a; ///< acceleration
    int current_frame;
    double frame_time;
    std::vector<std::shared_ptr<SDL_Texture>> textures;
    bool is_jumping;
    bool facing;
    int health;
    bool is_attacking;
};

struct enemy_t {
    vect_t position;
    int health;
};

int enemy_health = 100;
vect_t enemy_position = {{10.0, 5.0}};

bool is_in_collision(vect_t pos, const game_map_t &map) {
    return map.get(pos.v.x, pos.v.y) > 0;
}

bool is_on_the_ground(player_t player, const game_map_t &map) {
    return map.get(player.p.v.x, player.p.v.y + 0.01) > 0;
}

player_t update_player(player_t player_old, const game_map_t &map, double dt,
                       std::shared_ptr<SDL_Texture> player_texture,
                       std::shared_ptr<SDL_Texture> move2_right,
                       std::shared_ptr<SDL_Texture> move3_texture,
                       std::shared_ptr<SDL_Texture> fight1_texture,
                       std::shared_ptr<SDL_Texture> fight2_texture) {
    player_t player = player_old;

    // Apply gravity only if the player is not on the ground
    if (!is_on_the_ground(player_old, map)) player_old.a.v.y = 10; // gravity

    player.p = player_old.p + (player_old.v * dt) + (player_old.a * dt * dt) * 0.5;
    player.v = player_old.v + (player_old.a * dt);
    player.v = player.v * 0.99;

    if (player.p.v.x < 0) {
        player.p.v.x = 0;
        player.v.v.x = 0;
    }

    if (player.p.v.y < 0) {
        player.p.v.y = 0;
        player.v.v.y = 0;
    }
    if (player.p.v.y > current_map.height - 1) {
        player.p.v.y = current_map.height - 1;
        player.v.v.y = 0;
    }

    std::vector<vect_t> collision_points = {
            {v:{-0.4, 0.0}},
            {v:{0.4, 0.0}}
    };
    std::vector<vect_t> collision_mods = {
            {v:{0.0, -1.0}},
            {v:{0.0, -1.0}}
    };
    bool should_apply_jump = false;

    for (int i = 0; i < collision_points.size(); i++) {
        auto test_point = player.p + collision_points[i];

        if (is_in_collision(test_point, map)) {
            if (collision_mods[i].v.y < 0) { // lift the player
                player.v.v.y = 0;
                player.p.v.y = player_old.p.v.y;
            }
        }
    }
    // Apply movement based on keyboard input
    if (player_old.a.v.x != 0) {
        player.v.v.x += player_old.a.v.x * dt; // apply acceleration to velocity
        player.facing = (player_old.a.v.x > 0); // set facing direction

        // Allow jumping forward
        if (should_apply_jump && is_on_the_ground(player_old, map)) {
            const double jump_speed = 8.0; // Adjust the jump speed as needed
            player.v.v.y = -jump_speed;

            // Adjust horizontal velocity based on movement direction
            if (player_old.a.v.x > 0) {
                player.v.v.x += jump_speed / 2; // Jump forward to the right
            } else if (player_old.a.v.x < 0) {
                player.v.v.x -= jump_speed / 2; // Jump forward to the left
            }
        }
    } else {
        // If no movement keys pressed, apply friction to slow down
        const double friction = 0.8;
        player.v.v.x *= friction;

        // Stop completely if speed is low enough to prevent drifting
        if (fabs(player.v.v.x) < 0.1) {
            player.v.v.x = 0;
        }
    }

    if (fabs(player.v.v.x) > 0.1) {
        player.frame_time += dt;
        if (player.frame_time >= 0.1) { // Adjust the value for speed of animation
            player.frame_time = 0;
            player.current_frame = (player.current_frame + 1) % 2; // Cycle through move frames (0 and 1)
        }
    } else if (is_on_the_ground(player, map)) {
        player.current_frame = 0; // Set to idle frame when not moving

    }

    if (player.is_attacking) {
        // If attacking, do not allow horizontal movement
        player.v.v.x = 0;
    } else {
        // Apply movement based on keyboard input
        if (player_old.a.v.x != 0) {
            player.v.v.x += player_old.a.v.x * dt; // apply acceleration to velocity
            player.facing = (player_old.a.v.x > 0); // set facing direction
        } else {
            // If no movement keys pressed, apply friction to slow down
            const double friction = 0.8;
            player.v.v.x *= friction;

            // Stop completely if speed is low enough to prevent drifting
            if (fabs(player.v.v.x) < 0.1) {
                player.v.v.x = 0;
            }
        }
    }

    return player;
}



void update_camera(camera_t &camera, const player_t &player, const game_map_t &map) {
    // Margines, który pozwala graczowi przemieszczać się bez ruszania kamery
    int margin_x = camera.width / 2;
    int margin_y = camera.height / 2;

    // Oblicz docelową pozycję kamery, uwzględniając margines
    int target_x = static_cast<int>(player.p.v.x * TILE_SIZE - margin_x);
    int target_y = static_cast<int>(player.p.v.y * TILE_SIZE - margin_y);

    // Ogranicz kamery do granic mapy
    if (target_x < 0) target_x = 0;
    if (target_y < 0) target_y = 0;
    if (target_x > map.width * TILE_SIZE - camera.width) target_x = map.width * TILE_SIZE - camera.width;
    if (target_y > map.height * TILE_SIZE - camera.height) target_y = map.height * TILE_SIZE - camera.height;

    // Współczynnik intensywnej interpolacji liniowej
    const float interpolation_factor = 0.2f; // Możesz dostosować wartość w zakresie 0 do 1

    // Zastosuj intensywną interpolację liniową do płynnego poruszania kamery
    camera.x = static_cast<int>(camera.x + interpolation_factor * (target_x - camera.x));
    camera.y = static_cast<int>(camera.y + interpolation_factor * (target_y - camera.y));
}









void draw_map(SDL_Renderer *renderer, const game_map_t &map, const camera_t &camera, std::shared_ptr<SDL_Texture> tex) {
    // Ustal widoczne granice na podstawie pozycji kamery
    int startX = camera.x / TILE_SIZE;
    int startY = camera.y / TILE_SIZE;
    int endX = (camera.x + camera.width) / TILE_SIZE;
    int endY = (camera.y + camera.height) / TILE_SIZE;

    // Upewnij się, że granice są w zakresie mapy
    if (startX < 0) startX = 0;
    if (startY < 0) startY = 0;
    if (endX >= map.width) endX = map.width - 1;
    if (endY >= map.height) endY = map.height - 1;

    // Renderuj tylko widoczne kafelki
    for (int y = startY; y <= endY; y++) {
        for (int x = startX; x <= endX; x++) {
            SDL_Rect dst = { x * TILE_SIZE - camera.x, y * TILE_SIZE - camera.y, TILE_SIZE, TILE_SIZE };
            if (map.get(x, y) > 0) {
                SDL_Rect src = { 128 * (map.get(x, y) - 1), 0, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, tex.get(), &src, &dst);
            }
        }
    }
}





void handle_combat(player_t &player,
                   std::shared_ptr<SDL_Texture> player_texture,
                   std::shared_ptr<SDL_Texture> move2_texture,
                   std::shared_ptr<SDL_Texture> move3_texture,
                   std::shared_ptr<SDL_Texture> fight1_texture,
                   std::shared_ptr<SDL_Texture> fight2_texture) {
    // Attack logic triggered by pressing space
    if (player.is_attacking) {
        // Check if attack collides with enemy (simplified check within 0.5 units)
        // For single player game, assume enemy's position or any other collision logic
        // For simplicity, we'll just simulate an attack here
        if (fabs(player.p.v.x - enemy_position.v.x) < 0.5 &&
            fabs(player.p.v.y - enemy_position.v.y) < 0.5) {
            // Damage to enemy (change as needed)
            // For example, decrease enemy's health
            enemy_health -= 10;

            // Change player's animation to show attack frames
            player.textures = {player_texture, fight1_texture, fight2_texture};
            // Set player's current frame to the first attack frame
            player.current_frame = 1;

            // End player's attack animation after a duration (simulate here)
            // You can implement a timer or use frame counting logic to control animation duration
            // Here, we'll reset attack state after a short duration (simulation)
            player.is_attacking = false;
        }
    }

    // Restore default textures if not attacking
    if (!player.is_attacking) {
        if (player.a.v.x != 0) {
            player.textures = {player_texture, move2_texture, move3_texture};
        } else {
            player.textures = {player_texture};
        }
    }
}




int main(int argc, char *argv[]) {
    using namespace std::chrono_literals;
    using namespace std::chrono;
    using namespace std;
    SDL_Window *window;
    SDL_Renderer *renderer;

    int initial_window_width = 640; // Szerokość okna przy starcie aplikacji
    int initial_window_height = 480; // Wysokość okna przy starcie aplikacji




    double dt = 1. / 60.;



    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }

    if (SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return 3;
    }


    auto player_texture = load_image(renderer, "hero_right.bmp");
    auto tiles_texture = load_image(renderer, "tile1.bmp");
    auto background_texture = load_image(renderer, "gamebck.bmp");

    auto move2_texture = load_image(renderer, "move2_right.bmp");
    auto move3_texture = load_image(renderer, "move3_right.bmp");

    auto fight1_texture = load_image(renderer, "fight1.bmp");
    auto fight2_texture = load_image(renderer, "fight2.bmp");

    bool still_playing = true;
    player_t player;
    player.p.v.x = 1;
    player.p.v.y = 1;
    player.a.v.x = 0;
    player.a.v.y = 0;
    player.v.v.x = 0;
    player.v.v.y = 0;
    player.current_frame = 0;
    player.frame_time = 0;
    player.is_jumping = false;
    player.facing = true;
    player.health = 100;
    player.is_attacking = false;

    player.textures.push_back(player_texture);
    player.textures.push_back(move2_texture);
    player.textures.push_back(move3_texture);

    camera_t camera;
    camera.width = 640;
    camera.height = 480;

    double game_time = 0.;
    steady_clock::time_point current_time = steady_clock::now();

    while (still_playing) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    still_playing = false;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        // Pobierz nowe wymiary okna
                        int new_width, new_height;
                        SDL_GetWindowSize(window, &new_width, &new_height);

                        // Uaktualnij kamery na podstawie zmiany rozmiaru okna
                        double width_ratio = static_cast<double>(new_width) / initial_window_width;
                        double height_ratio = static_cast<double>(new_height) / initial_window_height;

                        camera.x *= width_ratio;
                        camera.y *= height_ratio;
                        camera.width = new_width;
                        camera.height = new_height;

                        // Zaktualizuj również początkowe wymiary okna
                        initial_window_width = new_width;
                        initial_window_height = new_height;

                        // Dodatkowo, uaktualnij kamerę w funkcji update_camera
                        update_camera(camera, player, current_map);
                    }
                    break;


                case SDL_KEYDOWN:
                    if (is_on_the_ground(player, current_map)) {
                        if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                            player.a.v.y = -500;
                            player.is_jumping = true;
                        }
                        if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                            player.a.v.x = -5;
                            player.facing = false;
                        }
                        if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                            player.a.v.x = 5;
                            player.facing = true;
                        }
                        if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                            player.is_attacking = true;
                        }
                    }
                    break;
                case SDL_KEYUP:
                    if (event.key.keysym.scancode == SDL_SCANCODE_Q) still_playing = false;
                    if (event.key.keysym.scancode == SDL_SCANCODE_UP) player.a.v.y = 0;
                    if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) player.a.v.x = 0;
                    if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) player.a.v.x = 0;
                    break;


            }
        }
        if (player.p.v.x > current_map.width) {
            current_map = game_map2; // Przełącz na mapę 2 przy przekroczeniu prawej granicy mapy 1
            player.p.v.x = 0; // Zresetuj pozycję gracza
        } else if (player.p.v.x < 0) {
            current_map = game_map1; // Przełącz z powrotem na mapę 1 przy przekroczeniu lewej granicy mapy 2
            player.p.v.x = current_map.width - 1; // Zresetuj pozycję gracza
        }

        game_time += dt;

        player = update_player(player, current_map, dt, player_texture, move2_texture, move3_texture, fight1_texture, fight2_texture);


        if (!is_on_the_ground(player, current_map)) {
            player.is_jumping = true;
        } else {
            player.is_jumping = false;
        }

        if (player.is_jumping) {
            player.current_frame = 1; // Jumping frame
        } else if (player.a.v.x != 0) {
            player.frame_time += dt;
            if (player.frame_time >= 0.1) {
                player.current_frame = (player.current_frame + 1) % 2 + 1; // Walking frames
                player.frame_time = 0;
            }
        } else {
            player.current_frame = 0; // Idle frame
        }

        update_camera(camera, player, current_map);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_texture.get(), NULL, NULL);

        draw_map(renderer, current_map, camera, tiles_texture);


        SDL_Rect player_rect = { (int)(player.p.v.x * TILE_SIZE - (TILE_SIZE / 2)), (int)(player.p.v.y * TILE_SIZE - TILE_SIZE), 64, 128 };

        SDL_RendererFlip flip = player.facing ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(renderer, player.textures[player.current_frame].get(), NULL, &player_rect, 0, NULL, flip);

        // Display health bars
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect health_bar = { 10, 10, player.health * 2, 20 };
        SDL_RenderFillRect(renderer, &health_bar);

        SDL_RenderPresent(renderer);

        current_time = current_time + microseconds((long long int)(dt * 1000000.0));
        std::this_thread::sleep_for(16ms);

        if (player.health <= 0) {
            still_playing = false;
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "You Lose!", window);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
