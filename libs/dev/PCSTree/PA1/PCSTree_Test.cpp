//---------------------------------------------------------------------------
// HEADER FILES:
//---------------------------------------------------------------------------
#include <string.h>
#include "UnitTest.h"
#include "PCSTree.h"
#include "PCSNode.h"

//---------------------------------------------------------------------------
// Test Files:
// Single step throught, set break points, but do not modify it
//---------------------------------------------------------------------------

TEST( constructor, PCSTree_group ) {
	PCSTree tree;
	PCSTreeInfo info;
	PCSNode  *root;

	tree.getInfo( info );
	root = tree.getRoot();

	CHECK( root == 0 );
	CHECK( info.maxNodeCount == 0 );
	CHECK( info.numLevels == 0 );
	CHECK( info.numNodes == 0 );
}

TEST( addNodeRoot, PCSTree_group ) {
	PCSTree tree;
	PCSTreeInfo info;
	PCSNode  *root;
	PCSNode nodeRoot( "Root" );

	CHECK( nodeRoot.getChild() == 0 );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	root = tree.getRoot();
	tree.insert( &nodeRoot, root );

	CHECK( nodeRoot.getChild() == 0 );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	root = tree.getRoot();
	CHECK( root == &nodeRoot );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 1 );
	CHECK( info.maxLevelCount == 1 );
	CHECK( info.numLevels == 1 );
	CHECK( info.numNodes == 1 );
}

TEST( addNodeRootA, PCSTree_group ) {
	PCSTree tree;
	PCSTreeInfo info;
	PCSNode  *root;
	PCSNode nodeRoot( "Root" );
	PCSNode nodeA( "Node_A" );

	CHECK( nodeRoot.getChild() == 0 );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	root = tree.getRoot();
	tree.insert( &nodeRoot, root );

	CHECK( nodeRoot.getChild() == 0 );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	root = tree.getRoot();
	CHECK( root == &nodeRoot );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 1 );
	CHECK( info.maxLevelCount == 1 );
	CHECK( info.numLevels == 1 );
	CHECK( info.numNodes == 1 );

	tree.insert( &nodeA, &nodeRoot );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 2 );
	CHECK( info.maxLevelCount == 2 );
	CHECK( info.numLevels == 2 );
	CHECK( info.numNodes == 2 );

	CHECK( nodeRoot.getChild() == &nodeA );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == 0 );
	CHECK( nodeA.getParent() == &nodeRoot );
	CHECK( nodeA.getSibling() == 0 );
}

TEST( addNodeRootAD, PCSTree_group ) {
	PCSTree tree;
	PCSTreeInfo info;
	PCSNode  *root;
	PCSNode nodeRoot( "Root" );
	PCSNode nodeA( "Node_A" );
	PCSNode nodeD( "Node_D" );

	CHECK( nodeRoot.getChild() == 0 );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	root = tree.getRoot();
	tree.insert( &nodeRoot, root );

	CHECK( nodeRoot.getChild() == 0 );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	root = tree.getRoot();
	CHECK( root == &nodeRoot );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 1 );
	CHECK( info.maxLevelCount == 1 );
	CHECK( info.numLevels == 1 );
	CHECK( info.numNodes == 1 );

	tree.insert( &nodeA, &nodeRoot );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 2 );
	CHECK( info.maxLevelCount == 2 );
	CHECK( info.numLevels == 2 );
	CHECK( info.numNodes == 2 );

	CHECK( nodeRoot.getChild() == &nodeA );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == 0 );
	CHECK( nodeA.getParent() == &nodeRoot );
	CHECK( nodeA.getSibling() == 0 );

	tree.insert( &nodeD, &nodeA );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 3 );
	CHECK( info.maxLevelCount == 3 );
	CHECK( info.numLevels == 3 );
	CHECK( info.numNodes == 3 );

	CHECK( nodeRoot.getChild() == &nodeA );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == &nodeD );
	CHECK( nodeA.getParent() == &nodeRoot );
	CHECK( nodeA.getSibling() == 0 );

	CHECK( nodeD.getChild() == 0 );
	CHECK( nodeD.getParent() == &nodeA );
	CHECK( nodeD.getSibling() == 0 );
}

TEST( addNodeRootADF, PCSTree_group ) {
	PCSTree tree;
	PCSTreeInfo info;
	PCSNode  *root;
	PCSNode nodeRoot( "Root" );
	PCSNode nodeA( "Node_A" );
	PCSNode nodeD( "Node_D" );
	PCSNode nodeF( "Node_F" );

	CHECK( nodeRoot.getChild() == 0 );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	root = tree.getRoot();
	tree.insert( &nodeRoot, root );

	CHECK( nodeRoot.getChild() == 0 );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	root = tree.getRoot();
	CHECK( root == &nodeRoot );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 1 );
	CHECK( info.maxLevelCount == 1 );
	CHECK( info.numLevels == 1 );
	CHECK( info.numNodes == 1 );

	tree.insert( &nodeA, &nodeRoot );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 2 );
	CHECK( info.maxLevelCount == 2 );
	CHECK( info.numLevels == 2 );
	CHECK( info.numNodes == 2 );

	CHECK( nodeRoot.getChild() == &nodeA );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == 0 );
	CHECK( nodeA.getParent() == &nodeRoot );
	CHECK( nodeA.getSibling() == 0 );

	tree.insert( &nodeD, &nodeA );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 3 );
	CHECK( info.maxLevelCount == 3 );
	CHECK( info.numLevels == 3 );
	CHECK( info.numNodes == 3 );

	CHECK( nodeRoot.getChild() == &nodeA );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == &nodeD );
	CHECK( nodeA.getParent() == &nodeRoot );
	CHECK( nodeA.getSibling() == 0 );

	CHECK( nodeD.getChild() == 0 );
	CHECK( nodeD.getParent() == &nodeA );
	CHECK( nodeD.getSibling() == 0 );

	tree.insert( &nodeF, &nodeD );
	tree.getInfo( info );

	CHECK( info.maxNodeCount == 4 );
	CHECK( info.maxLevelCount == 4 );
	CHECK( info.numLevels == 4 );
	CHECK( info.numNodes == 4 );

	CHECK( nodeRoot.getChild() == &nodeA );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == &nodeD );
	CHECK( nodeA.getParent() == &nodeRoot );
	CHECK( nodeA.getSibling() == 0 );

	CHECK( nodeD.getChild() == &nodeF );
	CHECK( nodeD.getParent() == &nodeA );
	CHECK( nodeD.getSibling() == 0 );

	CHECK( nodeF.getChild() == 0 );
	CHECK( nodeF.getParent() == &nodeD );
	CHECK( nodeF.getSibling() == 0 );
}

TEST( addNodeRootADFH, PCSTree_group ) {
	PCSTree tree;
	PCSTreeInfo info;
	PCSNode  *root;
	PCSNode nodeRoot( "Root" );
	PCSNode nodeA( "Node_A" );
	PCSNode nodeD( "Node_D" );
	PCSNode nodeF( "Node_F" );
	PCSNode nodeH( "Node_H" );

	root = tree.getRoot();
	tree.insert( &nodeRoot, root );
	tree.insert( &nodeA, &nodeRoot );
	tree.insert( &nodeD, &nodeA );
	tree.insert( &nodeF, &nodeD );
	tree.insert( &nodeH, &nodeF );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 5 );
	CHECK( info.maxLevelCount == 5 );
	CHECK( info.numLevels == 5 );
	CHECK( info.numNodes == 5 );

	CHECK( nodeRoot.getChild() == &nodeA );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == &nodeD );
	CHECK( nodeA.getParent() == &nodeRoot );
	CHECK( nodeA.getSibling() == 0 );

	CHECK( nodeD.getChild() == &nodeF );
	CHECK( nodeD.getParent() == &nodeA );
	CHECK( nodeD.getSibling() == 0 );

	CHECK( nodeF.getChild() == &nodeH );
	CHECK( nodeF.getParent() == &nodeD );
	CHECK( nodeF.getSibling() == 0 );

	CHECK( nodeH.getChild() == 0 );
	CHECK( nodeH.getParent() == &nodeF );
	CHECK( nodeH.getSibling() == 0 );
}

