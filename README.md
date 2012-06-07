GLtester
========

A tiny utility to check OpenGL contexts and versions that are available.

Why?
====

- To help you make sure your GPU driver is sane.
- To let more people know how many GL context types are there.
- Perhaps, to collect stats about what different GPUs support.

What are the OpenGL profiles?
=============================

Since OpenGL 3 introduced a deprecation model in order to remove old, outdated programming API from OpenGL, a lot happened. The Khronos Group took it easy on people and took a lot of effort to make sure that people with huge codebases could benefit from the new versions without rewriting lots of code to a completely new API. This was good.
This also caused a lot of confusion, which is bad.

Some facts:

- OpenGL 3.0 introduced "deprecation", so that some features could be marked as outdated.
- OpenGL 3.1 was the first version that actually removed _some_ old functionality (part of what was deprecated in 3.0).
- OpenGL 3.2 was the first to have two "profiles": core and compatibility.

On top of that, since OpenGL 3.0 there's also the "forward compatible" switch that allows you to ask for a core context with no deprecated functionality altogether.

Read the whole story on [OpenGL wiki](http://www.opengl.org/wiki/Core_And_Compatibility_in_Contexts).

This means that:
- OpenGL 3.0 and 3.1 contexts come in 2 flavours: Core Profile and Core Forward-Compatible Profile.
- OpenGL 3.2 and newer have three steps: Compatibility, Core and Core Forward-Compatible.

And also:

- If you ask for OpenGL 3+ context on a modern card, you should get this exact version,
- IF you ask for an OpenGL 1 or 2 context, you can get a compatibility profile context as well.

**My tip is**

If you are learning modern OpenGL, **use the core profile**, perhaps even a forward-compatible profile. Also be wary which specific OpenGL version you're using.

Yes, I know this is hard- most online resources don't mention this and expect you to have a compatibility profile on; others predate the very idea of profiles. Always take note that some old techniques may be still in use, but implementation on the new API would look different.

Also the modern OpenGL, while being more powerful, requires more effort to set up (as in: some features were removed for the sake of better flexibility).

How to run?
===========

Pick one of the binaries from `bin/` and run it. If there's no binary, you can compile it.

The program will create a couple of windows and close them immediately (warning: some blinking ahead!).
Then it will write some info to standard output, namely:
- your GPU information
- OpenGL version of the context created when a given OpenGL version is requested.

How to compile?
===============

Required libs:
- [GLFW](http://www.glfw.org/download.html) my favourite cross-platform OpenGL window creator

Standard C++; compile using your favourite compiler. Something like:

	g++ -s -Wall src/* -lglfw -lopengl32

It's a single-file mini-app, so I'm not introducing	any build scripts.

Can I contribute my logs?
=========================

Sure, that would be cool. :) Fork me and add the output of the app.

Please stick to the format `RENDERER, PLATFORM.txt`.