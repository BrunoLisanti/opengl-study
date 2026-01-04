#include "../lib/include/glad/glad.h"
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"
#include <vector>
#include <filesystem>



namespace b
{
	//La textura deberia poder actuar como texture unit
	class texture
	{
	private:
		unsigned ID;
		int width, height, nrchannels;

	public:
		texture() { }

		texture(std::filesystem::path file_path) 
		{
			stbi_set_flip_vertically_on_load(true);
			unsigned char *data = stbi_load(file_path.c_str(), &width, &height, &nrchannels, 0);

			if (!data) 
				throw std::runtime_error("No se pudo cargar la textura");

			glGenTextures(1, &ID);
			glBindTexture(GL_TEXTURE_2D, ID);

			// TODO: Esto esta recontra hardcodeado
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			//Estos parametros tienen que ir como opciones en el constructor

			if (file_path.extension() == ".jpg")
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			else if (file_path.extension() == ".png")
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);
			stbi_image_free(data);
		}

		void bind() 
		{
			glBindTexture(GL_TEXTURE_2D, ID);
		}

		unsigned get_id() { return ID; }

	private:
	};
}
