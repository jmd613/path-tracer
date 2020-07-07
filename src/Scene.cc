#include "Scene.h"

std::optional<HitRecord> Scene::Hit(const math::Ray &ray, double min_dist,
                             double max_dist) const
{
   std::optional<HitRecord> closest_hit{};
   for (const auto &obj : objects_)
   {
      if (auto hit = obj->Hit(ray, min_dist, max_dist); hit)
      {
         max_dist = hit->dist;   // maximum dist is now the distance of the hit
         closest_hit = hit;
      }
   }
   return closest_hit;
}
