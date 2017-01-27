/* CS580 Homework 3 */

#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include	"Gz.h"
#include	"rend.h"


//for homework 5
//int(*pfunc)(float, float, GzColor);


int GzRotXMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along x axis
// Pass back the matrix using mat value
	float d = (degree*3.14) / (180);

	mat[0][0] = 1;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = 0;
	mat[1][0] = 0;
	mat[1][1] = cosf(d);
	mat[1][2] = -sinf(d);
	mat[1][3] = 0;
	mat[2][0] = 0;
	mat[2][1] = sin(d);
	mat[2][2] = cos(d);
	mat[2][3] = 0;
	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;

	return GZ_SUCCESS;
}


int GzRotYMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along y axis
// Pass back the matrix using mat value
	float d = (degree*3.14) / (180);
	
	mat[0][0] = cosf(d);
	mat[0][1] = 0;
	mat[0][2] = sinf(d);
	mat[0][3] = 0;
	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[1][3] = 0;
	mat[2][0] = -sinf(d);
	mat[2][1] = 0;
	mat[2][2] = cosf(d);
	mat[2][3] = 0;
	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;

	return GZ_SUCCESS;
}


int GzRotZMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along z axis
// Pass back the matrix using mat value
	float d = (degree*3.14) / (180);

	mat[0][0] = cosf(d);
	mat[0][1] = -sinf(d);
	mat[0][2] = 0;
	mat[0][3] = 0;
	mat[1][0] = sinf(d);
	mat[1][1] = cosf(d);
	mat[1][2] = 0;
	mat[1][3] = 0;
	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 1;
	mat[2][3] = 0;
	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
	return GZ_SUCCESS;
}


int GzTrxMat(GzCoord translate, GzMatrix mat)
{
// Create translation matrix
// Pass back the matrix using mat value
	float Xtrans = translate[0];
	float Ytrans = translate[1];
	float Ztrans = translate[2];
	mat[0][0] = 1;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = Xtrans;
	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[1][3] = Ytrans;
	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 1;
	mat[2][3] = Ztrans;
	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
	return GZ_SUCCESS;
}


int GzScaleMat(GzCoord scale, GzMatrix mat)
{
// Create scaling matrix
// Pass back the matrix using mat value
	mat[0][0] = scale[0];
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = 0;
	mat[1][0] = 0;
	mat[1][1] = scale[1];
	mat[1][2] = 0;
	mat[1][3] = 0;
	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = scale[2];
	mat[2][3] = 0;
	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
	return GZ_SUCCESS;
}


//----------------------------------------------------------
// Begin main functions

int GzNewRender(GzRender **render, GzDisplay	*display)
{
/*  
- malloc a renderer struct 
- setup Xsp and anything only done once 
- save the pointer to display 
- init default camera 
*/ 
	*render = (GzRender*)malloc(sizeof(GzRender));
	(*render)->matlevel = 0;
	//setup Xsp and others
	(*render)->Xsp[0][0] = 128;
	(*render)->Xsp[0][1] = 0;
	(*render)->Xsp[0][2] = 0;
	(*render)->Xsp[0][3] = 128;
	(*render)->Xsp[1][0] = 0;
	(*render)->Xsp[1][1] = -128;
	(*render)->Xsp[1][2] = 0;
	(*render)->Xsp[1][3] = 128;
	(*render)->Xsp[2][0] = 0;
	(*render)->Xsp[2][1] = 0;
	(*render)->Xsp[2][2] = MAXINT;
	(*render)->Xsp[2][3] = 0;
	(*render)->Xsp[3][0] = 0;
	(*render)->Xsp[3][1] = 0;
	(*render)->Xsp[3][2] = 0;
	(*render)->Xsp[3][3] = 1;
	
	
	(**render).display = display;

	//init camera
	(*render)->camera.lookat[X] = 0;
	(*render)->camera.lookat[Y] = 0;
	(*render)->camera.lookat[Z] = 0;
	(*render)->camera.position[X] = DEFAULT_IM_X;
	(*render)->camera.position[Y] = DEFAULT_IM_Y;
	(*render)->camera.position[Z] = DEFAULT_IM_Z;
	(*render)->camera.worldup[X] = 0;
	(*render)->camera.worldup[Y] = 1;
	(*render)->camera.worldup[Z] = 0;
	(*render)->camera.FOV = DEFAULT_FOV;

	(*render)->numlights = 0;
	(*render)->normlevel = 0;

	return GZ_SUCCESS;

}


int GzFreeRender(GzRender *render)
{
/* 
-free all renderer resources
*/
	free(render);
	return GZ_SUCCESS;
}


