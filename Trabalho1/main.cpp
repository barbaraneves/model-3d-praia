#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#include <CameraDistante.h>

/** INCLUDES DOS OBJETOS **/

#include <bamboo.h>
#include <barco.h>
#include <bola.h>
#include <casa.h>
#include <guardasol.h>
#include <palmeira.h>
#include <prancha.h>
#include <trave.h>

vector<Objeto*> objetos;
vector<Camera*> cameras;

int marcaCamera = -1;
int posSelecionado = -1;

int slices = 16;
int stacks = 16;

float trans_obj = false;
float trans_luz = false;

void desenha_camera(float tam) {
    GLUquadricObj *quad = gluNewQuadric();

    glPushMatrix();
        Desenha::drawBox(-tam, -tam, 0.0, tam, tam, 2*tam);
        glTranslated(0, 0, -tam);
        Desenha::gluClosedCylinder(quad, tam, tam/2, tam, slices, stacks);
    glPopMatrix();

    gluDeleteQuadric(quad);
}

/** MÉTODO DESENHAR (VIRTUAL) **/

void desenha() {
    GUI::displayInit();

    GUI::setLight(1, 0, 3, 0, true, false);

    //GUI::setLight(1, 1, 3, 5, true, false);
    //GUI::setLight(2, -1.5, 0.5, -1, true, false);

    //GUI::drawOrigin(1);

    // Areia
    GUI::setColor(1, 1, 0.4);
    GUI::drawFloor(7, 5);

    // Mar
    GUI::setColor(0, 0.9, 1);
    glPushMatrix();
        glTranslated(0, 0.13, -1.5);
        glRotated(8, 1, 0, 0);
        GUI::drawFloor(7, 2);
    glPopMatrix();

    // Céu
    GUI::setColor(0.9, 2, 2);

    // Face da frente
    glPushMatrix();
        glTranslated(0, 2.5, -2.5);
        glRotated(90, 1, 0, 0);
        GUI::drawFloor(7, 5);
    glPopMatrix();

    // Face do lado direito
    glPushMatrix();
        glTranslated(3.77, 2.5, 0);
        glRotated(90, 0, 0, 1);
        GUI::drawFloor(5, 5);
    glPopMatrix();

    // Face do lado esquerdo
    glPushMatrix();
        glTranslated(-3.49, 2.5, 0);
        glRotated(180, 0, 0, 1);
        glRotated(90, 0, 0, 1);
        GUI::drawFloor(5, 5);
    glPopMatrix();

    for (int i = 0; i < objetos.size(); ++i) {
        glPushMatrix();
            objetos[i]->desenha();
        glPopMatrix();
    }

    if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
        objetos[posSelecionado]->t.x += glutGUI::dtx;
        objetos[posSelecionado]->t.y += glutGUI::dty;
        objetos[posSelecionado]->t.z += glutGUI::dtz;

        objetos[posSelecionado]->a.x += glutGUI::dax;
        objetos[posSelecionado]->a.y += glutGUI::day;
        objetos[posSelecionado]->a.z += glutGUI::daz;

        objetos[posSelecionado]->s.x += glutGUI::dsx;
        objetos[posSelecionado]->s.y += glutGUI::dsy;
        objetos[posSelecionado]->s.z += glutGUI::dsz;
    }

//    glutGUI::dtx = 0.0; glutGUI::dty = 0.0; glutGUI::dtz = 0.0;
//    glutGUI::dax = 0.0; glutGUI::day = 0.0; glutGUI::daz = 0.0;
//    glutGUI::dsx = 0.0; glutGUI::dsy = 0.0; glutGUI::dsz = 0.0;

    GUI::displayEnd();
}


/** SALVAR E CARREGAR OBJETOS DE UM VETOR EM ARQUIVO **/

