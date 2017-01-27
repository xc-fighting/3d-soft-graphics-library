/* Texture functions for cs580 GzLib	*/
#include    "stdafx.h" 
#include	"stdio.h"
#include	"Gz.h"

GzColor	*image=NULL;
int xs, ys;
int reset = 1;

/* Image texture function */
int tex_fun(float u, float v,GzColor newcolor)
{
  unsigned char		pixel[3];
  unsigned char     dummy;
  char  		foo[8];
  int   		i, j;
  FILE			*fd;

  if (reset) {          /* open and load texture file */
    fd = fopen ("texture", "rb");
    if (fd == NULL) {
      fprintf (stderr, "texture file not found\n");
      exit(-1);
    }
    fscanf (fd, "%s %d %d %c", foo, &xs, &ys, &dummy);
    image = (GzColor*)malloc(sizeof(GzColor)*(xs+1)*(ys+1));
    if (image == NULL) {
      fprintf (stderr, "malloc for texture image failed\n");
      exit(-1);
    }

    for (i = 0; i < xs*ys; i++) {	/* create array of GzColor values */
      fread(pixel, sizeof(pixel), 1, fd);
      image[i][RED] = (float)((int)pixel[RED]) * (1.0 / 255.0);
      image[i][GREEN] = (float)((int)pixel[GREEN]) * (1.0 / 255.0);
      image[i][BLUE] = (float)((int)pixel[BLUE]) * (1.0 / 255.0);
      }

    reset = 0;          /* init is done */
	fclose(fd);
  }

/* bounds-test u,v to make sure nothing will overflow image array bounds */
/* determine texture cell corner values and perform bilinear interpolation */
/* set color to interpolated GzColor value and return */

  //u,v bound test
  if (u < 0)u = 0;
  if (u > 1)u = 1;
  if (v < 0)v = 0;
  if (v > 1)v = 1;
 
  //do the interpolation of uv to get the color
  float tX = u*(xs - 1);
  float tY = v*(ys - 1);
  int ax,ay,bx,by,cx,cy,dx,dy;
  ax = tX;
  ay = tY;
  bx = ax + 1;
  by = ay;
  cx = ax + 1;
  cy = ay + 1;
  dx = ax;
  dy = ay + 1;
  float s = tX - ax;
  float t = tY - ay;
  
  newcolor[RED] = s*t*image[cx+cy*xs][RED] + (1 - s)*t*image[dx+dy*xs][RED] + s*(1 - t)*image[bx+by*xs][RED] + (1 - t)*(1 - s)*image[ax+ay*xs][RED];
  newcolor[GREEN]= s*t*image[cx+cy*xs][GREEN] + (1 - s)*t*image[dx+dy*xs][GREEN] + s*(1 - t)*image[bx+by*xs][GREEN] + (1 - t)*(1 - s)*image[ax+ay*xs][GREEN];
  newcolor[BLUE] = s*t*image[cx+cy*xs][BLUE] + (1 - s)*t*image[dx+dy*xs][BLUE] + s*(1 - t)*image[bx+by*xs][BLUE] + (1 - t)*(1 - s)*image[ax+ay*xs][BLUE];
 
 

  return GZ_SUCCESS;

}



/* Procedural texture function */
int ptex_fun(float u, float v, GzColor color)
{
/*	float Creal = -0.7;
	float Cimage = 0.27015;
	int N = 9999;
	float Xreal, Ximage;
	Xreal = u; Ximage = v;
	
	/*GzColor innerColor = { 0,0,1 };
	GzColor outerColor1 = { 0.1,0,0};
	GzColor outerColor2 = { 0,1,0 };


	float tempR; float length=0;
	int i = 0;
	for (i = 0; i < N; i++)
	{ 
		tempR = Xreal;
		Xreal = tempR*tempR - Ximage*Ximage + Creal;
		Ximage = 2 * tempR*Ximage + Cimage;
		length=  Xreal*Xreal + Ximage*Ximage;
		if (length > 2)break;
	}
	float zfactor = i / N;
	color[0] = zfactor;
	color[1] = zfactor;
	color[2] = zfactor;





	/*if (length < 1)
	{
		color[0] = innerColor[0];
		color[1] = innerColor[1];
		color[2] = innerColor[2];

	}
	else
	{
		float fraction = i*0.07;
		int Integer = fraction;
		float frag = fraction - Integer;
		color[0] = frag*outerColor1[0] + (1 - frag)*outerColor2[0];
		color[1]= frag*outerColor1[1] + (1 - frag)*outerColor2[1];
		color[2]= frag*outerColor1[2] + (1 - frag)*outerColor2[2];
	}
	/*GzColor bColor = {0.678,0.231,0.129};
	GzColor mcolor = { 1,1,1 };
	int a = v * 100;
	if (a % 2 == 0)
	{
		color[0] = bColor[0];
		color[1] = bColor[1];
		color[2] = bColor[2];

	}
	else
	{
		color[1] = mcolor[0];
		color[1] = mcolor[1];
		color[2] = mcolor[2];
	}
		*/

	if (reset == 1)
	{
		xs = 64;
		ys = 64;
		image = (GzColor*)malloc(sizeof(GzColor)*(xs + 1)*(ys + 1));
		for(int j=0;j<ys;j++)
			for (int i = 0; i < xs; i++)
			{
				if (((i & 0x8) == 0) ^ ((j & 0x8) == 0))
				{
					image[j*xs + i][RED] = 1;
					image[j*xs + i][GREEN] = 0;
					image[j*xs + i][BLUE] = 0;
				}
				else
				{
					image[j*xs + i][RED] = 0;
					image[j*xs + i][GREEN] = 0;
					image[j*xs + i][BLUE] = 1;
				}
			}
		reset = 0;
	}

	//u,v bound test
	if (u < 0)u = 0;
	if (u > 1)u = 1;
	if (v < 0)v = 0;
	if (v > 1)v = 1;

	//do the interpolation of uv to get the color
	float tX = u*(xs - 1);
	float tY = v*(ys - 1);
	int ax, ay, bx, by, cx, cy, dx, dy;
	ax = tX;
	ay = tY;
	bx = ax + 1;
	by = ay;
	cx = ax + 1;
	cy = ay + 1;
	dx = ax;
	dy = ay + 1;
	float s = tX - ax;
	float t = tY - ay;

	color[RED] = s*t*image[cx + cy*xs][RED] + (1 - s)*t*image[dx + dy*xs][RED] + s*(1 - t)*image[bx + by*xs][RED] + (1 - t)*(1 - s)*image[ax + ay*xs][RED];
	color[GREEN] = s*t*image[cx + cy*xs][GREEN] + (1 - s)*t*image[dx + dy*xs][GREEN] + s*(1 - t)*image[bx + by*xs][GREEN] + (1 - t)*(1 - s)*image[ax + ay*xs][GREEN];
	color[BLUE] = s*t*image[cx + cy*xs][BLUE] + (1 - s)*t*image[dx + dy*xs][BLUE] + s*(1 - t)*image[bx + by*xs][BLUE] + (1 - t)*(1 - s)*image[ax + ay*xs][BLUE];




	return GZ_SUCCESS;
}

/* Free texture memory */
int GzFreeTexture()
{
	if(image!=NULL)
		free(image);
	return GZ_SUCCESS;
}

