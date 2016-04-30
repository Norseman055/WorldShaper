//---------------------------------------------------------------------------
// HEADER FILES:
//---------------------------------------------------------------------------
#include <string.h>
#include "UnitTest.h"
#include "PCSTree.h"
#include "PCSNode.h"

//---------------------------------------------------------------------------
// Test Files:
// Single step through, set break points, but do not modify it
//---------------------------------------------------------------------------

TEST( version, PCSNode_group ) {
	CHECK( PCSNODE_VERSION == 1.5 );
}

TEST( defaultConstructor, PCSNode_group ) {
	PCSNode node;

	CHECK( node.getChild() == nullptr );
	CHECK( node.getParent() == nullptr );
	CHECK( node.getSibling() == nullptr );

	char buff[16];
	PCSNodeReturnCode returnCode;
	returnCode = node.getName( buff, PCSNODE_NAME_SIZE );
	char testbuff[16];
	memset( &testbuff[0], 0x0, PCSNODE_NAME_SIZE );

	CHECK( memcmp( buff, testbuff, PCSNODE_NAME_SIZE ) == 0 );
	CHECK( returnCode == PCSNode_SUCCESS );
}

TEST( setChild, PCSNode_group ) {
	PCSNode nodeA;
	PCSNode nodeB;

	CHECK( &nodeA != &nodeB );
	CHECK( nodeA.getChild() == nullptr );
	CHECK( nodeA.getParent() == nullptr );
	CHECK( nodeA.getSibling() == nullptr );

	nodeA.setChild( &nodeB );

	CHECK( nodeA.getChild() == &nodeB );
	CHECK( nodeA.getParent() == nullptr );
	CHECK( nodeA.getSibling() == nullptr );
}

TEST( getChild, PCSNode_group ) {
	PCSNode nodeA;
	PCSNode nodeB;
	PCSNode *nodeC;

	CHECK( &nodeA != &nodeB );
	CHECK( nodeA.getChild() == nullptr );
	CHECK( nodeA.getParent() == nullptr );
	CHECK( nodeA.getSibling() == nullptr );

	nodeA.setChild( &nodeB );
	nodeC = nodeA.getChild();

	CHECK( nodeC == &nodeB );
	CHECK( nodeA.getChild() == &nodeB );
	CHECK( nodeA.getParent() == nullptr );
	CHECK( nodeA.getSibling() == nullptr );
}

TEST( setParent, PCSNode_group ) {
	PCSNode nodeA;
	PCSNode nodeB;

	CHECK( &nodeA != &nodeB );
	CHECK( nodeA.getChild() == nullptr );
	CHECK( nodeA.getParent() == nullptr );
	CHECK( nodeA.getSibling() == nullptr );

	nodeA.setParent( &nodeB );

	CHECK( nodeA.getParent() == &nodeB );
	CHECK( nodeA.getChild() == nullptr );
	CHECK( nodeA.getSibling() == nullptr );
}

TEST( getParent, PCSNode_group ) {
	PCSNode nodeA;
	PCSNode nodeB;
	PCSNode *nodeC;

	CHECK( &nodeA != &nodeB );
	CHECK( nodeA.getChild() == nullptr );
	CHECK( nodeA.getParent() == nullptr );
	CHECK( nodeA.getSibling() == nullptr );

	nodeA.setParent( &nodeB );
	nodeC = nodeA.getParent();

	CHECK( nodeC == &nodeB );
	CHECK( nodeA.getParent() == &nodeB );
	CHECK( nodeA.getChild() == nullptr );
	CHECK( nodeA.getSibling() == nullptr );
}

TEST( setSibling, PCSNode_group ) {
	PCSNode nodeA;
	PCSNode nodeB;

	CHECK( &nodeA != &nodeB );
	CHECK( nodeA.getChild() == nullptr );
	CHECK( nodeA.getParent() == nullptr );
	CHECK( nodeA.getSibling() == nullptr );

	nodeA.setSibling( &nodeB );

	CHECK( nodeA.getSibling() == &nodeB );
	CHECK( nodeA.getParent() == nullptr );
	CHECK( nodeA.getChild() == nullptr );
}

TEST( getSibling, PCSNode_group ) {
	PCSNode nodeA;
	PCSNode nodeB;
	PCSNode *nodeC;

	CHECK( &nodeA != &nodeB );
	CHECK( nodeA.getChild() == nullptr );
	CHECK( nodeA.getParent() == nullptr );
	CHECK( nodeA.getSibling() == nullptr );

	nodeA.setSibling( &nodeB );
	nodeC = nodeA.getSibling();

	CHECK( nodeC == &nodeB );
	CHECK( nodeA.getSibling() == &nodeB );
	CHECK( nodeA.getParent() == nullptr );
	CHECK( nodeA.getChild() == nullptr );
}

