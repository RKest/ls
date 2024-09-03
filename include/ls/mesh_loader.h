#pragma once

#include "ls/ext/obj_loader.h"
#include "ls/mesh.h"

#include <filesystem>

#define STATIC_IF(CONDITION, THEN, ELSE)                                                           \
    [&]                                                                                            \
    {                                                                                              \
        if constexpr (CONDITION)                                                                   \
            return THEN;                                                                           \
        else                                                                                       \
            return ELSE;                                                                           \
    }()

namespace ls
{
    struct MeshLoader
    {
        template<mesh_mods::MeshMods Mods> static auto loadObj(std::filesystem::path path) -> Mesh
        {
            OBJModel model(path);
            auto indexed_model = model.ToIndexedModel();
            if (indexed_model.normals.empty())
            {
                indexed_model.CalcNormals();
            }
            MeshArgs args{indexed_model.positions, indexed_model.indices};
            const auto& args2 = STATIC_IF(Mods & mesh_mods::Texture,
                                          args.withTextures(indexed_model.texCoords), args);
            return Mesh{args2};
        }
    };
} // namespace ls

#undef STATIC_IF