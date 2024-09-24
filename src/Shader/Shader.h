#pragma once
#include <set>

#include "Common.h"
#include "Engine.h"
#include "RenderCommon.h"
#include "Scene.h"

namespace Kong
{
	class AActor;
	class ShaderManager;
	
	// shader的主类型，后面每个shader的类型都会建一个类集成Shader类
	// 每个shader子类对应相同的shader编译文件，所以按理来说是可以每个类型的shader加载一次就行，而不需要每个模型加载一次，性能得以优化
    class Shader
    {
    public:
    	Shader() = default;
    	Shader(const map<EShaderType, string>& shader_paths);
	    virtual ~Shader() = default;
	    //static GLuint LoadShaders(const std::string& vertex_file_path, const std::string& fragment_file_path)
    	static GLuint LoadShaders(const map<EShaderType, string>& shader_path_map);
    	static void IncludeShader(const string& include_path);
    	static std::vector<std::string> FindIncludeFiles(const string& code_content);
    	
    	void SetBool(const std::string &name, bool value)
	    {         
	        glUniform1i(glGetUniformLocation(shader_id, name.c_str()), (int)value); 
	    }
	    // ------------------------------------------------------------------------
	    void SetInt(const std::string &name, int value)
	    { 
	        glUniform1i(glGetUniformLocation(shader_id, name.c_str()), value); 
	    }
	    // ------------------------------------------------------------------------
	    void SetFloat(const std::string &name, float value)
	    { 
	        glUniform1f(glGetUniformLocation(shader_id, name.c_str()), value); 
	    }
	    // ------------------------------------------------------------------------
	    void SetVec2(const std::string &name, const glm::vec2 &value)
	    { 
	        glUniform2fv(glGetUniformLocation(shader_id, name.c_str()), 1, &value[0]); 
	    }
	    void SetVec2(const std::string &name, float x, float y)
	    { 
	        glUniform2f(glGetUniformLocation(shader_id, name.c_str()), x, y); 
	    }
	    // ------------------------------------------------------------------------
	    void SetVec3(const std::string &name, const glm::vec3 &value)
	    { 
	        glUniform3fv(glGetUniformLocation(shader_id, name.c_str()), 1, &value[0]); 
	    }
	    void SetVec3(const std::string &name, float x, float y, float z)
	    { 
	        glUniform3f(glGetUniformLocation(shader_id, name.c_str()), x, y, z); 
	    }
	    // ------------------------------------------------------------------------
	    void SetVec4(const std::string &name, const glm::vec4 &value)
	    { 
	        glUniform4fv(glGetUniformLocation(shader_id, name.c_str()), 1, &value[0]); 
	    }
	    void SetVec4(const std::string &name, float x, float y, float z, float w)
	    { 
	        glUniform4f(glGetUniformLocation(shader_id, name.c_str()), x, y, z, w); 
	    }
	    // ------------------------------------------------------------------------
	    void SetMat2(const std::string &name, const glm::mat2 &mat) 
	    {
	        glUniformMatrix2fv(glGetUniformLocation(shader_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	    }
	    // ------------------------------------------------------------------------
	    void SetMat3(const std::string &name, const glm::mat3 &mat)
	    {
	        glUniformMatrix3fv(glGetUniformLocation(shader_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	    }
	    // ------------------------------------------------------------------------
	    void SetMat4(const std::string &name, const glm::mat4 &mat)
	    {
	        glUniformMatrix4fv(glGetUniformLocation(shader_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	    }

    	void Init(const map<EShaderType, string>& shader_path_cache);
    	// 使用该shader
    	void Use() const;
    	// 获取这个shader需要的数据，每个shader的需求应该是不一样的所以子类需要实现;
    	// 父类的这个是为了支持原先的传入shader文件的写法，也就是设置尽量全名的参数传入
    	virtual void UpdateRenderData(const SMaterial& render_material,
    		const SSceneRenderInfo& scene_render_info);
    	virtual void InitDefaultShader(){};
    	
    	bool bIsBlend = false;
    protected:
    	// shader id
    	GLuint shader_id = GL_NONE;
		// shader file path
    	map<EShaderType, string> shader_path_map;

    };
	
	class ShaderManager
	{
	public:
		static shared_ptr<Shader> GetShader(const string& shader_name);

	protected:
		shared_ptr<Shader> GetShaderFromTypeName(const string& shader_name);
	private:
		
		std::map<string, shared_ptr<Shader>> shader_cache;
	};
}
