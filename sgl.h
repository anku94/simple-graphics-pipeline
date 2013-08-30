#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stack>
#include<GL/glut.h>

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#define SGL_TRIANGLES 0

float triangles[600][6];
float curColor[3];
float clearColor[3];
int curTriangle;

using namespace std;

class Matrix{
	public:
		double val[4][4];
		Matrix(){
			int i, j;
			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
					val[i][j]=(i==j);
		}
		void setValue(float *source){
			int i, j;
			for(i=0;i<4;i++){
				for(j=0;j<4;j++){
					val[i][j] = source[4*i + j];
				}
			}
		}
		Matrix multiply(Matrix B){
			int i, j, k;
			Matrix product;
			for(i=0;i<4;i++){
				for(j=0;j<4;j++){
					product.val[i][j]=0;
					for(k=0;k<4;k++){
						product.val[i][j] += val[i][k] * B.val[k][j];
					}
				}
			}
			return product;
		}
		void print(){
			int i, j;
			printf("-----\n");
			for(i=0;i<4;i++){
				for(j=0;j<4;j++){
					printf("%0.2f ", val[i][j]);
				}
				printf("\n");
			}
			printf("-----\n");
		}

};
void normalizeMatrix(float fov, float ratio, float w, float h){
	Matrix normalizedMatrix;
	gluPerspective(45.0f, ratio, 0.1f, 200.0f);
}

stack<Matrix> sglStack;

Matrix modelMatrix, viewMatrix, projMatrix, viewportMatrix;
void init()
{
        glLoadIdentity();
        int w = glutGet(GLUT_SCREEN_WIDTH);
        int h = glutGet(GLUT_SCREEN_HEIGHT);
        int windowWidth = w * 2 / 3;
        int windowHeight = h * 2 / 3;
        sglStack.push(viewMatrix);


        glutInitWindowSize(windowWidth, windowHeight);
        glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2); 

        glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
        glutCreateWindow("CSE251_sampleCode");  // Setup the window
    
//      glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
//      glEnable(GL_COLOR_MATERIAL);    // Enable coloring
    
//        triCount=0;
//        pointCount=0;
//        vertexCount=0;

}

void sglModRotate(double angle, double axisx, double axisy, double axisz){
	
	float mod = sqrt(pow(axisx, 2) + pow(axisy, 2) + pow(axisz, 2));
	float x = axisx/mod, y = axisy/mod, z = axisz/mod;
	float s = sin(DEG2RAD(angle));	
	float c = cos(DEG2RAD(angle));
	Matrix rotMatrix;
	rotMatrix.val[0][0] = x*x*(1-c) + c;
	rotMatrix.val[0][1] = x*y*(1-c) - z*s;
	rotMatrix.val[0][2] = x*z*(1-c) + y*z;
	rotMatrix.val[0][3] = 0; 

	rotMatrix.val[1][0] = x*y*(1-c) + z*s;
	rotMatrix.val[1][1] = y*y*(1-c)  + c;
	rotMatrix.val[1][2] = y*z*(1-c) - x*s;
	rotMatrix.val[1][3] = 0; 

	rotMatrix.val[2][0] = x*z*(1-c) - y*s;
	rotMatrix.val[2][1] = y*z*(1-c)  + x*s;
	rotMatrix.val[2][2] = z*z*(1-c)  + c;
	rotMatrix.val[2][3] = 0; 

	Matrix M = sglStack.top();
	sglStack.pop();
	sglStack.push(M.multiply(rotMatrix));
	
}
void sglModTranslate(double tx, double ty, double tz){
	Matrix transMatrix;
	transMatrix.val[0][3] = tx;
	transMatrix.val[1][3] = ty;
	transMatrix.val[2][3] = tz;
	transMatrix.val[3][3] = 1;

	Matrix M = sglStack.top();
	sglStack.pop();
	sglStack.push(M.multiply(transMatrix));
}
void sglModScale(float sx, float sy, float sz){
	Matrix scaleMatrix;
	scaleMatrix.val[0][0] = sx;
	scaleMatrix.val[1][1] = sy;
	scaleMatrix.val[2][2] = sz;

	Matrix M = sglStack.top();
	sglStack.pop();
	sglStack.push(M.multiply(scaleMatrix));
}
void sglModMatrix(float * mat){
	int i, j;
	Matrix tempModel;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			tempModel.val[i][j] = mat[4*i + j];
		}
	sglStack.pop();
	sglStack.push(tempModel);
}
void sglModLoadIdentity(){
	sglStack.pop();
	Matrix identityMatrix;
	sglStack.push(identityMatrix);
}
void sglModPushMatrix(){
	sglStack.push(sglStack.top());
}
void sglModPopMatrix(){
	sglStack.pop();
}

