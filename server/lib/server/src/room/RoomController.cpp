#include "RoomController.hpp"

RoomController::RoomController() {}

RoomController::~RoomController() {}

bool RoomController::addSession(const std::shared_ptr<Session>& session) {}

void RoomController::removeSession(const std::shared_ptr<Session>& session) {}

std::uint64_t RoomController::createRoom(std::string name) {}

void RoomController::removeRoom(std::uint64_t roomId) {}

void RoomController::moveToRoom(std::uint64_t roomId, const std::shared_ptr<Session>& session) {}

void RoomController::moveFromRoom(std::uint64_t roomId, const std::shared_ptr<Session>& session) {}

std::vector<std::string> RoomController::getAllRooms() const {}

void RoomController::runGame(std::uint64_t roomId) {}

void RoomController::broadcast(const std::string& message, const Session* session) {}

void RoomController::clear() {}
