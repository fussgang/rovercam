#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <GLFW/glfw3.h>

extern void initsock();

#define psize 19200
char pic[psize]; 
long size;
int got = 0;
int sock, conn;
FILE *fp;
GLFWwindow *win;

void
resized(GLFWwindow *wnd, int w, int h)
{
	glViewport(0,0,w,h);
}

int
main(void)
{
	glfwInit();
	win = glfwCreateWindow(640, 480, "Rover CCTV", 0, 0);
	glfwMakeContextCurrent(win);
	glfwSetWindowSizeCallback(win, resized);

	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	initsock();

	while(!glfwWindowShouldClose(win)){
		got = 0;
		for(;;){
			size = recv(sock, pic+got, psize, 0);
			puts("recv...");
			got += size;
			printf("%d\n", got);
			if(got >= psize) break;
		}

		glTexImage2D(GL_TEXTURE_2D,0,GL_LUMINANCE8,160,120,0,GL_LUMINANCE,GL_UNSIGNED_BYTE,pic);

		glBegin(GL_POLYGON);
		glTexCoord2f(1, 1); glVertex3f(1, 1, 0);
		glTexCoord2f(1, 0); glVertex3f(1, -1, 0);
		glTexCoord2f(0, 0); glVertex3f(-1, -1, 0);
		glTexCoord2f(0, 1); glVertex3f(-1, 1, 0);
		glEnd();
		glFlush();

		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	close(conn);
}