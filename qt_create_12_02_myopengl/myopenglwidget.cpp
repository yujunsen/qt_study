#include "myopenglwidget.h"
#include <QOpenGLShaderProgram>

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{

}

void MyOpenGLWidget::initializeGL()
{
    // 为当前环境初始化OpenGL函数
    initializeOpenGLFunctions();
    // 创建顶点着色器
    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    const char *vsrc =
            "in vec4 vPosition;                      \n"    //in存储限制符表明了数据进入着色器的流向,与其对应的是out存储限制符 vPosition用于获取外部输入的顶点数据
            "void main() {                             \n"
            "   gl_Position = vPosition;\n" //将顶点位置复制到顶点的指定输出位置gl_Position
            "}                                         \n";
    vshader->compileSourceCode(vsrc);
    // 创建片段着色器
    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    const char *fsrc =
            "void main() {                              \n"
            "   gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
            "}                                          \n";
    fshader->compileSourceCode(fsrc);
     // 创建着色器程序
    program = new QOpenGLShaderProgram;
    program->addShader(vshader);
    program->addShader(fshader);
    program->link();
    program->bind();
}
/*
    这里首先调用 QOpenGLFunctions::initializeOpenGLFunctions()对 OpenGL函数进行了初始化,
    这样 QOpenGLFunctions中的函数只能在当前环境中使用。然后进行了看色器的相关设置。
    使用QOpenGlLShader创建 了一顶点着色器 和一片段着色器，
    并使用compileSourceCode()函数为着色器设置了源码并进行了编译。
    下面创建了着色器程序QOpenGLShaderProgram对象，
    使用addShader()将前面已经编译好的着色器添加进来，
    然后调用link(）函数将所有加入到程序中的着色器链接到一起，
    最后调用bind（）函数将该着色器程序绑定到当前OpenGL环境中。
*/
void MyOpenGLWidget::paintGL()
{
    int w = width();
    int h = width();
    int side = qMin(w, h);
    glViewport((w-side)/2, (h-side)/2, side, side);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //顶点位置
    GLfloat vertices[] = {//每行一个顶点位置
        -0.8f, 0.8f,    //当指定XY其他俩个值 自动0 1
        -0.8f, -0.8f,
        0.8f, -0.8f,
        0.8f, 0.8f
    };
    //attributeLocation可以反回变量在着色器程序参数列表中的位置,这里获取了 vPosition的位置
    GLuint vPosition = static_cast<GLuint>(program->attributeLocation("vPosition"));
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, vertices);   //将 vPosition与顶点数组 vertices进行关联
    glEnableVertexAttribArray(vPosition);
    /*
     * void QOpenGLFunctions::glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr)
     * index参数就是要输入变量的位置索引
     * size表示每个顶点需要更新的分量数目，例如，这里vertices每行只有2个值，所以size为2
     * type指定了数组中元素的类型，例如，这里vertices是GLfloat 类型的，所以这里type为Gl.float
     * normalized设置顶点数据在存储前是否需要进行归一化，这里设置为否
     * stride是数组中每两个元素之间的大小偏移值，一般设置为0即可
     * pointer设置顶点数组指针或者缓存内的偏移量，这里使用了顶点数组，所以直接设置为vertices即可
    */
    // 绘制
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void MyOpenGLWidget::resizeGL(int /*width*/, int /*height*/)
{

}
