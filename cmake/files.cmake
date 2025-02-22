# Automatically generated from build/files by build/upmake
# DO NOT MODIFY MANUALLY !

set(ANALYTICS_SRC
	../OpenGL/Analytics/ProfilterReport.h
	../OpenGL/Analytics/ProfilterReport.h
)

set(AUDIO_CORE_SRC
	../OpenGL/Audio/Core/AudioEngine.h
	../OpenGL/Audio/Core/AudioEngine.cpp
	../OpenGL/Audio/Core/AudioPlayer.h
	../OpenGL/Audio/Core/AudioPlayer.cpp
)

set(AUDIO_ENTITY_SRC
	../OpenGL/Audio/Entity/AudioSource.h
	../OpenGL/Audio/Entity/AudioSource.cpp
	../OpenGL/Audio/Entity/AudioListener.h
	../OpenGL/Audio/Entity/AudioListener.cpp
)

set(AUDIO_RESOURCE_SRC
	../OpenGL/Audio/Resource/Sound.h
	../OpenGL/Audio/Resource/Sound.cpp
)

set(CAMERA_SRC
	../OpenGL/Camera/Camera.h
	../OpenGL/Camera/Camera.cpp
	../OpenGL/Camera/CameraFrustum.h
	../OpenGL/Camera/CameraFrustum.cpp
	../OpenGL/Camera/FlyCamera.h
	../OpenGL/Camera/FlyCamera.cpp
)

set(CORE_API_SRC
	../OpenGL/Core/API/IInspectorItem.h
	../OpenGL/Core/API/IInspectorItem.cpp
	../OpenGL/Core/API/ISerializable.h
	../OpenGL/Core/API/ISerializable.cpp
	../OpenGL/Core/API/tinyxml2.h
	../OpenGL/Core/API/tinyxml2.cpp
)

set(CORE_ECS_SRC
	../OpenGL/Core/ECS/Actor.inl
	../OpenGL/Core/ECS/Actor.h
	../OpenGL/Core/ECS/Actor.cpp
)

set(CORE_ECS_COMPONENT_SRC
	../OpenGL/Core/ECS/Components/AComponent.h
	../OpenGL/Core/ECS/Components/AComponent.cpp
	../OpenGL/Core/ECS/Components/AComponent.h
	../OpenGL/Core/ECS/Components/Behaviour.inl
	../OpenGL/Core/ECS/Components/Behaviour.h
	../OpenGL/Core/ECS/Components/Behaviour.cpp
	../OpenGL/Core/ECS/Components/CAmbientSphereLight.h
	../OpenGL/Core/ECS/Components/CAmbientSphereLight.cpp
	../OpenGL/Core/ECS/Components/CArmature.h
	../OpenGL/Core/ECS/Components/CArmature.cpp
	../OpenGL/Core/ECS/Components/CAudioSource.h
	../OpenGL/Core/ECS/Components/CAudioSource.cpp
	../OpenGL/Core/ECS/Components/CCamera.h
	../OpenGL/Core/ECS/Components/CCamera.cpp
	../OpenGL/Core/ECS/Components/CDirectionalLight.h
	../OpenGL/Core/ECS/Components/CDirectionalLight.cpp
	../OpenGL/Core/ECS/Components/CLight.h
	../OpenGL/Core/ECS/Components/CLight.cpp
	../OpenGL/Core/ECS/Components/CMaterialRenderer.h
	../OpenGL/Core/ECS/Components/CMaterialRenderer.cpp
	../OpenGL/Core/ECS/Components/CModelRenderer.h
	../OpenGL/Core/ECS/Components/CModelRenderer.cpp
	../OpenGL/Core/ECS/Components/CPose.h
	../OpenGL/Core/ECS/Components/CPose.cpp
	../OpenGL/Core/ECS/Components/CTextMeshPro.h
	../OpenGL/Core/ECS/Components/CTextMeshPro.cpp
	../OpenGL/Core/ECS/Components/CTransform.h
	../OpenGL/Core/ECS/Components/CTransform.cpp
)

set(CORE_HELPER_SRC
	../OpenGL/Core/Helper/Serializer.h
	../OpenGL/Core/Helper/Serializer.cpp
)