int GzBeginRender(GzRender *render)
{
/*  
- setup for start of each frame - init frame buffer color,alpha,z
- compute Xiw and projection xform Xpi from camera definition 
- init Ximage - put Xsp at base of stack, push on Xpi and Xiw 
- now stack contains Xsw and app can push model Xforms when needed 
*/ 

	for (int j = 0; j < (*render).display->yres; j++)
	{
		for (int i = 0; i < (*render).display->xres; i++)
		{
			//find the index of gzpixel buffer ,
			//every r g b multiply 16 for in the next all of the pixel will be divided by 16 ,
			//ensure the back ground will not be another color
			int index = i + j*(*render).display->yres;
			(*render).display->fbuf[index].red = 255 * 16;
			(*render).display->fbuf[index].green = 255 * 16;
			(*render).display->fbuf[index].blue = 0;
			(*render).display->fbuf[index].alpha = 1;
			(*render).display->fbuf[index].z = MAXINT;
		}
	}
	//initialize Xpi
	float degree = ((render->camera.FOV / 2)*3.14) / 180;
	render->camera.Xpi[0][0] = 1;
	render->camera.Xpi[0][1] = 0;
	render->camera.Xpi[0][2] = 0;
	render->camera.Xpi[0][3] = 0;
	render->camera.Xpi[1][0] = 0;
	render->camera.Xpi[1][1] = 1;
	render->camera.Xpi[1][2] = 0;
	render->camera.Xpi[1][3] = 0;
	render->camera.Xpi[2][0] = 0;
	render->camera.Xpi[2][1] = 0;
	render->camera.Xpi[2][2] = tan(degree);
	render->camera.Xpi[2][3] = 0;
	render->camera.Xpi[3][0] = 0;
	render->camera.Xpi[3][1] = 0;
	render->camera.Xpi[3][2] = tan(degree);
	render->camera.Xpi[3][3] = 1;
	//initialize Xiw
	//calculate the z information
	float clx = render->camera.lookat[X] - render->camera.position[X];
	float cly = render->camera.lookat[Y] - render->camera.position[Y];
	float clz = render->camera.lookat[Z] - render->camera.position[Z];
	float lenofcl = sqrt(clx*clx + cly*cly + clz*clz);
	float zx = clx / lenofcl;
	float zy = cly / lenofcl;
	float zz = clz / lenofcl;
	//calculate the y information
	float dotproduct = render->camera.worldup[X] * zx + render->camera.worldup[Y] * zy + render->camera.worldup[Z] * zz;
	float upX = render->camera.worldup[X] - dotproduct*zx;
	float upY = render->camera.worldup[Y] - dotproduct*zy;
	float upZ = render->camera.worldup[Z] - dotproduct*zz;
	float lenofUp = sqrt(upX*upX + upY*upY + upZ*upZ);
	float yx = upX / lenofUp;
	float yy = upY / lenofUp;
	float yz = upZ / lenofUp;
	//calculate the x information
	float xx = yy*zz - yz*zy;
	float xy = yz*zx - yx*zz;
	float xz = yx*zy - yy*zx;
	float XC = render->camera.position[X] * xx + render->camera.position[Y] * xy + render->camera.position[Z] * xz;
	float YC = render->camera.position[X] * yx + render->camera.position[Y] * yy + render->camera.position[Z] * yz;
	float ZC = render->camera.position[X] * zx + render->camera.position[Y] * zy + render->camera.position[Z] * zz;
	render->camera.Xiw [0][0]= xx ;
	render->camera.Xiw[0][1] = xy;
	render->camera.Xiw[0][2] = xz;
	render->camera.Xiw[0][3] = -XC;
	render->camera.Xiw[1][0] = yx;
	render->camera.Xiw[1][1] = yy;
	render->camera.Xiw[1][2] = yz;
	render->camera.Xiw[1][3] = -YC;
	render->camera.Xiw[2][0] = zx;
	render->camera.Xiw[2][1] = zy;
	render->camera.Xiw[2][2] = zz;
	render->camera.Xiw[2][3] = -ZC;
	render->camera.Xiw[3][0] = 0;
	render->camera.Xiw[3][1] = 0;
	render->camera.Xiw[3][2] = 0;
	render->camera.Xiw[3][3] = 1;

	//push xsp,xpi,xiw
	GzPushMatrix(render,render->Xsp);
	GzPushMatrix(render, render->camera.Xpi);
	GzPushMatrix(render, render->camera.Xiw);
//	GzPushNormMatrix(render, render->camera.Xiw);
	return GZ_SUCCESS;
}

int GzPutCamera(GzRender *render, GzCamera *camera)
{
/*
- overwrite renderer camera structure with new camera definition
*/
	(*render).camera.position[X] = camera->position[X];
	(*render).camera.position[Y] = camera->position[Y];
	(*render).camera.position[Z] = camera->position[Z];
	(*render).camera.lookat[X] = camera->lookat[X];
	(*render).camera.lookat[Y] = camera->lookat[Y];
	(*render).camera.lookat[Z] = camera->lookat[Z];
	(*render).camera.worldup[X] = camera->worldup[X];
	(*render).camera.worldup[Y] = camera->worldup[Y];
	(*render).camera.worldup[Z] = camera->worldup[Z];
	(*render).camera.FOV = camera->FOV;
	return GZ_SUCCESS;	
}

int GzPushMatrix(GzRender *render, GzMatrix	matrix)
{
/*
- push a matrix onto the Ximage stack
- check for stack overflow
*/
	
	if (render->matlevel > MATLEVELS)return GZ_FAILURE;
	if (render->matlevel == 0)
	{
		for(int i=0;i<4;i++)
			for (int j = 0; j < 4; j++)
			{
				render->Ximage[0][i][j] = matrix[i][j];
			}
		render->matlevel++;

	}
	else
	{
		
		int index = render->matlevel - 1;
		for(int row=0;row<4;row++)
			for (int col = 0; col < 4; col++)
			{
				
				render->Ximage[render->matlevel][row][col] = render->Ximage[index][row][0]*matrix[0][col]+ render->Ximage[index][row][1] * matrix[1][col]
					+ render->Ximage[index][row][2] * matrix[2][col]+ render->Ximage[index][row][3] * matrix[3][col];

			}
		render->matlevel++;
		if (render->matlevel > 2)
			GzPushNormMatrix(render, matrix);
	}
	return GZ_SUCCESS;
}

int GzPopMatrix(GzRender *render)
{
/*
- pop a matrix off the Ximage stack
- check for stack underflow
*/
	if (render->matlevel > 0)render->matlevel--;
	if (render->normlevel > 0)render->normlevel--;
	return GZ_SUCCESS;
}


int GzPushNormMatrix(GzRender* render,GzMatrix matrix)
{
	if (render->normlevel > MATLEVELS)return GZ_FAILURE;
	GzMatrix temp;
	for(int i=0;i<3;i++)
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = matrix[i][j];
		}

	temp[0][3] = 0;
	temp[1][3] = 0;
	temp[2][3] = 0;
	float k = sqrt(temp[0][0] * temp[0][0] + temp[0][1] * temp[0][1] + temp[0][2] * temp[0][2]);
	temp[0][0] = temp[0][0] / k;
	temp[0][1] = temp[0][1] / k;
	temp[0][2] = temp[0][2] / k;
	temp[1][0] = temp[1][0] / k;
	temp[1][1] = temp[1][1] / k;
	temp[1][2] = temp[1][2] / k;
	temp[2][0] = temp[2][0] / k;
	temp[2][1] = temp[2][1] / k;
	temp[2][2] = temp[2][2] / k;
	if (render->normlevel == 0)
	{
		for (int i = 0; i<4; i++)
			for (int j = 0; j < 4; j++)
			{
				render->Xnorm[0][i][j] = temp[i][j];
			}
		render->normlevel++;
	}
	else
	{
		int index = render->normlevel - 1;
		for (int row = 0; row<4; row++)
			for (int col = 0; col < 4; col++)
			{

				render->Xnorm[render->normlevel][row][col] = render->Xnorm[index][row][0] * temp[0][col] + render->Xnorm[index][row][1] * temp[1][col]
					+ render->Xnorm[index][row][2] * temp[2][col] + render->Xnorm[index][row][3] *temp[3][col];

			}
		render->normlevel++;
	}
	return GZ_SUCCESS;

}




