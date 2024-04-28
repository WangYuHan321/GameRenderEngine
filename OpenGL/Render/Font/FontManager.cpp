#include "FontManager.h"
#include<filesystem>
#include "../Mesh/Mesh.h"
#include "../Shader/Texture.h"
#include "../Mesh/Model.h"
#include "../../File/ConfigManager.h"
#include "../../File/Path/PathParser.h"
#include "../../Global/ServiceLocator.h"
#include "../../Editor/Core/EditorAction.h"
#include "../../Render/Resource/RawShader.h"
#include "../../Render/Resource/Loader/ShaderLoader.h"
#include "../../Core/ECS/Components/CTextMeshPro.h"
#include "../../Core/ECS/Components/CModelRenderer.h"
#include "../../Core/ECS/Components/CMaterialRenderer.h"

#define ASCII_TAB       9
#define ASCII_NEW_LINE  10
#define ASCII_SPACE     32

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
	ShaderLoader::getInstance()->Destroy(m_fontShader);
}

void FontManager::Initialize()
{
	auto fontShader = RawShader::GetFont();
	m_fontShader = ShaderLoader::getInstance()->CreateFromSource("Font Shader", fontShader.first, fontShader.second);
	m_fontMaterial.SetShader(m_fontShader);
	m_fontMaterial.Blend = true;
	m_fontMaterial.Cull = false;
}

Model* FontManager::GenerateModelByFontData(std::vector<Font::Character*> characterInfo)
{
	int offset_x = 0;
	int index = 0;

	std::vector<Vector3> vertexPos;
	std::vector<Vector2> vertexUV;
	std::vector<unsigned int> indexVector;

	for (int i= 0; i< characterInfo.size(); i++)
	{
		//vertexPos.push_back({ -1.0f + offset_x, 2.0f, 1.0f });
		//vertexPos.push_back({ 1.0f + offset_x, 2.0f, 1.0f });
		//vertexPos.push_back({ 1.0f + offset_x,  4.0f, 1.0f });
		//vertexPos.push_back({ -1.0f + offset_x,  4.0f, 1.0f });

		vertexPos.push_back({ 0.0f + offset_x, 0.0f, 0.0f });
		vertexPos.push_back({ 1.0f + offset_x, 0.0f, 0.0f });
		vertexPos.push_back({ 1.0f + offset_x,  1.0f, 0.0f });
		vertexPos.push_back({ 0.0f + offset_x,  1.0f, 0.0f });

		vertexUV.push_back({ characterInfo[i]->left_top_x_, characterInfo[i]->right_bottom_y_ });
		vertexUV.push_back({ characterInfo[i]->right_bottom_x_, characterInfo[i]->right_bottom_y_ });
		vertexUV.push_back({ characterInfo[i]->right_bottom_x_, characterInfo[i]->left_top_y_ });
		vertexUV.push_back({ characterInfo[i]->left_top_x_, characterInfo[i]->left_top_y_ });

		indexVector.push_back(0 + i * 4);
		indexVector.push_back(1 + i * 4);
		indexVector.push_back(2 + i * 4);
		indexVector.push_back(0 + i * 4);
		indexVector.push_back(2 + i * 4);
		indexVector.push_back(3 + i * 4);

		offset_x += 1;
	}

	Mesh* pMesh = new Mesh(vertexPos, vertexUV, indexVector);
	Model* pModel = new Model();

	pMesh->Finalize();
	pMesh->MaterialIndex = 0;

	std::vector<Mesh*> meshes;
	meshes.emplace_back(pMesh);
	pModel->m_meshes = meshes;

	return pModel;
}

void FontManager::ModifyFontStr(Actor& p_actor)
{
	if (auto textComp = p_actor.GetComponent<CTextMeshPro>(); textComp)
	{
		if (textComp->GetTTFFile() == "")
			return;
		Font* font = Font::LoadFromFile(ConfigManager::getInstance()->GetFontPath() + "/" + textComp->GetTTFFile(), textComp->GetFontSize());
		std::vector<Font::Character*> character_vec = font->LoadStr(textComp->GetContent());

		m_fontMaterial.SetTextureValue("font_texture", font->font_texture());

		auto* modelRenderer = p_actor.GetComponent<CModelRenderer>();
		auto* materialRenderer = p_actor.GetComponent<CMaterialRenderer>();

		delete modelRenderer->GetModel(); //delte model deconstruct mesh

		modelRenderer->SetModel(GenerateModelByFontData(character_vec));
		materialRenderer->FillWithMaterial(m_fontMaterial);
	}
}