/////////////////////////////////////////////
//	Viewing Transformations		   //
/////////////////////////////////////////////

void sglViewLoadIdentity(){
	Matrix identityMatrix;
	viewMatrix = identityMatrix;	
}
void sglViewRotate(float angle, float axisx, float axisy, float axisz){
	
	float mod = sqrt(pow(axisx, 2) + pow(axisy, 2) + pow(axisz, 2));
	float x = axisx/mod, y = axisy/mod, z = axisz/mod;
	float s = sin(DEG2RAD(angle));	
	float c = cos(DEG2RAD(angle));
	Matrix rotMatrix;
	rotMatrix.val[0][0] = x*x*(1-c) + c;
	rotMatrix.val[0][1] = x*y*(1-c) - z*s;
	rotMatrix.val[0][2] = x*z*(1-c) + y*z;
	rotMatrix.val[0][3] = 0; 

	rotMatrix.val[1][0] = x*y*(1-c) + z*s;
	rotMatrix.val[1][1] = y*y*(1-c)  + c;
	rotMatrix.val[1][2] = y*z*(1-c) - x*s;
	rotMatrix.val[1][3] = 0; 

	rotMatrix.val[2][0] = x*z*(1-c) - y*s;
	rotMatrix.val[2][1] = y*z*(1-c)  + x*s;
	rotMatrix.val[2][2] = z*z*(1-c)  + c;
	rotMatrix.val[2][3] = 0; 

	viewMatrix = viewMatrix.multiply(rotMatrix);
}
void sglViewTranslate(float tx, float ty, float tz){
	Matrix transMatrix;
	transMatrix.val[0][3] = tx;
	transMatrix.val[1][3] = ty;
	transMatrix.val[2][3] = tz;

	viewMatrix = viewMatrix.multiply(transMatrix);
}
void sglLookAt(float cx, float cy, float cz, float lx, float ly, float lz, float upx, float upy, float upz){
	//ToDo
	Matrix lookMatrix;

	//float fx =  cx - lx, fy = cy - ly, fz = cz - lz;
	float fx = - cx + lx, fy = - cy + ly, fz = - cz + lz;
	float modf = sqrt(fx*fx + fy*fy + fz*fz);
	fx/=modf; fy/=modf; fz/=modf;

	float sx = fy*upz - upy*fz, sy = fz*upx - upz*fx, sz = fx*upy - upx*fy;
	float mods = sqrt(sx*sx + sy*sy + sz*sz);
	sx/=mods, sy/=mods, sz/=mods;

	float ux = sy*fz - fy*sz, uy = sz*fx - fz*sx, uz = sx*fy - sy*fx;
	float modu = sqrt(ux*ux + uy*uy + uz*uz);
	ux/=modu, uy/=modu, uz/=modu;

	lookMatrix.val[0][0] = sx; lookMatrix.val[0][1] = sy;lookMatrix.val[0][2] = sz;
	lookMatrix.val[1][0] = ux; lookMatrix.val[1][1] = uy;lookMatrix.val[1][2] = uz;
	lookMatrix.val[2][0] = -fx; lookMatrix.val[2][1] = -fy;lookMatrix.val[2][2] = -fz;

	//lookMatrix.print();

	viewMatrix = viewMatrix.multiply(lookMatrix);
	sglViewTranslate ( - cx, - cy, - cz );
}
void sglViewMatrix(float *mat){
	viewMatrix.setValue(mat);
}

