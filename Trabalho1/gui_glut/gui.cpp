#include "gui.h"

GUI::GUI(int width, int height, displayFunction dFunction, keyFunction kFunction, const char *title) {
    wTitle = title;
    wWidth = width;
    wHeight = height;
    display = dFunction;
    key = kFunction;

    GLUTInit();

    GLInit();

    glutMainLoop();
}

void GUI::GLUTInit()
{
    int argc = 0; char **argv = NULL;
    glutInit(&argc, argv);
    glutInitWindowSize(wWidth,wHeight);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    id = glutCreateWindow(wTitle);

    glutReshapeFunc(glutGUI::resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(glutGUI::idle);
    glutMouseFunc(glutGUI::mouseButton);
    glutMotionFunc(glutGUI::mouseMove);
}

void GUI::GLInit()
{
    glClearColor(0.6,0.6,0.0,1.0); //define a cor para limpar a imagem (cor de fundo)

    glEnable(GL_LIGHTING); //habilita iluminacao (chamada no setLight)
    //glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_CULL_FACE); //nao mostra as faces dos dois "lados" (frente [anti-horaria] e tras [horaria])
    //glCullFace(GL_BACK); //define qual "lado" da face nao sera mostrado (padrao = nao mostrar a de tras)
    glEnable(GL_NORMALIZE); //mantem a qualidade da iluminacao mesmo quando glScalef eh usada

    glShadeModel(GL_SMOOTH);
    //glShadeModel(GL_FLAT);

    glEnable( GL_LINE_SMOOTH );
    //glLineWidth( 1.0 );
    //glEnable( GL_POLYGON_SMOOTH ); //tem que modificar a maneira de fazer o blend ( GL_BLEND e GL_ALPHA )

    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);

    glEnable(GL_BLEND); //habilita a transparencia
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

GUI::~GUI(){
    glutDestroyWindow(id);
}

void GUI::setTitle(const char *title)
{
    wTitle = title;
    glutSetWindowTitle(wTitle);
}

void GUI::setDimensions(int width, int height) {
    wWidth = width;
    wHeight = height;
    glutReshapeWindow(wWidth,wHeight);
}

void GUI::setDisplay(displayFunction dFunction) {
    display = dFunction;
    glutDisplayFunc(display);
}

void GUI::setKey(keyFunction kFunction) {
    key = kFunction;
    glutKeyboardFunc(key);
}

//using namespace glutGUI;

void GUI::displayInit()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa a imagem com a cor de fundo

    const float ar = glutGUI::height>0 ? (float) glutGUI::width / (float) glutGUI::height : 1.0;
    const float w = glutGUI::width;
    const float h = glutGUI::height;
    const float orthof = 0.003; //orthoFactor

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (glutGUI::perspective)
        gluPerspective(30.,ar,0.1,1000.);
    else
        glOrtho(-orthof*w,orthof*w,-orthof*h,orthof*h,0.0,100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //viewport unica
    glViewport(0, 0, glutGUI::width, glutGUI::height);
        glLoadIdentity();
        gluLookAt(glutGUI::cam->e.x,glutGUI::cam->e.y,glutGUI::cam->e.z, glutGUI::cam->c.x,glutGUI::cam->c.y,glutGUI::cam->c.z, glutGUI::cam->u.x,glutGUI::cam->u.y,glutGUI::cam->u.z);

    GUI::setLight(7,0,4,0,true,false,true);
}

void GUI::displayEnd()
{
    glutSwapBuffers();
}

void GUI::keyInit(unsigned char key, int x, int y)
{
    glutGUI::defaultKey(key,x,y);
}

void GUI::setLight(int id, float posx, float posy, float posz, bool onOffKeyDefault, bool attenuated, bool low, bool hidden, bool pontual, bool spot, bool onOffUserControl) {
    if (!onOffKeyDefault) glutGUI::enabled_light[id] = onOffUserControl;
    glutGUI::hidden_light[id] = hidden;
    glutGUI::pontual_light[id] = pontual;
    glutGUI::spot_light[id] = spot;
    //habilita/desabilita luz
    if (glutGUI::iluminacao && glutGUI::enabled_light[id]) glEnable(GL_LIGHT0+id);
    else glDisable(GL_LIGHT0+id);
    //definindo intensidades de cor da luz
    GLfloat light_ambient[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[]  = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat light_specular[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    if (low) {
        light_ambient[0] = light_ambient[1] = light_ambient[2] = 0.02f;
        light_diffuse[0] = light_diffuse[1] = light_diffuse[2] = 0.4f;
        light_specular[0] = light_specular[1] = light_specular[2] = 0.5f;
    }
    glLightfv(GL_LIGHT0+id, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0+id, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0+id, GL_SPECULAR, light_specular);
    //posicionando a luz
    GLfloat light_position[] = { posx + glutGUI::lx, posy + glutGUI::ly, posz + glutGUI::lz, 1.0f }; //4o parametro: 0.0 - luz no infinito, 1.0 - luz pontual
        if (!glutGUI::pontual_light[id]) light_position[3] = 0.0f;
    glLightfv(GL_LIGHT0+id, GL_POSITION, light_position);
    //desenha uma esfera representando a luz
    if (glutGUI::iluminacao && glutGUI::enabled_light[id] && !glutGUI::hidden_light[id]) {
        glDisable(GL_LIGHTING);
        glColor4f(1.0,1.0,1.0,1.0);
        glPushMatrix();
            glTranslatef(light_position[0],light_position[1],light_position[2]);
            glutSolidSphere(0.05,glutGUI::slices,glutGUI::stacks);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    }
    //desenha uma linha do (0,0,0) ate a posicao da luz
    if (glutGUI::iluminacao && glutGUI::enabled_light[id] && glutGUI::trans_luz) {
        glDisable(GL_LIGHTING);
        glColor4f(1.0,1.0,1.0,1.0);
        glBegin(GL_LINES);
            glVertex3f(0,0,0);
            glVertex4fv(light_position);
        glEnd();
        glEnable(GL_LIGHTING);
    }
    //spot_light
    if (glutGUI::spot_light[id]) {
        const GLfloat light_direction[] = { 0.0f, 0.0f, -1.0f, 1.0f }; //{ -(2.0f + lx), -(5.0f + ly), -(5.0f + lz), 1.0f };
        glLightfv(GL_LIGHT0+id, GL_SPOT_DIRECTION, light_direction);
        glLightf(GL_LIGHT0+id, GL_SPOT_CUTOFF, glutGUI::spot_angle);
    } else {
        glLightf(GL_LIGHT0+id, GL_SPOT_CUTOFF, 180.0);
    }
    //attenuation
    if (attenuated) {
        glLightf(GL_LIGHT0+id, GL_CONSTANT_ATTENUATION, 2.0);
        glLightf(GL_LIGHT0+id, GL_LINEAR_ATTENUATION, 1.0);
        glLightf(GL_LIGHT0+id, GL_QUADRATIC_ATTENUATION, 0.5);
    } else {
        glLightf(GL_LIGHT0+id, GL_CONSTANT_ATTENUATION, 1.0);
        glLightf(GL_LIGHT0+id, GL_LINEAR_ATTENUATION, 0.0);
        glLightf(GL_LIGHT0+id, GL_QUADRATIC_ATTENUATION, 0.0);
    }
}

void GUI::setColor(float r, float g, float b, float a, bool specular) {
    GLfloat mat_ambient[]    = { 0.6*r, 0.6*g, 0.6*b, a };
    GLfloat mat_diffuse[]    = { r, g, b, a };
    GLfloat mat_specular[]   = { 0.0f, 0.0f, 0.0f, a };
        if (specular) mat_specular[0] = mat_specular[1] = mat_specular[2] = 1.0f; //0.5f;
    GLfloat high_shininess[] = { 100.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void GUI::glShearXf(float shY, float shZ)
{
    double transform[16] = {
                            1.0,    shY,    shZ,    0.0,
                            0.0,    1.0,    0.0,    0.0,
                            0.0,    0.0,    1.0,    0.0,
                            0.0,    0.0,    0.0,    1.0
                         };
    glMultTransposeMatrixd( transform );
}

void GUI::glShearYf(float shX, float shZ)
{
    double transform[16] = {
                            1.0,    0.0,    0.0,    0.0,
                            shX,    1.0,    shZ,    0.0,
                            0.0,    0.0,    1.0,    0.0,
                            0.0,    0.0,    0.0,    1.0
                         };
    glMultTransposeMatrixd( transform );
}

void GUI::glShearZf(float shX, float shY)
{
    double transform[16] = {
                            1.0,    0.0,    0.0,    0.0,
                            0.0,    1.0,    0.0,    0.0,
                            shX,    shY,    1.0,    0.0,
                            0.0,    0.0,    0.0,    1.0
                         };
    glMultTransposeMatrixd( transform );
}

void GUI::glShearXYf(float shX, float shY)
{
    double transform[16] = {
                            1.0,    0.0,    shX,    0.0,
                            0.0,    1.0,    shY,    0.0,
                            0.0,    0.0,    1.0,    0.0,
                            0.0,    0.0,    0.0,    1.0
                         };
    glMultTransposeMatrixd( transform );
}

void GUI::glShearXZf(float shX, float shZ)
{
    double transform[16] = {
                            1.0,    shX,    0.0,    0.0,
                            0.0,    1.0,    0.0,    0.0,
                            0.0,    shZ,    1.0,    0.0,
                            0.0,    0.0,    0.0,    1.0
                         };
    glMultTransposeMatrixd( transform );
}

void GUI::glShearYZf(float shY, float shZ)
{
    double transform[16] = {
                            1.0,    0.0,    0.0,    0.0,
                            shY,    1.0,    0.0,    0.0,
                            shZ,    0.0,    1.0,    0.0,
                            0.0,    0.0,    0.0,    1.0
                         };
    glMultTransposeMatrixd( transform );
}

void GUI::glReflectPlaneYZf()
{
    double transform[16] = {
                           -1.0,    0.0,    0.0,    0.0,
                            0.0,    1.0,    0.0,    0.0,
                            0.0,    0.0,    1.0,    0.0,
                            0.0,    0.0,    0.0,    1.0
                         };
    glMultTransposeMatrixd( transform );
}

void GUI::glReflectPlaneXZf()
{
    double transform[16] = {
                            1.0,    0.0,    0.0,    0.0,
                            0.0,   -1.0,    0.0,    0.0,
                            0.0,    0.0,    1.0,    0.0,
                            0.0,    0.0,    0.0,    1.0
                         };
    glMultTransposeMatrixd( transform );
}

void GUI::glReflectPlaneXYf()
{
    double transform[16] = {
                            1.0,    0.0,    0.0,    0.0,
                            0.0,    1.0,    0.0,    0.0,
                            0.0,    0.0,   -1.0,    0.0,
                            0.0,    0.0,    0.0,    1.0
                         };
    glMultTransposeMatrixd( transform );
}

void GUI::drawSphere(float x, float y, float z, float radius)
{
    GLUquadric* quad = gluNewQuadric();
      gluQuadricDrawStyle(quad, GLU_FILL);
      gluQuadricNormals(quad, GLU_SMOOTH);			// Create Smooth Normals
      gluQuadricTexture(quad, GL_TRUE);		  		// Create Texture Coords

    //sphere
        glPushMatrix();
            glTranslated(x,y,z);
            //glutSolidSphere(radius,slices,stacks);
            gluSphere(quad,radius,glutGUI::slices,glutGUI::stacks);
        glPopMatrix();

        gluDeleteQuadric(quad);
}

void GUI::drawQuad(float width, float height, float discrWidth, float discrHeight, float texWidth, float texHeight, bool inverted)
{
    int nWidth = width/discrWidth;
    int nHeight = height/discrHeight;
    discrWidth = width/nWidth; //correcao necessaria, pois, caso width/discrWidth nao seja inteiro, nWidth*discrWidth (feito pelo for) nao completara exatamente a width
    discrHeight = height/nHeight; //correcao necessaria, pois, caso height/discrHeight nao seja inteiro, nHeight*discrHeight (feito pelo for) nao completara exatamente a height
    float discrTexWidth = texWidth*(discrWidth/width);
    float discrTexHeight = texHeight*(discrHeight/height);
    for(float i=-0.5*(width/discrWidth);i<0.5*(width/discrWidth);i++) {
        for(float j=-0.5*(height/discrHeight);j<0.5*(height/discrHeight);j++) {
            glPushMatrix();
                if (inverted) glRotatef(180,1,0,0);
                glTranslatef(i*discrWidth,0.0,j*discrHeight);
                glBegin( GL_QUADS );
                    glNormal3f(0.,1.,0.);
                        glTexCoord2f(     i*discrTexWidth, (j+1)*discrTexHeight); glVertex3f(        0.0,0.0,+discrHeight);
                        glTexCoord2f( (i+1)*discrTexWidth, (j+1)*discrTexHeight); glVertex3f(+discrWidth,0.0,+discrHeight);
                        glTexCoord2f( (i+1)*discrTexWidth,     j*discrTexHeight); glVertex3f(+discrWidth,0.0,         0.0);
                        glTexCoord2f(     i*discrTexWidth,     j*discrTexHeight); glVertex3f(        0.0,0.0,         0.0);
                glEnd();
            glPopMatrix();
        }
    }
}

void GUI::drawOriQuad(float angle, float ex, float ey, float ez, float width, float height, float discrWidth, float discrHeight, float texWidth, float texHeight, bool inverted)
{
    glPushMatrix();
        glRotatef(angle,ex,ey,ez);
        drawQuad(width,height,discrWidth,discrHeight,texWidth,texHeight,inverted);
    glPopMatrix();
}

void GUI::drawQuadBox(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax, float discrWidth, float discrHeight, bool inverted)
{
    float xmed = (xmin + xmax)/2.0;
    float ymed = (ymin + ymax)/2.0;
    float zmed = (zmin + zmax)/2.0;

    float xdiff = xmax - xmin;
    float ydiff = ymax - ymin;
    float zdiff = zmax - zmin;

    //bottom
    glPushMatrix();
        glTranslatef(xmed,ymin,zmed);
        drawOriQuad(180,1,0,0,xdiff,zdiff,discrWidth,discrHeight,xdiff,zdiff,inverted);
    glPopMatrix();

    //top
    glPushMatrix();
        glTranslatef(xmed,ymax,zmed);
        drawOriQuad(0,1,0,0,xdiff,zdiff,discrWidth,discrHeight,xdiff,zdiff,inverted);
    glPopMatrix();

    //right
    glPushMatrix();
        glTranslatef(xmax,ymed,zmed);
        drawOriQuad(-90,0,0,1,ydiff,zdiff,discrWidth,discrHeight,ydiff,zdiff,inverted);
    glPopMatrix();

    //left
    glPushMatrix();
        glTranslatef(xmin,ymed,zmed);
        drawOriQuad(90,0,0,1,ydiff,zdiff,discrWidth,discrHeight,ydiff,zdiff,inverted);
    glPopMatrix();

    //back
    glPushMatrix();
        glTranslatef(xmed,ymed,zmin);
        drawOriQuad(-90,1,0,0,xdiff,ydiff,discrWidth,discrHeight,xdiff,ydiff,inverted);
    glPopMatrix();

    //front
    glPushMatrix();
        glTranslatef(xmed,ymed,zmax);
        drawOriQuad(90,1,0,0,xdiff,ydiff,discrWidth,discrHeight,xdiff,ydiff,inverted);
    glPopMatrix();
}

void GUI::drawBox(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax, bool inverted)
{
//    if (inverted) glCullFace(GL_FRONT);
//    else glCullFace(GL_BACK);

    if (!inverted) {
        float um = 1.0;

        glBegin(GL_QUADS);
          glNormal3f(0.,0.,-um);
          glTexCoord2f(0.0f, 0.0f); glVertex3f(xmin, ymin, zmin);
          glTexCoord2f(1.0f, 0.0f); glVertex3f(xmin, ymax, zmin);
          glTexCoord2f(1.0f, 1.0f); glVertex3f(xmax, ymax, zmin);
          glTexCoord2f(0.0f, 1.0f); glVertex3f(xmax, ymin, zmin);
        glEnd();

        glBegin(GL_QUADS);
          glNormal3f(um,0.,0.);
          glTexCoord2f(0.0f, 0.0f); glVertex3f(xmax, ymin, zmin);
          glTexCoord2f(1.0f, 0.0f); glVertex3f(xmax, ymax, zmin);
          glTexCoord2f(1.0f, 1.0f); glVertex3f(xmax, ymax, zmax);
          glTexCoord2f(0.0f, 1.0f); glVertex3f(xmax, ymin, zmax);
        glEnd();

        glBegin(GL_QUADS);
          glNormal3f(0.,0.,um);
          glTexCoord2f(0.0f, 0.0f); glVertex3f(xmax, ymin, zmax);
          glTexCoord2f(1.0f, 0.0f); glVertex3f(xmax, ymax, zmax);
          glTexCoord2f(1.0f, 1.0f); glVertex3f(xmin, ymax, zmax);
          glTexCoord2f(0.0f, 1.0f); glVertex3f(xmin, ymin, zmax);
        glEnd();

        glBegin(GL_QUADS);
          glNormal3f(-um,0.,0.);
          glTexCoord2f(0.0f, 0.0f); glVertex3f(xmin, ymin, zmax);
          glTexCoord2f(1.0f, 0.0f); glVertex3f(xmin, ymax, zmax);
          glTexCoord2f(1.0f, 1.0f); glVertex3f(xmin, ymax, zmin);
          glTexCoord2f(0.0f, 1.0f); glVertex3f(xmin, ymin, zmin);
        glEnd();

        glBegin(GL_QUADS);
          glNormal3f(0.,um,0.);
          glTexCoord2f(0.0f, 0.0f); glVertex3f(xmin, ymax, zmin);
          glTexCoord2f(1.0f, 0.0f); glVertex3f(xmin, ymax, zmax);
          glTexCoord2f(1.0f, 1.0f); glVertex3f(xmax, ymax, zmax);
          glTexCoord2f(0.0f, 1.0f); glVertex3f(xmax, ymax, zmin);
        glEnd();

        glBegin(GL_QUADS);
          glNormal3f(0.,-um,0.);
          glTexCoord2f(0.0f, 0.0f); glVertex3f(xmax, ymin, zmin);
          glTexCoord2f(1.0f, 0.0f); glVertex3f(xmax, ymin, zmax);
          glTexCoord2f(1.0f, 1.0f); glVertex3f(xmin, ymin, zmax);
          glTexCoord2f(0.0f, 1.0f); glVertex3f(xmin, ymin, zmin);
        glEnd();
    } else {
        float um = -1.0;

        glBegin(GL_QUADS);
          glNormal3f(0.,0.,-um);
          glTexCoord2f(0.0f, 0.0f); glVertex3f(xmin, ymin, zmin);
          glTexCoord2f(0.0f, 1.0f); glVertex3f(xmax, ymin, zmin);
          glTexCoord2f(1.0f, 1.0f); glVertex3f(xmax, ymax, zmin);
          glTexCoord2f(1.0f, 0.0f); glVertex3f(xmin, ymax, zmin);
        glEnd();

        glBegin(GL_QUADS);
          glNormal3f(um,0.,0.);
          glTexCoord2f(0.0f, 0.0f); glVertex3f(xmax, ymin, zmin);
          glTexCoord2f(0.0f, 1.0f); glVertex3f(xmax, ymin, zmax);
          glTexCoord2f(1.0f, 1.0f); glVertex3f(xmax, ymax, zmax);
          glTexCoord2f(1.0f, 0.0f); glVertex3f(xmax, ymax, zmin);
        glEnd();

        glBegin(GL_QUADS);
          glNormal3f(0.,0.,um);
          glTexCoord2f(0.0f, 0.0f); glVertex3f(xmax, ymin, zmax);
          glTexCoord2f(0.0f, 1.0f); glVertex3f(xmin, ymin, zmax);
          glTexCoord2f(1.0f, 1.0f); glVertex3f(xmin, ymax, zmax);
          glTexCoord2f(1.0f, 0.0f); glVertex3f(xmax, ymax, zmax);
        glEnd();

        glBegin(GL_QUADS);
          glNormal3f(-um,0.,0.);
          glTexCoord2f(0.0f, 0.0f); glVertex3f(xmin, ymin, zmax);
          glTexCoord2f(0.0f, 1.0f); glVertex3f(xmin, ymin, zmin);
          glTexCoord2f(1.0f, 1.0f); glVertex3f(xmin, ymax, zmin);
          glTexCoord2f(1.0f, 0.0f); glVertex3f(xmin, ymax, zmax);
        glEnd();

        glBegin(GL_QUADS);
          glNormal3f(0.,um,0.);
          glTexCoord2f(0.0f, 0.0f); glVertex3f(xmin, ymax, zmin);
          glTexCoord2f(0.0f, 1.0f); glVertex3f(xmax, ymax, zmin);
          glTexCoord2f(1.0f, 1.0f); glVertex3f(xmax, ymax, zmax);
          glTexCoord2f(1.0f, 0.0f); glVertex3f(xmin, ymax, zmax);
        glEnd();

        glBegin(GL_QUADS);
          glNormal3f(0.,-um,0.);
          glTexCoord2f(0.0f, 0.0f); glVertex3f(xmax, ymin, zmin);
          glTexCoord2f(0.0f, 1.0f); glVertex3f(xmin, ymin, zmin);
          glTexCoord2f(1.0f, 1.0f); glVertex3f(xmin, ymin, zmax);
          glTexCoord2f(1.0f, 0.0f); glVertex3f(xmax, ymin, zmax);
        glEnd();
    }
}

void GUI::drawScaledBox(float scale, float xmin, float ymin, float zmin, float xmax, float ymax, float zmax, bool inverted)
{
    glPushMatrix();
        glTranslatef((xmin+xmax)/2.0,(ymin+ymax)/2.0,(zmin+zmax)/2.0);
        glScalef(scale,scale,scale);
        glTranslatef(-(xmin+xmax)/2.0,-(ymin+ymax)/2.0,-(zmin+zmax)/2.0);
        GUI::drawBox(xmin, ymin, zmin, xmax, ymax, zmax, inverted);
    glPopMatrix();
}

//desenha eixos do sistema de coordenadas atual (global, caso nao esteja influenciado por transformacoes)
void GUI::drawOrigin(float tamanho)
{
    glPushMatrix();
        if (glutGUI::draw_eixos) Desenha::drawEixos( tamanho );
    glPopMatrix();
}

void GUI::drawCamera(float tamanho) {
    GLUquadricObj *quad = gluNewQuadric();

    glPushMatrix();
        Desenha::drawBox(-tamanho,-tamanho,-tamanho,tamanho,tamanho,tamanho);
        glTranslatef(0,0,-2*tamanho);
        Desenha::gluClosedCylinder(quad,tamanho,tamanho/2,tamanho,glutGUI::slices,glutGUI::stacks);
    glPopMatrix();

    gluDeleteQuadric( quad );
}

void GUI::draw3ds(Model3DS &model3DS, float tx, float ty, float tz,
                                      float ax, float ay, float az,
                                      float sx, float sy, float sz)
{
    glPushMatrix();
        //transformacoes do objeto ja desenhado de acordo com o seu sistema local
        glTranslatef(tx,ty,tz);
        glRotatef(ax,1,0,0);
        glRotatef(ay,0,1,0);
        glRotatef(az,0,0,1);
        glScalef(sx,sy,sz);
        //sist local
        //drawOrigin(0.5);
        //trazendo para a origem, alinhando com os eixos locais e ajustando para um tamanho adequado (Sl.Rl.Tl)
        float s = 0.0005;
        glScalef(s,s,s);
        glRotatef(-90,1,0,0);
        model3DS.draw();
    glPopMatrix();
}

void GUI::drawFloor(float width, float height, float discrWidth, float discrHeight, float texWidth, float texHeight)
{
    //glDisable(GL_CULL_FACE);

    //int discr = 1;
    //Desenha::drawGrid( width/discr, 0, height/discr, discr );

    glPushMatrix();
        glTranslated(0.,-0.0001,0.);
        drawQuad(width,height,discrWidth,discrHeight,texWidth,texHeight);
    glPopMatrix();

    //glEnable(GL_CULL_FACE);
}
