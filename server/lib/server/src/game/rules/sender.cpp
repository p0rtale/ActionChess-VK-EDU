
std::string Timeout_Move(int id, Tile tile)
{
	rapidjson::Document document;
	document.SetObject();
	auto& allocator = document.GetAllocator();

	rapidjson::Value val;
	rapidjson::Value data(rapidjson::kObjectType);
	rapidjson::Value arr(rapidjson::kArrayType);

	std::string typeName = "listen-figure";
	val.SetString(typeName.c_str(), allocator);
	document.AddMember("type", val, allocator);
	document.AddMember("status", 0, allocator);

	val.SetInt(id);
	data.AddMember("id", val, allocator);
	arr.PushBack(tile.row, allocator);
	arr.PushBack(tile.column, allocator);
	data.AddMember("pos", arr, allocator);
	document.AddMember("data", data, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);

	return buffer.GetString();
}

std::string Delete_Figure(int id)
{
	rapidjson::Document document;
	document.SetObject();
	auto& allocator = document.GetAllocator();

	rapidjson::Value val;
	rapidjson::Value data(rapidjson::kObjectType);
	rapidjson::Value arr(rapidjson::kArrayType);

	std::string typeName = "delete-figure";
	val.SetString(typeName.c_str(), allocator);
	document.AddMember("type", val, allocator);
	document.AddMember("status", 0, allocator);

	val.SetInt(id);
	data.AddMember("id", val, allocator);
	document.AddMember("data", data, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);

	return buffer.GetString();
}

std::string Game_Over(char color)
{
	rapidjson::Document document;
	document.SetObject();
	auto& allocator = document.GetAllocator();

	rapidjson::Value val;
	rapidjson::Value data(rapidjson::kObjectType);
	rapidjson::Value arr(rapidjson::kArrayType);

	std::string typeName = "game-over";
	val.SetString(typeName.c_str(), allocator);
	document.AddMember("type", val, allocator);
	document.AddMember("status", 0, allocator);

	std::string winner(1, color);
	val.SetString(winner.c_str(), allocator);
	data.AddMember("color", val, allocator);
	document.AddMember("data", data, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);

	return buffer.GetString();
}