set(CORE_SCRIPTING_SRC
	../OpenGL/Core/Scripting/LuaActorBinder.h
	../OpenGL/Core/Scripting/LuaActorBinder.cpp
	../OpenGL/Core/Scripting/LuaBinder.h
	../OpenGL/Core/Scripting/LuaBinder.cpp
	../OpenGL/Core/Scripting/ScriptInterpreter.h
	../OpenGL/Core/Scripting/ScriptInterpreter.cpp
)

set(CORE_Util_SRC
	../OpenGL/Core/Util/Light.h
	../OpenGL/Core/Util/Light.cpp
	../OpenGL/Core/Util/SystemCall.h
	../OpenGL/Core/Util/SystemCall.cpp
)

set(EDITOR_CORE_SRC
	../OpenGL/Editor/Core/Application.h
	../OpenGL/Editor/Core/Application.cpp
	../OpenGL/Editor/Core/CameraController.h
	../OpenGL/Editor/Core/CameraController.cpp
	../OpenGL/Editor/Core/Context.h
	../OpenGL/Editor/Core/Context.cpp
	../OpenGL/Editor/Core/Editor.h
	../OpenGL/Editor/Core/Editor.cpp
	../OpenGL/Editor/Core/EditorAction.h
	../OpenGL/Editor/Core/EditorAction.cpp
	../OpenGL/Editor/Core/EditorRender.h
	../OpenGL/Editor/Core/EditorRender.cpp
	../OpenGL/Editor/Core/EditorResource.h
	../OpenGL/Editor/Core/EditorResource.cpp
	../OpenGL/Editor/Core/GizmoBehaviour.h
	../OpenGL/Editor/Core/GizmoBehaviour.cpp
	../OpenGL/Editor/Core/PanelsManager.h
	../OpenGL/Editor/Core/PanelsManager.cpp
)

set(EDITOR_HELPER_SRC
	../OpenGL/Editor/Helper/GUIDrawer.inl
	../OpenGL/Editor/Helper/GUIDrawer.h
	../OpenGL/Editor/Helper/GUIDrawer.cpp
)

set(EDITOR_PANELS_SRC
	../OpenGL/Editor/Panels/AssetBrowser.h
	../OpenGL/Editor/Panels/AssetBrowser.cpp
	../OpenGL/Editor/Panels/AssetView.h
	../OpenGL/Editor/Panels/AssetView.cpp
	../OpenGL/Editor/Panels/AView.h
	../OpenGL/Editor/Panels/AView.cpp
	../OpenGL/Editor/Panels/AViewControllable.h
	../OpenGL/Editor/Panels/AViewControllable.cpp
	../OpenGL/Editor/Panels/Console.h
	../OpenGL/Editor/Panels/Console.cpp
	../OpenGL/Editor/Panels/DebugView.h
	../OpenGL/Editor/Panels/DebugView.cpp
	../OpenGL/Editor/Panels/GameView.h
	../OpenGL/Editor/Panels/GameView.cpp
	../OpenGL/Editor/Panels/Hierarchy.h
	../OpenGL/Editor/Panels/Hierarchy.cpp
	../OpenGL/Editor/Panels/HierarchyNew.h
	../OpenGL/Editor/Panels/HierarchyNew.cpp
	../OpenGL/Editor/Panels/Inspector.h
	../OpenGL/Editor/Panels/Inspector.cpp
	../OpenGL/Editor/Panels/MaterialEditor.h
	../OpenGL/Editor/Panels/MaterialEditor.cpp
	../OpenGL/Editor/Panels/MenuBar.h
	../OpenGL/Editor/Panels/MenuBar.cpp
	../OpenGL/Editor/Panels/ModelView.h
	../OpenGL/Editor/Panels/ModelView.cpp
	../OpenGL/Editor/Panels/Profiler.h
	../OpenGL/Editor/Panels/Profiler.cpp
	../OpenGL/Editor/Panels/ProjectSettings.h
	../OpenGL/Editor/Panels/ProjectSettings.cpp
	../OpenGL/Editor/Panels/SceneView.h
	../OpenGL/Editor/Panels/SceneView.cpp
	../OpenGL/Editor/Panels/TimeLine.h
	../OpenGL/Editor/Panels/TimeLine.cpp
	../OpenGL/Editor/Panels/ToolBar.h
	../OpenGL/Editor/Panels/ToolBar.cpp
)

