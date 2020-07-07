#pragma once

#include <vector>

#include "IHittable.h"

class Scene : public IHittable
{
public:
   Scene() = default;

   void add(std::unique_ptr<IHittable> hittable)
   {
      objects_.push_back(std::move(hittable));
   }

   std::optional<HitRecord> Hit(const math::Ray &ray, double min_dist,
                                double max_dist) const override;

private:
   std::vector<std::unique_ptr<IHittable>> objects_;
};