TEST( addNodeRootAB, PCSTree_group ) {
	PCSTree tree;
	PCSTreeInfo info;
	PCSNode  *root;
	PCSNode nodeRoot( "Root" );
	PCSNode nodeA( "Node_A" );
	PCSNode nodeB( "Node_B" );

	root = tree.getRoot();
	tree.insert( &nodeRoot, root );
	tree.insert( &nodeB, &nodeRoot );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 2 );
	CHECK( info.maxLevelCount == 2 );
	CHECK( info.numLevels == 2 );
	CHECK( info.numNodes == 2 );

	CHECK( nodeRoot.getChild() == &nodeB );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeB.getChild() == 0 );
	CHECK( nodeB.getParent() == &nodeRoot );
	CHECK( nodeB.getSibling() == 0 );

	tree.insert( &nodeA, &nodeRoot );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 3 );
	CHECK( info.maxLevelCount == 2 );
	CHECK( info.numLevels == 2 );
	CHECK( info.numNodes == 3 );

	CHECK( nodeRoot.getChild() == &nodeA );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeB.getChild() == 0 );
	CHECK( nodeB.getParent() == &nodeRoot );
	CHECK( nodeB.getSibling() == 0 );

	CHECK( nodeA.getChild() == 0 );
	CHECK( nodeA.getParent() == &nodeRoot );
	CHECK( nodeA.getSibling() == &nodeB );
}

TEST( addNodeRootABC, PCSTree_group ) {
	PCSTree tree;
	PCSTreeInfo info;
	PCSNode  *root;

	PCSNode nodeRoot( "Root" );
	PCSNode nodeA( "Node_A" );
	PCSNode nodeB( "Node_B" );
	PCSNode nodeC( "Node_C" );

	root = tree.getRoot();

	tree.insert( &nodeRoot, root );
	tree.insert( &nodeC, &nodeRoot );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 2 );
	CHECK( info.maxLevelCount == 2 );
	CHECK( info.numLevels == 2 );
	CHECK( info.numNodes == 2 );

	CHECK( nodeRoot.getChild() == &nodeC );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeC.getChild() == 0 );
	CHECK( nodeC.getParent() == &nodeRoot );
	CHECK( nodeC.getSibling() == 0 );

	tree.insert( &nodeB, &nodeRoot );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 3 );
	CHECK( info.maxLevelCount == 2 );
	CHECK( info.numLevels == 2 );
	CHECK( info.numNodes == 3 );

	CHECK( nodeRoot.getChild() == &nodeB );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeB.getChild() == 0 );
	CHECK( nodeB.getParent() == &nodeRoot );
	CHECK( nodeB.getSibling() == &nodeC );

	CHECK( nodeC.getChild() == 0 );
	CHECK( nodeC.getParent() == &nodeRoot );
	CHECK( nodeC.getSibling() == 0 );

	tree.insert( &nodeA, &nodeRoot );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 4 );
	CHECK( info.maxLevelCount == 2 );
	CHECK( info.numLevels == 2 );
	CHECK( info.numNodes == 4 );

	CHECK( nodeRoot.getChild() == &nodeA );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == 0 );
	CHECK( nodeA.getParent() == &nodeRoot );
	CHECK( nodeA.getSibling() == &nodeB );

	CHECK( nodeB.getChild() == 0 );
	CHECK( nodeB.getParent() == &nodeRoot );
	CHECK( nodeB.getSibling() == &nodeC );

	CHECK( nodeC.getChild() == 0 );
	CHECK( nodeC.getParent() == &nodeRoot );
	CHECK( nodeC.getSibling() == 0 );
}

TEST( addNodeRootABCDEI, PCSTree_group ) {
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

	root = tree.getRoot();

	tree.insert( &nodeRoot, root );
	tree.insert( &nodeC, &nodeRoot );
	tree.insert( &nodeB, &nodeRoot );
	tree.insert( &nodeA, &nodeRoot );
	tree.insert( &nodeI, &nodeA );
	tree.insert( &nodeE, &nodeA );
	tree.insert( &nodeD, &nodeA );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 7 );
	CHECK( info.maxLevelCount == 3 );
	CHECK( info.numLevels == 3 );
	CHECK( info.numNodes == 7 );

	CHECK( nodeRoot.getChild() == &nodeA );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == &nodeD );
	CHECK( nodeA.getParent() == &nodeRoot );
	CHECK( nodeA.getSibling() == &nodeB );

	CHECK( nodeB.getChild() == 0 );
	CHECK( nodeB.getParent() == &nodeRoot );
	CHECK( nodeB.getSibling() == &nodeC );

	CHECK( nodeC.getChild() == 0 );
	CHECK( nodeC.getParent() == &nodeRoot );
	CHECK( nodeC.getSibling() == 0 );

	CHECK( nodeD.getChild() == 0 );
	CHECK( nodeD.getParent() == &nodeA );
	CHECK( nodeD.getSibling() == &nodeE );

	CHECK( nodeE.getChild() == 0 );
	CHECK( nodeE.getParent() == &nodeA );
	CHECK( nodeE.getSibling() == &nodeI );

	CHECK( nodeI.getChild() == 0 );
	CHECK( nodeI.getParent() == &nodeA );
	CHECK( nodeI.getSibling() == 0 );
}

TEST( addNodeRootABCDEIKL, PCSTree_group ) {
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

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 9 );
	CHECK( info.maxLevelCount == 3 );
	CHECK( info.numLevels == 3 );
	CHECK( info.numNodes == 9 );

	CHECK( nodeRoot.getChild() == &nodeA );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == &nodeD );
	CHECK( nodeA.getParent() == &nodeRoot );
	CHECK( nodeA.getSibling() == &nodeB );

	CHECK( nodeB.getChild() == &nodeK );
	CHECK( nodeB.getParent() == &nodeRoot );
	CHECK( nodeB.getSibling() == &nodeC );

	CHECK( nodeC.getChild() == 0 );
	CHECK( nodeC.getParent() == &nodeRoot );
	CHECK( nodeC.getSibling() == 0 );

	CHECK( nodeD.getChild() == 0 );
	CHECK( nodeD.getParent() == &nodeA );
	CHECK( nodeD.getSibling() == &nodeE );

	CHECK( nodeE.getChild() == 0 );
	CHECK( nodeE.getParent() == &nodeA );
	CHECK( nodeE.getSibling() == &nodeI );

	CHECK( nodeI.getChild() == 0 );
	CHECK( nodeI.getParent() == &nodeA );
	CHECK( nodeI.getSibling() == 0 );

	CHECK( nodeK.getChild() == 0 );
	CHECK( nodeK.getParent() == &nodeB );
	CHECK( nodeK.getSibling() == &nodeL );

	CHECK( nodeL.getChild() == 0 );
	CHECK( nodeL.getParent() == &nodeB );
	CHECK( nodeL.getSibling() == 0 );
}

TEST( addNodeRootABCDEIKLR, PCSTree_group ) {
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

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 10 );
	CHECK( info.maxLevelCount == 3 );
	CHECK( info.numLevels == 3 );
	CHECK( info.numNodes == 10 );

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

	CHECK( nodeD.getChild() == 0 );
	CHECK( nodeD.getParent() == &nodeA );
	CHECK( nodeD.getSibling() == &nodeE );

	CHECK( nodeE.getChild() == 0 );
	CHECK( nodeE.getParent() == &nodeA );
	CHECK( nodeE.getSibling() == &nodeI );

	CHECK( nodeI.getChild() == 0 );
	CHECK( nodeI.getParent() == &nodeA );
	CHECK( nodeI.getSibling() == 0 );

	CHECK( nodeK.getChild() == 0 );
	CHECK( nodeK.getParent() == &nodeB );
	CHECK( nodeK.getSibling() == &nodeL );

	CHECK( nodeL.getChild() == 0 );
	CHECK( nodeL.getParent() == &nodeB );
	CHECK( nodeL.getSibling() == 0 );

	CHECK( nodeR.getChild() == 0 );
	CHECK( nodeR.getParent() == &nodeC );
	CHECK( nodeR.getSibling() == 0 );
}

