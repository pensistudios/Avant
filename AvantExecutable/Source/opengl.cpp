#include <windows.h>
#include <math.h>
#include "opengl.h"

#pragma warning(disable:4305)

using namespace Avant;

OpenGLRenderer::OpenGLRenderer()
{
}

OpenGLRenderer::~OpenGLRenderer()
{
}

bool OpenGLRenderer::Init()
{

	if(!m_gameEngine->init())
		return false;

    glClearColor(0.0, 0.0, 0.0, 0.0);

	m_woodTexture = new Resource::CTargaImage();

	if(!m_woodTexture->Load("Media/wood.tga"))
		return false;
	
	glGenTextures(1, &m_woodTextureId);

	glBindTexture(GL_TEXTURE_2D, m_woodTextureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_woodTexture->GetWidth(), m_woodTexture->GetHeight(),
				0, GL_RGB, GL_UNSIGNED_BYTE, m_woodTexture->GetImage());


	list = glGenLists(1);
	fontBase = glGenLists(96);

    return true;
}

bool OpenGLRenderer::Shutdown()
{
	glDeleteTextures(1, &m_woodTextureId);

	glDeleteLists(fontBase, 96);
	glDeleteLists(list, 1);

	m_woodTexture->Release();
	delete m_woodTexture;

    return true;
}

void OpenGLRenderer::SetupProjection(int width, int height)
{
    if (height == 0)                   
    {
        height = 1;                 
    }

    glViewport(0, 0, width, height);        
    glMatrixMode(GL_PROJECTION);            
    glLoadIdentity();                       
	
    gluPerspective(52.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);
	
    glMatrixMode(GL_MODELVIEW);             
    glLoadIdentity();                       

    m_windowWidth = width;
    m_windowHeight = height;
}

void OpenGLRenderer::Prepare(float dt, Avant::Input * input)
{
	state = m_gameEngine->state;

	m_gameEngine->update(dt, m_windowWidth,m_windowHeight,input);
}

void OpenGLRenderer::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);     
    glLoadIdentity();

	if(state == Avant::GameEngine::GAMESTATE_MENU || state == Avant::GameEngine::GAMESTATE_TRANSITION)
	{
		if(state == Avant::GameEngine::GAMESTATE_MENU)
		{
			glTranslatef(0.0,0.0,-50.0);
		}
		
		

		glNewList(list, GL_COMPILE_AND_EXECUTE);
		
		glColor3f(0.5,0.5,0.5);
		glBegin(GL_QUADS);
			glVertex3f(40.0f,30.0f,0.0f);
			glVertex3f(40.0f,-30.0f,0.0f);
			glVertex3f(-40.0f,-30.0f,0.0f);
			glVertex3f(-40.0f,30.0f,0.0f);
		glEnd();
		glColor3f(1.0f,1.0f,1.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_woodTextureId);
		glBegin(GL_QUADS); 
			glTexCoord2f(0.0, 0.0); glVertex3f(-20.0f,-20.0f,0.0f);
			glTexCoord2f(2.0, 0.0); glVertex3f(20.0f,-20.0f,0.0f);
			glTexCoord2f(2.0, 2.0); glVertex3f(20.0f,20.0f,0.0f);
			glTexCoord2f(0.0, 2.0); glVertex3f(-20.0f,20.0f,0.0f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glColor4f(1.0,1.0,1.0,1.0);
		//Paper Stuff
		glPushMatrix();
		glRotatef(15.0,0.0,0.0,1.0);
		glBegin(GL_QUADS);
			glVertex3f(5.0,10.0,0.0);
			glVertex3f(5.0,-10.0,0.0);
			glVertex3f(-5.0,-10.0,0.0);
			glVertex3f(-5.0,10.0,0.0);
		glEnd();
		
		drawLines();
		glPopMatrix();
		glEndList();
	}
	
//	char * str = "FPS: " + (char) fps;
////	glPushMatrix();
//		glColor3f(1.0,1.0,1.0);
//		glRasterPos2i(270, m_windowHeight/2);
//		glPushAttrib(GL_LIST_BIT);
//			glListBase(fontBase - 32);
//			glCallLists(strlen(str), GL_UNSIGNED_BYTE, str);
//		glPopAttrib();
//	//glPopMatrix();

}

void OpenGLRenderer::drawLines()
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
		for(float i = 0; i < 100; i++)
		{
			glVertex3f(i,-100.0,0.0);
			glVertex3f(i,100.0,0.0);
			glVertex3f(-i,-100.0,0.0);
			glVertex3f(-i,100.0,0.0);
		}
		glColor3f(0.0,1.0,0.0);
		for(float i = 0; i < 100; i++)
		{
			glVertex3f(-100.0,i,0.0);
			glVertex3f(100.0,i,0.0);
			glVertex3f(-100.0,-i,0.0);
			glVertex3f(100.0,-i,0.0);
		}

	glEnd();
}

void OpenGLRenderer::AttachToGame(Avant::GameEngine *gengine)
{
	m_gameEngine = gengine;
}

bool OpenGLRenderer::checkExtension(char* extName)
{
	char* extList = (char*) glGetString(GL_EXTENSIONS);

	if(!extList || !extName)
		return false;

	while(*extList)
	{
		unsigned int firstExtLength = strcspn(extList, " ");

		if(strlen(extName) == firstExtLength && strncmp(extName, extList, firstExtLength) == 0)
		{
			return true;
		}

		extList += firstExtLength + 1;
	}

	return false;
}

unsigned int OpenGLRenderer::getFontBase()
{
	return fontBase;
}

	//Extension example
	//
	//void (APIENTRY * pglActiveTextureARB) (GLenum) = NULL;
	//if(checkExtension("GL_ARB_multitexture"))
	//{
	//	pglActiveTextureARB = (void (APIENTRY *) (GLenum texUnit))
	//		wglGetProcAddress("glActiveTextureARB");

	//}
