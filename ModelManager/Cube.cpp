#include "Cube.h"

#include "Vertex.h"
#include <stdio.h>

Cube::Cube()
	: Model( Model_Cube ) {
	printf( "    Loading cube...\n" );

	this->numVertices = 12 * 2;
	this->vertices = new Vertex[numVertices];

	// -Z face
	vertices[0].pos = Vect( -0.3f, -0.3f, -0.3f );
	vertices[1].pos = Vect( -0.3f, 0.3f, -0.3f );
	vertices[2].pos = Vect( 0.3f, 0.3f, -0.3f );
	vertices[3].pos = Vect( 0.3f, -0.3f, -0.3f );
	vertices[0].normal = Vect( 0, 0, -1 );
	vertices[1].normal = Vect( 0, 0, -1 );
	vertices[2].normal = Vect( 0, 0, -1 );
	vertices[3].normal = Vect( 0, 0, -1 );
	vertices[0].color = Vect( 1, 1, 1 );
	vertices[1].color = Vect( 1, 1, 1 );
	vertices[2].color = Vect( 1, 1, 1 );
	vertices[3].color = Vect( 1, 1, 1 );

	vertices[3].uv = Vect( 0, 0, 0 );
	vertices[0].uv = Vect( 1, 0, 0 );
	vertices[1].uv = Vect( 1, 1, 0 );
	vertices[2].uv = Vect( 0, 1, 0 );

	// +Z face
	vertices[4].pos = Vect( -0.3f, -0.3f, 0.3f );
	vertices[5].pos = Vect( 0.3f, -0.3f, 0.3f );
	vertices[6].pos = Vect( 0.3f, 0.3f, 0.3f );
	vertices[7].pos = Vect( -0.3f, 0.3f, 0.3f );
	vertices[4].normal = Vect( 0, 0, 1 );
	vertices[5].normal = Vect( 0, 0, 1 );
	vertices[6].normal = Vect( 0, 0, 1 );
	vertices[7].normal = Vect( 0, 0, 1 );
	vertices[4].color = Vect( 1, 1, 1 );
	vertices[5].color = Vect( 1, 1, 1 );
	vertices[6].color = Vect( 1, 1, 1 );
	vertices[7].color = Vect( 1, 1, 1 );

	vertices[4].uv = Vect( 0, 0, 0 );
	vertices[5].uv = Vect( 1, 0, 0 );
	vertices[6].uv = Vect( 1, 1, 0 );
	vertices[7].uv = Vect( 0, 1, 0 );

	// -Y face
	vertices[8].pos = Vect( -0.3f, -0.3f, -0.3f );
	vertices[9].pos = Vect( 0.3f, -0.3f, -0.3f );
	vertices[10].pos = Vect( 0.3f, -0.3f, 0.3f );
	vertices[11].pos = Vect( -0.3f, -0.3f, 0.3f );
	vertices[8].normal = Vect( 0, -1, 0 );
	vertices[9].normal = Vect( 0, -1, 0 );
	vertices[10].normal = Vect( 0, -1, 0 );
	vertices[11].normal = Vect( 0, -1, 0 );
	vertices[8].color = Vect( 1, 1, 1 );
	vertices[9].color = Vect( 1, 1, 1 );
	vertices[10].color = Vect( 1, 1, 1 );
	vertices[11].color = Vect( 1, 1, 1 );

	vertices[8].uv = Vect( 0, 0, 0 );
	vertices[9].uv = Vect( 1, 0, 0 );
	vertices[10].uv = Vect( 1, 1, 0 );
	vertices[11].uv = Vect( 0, 1, 0 );

	// +Y face
	vertices[12].pos = Vect( -0.3f, 0.3f, -0.3f );
	vertices[13].pos = Vect( -0.3f, 0.3f, 0.3f );
	vertices[14].pos = Vect( 0.3f, 0.3f, 0.3f );
	vertices[15].pos = Vect( 0.3f, 0.3f, -0.3f );
	vertices[12].normal = Vect( 0, 1, 0 );
	vertices[13].normal = Vect( 0, 1, 0 );
	vertices[14].normal = Vect( 0, 1, 0 );
	vertices[15].normal = Vect( 0, 1, 0 );
	vertices[12].color = Vect( 1, 1, 1 );
	vertices[13].color = Vect( 1, 1, 1 );
	vertices[14].color = Vect( 1, 1, 1 );
	vertices[15].color = Vect( 1, 1, 1 );

	vertices[15].uv = Vect( 0, 0, 0 );
	vertices[12].uv = Vect( 1, 0, 0 );
	vertices[13].uv = Vect( 1, 1, 0 );
	vertices[14].uv = Vect( 0, 1, 0 );

	// -X face
	vertices[16].pos = Vect( -0.3f, -0.3f, -0.3f );
	vertices[17].pos = Vect( -0.3f, -0.3f, 0.3f );
	vertices[18].pos = Vect( -0.3f, 0.3f, 0.3f );
	vertices[19].pos = Vect( -0.3f, 0.3f, -0.3f );
	vertices[16].normal = Vect( -1, 0, 0 );
	vertices[17].normal = Vect( -1, 0, 0 );
	vertices[18].normal = Vect( -1, 0, 0 );
	vertices[19].normal = Vect( -1, 0, 0 );
	vertices[16].color = Vect( 1, 1, 1 );
	vertices[17].color = Vect( 1, 1, 1 );
	vertices[18].color = Vect( 1, 1, 1 );
	vertices[19].color = Vect( 1, 1, 1 );

	vertices[16].uv = Vect( 0, 0, 0 );
	vertices[17].uv = Vect( 1, 0, 0 );
	vertices[18].uv = Vect( 1, 1, 0 );
	vertices[19].uv = Vect( 0, 1, 0 );

	// +X face
	vertices[20].pos = Vect( 0.3f, -0.3f, -0.3f );
	vertices[21].pos = Vect( 0.3f, 0.3f, -0.3f );
	vertices[22].pos = Vect( 0.3f, 0.3f, 0.3f );
	vertices[23].pos = Vect( 0.3f, -0.3f, 0.3f );
	vertices[20].normal = Vect( 1, 0, 0 );
	vertices[21].normal = Vect( 1, 0, 0 );
	vertices[22].normal = Vect( 1, 0, 0 );
	vertices[23].normal = Vect( 1, 0, 0 );
	vertices[20].color = Vect( 1, 1, 1 );
	vertices[21].color = Vect( 1, 1, 1 );
	vertices[22].color = Vect( 1, 1, 1 );
	vertices[23].color = Vect( 1, 1, 1 );

	vertices[23].uv = Vect( 0, 0, 0 );
	vertices[20].uv = Vect( 1, 0, 0 );
	vertices[21].uv = Vect( 1, 1, 0 );
	vertices[22].uv = Vect( 0, 1, 0 );

	this->numFaces = 12 * 3;

	this->faces = new int[numFaces];

	// 6 sides to populate square, this is different from rest of models because hard-coded
	for ( auto i = 0; i < 6; i++ ) {
		faces[6 * i] = 4 * i;
		faces[6 * i + 1] = 4 * i + 1;  // Move over to the next column
		faces[6 * i + 2] = 4 * i + 2;    // Now, move up to the top

		faces[6 * i + 3] = 4 * i;
		faces[6 * i + 4] = 4 * i + 2;
		faces[6 * i + 5] = 4 * i + 3;
	}

	this->setupOpenGLBuffers();
	printf( "    Cube loaded successfully!\n" );
}