int GzPutAttribute(GzRender	*render, int numAttributes, GzToken	*nameList, 
	GzPointer	*valueList) /* void** valuelist */
{
/*
- set renderer attribute states (e.g.: GZ_RGB_COLOR default color)
- later set shaders, interpolaters, texture maps, and lights
*/
	for (int index = 0; index < numAttributes; index++)
	{
		GzToken flag = nameList[index];
		switch (flag)
		{
			case GZ_RGB_COLOR:
			{
				GzPointer temp = valueList[index];
				float* a = (float*)temp;
				GzColor color = { a[0],a[1],a[2] };
				for (int i = 0; i < 3; i++)
				{
					if (color[i] < 0)color[i] = 0;
					if (color[i] > 1)color[i] = 1;
				}
				(*render).flatcolor[0] = color[0];
				(*render).flatcolor[1] = color[1];
				(*render).flatcolor[2] = color[2];
			}break;
			case GZ_DIRECTIONAL_LIGHT:
			{
				GzLight* light = (GzLight*)valueList[index];
				(*render).lights[render->numlights].color[0] = light->color[0];
				(*render).lights[render->numlights].color[1] = light->color[1];
				(*render).lights[render->numlights].color[2] = light->color[2];
				(*render).lights[render->numlights].direction[0] = light->direction[0];
				(*render).lights[render->numlights].direction[1] = light->direction[1];
				(*render).lights[render->numlights].direction[2] = light->direction[2];
				render->numlights++;
			}break;
			case GZ_AMBIENT_LIGHT:
			{
				GzLight* ambient = (GzLight*)valueList[index];
				render->ambientlight.color[0] = ambient->color[0];
				render->ambientlight.color[1] = ambient->color[1];
				render->ambientlight.color[2] = ambient->color[2];
				render->ambientlight.direction[0] = ambient->direction[0];
				render->ambientlight.direction[1] = ambient->direction[1];
				render->ambientlight.direction[2] = ambient->direction[2];
			}break;
			case GZ_AMBIENT_COEFFICIENT:
			{
				
				GzPointer temp = valueList[index];
				float* a = (float*)temp;
				GzColor color = { a[0],a[1],a[2] };
				render->Ka[0] = color[0];
				render->Ka[1] = color[1];
				render->Ka[2] = color[2];

			}break;
			case GZ_DIFFUSE_COEFFICIENT:
			{
				
				GzPointer temp = valueList[index];
				float* a = (float*)temp;
				GzColor color = { a[0],a[1],a[2] };
				render->Kd[0] = color[0];
				render->Kd[1] = color[1];
				render->Kd[2] = color[2];


			}break;
			case GZ_SPECULAR_COEFFICIENT:
			{
				
				GzPointer temp = valueList[index];
				float* a = (float*)temp;
				GzColor color = { a[0],a[1],a[2] };
				render->Ks[0] = color[0];
				render->Ks[1] = color[1];
				render->Ks[2] = color[2];


			}break;
			case GZ_DISTRIBUTION_COEFFICIENT:
			{
				render->spec = 32;
			}break;
			case GZ_INTERPOLATE:
			{
				render->interp_mode = *((int*)valueList[index]);
			}break;
			case GZ_TEXTURE_MAP:
			{
			
				render->tex_fun = (int(*) (float, float, GzColor))(valueList[index]);
				
			}break;
			case GZ_ANTIALIASING:
			{
				GzPointer temp = valueList[index];
				float *a = (float*)temp;
				render->Xoffset = a[0];
				render->Yoffset = a[1];
				render->weight = a[2];
			}break;
		}
	}
	return GZ_SUCCESS;
}


/* NOT part of API - just for general assistance */

short	ctoi(float color)		/* convert float color to GzIntensity short */
{
	return(short)((int)(color * ((1 << 12) - 1)));
}



//pass vertex 's normal and then get the color in float[3]
float* ShadeFunction(GzRender* render, GzCoord N)
{
	float result[3];//0,1,2 red green blue

	

	//fixed one in the formula ka*la
	GzColor kaMULla = 
	{ 
		render->ambientlight.color[0] * render->Ka[0]
		,render->ambientlight.color[1] * render->Ka[1]
		,render->ambientlight.color[2] * render->Ka[2] 
	};



	GzColor sumRE = { 0,0,0 }, sumNL = {0,0,0};

	//fixed E direction
	GzCoord E = { 0,0,-1 };


	//calculte the sum of each ks,kd
	for (int num = 0; num < render->numlights; num++)
	{
		
		GzCoord R,L;
		GzColor le;
		float NL, NE;


		le[0] = render->lights[num].color[0];
		le[1] = render->lights[num].color[1];
		le[2] = render->lights[num].color[2];


		//get unit L 
		L[0] = render->lights[num].direction[0];
		L[1] = render->lights[num].direction[1];
		L[2] = render->lights[num].direction[2];
		float lenlight = sqrt(L[0] * L[0] + L[1] * L[1] + L[2] * L[2]);
		L[0] = L[0] / lenlight;
		L[1] = L[1] / lenlight;
		L[2] = L[2] / lenlight;

		//calculate NL NE for judge
		NL = N[0] * L[0] + N[1] * L[1] + N[2] * L[2];
		NE = N[0] * E[0] + N[1] * E[1] + N[2] * E[2];

		if (NL > 0 && NE > 0)//eye light on the same side,then calculate it 
		{

			//we get unit R
			R[0] = 2 * NL*N[0] - L[0];
			R[1] = 2 * NL*N[1] - L[1];
			R[2] = 2 * NL*N[2] - L[2];

			float lenR = sqrt(R[0] * R[0] + R[1] * R[1] + R[2] * R[2]);

			R[0] = R[0] / lenR;
			R[1] = R[1] / lenR;
			R[2] = R[2] / lenR;

			//calculate RE clamp it to [0,1]
			float RE = R[0] * E[0] + R[1] * E[1] + R[2] * E[2];
			if (RE < 0)RE = 0;
			if (RE > 1)RE = 1;
			float powRE = pow(RE, render->spec);

			//
			sumRE[0] = sumRE[0] + le[0] * powRE;
			sumRE[1] = sumRE[1] + le[1] * powRE;
			sumRE[2] = sumRE[2] + le[2] * powRE;

			sumNL[0] = sumNL[0] + le[0] * NL;
			sumNL[1] = sumNL[1] + le[1] * NL;
			sumNL[2] = sumNL[2] + le[2] * NL;


		}
		else if (NL < 0 && NE < 0)//calculate the back
		{
			//reverse the normal
			float n0 = -N[0];
			float n1 = -N[1];
			float n2 = -N[2];
		    NL = n0 * L[0] + n1 * L[1] + n2 * L[2];
			
			//get R in unit
			R[0] = 2 * NL*n0 - L[0];
			R[1] = 2 * NL*n1 - L[1];
			R[2] = 2 * NL*n2 - L[2];

			float lenR = sqrt(R[0] * R[0] + R[1] * R[1] + R[2] * R[2]);

			R[0] = R[0] / lenR;
			R[1] = R[1] / lenR;
			R[2] = R[2] / lenR;

			//get RE
			float RE = R[0] * E[0] + R[1] * E[1] + R[2] * E[2];
			if (RE < 0)RE = 0;
			if (RE > 1)RE = 1;
			float powRE = pow(RE, render->spec);

			//
			sumRE[0] = sumRE[0] + le[0] * powRE;
			sumRE[1] = sumRE[1] + le[1] * powRE;
			sumRE[2] = sumRE[2] + le[2] * powRE;

			sumNL[0] = sumNL[0] + le[0] * NL;
			sumNL[1] = sumNL[1] + le[1] * NL;
			sumNL[2] = sumNL[2] + le[2] * NL;

			

		}
		else if (NL*NE < 0)//if eye and light not on the same side,ignore it 
		{
			continue;
		}
	}

	result[0] = render->Ks[0] * sumRE[0] + render->Kd[0] * sumNL[0] + kaMULla[0];
	result[1] = render->Ks[1] * sumRE[1] + render->Kd[1] * sumNL[1] + kaMULla[1];
	result[2] = render->Ks[2] * sumRE[2] + render->Kd[2] * sumNL[2] + kaMULla[2];


	
	return result;
}


