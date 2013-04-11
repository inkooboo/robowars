#include "xserver_writer.hpp"
#include "game_object.hpp"

#include <json.h>

std::string xserver_serialize_objects(game_object_set_t &objects)
{
    Json::Value jroot;
    Json::Value &jobjects = jroot["objects"];
    jobjects = Json::Value(Json::arrayValue);

    for (auto object : objects)
    {
        Json::Value next;
        next["id"] = (unsigned)object->id;
        next["type_id"] = object->type;
        next["owner"] = object->owner;
        next["pos_x"] = object->position.x;
        next["pos_y"] = object->position.y;
        next["pos_z"] = object->position.z;
        next["vel_x"] = object->speed.x;
        next["vel_y"] = object->speed.y;
        next["vel_z"] = object->speed.z;

        jobjects.append(next);
    }

    Json::FastWriter writer;

    return writer.write(jroot, "x");
}



