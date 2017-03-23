#include "ShaderImporter.hpp"
#include <Shader.hpp>

FishEngine::ShaderPtr FishEditor::ShaderImporter::Load()
{
	auto shader = FishEngine::Shader::CreateFromFile(m_assetPath);
	m_assetObject = shader;
	return shader;
}