set(EDITOR_UTIL_SRC
	../OpenGL/Editor/Util/ActorCreationMenu.h
	../OpenGL/Editor/Util/ActorCreationMenu.cpp
)

set(EVENT_SRC
	../OpenGL/Event/Event.inl
	../OpenGL/Event/Event.h
)

set(FILE_SRC
	../OpenGL/File/ConfigManager.h
	../OpenGL/File/ConfigManager.cpp
	../OpenGL/File/FileMonitor.h
	../OpenGL/File/FileMonitor.cpp
	../OpenGL/File/LanguageDefine.h
	../OpenGL/File/LuaFileChangeHandler.h
	../OpenGL/File/LuaFileChangeHandler.cpp
	../OpenGL/File/ResourceChangeHandler.h
	../OpenGL/File/ResourceChangeHandler.cpp
	../OpenGL/File/ShaderFileChangeHandler.h
	../OpenGL/File/ShaderFileChangeHandler.cpp
	../OpenGL/File/XmlManager.h
	../OpenGL/File/XmlManager.cpp
)

set(FILE_PATH_SRC
	../OpenGL/File/Path/PathParser.h
	../OpenGL/File/Path/PathParser.cpp
)

set(GLOBAL_SRC
	../OpenGL/Global/BaseFunction.h
	../OpenGL/Global/BaseFunction.cpp
	../OpenGL/Global/GlobalContext.h
	../OpenGL/Global/GlobalContext.cpp
	../OpenGL/Global/ServiceLocator.h
	../OpenGL/Global/ServiceLocator.cpp
)

set(LOG_SRC
	../OpenGL/Log/ConsoleColor.h
	../OpenGL/Log/ConsoleHandler.h
	../OpenGL/Log/ConsoleHandler.cpp
	../OpenGL/Log/DumpFileManager.h
	../OpenGL/Log/ILogHandler.h
	../OpenGL/Log/ILogHandler.cpp
	../OpenGL/Log/Logger.inl
	../OpenGL/Log/Logger.h
	../OpenGL/Log/Logger.cpp
)

set(MATH_SRC
	../OpenGL/Math/Math.h
	../OpenGL/Math/Math.cpp
)

set(RENDER_SRC
	../OpenGL/Render/BaseRenderer.h
	../OpenGL/Render/BaseRenderer.cpp
	../OpenGL/Render/CommandBuffer.h
	../OpenGL/Render/CommandBuffer.cpp
	../OpenGL/Render/GLCache.h
	../OpenGL/Render/GLCache.cpp
	../OpenGL/Render/PBR.h
	../OpenGL/Render/PBR.cpp
	../OpenGL/Render/PostProcess.h
	../OpenGL/Render/PostProcess.cpp
	../OpenGL/Render/RenderCommand.h
	../OpenGL/Render/Renderer.h
	../OpenGL/Render/Renderer.cpp
	../OpenGL/Render/RenderManager.h
	../OpenGL/Render/RenderManager.cpp
	../OpenGL/Render/RenderTarget.h
	../OpenGL/Render/RenderTarget.cpp
	../OpenGL/Render/ShaderConfig.h
	../OpenGL/Render/ShapeDrawer.h
	../OpenGL/Render/ShapeDrawer.cpp
)

set(RENDER_ANIMATION_SRC
	../OpenGL/Render/Animation/Animation.h
	../OpenGL/Render/Animation/Animation.cpp
	../OpenGL/Render/Animation/Animator.h
	../OpenGL/Render/Animation/Animator.cpp
	../OpenGL/Render/Animation/Bone.h
	../OpenGL/Render/Animation/Bone.cpp	
)

set(RENDER_BOUNDING_SRC
	../OpenGL/Render/Bounding/BoundingSphere.h
	../OpenGL/Render/Bounding/BoundingSphere.cpp
)

set(RENDER_CONTEXT_SRC
	../OpenGL/Render/Context/Driver.h
	../OpenGL/Render/Context/Driver.cpp
)

set(RENDER_DEFERRED_SRC
	../OpenGL/Render/Deferred/DeferredRenderer.h
	../OpenGL/Render/Deferred/DeferredRenderer.cpp
)