TEST( addNodeRootABCDEIKLRFGJ, PCSTree_group ) {
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

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 13 );
	CHECK( info.maxLevelCount == 4 );
	CHECK( info.numLevels == 4 );
	CHECK( info.numNodes == 13 );

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

	CHECK( nodeL.getChild() == 0 );
	CHECK( nodeL.getParent() == &nodeB );
	CHECK( nodeL.getSibling() == 0 );

	CHECK( nodeR.getChild() == 0 );
	CHECK( nodeR.getParent() == &nodeC );
	CHECK( nodeR.getSibling() == 0 );

	CHECK( nodeF.getChild() == 0 );
	CHECK( nodeF.getParent() == &nodeD );
	CHECK( nodeF.getSibling() == 0 );

	CHECK( nodeG.getChild() == 0 );
	CHECK( nodeG.getParent() == &nodeI );
	CHECK( nodeG.getSibling() == &nodeJ );

	CHECK( nodeJ.getChild() == 0 );
	CHECK( nodeJ.getParent() == &nodeI );
	CHECK( nodeJ.getSibling() == 0 );
}

TEST( addNodeRootABCDEIKLRFGJMNOPQ, PCSTree_group ) {
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

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 18 );
	CHECK( info.maxLevelCount == 4 );
	CHECK( info.numLevels == 4 );
	CHECK( info.numNodes == 18 );

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

	CHECK( nodeF.getChild() == 0 );
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

	CHECK( nodeP.getChild() == 0 );
	CHECK( nodeP.getParent() == &nodeR );
	CHECK( nodeP.getSibling() == &nodeQ );

	CHECK( nodeQ.getChild() == 0 );
	CHECK( nodeQ.getParent() == &nodeR );
	CHECK( nodeQ.getSibling() == 0 );
}

TEST( addNodeRootABCDEIKLRFGJMNOPQHS, PCSTree_group ) {
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

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 20 );
	CHECK( info.maxLevelCount == 5 );
	CHECK( info.numLevels == 5 );
	CHECK( info.numNodes == 20 );

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

	CHECK( nodeS.getChild() == 0 );
	CHECK( nodeS.getParent() == &nodeP );
	CHECK( nodeS.getSibling() == 0 );
}

TEST( addNodeRootABCDEIKLRFGJMNOPQHSTUVW, PCSTree_group ) {
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
}

TEST( fullTree_RemoveW, PCSTree_group ) {
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

	// Remove W
	tree.remove( &nodeW );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 23 );

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
	CHECK( nodeV.getSibling() == 0 );

	CHECK( nodeW.getChild() == 0 );
	CHECK( nodeW.getParent() == 0 );
	CHECK( nodeW.getSibling() == 0 );
}

TEST( fullTree_RemoveV, PCSTree_group ) {
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

	// Remove V
	tree.remove( &nodeV );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 23 );

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
	CHECK( nodeU.getSibling() == &nodeW );

	CHECK( nodeV.getChild() == 0 );
	CHECK( nodeV.getParent() == 0 );
	CHECK( nodeV.getSibling() == 0 );

	CHECK( nodeW.getChild() == 0 );
	CHECK( nodeW.getParent() == &nodeS );
	CHECK( nodeW.getSibling() == 0 );
}

TEST( fullTree_RemoveU, PCSTree_group ) {
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

	// Remove U
	tree.remove( &nodeU );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 23 );

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
	CHECK( nodeT.getSibling() == &nodeV );

	CHECK( nodeU.getChild() == 0 );
	CHECK( nodeU.getParent() == 0 );
	CHECK( nodeU.getSibling() == 0 );

	CHECK( nodeV.getChild() == 0 );
	CHECK( nodeV.getParent() == &nodeS );
	CHECK( nodeV.getSibling() == &nodeW );

	CHECK( nodeW.getChild() == 0 );
	CHECK( nodeW.getParent() == &nodeS );
	CHECK( nodeW.getSibling() == 0 );
}

TEST( fullTree_RemoveT, PCSTree_group ) {
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

	// Remove T
	tree.remove( &nodeT );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 23 );

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

	CHECK( nodeS.getChild() == &nodeU );
	CHECK( nodeS.getParent() == &nodeP );
	CHECK( nodeS.getSibling() == 0 );

	CHECK( nodeT.getChild() == 0 );
	CHECK( nodeT.getParent() == 0 );
	CHECK( nodeT.getSibling() == 0 );

	CHECK( nodeU.getChild() == 0 );
	CHECK( nodeU.getParent() == &nodeS );
	CHECK( nodeU.getSibling() == &nodeV );

	CHECK( nodeV.getChild() == 0 );
	CHECK( nodeV.getParent() == &nodeS );
	CHECK( nodeV.getSibling() == &nodeW );

	CHECK( nodeW.getChild() == 0 );
	CHECK( nodeW.getParent() == &nodeS );
	CHECK( nodeW.getSibling() == 0 );
}

TEST( fullTree_RemoveH, PCSTree_group ) {
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

	// Remove H
	tree.remove( &nodeH );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 23 );

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

	CHECK( nodeF.getChild() == 0 );
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
	CHECK( nodeH.getParent() == 0 );
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
}

TEST( fullTree_RemoveQ, PCSTree_group ) {
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

	// Remove Q
	tree.remove( &nodeQ );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 23 );

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
	CHECK( nodeP.getSibling() == 0 );

	CHECK( nodeQ.getChild() == 0 );
	CHECK( nodeQ.getParent() == 0 );
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
}

TEST( fullTree_RemoveO, PCSTree_group ) {
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

	// Remove O
	tree.remove( &nodeO );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 23 );

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

	CHECK( nodeR.getChild() == &nodeP );
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
	CHECK( nodeO.getParent() == 0 );
	CHECK( nodeO.getSibling() == 0 );

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
}

TEST( fullTree_RemoveK, PCSTree_group ) {
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

	// Remove K
	tree.remove( &nodeK );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 23 );

	CHECK( nodeRoot.getChild() == &nodeA );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == &nodeD );
	CHECK( nodeA.getParent() == &nodeRoot );
	CHECK( nodeA.getSibling() == &nodeB );

	CHECK( nodeB.getChild() == &nodeL );
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
	CHECK( nodeK.getParent() == 0 );
	CHECK( nodeK.getSibling() == 0 );

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
}

TEST( fullTree_RemoveM, PCSTree_group ) {
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

	// Remove M
	tree.remove( &nodeM );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 23 );

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

	CHECK( nodeL.getChild() == &nodeN );
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
	CHECK( nodeM.getParent() == 0 );
	CHECK( nodeM.getSibling() == 0 );

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
}

TEST( fullTree_RemoveN, PCSTree_group ) {
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

	// Remove N
	tree.remove( &nodeN );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 23 );

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
	CHECK( nodeM.getSibling() == 0 );

	CHECK( nodeN.getChild() == 0 );
	CHECK( nodeN.getParent() == 0 );
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
}

TEST( fullTree_RemoveJ, PCSTree_group ) {
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

	// Remove J
	tree.remove( &nodeJ );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 23 );

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
	CHECK( nodeG.getSibling() == 0 );

	CHECK( nodeJ.getChild() == 0 );
	CHECK( nodeJ.getParent() == 0 );
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
}

TEST( fullTree_RemoveG, PCSTree_group ) {
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

	// Remove G
	tree.remove( &nodeG );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 23 );

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

	CHECK( nodeI.getChild() == &nodeJ );
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
	CHECK( nodeG.getParent() == 0 );
	CHECK( nodeG.getSibling() == 0 );

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
}

TEST( fullTree_RemoveE, PCSTree_group ) {
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

	// Remove E
	tree.remove( &nodeE );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 23 );

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
	CHECK( nodeD.getSibling() == &nodeI );

	CHECK( nodeE.getChild() == 0 );
	CHECK( nodeE.getParent() == 0 );
	CHECK( nodeE.getSibling() == 0 );

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
}

TEST( fullTree_RemoveF, PCSTree_group ) {
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

	// Remove F
	tree.remove( &nodeF );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 22 );

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

	CHECK( nodeD.getChild() == 0 );
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

	CHECK( nodeF.getChild() == 0 );
	CHECK( nodeF.getParent() == 0 );
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
	CHECK( nodeH.getParent() == 0 );
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
}

