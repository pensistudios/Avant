#include <gl/gl.h>
#include <gl/glu.h>
#include "CTargaImage.h"
#include "gengine.h"

#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1

namespace Avant
{

class OpenGLRenderer
{
private:
		
	int m_windowWidth;
	int m_windowHeight;
	unsigned int fontBase;
	GLuint list;
	int state;
	

	Resource::CTargaImage* m_woodTexture;
	unsigned int m_woodTextureId;

	Avant::GameEngine *m_gameEngine;
	void drawLines();
	

public:
	
	OpenGLRenderer();
	virtual ~OpenGLRenderer();

	bool Init();
	bool Shutdown();

	void SetupProjection(int width, int height);

	void Prepare(float dt, Avant::Input * input);
	void Render();

	void AttachToGame(Avant::GameEngine * gengine);

	bool checkExtension(char* extName);

	unsigned int getFontBase();

};

};	