set(RENDER_DEFERRED_PROGRAM_SRC
	../OpenGL/Render/Deferred/Program/Program.h
	../OpenGL/Render/Deferred/Program/Program.cpp
)

set(RENDER_FONT_SRC
	../OpenGL/Render/Font/Font.h
	../OpenGL/Render/Font/Font.cpp
	../OpenGL/Render/Font/FontManager.h
	../OpenGL/Render/Font/FontManager.cpp
)

set(RENDER_FORWARD_SRC
	../OpenGL/Render/Forward/ForwardRenderer.h
	../OpenGL/Render/Forward/ForwardRenderer.cpp
)

set(RENDER_LIGHTING_SRC
	../OpenGL/Render/Lighting/DirectionalLight.h
	../OpenGL/Render/Lighting/DirectionalLight.cpp
	../OpenGL/Render/Lighting/PointLight.h
)

set(RENDER_MATERIAL_SRC
	../OpenGL/Render/Material/MaterialLibrary.h
	../OpenGL/Render/Material/MaterialLibrary.cpp
	../OpenGL/Render/Material/MaterialEditorType.h
)

set(RENDER_MESH_SRC
	../OpenGL/Render/Mesh/AABB.h
	../OpenGL/Render/Mesh/AABB.cpp
	../OpenGL/Render/Mesh/Cube.h
	../OpenGL/Render/Mesh/Cube.cpp
	../OpenGL/Render/Mesh/DebugScreenQuad.h
	../OpenGL/Render/Mesh/DebugScreenQuad.cpp
	../OpenGL/Render/Mesh/Material.h
	../OpenGL/Render/Mesh/Material.cpp
	../OpenGL/Render/Mesh/Mesh.h
	../OpenGL/Render/Mesh/Mesh.cpp
	../OpenGL/Render/Mesh/Mesh_ID.h
	../OpenGL/Render/Mesh/Model.h
	../OpenGL/Render/Mesh/Model.cpp
	../OpenGL/Render/Mesh/Quad.h
	../OpenGL/Render/Mesh/Quad.cpp
	../OpenGL/Render/Mesh/Sphere.h
	../OpenGL/Render/Mesh/Sphere.cpp
)

set(RENDER_RESOURCE_SRC
	../OpenGL/Render/Resource/AResourceManager.h
	../OpenGL/Render/Resource/AResourceManager.cpp
	../OpenGL/Render/Resource/AResourceManager.inl
	../OpenGL/Render/Resource/MaterialManager.h
	../OpenGL/Render/Resource/MaterialManager.cpp
	../OpenGL/Render/Resource/ModelManager.h
	../OpenGL/Render/Resource/ModelManager.cpp
	../OpenGL/Render/Resource/RawShader.h
	../OpenGL/Render/Resource/RawShader.cpp
	../OpenGL/Render/Resource/ResourceManager.h
	../OpenGL/Render/Resource/ResourceManager.cpp
	../OpenGL/Render/Resource/ShaderManager.h
	../OpenGL/Render/Resource/ShaderManager.cpp
	../OpenGL/Render/Resource/TextureManager.h
	../OpenGL/Render/Resource/TextureManager.cpp
)

set(RENDER_RESOURCE_LOADER_SRC
	../OpenGL/Render/Resource/Loader/AnimLoader.h
	../OpenGL/Render/Resource/Loader/AnimLoader.cpp
	../OpenGL/Render/Resource/Loader/MaterialLoader.h
	../OpenGL/Render/Resource/Loader/MaterialLoader.cpp
	../OpenGL/Render/Resource/Loader/MeshLoader.h
	../OpenGL/Render/Resource/Loader/MeshLoader.cpp
	../OpenGL/Render/Resource/Loader/ModelLoader.h
	../OpenGL/Render/Resource/Loader/ModelLoader.cpp
	../OpenGL/Render/Resource/Loader/ShaderLoader.h
	../OpenGL/Render/Resource/Loader/ShaderLoader.cpp
	../OpenGL/Render/Resource/Loader/TextureLoader.h
	../OpenGL/Render/Resource/Loader/TextureLoader.cpp
)