TEST( fullTree_RemoveD, PCSTree_group ) {
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

	// Remove D
	tree.remove( &nodeD );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 21 );

	CHECK( nodeRoot.getChild() == &nodeA );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == &nodeE );
	CHECK( nodeA.getParent() == &nodeRoot );
	CHECK( nodeA.getSibling() == &nodeB );

	CHECK( nodeB.getChild() == &nodeK );
	CHECK( nodeB.getParent() == &nodeRoot );
	CHECK( nodeB.getSibling() == &nodeC );

	CHECK( nodeC.getChild() == &nodeR );
	CHECK( nodeC.getParent() == &nodeRoot );
	CHECK( nodeC.getSibling() == 0 );

	CHECK( nodeD.getChild() == 0 );
	CHECK( nodeD.getParent() == 0 );
	CHECK( nodeD.getSibling() == 0 );

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

	CHECK( nodeF.getChild() == 0 );
	CHECK( nodeF.getParent() == 0 );
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
	CHECK( nodeH.getParent() == 0 );
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
}

TEST( fullTree_RemoveI, PCSTree_group ) {
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

	// Remove I
	tree.remove( &nodeI );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 21 );

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
	CHECK( nodeE.getSibling() == 0 );

	CHECK( nodeI.getChild() == 0 );
	CHECK( nodeI.getParent() == 0 );
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
	CHECK( nodeG.getParent() == 0 );
	CHECK( nodeG.getSibling() == 0 );

	CHECK( nodeJ.getChild() == 0 );
	CHECK( nodeJ.getParent() == 0 );
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
}

TEST( fullTree_RemoveL, PCSTree_group ) {
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

	// Remove L
	tree.remove( &nodeL );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 21 );

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
	CHECK( nodeK.getSibling() == 0 );

	CHECK( nodeL.getChild() == 0 );
	CHECK( nodeL.getParent() == 0 );
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
	CHECK( nodeM.getParent() == 0 );
	CHECK( nodeM.getSibling() == 0 );

	CHECK( nodeN.getChild() == 0 );
	CHECK( nodeN.getParent() == 0 );
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
}

TEST( fullTree_RemoveS, PCSTree_group ) {
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

	// Remove S
	tree.remove( &nodeS );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 5 );
	CHECK( info.numNodes == 19 );

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

	CHECK( nodeP.getChild() == 0 );
	CHECK( nodeP.getParent() == &nodeR );
	CHECK( nodeP.getSibling() == &nodeQ );

	CHECK( nodeQ.getChild() == 0 );
	CHECK( nodeQ.getParent() == &nodeR );
	CHECK( nodeQ.getSibling() == 0 );

	CHECK( nodeH.getChild() == 0 );
	CHECK( nodeH.getParent() == &nodeF );
	CHECK( nodeH.getSibling() == 0 );

	CHECK( nodeS.getChild() == 0 );
	CHECK( nodeS.getParent() == 0 );
	CHECK( nodeS.getSibling() == 0 );

	CHECK( nodeT.getChild() == 0 );
	CHECK( nodeT.getParent() == 0 );
	CHECK( nodeT.getSibling() == 0 );

	CHECK( nodeU.getChild() == 0 );
	CHECK( nodeU.getParent() == 0 );
	CHECK( nodeU.getSibling() == 0 );

	CHECK( nodeV.getChild() == 0 );
	CHECK( nodeV.getParent() == 0 );
	CHECK( nodeV.getSibling() == 0 );

	CHECK( nodeW.getChild() == 0 );
	CHECK( nodeW.getParent() == 0 );
	CHECK( nodeW.getSibling() == 0 );
}

TEST( fullTree_RemoveP, PCSTree_group ) {
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

	// Remove P
	tree.remove( &nodeP );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 5 );
	CHECK( info.numNodes == 18 );

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
	CHECK( nodeO.getSibling() == &nodeQ );

	CHECK( nodeP.getChild() == 0 );
	CHECK( nodeP.getParent() == 0 );
	CHECK( nodeP.getSibling() == 0 );

	CHECK( nodeQ.getChild() == 0 );
	CHECK( nodeQ.getParent() == &nodeR );
	CHECK( nodeQ.getSibling() == 0 );

	CHECK( nodeH.getChild() == 0 );
	CHECK( nodeH.getParent() == &nodeF );
	CHECK( nodeH.getSibling() == 0 );

	CHECK( nodeS.getChild() == 0 );
	CHECK( nodeS.getParent() == 0 );
	CHECK( nodeS.getSibling() == 0 );

	CHECK( nodeT.getChild() == 0 );
	CHECK( nodeT.getParent() == 0 );
	CHECK( nodeT.getSibling() == 0 );

	CHECK( nodeU.getChild() == 0 );
	CHECK( nodeU.getParent() == 0 );
	CHECK( nodeU.getSibling() == 0 );

	CHECK( nodeV.getChild() == 0 );
	CHECK( nodeV.getParent() == 0 );
	CHECK( nodeV.getSibling() == 0 );

	CHECK( nodeW.getChild() == 0 );
	CHECK( nodeW.getParent() == 0 );
	CHECK( nodeW.getSibling() == 0 );
}

TEST( fullTree_RemoveR, PCSTree_group ) {
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

	// Remove R
	tree.remove( &nodeR );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 5 );
	CHECK( info.numNodes == 15 );

	CHECK( nodeRoot.getChild() == &nodeA );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == &nodeD );
	CHECK( nodeA.getParent() == &nodeRoot );
	CHECK( nodeA.getSibling() == &nodeB );

	CHECK( nodeB.getChild() == &nodeK );
	CHECK( nodeB.getParent() == &nodeRoot );
	CHECK( nodeB.getSibling() == &nodeC );

	CHECK( nodeC.getChild() == 0 );
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

	CHECK( nodeR.getChild() == 0 );
	CHECK( nodeR.getParent() == 0 );
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
	CHECK( nodeO.getParent() == 0 );
	CHECK( nodeO.getSibling() == 0 );

	CHECK( nodeP.getChild() == 0 );
	CHECK( nodeP.getParent() == 0 );
	CHECK( nodeP.getSibling() == 0 );

	CHECK( nodeQ.getChild() == 0 );
	CHECK( nodeQ.getParent() == 0 );
	CHECK( nodeQ.getSibling() == 0 );

	CHECK( nodeH.getChild() == 0 );
	CHECK( nodeH.getParent() == &nodeF );
	CHECK( nodeH.getSibling() == 0 );

	CHECK( nodeS.getChild() == 0 );
	CHECK( nodeS.getParent() == 0 );
	CHECK( nodeS.getSibling() == 0 );

	CHECK( nodeT.getChild() == 0 );
	CHECK( nodeT.getParent() == 0 );
	CHECK( nodeT.getSibling() == 0 );

	CHECK( nodeU.getChild() == 0 );
	CHECK( nodeU.getParent() == 0 );
	CHECK( nodeU.getSibling() == 0 );

	CHECK( nodeV.getChild() == 0 );
	CHECK( nodeV.getParent() == 0 );
	CHECK( nodeV.getSibling() == 0 );

	CHECK( nodeW.getChild() == 0 );
	CHECK( nodeW.getParent() == 0 );
	CHECK( nodeW.getSibling() == 0 );
}

TEST( fullTree_RemoveC, PCSTree_group ) {
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

	// Remove C
	tree.remove( &nodeC );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 5 );
	CHECK( info.numNodes == 14 );

	CHECK( nodeRoot.getChild() == &nodeA );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == &nodeD );
	CHECK( nodeA.getParent() == &nodeRoot );
	CHECK( nodeA.getSibling() == &nodeB );

	CHECK( nodeB.getChild() == &nodeK );
	CHECK( nodeB.getParent() == &nodeRoot );
	CHECK( nodeB.getSibling() == 0 );

	CHECK( nodeC.getChild() == 0 );
	CHECK( nodeC.getParent() == 0 );
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

	CHECK( nodeR.getChild() == 0 );
	CHECK( nodeR.getParent() == 0 );
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
	CHECK( nodeO.getParent() == 0 );
	CHECK( nodeO.getSibling() == 0 );

	CHECK( nodeP.getChild() == 0 );
	CHECK( nodeP.getParent() == 0 );
	CHECK( nodeP.getSibling() == 0 );

	CHECK( nodeQ.getChild() == 0 );
	CHECK( nodeQ.getParent() == 0 );
	CHECK( nodeQ.getSibling() == 0 );

	CHECK( nodeH.getChild() == 0 );
	CHECK( nodeH.getParent() == &nodeF );
	CHECK( nodeH.getSibling() == 0 );

	CHECK( nodeS.getChild() == 0 );
	CHECK( nodeS.getParent() == 0 );
	CHECK( nodeS.getSibling() == 0 );

	CHECK( nodeT.getChild() == 0 );
	CHECK( nodeT.getParent() == 0 );
	CHECK( nodeT.getSibling() == 0 );

	CHECK( nodeU.getChild() == 0 );
	CHECK( nodeU.getParent() == 0 );
	CHECK( nodeU.getSibling() == 0 );

	CHECK( nodeV.getChild() == 0 );
	CHECK( nodeV.getParent() == 0 );
	CHECK( nodeV.getSibling() == 0 );

	CHECK( nodeW.getChild() == 0 );
	CHECK( nodeW.getParent() == 0 );
	CHECK( nodeW.getSibling() == 0 );
}

