#include <GL/glfw.h>

#include <iostream>
#include <cstdlib>
#include <cstdio>

#ifndef GL_SHADING_LANGUAGE_VERSION
#define GL_SHADING_LANGUAGE_VERSION       0x8B8C
#endif

int versions[] = {
	11,
	20,
	30, 31, 32, 33,
	40, 41, 42
};

void test(int major, int minor, bool core, bool fwc)
{
	glfwInit();
	
	bool atLeast3  = (major >= 3);
	bool atLeast32 = (major > 3) || (major == 3 && minor >= 2);

	using namespace std;
	const char* sprof;
	if (atLeast32) sprof = (core ? (fwc ? "FWD CORE" : "CORE    ") : "COMPAT  ");
	else if (atLeast3) sprof = (fwc ? "FWD     " : "        ");
	else sprof = "        ";
	
	cout << "Version: " << major << "." << minor << " " << sprof << " ";
	
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, major);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, minor);
	if (atLeast3) {
		glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, fwc);
	}
	if (atLeast32) {
		glfwOpenWindowHint(GLFW_OPENGL_PROFILE, core ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE);
	}
	if (glfwOpenWindow(640,480,8,8,8,8,24,8,GLFW_WINDOW) == GL_TRUE) {
		cout << glGetString(GL_VERSION) << endl;	
		glfwCloseWindow();
	} else {
		cout << "Can't create" << endl;
	}
	glfwTerminate();
}

void test(int version)
{
	int major = version/10;
	int minor = version%10;
	if ((major > 3) || (major == 3 && minor >= 2)) {
		test(major, minor, false, false); // compat
		test(major, minor, true, false); // core
		test(major, minor, true, true); // core fwd
	} else if (major >= 3) {
		test(major, minor,  /* ignored */ false, false); // regular
		test(major, minor,  /* ignored */ false,  true); // fwd
	} else {
		test(major, minor, /* ignored */ false, /* ignored */ false); // regular
	}
}

const char* coalesce(const GLubyte* c) {
	return c ? (const char*)c : "(n/a)";
}

const char* meta()
{
	glfwInit();
	using namespace std;
	const char* r;
	// ask for default context - probably lastest on compat mode
	if (glfwOpenWindow(640,480,8,8,8,8,24,8,GLFW_WINDOW) == GL_TRUE) {
		cout << "Vendor:     " <<    coalesce(glGetString(GL_VENDOR)) << endl;	// supported since when?
		cout << "Renderer:   " << (r=coalesce(glGetString(GL_RENDERER))) << endl; // supported since when?
		cout << "Version:    " <<    coalesce(glGetString(GL_VERSION)) << endl;
		cout << "GLSL:       " <<    coalesce(glGetString(GL_SHADING_LANGUAGE_VERSION)) << endl; // supported circa 2.0
//		cout << "Extensions: " << "(not implemented)" << endl; // different since GL3.x
		glfwCloseWindow();
	} else {
		cout << "Can't create" << endl;
	}
	glfwTerminate();
	return r;
}


int main(int argc, char** argv)
{
	using namespace std;
	freopen("/dev/null", "w", stderr); // let us silence GLFW's cries about failing contexts
	const char* renderer = meta();
	for (int i=0; i<sizeof(versions)/sizeof(*versions); ++i) {
		test(versions[i]);
	}
	// TODO detect OS, get a standarised filename using the OS and renderer, allow to save to a file w/ a flag
}