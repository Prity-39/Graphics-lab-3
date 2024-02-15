#include<stdio.h> 
#include<GL/glut.h> 
#include<math.h>

#define pii pair<int, int>

int step, r, angle;
float theta;

const double PI = 3.1416;

void myInit(void);
void display(void);
void reshape(int w, int h);
void DrawCircle(void);
void drawline_zone_5(int x0, int y0, int x1, int y1);

struct  point
{
    int x;
    int y;
};

void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void reshape(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-width/2.0, width/2.0 - 1, -height/2.0, height/2.0 - 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display (void) 
{ 
    glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    DrawCircle();
    glEnd();
    glFlush();
} 

void DrawCircle()
{
    for(int i = 0; i < 360; i += step){
        theta = PI*i/180;
        int x = r*cos(theta);
        int y = r*sin(theta);
        drawline_zone_5(0, 0, x, y);
    }

}

int find_zone(int dx, int dy)
{
    if(abs(dx) >= abs(dy)){
        if(dx >= 0){
            return (dy >= 0) ? 0 : 7;
        }
        else {
            return (dy >= 0) ? 3 : 4;
        }
    }
    else{
        if(dy >= 0){
            return (dx >= 0) ? 1 : 2;
        }
        else{
            return (dx >= 0) ? 6 : 5;
        }
    }
}

//convert from other zones to zone 5
struct point convert_to_zone_5(int x, int y, int zone)
{
    struct point p;
    int tx, ty;
    switch (zone)
    {
        case 0:
            tx = -y;
            ty = -x;
            break;
        case 1:
            tx = -x;
            ty = -y;
            break;
        case 2:
            tx = x;
            ty = -y;
            break;
        case 3:
            tx = -y;
            ty = x;
            break;
        case 4:
            tx = y;
            ty = x;
            break;
        case 5:
            tx = x;
            ty = y;
            break;
        case 6:
            tx = -x;
            ty = y;
            break;
        case 7:
            tx = y;
            ty = -x;
            break;
        default:
            printf("Invalid zone.\n");
            break;
    }
    p.x = tx;
    p.y = ty;
    return p;
}

//reconvert points from zone 5 to other zones
struct point convert_from_zone_5(int x, int y, int zone)
{
    struct point p;
    int tx, ty;
    switch (zone)
    {
        case 0:
            tx = -y;
            ty = -x;
            break;
        case 1:
            tx = -x;
            ty = -y;
            break;
        case 2:
            tx = x;
            ty = -y;
            break;
        case 3:
            tx = y;
            ty = -x;
            break;
        case 4:
            tx = y;
            ty = x;
            break;
        case 5:
            tx = x;
            ty = y;
            break;
        case 6:
            tx = -x;
            ty = y;
            break;
        case 7:
            tx = -y;
            ty = x;
            break;
        default:
            printf("Invalid zone.\n");
            break;
    }
    p.x = tx;
    p.y = ty;
    return p;
}


void drawline_zone_5(int x0, int y0, int x1, int y1)
{

    int zone = find_zone(x1 - x0, y1 - y0);
    struct point p1 = convert_to_zone_5(x0, y0, zone);
    struct point p2 = convert_to_zone_5(x1, y1, zone);

    x0 = p1.x;
    y0 = p1.y;
    x1 = p2.x;
    y1 = p2.y;

    int dx = x1 - x0;
    int dy = y1 - y0;
    int x = x0;
    int y = y0;
    int d = 2 * dx - dy;
    int del_s = 2 * dx;
    int del_sw = 2 * (dx - dy);
    
    switch (zone)
    {
        case 0: glColor3ub(255, 255, 255); break;  //white
        case 1: glColor3ub(255, 0, 0); break;      //red
        case 2: glColor3ub(0, 255, 0); break;      //green
        case 3: glColor3ub(0, 0, 255); break;       //blue
        case 4: glColor3ub(255, 255, 0); break;     //yellow
        case 5: glColor3ub(0, 255, 255); break;     //cyan
        case 6: glColor3ub(255, 0, 255); break;     //magenta
        case 7: glColor3ub(127, 127, 127); break;   //gray
    }
    
    while(y >= y1)
    {
        struct point p = convert_from_zone_5(x, y, zone);
        printf("%d %d\n", p.x, p.y);
        glVertex2i(p.x, p.y);

        if (d > 0)
        {
            d += del_s;
            y--;
        }
        else
        {
            d += del_sw;
            x--;
            y--;
        }
    }
}






int main (int argc, char** argv) 
{ 


    printf("Enter steps/angle:\n");
    scanf("%d", &step);
    printf("Enter radius\n");
    scanf("%d", &r);

    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Circle drawing using 8_way symmetry");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();

    
    return 0;
} 