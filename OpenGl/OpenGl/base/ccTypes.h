#ifndef _TYPE_H_
#define _TYPE_H_

#include "math/Vec2.h"
#include "math/Vec3.h"
#include "GL/GL.h"

struct Color4B;
struct Color4F;

/** RGB color composed of bytes 3 bytes
@since v3.0
*/
struct CC_DLL Color3B
{
	Color3B();
	Color3B(GLubyte _r, GLubyte _g, GLubyte _b);
	explicit Color3B(const Color4B& color);
	explicit Color3B(const Color4F& color);

	bool operator==(const Color3B& right) const;
	bool operator==(const Color4B& right) const;
	bool operator==(const Color4F& right) const;
	bool operator!=(const Color3B& right) const;
	bool operator!=(const Color4B& right) const;
	bool operator!=(const Color4F& right) const;

	bool equals(const Color3B& other)
	{
		return (*this == other);
	}

	GLubyte r;
	GLubyte g;
	GLubyte b;

	static const Color3B WHITE;
	static const Color3B YELLOW;
	static const Color3B BLUE;
	static const Color3B GREEN;
	static const Color3B RED;
	static const Color3B MAGENTA;
	static const Color3B BLACK;
	static const Color3B ORANGE;
	static const Color3B GRAY;
};

/** RGBA color composed of 4 bytes
@since v3.0
*/
struct CC_DLL Color4B
{
	Color4B();
	Color4B(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a);
	explicit Color4B(const Color3B& color);
	explicit Color4B(const Color4F& color);

	bool operator==(const Color4B& right) const;
	bool operator==(const Color3B& right) const;
	bool operator==(const Color4F& right) const;
	bool operator!=(const Color4B& right) const;
	bool operator!=(const Color3B& right) const;
	bool operator!=(const Color4F& right) const;

	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;

	static const Color4B WHITE;
	static const Color4B YELLOW;
	static const Color4B BLUE;
	static const Color4B GREEN;
	static const Color4B RED;
	static const Color4B MAGENTA;
	static const Color4B BLACK;
	static const Color4B ORANGE;
	static const Color4B GRAY;
};


/** RGBA color composed of 4 floats
@since v3.0
*/
struct CC_DLL Color4F
{
	Color4F();
	Color4F(float _r, float _g, float _b, float _a);
	explicit Color4F(const Color3B& color);
	explicit Color4F(const Color4B& color);

	bool operator==(const Color4F& right) const;
	bool operator==(const Color3B& right) const;
	bool operator==(const Color4B& right) const;
	bool operator!=(const Color4F& right) const;
	bool operator!=(const Color3B& right) const;
	bool operator!=(const Color4B& right) const;

	bool equals(const Color4F &other)
	{
		return (*this == other);
	}

	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;

	static const Color4F WHITE;
	static const Color4F YELLOW;
	static const Color4F BLUE;
	static const Color4F GREEN;
	static const Color4F RED;
	static const Color4F MAGENTA;
	static const Color4F BLACK;
	static const Color4F ORANGE;
	static const Color4F GRAY;
};

/** A vertex composed of 2 floats: x, y
@since v3.0
*/
// struct Vertex2F
// {
//     Vertex2F(float _x, float _y) :x(_x), y(_y) {}

//     Vertex2F(): x(0.f), y(0.f) {}

//     GLfloat x;
//     GLfloat y;
// };


/** A vertex composed of 2 floats: x, y
@since v3.0
*/
// struct Vertex3F
// {
//     Vertex3F(float _x, float _y, float _z)
//         : x(_x)
//         , y(_y)
//         , z(_z)
//     {}

//     Vertex3F(): x(0.f), y(0.f), z(0.f) {}

//     GLfloat x;
//     GLfloat y;
//     GLfloat z;
// };

/** A texcoord composed of 2 floats: u, y
@since v3.0
*/
struct CC_DLL Tex2F {
	Tex2F(float _u, float _v) : u(_u), v(_v) {}

	Tex2F() : u(0.f), v(0.f) {}

	GLfloat u;
	GLfloat v;
};


//! Vec2 Sprite component
struct CC_DLL PointSprite
{
	Vec2   pos;        // 8 bytes
	Color4B    color;      // 4 bytes
	GLfloat    size;       // 4 bytes
};

//!    A 2D Quad. 4 * 2 floats
struct CC_DLL Quad2
{
	Vec2        tl;
	Vec2        tr;
	Vec2        bl;
	Vec2        br;
};


//!    A 3D Quad. 4 * 3 floats
struct CC_DLL Quad3 {
	Vec3        bl;
	Vec3        br;
	Vec3        tl;
	Vec3        tr;
};

//! a Vec2 with a vertex point, a tex coord point and a color 4B
struct V2F_C4B_T2F
{
	//! vertices (2F)
	Vec2       vertices;
	//! colors (4B)
	Color4B        colors;
	//! tex coords (2F)
	Tex2F          texCoords;
};


struct V2F_C4B_PF
{
	//! vertices (2F)
	Vec2       vertices;
	//! colors (4B)
	Color4B        colors;
	//! pointsize
	float      pointSize;
};

//! a Vec2 with a vertex point, a tex coord point and a color 4F
struct CC_DLL V2F_C4F_T2F
{
	//! vertices (2F)
	Vec2       vertices;
	//! colors (4F)
	Color4F        colors;
	//! tex coords (2F)
	Tex2F          texCoords;
};

//! a Vec2 with a vertex point, a tex coord point and a color 4B
struct CC_DLL V3F_C4B_T2F
{
	//! vertices (3F)
	Vec3     vertices;            // 12 bytes

	//! colors (4B)
	Color4B      colors;              // 4 bytes

	// tex coords (2F)
	Tex2F        texCoords;           // 8 bytes
};

//! a Vec2 with a vertex point, a tex coord point
struct CC_DLL V3F_T2F
{
	//! vertices (2F)
	Vec3       vertices;
	//! tex coords (2F)
	Tex2F          texCoords;
};

//! A Triangle of V2F_C4B_T2F
struct CC_DLL V2F_C4B_T2F_Triangle
{
	//! Vec2 A
	V2F_C4B_T2F a;
	//! Vec2 B
	V2F_C4B_T2F b;
	//! Vec2 B
	V2F_C4B_T2F c;
};

//! A Quad of V2F_C4B_T2F
struct CC_DLL V2F_C4B_T2F_Quad
{
	//! bottom left
	V2F_C4B_T2F    bl;
	//! bottom right
	V2F_C4B_T2F    br;
	//! top left
	V2F_C4B_T2F    tl;
	//! top right
	V2F_C4B_T2F    tr;
};

//! 4 Vertex3FTex2FColor4B
struct CC_DLL V3F_C4B_T2F_Quad
{
	//! top left
	V3F_C4B_T2F    tl;
	//! bottom left
	V3F_C4B_T2F    bl;
	//! top right
	V3F_C4B_T2F    tr;
	//! bottom right
	V3F_C4B_T2F    br;
};

//! 4 Vertex2FTex2FColor4F Quad
struct CC_DLL V2F_C4F_T2F_Quad
{
	//! bottom left
	V2F_C4F_T2F    bl;
	//! bottom right
	V2F_C4F_T2F    br;
	//! top left
	V2F_C4F_T2F    tl;
	//! top right
	V2F_C4F_T2F    tr;
};

struct CC_DLL V3F_T2F_Quad
{
	//! bottom left
	V3F_T2F    bl;
	//! bottom right
	V3F_T2F    br;
	//! top left
	V3F_T2F    tl;
	//! top right
	V3F_T2F    tr;
};

#endif