TEST( fullTree_RemoveB, PCSTree_group ) {
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

	// Remove B
	tree.remove( &nodeB );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 19 );

	CHECK( nodeRoot.getChild() == &nodeA );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == &nodeD );
	CHECK( nodeA.getParent() == &nodeRoot );
	CHECK( nodeA.getSibling() == &nodeC );

	CHECK( nodeB.getChild() == 0 );
	CHECK( nodeB.getParent() == 0 );
	CHECK( nodeB.getSibling() == 0 );

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
	CHECK( nodeK.getParent() == 0 );
	CHECK( nodeK.getSibling() == 0 );

	CHECK( nodeL.getChild() == 0 );
	CHECK( nodeL.getParent() == 0 );
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
	CHECK( nodeM.getParent() == 0 );
	CHECK( nodeM.getSibling() == 0 );

	CHECK( nodeN.getChild() == 0 );
	CHECK( nodeN.getParent() == 0 );
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
}

TEST( fullTree_RemoveA, PCSTree_group ) {
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

	// Remove A
	tree.remove( &nodeA );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 16 );

	CHECK( nodeRoot.getChild() == &nodeB );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == 0 );
	CHECK( nodeA.getParent() == 0 );
	CHECK( nodeA.getSibling() == 0 );

	CHECK( nodeB.getChild() == &nodeK );
	CHECK( nodeB.getParent() == &nodeRoot );
	CHECK( nodeB.getSibling() == &nodeC );

	CHECK( nodeC.getChild() == &nodeR );
	CHECK( nodeC.getParent() == &nodeRoot );
	CHECK( nodeC.getSibling() == 0 );

	CHECK( nodeD.getChild() == 0 );
	CHECK( nodeD.getParent() == 0 );
	CHECK( nodeD.getSibling() == 0 );

	CHECK( nodeE.getChild() == 0 );
	CHECK( nodeE.getParent() == 0 );
	CHECK( nodeE.getSibling() == 0 );

	CHECK( nodeI.getChild() == 0 );
	CHECK( nodeI.getParent() == 0 );
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

	CHECK( nodeF.getChild() == 0 );
	CHECK( nodeF.getParent() == 0 );
	CHECK( nodeF.getSibling() == 0 );

	CHECK( nodeG.getChild() == 0 );
	CHECK( nodeG.getParent() == 0 );
	CHECK( nodeG.getSibling() == 0 );

	CHECK( nodeJ.getChild() == 0 );
	CHECK( nodeJ.getParent() == 0 );
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
	CHECK( nodeH.getParent() == 0 );
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
}

TEST( fullTree_RemoveRoot, PCSTree_group ) {
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

	// RemoveROOT
	tree.remove( &nodeRoot );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 0 );
	CHECK( info.numNodes == 0 );

	CHECK( nodeRoot.getChild() == 0 );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == 0 );
	CHECK( nodeA.getParent() == 0 );
	CHECK( nodeA.getSibling() == 0 );

	CHECK( nodeB.getChild() == 0 );
	CHECK( nodeB.getParent() == 0 );
	CHECK( nodeB.getSibling() == 0 );

	CHECK( nodeC.getChild() == 0 );
	CHECK( nodeC.getParent() == 0 );
	CHECK( nodeC.getSibling() == 0 );

	CHECK( nodeD.getChild() == 0 );
	CHECK( nodeD.getParent() == 0 );
	CHECK( nodeD.getSibling() == 0 );

	CHECK( nodeE.getChild() == 0 );
	CHECK( nodeE.getParent() == 0 );
	CHECK( nodeE.getSibling() == 0 );

	CHECK( nodeI.getChild() == 0 );
	CHECK( nodeI.getParent() == 0 );
	CHECK( nodeI.getSibling() == 0 );

	CHECK( nodeK.getChild() == 0 );
	CHECK( nodeK.getParent() == 0 );
	CHECK( nodeK.getSibling() == 0 );

	CHECK( nodeL.getChild() == 0 );
	CHECK( nodeL.getParent() == 0 );
	CHECK( nodeL.getSibling() == 0 );

	CHECK( nodeR.getChild() == 0 );
	CHECK( nodeR.getParent() == 0 );
	CHECK( nodeR.getSibling() == 0 );

	CHECK( nodeF.getChild() == 0 );
	CHECK( nodeF.getParent() == 0 );
	CHECK( nodeF.getSibling() == 0 );

	CHECK( nodeG.getChild() == 0 );
	CHECK( nodeG.getParent() == 0 );
	CHECK( nodeG.getSibling() == 0 );

	CHECK( nodeJ.getChild() == 0 );
	CHECK( nodeJ.getParent() == 0 );
	CHECK( nodeJ.getSibling() == 0 );

	CHECK( nodeM.getChild() == 0 );
	CHECK( nodeM.getParent() == 0 );
	CHECK( nodeM.getSibling() == 0 );

	CHECK( nodeN.getChild() == 0 );
	CHECK( nodeN.getParent() == 0 );
	CHECK( nodeN.getSibling() == 0 );

	CHECK( nodeO.getChild() == 0 );
	CHECK( nodeO.getParent() == 0 );
	CHECK( nodeO.getSibling() == 0 );

	CHECK( nodeP.getChild() == 0 );
	CHECK( nodeP.getParent() == 0 );
	CHECK( nodeP.getSibling() == 0 );

	CHECK( nodeQ.getChild() == 0 );
	CHECK( nodeQ.getParent() == 0 );
	CHECK( nodeQ.getSibling() == 0 );

	CHECK( nodeH.getChild() == 0 );
	CHECK( nodeH.getParent() == 0 );
	CHECK( nodeH.getSibling() == 0 );

	CHECK( nodeS.getChild() == 0 );
	CHECK( nodeS.getParent() == 0 );
	CHECK( nodeS.getSibling() == 0 );

	CHECK( nodeT.getChild() == 0 );
	CHECK( nodeT.getParent() == 0 );
	CHECK( nodeT.getSibling() == 0 );

	CHECK( nodeU.getChild() == 0 );
	CHECK( nodeU.getParent() == 0 );
	CHECK( nodeU.getSibling() == 0 );

	CHECK( nodeV.getChild() == 0 );
	CHECK( nodeV.getParent() == 0 );
	CHECK( nodeV.getSibling() == 0 );

	CHECK( nodeW.getChild() == 0 );
	CHECK( nodeW.getParent() == 0 );
	CHECK( nodeW.getSibling() == 0 );
}

TEST( fullTree_dumpTree, PCSNode_group ) {
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

	tree.dumpTree();
}