TEST( assignOperator, PCSNode_group ) {
	PCSNode nodeA( "node_A" );
	PCSNode nodeB( "node_B" );
	PCSNode nodeC( "node_C" );
	PCSNode node( "TestNode" );

	CHECK( &nodeA != &nodeB );
	CHECK( &nodeA != &nodeC );
	CHECK( &nodeC != &nodeB );
	CHECK( node.getChild() == nullptr );
	CHECK( node.getParent() == nullptr );
	CHECK( node.getSibling() == nullptr );

	node.setParent( &nodeA );
	node.setChild( &nodeB );
	node.setSibling( &nodeC );

	CHECK( node.getSibling() == &nodeC );
	CHECK( node.getParent() == &nodeA );
	CHECK( node.getChild() == &nodeB );

	CHECK( nodeA.getSibling() == 0 );
	CHECK( nodeA.getParent() == 0 );
	CHECK( nodeA.getChild() == 0 );

	CHECK( nodeB.getSibling() == 0 );
	CHECK( nodeB.getParent() == 0 );
	CHECK( nodeB.getChild() == 0 );

	CHECK( nodeC.getSibling() == 0 );
	CHECK( nodeC.getParent() == 0 );
	CHECK( nodeC.getChild() == 0 );

	PCSNode copyNode;
	// assignment
	copyNode = node;

	CHECK( node.getSibling() == copyNode.getSibling() );
	CHECK( node.getParent() == copyNode.getParent() );
	CHECK( node.getChild() == copyNode.getChild() );

	char buff[16];
	PCSNodeReturnCode returnCode;
	returnCode = copyNode.getName( buff, 16 );
	CHECK( strcmp( buff, "TestNode" ) == 0 );
	CHECK( returnCode == PCSNode_SUCCESS );

	CHECK( nodeA.getSibling() == 0 );
	CHECK( nodeA.getParent() == 0 );
	CHECK( nodeA.getChild() == 0 );

	CHECK( nodeB.getSibling() == 0 );
	CHECK( nodeB.getParent() == 0 );
	CHECK( nodeB.getChild() == 0 );

	CHECK( nodeC.getSibling() == 0 );
	CHECK( nodeC.getParent() == 0 );
	CHECK( nodeC.getChild() == 0 );
}

TEST( destructor, PCSNode_group ) {
	PCSNode *pn = new PCSNode();
	PCSNode nodeB;
	PCSNode nodeC;
	PCSNode nodeA;

	CHECK( &nodeA != &nodeB );
	CHECK( &nodeA != &nodeC );
	CHECK( &nodeC != &nodeB );
	CHECK( pn->getChild() == 0 );
	CHECK( pn->getParent() == 0 );
	CHECK( pn->getSibling() == 0 );

	pn->setParent( &nodeA );
	pn->setChild( &nodeB );
	pn->setSibling( &nodeC );

	CHECK( pn->getSibling() == &nodeC );
	CHECK( pn->getParent() == &nodeA );
	CHECK( pn->getChild() == &nodeB );

	delete pn;
}

TEST( copyConstructor, PCSNode_group ) {
	PCSNode nodeB;
	PCSNode nodeC;
	PCSNode nodeA;
	PCSNode *pn = new PCSNode();

	CHECK( &nodeA != &nodeB );
	CHECK( &nodeA != &nodeC );
	CHECK( &nodeC != &nodeB );
	CHECK( pn->getChild() == 0 );
	CHECK( pn->getParent() == 0 );
	CHECK( pn->getSibling() == 0 );

	pn->setParent( &nodeA );
	pn->setChild( &nodeB );
	pn->setSibling( &nodeC );

	CHECK( pn->getSibling() == &nodeC );
	CHECK( pn->getParent() == &nodeA );
	CHECK( pn->getChild() == &nodeB );

	PCSNode pn2( *pn );

	char buff[16];
	PCSNodeReturnCode returnCode;
	returnCode = pn2.getName( buff, PCSNODE_NAME_SIZE );
	CHECK( returnCode == PCSNode_SUCCESS );

	char buff2[16];
	returnCode = pn->getName( buff2, PCSNODE_NAME_SIZE );
	CHECK( returnCode == PCSNode_SUCCESS );

	CHECK( memcmp( buff, buff2, PCSNODE_NAME_SIZE ) == 0 );

	CHECK( pn->getSibling() == &nodeC );
	CHECK( pn->getParent() == &nodeA );
	CHECK( pn->getChild() == &nodeB );

	CHECK( pn2.getSibling() == &nodeC );
	CHECK( pn2.getParent() == &nodeA );
	CHECK( pn2.getChild() == &nodeB );

	delete pn;
}

TEST( setName_normal, PCSNode_group ) {
	PCSNode pn;

	CHECK( pn.getChild() == 0 );
	CHECK( pn.getParent() == 0 );
	CHECK( pn.getSibling() == 0 );

	PCSNodeReturnCode returnCode;

	returnCode = pn.setName( "Node_A" );

	CHECK( returnCode == PCSNode_SUCCESS );
	char buff[16];

	returnCode = pn.getName( buff, 16 );

	CHECK( strcmp( buff, "Node_A" ) == 0 );
	CHECK( returnCode == PCSNode_SUCCESS );
}

TEST( setName_normal_null, PCSNode_group ) {
	PCSNode pn;

	CHECK( pn.getChild() == 0 );
	CHECK( pn.getParent() == 0 );
	CHECK( pn.getSibling() == 0 );

	char *buff_null = 0;
	PCSNodeReturnCode returnCode;

	returnCode = pn.setName( buff_null );
	CHECK( returnCode == PCSNode_FAIL_NULL_PTR );

	char buff[16];

	returnCode = pn.getName( buff, 16 );

	CHECK( returnCode == PCSNode_SUCCESS );
}

TEST( setName_too_Big, PCSNode_group ) {
	PCSNode pn;

	CHECK( pn.getChild() == 0 );
	CHECK( pn.getParent() == 0 );
	CHECK( pn.getSibling() == 0 );

	PCSNodeReturnCode returnCode;

	returnCode = pn.setName( "Node_A_12345678901234567890" );
	CHECK( returnCode == PCSNode_SUCCESS );
	char buff[16];

	returnCode = pn.getName( buff, 16 );

	CHECK( strcmp( buff, "Node_A_12345678" ) == 0 );
	CHECK( returnCode == PCSNode_SUCCESS );
}