set(RENDER_RESOURCE_LOADER_ASYNC_SRC
	../OpenGL/Render/Resource/Loader/Async/FileJob.h
	../OpenGL/Render/Resource/Loader/Async/FileJob.cpp
	../OpenGL/Render/Resource/Loader/Async/FontJob.h
	../OpenGL/Render/Resource/Loader/Async/FontJob.cpp
	../OpenGL/Render/Resource/Loader/Async/AnimJob.h
	../OpenGL/Render/Resource/Loader/Async/AnimJob.cpp
	../OpenGL/Render/Resource/Loader/Async/ModelJob.h
	../OpenGL/Render/Resource/Loader/Async/ModelJob.cpp
	../OpenGL/Render/Resource/Loader/Async/ShaderJob.h
	../OpenGL/Render/Resource/Loader/Async/ShaderJob.cpp
	../OpenGL/Render/Resource/Loader/Async/ResourceJob.h
	../OpenGL/Render/Resource/Loader/Async/ResourceJob.cpp
	../OpenGL/Render/Resource/Loader/Async/MaterialJob.h
	../OpenGL/Render/Resource/Loader/Async/MaterialJob.cpp
	../OpenGL/Render/Resource/Loader/Async/Texture2DJob.h
	../OpenGL/Render/Resource/Loader/Async/Texture2DJob.cpp
	../OpenGL/Render/Resource/Loader/Async/Texture3DJob.h
	../OpenGL/Render/Resource/Loader/Async/Texture3DJob.cpp
	../OpenGL/Render/Resource/Loader/Async/AsynLoaderManager.h
	../OpenGL/Render/Resource/Loader/Async/AsynLoaderManager.cpp
)

set(RENDER_RESOURCE_PARSER_SRC
	../OpenGL/Render/Resource/Parser/AssimpParser.h
	../OpenGL/Render/Resource/Parser/AssimpParser.cpp
	../OpenGL/Render/Resource/Parser/EModelParserFlags.h
	../OpenGL/Render/Resource/Parser/IAnimationParser.h
	../OpenGL/Render/Resource/Parser/IModelParser.h
	../OpenGL/Render/Resource/Parser/IModelParser.cpp
)

set(RENDER_SETTING_SRC
	../OpenGL/Render/Setting/EPrimitiveMode.h
)

set(RENDER_SHADER_SRC
	../OpenGL/Render/Shader/EShader.h
	../OpenGL/Render/Shader/EShader.cpp
	../OpenGL/Render/Shader/ShaderStorageBuffer.h
	../OpenGL/Render/Shader/ShaderStorageBuffer.cpp
	../OpenGL/Render/Shader/ShaderStorageBuffer.inl
	../OpenGL/Render/Shader/ShaderType.h
	../OpenGL/Render/Shader/Texture.h
	../OpenGL/Render/Shader/Texture.cpp
	../OpenGL/Render/Shader/TextureCube.h
	../OpenGL/Render/Shader/TextureCube.cpp
	../OpenGL/Render/Shader/UniformBuffer.h
	../OpenGL/Render/Shader/UniformBuffer.cpp
	../OpenGL/Render/Shader/UniformBuffer.inl
)

set(RENDER_SHADOW_SRC
	../OpenGL/Render/Shadow/CascadeShadowMap.h
	../OpenGL/Render/Shadow/CascadeShadowMap.cpp
	../OpenGL/Render/Shadow/ShadowMap.h
	../OpenGL/Render/Shadow/ShadowMap.cpp	
)

set(RHI_SRC
	../OpenGL/RHI/GraphicsManager.h
	../OpenGL/RHI/GraphicsManager.cpp
	../OpenGL/RHI/PipelineState.h
	../OpenGL/RHI/PipelineState.cpp	
	../OpenGL/RHI/PipelineStateManager.h
	../OpenGL/RHI/PipelineStateManager.cpp
	../OpenGL/RHI/RenderRHI.h
	../OpenGL/RHI/RenderRHI.cpp	
	../OpenGL/RHI/RHIVulkan.h
	../OpenGL/RHI/RHIVulkan.cpp	
)

