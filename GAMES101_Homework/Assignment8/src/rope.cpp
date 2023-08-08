#include <iostream>
#include <vector>

#include "CGL/vector2D.h"

#include "mass.h"
#include "rope.h"
#include "spring.h"

namespace CGL {

    Rope::Rope(Vector2D start, Vector2D end, int num_nodes, float node_mass, float k, vector<int> pinned_nodes)
    {
        // TODO (Part 1): Create a rope starting at `start`, ending at `end`, and containing `num_nodes` nodes.

//        Comment-in this part when you implement the constructor
//        for (auto &i : pinned_nodes) {
//            masses[i]->pinned = true;
//        }
        auto dir = (end - start) / (num_nodes - 1);
        for (auto i = 0; i < num_nodes; i++) {
            masses.push_back(new Mass(start + i * dir, node_mass, false));
        }
        for (auto i = 0; i < num_nodes - 1; i++) {
            this->springs.push_back(new Spring(masses[i], masses[i+1], k));
        }
        for (auto &i : pinned_nodes) {
            masses[i]->pinned = true;
        }
    }

    void Rope::simulateEuler(float delta_t, Vector2D gravity)
    {
        for (auto &s : springs)
        {
            // TODO (Part 2): Use Hooke's law to calculate the force on a node
            auto N1 = s->m1->position;
            auto N2 = s->m2->position;
            auto f = s->k * (N2 - N1).unit() * ((N2 - N1).norm() - s->rest_length);
            s->m1->forces += f;
            s->m2->forces += -f;

        }

        for (auto &m : masses)
        {
            if (!m->pinned)
            {
                // TODO (Part 2): Add the force due to gravity, then compute the new velocity and position
                m->velocity = m->velocity + ((m->forces) / m->mass + gravity) * delta_t;
                // semi-implicit
                m->position = m->position + m->velocity * delta_t;
                // TODO (Part 2): Add global damping
            }
            std::cout << m->position << std::endl;
            // Reset all forces on each mass
            m->forces = Vector2D(0, 0);
        }
    }

    void Rope::simulateVerlet(float delta_t, Vector2D gravity)
    {
        for (auto &s : springs)
        {
            // TODO (Part 3): Simulate one timestep of the rope using explicit Verlet （solving constraints)
            // auto m1ToM2 = s->m2->position - s->m1->position;
            // auto halfLength = (m1ToM2.norm() - s->rest_length)/2;
            // s->m1->position += halfLength * m1ToM2.unit();
            // s->m2->position += -halfLength * m1ToM2.unit();
            // s->m1->forces += {0,0};
            // s->m2->forces += {0,0};

            auto N1 = s->m1->position;
            auto N2 = s->m2->position;
            auto f = s->k * (N2 - N1).unit() * ((N2 - N1).norm() - s->rest_length);
            s->m1->forces += f;
            s->m2->forces += -f;
        }

        for (auto &m : masses)
        {
            if (!m->pinned)
            {
                Vector2D temp_position = m->position;
                // TODO (Part 3.1): Set the new position of the rope mass
                Vector2D last_position = m->last_position;
                double damping_factor = 0.00005;
                Vector2D new_position = temp_position + (1-damping_factor)*(temp_position - last_position) + (m->forces / m->mass + gravity)* delta_t * delta_t;

                m->last_position = temp_position;
                m->position = new_position;
                // TODO (Part 4): Add global Verlet damping
            }
            m->forces = Vector2D{0,0};
        }
    }
}