TEST( getName_normal, PCSNode_group ) {
	PCSNode pn;

	CHECK( pn.getChild() == 0 );
	CHECK( pn.getParent() == 0 );
	CHECK( pn.getSibling() == 0 );

	pn.setName( "123456789012345" );

	char buff[16];
	PCSNodeReturnCode returnCode;

	returnCode = pn.getName( buff, 16 );

	CHECK( strcmp( buff, "123456789012345" ) == 0 );
	CHECK( returnCode == PCSNode_SUCCESS );
}

TEST( getName_normal_null, PCSNode_group ) {
	PCSNode pn;

	CHECK( pn.getChild() == 0 );
	CHECK( pn.getParent() == 0 );
	CHECK( pn.getSibling() == 0 );

	pn.setName( "123456789012345" );

	char *buff_null = 0;

	PCSNodeReturnCode returnCode;

	returnCode = pn.getName( buff_null, 16 );

	CHECK( buff_null == 0 );
	CHECK( returnCode == PCSNode_FAIL_NULL_PTR );
}

TEST( getName_too_small, PCSNode_group ) {
	PCSNode pn;

	CHECK( pn.getChild() == 0 );
	CHECK( pn.getParent() == 0 );
	CHECK( pn.getSibling() == 0 );

	pn.setName( "123456789012345" );

	char buff[8];
	PCSNodeReturnCode returnCode;

	returnCode = pn.getName( buff, 8 );

	CHECK( strcmp( buff, "1234567" ) == 0 );

	CHECK( returnCode == PCSNode_SUCCESS );
}

TEST( getName_too_big, PCSNode_group ) {
	PCSNode pn;

	CHECK( pn.getChild() == 0 );
	CHECK( pn.getParent() == 0 );
	CHECK( pn.getSibling() == 0 );

	pn.setName( "123456789012345" );

	char buff[80];
	PCSNodeReturnCode returnCode;

	returnCode = pn.getName( buff, 80 );

	CHECK( strcmp( buff, "123456789012345" ) == 0 );

	CHECK( returnCode == PCSNode_SUCCESS );
}

TEST( print, PCSNode_group ) {
	PCSNode n;

	PCSNode nodeA;
	PCSNode nodeB;
	PCSNode nodeC;

	nodeA.setName( "Node_A" );
	nodeB.setName( "Node_B" );
	nodeC.setName( "Node_C" );
	n.setName( "Node_X" );

	n.setParent( &nodeA );
	n.setSibling( &nodeB );
	n.setChild( &nodeC );

	CHECK( n.getChild() == &nodeC );
	CHECK( n.getParent() == &nodeA );
	CHECK( n.getSibling() == &nodeB );

	n.dumpNode();

	CHECK( n.getChild() == &nodeC );
	CHECK( n.getParent() == &nodeA );
	CHECK( n.getSibling() == &nodeB );
}

TEST( specializeConstuctor, PCSNode_group ) {
	PCSNode nodeA;
	PCSNode nodeB;
	PCSNode nodeC;

	PCSNode n( &nodeA, &nodeB, &nodeC, "Node_Z" );

	nodeA.setName( "Node_A" );
	nodeB.setName( "Node_B" );
	nodeC.setName( "Node_C" );

	CHECK( n.getChild() == &nodeB );
	CHECK( n.getParent() == &nodeA );
	CHECK( n.getSibling() == &nodeC );

	char tmpName[PCSNODE_NAME_SIZE];

	n.getName( tmpName, PCSNODE_NAME_SIZE );

	CHECK( strcmp( tmpName, "Node_Z" ) == 0 );
}

TEST( specializeConstuctorName, PCSNode_group ) {
	PCSNode nodeA;
	PCSNode nodeB;
	PCSNode nodeC;

	PCSNode n( "Node_X" );

	CHECK( n.getChild() == 0 );
	CHECK( n.getParent() == 0 );
	CHECK( n.getSibling() == 0 );

	nodeA.setName( "Node_A" );
	nodeB.setName( "Node_B" );
	nodeC.setName( "Node_C" );

	n.setParent( &nodeA );
	n.setSibling( &nodeC );
	n.setChild( &nodeB );

	CHECK( n.getChild() == &nodeB );
	CHECK( n.getParent() == &nodeA );
	CHECK( n.getSibling() == &nodeC );

	char tmpName[PCSNODE_NAME_SIZE];
	n.getName( tmpName, PCSNODE_NAME_SIZE );
	CHECK( strcmp( tmpName, "Node_X" ) == 0 );
}

TEST( printNode_with0Links, PCSNode_group ) {
	PCSNode n( "Node_X" );

	CHECK( n.getChild() == 0 );
	CHECK( n.getParent() == 0 );
	CHECK( n.getSibling() == 0 );

	n.dumpNode();
}