void gerarObjeto(string nome, GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ax, GLfloat ay, GLfloat az, GLfloat sx, GLfloat sy, GLfloat sz, bool selecionado, bool eixo)
{
    if (nome == "Bamboo") {
        objetos.push_back(new Bamboo());
        objetos.back()->salvarObjeto(tx, ty, tz, ax, ay, az, sx, sy, sz, selecionado, eixo);
        cout << "Objeto Bamboo gerado!" << endl;
    } else if (nome == "Barco") {
        objetos.push_back(new Barco());
        objetos.back()->salvarObjeto(tx, ty, tz, ax, ay, az, sx, sy, sz, selecionado, eixo);
        cout << "Objeto Barco gerado!" << endl;
    } else if (nome == "Bola") {
        objetos.push_back(new Bola());
        objetos.back()->salvarObjeto(tx, ty, tz, ax, ay, az, sx, sy, sz, selecionado, eixo);
        cout << "Objeto Bola gerado!" << endl;
    } else if (nome == "Casa") {
        objetos.push_back(new Casa());
        objetos.back()->salvarObjeto(tx, ty, tz, ax, ay, az, sx, sy, sz, selecionado, eixo);
        cout << "Objeto Casa gerado!" << endl;
    } else if (nome == "GuardaSol") {
        objetos.push_back(new GuardaSol());
        objetos.back()->salvarObjeto(tx, ty, tz, ax, ay, az, sx, sy, sz, selecionado, eixo);
        cout << "Objeto Guarda-sol gerado!" << endl;
    } else if (nome == "Palmeira") {
        objetos.push_back(new Palmeira());
        objetos.back()->salvarObjeto(tx, ty, tz, ax, ay, az, sx, sy, sz, selecionado, eixo);
        cout << "Objeto Palmeira gerado!" << endl;
    } else if (nome == "Prancha") {
        objetos.push_back(new Prancha());
        objetos.back()->salvarObjeto(tx, ty, tz, ax, ay, az, sx, sy, sz, selecionado, eixo);
        cout << "Objeto Prancha gerado!" << endl;
    } else if (nome == "Trave") {
        objetos.push_back(new Trave());
        objetos.back()->salvarObjeto(tx, ty, tz, ax, ay, az, sx, sy, sz, selecionado, eixo);
        cout << "Objeto Trave gerado!" << endl;
    }
}

void salvarArquivo()
{
    ofstream arquivo;

    arquivo.open("../cenario_salvo/cenario.txt", ios::app);
    arquivo.clear();

    if (!arquivo.is_open()) {
        cout << "Não foi possível abrir 'cenario.txt' :(" << endl;
    } else {
        for (int i = 0; i < objetos.size(); i++) {
            arquivo << objetos[i]->nomeObjeto << " ";
            arquivo << objetos[i]->t.x << " ";
            arquivo << objetos[i]->t.y << " ";
            arquivo << objetos[i]->t.z << " ";
            arquivo << objetos[i]->a.x << " ";
            arquivo << objetos[i]->a.y << " ";
            arquivo << objetos[i]->a.z << " ";
            arquivo << objetos[i]->s.x << " ";
            arquivo << objetos[i]->s.y << " ";
            arquivo << objetos[i]->s.z << " ";
            arquivo << objetos[i]->selecionado << " ";
            arquivo << objetos[i]->eixos << endl;
        }
    }

    arquivo.close();
}

void carregarArquivo()
{
    ifstream arquivo;

    arquivo.open("../cenario_salvo/cenario.txt", ios::app);

    if (arquivo.is_open()) {
        while (!arquivo.eof()) {
            string nomeObjeto = "";
                GLfloat tx = 0, ty = 0, tz = 0;
                GLfloat ax = 0, ay = 0, az = 0;
                GLfloat sx = 0, sy = 0, sz = 0;
            bool selecionado, eixo;

            arquivo >> nomeObjeto;
            arquivo >> tx >> ty >> tz;
            arquivo >> ax >> ay >> az;
            arquivo >> sx >> sy >> sz;
            arquivo >> selecionado >> eixo;

            cout << nomeObjeto << endl;

            gerarObjeto(nomeObjeto, tx, ty, tz, ax, ay, az, sx, sy, sz, selecionado, eixo);
        }
    } else {
        cout << "Não foi possível abrir 'cenario.txt' :(" << endl;
    }
}

Camera* cam = new CameraDistante();
float savedCamera[9];

bool incluirObjeto = false;
Vetor3D objProj;


/** MÉTODO PARA USO DO TECLADO **/

