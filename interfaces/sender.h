#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <string>
#include <tile.h>

std::string Timeout_Move(int id, Tile tile);
std::string Delete_Figure(int id);
std::string Game_Over(char color);