void FontManager::CreateFontActor()
{
	Actor& pActor = GLOBALSERVICE(EditorAction).CreateEmptyActor();
	auto& textComp = pActor.AddComponent<CTextMeshPro>();
	auto& modelRenderer = pActor.AddComponent<CModelRenderer>();
	auto& materialRenderer = pActor.AddComponent<CMaterialRenderer>();

	if (auto textComp = pActor.GetComponent<CTextMeshPro>(); textComp)
	{
		if (textComp->GetTTFFile() == "")
			return;
		Font* font = Font::LoadFromFile(ConfigManager::getInstance()->GetFontPath() + "/" + textComp->GetTTFFile(), textComp->GetFontSize());
		std::vector<Font::Character*> character_vec = font->LoadStr(textComp->GetContent());

		m_fontMaterial.SetTextureValue("font_texture", font->font_texture());

		auto& modelRenderer = pActor.AddComponent<CModelRenderer>();
		auto& materialRenderer = pActor.AddComponent<CMaterialRenderer>();

		modelRenderer.SetModel(GenerateModelByFontData(character_vec));
		materialRenderer.FillWithMaterial(m_fontMaterial);
	}
}

//void FontManager::ModifyFontStr(Actor& p_actor)
//{
//	for (auto item : p_actor.GetChildren())
//	{
//		item->SetActive(false);
//	}
//
//	if (auto textComp = p_actor.GetComponent<CTextMeshPro>(); textComp)
//	{
//
//		//遍历每个字符进行绘制
//		int offset_x = 0;
//
//		if (textComp->GetTTFFile() == "")
//			return;
//		Font* font = Font::LoadFromFile(ConfigManager::getInstance()->GetFontPath() + "/" + textComp->GetTTFFile(), textComp->GetFontSize());
//		std::vector<Font::Character*> character_vec = font->LoadStr(textComp->GetContent());
//
//		for (auto character : character_vec)
//		{
//			offset_x += 2;
//			//因为FreeType生成的bitmap是上下颠倒的，所以这里UV坐标也要做对应翻转，将左上角作为零点。
//			std::vector<Vector3> vertexPos =
//			{
//				{ -1.0f + offset_x, 2.0f, 1.0f},
//				{ 1.0f + offset_x, 2.0f, 1.0f },
//				{ 1.0f + offset_x,  4.0f, 1.0f },
//				{ -1.0f + offset_x,  4.0f, 1.0f },
//			};
//
//			std::vector<Vector2> vertexUV =
//			{
//				{character->left_top_x_, character->right_bottom_y_},
//				{character->right_bottom_x_, character->right_bottom_y_},
//				{character->right_bottom_x_, character->left_top_y_},
//				{character->left_top_x_, character->left_top_y_}
//
//			};
//
//			std::vector<unsigned int> indexVector =
//			{
//				0,1,2,
//				0,2,3
//			};
//
//			Mesh* pMesh = new Mesh(vertexPos, vertexUV, indexVector);
//			pMesh->Finalize();
//			pMesh->MaterialIndex = 0;
//
//			m_fontMaterial.SetTextureValue("font_texture", font->font_texture());
//
//			Actor& pActor = GLOBALSERVICE(EditorAction).CreateEmptyActor(false, &p_actor, std::to_string(character->ch_font_));
//
//			auto& modelRenderer = pActor.AddComponent<CModelRenderer>();
//			auto& materialRenderer = pActor.AddComponent<CMaterialRenderer>();
//
//			Model* pModel = new Model();
//			std::vector<Mesh*> meshes;
//			meshes.emplace_back(pMesh);
//			pModel->m_meshes = meshes;
//
//			modelRenderer.SetModel(pModel);
//			materialRenderer.FillWithMaterial(m_fontMaterial);
//		}
//	}
//}
//
//void FontManager::CreateFontActor()
//{
//	Actor& pRootActor = GLOBALSERVICE(EditorAction).CreateEmptyActor();
//	auto& textComp = pRootActor.AddComponent<CTextMeshPro>();
//
//	//生成文字贴图
//	Font* font = Font::LoadFromFile(ConfigManager::getInstance()->GetFontPath() + "/SIMLI.ttf", 100);
//	std::vector<Font::Character*> character_vec = font->LoadStr(textComp.GetContent());
//
//	//遍历每个字符进行绘制
//	int offset_x = 0;
//	for (auto character : character_vec)
//	{
//		offset_x += 2;
//		//因为FreeType生成的bitmap是上下颠倒的，所以这里UV坐标也要做对应翻转，将左上角作为零点。
//		std::vector<Vector3> vertexPos =
//		{
//			{ -1.0f + offset_x, 2.0f, 1.0f},
//			{ 1.0f + offset_x, 2.0f, 1.0f },
//			{ 1.0f + offset_x,  4.0f, 1.0f },
//			{ -1.0f + offset_x,  4.0f, 1.0f },
//		};
//
//		std::vector<Vector2> vertexUV =
//		{
//			{character->left_top_x_, character->right_bottom_y_},
//			{character->right_bottom_x_, character->right_bottom_y_},
//			{character->right_bottom_x_, character->left_top_y_},
//			{character->left_top_x_, character->left_top_y_}
//
//		};
//
//		std::vector<unsigned int> indexVector =
//		{
//			0,1,2,
//			0,2,3
//		};
//
//		Mesh* pMesh = new Mesh(vertexPos, vertexUV, indexVector);
//		pMesh->Finalize();
//		pMesh->MaterialIndex = 0;
//
//		m_fontMaterial.SetTextureValue("font_texture", font->font_texture());
//
//		Actor& pActor = GLOBALSERVICE(EditorAction).CreateEmptyActor(false, &pRootActor, textComp.GetContent());
//
//		auto& modelRenderer = pActor.AddComponent<CModelRenderer>();
//		auto& materialRenderer = pActor.AddComponent<CMaterialRenderer>();
//
//		Model* pModel = new Model();
//		std::vector<Mesh*> meshes;
//		meshes.emplace_back(pMesh);
//		pModel->m_meshes = meshes;
//
//		modelRenderer.SetModel(pModel);
//		materialRenderer.FillWithMaterial(m_fontMaterial);
//
//	}
//}

