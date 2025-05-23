#pragma once

#include "WallpaperEngine/Core/Core.h"

namespace WallpaperEngine::Core::Objects::Particles {
using json = nlohmann::json;

/**
 * Control point for particles
 */
class CControlPoint {
  public:
    static const CControlPoint* fromJSON (const json& data);

    /**
     * @return The id of the controlpoint used for ordering purposes
     */
    [[nodiscard]] uint32_t getId () const;
    /**
     * @return The offset from origin
     */
    [[nodiscard]] const glm::vec3& getOffset () const;
    /**
     * @return Flags for the control point, controls how it should behave
     */
    [[nodiscard]] uint32_t getFlags () const;

  protected:
    explicit CControlPoint (uint32_t id, uint32_t flags, glm::vec3 offset);

  private:
    /** ID used for ordering purposes */
    const uint32_t m_id;
    /** Flags that control how it behaves */
    const uint32_t m_flags;
    /** The offset from starting position */
    const glm::vec3 m_offset;
};
} // namespace WallpaperEngine::Core::Objects::Particles