TEST( fullTree_dumpChildren, PCSNode_group ) {
	PCSTree tree;
	PCSTreeInfo info;
	PCSNode  *root;

	PCSNode nodeRoot( "Root" );
	PCSNode nodeA( "Node_A" );
	PCSNode nodeB( "Node_B" );
	PCSNode nodeC( "Node_C" );
	PCSNode nodeD( "Node_D" );
	PCSNode nodeE( "Node_E" );
	PCSNode nodeI( "Node_I" );
	PCSNode nodeK( "Node_K" );
	PCSNode nodeL( "Node_L" );
	PCSNode nodeR( "Node_R" );
	PCSNode nodeF( "Node_F" );
	PCSNode nodeG( "Node_G" );
	PCSNode nodeJ( "Node_J" );
	PCSNode nodeM( "Node_M" );
	PCSNode nodeN( "Node_N" );
	PCSNode nodeO( "Node_O" );
	PCSNode nodeP( "Node_P" );
	PCSNode nodeQ( "Node_Q" );
	PCSNode nodeH( "Node_H" );
	PCSNode nodeS( "Node_S" );
	PCSNode nodeT( "Node_T" );
	PCSNode nodeU( "Node_U" );
	PCSNode nodeV( "Node_V" );
	PCSNode nodeW( "Node_W" );

	root = tree.getRoot();

	tree.insert( &nodeRoot, root );

	tree.insert( &nodeC, &nodeRoot );
	tree.insert( &nodeB, &nodeRoot );
	tree.insert( &nodeA, &nodeRoot );
	tree.insert( &nodeI, &nodeA );
	tree.insert( &nodeE, &nodeA );
	tree.insert( &nodeD, &nodeA );
	tree.insert( &nodeL, &nodeB );
	tree.insert( &nodeK, &nodeB );
	tree.insert( &nodeR, &nodeC );
	tree.insert( &nodeF, &nodeD );
	tree.insert( &nodeJ, &nodeI );
	tree.insert( &nodeG, &nodeI );
	tree.insert( &nodeN, &nodeL );
	tree.insert( &nodeM, &nodeL );
	tree.insert( &nodeQ, &nodeR );
	tree.insert( &nodeP, &nodeR );
	tree.insert( &nodeO, &nodeR );
	tree.insert( &nodeH, &nodeF );
	tree.insert( &nodeS, &nodeP );
	tree.insert( &nodeW, &nodeS );
	tree.insert( &nodeV, &nodeS );
	tree.insert( &nodeU, &nodeS );
	tree.insert( &nodeT, &nodeS );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 24 );

	CHECK( nodeRoot.getChild() == &nodeA );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == &nodeD );
	CHECK( nodeA.getParent() == &nodeRoot );
	CHECK( nodeA.getSibling() == &nodeB );

	CHECK( nodeB.getChild() == &nodeK );
	CHECK( nodeB.getParent() == &nodeRoot );
	CHECK( nodeB.getSibling() == &nodeC );

	CHECK( nodeC.getChild() == &nodeR );
	CHECK( nodeC.getParent() == &nodeRoot );
	CHECK( nodeC.getSibling() == 0 );

	CHECK( nodeD.getChild() == &nodeF );
	CHECK( nodeD.getParent() == &nodeA );
	CHECK( nodeD.getSibling() == &nodeE );

	CHECK( nodeE.getChild() == 0 );
	CHECK( nodeE.getParent() == &nodeA );
	CHECK( nodeE.getSibling() == &nodeI );

	CHECK( nodeI.getChild() == &nodeG );
	CHECK( nodeI.getParent() == &nodeA );
	CHECK( nodeI.getSibling() == 0 );

	CHECK( nodeK.getChild() == 0 );
	CHECK( nodeK.getParent() == &nodeB );
	CHECK( nodeK.getSibling() == &nodeL );

	CHECK( nodeL.getChild() == &nodeM );
	CHECK( nodeL.getParent() == &nodeB );
	CHECK( nodeL.getSibling() == 0 );

	CHECK( nodeR.getChild() == &nodeO );
	CHECK( nodeR.getParent() == &nodeC );
	CHECK( nodeR.getSibling() == 0 );

	CHECK( nodeF.getChild() == &nodeH );
	CHECK( nodeF.getParent() == &nodeD );
	CHECK( nodeF.getSibling() == 0 );

	CHECK( nodeG.getChild() == 0 );
	CHECK( nodeG.getParent() == &nodeI );
	CHECK( nodeG.getSibling() == &nodeJ );

	CHECK( nodeJ.getChild() == 0 );
	CHECK( nodeJ.getParent() == &nodeI );
	CHECK( nodeJ.getSibling() == 0 );

	CHECK( nodeM.getChild() == 0 );
	CHECK( nodeM.getParent() == &nodeL );
	CHECK( nodeM.getSibling() == &nodeN );

	CHECK( nodeN.getChild() == 0 );
	CHECK( nodeN.getParent() == &nodeL );
	CHECK( nodeN.getSibling() == 0 );

	CHECK( nodeO.getChild() == 0 );
	CHECK( nodeO.getParent() == &nodeR );
	CHECK( nodeO.getSibling() == &nodeP );

	CHECK( nodeP.getChild() == &nodeS );
	CHECK( nodeP.getParent() == &nodeR );
	CHECK( nodeP.getSibling() == &nodeQ );

	CHECK( nodeQ.getChild() == 0 );
	CHECK( nodeQ.getParent() == &nodeR );
	CHECK( nodeQ.getSibling() == 0 );

	CHECK( nodeH.getChild() == 0 );
	CHECK( nodeH.getParent() == &nodeF );
	CHECK( nodeH.getSibling() == 0 );

	CHECK( nodeS.getChild() == &nodeT );
	CHECK( nodeS.getParent() == &nodeP );
	CHECK( nodeS.getSibling() == 0 );

	CHECK( nodeT.getChild() == 0 );
	CHECK( nodeT.getParent() == &nodeS );
	CHECK( nodeT.getSibling() == &nodeU );

	CHECK( nodeU.getChild() == 0 );
	CHECK( nodeU.getParent() == &nodeS );
	CHECK( nodeU.getSibling() == &nodeV );

	CHECK( nodeV.getChild() == 0 );
	CHECK( nodeV.getParent() == &nodeS );
	CHECK( nodeV.getSibling() == &nodeW );

	CHECK( nodeW.getChild() == 0 );
	CHECK( nodeW.getParent() == &nodeS );
	CHECK( nodeW.getSibling() == 0 );

	nodeS.dumpChildren();

	// visually verify it prints nodes: T,U,V,W

	nodeA.dumpChildren();

	// visually verify it prints nodes: D,E,I
}