//void FontManager::LoadAllFontList()
//{
//	FT_Error error;
//	std::vector<std::string> fontFileList;
//
//	std::string fontDir = ConfigManager::getInstance()->GetFontPath();
//
//	std::filesystem::path path(fontDir);
//	for (const auto& entry : std::filesystem::directory_iterator(path))
//	{
//		if (!entry.is_directory())
//		{
//			if (PathParser::getInstance()->GetFileType(entry.path().string()) == EFileType::FONT)
//			{
//				// 加载字体
//				FT_Face face;
//				error = FT_New_Face(m_library, entry.path().string().c_str(), 0, &face);
//				if (error == FT_Err_Unknown_File_Format)
//				{
//					LOG_ERROR("error : the font file could be opened and read, its font format is unsupported");
//				}
//				else if (error)
//				{
//					LOG_ERROR("error : the font file could not be opened or read, or that it is broken");
//				}
//				else
//				{
//					std::string fileNameNoSuffix = PathParser::getInstance()->GetFileNameByPath(entry.path().string());
//					m_fontList[fileNameNoSuffix] = Font::LoadFromFile(entry.path().string(), 100);
//				}
//			}
//		}
//	}
//
//}











































//Actor& FontManager::ConvertToActor()
//{
//
//	m_fontMaterial.SetShader(GLOBALSERVICE(EditorResource).GetShader("Font"));
//	m_fontMaterial.SetVector("font_color", Vector4(1.f, 1.f, 1.f, 1.f));
//
//	Actor& pActor = GLOBALSERVICE(EditorAction).CreateEmptyActor();
//
//	auto& modelRenderer = pActor.AddComponent<CModelRenderer>();
//	auto& materialRenderer = pActor.AddComponent<CMaterialRenderer>();
//
//	Model* pModel  = new Model();
//
//	std::vector<Mesh*> meshes;
//
//	for (auto it : m_fontMesh)
//		meshes.push_back(&it.second);
//
//	pModel->m_meshes = meshes;
//
//	modelRenderer.SetModel(pModel);
//	materialRenderer.FillWithMaterial(m_fontMaterial);
//
//	return pActor;
//}
//
//void FontManager::ExtraceTexture(std::string p_string, FT_Face& p_face)
//{
//	for (auto text_char : p_string)
//	{
//		FT_UInt charIndex = FT_Get_Char_Index(p_face, wchar_t(text_char));
//		FT_Error error = FT_Load_Glyph(p_face, charIndex, FT_LOAD_DEFAULT);
//		if (error)
//		{
//			LOG_ERROR("error : an error occurs when trying to load the corresponding glgyh image");
//			return ;
//		}
//
//		error = FT_Render_Glyph(p_face->glyph, FT_RENDER_MODE_NORMAL);
//		if (error)
//		{
//			LOG_ERROR("error : an error occurs when trying to render glyph");
//			return ;
//		}
//
//		FT_Glyph glyph;
//		error = FT_Get_Glyph(p_face->glyph, &glyph);
//		if (error)
//		{
//			LOG_ERROR("error : get glyph error");
//			return ;
//		}
//
//		//convert glyph to bitmap with 256 gray   
//		FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
//		FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
//		FT_Bitmap& bitmap = bitmap_glyph->bitmap;
//
//		Texture texture;
//		texture.Generate(m_font.m_width, m_font.m_height, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, bitmap_glyph->bitmap.buffer);
//
//		m_fontBmp[text_char] = texture;
//
//		FT_Done_Glyph(glyph);
//	}
//}
//
//void FontManager::ExtraceMesh(std::string p_string, FT_Face& p_face)
//{
//	Vector2 pen = Vector3(0.0f);
//	int offset_x = 0;
//	for (auto text_char : p_string)
//	{
//		offset_x += 2;
//
//		FT_UInt charIndex = FT_Get_Char_Index(p_face, wchar_t(m_font.m_currentStr.c_str()));
//		FT_Error error = FT_Load_Glyph(p_face, charIndex, FT_LOAD_DEFAULT);
//		if (error)
//		{
//			LOG_ERROR("error : an error occurs when trying to load the corresponding glgyh image");
//			return ;
//		}
//
//		error = FT_Render_Glyph(p_face->glyph, FT_RENDER_MODE_NORMAL);
//		if (error)
//		{
//			LOG_ERROR("error : an error occurs when trying to render glyph");
//			return ;
//		}
//
//		FT_Glyph glyph;
//		error = FT_Get_Glyph(p_face->glyph, &glyph);
//		if (error)
//		{
//			LOG_ERROR("error : get glyph error");
//			return ;
//		}
//
//		//convert glyph to bitmap with 256 gray   
//		FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
//		FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
//		FT_Bitmap& bitmap = bitmap_glyph->bitmap;
//
//		std::vector<Vector3> Position;
//		std::vector<Vector2> UV;
//		std::vector<unsigned int> indice;
//	
//		float w = bitmap_glyph->left;
//		float h = bitmap_glyph->top;
//
//		Position.emplace_back(-1.0f + offset_x, 2.0f, 1.0f);
//		Position.emplace_back(1.0f, 0.0f, 0.0f, 1.0f);
//		Position.emplace_back(1.0f + offset_x, 2.0f, 1.0f);
//		Position.emplace_back(1.0f, 0.0f, 0.0f, 1.0f);
//		Position.emplace_back(1.0f + offset_x, 4.0f, 1.0f);
//		Position.emplace_back(0.0f, 1.0f, 0.0f, 1.0f);
//		Position.emplace_back(-1.0f + offset_x, 4.0f, 1.0f);
//		Position.emplace_back(0.0f, 1.0f, 0.0f, 1.0f);
//
//
//		UV.emplace_back(0.0f, 0.0f);
//		UV.emplace_back(0.0f, 1.0f);
//		UV.emplace_back(1.0f, 1.0f);
//		UV.emplace_back(0.0f, 0.0f);
//
//		indice.emplace_back(0);
//		indice.emplace_back(1);
//		indice.emplace_back(2);
//
//		indice.emplace_back(0);
//		indice.emplace_back(2);
//		indice.emplace_back(3);
//
//		Mesh mesh(Position, UV, indice);
//		mesh.Finalize();
//
//		m_fontMesh[text_char] = mesh;
//
//		FT_Done_Glyph(glyph);
//	}
//}
//
//bool FontManager::GetFontBitmapData(const std::string& fontName)
//{
//	auto iterFont = m_fontList.find(fontName);
//	if (iterFont == m_fontList.end())
//	{
//		LOG_ERROR("error : can not find font %s!", fontName.c_str());
//		return false;
//	}
//
//	FT_Face face = iterFont->second;
//
//	FT_Error error = FT_Set_Pixel_Sizes(face, m_font.m_width, m_font.m_height);
//	if (error)
//	{
//		LOG_ERROR("error : an error occurs when trying to set the pixel size to a value");
//		return false;
//	}
//
//	ExtraceTexture("尼玛我在测试", face);
//	ExtraceMesh("尼玛我在测试", face);
//
//	return true;
//}