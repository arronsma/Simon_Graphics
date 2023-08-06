//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"
#include <cassert>


void Scene::buildBVH() {
    printf(" - Generating BVH...\n\n");
    this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

Intersection Scene::intersect(const Ray &ray) const
{
    return this->bvh->Intersect(ray);
}

void Scene::sampleLight(Intersection &pos, float &pdf) const
{
    float emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
        }
    }
    float p = get_random_float() * emit_area_sum;
    emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
            if (p <= emit_area_sum){
                objects[k]->Sample(pos, pdf);
                break;
            }
        }
    }
}

bool Scene::trace(
        const Ray &ray,
        const std::vector<Object*> &objects,
        float &tNear, uint32_t &index, Object **hitObject)
{
    *hitObject = nullptr;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        float tNearK = kInfinity;
        uint32_t indexK;
        Vector2f uvK;
        if (objects[k]->intersect(ray, tNearK, indexK) && tNearK < tNear) {
            *hitObject = objects[k];
            tNear = tNearK;
            index = indexK;
        }
    }


    return (*hitObject != nullptr);
}

// Implementation of Path Tracing
Vector3f Scene::shade(const Intersection& p, const Vector3f& w0) const{
    Vector3f L_dir(0, 0, 0);
    Vector3f L_indir(0, 0, 0);
    
    Intersection res;
    float pdf_light;
    sampleLight(res, pdf_light);
    Vector3f x = res.coords; //light point
    Vector3f NN = res.normal; // normal of light point
    Vector3f lightDir = x - p.coords; // p to light x
    Vector3f ws = lightDir.normalized();
    Ray lightRay(p.coords + p.normal * EPSILON, ws);

    // there is no light type here!!! 
    // light is an object!!!
    auto point2light_intersect = intersect(lightRay);
    // assert(light_intersect.happened);
    if (point2light_intersect.happened && point2light_intersect.m->hasEmission())  {
        L_dir = point2light_intersect.emit * p.m->eval(w0, lightDir.normalized(), p.normal) * dotProduct(ws, p.normal) * dotProduct(-ws, NN) / pow(lightDir.norm(), 2) / pdf_light;
    }
    double rand_d = get_random_float();
    if (rand_d < RussianRoulette) {
        auto wi = p.m->sample(w0, p.normal);
        auto next_point_intersect = intersect({ p.coords, wi });
        if (next_point_intersect.happened && !next_point_intersect.m->hasEmission()) {
            auto recursiveRes = shade(next_point_intersect, wi);
            L_indir = recursiveRes * p.m->eval(w0, wi, p.normal) * dotProduct(wi, p.normal) / p.m->pdf(w0, wi, p.normal) / RussianRoulette;
        }
    }
    return L_dir + L_indir + p.m->getEmission();
}

Vector3f Scene::castRay(const Ray &ray, int depth) const
{
    Intersection obj_intersect = intersect(ray);
    if (!obj_intersect.happened) {
        return Vector3f{ 0.0,0.0,0.0 };
    }
    Vector3f w0 = ray.direction;
    Vector3f res = shade(obj_intersect, w0);
    return res;
}