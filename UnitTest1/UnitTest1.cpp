#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab12.9/lab12.9.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(InsertSingleElement) {
            Node* root = nullptr;
            root = insertBST(root, 50);
            Assert::IsNotNull(root);
            Assert::AreEqual(50, root->data);
        }

        TEST_METHOD(InsertMultipleElements) {
            Node* root = nullptr;
            root = insertBST(root, 50);
            root = insertBST(root, 30);
            root = insertBST(root, 70);

            Assert::AreEqual(50, root->data);
            Assert::IsNotNull(root->left);
            Assert::IsNotNull(root->right);
            Assert::AreEqual(30, root->left->data);
            Assert::AreEqual(70, root->right->data);
        }

        TEST_METHOD(DeleteLeafNode) {
            Node* root = nullptr;
            root = insertBST(root, 50);
            root = insertBST(root, 30);
            root = insertBST(root, 70);
            root = deleteNode(root, 30);

            Assert::IsNotNull(root);
            Assert::IsNull(root->left);
            Assert::IsNotNull(root->right);
        }

        TEST_METHOD(DeleteNodeWithOneChild) {
            Node* root = nullptr;
            root = insertBST(root, 50);
            root = insertBST(root, 30);
            root = insertBST(root, 70);
            root = insertBST(root, 60);
            root = deleteNode(root, 70);

            Assert::IsNotNull(root);
            Assert::IsNotNull(root->right);
            Assert::AreEqual(60, root->right->data);
        }

        TEST_METHOD(DeleteNodeWithTwoChildren) {
            Node* root = nullptr;
            root = insertBST(root, 50);
            root = insertBST(root, 30);
            root = insertBST(root, 70);
            root = insertBST(root, 60);
            root = insertBST(root, 80);
            root = deleteNode(root, 70);

            Assert::IsNotNull(root);
            Assert::IsNotNull(root->right);
            Assert::AreEqual(80, root->right->data);
            Assert::IsNotNull(root->right->left);
            Assert::AreEqual(60, root->right->left->data);
        }

        TEST_METHOD(BalanceBST) {
            Node* root = nullptr;
            root = insertBST(root, 30);
            root = insertBST(root, 20);
            root = insertBST(root, 40);
            root = insertBST(root, 10);
            root = insertBST(root, 25);
            root = insertBST(root, 35);
            root = insertBST(root, 50);

            int size = countNodes(root);
            int* array = new int[size];
            int index = 0;
            inorderToArray(root, array, &index);
            deleteTree(root);
            root = balanceBST(array, 0, size - 1);
            delete[] array;

            Assert::IsNotNull(root);
            Assert::AreEqual(30, root->data);
            Assert::IsNotNull(root->left);
            Assert::IsNotNull(root->right);
        }
	};
}