TEST( fullTree_CheckLevel_C_children, PCSNode_group ) {
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

	tree.remove( &nodeA );
	tree.remove( &nodeB );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 6 );
	CHECK( info.numNodes == 11 );

	CHECK( nodeRoot.getChild() == &nodeC );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == 0 );
	CHECK( nodeA.getParent() == 0 );
	CHECK( nodeA.getSibling() == 0 );

	CHECK( nodeB.getChild() == 0 );
	CHECK( nodeB.getParent() == 0 );
	CHECK( nodeB.getSibling() == 0 );

	CHECK( nodeC.getChild() == &nodeR );
	CHECK( nodeC.getParent() == &nodeRoot );
	CHECK( nodeC.getSibling() == 0 );

	CHECK( nodeD.getChild() == 0 );
	CHECK( nodeD.getParent() == 0 );
	CHECK( nodeD.getSibling() == 0 );

	CHECK( nodeE.getChild() == 0 );
	CHECK( nodeE.getParent() == 0 );
	CHECK( nodeE.getSibling() == 0 );

	CHECK( nodeI.getChild() == 0 );
	CHECK( nodeI.getParent() == 0 );
	CHECK( nodeI.getSibling() == 0 );

	CHECK( nodeK.getChild() == 0 );
	CHECK( nodeK.getParent() == 0 );
	CHECK( nodeK.getSibling() == 0 );

	CHECK( nodeL.getChild() == 0 );
	CHECK( nodeL.getParent() == 0 );
	CHECK( nodeL.getSibling() == 0 );

	CHECK( nodeR.getChild() == &nodeO );
	CHECK( nodeR.getParent() == &nodeC );
	CHECK( nodeR.getSibling() == 0 );

	CHECK( nodeF.getChild() == 0 );
	CHECK( nodeF.getParent() == 0 );
	CHECK( nodeF.getSibling() == 0 );

	CHECK( nodeG.getChild() == 0 );
	CHECK( nodeG.getParent() == 0 );
	CHECK( nodeG.getSibling() == 0 );

	CHECK( nodeJ.getChild() == 0 );
	CHECK( nodeJ.getParent() == 0 );
	CHECK( nodeJ.getSibling() == 0 );

	CHECK( nodeM.getChild() == 0 );
	CHECK( nodeM.getParent() == 0 );
	CHECK( nodeM.getSibling() == 0 );

	CHECK( nodeN.getChild() == 0 );
	CHECK( nodeN.getParent() == 0 );
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
	CHECK( nodeH.getParent() == 0 );
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
}

TEST( fullTree_CheckLevel_C_children_remove_TUVW, PCSNode_group ) {
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

	tree.remove( &nodeA );
	tree.remove( &nodeB );
	tree.remove( &nodeT );
	tree.remove( &nodeU );
	tree.remove( &nodeV );
	tree.remove( &nodeW );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 5 );
	CHECK( info.numNodes == 7 );

	CHECK( nodeRoot.getChild() == &nodeC );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == 0 );
	CHECK( nodeA.getParent() == 0 );
	CHECK( nodeA.getSibling() == 0 );

	CHECK( nodeB.getChild() == 0 );
	CHECK( nodeB.getParent() == 0 );
	CHECK( nodeB.getSibling() == 0 );

	CHECK( nodeC.getChild() == &nodeR );
	CHECK( nodeC.getParent() == &nodeRoot );
	CHECK( nodeC.getSibling() == 0 );

	CHECK( nodeD.getChild() == 0 );
	CHECK( nodeD.getParent() == 0 );
	CHECK( nodeD.getSibling() == 0 );

	CHECK( nodeE.getChild() == 0 );
	CHECK( nodeE.getParent() == 0 );
	CHECK( nodeE.getSibling() == 0 );

	CHECK( nodeI.getChild() == 0 );
	CHECK( nodeI.getParent() == 0 );
	CHECK( nodeI.getSibling() == 0 );

	CHECK( nodeK.getChild() == 0 );
	CHECK( nodeK.getParent() == 0 );
	CHECK( nodeK.getSibling() == 0 );

	CHECK( nodeL.getChild() == 0 );
	CHECK( nodeL.getParent() == 0 );
	CHECK( nodeL.getSibling() == 0 );

	CHECK( nodeR.getChild() == &nodeO );
	CHECK( nodeR.getParent() == &nodeC );
	CHECK( nodeR.getSibling() == 0 );

	CHECK( nodeF.getChild() == 0 );
	CHECK( nodeF.getParent() == 0 );
	CHECK( nodeF.getSibling() == 0 );

	CHECK( nodeG.getChild() == 0 );
	CHECK( nodeG.getParent() == 0 );
	CHECK( nodeG.getSibling() == 0 );

	CHECK( nodeJ.getChild() == 0 );
	CHECK( nodeJ.getParent() == 0 );
	CHECK( nodeJ.getSibling() == 0 );

	CHECK( nodeM.getChild() == 0 );
	CHECK( nodeM.getParent() == 0 );
	CHECK( nodeM.getSibling() == 0 );

	CHECK( nodeN.getChild() == 0 );
	CHECK( nodeN.getParent() == 0 );
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
	CHECK( nodeH.getParent() == 0 );
	CHECK( nodeH.getSibling() == 0 );

	CHECK( nodeS.getChild() == 0 );
	CHECK( nodeS.getParent() == &nodeP );
	CHECK( nodeS.getSibling() == 0 );

	CHECK( nodeT.getChild() == 0 );
	CHECK( nodeT.getParent() == 0 );
	CHECK( nodeT.getSibling() == 0 );

	CHECK( nodeU.getChild() == 0 );
	CHECK( nodeU.getParent() == 0 );
	CHECK( nodeU.getSibling() == 0 );

	CHECK( nodeV.getChild() == 0 );
	CHECK( nodeV.getParent() == 0 );
	CHECK( nodeV.getSibling() == 0 );

	CHECK( nodeW.getChild() == 0 );
	CHECK( nodeW.getParent() == 0 );
	CHECK( nodeW.getSibling() == 0 );
}

TEST( fullTree_CheckLevel_C_children_remove_S, PCSNode_group ) {
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

	tree.remove( &nodeA );
	tree.remove( &nodeB );
	tree.remove( &nodeS );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 4 );
	CHECK( info.numNodes == 6 );

	CHECK( nodeRoot.getChild() == &nodeC );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == 0 );
	CHECK( nodeA.getParent() == 0 );
	CHECK( nodeA.getSibling() == 0 );

	CHECK( nodeB.getChild() == 0 );
	CHECK( nodeB.getParent() == 0 );
	CHECK( nodeB.getSibling() == 0 );

	CHECK( nodeC.getChild() == &nodeR );
	CHECK( nodeC.getParent() == &nodeRoot );
	CHECK( nodeC.getSibling() == 0 );

	CHECK( nodeD.getChild() == 0 );
	CHECK( nodeD.getParent() == 0 );
	CHECK( nodeD.getSibling() == 0 );

	CHECK( nodeE.getChild() == 0 );
	CHECK( nodeE.getParent() == 0 );
	CHECK( nodeE.getSibling() == 0 );

	CHECK( nodeI.getChild() == 0 );
	CHECK( nodeI.getParent() == 0 );
	CHECK( nodeI.getSibling() == 0 );

	CHECK( nodeK.getChild() == 0 );
	CHECK( nodeK.getParent() == 0 );
	CHECK( nodeK.getSibling() == 0 );

	CHECK( nodeL.getChild() == 0 );
	CHECK( nodeL.getParent() == 0 );
	CHECK( nodeL.getSibling() == 0 );

	CHECK( nodeR.getChild() == &nodeO );
	CHECK( nodeR.getParent() == &nodeC );
	CHECK( nodeR.getSibling() == 0 );

	CHECK( nodeF.getChild() == 0 );
	CHECK( nodeF.getParent() == 0 );
	CHECK( nodeF.getSibling() == 0 );

	CHECK( nodeG.getChild() == 0 );
	CHECK( nodeG.getParent() == 0 );
	CHECK( nodeG.getSibling() == 0 );

	CHECK( nodeJ.getChild() == 0 );
	CHECK( nodeJ.getParent() == 0 );
	CHECK( nodeJ.getSibling() == 0 );

	CHECK( nodeM.getChild() == 0 );
	CHECK( nodeM.getParent() == 0 );
	CHECK( nodeM.getSibling() == 0 );

	CHECK( nodeN.getChild() == 0 );
	CHECK( nodeN.getParent() == 0 );
	CHECK( nodeN.getSibling() == 0 );

	CHECK( nodeO.getChild() == 0 );
	CHECK( nodeO.getParent() == &nodeR );
	CHECK( nodeO.getSibling() == &nodeP );

	CHECK( nodeP.getChild() == 0 );
	CHECK( nodeP.getParent() == &nodeR );
	CHECK( nodeP.getSibling() == &nodeQ );

	CHECK( nodeQ.getChild() == 0 );
	CHECK( nodeQ.getParent() == &nodeR );
	CHECK( nodeQ.getSibling() == 0 );

	CHECK( nodeH.getChild() == 0 );
	CHECK( nodeH.getParent() == 0 );
	CHECK( nodeH.getSibling() == 0 );

	CHECK( nodeS.getChild() == 0 );
	CHECK( nodeS.getParent() == 0 );
	CHECK( nodeS.getSibling() == 0 );

	CHECK( nodeT.getChild() == 0 );
	CHECK( nodeT.getParent() == 0 );
	CHECK( nodeT.getSibling() == 0 );

	CHECK( nodeU.getChild() == 0 );
	CHECK( nodeU.getParent() == 0 );
	CHECK( nodeU.getSibling() == 0 );

	CHECK( nodeV.getChild() == 0 );
	CHECK( nodeV.getParent() == 0 );
	CHECK( nodeV.getSibling() == 0 );

	CHECK( nodeW.getChild() == 0 );
	CHECK( nodeW.getParent() == 0 );
	CHECK( nodeW.getSibling() == 0 );
}

