#include <string.h>
#include <stdio.h>

#include "PCSNode.h"

// constructor
PCSNode::PCSNode()
	: level( 0 ) {
	this->parent = nullptr;
	this->child = nullptr;
	this->sibling = nullptr;
	memset( &name[0], 0x0, 16 );
}

// copy constructor
PCSNode::PCSNode( const PCSNode &in )
	:parent( in.parent ), child( in.child ), sibling( in.sibling ), level( in.level ) {
	memcpy( name, in.name, 16 );
	name[15] = '\0';
}

// Specialize Constructor
PCSNode::PCSNode( PCSNode* const inParent, PCSNode* const inChild, PCSNode* const inSibling, const char* const inName )
	: parent( inParent ), child( inChild ), sibling( inSibling ), level( inSibling->level ) {
	memcpy( name, inName, 16 );
	name[15] = '\0';
}

PCSNode::PCSNode( const char* const inName )
	: parent( nullptr ), child( nullptr ), sibling( nullptr ), level( 0 ) {
	memcpy( name, inName, 16 );
	name[15] = '\0';
}

// destructor
PCSNode::~PCSNode() { }

// assignment operator
PCSNode &PCSNode::operator = (const PCSNode &in) {
	this->parent = in.parent;
	this->child = in.child;
	this->sibling = in.sibling;
	this->level = in.level;
	memcpy( name, in.name, 16 );
	this->name[15] = '\0';
	return *this;
}

void PCSNode::setParent( PCSNode* const in ) {
	this->parent = in;
}

void PCSNode::setChild( PCSNode* const in ) {
	this->child = in;
}

void PCSNode::setSibling( PCSNode* const in ) {
	this->sibling = in;
}

void PCSNode::setLevel( const int inLevel ) {
	this->level = inLevel;
}

PCSNode* PCSNode::getParent( void ) const {
	return this->parent;
}

PCSNode* PCSNode::getChild( void ) const {
	return this->child;
}

PCSNode* PCSNode::getSibling( void ) const {
	return this->sibling;
}

int PCSNode::getLevel( void ) const {
	return level;
}

PCSNodeReturnCode PCSNode::setName( const char * const inName ) {
	auto tmp = PCSNode_FAIL_NULL_PTR;
	if ( inName ) {
		memcpy( name, inName, 16 );
		name[15] = '\0';
		tmp = PCSNode_SUCCESS;
	}

	return tmp;
}

PCSNodeReturnCode PCSNode::getName( char * const outBuffer, int sizeOutBuffer ) const {
	auto tmp = PCSNode_FAIL_NULL_PTR;
	if ( outBuffer ) {
		if ( sizeOutBuffer <= 0 )					// user is messing with us. cant deliver a negative number of characters.
		{
			memset( outBuffer, 0x0, 16 );	// just copy 0's to the outBuffer. don't want the program to explode.
			outBuffer[15] = '\0';				// include a null terminator just because.
		}

		if ( sizeOutBuffer > 16 )					// asking for name larger than buffer
		{
			memcpy( outBuffer, this->name, 16 );			// only copy name up to length of buffer
			outBuffer[15] = '\0';
		}

		if ( sizeOutBuffer <= 16 )				// asking for name less than or equal to buffer
		{
			memcpy( outBuffer, this->name, sizeOutBuffer - 1 );	// copy name into buffer byte by byte
			outBuffer[sizeOutBuffer - 1] = '\0';
		}

		tmp = PCSNode_SUCCESS;
	}
	return tmp;
}

// the dumpNode() method contains code heavily modeled after Ed Keenan's work displayed in class.
// I made only minor changes to it, so all credit goes to him.
void PCSNode::dumpNode() const {
	char parentName[16];
	char childName[16];
	char siblingName[16];

	if ( this->getParent() )
		this->getParent()->getName( parentName, 16 );
	else
		memcpy( parentName, "0", 2 );

	if ( this->getChild() )
		this->getChild()->getName( childName, 16 );
	else
		memcpy( childName, "0", 2 );

	if ( this->getSibling() )
		this->getSibling()->getName( siblingName, 16 );
	else
		memcpy( siblingName, "0", 2 );

	printf( "\n" );
	printf( "    Name: %s\n", this->name );
	printf( " Address: 0x%p\n", this );
	printf( "  Parent: %s (0x%p)\n", parentName, this->getParent() );
	printf( "   Child: %s (0x%p)\n", childName, this->getChild() );
	printf( " Sibling: %s (0x%p)\n", siblingName, this->getSibling() );
}

void PCSNode::dumpChildren() const {
	if ( this->getChild() ) {
		this->getChild()->dumpNode();
		this->getChild()->dumpSiblings();
	}
}

void PCSNode::dumpSiblings() const {
	if ( this->getSibling() ) {
		this->getSibling()->privDumpSibling();
	}
}

void PCSNode::privDumpSibling() const {
	this->dumpNode();
	if ( this->getSibling() ) {
		this->getSibling()->privDumpSibling();
	}
}

void PCSNode::printDown( PCSNode* const _root ) const {
	_root->dumpNode();

	if ( _root->getChild() )		// if root has a child, go down again.
	{
		printDown( _root->getChild() );
	}

	if ( _root->getSibling() )		// now traverse siblings.
	{
		printDown( _root->getSibling() );
	}
}

int PCSNode::getNumSiblings() const {
	auto count = 1;

	if ( this->getParent() && this->getParent()->getChild() )	// if this is not the root node
	{
		auto walker = this->getParent()->getChild();	// go to first child on list
		while ( walker->getSibling() )		// while there are siblings, count them
		{
			walker = walker->getSibling();
			count++;
		}
	}

	return count;
}

int PCSNode::getNumChildren() const {
	auto count = 0;
	if ( this->getChild() )	// if there are children, count them.
	{
		auto node = this->getChild();
		count++;

		while ( node->getSibling() ) {
			node = node->getSibling();
			count++;
		}
	}

	return count;
}