TEST( fullTree_dumpSiblings, PCSNode_group ) {
	PCSTree tree;
	PCSTreeInfo info;
	PCSNode  *root;

	PCSNode nodeRoot( "Root" );
	PCSNode nodeA( "Node_A" );
	PCSNode nodeB( "Node_B" );
	PCSNode nodeC( "Node_C" );
	PCSNode nodeD( "Node_D" );
	PCSNode nodeE( "Node_E" );
	PCSNode nodeI( "Node_I" );
	PCSNode nodeK( "Node_K" );
	PCSNode nodeL( "Node_L" );
	PCSNode nodeR( "Node_R" );
	PCSNode nodeF( "Node_F" );
	PCSNode nodeG( "Node_G" );
	PCSNode nodeJ( "Node_J" );
	PCSNode nodeM( "Node_M" );
	PCSNode nodeN( "Node_N" );
	PCSNode nodeO( "Node_O" );
	PCSNode nodeP( "Node_P" );
	PCSNode nodeQ( "Node_Q" );
	PCSNode nodeH( "Node_H" );
	PCSNode nodeS( "Node_S" );
	PCSNode nodeT( "Node_T" );
	PCSNode nodeU( "Node_U" );
	PCSNode nodeV( "Node_V" );
	PCSNode nodeW( "Node_W" );

	root = tree.getRoot();

	tree.insert( &nodeRoot, root );

	tree.insert( &nodeC, &nodeRoot );
	tree.insert( &nodeB, &nodeRoot );
	tree.insert( &nodeA, &nodeRoot );
	tree.insert( &nodeI, &nodeA );
	tree.insert( &nodeE, &nodeA );
	tree.insert( &nodeD, &nodeA );
	tree.insert( &nodeL, &nodeB );
	tree.insert( &nodeK, &nodeB );
	tree.insert( &nodeR, &nodeC );
	tree.insert( &nodeF, &nodeD );
	tree.insert( &nodeJ, &nodeI );
	tree.insert( &nodeG, &nodeI );
	tree.insert( &nodeN, &nodeL );
	tree.insert( &nodeM, &nodeL );
	tree.insert( &nodeQ, &nodeR );
	tree.insert( &nodeP, &nodeR );
	tree.insert( &nodeO, &nodeR );
	tree.insert( &nodeH, &nodeF );
	tree.insert( &nodeS, &nodeP );
	tree.insert( &nodeW, &nodeS );
	tree.insert( &nodeV, &nodeS );
	tree.insert( &nodeU, &nodeS );
	tree.insert( &nodeT, &nodeS );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 24 );

	CHECK( nodeRoot.getChild() == &nodeA );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == &nodeD );
	CHECK( nodeA.getParent() == &nodeRoot );
	CHECK( nodeA.getSibling() == &nodeB );

	CHECK( nodeB.getChild() == &nodeK );
	CHECK( nodeB.getParent() == &nodeRoot );
	CHECK( nodeB.getSibling() == &nodeC );

	CHECK( nodeC.getChild() == &nodeR );
	CHECK( nodeC.getParent() == &nodeRoot );
	CHECK( nodeC.getSibling() == 0 );

	CHECK( nodeD.getChild() == &nodeF );
	CHECK( nodeD.getParent() == &nodeA );
	CHECK( nodeD.getSibling() == &nodeE );

	CHECK( nodeE.getChild() == 0 );
	CHECK( nodeE.getParent() == &nodeA );
	CHECK( nodeE.getSibling() == &nodeI );

	CHECK( nodeI.getChild() == &nodeG );
	CHECK( nodeI.getParent() == &nodeA );
	CHECK( nodeI.getSibling() == 0 );

	CHECK( nodeK.getChild() == 0 );
	CHECK( nodeK.getParent() == &nodeB );
	CHECK( nodeK.getSibling() == &nodeL );

	CHECK( nodeL.getChild() == &nodeM );
	CHECK( nodeL.getParent() == &nodeB );
	CHECK( nodeL.getSibling() == 0 );

	CHECK( nodeR.getChild() == &nodeO );
	CHECK( nodeR.getParent() == &nodeC );
	CHECK( nodeR.getSibling() == 0 );

	CHECK( nodeF.getChild() == &nodeH );
	CHECK( nodeF.getParent() == &nodeD );
	CHECK( nodeF.getSibling() == 0 );

	CHECK( nodeG.getChild() == 0 );
	CHECK( nodeG.getParent() == &nodeI );
	CHECK( nodeG.getSibling() == &nodeJ );

	CHECK( nodeJ.getChild() == 0 );
	CHECK( nodeJ.getParent() == &nodeI );
	CHECK( nodeJ.getSibling() == 0 );

	CHECK( nodeM.getChild() == 0 );
	CHECK( nodeM.getParent() == &nodeL );
	CHECK( nodeM.getSibling() == &nodeN );

	CHECK( nodeN.getChild() == 0 );
	CHECK( nodeN.getParent() == &nodeL );
	CHECK( nodeN.getSibling() == 0 );

	CHECK( nodeO.getChild() == 0 );
	CHECK( nodeO.getParent() == &nodeR );
	CHECK( nodeO.getSibling() == &nodeP );

	CHECK( nodeP.getChild() == &nodeS );
	CHECK( nodeP.getParent() == &nodeR );
	CHECK( nodeP.getSibling() == &nodeQ );

	CHECK( nodeQ.getChild() == 0 );
	CHECK( nodeQ.getParent() == &nodeR );
	CHECK( nodeQ.getSibling() == 0 );

	CHECK( nodeH.getChild() == 0 );
	CHECK( nodeH.getParent() == &nodeF );
	CHECK( nodeH.getSibling() == 0 );

	CHECK( nodeS.getChild() == &nodeT );
	CHECK( nodeS.getParent() == &nodeP );
	CHECK( nodeS.getSibling() == 0 );

	CHECK( nodeT.getChild() == 0 );
	CHECK( nodeT.getParent() == &nodeS );
	CHECK( nodeT.getSibling() == &nodeU );

	CHECK( nodeU.getChild() == 0 );
	CHECK( nodeU.getParent() == &nodeS );
	CHECK( nodeU.getSibling() == &nodeV );

	CHECK( nodeV.getChild() == 0 );
	CHECK( nodeV.getParent() == &nodeS );
	CHECK( nodeV.getSibling() == &nodeW );

	CHECK( nodeW.getChild() == 0 );
	CHECK( nodeW.getParent() == &nodeS );
	CHECK( nodeW.getSibling() == 0 );

	nodeE.dumpSiblings();

	// visually verify it prints nodes: D,E,I

	nodeI.dumpSiblings();

	// visually verify it prints nodes: D,E,I

	nodeD.dumpSiblings();

	// visually verify it prints nodes: D,E,I
}

