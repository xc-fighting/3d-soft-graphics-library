/*   CS580 HW1 display functions to be completed   */

#include   "stdafx.h"  
#include	"Gz.h"
#include	"disp.h"


int GzNewFrameBuffer(char** framebuffer, int width, int height)
{
/* HW1.1 create a framebuffer for MS Windows display:
 -- allocate memory for framebuffer : 3 bytes(b, g, r) x width x height
 -- pass back pointer 
 */
	// allocate width*height*3 memory for framebuffer 3 bytes for each b,g,r (0-255)
	*framebuffer = (char*)malloc(sizeof(byte) * 3 * width*height);
	//if allocate fail return failure
	if (*framebuffer == NULL)return GZ_FAILURE;
	else
	return GZ_SUCCESS;
}

int GzNewDisplay(GzDisplay	**display, int xRes, int yRes)
{
/* HW1.2 create a display:
  -- allocate memory for indicated resolution
  -- pass back pointer to GzDisplay object in display
*/

	//check if xRes & yRes exceed the max limit
	if (xRes < MAXXRES&&yRes < MAXYRES)
	{
		//allocate the memory for display
		(*display) = (GzDisplay*)malloc(sizeof(GzDisplay));
		//set the property of display
		(*display)->xres = xRes;
		(*display)->yres = yRes;
		//allocate the memory of gzpixel buffer
		(*display)->fbuf = (GzPixel*)malloc(sizeof(GzPixel)*xRes*yRes);
		//if allocate fail
		if((**display).fbuf!=NULL)
		return GZ_SUCCESS;
		else return GZ_FAILURE;
	}
	//if exceed return failure
	else return GZ_FAILURE;
	
}


int GzFreeDisplay(GzDisplay	*display)
{
/* HW1.3 clean up, free memory */
	if (display == NULL)return GZ_FAILURE;
	else
	{
		free(display);
		return GZ_SUCCESS;
	}
	
}


int GzGetDisplayParams(GzDisplay *display, int *xRes, int *yRes)
{
/* HW1.4 pass back values for a display */
	if (display == NULL)return GZ_FAILURE;
	else
	{
		*xRes = (*display).xres;
		*yRes = (*display).yres;
		return GZ_SUCCESS;
	}
	
}


int GzInitDisplay(GzDisplay	*display)
{
/* HW1.5 set everything to some default values - start a new frame */
	if (display == NULL)return GZ_FAILURE;
	else
	{
		//also used to draw the background;
		display->fbuf = (GzPixel*)malloc(sizeof(GzPixel) * display->xres*display->yres);
		if (display->fbuf == NULL)return GZ_FAILURE;
		for (int j = 0; j < display->yres; j++)
		{
			for (int i = 0; i < display->xres; i++)
			{
				//find the index of gzpixel buffer ,
				//every r g b multiply 16 for in the next all of the pixel will be divided by 16 ,
				//ensure the back ground will not be another color
				int index = ARRAY(i, j);
				display->fbuf[index].red = 255*16;
				display->fbuf[index].green = 255*16;
				display->fbuf[index].blue = 0;
				display->fbuf[index].alpha = 1;
				display->fbuf[index].z = MAXINT;
			}
		}
		return GZ_SUCCESS;
	}
	
}


int GzPutDisplay(GzDisplay *display, int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z)
{
/* HW1.6 write pixel values into the display */
	//have to check the pixel is in the screen or not?
	//if (i > display->xres || j > display->yres)return GZ_FAILURE;
	if ((i < display->xres) && (i > 0) && (j < display->yres) && (j > 0))
	{
		int index = ARRAY(i, j);
		display->fbuf[index].red = r;
		display->fbuf[index].green = g;
		display->fbuf[index].blue = b;
		display->fbuf[index].alpha = a;
		display->fbuf[index].z = z;
		
	}
	return GZ_SUCCESS;
	
	
}


int GzGetDisplay(GzDisplay *display, int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z)
{
/* HW1.7 pass back a pixel value to the display */
	if (i > display->xres || j > display->yres)return GZ_FAILURE;
	else
	{
		int index = ARRAY(i, j);
		*r = display->fbuf[index].red;
		*g = display->fbuf[index].green;
		*b = display->fbuf[index].blue;
		*a = display->fbuf[index].alpha;
		*z = display->fbuf[index].z;
		return GZ_SUCCESS;
	}
	
}


int GzFlushDisplay2File(FILE* outfile, GzDisplay *display)
{

/* HW1.8 write pixels to ppm file -- "P6 %d %d 255\r" */
	if (outfile == NULL || display == NULL)return GZ_FAILURE;
	//input the head into the file
	fprintf(outfile, "P6 %d %d 255\r", display->xres, display->yres);
	for(int j=0;j<display->yres;j++)
		for (int i = 0; i < display->xres; i++)
		{
			//divided all of the b,g,r by 16 because r,g,b must be within (0-255)
			int index = ARRAY(i, j);
			int b, g, r;
			b = display->fbuf[index].blue / 16;
			g = display->fbuf[index].green / 16;
			r = display->fbuf[index].red / 16;
			//if the result >=255 ,just set them as 255
			if (b >=255)b = 255;
			if (g >=255)g = 255;
			if (r >=255) r = 255;
			fprintf(outfile,"%c%c%c",(char*)r,(char*)g,(char*)b);
		}
	return GZ_SUCCESS;
}

int GzFlushDisplay2FrameBuffer(char* framebuffer, GzDisplay *display)
{

/* HW1.9 write pixels to framebuffer: 
	- put the pixels into the frame buffer
	- CAUTION: when storing the pixels into the frame buffer, the order is blue, green, and red 
	- NOT red, green, and blue !!!
*/
	for(int j=0;j<display->yres;j++)
		for (int i = 0; i < display->xres; i++)
		{
			//divided all of the b,g,r by 16 because r,g,b must be within (0-255)
			int index = ARRAY(i, j);
			int b, g, r;
			b = display->fbuf[index].blue / 16;
			g = display->fbuf[index].green / 16;
			r = display->fbuf[index].red / 16;
			//if the result >=255 ,just set them as 255
			if (b > 255)b = 255;
			if (g > 255)g = 255;
			if (r > 255) r = 255;
			//bcause each pixel represent 3 units in framebuffer,so it has to multiply 3
			framebuffer[3*index] =b;
			framebuffer[3*index + 1] = g;
			framebuffer[3*index + 2] = r;
		}
	return GZ_SUCCESS;
}