/////////////////////////////////////////////
//	Projection Transformations	   //
/////////////////////////////////////////////

void sglProjOrtho(float left, float right, float bottom, float top, float near, float far){
	float a = 2.0/(right - left);	
	float b = 2.0/(top - bottom);
	float c = 2.0/(far - near);
	//float c = -2.0/(far - near);

	float tx = - 1.0*(right + left)/(right - left);
	float ty = - 1.0*(top + bottom)/(top - bottom);
	float tz =   (far + near)/(far - near);

	projMatrix.val[0][0] = a;
	projMatrix.val[0][1] = 0;
	projMatrix.val[0][2] = 0;
	projMatrix.val[0][3] = tx;

	projMatrix.val[1][0] = 0;
	projMatrix.val[1][1] = b;
	projMatrix.val[1][2] = 0;
	projMatrix.val[1][3] = ty;

	projMatrix.val[2][0] = 0;
	projMatrix.val[2][1] = 0;
	projMatrix.val[2][2] = c;
	projMatrix.val[2][3] = tz;

	projMatrix.val[3][0] = 0;
	projMatrix.val[3][1] = 0;
	projMatrix.val[3][2] = 0;
	projMatrix.val[3][3] = 1;

}
void sglProjFrustum(float left, float right, float bottom, float top, float near, float far){

	//float f = 1/tan(DEG2RAD(22.5f));
	//float aspect = right/top;

	float A = (right + left)/(right - left);
	float B = (top + bottom)/(top - bottom);
	float C = (far + near)/(far - near);
	float D = (2 * far * near) / (far - near);

	float tA = 2*near/(right - left);
	float tB = 2*near/(top - bottom);

	//normalizeMatrix(left, right, top, far);

	/*projMatrix.val[0][0] = (f/aspect);
	projMatrix.val[0][1] = 0;
	projMatrix.val[0][2] = 0;
	projMatrix.val[0][3] = 0;

	projMatrix.val[1][0] = 0;
	projMatrix.val[1][1] = f;
	projMatrix.val[1][2] = 0;
	projMatrix.val[1][3] = 0;

	projMatrix.val[2][0] = 0;
	projMatrix.val[2][1] = 0;
	projMatrix.val[2][2] = C;
	projMatrix.val[2][3] = -1;

	projMatrix.val[3][0] = 0;
	projMatrix.val[3][1] = 0;
	projMatrix.val[3][2] = D;
	projMatrix.val[3][3] = 0;*/
	
	projMatrix.val[0][0] = tA;
	projMatrix.val[0][1] = 0;
	projMatrix.val[0][2] = A;
	projMatrix.val[0][3] = 0;

	projMatrix.val[1][0] = 0;
	projMatrix.val[1][1] = tB;
	projMatrix.val[1][2] = B;
	projMatrix.val[1][3] = 0;

	projMatrix.val[2][0] = 0;
	projMatrix.val[2][1] = 0;
	projMatrix.val[2][2] = C;
	projMatrix.val[2][3] = D;

	projMatrix.val[3][0] = 0;
	projMatrix.val[3][1] = 0;
	projMatrix.val[3][2] = -1;
	projMatrix.val[3][3] = 0;
	Matrix temp;
	//projMatrix =  temp;

}
void sglViewport(float llx, float lly, float width, float height){

	viewportMatrix.val[0][0] = (width - llx)/2.0;	
	viewportMatrix.val[0][1] = 0; 
	viewportMatrix.val[0][2] = 0; 
	viewportMatrix.val[0][3] = (width + llx)/2.0;	
	
	viewportMatrix.val[1][0] = 0; 
	viewportMatrix.val[1][1] = (height - lly)/2.0;	
	viewportMatrix.val[1][2] = 0; 
	viewportMatrix.val[1][3] = (height + lly)/2.0;	
	
	viewportMatrix.val[2][0] = 0;
	viewportMatrix.val[2][1] = 0; 
	viewportMatrix.val[2][2] = 1; 
	viewportMatrix.val[2][3] = 0; 
	
	viewportMatrix.val[3][0] = 0; 
	viewportMatrix.val[3][1] = 0; 
	viewportMatrix.val[3][2] = 0; 
	viewportMatrix.val[3][3] = 1;

	gluOrtho2D(llx, width, lly, height);

}

