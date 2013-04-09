#include "field.hpp"
#include "game_object.hpp"
#include "xserver_writer.hpp"
#include <mutex>

field_t::field_t()
{
    // add test object
    game_object_ptr test = std::make_shared<game_object_t>();

//    test->ai = ;
    test->id = 0;
    test->type = "test_object";
    test->owner = "nobody";

    test->max_speed = 10.f;
    test->mass = 100.f;
    test->force = 1000.f;

    test->position = vector3();
    test->speed = vector3(0.1f, 0.f, 0.f);

    m_objects.insert(test);
}



void field_t::on_time_chunk(float dt_ms)
{
    float dt_s = dt_ms / 1000.f;

    {
        std::lock_guard<spinlock_t> lock(m_objects_guard);
        for (auto &object : m_objects)
        {
            // ai step
            //object->ai;

            // physics step
            object->position += object->speed*dt_s;
        }
    }

}

std::string field_t::xserver_field_dump()
{
    std::lock_guard<spinlock_t> lock(m_objects_guard);

    return xserver_serialize_objects(m_objects);
}