void teclado(unsigned char key, int x, int y) {

    GUI::keyInit(key, x, y);

    switch (key) {

        /** COMANDOS PADRÃO **/

        case 't':
            glutGUI::trans_obj = !glutGUI::trans_obj;
            break;

        case 'l':
            glutGUI::trans_luz = !glutGUI::trans_luz;
            break;

        // Sair
        case 'q':
            exit(0);

        // Tela cheia
        case 'F':
            glutFullScreen();
            break;

        // Tela 800x600
        case 'f':
            glutReshapeWindow(800, 600);
            break;

        // Seleciona o objeto: passa
        case 'n':
            if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
                objetos[posSelecionado]->selecionado = false;
            }
            posSelecionado++;
            posSelecionado = posSelecionado%objetos.size();
            if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
                objetos[posSelecionado]->selecionado = true;
            }
            break;

        // Seleciona o objeto: volta
        case 'm':
            if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
                objetos[posSelecionado]->selecionado = false;
            }
            posSelecionado--;
            if (posSelecionado < 0) {
                posSelecionado = objetos.size()-1;
            }
            if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
                objetos[posSelecionado]->selecionado = true;
            }
            break;

        // Incluir os objetos do cenário
        case 'o':
            incluirObjeto = !incluirObjeto;
            break;

        // Apaga o objeto selecionado
        case 'a':
            if (incluirObjeto || !incluirObjeto) {
                for (int i = 0; i < objetos.size(); i++) {
                    if (objetos[i]->selecionado) {
                        objetos.erase(objetos.begin()+i);
                    }
                }
            }
            break;

        // Apaga o último objeto do vetor
        case 'u':
            if (incluirObjeto || !incluirObjeto) {
                objetos.pop_back();
            }
            break;

        // Desenha ou não os eixos do sistema local do objeto selecionado
        case 's':
            if (incluirObjeto || !incluirObjeto){
                for (int i = 0; i < objetos.size(); i++) {
                    if (objetos[i]->selecionado) {
                        objetos[i]->eixos = !objetos[i]->eixos;
                    }
                }
            }
            break;

        // Mostra a sombra de um objeto selecionado
        case 'x':
            if (incluirObjeto || !incluirObjeto) {
                for (int i = 0; i < objetos.size(); i++) {
                    if (objetos[i]->selecionado) {

                    }
                }
            }
            break;


        /** SALVAR E CARREGAR EM ARQUIVO **/

        // Salva o cenário
        case 'w':
            if (!incluirObjeto) {
                salvarArquivo();
            }
            break;

        // Carrega o cenário pronto
        case 'W':
            if (!incluirObjeto) {
                cout << "Tamanho do vetor: " << objetos.size() << endl;
                carregarArquivo();
            }
            break;


        /** CÂMERAS **/

        case 'c':
            marcaCamera++;
            if (marcaCamera >= cameras.size()) {
                marcaCamera = 0;
            }

            glutGUI::cam = new CameraDistante(cameras[marcaCamera]->e, cameras[marcaCamera]->c, cameras[marcaCamera]->u);

            break;


        /** OBJETOS **/

        // Barco/navio
        case 'i':
            if (incluirObjeto) {
                objetos.push_back( new Barco() );
            }
            break;

        // Bola
        case 'b':
            if (incluirObjeto) {
                objetos.push_back( new Bola() );
            }
            break;

        // Casa
        case 'h':
            if (incluirObjeto) {
                objetos.push_back( new Casa() );
            }
            break;

        // Guarda-Sol
        case 'g':
            if (incluirObjeto) {
                objetos.push_back( new GuardaSol() );
            }
            break;

        // Bamboo
        case 'd':
            if (incluirObjeto) {
                objetos.push_back( new Bamboo() );
            }
            break;

        // Palmeira
        case 'p':
            if (incluirObjeto) {
                objetos.push_back( new Palmeira() );
            }
            break;

        // Prancha
        case 'r':
            if (incluirObjeto) {
                objetos.push_back( new Prancha() );
            }
            break;

        // Trave
        case 'v':
            if (incluirObjeto) {
                objetos.push_back( new Trave() );
            }
            break;

        default:
            break;
        }
}

int main()
{
    /** MAPA PARA O USUÁRIO **/

    cout << "-------------- MAPA DA PRAIA --------------\n" << endl;

    cout << "-> Comandos de inclusão de objetos:" << endl;
        cout << "   o - Inicializa a inclusão de objetos;" << endl;
        cout << "   d - Bamboo;" << endl;
        cout << "   i - Barco;" << endl;
        cout << "   b - Bola;" << endl;
        cout << "   h - Casa;" << endl;
        cout << "   g - Guarda-sol;" << endl;
        cout << "   p - Palmeira;" << endl;
        cout << "   r - Prancha de surf;" << endl;
        cout << "   v - Trave de futebol;\n" << endl;

    cout << "-> Comandos de interação:" << endl;
        cout << "   F - Tela cheia;" << endl;
        cout << "   f - Tela padrão (800x600);" << endl;
        cout << "   n - Seleciona o objeto;" << endl;
        cout << "   m - Seleciona o objeto seguinte;" << endl;
        cout << "   a - Apaga o objeto selecionado;" << endl;
        cout << "   u - Apaga o último objeto colocado no cenário;" << endl;
        cout << "   s - Mostra os eixos do sistema local do objeto selecionado;" << endl;
        cout << "   S - Apaga os eixos do sistema local do objeto selecionado;" << endl;
        cout << "   t - Translada o objeto;" << endl;
        cout << "   l - Translada a luz;" << endl;
        cout << "   c - Movimenta a câmera pelo cenário;" << endl;
        cout << "   w - Salva o cenário feito;" << endl;
        cout << "   W - Carrega algum cenário;" << endl;
        cout << "   q - Sair (ou apenas pode usar o botão Esc);\n" << endl;


    /** CÂMERAS **/

    cameras.push_back(new CameraDistante(0, 10, -4.7, 0, 0, 0, 0, 1, 0));
    cameras.push_back(new CameraDistante(4.7, 10, 0, 0, 0, 0, 0, 1, 0));
    cameras.push_back(new CameraDistante(15, 5, 15, 0, 0, 0, 0, 1, 0));
    cameras.push_back(new CameraDistante(-15, 5, -15, 0, 0, 0, 0, 1, 0));


    /** INICIALIZAÇÃO **/

    GUI gui = GUI(800, 600, desenha, teclado);
}