//Drawing functions

void sglBegin(int shapeCode){
	glBegin(GL_TRIANGLES);
}
void sglEnd(){
	glEnd();
}
void sglColor(float r, float g, float b){
	glColor3f(r, g, b);
	curColor[0] = r;
	curColor[1] = g;
	curColor[2] = b;
}
void sglClear(float r, float g, float b){
	clearColor[0] = r;
	clearColor[1] = g;
	clearColor[2] = b;
	//glClearColor(r, g, b, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void sglVertex(float x, float y, float z){
	Matrix allTrans;
	allTrans = allTrans.multiply(viewportMatrix);
	allTrans = allTrans.multiply(projMatrix);
	allTrans = allTrans.multiply(viewMatrix);
	allTrans = allTrans.multiply(sglStack.top());

	double points[6];
	double homoFactor;

	points[0] = allTrans.val[0][0]*x + allTrans.val[0][1]*y + allTrans.val[0][2]*z + allTrans.val[0][3]*1;
	points[1] = allTrans.val[1][0]*x + allTrans.val[1][1]*y + allTrans.val[1][2]*z + allTrans.val[1][3]*1;
	points[2] = allTrans.val[2][0]*x + allTrans.val[2][1]*y + allTrans.val[2][2]*z + allTrans.val[2][3]*1;
	homoFactor = allTrans.val[3][0]*x + allTrans.val[3][1]*y + allTrans.val[3][2]*z + allTrans.val[3][3]*1;

	points[0] /= homoFactor;
	points[1] /= homoFactor;
	points[2] /= homoFactor;

	//glVertex3f(points[0], points[1], points[2]);

	//printf("--> %0.2f %0.2f %0.2f\n", points[0], points[1], points[2]);

	triangles[curTriangle][0] = points[0];
	triangles[curTriangle][1] = points[1];
	triangles[curTriangle][2] = points[2];
	triangles[curTriangle][3] = curColor[0];
	triangles[curTriangle][4] = curColor[1];
	triangles[curTriangle][5] = curColor[2];
	curTriangle++;
}
/*
int main(){
	
	sglStack.push(modelMatrix);

	Matrix test;
	float sourceVals[] = {0.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 1.0f};
	test.setValue(sourceVals);
	test.multiply(test);
	test.print();
	return 0;
}*/
void writePly(){
	FILE * plyFile;
	plyFile = fopen("plyFile.txt", "w");
	fprintf(plyFile, "ply\n");
	fprintf(plyFile, "format ascii 1.0 custom\n");
	fprintf(plyFile, "element vertex %d\n", curTriangle);
	fprintf(plyFile, "property float x\n");
	fprintf(plyFile, "property float y\n");
	fprintf(plyFile, "property float z\n");
	fprintf(plyFile, "property float r\n");
	fprintf(plyFile, "property float g\n");
	fprintf(plyFile, "property float b\n");
	fprintf(plyFile, "end_header\n");
	int i;
	for(i=0;i<curTriangle;i++){
		fprintf(plyFile, "%0.2f %0.2f %0.2f %0.2f %0.2f %0.2f\n", triangles[i][0], triangles[i][1], triangles[i][2], triangles[i][3], triangles[i][4], triangles[i][5]);

	}

	fclose(plyFile);
}

void sglShow(){

	int i;
	writePly();
	glClearColor(clearColor[0],clearColor[1],clearColor[2],1);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);

	//cout<<curTriangle<<endl;

	for(i=0;i<curTriangle;i++){
		
		glColor3f(triangles[i][3], triangles[i][4], triangles[i][5]);
		glVertex3f(triangles[i][0], triangles[i][1], triangles[i][2]);
	}
	glEnd();
	glutSwapBuffers();
	//cout<<"Ended sglShow"<<endl;
	curTriangle = 0;
}