TEST( fullTree_CheckLevel_C_children_remove_OPQ, PCSNode_group ) {
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

	tree.remove( &nodeA );
	tree.remove( &nodeB );
	tree.remove( &nodeO );
	tree.remove( &nodeP );
	tree.remove( &nodeQ );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 3 );
	CHECK( info.numNodes == 3 );

	CHECK( nodeRoot.getChild() == &nodeC );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == 0 );
	CHECK( nodeA.getParent() == 0 );
	CHECK( nodeA.getSibling() == 0 );

	CHECK( nodeB.getChild() == 0 );
	CHECK( nodeB.getParent() == 0 );
	CHECK( nodeB.getSibling() == 0 );

	CHECK( nodeC.getChild() == &nodeR );
	CHECK( nodeC.getParent() == &nodeRoot );
	CHECK( nodeC.getSibling() == 0 );

	CHECK( nodeD.getChild() == 0 );
	CHECK( nodeD.getParent() == 0 );
	CHECK( nodeD.getSibling() == 0 );

	CHECK( nodeE.getChild() == 0 );
	CHECK( nodeE.getParent() == 0 );
	CHECK( nodeE.getSibling() == 0 );

	CHECK( nodeI.getChild() == 0 );
	CHECK( nodeI.getParent() == 0 );
	CHECK( nodeI.getSibling() == 0 );

	CHECK( nodeK.getChild() == 0 );
	CHECK( nodeK.getParent() == 0 );
	CHECK( nodeK.getSibling() == 0 );

	CHECK( nodeL.getChild() == 0 );
	CHECK( nodeL.getParent() == 0 );
	CHECK( nodeL.getSibling() == 0 );

	CHECK( nodeR.getChild() == 0 );
	CHECK( nodeR.getParent() == &nodeC );
	CHECK( nodeR.getSibling() == 0 );

	CHECK( nodeF.getChild() == 0 );
	CHECK( nodeF.getParent() == 0 );
	CHECK( nodeF.getSibling() == 0 );

	CHECK( nodeG.getChild() == 0 );
	CHECK( nodeG.getParent() == 0 );
	CHECK( nodeG.getSibling() == 0 );

	CHECK( nodeJ.getChild() == 0 );
	CHECK( nodeJ.getParent() == 0 );
	CHECK( nodeJ.getSibling() == 0 );

	CHECK( nodeM.getChild() == 0 );
	CHECK( nodeM.getParent() == 0 );
	CHECK( nodeM.getSibling() == 0 );

	CHECK( nodeN.getChild() == 0 );
	CHECK( nodeN.getParent() == 0 );
	CHECK( nodeN.getSibling() == 0 );

	CHECK( nodeO.getChild() == 0 );
	CHECK( nodeO.getParent() == 0 );
	CHECK( nodeO.getSibling() == 0 );

	CHECK( nodeP.getChild() == 0 );
	CHECK( nodeP.getParent() == 0 );
	CHECK( nodeP.getSibling() == 0 );

	CHECK( nodeQ.getChild() == 0 );
	CHECK( nodeQ.getParent() == 0 );
	CHECK( nodeQ.getSibling() == 0 );

	CHECK( nodeH.getChild() == 0 );
	CHECK( nodeH.getParent() == 0 );
	CHECK( nodeH.getSibling() == 0 );

	CHECK( nodeS.getChild() == 0 );
	CHECK( nodeS.getParent() == 0 );
	CHECK( nodeS.getSibling() == 0 );

	CHECK( nodeT.getChild() == 0 );
	CHECK( nodeT.getParent() == 0 );
	CHECK( nodeT.getSibling() == 0 );

	CHECK( nodeU.getChild() == 0 );
	CHECK( nodeU.getParent() == 0 );
	CHECK( nodeU.getSibling() == 0 );

	CHECK( nodeV.getChild() == 0 );
	CHECK( nodeV.getParent() == 0 );
	CHECK( nodeV.getSibling() == 0 );

	CHECK( nodeW.getChild() == 0 );
	CHECK( nodeW.getParent() == 0 );
	CHECK( nodeW.getSibling() == 0 );
}

TEST( fullTree_CheckLevel_C_children_remove_R, PCSNode_group ) {
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

	tree.remove( &nodeA );
	tree.remove( &nodeB );
	tree.remove( &nodeR );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 2 );
	CHECK( info.numNodes == 2 );

	CHECK( nodeRoot.getChild() == &nodeC );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == 0 );
	CHECK( nodeA.getParent() == 0 );
	CHECK( nodeA.getSibling() == 0 );

	CHECK( nodeB.getChild() == 0 );
	CHECK( nodeB.getParent() == 0 );
	CHECK( nodeB.getSibling() == 0 );

	CHECK( nodeC.getChild() == 0 );
	CHECK( nodeC.getParent() == &nodeRoot );
	CHECK( nodeC.getSibling() == 0 );

	CHECK( nodeD.getChild() == 0 );
	CHECK( nodeD.getParent() == 0 );
	CHECK( nodeD.getSibling() == 0 );

	CHECK( nodeE.getChild() == 0 );
	CHECK( nodeE.getParent() == 0 );
	CHECK( nodeE.getSibling() == 0 );

	CHECK( nodeI.getChild() == 0 );
	CHECK( nodeI.getParent() == 0 );
	CHECK( nodeI.getSibling() == 0 );

	CHECK( nodeK.getChild() == 0 );
	CHECK( nodeK.getParent() == 0 );
	CHECK( nodeK.getSibling() == 0 );

	CHECK( nodeL.getChild() == 0 );
	CHECK( nodeL.getParent() == 0 );
	CHECK( nodeL.getSibling() == 0 );

	CHECK( nodeR.getChild() == 0 );
	CHECK( nodeR.getParent() == 0 );
	CHECK( nodeR.getSibling() == 0 );

	CHECK( nodeF.getChild() == 0 );
	CHECK( nodeF.getParent() == 0 );
	CHECK( nodeF.getSibling() == 0 );

	CHECK( nodeG.getChild() == 0 );
	CHECK( nodeG.getParent() == 0 );
	CHECK( nodeG.getSibling() == 0 );

	CHECK( nodeJ.getChild() == 0 );
	CHECK( nodeJ.getParent() == 0 );
	CHECK( nodeJ.getSibling() == 0 );

	CHECK( nodeM.getChild() == 0 );
	CHECK( nodeM.getParent() == 0 );
	CHECK( nodeM.getSibling() == 0 );

	CHECK( nodeN.getChild() == 0 );
	CHECK( nodeN.getParent() == 0 );
	CHECK( nodeN.getSibling() == 0 );

	CHECK( nodeO.getChild() == 0 );
	CHECK( nodeO.getParent() == 0 );
	CHECK( nodeO.getSibling() == 0 );

	CHECK( nodeP.getChild() == 0 );
	CHECK( nodeP.getParent() == 0 );
	CHECK( nodeP.getSibling() == 0 );

	CHECK( nodeQ.getChild() == 0 );
	CHECK( nodeQ.getParent() == 0 );
	CHECK( nodeQ.getSibling() == 0 );

	CHECK( nodeH.getChild() == 0 );
	CHECK( nodeH.getParent() == 0 );
	CHECK( nodeH.getSibling() == 0 );

	CHECK( nodeS.getChild() == 0 );
	CHECK( nodeS.getParent() == 0 );
	CHECK( nodeS.getSibling() == 0 );

	CHECK( nodeT.getChild() == 0 );
	CHECK( nodeT.getParent() == 0 );
	CHECK( nodeT.getSibling() == 0 );

	CHECK( nodeU.getChild() == 0 );
	CHECK( nodeU.getParent() == 0 );
	CHECK( nodeU.getSibling() == 0 );

	CHECK( nodeV.getChild() == 0 );
	CHECK( nodeV.getParent() == 0 );
	CHECK( nodeV.getSibling() == 0 );

	CHECK( nodeW.getChild() == 0 );
	CHECK( nodeW.getParent() == 0 );
	CHECK( nodeW.getSibling() == 0 );
}

