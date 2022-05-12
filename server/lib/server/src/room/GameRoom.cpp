#include "GameRoom.hpp"

GameRoom::GameRoom(std::uint64_t id, const std::string& name, std::uint64_t maxUserNum): Room(id, name, maxUserNum) {}

void GameRoom::runGame() {}
