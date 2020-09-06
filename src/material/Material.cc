#include "Material.h"

#include <cmath>

#include "IHittable.h"
#include "Util.h"

math::Vec3 _RandomLambertianVec()
{
   double a = math::RandomDouble(0, 2 * M_PI);
   double z = math::RandomDouble(-1, 1);
   double r = sqrt(1 - z * z);

   return {r * cos(a), r * sin(a), z};
}

std::optional<std::pair<math::Ray, math::Vec3>> Lambertian::Scatter(
   const math::Ray &ray, const HitRecord &record) const
{
   auto direction = math::Vec3{record.normal + _RandomLambertianVec()};
   auto scattered = math::Ray{record.point, direction};
   return {{scattered, albedo_}};
}

std::optional<std::pair<math::Ray, math::Vec3>> Metal::Scatter(
   const math::Ray &ray, const HitRecord &record) const
{
   auto reflected =
      math::ReflectAcrossNormal(ray.GetDirection(), record.normal);
   auto scattered =
      math::Ray{record.point, reflected + fuzz_ * math::RandomInUnitSphere()};

   if (scattered.GetDirection().Dot(record.normal) < 0) return {};
   return {{scattered, albedo_}};
}