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
            "in vec4 vColor;                           \n"
            "out vec4 color;                           \n"
            "uniform mat4 matrix;                      \n"
            "void main() {                             \n"
            "   color = vColor;                        \n"
           "   gl_Position = matrix * vPosition;      \n"
            "}                                         \n";
    /*
     *  这里声明了一个matrix变量，使用了uniform存储限制符，
     *  表明该变量不会在处理过程中发生变化，
     *  着色器无法写入到uniform变量，也无法改变它的值。
     *  可以通过setUniformValue（)函数来为uniform变量设置值。
     *  最后在着色器main（）函数中进行了矩阵与顶点的乘法运算，
     * 注意，矩阵应该在左侧而顶点在右侧。现在运行程序就已经可以看到3D立体效果了。
    */
    vshader->compileSourceCode(vsrc);
    // 创建片段着色器
    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    const char *fsrc =
            "in vec4 color;                             \n"
             "out vec4 fColor;                           \n"
            "void main() {                              \n"
            "   fColor = color;                         \n"
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
    int h = height();
    int side = qMin(w, h);
    glViewport((w-side)/2, (h-side)/2, side, side);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //顶点位置
//    GLfloat vertices[] = {//每行一个顶点位置
//        -0.8f, 0.8f,    //当指定XY其他俩个值 自动0 1
//        -0.8f, -0.8f,
//        0.8f, -0.8f,
//        0.8f, 0.8f
//    };
    GLfloat vertices[2][4][3] = {   // 该数组每行指定了4个顶点(即一个正方形面),每个顶点由3个元素组成,因为要设置3D效果,所以每个顶点都指定了Z轴坐标。
            { {-0.8f, 0.8f, 0.8f}, {-0.8f, -0.8f, 0.8f}, {0.8f, -0.8f, 0.8f}, {0.8f, 0.8f, 0.8f} },
            { {0.8f, 0.8f, 0.8f}, {0.8f, -0.8f, 0.8f}, {0.8f, -0.8f, -0.8f}, {0.8f, 0.8f, -0.8f} }
        };
    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, 48*sizeof(GLfloat));

    GLuint vPosition = static_cast<GLuint>(program->attributeLocation("vPosition"));
    program->setAttributeBuffer(static_cast<GLint>(vPosition), GL_FLOAT, 0, 3, 0);
    glEnableVertexAttribArray(vPosition);

    // 顶点颜色
//    GLfloat colors[] = {
//        1.0f, 0.0f, 0.0f,
//        0.0f, 1.0f, 0.0f,
//        0.0f, 0.0f, 1.0f,
//        1.0f, 1.0f, 1.0f
//    };
    GLfloat colors[2][4][3] = {
            { {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f} },
            { {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f} }
        };
    vbo.write(24*sizeof(GLfloat), colors, 24*sizeof(GLfloat));
    GLuint vColor = static_cast<GLuint>(program->attributeLocation("vColor"));
    program->setAttributeBuffer(static_cast<GLint>(vColor), GL_FLOAT, 24*sizeof(GLfloat), 3, 0);
    glEnableVertexAttribArray(vColor);

    QMatrix4x4 matrix;
    matrix.perspective(45.0f, static_cast<GLfloat>(w) / h, 0.1f, 100.0f);
    matrix.translate(0, 0, -3);
    matrix.rotate(-60, 0, 1, 0);    ////绕Y轴逆时针旋转
    program->setUniformValue("matrix", matrix);
    /*
     * 第一次绘制用去了4个顶点,所以第2次调用时设置了起始位置(即第2个参数的值) 为4。
     * 现在已经绘制出了立方体两个相邻的面,但是运行程序发现,因为角度问题只能 看到前面的面。
     * 下面通过使用透视投影矩阵对顶点进行变换来改变显示图形的角度。
     *  QMatrix4x4类可以表示一个3D空间中的4×4变换矩阵，
     *  perspective（)函数用来设置透视投影矩阵，
     *      这里设置了视角为45°，
     *      纵横比为窗口的纵横比，
     *      最近的位置为0.1，
     *      最远的位置为100。
     *  然后使用translate（）函数平移X、Y和Z轴，这里将Z轴平移-3即向屏幕里移动。
     *  rotate（)可以设置旋转角度，4个参数分别用来设置角度和X、Y、Z轴，比如这里将Y轴设置为1，
     *      就是绕Y轴旋转，角度为一60，也就是逆时针旋转60°；
     *      如果角度为正值，则就是顺时针旋转。
     *  最后使用setUniformValue()函数将矩阵关联到顶点着色器的matrix变量
    */
    // 绘制
    //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    //这里要绘制两个面,所以用for()函数调用了2次 gIDrawArrays()函数进行绘制,
    for(int i=0; i<2; i++)
            glDrawArrays(GL_TRIANGLE_FAN, i*4, 4);
}


void MyOpenGLWidget::resizeGL(int /*width*/, int /*height*/)
{

}