TEST( fullTree_CheckLevel_C_children_remove_C, PCSNode_group ) {
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

	tree.remove( &nodeA );
	tree.remove( &nodeB );
	tree.remove( &nodeC );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 1 );
	CHECK( info.numNodes == 1 );

	CHECK( nodeRoot.getChild() == 0 );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == 0 );
	CHECK( nodeA.getParent() == 0 );
	CHECK( nodeA.getSibling() == 0 );

	CHECK( nodeB.getChild() == 0 );
	CHECK( nodeB.getParent() == 0 );
	CHECK( nodeB.getSibling() == 0 );

	CHECK( nodeC.getChild() == 0 );
	CHECK( nodeC.getParent() == 0 );
	CHECK( nodeC.getSibling() == 0 );

	CHECK( nodeD.getChild() == 0 );
	CHECK( nodeD.getParent() == 0 );
	CHECK( nodeD.getSibling() == 0 );

	CHECK( nodeE.getChild() == 0 );
	CHECK( nodeE.getParent() == 0 );
	CHECK( nodeE.getSibling() == 0 );

	CHECK( nodeI.getChild() == 0 );
	CHECK( nodeI.getParent() == 0 );
	CHECK( nodeI.getSibling() == 0 );

	CHECK( nodeK.getChild() == 0 );
	CHECK( nodeK.getParent() == 0 );
	CHECK( nodeK.getSibling() == 0 );

	CHECK( nodeL.getChild() == 0 );
	CHECK( nodeL.getParent() == 0 );
	CHECK( nodeL.getSibling() == 0 );

	CHECK( nodeR.getChild() == 0 );
	CHECK( nodeR.getParent() == 0 );
	CHECK( nodeR.getSibling() == 0 );

	CHECK( nodeF.getChild() == 0 );
	CHECK( nodeF.getParent() == 0 );
	CHECK( nodeF.getSibling() == 0 );

	CHECK( nodeG.getChild() == 0 );
	CHECK( nodeG.getParent() == 0 );
	CHECK( nodeG.getSibling() == 0 );

	CHECK( nodeJ.getChild() == 0 );
	CHECK( nodeJ.getParent() == 0 );
	CHECK( nodeJ.getSibling() == 0 );

	CHECK( nodeM.getChild() == 0 );
	CHECK( nodeM.getParent() == 0 );
	CHECK( nodeM.getSibling() == 0 );

	CHECK( nodeN.getChild() == 0 );
	CHECK( nodeN.getParent() == 0 );
	CHECK( nodeN.getSibling() == 0 );

	CHECK( nodeO.getChild() == 0 );
	CHECK( nodeO.getParent() == 0 );
	CHECK( nodeO.getSibling() == 0 );

	CHECK( nodeP.getChild() == 0 );
	CHECK( nodeP.getParent() == 0 );
	CHECK( nodeP.getSibling() == 0 );

	CHECK( nodeQ.getChild() == 0 );
	CHECK( nodeQ.getParent() == 0 );
	CHECK( nodeQ.getSibling() == 0 );

	CHECK( nodeH.getChild() == 0 );
	CHECK( nodeH.getParent() == 0 );
	CHECK( nodeH.getSibling() == 0 );

	CHECK( nodeS.getChild() == 0 );
	CHECK( nodeS.getParent() == 0 );
	CHECK( nodeS.getSibling() == 0 );

	CHECK( nodeT.getChild() == 0 );
	CHECK( nodeT.getParent() == 0 );
	CHECK( nodeT.getSibling() == 0 );

	CHECK( nodeU.getChild() == 0 );
	CHECK( nodeU.getParent() == 0 );
	CHECK( nodeU.getSibling() == 0 );

	CHECK( nodeV.getChild() == 0 );
	CHECK( nodeV.getParent() == 0 );
	CHECK( nodeV.getSibling() == 0 );

	CHECK( nodeW.getChild() == 0 );
	CHECK( nodeW.getParent() == 0 );
	CHECK( nodeW.getSibling() == 0 );
}

TEST( fullTree_CheckLevel_C_children_remove_root, PCSNode_group ) {
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

	tree.remove( &nodeRoot );

	tree.getInfo( info );

	CHECK( info.maxNodeCount == 24 );
	CHECK( info.maxLevelCount == 6 );
	CHECK( info.numLevels == 0 );
	CHECK( info.numNodes == 0 );

	CHECK( nodeRoot.getChild() == 0 );
	CHECK( nodeRoot.getParent() == 0 );
	CHECK( nodeRoot.getSibling() == 0 );

	CHECK( nodeA.getChild() == 0 );
	CHECK( nodeA.getParent() == 0 );
	CHECK( nodeA.getSibling() == 0 );

	CHECK( nodeB.getChild() == 0 );
	CHECK( nodeB.getParent() == 0 );
	CHECK( nodeB.getSibling() == 0 );

	CHECK( nodeC.getChild() == 0 );
	CHECK( nodeC.getParent() == 0 );
	CHECK( nodeC.getSibling() == 0 );

	CHECK( nodeD.getChild() == 0 );
	CHECK( nodeD.getParent() == 0 );
	CHECK( nodeD.getSibling() == 0 );

	CHECK( nodeE.getChild() == 0 );
	CHECK( nodeE.getParent() == 0 );
	CHECK( nodeE.getSibling() == 0 );

	CHECK( nodeI.getChild() == 0 );
	CHECK( nodeI.getParent() == 0 );
	CHECK( nodeI.getSibling() == 0 );

	CHECK( nodeK.getChild() == 0 );
	CHECK( nodeK.getParent() == 0 );
	CHECK( nodeK.getSibling() == 0 );

	CHECK( nodeL.getChild() == 0 );
	CHECK( nodeL.getParent() == 0 );
	CHECK( nodeL.getSibling() == 0 );

	CHECK( nodeR.getChild() == 0 );
	CHECK( nodeR.getParent() == 0 );
	CHECK( nodeR.getSibling() == 0 );

	CHECK( nodeF.getChild() == 0 );
	CHECK( nodeF.getParent() == 0 );
	CHECK( nodeF.getSibling() == 0 );

	CHECK( nodeG.getChild() == 0 );
	CHECK( nodeG.getParent() == 0 );
	CHECK( nodeG.getSibling() == 0 );

	CHECK( nodeJ.getChild() == 0 );
	CHECK( nodeJ.getParent() == 0 );
	CHECK( nodeJ.getSibling() == 0 );

	CHECK( nodeM.getChild() == 0 );
	CHECK( nodeM.getParent() == 0 );
	CHECK( nodeM.getSibling() == 0 );

	CHECK( nodeN.getChild() == 0 );
	CHECK( nodeN.getParent() == 0 );
	CHECK( nodeN.getSibling() == 0 );

	CHECK( nodeO.getChild() == 0 );
	CHECK( nodeO.getParent() == 0 );
	CHECK( nodeO.getSibling() == 0 );

	CHECK( nodeP.getChild() == 0 );
	CHECK( nodeP.getParent() == 0 );
	CHECK( nodeP.getSibling() == 0 );

	CHECK( nodeQ.getChild() == 0 );
	CHECK( nodeQ.getParent() == 0 );
	CHECK( nodeQ.getSibling() == 0 );

	CHECK( nodeH.getChild() == 0 );
	CHECK( nodeH.getParent() == 0 );
	CHECK( nodeH.getSibling() == 0 );

	CHECK( nodeS.getChild() == 0 );
	CHECK( nodeS.getParent() == 0 );
	CHECK( nodeS.getSibling() == 0 );

	CHECK( nodeT.getChild() == 0 );
	CHECK( nodeT.getParent() == 0 );
	CHECK( nodeT.getSibling() == 0 );

	CHECK( nodeU.getChild() == 0 );
	CHECK( nodeU.getParent() == 0 );
	CHECK( nodeU.getSibling() == 0 );

	CHECK( nodeV.getChild() == 0 );
	CHECK( nodeV.getParent() == 0 );
	CHECK( nodeV.getSibling() == 0 );

	CHECK( nodeW.getChild() == 0 );
	CHECK( nodeW.getParent() == 0 );
	CHECK( nodeW.getSibling() == 0 );
}