set(RHI_OPENGL_SRC
	../OpenGL/RHI/OpenGL/OpenGLGraphicsManager.h
	../OpenGL/RHI/OpenGL/OpenGLGraphicsManager.cpp
	../OpenGL/RHI/OpenGL/OpenGLPipelineState.h
	../OpenGL/RHI/OpenGL/OpenGLPipelineState.cpp	
	../OpenGL/RHI/OpenGL/OpenGLRenderCommand.h
	../OpenGL/RHI/OpenGL/OpenGLRenderCommand.cpp	
	../OpenGL/RHI/OpenGL/OpenGLSatateManager.h
	../OpenGL/RHI/OpenGL/OpenGLSatateManager.cpp	
)

set(SCENE_SRC
	../OpenGL/Scene/Background.h
	../OpenGL/Scene/Background.cpp
	../OpenGL/Scene/Scene.h
	../OpenGL/Scene/Scene.cpp	
	../OpenGL/Scene/SceneManager.h
	../OpenGL/Scene/SceneManager.cpp	
	../OpenGL/Scene/SceneNode.h
	../OpenGL/Scene/SceneNode.cpp	
)

set(THREAD_SRC
	../OpenGL/Thread/Runable.h
	../OpenGL/Thread/Util.h
	../OpenGL/Thread/Thread.h
	../OpenGL/Thread/Thread.cpp
	../OpenGL/Thread/WinThread.h
	../OpenGL/Thread/WinThread.cpp
	../OpenGL/Thread/ThreadPool.h
	../OpenGL/Thread/ThreadPool.cpp	
)

set(TIME_SRC
	../OpenGL/Time/Date.h
	../OpenGL/Time/Date.cpp	
	../OpenGL/Time/Time.h
	../OpenGL/Time/Time.cpp	
)

set(UI_SRC
	../OpenGL/UI/UIManager.h
	../OpenGL/UI/UIManager.cpp	
)

set(UI_API_SRC
	../OpenGL/UI/API/IDrawable.h
)

set(UI_INTERNEL_SRC
	../OpenGL/UI/Internel/UI_Common.h
	../OpenGL/UI/Internel/UI_MemoryModel.h
	../OpenGL/UI/Internel/WidgetContainer.h
	../OpenGL/UI/Internel/WidgetContainer.cpp
)

set(UI_LAYOUT_SRC
	../OpenGL/UI/Layout/Columns.h
	../OpenGL/UI/Layout/Columns.cpp
	../OpenGL/UI/Layout/Group.h
	../OpenGL/UI/Layout/Group.cpp
	../OpenGL/UI/Layout/GroupCollapsable.h
	../OpenGL/UI/Layout/GroupCollapsable.cpp
	../OpenGL/UI/Layout/TreeNode.h
	../OpenGL/UI/Layout/TreeNode.cpp
)

set(UI_MODULE_SRC
	../OpenGL/UI/Module/Canvas.h
	../OpenGL/UI/Module/Canvas.cpp
)

set(UI_PANEL_SRC
	../OpenGL/UI/Panel/APanel.h
	../OpenGL/UI/Panel/APanel.cpp
	../OpenGL/UI/Panel/APanelTransformable.h
	../OpenGL/UI/Panel/APanelTransformable.cpp
	../OpenGL/UI/Panel/PanelMenuBar.h
	../OpenGL/UI/Panel/PanelMenuBar.cpp
	../OpenGL/UI/Panel/PanelWindow.h
	../OpenGL/UI/Panel/PanelWindow.cpp
)

set(UI_PLUGIN_SRC
	../OpenGL/UI/Plugin/ContextualMenu.h
	../OpenGL/UI/Plugin/ContextualMenu.cpp
	../OpenGL/UI/Plugin/DataDispatcher.h
	../OpenGL/UI/Plugin/DataDispatcher.cpp
	../OpenGL/UI/Plugin/DDSource.h
	../OpenGL/UI/Plugin/DDSource.cpp
	../OpenGL/UI/Plugin/DDTarget.h
	../OpenGL/UI/Plugin/DDTarget.cpp
	../OpenGL/UI/Plugin/IPlugin.h
	../OpenGL/UI/Plugin/Pluginable.h
	../OpenGL/UI/Plugin/TexturePreview.h
	../OpenGL/UI/Plugin/TexturePreview.cpp
)

set(UI_VISUAL_SRC
	../OpenGL/UI/Visual/Image.h
	../OpenGL/UI/Visual/Image.cpp
	../OpenGL/UI/Visual/ProgressBar.h
	../OpenGL/UI/Visual/ProgressBar.cpp
	../OpenGL/UI/Visual/Separator.h
	../OpenGL/UI/Visual/Separator.cpp
)

