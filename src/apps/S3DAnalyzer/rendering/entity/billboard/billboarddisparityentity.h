#ifndef RENDERING_ENTITY_BILLBOARD_BILLBOARDINTENSITYENTITY_H
#define RENDERING_ENTITY_BILLBOARD_BILLBOARDINTENSITYENTITY_H

#include "billboardentity.h"

#include <Eigen/Dense>

class BillboardDisparityEntity : public BillboardEntity {
 public:
  explicit BillboardDisparityEntity(const QSize& imageSize);

  void setPoints(const std::vector<Eigen::Vector2f>& points, const std::vector<float>& intensities);
  void setMinIntensity(float value);
  void setMaxIntensity(float value);

  void addShaders() override;
  void setDefaultAttributeBuffers() override;
  void setDefaultUniforms() override;

 private:
  virtual std::vector<Vertex> verticesFromPoints(const std::vector<Eigen::Vector2f>& points,
                                                 const std::vector<float>& intensities);
};

#endif  // RENDERING_ENTITY_BILLBOARD_BILLBOARDINTENSITYENTITY_H
