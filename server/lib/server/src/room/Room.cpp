#include "Room.hpp"

Room::Room() {}

Room::~Room() {}

void Room::addSession(const std::shared_ptr<Session>& session) {}

void Room::removeSession(const Session* session) {}

void Room::broadcast(const std::string& message, const Session* session) {}

void Room::clear() {}