set(UI_WIDGETS_SRC
	../OpenGL/UI/Widgets/AWidget.h
	../OpenGL/UI/Widgets/AWidget.cpp
	../OpenGL/UI/Widgets/DataWidget.h
	../OpenGL/UI/Widgets/DataWidget.cpp
)

set(UI_WIDGETS_BUTTON_SRC
	../OpenGL/UI/Widgets/Button/AButton.h
	../OpenGL/UI/Widgets/Button/AButton.cpp
	../OpenGL/UI/Widgets/Button/Button.h
	../OpenGL/UI/Widgets/Button/Button.cpp
	../OpenGL/UI/Widgets/Button/ButtonImage.h
	../OpenGL/UI/Widgets/Button/ButtonImage.cpp
)

set(UI_WIDGETS_DRAG_SRC
	../OpenGL/UI/Widgets/Drag/DragMultipleScalars.h
	../OpenGL/UI/Widgets/Drag/DragMultipleScalars.cpp
	../OpenGL/UI/Widgets/Drag/DragSingleScalar.h
	../OpenGL/UI/Widgets/Drag/DragSingleScalar.cpp
)

set(UI_WIDGETS_INPUTFIELD_SRC
	../OpenGL/UI/Widgets/InputField/InputText.h
	../OpenGL/UI/Widgets/InputField/InputText.cpp
)

set(UI_WIDGETS_MENU_SRC
	../OpenGL/UI/Widgets/Menu/MenuItem.h
	../OpenGL/UI/Widgets/Menu/MenuItem.cpp
	../OpenGL/UI/Widgets/Menu/MenuList.h
	../OpenGL/UI/Widgets/Menu/MenuList.cpp
)

set(UI_WIDGETS_SELECTION_SRC
	../OpenGL/UI/Widgets/Selection/CheckBox.h
	../OpenGL/UI/Widgets/Selection/CheckBox.cpp
	../OpenGL/UI/Widgets/Selection/ColorEdit.h
	../OpenGL/UI/Widgets/Selection/ColorEdit.cpp
	../OpenGL/UI/Widgets/Selection/ComboBox.h
	../OpenGL/UI/Widgets/Selection/ComboBox.cpp
)

set(UI_WIDGETS_TEXT_SRC
	../OpenGL/UI/Widgets/Text/Text.h
	../OpenGL/UI/Widgets/Text/Text.cpp
	../OpenGL/UI/Widgets/Text/TextClickable.h
	../OpenGL/UI/Widgets/Text/TextClickable.cpp
	../OpenGL/UI/Widgets/Text/TextColored.h
	../OpenGL/UI/Widgets/Text/TextColored.cpp
	../OpenGL/UI/Widgets/Text/TextSelectable.h
	../OpenGL/UI/Widgets/Text/TextSelectable.cpp		
)

set(UTIL_SRC
	../OpenGL/Util/common.h
	../OpenGL/Util/Singleton.h
	../OpenGL/Util/Utils.h
	../OpenGL/Util/string_id.hpp		
)

set(WINDOW_SRC
	../OpenGL/Window/GLFWWindow.h
	../OpenGL/Window/GLFWWindow.cpp
	../OpenGL/Window/Window.h
	../OpenGL/Window/Window.cpp
	../OpenGL/Window/WindowManager.h
	../OpenGL/Window/WindowManager.cpp	
)

set(WINDOW_CONTEXT_SRC
	../OpenGL/Window/GLFWWindow.h
	../OpenGL/Window/GLFWWindow.cpp
	../OpenGL/Window/Window.h
	../OpenGL/Window/Window.cpp
	../OpenGL/Window/WindowManager.h
	../OpenGL/Window/WindowManager.cpp	
)

set(WINDOW_INPUT_SRC
	../OpenGL/Window/Input/Key.h
	../OpenGL/Window/Input/MouseBtn.h
	../OpenGL/Window/Input/InputManager.h
	../OpenGL/Window/Input/InputManager.cpp
)

set(WINDOW_CONTEXT_SRC
	../OpenGL/Window/Context/Device.h
	../OpenGL/Window/Context/Device.cpp
)
