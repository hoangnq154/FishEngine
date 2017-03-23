#pragma once

#include "AssetImporter.hpp"
#include "Shader.hpp"

namespace FishEditor
{
	class ShaderImporter final : public AssetImporter
	{
	public:
		InjectClassName(ShaderImporter);

		ShaderImporter() = default;

		FishEngine::ShaderPtr GetShader()
		{
			return FishEngine::As<FishEngine::Shader>(m_assetObject);
		}

		FishEngine::ShaderPtr Load();
	};
}