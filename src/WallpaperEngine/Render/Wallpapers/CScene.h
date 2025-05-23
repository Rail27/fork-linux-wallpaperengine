#pragma once

#include "WallpaperEngine/Render/CCamera.h"

#include "WallpaperEngine/Core/Wallpapers/CScene.h"

#include "WallpaperEngine/Render/CWallpaper.h"

namespace WallpaperEngine::Render {
class CCamera;
class CObject;
}

namespace WallpaperEngine::Render::Wallpapers {
class CScene final : public CWallpaper {
  public:
    CScene (
        std::shared_ptr<const Core::CWallpaper> wallpaper, CRenderContext& context, CAudioContext& audioContext,
        const CWallpaperState::TextureUVsScaling& scalingMode,
        const WallpaperEngine::Assets::ITexture::TextureFlags& clampMode);

    [[nodiscard]] CCamera* getCamera () const;

    [[nodiscard]] const Core::Wallpapers::CScene* getScene () const;

    [[nodiscard]] int getWidth () const override;
    [[nodiscard]] int getHeight () const override;

    glm::vec2* getMousePosition ();
    glm::vec2* getMousePositionLast ();
    glm::vec2* getParallaxDisplacement ();

    [[nodiscard]] const std::vector<CObject*>& getObjectsByRenderOrder () const;

  protected:
    void renderFrame (glm::ivec4 viewport) override;
    void updateMouse (glm::ivec4 viewport);

    friend class CWallpaper;

  private:
    Render::CObject* createObject (const Core::CObject* object);

    CCamera* m_camera = nullptr;
    CObject* m_bloomObject = nullptr;
    std::map<int, CObject*> m_objects = {};
    std::vector<CObject*> m_objectsByRenderOrder = {};
    glm::vec2 m_mousePosition = {};
    glm::vec2 m_mousePositionLast = {};
    glm::vec2 m_parallaxDisplacement = {};
    std::shared_ptr<const CFBO> _rt_4FrameBuffer = nullptr;
    std::shared_ptr<const CFBO> _rt_8FrameBuffer = nullptr;
    std::shared_ptr<const CFBO> _rt_Bloom = nullptr;
};
} // namespace WallpaperEngine::Render::Wallpaper