int GzPutTriangle(GzRender	*render, int numParts, GzToken *nameList, GzPointer	*valueList)
/* numParts : how many names and values */
{
/*  
- pass in a triangle description with tokens and values corresponding to 
      GZ_POSITION:3 vert positions in model space 
- Xform positions of verts using matrix on top of stack 
- Clip - just discard any triangle with any vert(s) behind view plane 
       - optional: test for triangles with all three verts off-screen (trivial frustum cull)
- invoke triangle rasterizer  
*/ 
	//initializing corresponding paramater
	float vertex[3][3];
	float normal[3][3];

	//for texture store
	float texture[3][2];


	int i = 0, j = 0;
	GzIntensity red, green, blue;


	//set the boundary
	float xstart, xend, ystart, yend;
	bool rightedged = false;
	float pA, pB, pC, pD;



	for (int index = 0; index < numParts; index++)
	{
		GzToken flag = nameList[index];
		switch (flag)
		{
		  case GZ_POSITION:
		      {
				  GzPointer temp = valueList[index];
				  GzCoord* vertlist = (GzCoord*)temp;				  
				  for (i = 0; i < 3; i++)
					  for (j = 0; j < 3; j++)
					  {
						  vertex[i][j] = vertlist[i][j];
					  }

				  //check whether it need to be discarded and calculate the screen x,y,z
				  int m = render->matlevel - 1;

				  for (i = 0; i < 3; i++)
				  {
					  float oldX, oldY, oldZ, oldW, W = 1;
					  oldX = vertex[i][X];
					  oldY = vertex[i][Y];
					  oldZ = vertex[i][Z];
					  oldW = 1;
					  //calculate the new one
					  vertex[i][X] = render->Ximage[m][0][0] * oldX + render->Ximage[m][0][1] * oldY + render->Ximage[m][0][2] * oldZ + render->Ximage[m][0][3] * oldW;
					  vertex[i][Y] = render->Ximage[m][1][0] * oldX + render->Ximage[m][1][1] * oldY + render->Ximage[m][1][2] * oldZ + render->Ximage[m][1][3] * oldW;
					  vertex[i][Z] = render->Ximage[m][2][0] * oldX + render->Ximage[m][2][1] * oldY + render->Ximage[m][2][2] * oldZ + render->Ximage[m][2][3] * oldW;
					  W = render->Ximage[m][3][0] * oldX + render->Ximage[m][3][1] * oldY + render->Ximage[m][3][2] * oldZ + render->Ximage[m][3][3] * oldW;
					  vertex[i][X] =render->Xoffset +vertex[i][X] / W;
					  vertex[i][Y] = render->Yoffset+vertex[i][Y] / W;
					  vertex[i][Z] = vertex[i][Z] / W;

					  if (vertex[i][Z] < 0)
						  return GZ_SUCCESS;

				  }

				

			  }break;
		  case GZ_NORMAL:
			  {
				  GzPointer norm = valueList[index];
				  GzCoord * normlist = (GzCoord*)norm;
				  for(i=0;i<3;i++)
					  for (j = 0; j < 3; j++)
					  {
						  normal[i][j] = normlist[i][j];
					  }
				  //calculate the normal after the change
				 int lev = render->normlevel - 1;

				  for (i = 0; i < 3; i++)
				  {
					  float oldX, oldY, oldZ, oldW, W = 1;
					  oldX = normal[i][X];
					  oldY = normal[i][Y];
					  oldZ = normal[i][Z];
					  oldW = 1;
					  //calculate the new one
					  normal[i][X] = render->Xnorm[lev][0][0] * oldX + render->Xnorm[lev][0][1] * oldY + render->Xnorm[lev][0][2] * oldZ+ render->Xnorm[lev][0][3] * oldW;
					  normal[i][Y] = render->Xnorm[lev][1][0] * oldX + render->Xnorm[lev][1][1] * oldY + render->Xnorm[lev][1][2] * oldZ + render->Xnorm[lev][1][3] * oldW;
					  normal[i][Z] = render->Xnorm[lev][2][0] * oldX + render->Xnorm[lev][2][1] * oldY + render->Xnorm[lev][2][2] * oldZ+ render->Xnorm[lev][2][3] * oldW;
					  W = render->Ximage[lev][3][0] * oldX + render->Ximage[lev][3][1] * oldY + render->Ximage[lev][3][2] * oldZ + render->Ximage[lev][3][3] * oldW;
					  normal[i][X] = normal[i][X] / W;
					  normal[i][Y] = normal[i][Y] / W;
					  normal[i][Z] = normal[i][Z] / W;

					  float lenofnorm = sqrt(normal[i][X] * normal[i][X] + normal[i][Y] * normal[i][Y] + normal[i][Z] * normal[i][Z]);
					  normal[i][X] = normal[i][X] / lenofnorm;
					  normal[i][Y] = normal[i][Y] / lenofnorm;
					  normal[i][Z] = normal[i][Z] / lenofnorm;
					  

				  }

			  }break;
		  case GZ_TEXTURE_INDEX:
		  {
			  GzPointer texture1 = valueList[index];
			  GzTextureIndex* tex = (GzTextureIndex*)texture1;
			  for (int i = 0; i < 3; i++)
			  {
				  texture[i][0] = tex[i][0];
				  texture[i][1] = tex[i][1];
			  }
		  }break;
		}
	}


	//calculate the color
	if (render->interp_mode == GZ_FLAT)
	{
		float* flatcolor = ShadeFunction(render, normal[0]);
		red = ctoi(flatcolor[0]);
		green = ctoi(flatcolor[1]);
		blue = ctoi(flatcolor[2]);

		xstart = min(min(vertex[0][0], vertex[1][0]), vertex[2][0]);
		if (xstart < 0)xstart = 0;

		xend = max(max(vertex[0][0], vertex[1][0]), vertex[2][0]);
		if (xend > 256)xend = 256;

		ystart = min(min(vertex[0][1], vertex[1][1]), vertex[2][1]);
		if (ystart < 0)ystart = 0;

		yend = max(max(vertex[0][1], vertex[1][1]), vertex[2][1]);
		if (yend > 256)yend = 256;


		//bubble sort for vertex
		float x, y, z;
	
		for (i = 0; i < 2; i++)
			for (j = i + 1; j < 3; j++)
			{
				if (vertex[i][1] > vertex[j][1])
				{
					
					x = vertex[i][0];
					y = vertex[i][1];
					z = vertex[i][2];
					vertex[i][0] = vertex[j][0];
					vertex[i][1] = vertex[j][1];
					vertex[i][2] = vertex[j][2];
					
					vertex[j][0] = x;
					vertex[j][1] = y;
					vertex[j][2] = z;
					
				}
			}
		//after the sort,the vertex sort in y from small to big
		//judge left or right save the middle point information

		//calculate the equation of the line 
		float a, b, c;
		a = vertex[2][1] - vertex[0][1];
		b = vertex[0][0] - vertex[2][0];
		c = vertex[2][0] * vertex[0][1] - vertex[0][0] * vertex[2][1];
		float x1 = (-c - b*vertex[1][1]) / a;
		if (x1 < vertex[1][0])rightedged = true;
		if (x1 > vertex[1][0])rightedged = false;

		//calculate a,b,c,d for the plane

		GzCoord v12 = { vertex[1][0] - vertex[0][0],vertex[1][1] - vertex[0][1],vertex[1][2] - vertex[0][2] };
		GzCoord v13 = { vertex[2][0] - vertex[0][0],vertex[2][1] - vertex[0][1],vertex[2][2] - vertex[0][2] };
		//aybz-azby azbx-axbz axby-aybx
		pA = v12[1] * v13[2] - v12[2] * v13[1];
		pB = v12[2] * v13[0] - v12[0] * v13[2];
		pC = v12[0] * v13[1] - v12[1] * v13[0];
		pD = 0 - pA*vertex[0][0] - pB*vertex[0][1] - pC*vertex[0][2];

		
		

		for (int ypos = ystart; ypos < yend; ypos++)
		{
			for (int xpos = xstart; xpos < xend; xpos++)
			{
				int index = xpos + ypos*(render->display->yres);
				float E12, E13, E23;
				if (rightedged == false)
				{
					E12 = (vertex[0][1] - vertex[1][1])*(xpos - vertex[1][0]) - (vertex[0][0] - vertex[1][0])*(ypos - vertex[1][1]);
					E23 = (vertex[1][1] - vertex[2][1])*(xpos - vertex[2][0]) - (vertex[1][0] - vertex[2][0])*(ypos - vertex[2][1]);
					E13 = (vertex[2][1] - vertex[0][1])*(xpos - vertex[0][0]) - (vertex[2][0] - vertex[0][0])*(ypos - vertex[0][1]);
				}
				else
				{
					E12 = (vertex[1][1] - vertex[0][1])*(xpos - vertex[0][0]) - (vertex[1][0] - vertex[0][0])*(ypos - vertex[0][1]);
					E23 = (vertex[2][1] - vertex[1][1])*(xpos - vertex[1][0]) - (vertex[2][0] - vertex[1][0])*(ypos - vertex[1][1]);
					E13 = (vertex[0][1] - vertex[2][1])*(xpos - vertex[2][0]) - (vertex[0][0] - vertex[2][0])*(ypos - vertex[2][1]);
				}
				if (E12 <= 0 && E13 <= 0 && E23 <= 0)
				{
					//calculate the z for that pixel
					float zpos = (-pD - pA*xpos - pB*ypos) / pC;
					//if z < z in buffer then update the color 
					if (zpos <= (*render).display->fbuf[index].z)
					{

						(*render).display->fbuf[index].red = red;
						(*render).display->fbuf[index].green = green;
						(*render).display->fbuf[index].blue = blue;
						(*render).display->fbuf[index].alpha = 1;
						(*render).display->fbuf[index].z = zpos;
					}
				}


			}

		}


	}


	if (render->interp_mode == GZ_COLOR)
	{

		/*
		
		compute color at each vertices with ka=kd=ks=1
		at each pixel 
		   interpolate C
		   interpolate u,v
		   fetch KT texture value at (u,v)
		   final color =c*kt
		   
		   
		   */


		float ua, ub, uc, ud, va, vb, vc, vd;

		float vz1 = vertex[0][2] / (MAXINT - vertex[0][2]);
		float vz2 = vertex[1][2] / (MAXINT - vertex[1][2]);
		float vz3 = vertex[2][2] / (MAXINT - vertex[2][2]);

		//texture in perspective
		texture[0][0] = texture[0][0] / (vz1 + 1);
		texture[1][0] = texture[1][0] / (vz2 + 1);
		texture[2][0] = texture[2][0] / (vz3 + 1);
		texture[0][1] = texture[0][1] / (vz1 + 1);
		texture[1][1] = texture[1][1] / (vz2 + 1);
		texture[2][1] = texture[2][1] / (vz3 + 1);

		//calculate for u interpolation
		float tu1[3] = { vertex[0][0],vertex[0][1],texture[0][0] };
		float tu2[3] = { vertex[1][0],vertex[1][1],texture[1][0] };
		float tu3[3] = { vertex[2][0],vertex[2][1],texture[2][0] };

		float u12[3] = { tu2[0] - tu1[0],tu2[1] - tu1[1],tu2[2] - tu1[2] };
		float u13[3] = { tu3[0] - tu1[0],tu3[1] - tu1[1],tu3[2] - tu1[2] };
		ua = u12[1] * u13[2] - u12[2] * u13[1];
		ub = u12[2] * u13[0] - u12[0] * u13[2];
		uc = u12[0] * u13[1] - u12[1] * u13[0];
		ud = 0 - ua*tu1[0] - ub*tu1[1] - uc*tu1[2];


		//calculate for v interpolation
		float tv1[3] = { vertex[0][0],vertex[0][1],texture[0][1] };
		float tv2[3] = { vertex[1][0],vertex[1][1],texture[1][1] };
		float tv3[3] = { vertex[2][0],vertex[2][1],texture[2][1] };

		float tv12[3] = { tv2[0] - tv1[0],tv2[1] - tv1[1],tv2[2] - tv1[2] };
		float tv13[3] = { tv3[0] - tv1[0],tv3[1] - tv1[1],tv3[2] - tv1[2] };
		va = tv12[1] * tv13[2] - tv12[2] * tv13[1];
		vb = tv12[2] * tv13[0] - tv12[0] * tv13[2];
		vc = tv12[0] * tv13[1] - tv12[1] * tv13[0];
		vd = 0 - va*tv1[0] - vb*tv1[1] - vc*tv1[2];
	



		//calculate for rgb in each vertex
		float narray1[3] = {normal[0][0],normal[0][1],normal[0][2]};
		float narray2[3] = { normal[1][0],normal[1][1],normal[1][2] };
		float narray3[3] = { normal[2][0],normal[2][1],normal[2][2] };


		GzColor newcolor;



		render->Ka[0] = 1;
		render->Ka[1] = 1;
		render->Ka[2] = 1;
		render->Ks[0] = 1;
		render->Ks[1] = 1;
		render->Ks[2] = 1;
		render->Kd[0] = 1;
		render->Kd[1] = 1;
		render->Kd[2] = 1;
		render->Ks[0] = 1;
		render->Ks[1] = 1;
		render->Ks[2] = 1;

		float rgb1[3] = { ShadeFunction(render, narray1)[0],ShadeFunction(render, narray1)[1],ShadeFunction(render, narray1)[2] };		
		float rgb2[3] = { ShadeFunction(render, narray2)[0],ShadeFunction(render, narray2)[1],ShadeFunction(render, narray2)[2] };
		float rgb3[3] = { ShadeFunction(render, narray3)[0],ShadeFunction(render, narray3)[1],ShadeFunction(render, narray3)[2] };
	



		//calculate for R equation
		float ar, br, cr, dr;
		float V1[3] = { vertex[0][0],vertex[0][1],ctoi(rgb1[0]) };
		float V2[3] = { vertex[1][0],vertex[1][1],ctoi(rgb2[0]) };
		float V3[3] = { vertex[2][0],vertex[2][1],ctoi(rgb3[0]) };
		float V1V2[3] = {V2[0]-V1[0],V2[1]-V1[1],V2[2]-V1[2]};
		float V1V3[3] = { V3[0] - V1[0],V3[1]-V1[1],V3[2]-V1[2] };
		ar = V1V2[1] * V1V3[2] - V1V2[2] * V1V3[1];
		br = V1V2[2] * V1V3[0] - V1V2[0] * V1V3[2];
		cr = V1V2[0] * V1V3[1] - V1V2[1] * V1V3[0];
		dr = 0 - ar*V1[0] - br*V1[1] - cr*V1[2];
		//calculate for G equation
		float ag, bg, cg, dg;
		float Vg1[3] = { vertex[0][0],vertex[0][1],ctoi(rgb1[1]) };
		float Vg2[3] = { vertex[1][0],vertex[1][1],ctoi(rgb2[1]) };
		float Vg3[3] = { vertex[2][0],vertex[2][1],ctoi(rgb3[1]) };
		float V1V2g[3] = { Vg2[0] - Vg1[0],Vg2[1] - Vg1[1],Vg2[2] - Vg1[2] };
		float V1V3g[3] = { Vg3[0] - Vg1[0],Vg3[1] - Vg1[1],Vg3[2] - Vg1[2] };
		ag = V1V2g[1] * V1V3g[2] - V1V2g[2] * V1V3g[1];
		bg = V1V2g[2] * V1V3g[0] - V1V2g[0] * V1V3g[2];
		cg = V1V2g[0] * V1V3g[1] - V1V2g[1] * V1V3g[0];
		dg = 0 - ag*Vg1[0] - bg*Vg1[1] - cg*Vg1[2];
		//calculate for B equation
		float Ab, Bb, Cb, Db;
		float Vb1[3] = { vertex[0][0],vertex[0][1],ctoi(rgb1[2]) };
		float Vb2[3] = { vertex[1][0],vertex[1][1],ctoi(rgb2[2]) };
		float Vb3[3] = { vertex[2][0],vertex[2][1],ctoi(rgb3[2]) };
		float V1V2b[3] = { Vb2[0] - Vb1[0],Vb2[1] - Vb1[1],Vb2[2] - Vb1[2] };
		float V1V3b[3] = { Vb3[0] - Vb1[0],Vb3[1] - Vb1[1],Vb3[2] - Vb1[2] };
		Ab = V1V2b[1] * V1V3b[2] - V1V2b[2] * V1V3b[1];
		Bb = V1V2b[2] * V1V3b[0] - V1V2b[0] * V1V3b[2];
		Cb = V1V2b[0] * V1V3b[1] - V1V2b[1] * V1V3b[0];
		Db = 0 - Ab*Vb1[0] - Bb*Vb1[1] - Cb*Vb1[2];
		//draw the triangle



		xstart = min(min(vertex[0][0], vertex[1][0]), vertex[2][0]);
		if (xstart < 0)xstart = 0;

		xend = max(max(vertex[0][0], vertex[1][0]), vertex[2][0]);
		if (xend > 256)xend = 256;

		ystart = min(min(vertex[0][1], vertex[1][1]), vertex[2][1]);
		if (ystart < 0)ystart = 0;

		yend = max(max(vertex[0][1], vertex[1][1]), vertex[2][1]);
		if (yend > 256)yend = 256;


		//bubble sort for vertex
		float x, y, z;

		for (i = 0; i < 2; i++)
			for (j = i + 1; j < 3; j++)
			{
				if (vertex[i][1] > vertex[j][1])
				{

					x = vertex[i][0];
					y = vertex[i][1];
					z = vertex[i][2];
					vertex[i][0] = vertex[j][0];
					vertex[i][1] = vertex[j][1];
					vertex[i][2] = vertex[j][2];

					vertex[j][0] = x;
					vertex[j][1] = y;
					vertex[j][2] = z;

				}
			}
		//after the sort,the vertex sort in y from small to big
		//judge left or right save the middle point information

		//calculate the equation of the line 
		float a, b, c;
		a = vertex[2][1] - vertex[0][1];
		b = vertex[0][0] - vertex[2][0];
		c = vertex[2][0] * vertex[0][1] - vertex[0][0] * vertex[2][1];
		float x1 = (-c - b*vertex[1][1]) / a;
		if (x1 < vertex[1][0])rightedged = true;
		if (x1 > vertex[1][0])rightedged = false;

		//calculate a,b,c,d for the plane

		GzCoord v12 = { vertex[1][0] - vertex[0][0],vertex[1][1] - vertex[0][1],vertex[1][2] - vertex[0][2] };
		GzCoord v13 = { vertex[2][0] - vertex[0][0],vertex[2][1] - vertex[0][1],vertex[2][2] - vertex[0][2] };
		//aybz-azby azbx-axbz axby-aybx
		pA = v12[1] * v13[2] - v12[2] * v13[1];
		pB = v12[2] * v13[0] - v12[0] * v13[2];
		pC = v12[0] * v13[1] - v12[1] * v13[0];
		pD = 0 - pA*vertex[0][0] - pB*vertex[0][1] - pC*vertex[0][2];



		for (int ypos = ystart; ypos < yend; ypos++)
		{
			for (int xpos = xstart; xpos < xend; xpos++)
			{
				int index = xpos + ypos*(render->display->yres);
				float E12, E13, E23;
				if (rightedged == false)
				{
					E12 = (vertex[0][1] - vertex[1][1])*(xpos - vertex[1][0]) - (vertex[0][0] - vertex[1][0])*(ypos - vertex[1][1]);
					E23 = (vertex[1][1] - vertex[2][1])*(xpos - vertex[2][0]) - (vertex[1][0] - vertex[2][0])*(ypos - vertex[2][1]);
					E13 = (vertex[2][1] - vertex[0][1])*(xpos - vertex[0][0]) - (vertex[2][0] - vertex[0][0])*(ypos - vertex[0][1]);
				}
				else
				{
					E12 = (vertex[1][1] - vertex[0][1])*(xpos - vertex[0][0]) - (vertex[1][0] - vertex[0][0])*(ypos - vertex[0][1]);
					E23 = (vertex[2][1] - vertex[1][1])*(xpos - vertex[1][0]) - (vertex[2][0] - vertex[1][0])*(ypos - vertex[1][1]);
					E13 = (vertex[0][1] - vertex[2][1])*(xpos - vertex[2][0]) - (vertex[0][0] - vertex[2][0])*(ypos - vertex[2][1]);
				}
				if (E12 <= 0 && E13 <= 0 && E23 <= 0)
				{
					//calculate the z for that pixel
					float zpos = (-pD - pA*xpos - pB*ypos) / pC;
					//if z < z in buffer then update the color 
					if (zpos <= (*render).display->fbuf[index].z)
					{
						float u = (-ud - ua*xpos - ub*ypos) / uc;
						float v = (-vd - va*xpos - vb*ypos) / vc;
						float factor = zpos / (MAXINT - zpos);

						float uback = u*(factor + 1);
						float vback = v*(factor + 1);

						GzColor newcolor;
					//	pfunc(uback, vback, newcolor);
						render->tex_fun(uback, vback, newcolor);
						float hong = (-dr - ar*xpos - br*ypos) / cr;
						float lv= (-dg - ag*xpos - bg*ypos) / cg;
						float lan= (-Db - Ab*xpos - Bb*ypos) / Cb;
						(*render).display->fbuf[index].red = hong*newcolor[0];
						(*render).display->fbuf[index].green = lv*newcolor[1];
						(*render).display->fbuf[index].blue = lan*newcolor[2];
						(*render).display->fbuf[index].alpha = 1;
						(*render).display->fbuf[index].z = zpos;
					}
				}


			}

		}

	}





	if (render->interp_mode == GZ_NORMALS)
	{


		float ua, ub, uc, ud, va, vb, vc, vd;

		float vz1 = vertex[0][2] / (MAXINT - vertex[0][2]);
		float vz2 = vertex[1][2] / (MAXINT - vertex[1][2]);
		float vz3 = vertex[2][2] / (MAXINT - vertex[2][2]);

		//texture in perspective
		texture[0][0] = texture[0][0] / (vz1 + 1);
		texture[1][0] = texture[1][0] / (vz2 + 1);
		texture[2][0] = texture[2][0] / (vz3 + 1);
		texture[0][1] = texture[0][1] / (vz1 + 1);
		texture[1][1] = texture[1][1] / (vz2 + 1);
		texture[2][1] = texture[2][1] / (vz3 + 1);  


		//calculate for u interpolation
		float tu1[3] = { vertex[0][0],vertex[0][1],texture[0][0] };
		float tu2[3] = { vertex[1][0],vertex[1][1],texture[1][0] };
		float tu3[3] = { vertex[2][0],vertex[2][1],texture[2][0] };

		float u12[3] = { tu2[0] - tu1[0],tu2[1] - tu1[1],tu2[2] - tu1[2] };
		float u13[3] = { tu3[0] - tu1[0],tu3[1] - tu1[1],tu3[2] - tu1[2] };
		ua = u12[1] * u13[2] - u12[2] * u13[1];
		ub = u12[2] * u13[0] - u12[0] * u13[2];
		uc = u12[0] * u13[1] - u12[1] * u13[0];
		ud = 0 - ua*tu1[0] - ub*tu1[1] - uc*tu1[2];


		//calculate for v interpolation
		float tv1[3] = { vertex[0][0],vertex[0][1],texture[0][1] };
		float tv2[3] = { vertex[1][0],vertex[1][1],texture[1][1] };
		float tv3[3] = { vertex[2][0],vertex[2][1],texture[2][1] };

		float tv12[3] = { tv2[0] - tv1[0],tv2[1] - tv1[1],tv2[2] - tv1[2] };
		float tv13[3] = { tv3[0] - tv1[0],tv3[1] - tv1[1],tv3[2] - tv1[2] };
		va = tv12[1] * tv13[2] - tv12[2] * tv13[1];
		vb = tv12[2] * tv13[0] - tv12[0] * tv13[2];
		vc = tv12[0] * tv13[1] - tv12[1] * tv13[0];
		vd = 0 - va*tv1[0] - vb*tv1[1] - vc*tv1[2];





		//initialize for nx calculation 
		float ax, bx, cx, dx;
		float V1[3] = { vertex[0][0],vertex[0][1],normal[0][0] };
		float V2[3] = { vertex[1][0],vertex[1][1],normal[1][0] };
		float V3[3] = { vertex[2][0],vertex[2][1],normal[2][0] };
		float V1V2[3] = { V2[0] - V1[0],V2[1] - V1[1],V2[2] - V1[2] };
		float V1V3[3] = { V3[0] - V1[0],V3[1] - V1[1],V3[2] - V1[2] };
		ax = V1V2[1] * V1V3[2] - V1V2[2] * V1V3[1];
		bx = V1V2[2] * V1V3[0] - V1V2[0] * V1V3[2];
		cx = V1V2[0] * V1V3[1] - V1V2[1] * V1V3[0];
		dx = 0 - ax*V1[0] - bx*V1[1] - cx*V1[2];

		//initialize for ny calculation
		float ay, by, cy, dy;
		float vn1[3] = { vertex[0][0],vertex[0][1],normal[0][1] };
		float vn2[3] = { vertex[1][0],vertex[1][1],normal[1][1] };
		float vn3[3] = { vertex[2][0],vertex[2][1],normal[2][1] };
		float vn12[3] = { vn2[0] - vn1[0],vn2[1] - vn1[1],vn2[2] - vn1[2] };
		float vn13[3] = { vn3[0] - vn1[0],vn3[1] - vn1[1],vn3[2] - vn1[2] };
		ay = vn12[1] * vn13[2] - vn12[2] * vn13[1];
		by = vn12[2] * vn13[0] - vn12[0] * vn13[2];
		cy = vn12[0] * vn13[1] - vn12[1] * vn13[0];
		dy = 0 - ay*vn1[0] - by*vn1[1] - cy*vn1[2];

		//calculate for nz equation
		float az, bz, cz, dz;
		float zn1[3] = { vertex[0][0],vertex[0][1],normal[0][2] };
		float zn2[3] = { vertex[1][0],vertex[1][1],normal[1][2] };
		float zn3[3] = { vertex[2][0],vertex[2][1],normal[2][2] };
		float zn12[3] = { zn2[0] - zn1[0],zn2[1] - zn1[1],zn2[2] - zn1[2] };
		float zn13[3] = { zn3[0] - zn1[0],zn3[1] - zn1[1],zn3[2] - zn1[2] };
		az = zn12[1] * zn13[2] - zn12[2] * zn13[1];
		bz = zn12[2] * zn13[0] - zn12[0] * zn13[2];
		cz = zn12[0] * zn13[1] - zn12[1] * zn13[0];
		dz = 0 - az*zn1[0] - bz*zn1[1] - cz*zn1[2];







		xstart = min(min(vertex[0][0], vertex[1][0]), vertex[2][0]);
		if (xstart < 0)xstart = 0;

		xend = max(max(vertex[0][0], vertex[1][0]), vertex[2][0]);
		if (xend > 256)xend = 256;

		ystart = min(min(vertex[0][1], vertex[1][1]), vertex[2][1]);
		if (ystart < 0)ystart = 0;

		yend = max(max(vertex[0][1], vertex[1][1]), vertex[2][1]);
		if (yend > 256)yend = 256;


		//bubble sort for vertex
		float x, y, z;

		for (i = 0; i < 2; i++)
			for (j = i + 1; j < 3; j++)
			{
				if (vertex[i][1] > vertex[j][1])
				{

					x = vertex[i][0];
					y = vertex[i][1];
					z = vertex[i][2];
					vertex[i][0] = vertex[j][0];
					vertex[i][1] = vertex[j][1];
					vertex[i][2] = vertex[j][2];

					vertex[j][0] = x;
					vertex[j][1] = y;
					vertex[j][2] = z;

				}
			}
		//after the sort,the vertex sort in y from small to big
		//judge left or right save the middle point information

		//calculate the equation of the line 
		float a, b, c;
		a = vertex[2][1] - vertex[0][1];
		b = vertex[0][0] - vertex[2][0];
		c = vertex[2][0] * vertex[0][1] - vertex[0][0] * vertex[2][1];
		float x1 = (-c - b*vertex[1][1]) / a;
		if (x1 < vertex[1][0])rightedged = true;
		if (x1 > vertex[1][0])rightedged = false;

		//calculate a,b,c,d for the plane

		GzCoord v12 = { vertex[1][0] - vertex[0][0],vertex[1][1] - vertex[0][1],vertex[1][2] - vertex[0][2] };
		GzCoord v13 = { vertex[2][0] - vertex[0][0],vertex[2][1] - vertex[0][1],vertex[2][2] - vertex[0][2] };
		//aybz-azby azbx-axbz axby-aybx
		pA = v12[1] * v13[2] - v12[2] * v13[1];
		pB = v12[2] * v13[0] - v12[0] * v13[2];
		pC = v12[0] * v13[1] - v12[1] * v13[0];
		pD = 0 - pA*vertex[0][0] - pB*vertex[0][1] - pC*vertex[0][2];



		for (int ypos = ystart; ypos < yend; ypos++)
		{
			for (int xpos = xstart; xpos < xend; xpos++)
			{
				int index = xpos + ypos*(render->display->yres);
				float E12, E13, E23;
				if (rightedged == false)
				{
					E12 = (vertex[0][1] - vertex[1][1])*(xpos - vertex[1][0]) - (vertex[0][0] - vertex[1][0])*(ypos - vertex[1][1]);
					E23 = (vertex[1][1] - vertex[2][1])*(xpos - vertex[2][0]) - (vertex[1][0] - vertex[2][0])*(ypos - vertex[2][1]);
					E13 = (vertex[2][1] - vertex[0][1])*(xpos - vertex[0][0]) - (vertex[2][0] - vertex[0][0])*(ypos - vertex[0][1]);
				}
				else
				{
					E12 = (vertex[1][1] - vertex[0][1])*(xpos - vertex[0][0]) - (vertex[1][0] - vertex[0][0])*(ypos - vertex[0][1]);
					E23 = (vertex[2][1] - vertex[1][1])*(xpos - vertex[1][0]) - (vertex[2][0] - vertex[1][0])*(ypos - vertex[1][1]);
					E13 = (vertex[0][1] - vertex[2][1])*(xpos - vertex[2][0]) - (vertex[0][0] - vertex[2][0])*(ypos - vertex[2][1]);
				}
				if (E12 <= 0 && E13 <= 0 && E23 <= 0)
				{
					//calculate the z for that pixel
					float zpos = (-pD - pA*xpos - pB*ypos) / pC;
					//if z < z in buffer then update the color 
					if (zpos <= (*render).display->fbuf[index].z)
					{

						float u = (-ud - ua*xpos - ub*ypos) / uc;
						float v = (-vd - va*xpos - vb*ypos) / vc;
						float factor = zpos / (MAXINT - zpos);

						float uback = u*(factor + 1);
						float vback = v*(factor + 1);

						GzColor newcolor; 
					
						render->tex_fun(uback, vback, newcolor);
					//	pfunc(uback, vback, newcolor);
						
						float nx = (-dx - ax*xpos - bx*ypos) / cx;
						float ny = (-dy - ay*xpos - by*ypos) / cy;
						float nz = (-dz - az*xpos - bz*ypos) / cz;
						float nl = sqrt(nx*nx + ny*ny + nz*nz);
						nx = nx / nl;
						ny = ny / nl;
						nz = nz / nl;
						float narray[3] = { nx,ny,nz };
						render->Ka[0] = newcolor[0];
						render->Ka[1] = newcolor[1];
						render->Ka[2] = newcolor[2];
						render->Kd[0] = newcolor[0];
						render->Kd[1] = newcolor[1];
						render->Kd[2] = newcolor[2];
						float* yanse = ShadeFunction(render, narray);
						(*render).display->fbuf[index].red = ctoi(yanse[0]);
						(*render).display->fbuf[index].green = ctoi(yanse[1]);
						(*render).display->fbuf[index].blue = ctoi(yanse[2]);
						(*render).display->fbuf[index].alpha = 1;
						(*render).display->fbuf[index].z = zpos;
					}
				}

			}

		}

	}


	return GZ_SUCCESS;
}