TEST( fullTree_getNumChildren, PCSNode_group ) {
	PCSTree tree;
	PCSTreeInfo info;
	PCSNode  *root;

	PCSNode nodeRoot( "Root" );
	PCSNode nodeA( "Node_A" );
	PCSNode nodeB( "Node_B" );
	PCSNode nodeC( "Node_C" );
	PCSNode nodeD( "Node_D" );
	PCSNode nodeE( "Node_E" );
	PCSNode nodeI( "Node_I" );
	PCSNode nodeK( "Node_K" );
	PCSNode nodeL( "Node_L" );
	PCSNode nodeR( "Node_R" );
	PCSNode nodeF( "Node_F" );
	PCSNode nodeG( "Node_G" );
	PCSNode nodeJ( "Node_J" );
	PCSNode nodeM( "Node_M" );
	PCSNode nodeN( "Node_N" );
	PCSNode nodeO( "Node_O" );
	PCSNode nodeP( "Node_P" );
	PCSNode nodeQ( "Node_Q" );
	PCSNode nodeH( "Node_H" );
	PCSNode nodeS( "Node_S" );
	PCSNode nodeT( "Node_T" );
	PCSNode nodeU( "Node_U" );
	PCSNode nodeV( "Node_V" );
	PCSNode nodeW( "Node_W" );

	root = tree.getRoot();

	tree.insert( &nodeRoot, root );

	tree.insert( &nodeC, &nodeRoot );
	tree.insert( &nodeB, &nodeRoot );
	tree.insert( &nodeA, &nodeRoot );
	tree.insert( &nodeI, &nodeA );
	tree.insert( &nodeE, &nodeA );
	tree.insert( &nodeD, &nodeA );
	tree.insert( &nodeL, &nodeB );
	tree.insert( &nodeK, &nodeB );
	tree.insert( &nodeR, &nodeC );
	tree.insert( &nodeF, &nodeD );
	tree.insert( &nodeJ, &nodeI );
	tree.insert( &nodeG, &nodeI );
	tree.insert( &nodeN, &nodeL );
	tree.insert( &nodeM, &nodeL );
	tree.insert( &nodeQ, &nodeR );
	tree.insert( &nodeP, &nodeR );
	tree.insert( &nodeO, &nodeR );
	tree.insert( &nodeH, &nodeF );
	tree.insert( &nodeS, &nodeP );
	tree.insert( &nodeW, &nodeS );
	tree.insert( &nodeV, &nodeS );
	tree.insert( &nodeU, &nodeS );
	tree.insert( &nodeT, &nodeS );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 24 );

	CHECK( nodeRoot.getChild() == &nodeA );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == &nodeD );
	CHECK( nodeA.getParent() == &nodeRoot );
	CHECK( nodeA.getSibling() == &nodeB );

	CHECK( nodeB.getChild() == &nodeK );
	CHECK( nodeB.getParent() == &nodeRoot );
	CHECK( nodeB.getSibling() == &nodeC );

	CHECK( nodeC.getChild() == &nodeR );
	CHECK( nodeC.getParent() == &nodeRoot );
	CHECK( nodeC.getSibling() == 0 );

	CHECK( nodeD.getChild() == &nodeF );
	CHECK( nodeD.getParent() == &nodeA );
	CHECK( nodeD.getSibling() == &nodeE );

	CHECK( nodeE.getChild() == 0 );
	CHECK( nodeE.getParent() == &nodeA );
	CHECK( nodeE.getSibling() == &nodeI );

	CHECK( nodeI.getChild() == &nodeG );
	CHECK( nodeI.getParent() == &nodeA );
	CHECK( nodeI.getSibling() == 0 );

	CHECK( nodeK.getChild() == 0 );
	CHECK( nodeK.getParent() == &nodeB );
	CHECK( nodeK.getSibling() == &nodeL );

	CHECK( nodeL.getChild() == &nodeM );
	CHECK( nodeL.getParent() == &nodeB );
	CHECK( nodeL.getSibling() == 0 );

	CHECK( nodeR.getChild() == &nodeO );
	CHECK( nodeR.getParent() == &nodeC );
	CHECK( nodeR.getSibling() == 0 );

	CHECK( nodeF.getChild() == &nodeH );
	CHECK( nodeF.getParent() == &nodeD );
	CHECK( nodeF.getSibling() == 0 );

	CHECK( nodeG.getChild() == 0 );
	CHECK( nodeG.getParent() == &nodeI );
	CHECK( nodeG.getSibling() == &nodeJ );

	CHECK( nodeJ.getChild() == 0 );
	CHECK( nodeJ.getParent() == &nodeI );
	CHECK( nodeJ.getSibling() == 0 );

	CHECK( nodeM.getChild() == 0 );
	CHECK( nodeM.getParent() == &nodeL );
	CHECK( nodeM.getSibling() == &nodeN );

	CHECK( nodeN.getChild() == 0 );
	CHECK( nodeN.getParent() == &nodeL );
	CHECK( nodeN.getSibling() == 0 );

	CHECK( nodeO.getChild() == 0 );
	CHECK( nodeO.getParent() == &nodeR );
	CHECK( nodeO.getSibling() == &nodeP );

	CHECK( nodeP.getChild() == &nodeS );
	CHECK( nodeP.getParent() == &nodeR );
	CHECK( nodeP.getSibling() == &nodeQ );

	CHECK( nodeQ.getChild() == 0 );
	CHECK( nodeQ.getParent() == &nodeR );
	CHECK( nodeQ.getSibling() == 0 );

	CHECK( nodeH.getChild() == 0 );
	CHECK( nodeH.getParent() == &nodeF );
	CHECK( nodeH.getSibling() == 0 );

	CHECK( nodeS.getChild() == &nodeT );
	CHECK( nodeS.getParent() == &nodeP );
	CHECK( nodeS.getSibling() == 0 );

	CHECK( nodeT.getChild() == 0 );
	CHECK( nodeT.getParent() == &nodeS );
	CHECK( nodeT.getSibling() == &nodeU );

	CHECK( nodeU.getChild() == 0 );
	CHECK( nodeU.getParent() == &nodeS );
	CHECK( nodeU.getSibling() == &nodeV );

	CHECK( nodeV.getChild() == 0 );
	CHECK( nodeV.getParent() == &nodeS );
	CHECK( nodeV.getSibling() == &nodeW );

	CHECK( nodeW.getChild() == 0 );
	CHECK( nodeW.getParent() == &nodeS );
	CHECK( nodeW.getSibling() == 0 );

	CHECK( nodeH.getNumChildren() == 0 );
	CHECK( nodeF.getNumChildren() == 1 );
	CHECK( nodeD.getNumChildren() == 1 );
	CHECK( nodeA.getNumChildren() == 3 );
	CHECK( nodeE.getNumChildren() == 0 );
	CHECK( nodeI.getNumChildren() == 2 );
	CHECK( nodeG.getNumChildren() == 0 );
	CHECK( nodeJ.getNumChildren() == 0 );

	CHECK( nodeB.getNumChildren() == 2 );
	CHECK( nodeK.getNumChildren() == 0 );
	CHECK( nodeL.getNumChildren() == 2 );
	CHECK( nodeM.getNumChildren() == 0 );
	CHECK( nodeN.getNumChildren() == 0 );

	CHECK( nodeC.getNumChildren() == 1 );
	CHECK( nodeR.getNumChildren() == 3 );
	CHECK( nodeO.getNumChildren() == 0 );
	CHECK( nodeP.getNumChildren() == 1 );
	CHECK( nodeQ.getNumChildren() == 0 );
	CHECK( nodeS.getNumChildren() == 4 );
	CHECK( nodeT.getNumChildren() == 0 );
	CHECK( nodeU.getNumChildren() == 0 );
	CHECK( nodeV.getNumChildren() == 0 );
	CHECK( nodeW.getNumChildren() == 0 );

	CHECK( nodeRoot.getNumChildren() == 3 );
}

