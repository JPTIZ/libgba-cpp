#ifndef RESOURCES_MAPS_SAMPLE_H
#define RESOURCES_MAPS_SAMPLE_H

#include <array>

#include <engine/graphics/tilemap.h>
#include <engine/graphics/palette.h>

namespace resources::maps {

using gba::graphics::Color;
using gba::graphics::Tile;
using gba::graphics::Tileset;
using gba::graphics::Palette;

const std::array<Color, 53> raw_sample_palette = {
    Color
    { 0,  0,  0}, {31, 31, 18},
    {28, 28, 12}, {19, 26,  7},
    {25, 23, 24}, {22, 23, 14},
    {20, 19, 16}, {20, 20,  6},
    {17, 18,  7}, {22, 17, 10},
    {17, 16, 16}, {17, 15, 13},
    {13, 15,  6}, {14, 14,  6},
    {13, 14,  7}, {15, 12,  7},
    {13, 12,  9}, {10, 13,  5},
    {10, 12,  3}, { 8, 14, 16},
    {12, 11,  6}, {11, 10, 10},
    { 8, 10,  4}, {13,  9,  9},
    {11,  8,  4}, {11,  7,  7},
    {10,  7,  2}, { 8,  9,  2},
    { 6, 11, 13}, { 7,  9,  4},
    { 5,  8,  9}, { 5,  8,  3},
    { 6,  7,  3}, {31,  3, 31},
    {22,  4, 24}, { 7,  6,  6},
    { 7,  6,  1}, { 7,  5,  5},
    { 6,  5,  2}, { 6,  5,  1},
    { 5,  6,  7}, { 5,  5,  5},
    { 5,  5,  1}, { 5,  3,  2},
    { 4,  6,  4}, { 4,  5,  3},
    { 4,  5,  1}, { 2,  5,  4},
    { 3,  4,  5}, { 3,  4,  1},
    { 2,  3,  1}, { 1,  2,  3},
};

extern const std::array<Tile, 128> sample_tiles;

const Palette sample_palette{raw_sample_palette};
extern const Tileset sample_tileset;

}

#endif
