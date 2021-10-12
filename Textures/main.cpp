//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "Object_3D.h"
#include <FreeImage.h>
//-----------------------------------------------------------------------------


class myWindow : public cwc::glutWindow
{
protected:
   cwc::glShaderManager SM;
   cwc::glShader *shader;
   GLuint ProgramObject;
   clock_t time0,time1;
   float timer010;  // timer counting 0->1->0
   bool bUp;        // flag if counting up or down.
   Object_3D* scene[6];
   GLuint texid;
   cwc::glShader* text;
   float movimientoC;
   float movimientoViejo;
public:
	myWindow(){}


    void initialize_textures(void)
    {
        GLubyte* data = 0;
        glGenTextures(1, &texid);
        glBindTexture(GL_TEXTURE_2D, texid);
        glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        // Loading JPG file
        FIBITMAP* bitmap = FreeImage_Load(
            FreeImage_GetFileType("./mallas/lava.jpg", 0),
            "./mallas/lava.jpg");
        FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
        int nWidth = FreeImage_GetWidth(pImage);
        int nHeight = FreeImage_GetHeight(pImage);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
            0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));
        FreeImage_Unload(pImage);
        //
        glEnable(GL_TEXTURE_2D);
    }

    

	virtual void OnRender(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
      //timer010 = 0.009; //for screenshot!
      glPushMatrix();
          if (shader) shader->begin();

             glTranslatef(0, 0, -17);
             glRotatef(20, 1, 0, 0);
             //glRotatef(timer010*360, 0, 0.001, 0);
             glRotatef(movimientoC * 360, 0, 0.001, 0);
             glPushMatrix();
             glRotatef(45, 0, 1, 0);
         
             glPushMatrix();
             glScalef(2, 2, 2);
             scene[0]->DibujarMalla(1, 0.8, -1.5);   // House
             glPopMatrix();




             glPushMatrix();
             glScalef(0.5, 0.5, 0.5);
             scene[1]->DibujarMalla(0.8 + movimientoViejo, 1, -0.2);   // Hyde
             glPopMatrix();

             glPushMatrix();
             scene[3]->DibujarMalla(1.5, 1, 0.2);   // Light
             glPopMatrix();

             glPushMatrix();
             glScalef(0.3, 0.3, 0.3);
             scene[2]->DibujarMalla(0.7 + movimientoViejo * 1.2, 1, -0.15);   // Stick
             glPopMatrix();


         
             glPushMatrix();
             const float scale_size = 10.0;
             glScalef(scale_size, scale_size, scale_size);
             scene[5]->DibujarMalla(0, 0, 0);   // Floor
             glPopMatrix();

         glPopMatrix();
      if (shader) shader->end();

      //if (text) text->begin();
      glPushMatrix();
      glScalef(2.5, 2.5, 2.5);
      scene[4]->DibujarMalla(-0.5, 1, 1, texid);   // Tree
      glPopMatrix();
      //if (text) text->end();


      glutSwapBuffers();
      glPopMatrix();

      UpdateTimer();

		Repaint();
	}

	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
	virtual void OnInit()
	{
		glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);

		shader = SM.loadfromFile("vertexshader.txt","fragmentshader.txt"); // load (and compile, link) from file
		if (shader==0) 
         std::cout << "Error Loading, compiling or linking shader\n";
      else
      {
         ProgramObject = shader->GetProgramObject();
      }

        text = SM.loadfromFile("vertextext.txt", "fragtext.txt"); // load (and compile, link) from file
        if (text == 0)
            std::cout << "Error Loading, compiling or linking shader\n";
        else
        {
            ProgramObject = shader->GetProgramObject();
        }





      time0 = clock();
      timer010 = 0.0f;
      bUp = true;
      
      scene[0] = new Object_3D();
      scene[0]->AbrirMalla("./mallas/house.obj");

      scene[1] = new Object_3D();
      scene[1]->AbrirMalla("./mallas/hyde.obj");

      scene[2] = new Object_3D();
      scene[2]->AbrirMalla("./mallas/stick.obj");

      scene[3] = new Object_3D();
      scene[3]->AbrirMalla("./mallas/light.obj");

      scene[4] = new Object_3D();
      scene[4]->AbrirMalla("./mallas/tree.obj");

      scene[5] = new Object_3D();
      scene[5]->AbrirMalla("./mallas/floor.obj");

      initialize_textures();

      movimientoC = 0.0f;
      movimientoViejo = 0.0f;

      DemoLight();

	}

	virtual void OnResize(int w, int h)
   {
      if(h == 0) h = 1;
	   float ratio = 1.0f * (float)w / (float)h;

      glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	
	   glViewport(0, 0, w, h);

      gluPerspective(45,ratio,1,100);
	   glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	   gluLookAt(0.0f,0.0f,4.0f, 
		          0.0,0.0,-1.0,
			       0.0f,1.0f,0.0f);
   }
	virtual void OnClose(void){}
	virtual void OnMouseDown(int button, int x, int y) {}    
	virtual void OnMouseUp(int button, int x, int y) {}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}

	virtual void OnKeyDown(int nKey, char cAscii)
	{       
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close Window!
		}
        else if (cAscii == 'r')
        {
            movimientoC += 0.01;
            if (movimientoC > 1) {
                movimientoC = 0;
            }
        }
        else if (cAscii == 'a') {
            movimientoViejo += 0.3;
        }
        else if (cAscii == 'd') {
            movimientoViejo -= 0.3;
        }
	};


	virtual void OnKeyUp(int nKey, char cAscii)
	{
      if (cAscii == 's')      // s: Shader
         shader->enable();
      else if (cAscii == 'f') // f: Fixed Function
         shader->disable();
	}

   void UpdateTimer()
   {
      time1 = clock();
      float delta = static_cast<float>(static_cast<double>(time1-time0)/static_cast<double>(CLOCKS_PER_SEC));
      delta = delta / 4;
      if (delta > 0.00005f)
      {
         time0 = clock();
         if (bUp)
         {
            timer010 += delta;
            if (timer010>=1.0f) { timer010 = 1.0f; bUp = false;}
         }
         else
         {
            timer010 -= delta;
            if (timer010<=0.0f) { timer010 = 0.0f; bUp = true;}
         }
      }
   }

   void DemoLight(void)
   {
       glEnable(GL_LIGHTING);
       glEnable(GL_LIGHT0);
       glEnable(GL_NORMALIZE);

       // Light model parameters:
       // -------------------------------------------

       GLfloat lmKa[] = { 0.0, 0.0, 0.0, 0.0 };
       glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);

       glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
       glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

       // -------------------------------------------
       // Spotlight Attenuation

       GLfloat spot_direction[] = { 1.0, -1.0, -1.0 };
       GLint spot_exponent = 30;
       GLint spot_cutoff = 180;

       glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
       glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
       glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);

       GLfloat Kc = 1.0;
       GLfloat Kl = 0.0;
       GLfloat Kq = 0.0;

       glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Kc);
       glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
       glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);


       // ------------------------------------------- 
       // Lighting parameters:

       GLfloat light_pos[] = { 0.0f, 5.0f, 5.0f, 1.0f };
       GLfloat light_Ka[] = { 1.0f, 0.5f, 0.5f, 1.0f };
       GLfloat light_Kd[] = { 1.0f, 0.1f, 0.1f, 1.0f };
       GLfloat light_Ks[] = { 1.0f, 1.0f, 1.0f, 1.0f };

       glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
       glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
       glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
       glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

       // -------------------------------------------
       // Material parameters:

       GLfloat material_Ka[] = { 0.5f, 0.0f, 0.0f, 1.0f };
       GLfloat material_Kd[] = { 0.4f, 0.4f, 0.5f, 1.0f };
       GLfloat material_Ks[] = { 0.8f, 0.8f, 0.0f, 1.0f };
       GLfloat material_Ke[] = { 0.1f, 0.0f, 0.0f, 0.0f };
       GLfloat material_Se = 20.0f;

       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
       glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
       glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
       glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
       glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
   }
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
    virtual void OnInit() { std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
    myApplication* pApp = new myApplication;
    myWindow* myWin = new myWindow();

    pApp->run();
    delete pApp;
    return 0;
}

//-----------------------------------------------------------------------------