TEST( fullTree_getNumSiblings, PCSNode_group ) {
	PCSTree tree;
	PCSTreeInfo info;
	PCSNode  *root;

	PCSNode nodeRoot( "Root" );
	PCSNode nodeA( "Node_A" );
	PCSNode nodeB( "Node_B" );
	PCSNode nodeC( "Node_C" );
	PCSNode nodeD( "Node_D" );
	PCSNode nodeE( "Node_E" );
	PCSNode nodeI( "Node_I" );
	PCSNode nodeK( "Node_K" );
	PCSNode nodeL( "Node_L" );
	PCSNode nodeR( "Node_R" );
	PCSNode nodeF( "Node_F" );
	PCSNode nodeG( "Node_G" );
	PCSNode nodeJ( "Node_J" );
	PCSNode nodeM( "Node_M" );
	PCSNode nodeN( "Node_N" );
	PCSNode nodeO( "Node_O" );
	PCSNode nodeP( "Node_P" );
	PCSNode nodeQ( "Node_Q" );
	PCSNode nodeH( "Node_H" );
	PCSNode nodeS( "Node_S" );
	PCSNode nodeT( "Node_T" );
	PCSNode nodeU( "Node_U" );
	PCSNode nodeV( "Node_V" );
	PCSNode nodeW( "Node_W" );

	root = tree.getRoot();

	tree.insert( &nodeRoot, root );

	tree.insert( &nodeC, &nodeRoot );
	tree.insert( &nodeB, &nodeRoot );
	tree.insert( &nodeA, &nodeRoot );
	tree.insert( &nodeI, &nodeA );
	tree.insert( &nodeE, &nodeA );
	tree.insert( &nodeD, &nodeA );
	tree.insert( &nodeL, &nodeB );
	tree.insert( &nodeK, &nodeB );
	tree.insert( &nodeR, &nodeC );
	tree.insert( &nodeF, &nodeD );
	tree.insert( &nodeJ, &nodeI );
	tree.insert( &nodeG, &nodeI );
	tree.insert( &nodeN, &nodeL );
	tree.insert( &nodeM, &nodeL );
	tree.insert( &nodeQ, &nodeR );
	tree.insert( &nodeP, &nodeR );
	tree.insert( &nodeO, &nodeR );
	tree.insert( &nodeH, &nodeF );
	tree.insert( &nodeS, &nodeP );
	tree.insert( &nodeW, &nodeS );
	tree.insert( &nodeV, &nodeS );
	tree.insert( &nodeU, &nodeS );
	tree.insert( &nodeT, &nodeS );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 24 );

	CHECK( nodeRoot.getChild() == &nodeA );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == &nodeD );
	CHECK( nodeA.getParent() == &nodeRoot );
	CHECK( nodeA.getSibling() == &nodeB );

	CHECK( nodeB.getChild() == &nodeK );
	CHECK( nodeB.getParent() == &nodeRoot );
	CHECK( nodeB.getSibling() == &nodeC );

	CHECK( nodeC.getChild() == &nodeR );
	CHECK( nodeC.getParent() == &nodeRoot );
	CHECK( nodeC.getSibling() == 0 );

	CHECK( nodeD.getChild() == &nodeF );
	CHECK( nodeD.getParent() == &nodeA );
	CHECK( nodeD.getSibling() == &nodeE );

	CHECK( nodeE.getChild() == 0 );
	CHECK( nodeE.getParent() == &nodeA );
	CHECK( nodeE.getSibling() == &nodeI );

	CHECK( nodeI.getChild() == &nodeG );
	CHECK( nodeI.getParent() == &nodeA );
	CHECK( nodeI.getSibling() == 0 );

	CHECK( nodeK.getChild() == 0 );
	CHECK( nodeK.getParent() == &nodeB );
	CHECK( nodeK.getSibling() == &nodeL );

	CHECK( nodeL.getChild() == &nodeM );
	CHECK( nodeL.getParent() == &nodeB );
	CHECK( nodeL.getSibling() == 0 );

	CHECK( nodeR.getChild() == &nodeO );
	CHECK( nodeR.getParent() == &nodeC );
	CHECK( nodeR.getSibling() == 0 );

	CHECK( nodeF.getChild() == &nodeH );
	CHECK( nodeF.getParent() == &nodeD );
	CHECK( nodeF.getSibling() == 0 );

	CHECK( nodeG.getChild() == 0 );
	CHECK( nodeG.getParent() == &nodeI );
	CHECK( nodeG.getSibling() == &nodeJ );

	CHECK( nodeJ.getChild() == 0 );
	CHECK( nodeJ.getParent() == &nodeI );
	CHECK( nodeJ.getSibling() == 0 );

	CHECK( nodeM.getChild() == 0 );
	CHECK( nodeM.getParent() == &nodeL );
	CHECK( nodeM.getSibling() == &nodeN );

	CHECK( nodeN.getChild() == 0 );
	CHECK( nodeN.getParent() == &nodeL );
	CHECK( nodeN.getSibling() == 0 );

	CHECK( nodeO.getChild() == 0 );
	CHECK( nodeO.getParent() == &nodeR );
	CHECK( nodeO.getSibling() == &nodeP );

	CHECK( nodeP.getChild() == &nodeS );
	CHECK( nodeP.getParent() == &nodeR );
	CHECK( nodeP.getSibling() == &nodeQ );

	CHECK( nodeQ.getChild() == 0 );
	CHECK( nodeQ.getParent() == &nodeR );
	CHECK( nodeQ.getSibling() == 0 );

	CHECK( nodeH.getChild() == 0 );
	CHECK( nodeH.getParent() == &nodeF );
	CHECK( nodeH.getSibling() == 0 );

	CHECK( nodeS.getChild() == &nodeT );
	CHECK( nodeS.getParent() == &nodeP );
	CHECK( nodeS.getSibling() == 0 );

	CHECK( nodeT.getChild() == 0 );
	CHECK( nodeT.getParent() == &nodeS );
	CHECK( nodeT.getSibling() == &nodeU );

	CHECK( nodeU.getChild() == 0 );
	CHECK( nodeU.getParent() == &nodeS );
	CHECK( nodeU.getSibling() == &nodeV );

	CHECK( nodeV.getChild() == 0 );
	CHECK( nodeV.getParent() == &nodeS );
	CHECK( nodeV.getSibling() == &nodeW );

	CHECK( nodeW.getChild() == 0 );
	CHECK( nodeW.getParent() == &nodeS );
	CHECK( nodeW.getSibling() == 0 );

	CHECK( nodeH.getNumSiblings() == 1 );
	CHECK( nodeF.getNumSiblings() == 1 );
	CHECK( nodeD.getNumSiblings() == 3 );
	CHECK( nodeA.getNumSiblings() == 3 );
	CHECK( nodeE.getNumSiblings() == 3 );
	CHECK( nodeI.getNumSiblings() == 3 );
	CHECK( nodeG.getNumSiblings() == 2 );
	CHECK( nodeJ.getNumSiblings() == 2 );

	CHECK( nodeB.getNumSiblings() == 3 );
	CHECK( nodeK.getNumSiblings() == 2 );
	CHECK( nodeL.getNumSiblings() == 2 );
	CHECK( nodeM.getNumSiblings() == 2 );
	CHECK( nodeN.getNumSiblings() == 2 );

	CHECK( nodeC.getNumSiblings() == 3 );
	CHECK( nodeR.getNumSiblings() == 1 );
	CHECK( nodeO.getNumSiblings() == 3 );
	CHECK( nodeP.getNumSiblings() == 3 );
	CHECK( nodeQ.getNumSiblings() == 3 );
	CHECK( nodeS.getNumSiblings() == 1 );
	CHECK( nodeT.getNumSiblings() == 4 );
	CHECK( nodeU.getNumSiblings() == 4 );
	CHECK( nodeV.getNumSiblings() == 4 );
	CHECK( nodeW.getNumSiblings() == 4 );

	CHECK( nodeRoot.getNumSiblings() == 1 );
}